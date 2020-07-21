/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/// @todo Implement proper support for vehicle+player teleportation
/// @todo Use spell victory/defeat in wg instead of RewardMarkOfHonor() && RewardHonor
/// @todo Add proper implement of achievement

#include "BattlefieldWG.h"
#include "AchievementMgr.h"
#include "BattlefieldMgr.h"
#include "Battleground.h"
#include "CreatureTextMgr.h"
#include "GameObject.h"
#include "GameTime.h"
#include "Log.h"
#include "MapManager.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "Player.h"
#include "Random.h"
#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "SpellAuras.h"
#include "TemporarySummon.h"
#include "World.h"
#include "WorldSession.h"
#include "WorldStatePackets.h"

struct BfWGCoordGY
{
    Position Pos;
    uint32 GraveyardID;
    uint32 TextID;          // for gossip menu
    TeamId StartControl;
};

// 7 in sql, 7 in header
BfWGCoordGY const WGGraveyard[BATTLEFIELD_WG_GRAVEYARD_MAX] =
{
    { { 5104.750f, 2300.940f, 368.579f, 0.733038f }, 1329, BATTLEFIELD_WG_GOSSIPTEXT_GY_NE,       TEAM_NEUTRAL  },
    { { 5099.120f, 3466.036f, 368.484f, 5.317802f }, 1330, BATTLEFIELD_WG_GOSSIPTEXT_GY_NW,       TEAM_NEUTRAL  },
    { { 4314.648f, 2408.522f, 392.642f, 6.268125f }, 1333, BATTLEFIELD_WG_GOSSIPTEXT_GY_SE,       TEAM_NEUTRAL  },
    { { 4331.716f, 3235.695f, 390.251f, 0.008500f }, 1334, BATTLEFIELD_WG_GOSSIPTEXT_GY_SW,       TEAM_NEUTRAL  },
    { { 5537.986f, 2897.493f, 517.057f, 4.819249f }, 1285, BATTLEFIELD_WG_GOSSIPTEXT_GY_KEEP,     TEAM_NEUTRAL  },
    { { 5032.454f, 3711.382f, 372.468f, 3.971623f }, 1331, BATTLEFIELD_WG_GOSSIPTEXT_GY_HORDE,    TEAM_HORDE    },
    { { 5140.790f, 2179.120f, 390.950f, 1.972220f }, 1332, BATTLEFIELD_WG_GOSSIPTEXT_GY_ALLIANCE, TEAM_ALLIANCE },
};

uint32 const ClockWorldState[]         = { 3781, 4354 };
uint32 const WintergraspFaction[]      = { FACTION_ALLIANCE_GENERIC_WG, FACTION_HORDE_GENERIC_WG, FACTION_FRIENDLY };
//TEAM_ALLIANCE/TEAM_HORDE
uint32 const NPCGuardFaction[] = { 1891, 1979 };
//TEAM_ALLIANCE/TEAM_HORDE
uint32 const NPCMechanicFaction[] = { 1732, 1735 };
/*
    WEST_TOWER_GUARD,
    MIDDLE_TOWER_GUARD,
    EAST_TOWER_GUARD,

    WEST_BRIDGE_GUARD,
    MIDDLE_BRIDGE_GUARD,
    EAST_BRIDGE_GUARD,

    WEST_TOWER_TURRET,
    MIDDLE_TOWER_TURRET,
    EAST_TOWER_TURRET,

    // Defender sector
    NE_TOWER_GUARD,
    NW_TOWER_GUARD,
    SE_TOWER_GUARD,
    SW_TOWER_GUARD,
    FORTRESS_GATE_GUARD,
    VAULT_GATE_GUARD,

    FORTRESS_GATE_TURRET,
    VAULT_GATE_TURRET,
    NE_TOWER_TURRET,
    NW_TOWER_TURRET,
    SE_TOWER_TURRET,
    SW_TOWER_TURRET,

    //workshop sector
    WG_WORKSHOP_SE_GUARD,
    WG_WORKSHOP_SW_GUARD,
    WG_WORKSHOP_NE_GUARD,
    WG_WORKSHOP_NW_GUARD,
    WG_WORKSHOP_KEEP_WEST_GUARD,
    WG_WORKSHOP_KEEP_EAST_GUARD
*/
uint32 const NPCGroup[] = {
GO_WINTERGRASP_SHADOWSIGHT_TOWER,
GO_WINTERGRASP_WINTER_S_EDGE_TOWER,
GO_WINTERGRASP_FLAMEWATCH_TOWER,

GO_WINTERGRASP_FORTRESS_GATE,
GO_WINTERGRASP_FORTRESS_GATE,
GO_WINTERGRASP_FORTRESS_GATE,

GO_WINTERGRASP_SHADOWSIGHT_TOWER,
GO_WINTERGRASP_WINTER_S_EDGE_TOWER,
GO_WINTERGRASP_FLAMEWATCH_TOWER,

GO_WINTERGRASP_FORTRESS_TOWER_NE,
GO_WINTERGRASP_FORTRESS_TOWER_NW,
GO_WINTERGRASP_FORTRESS_TOWER_SE,
GO_WINTERGRASP_FORTRESS_TOWER_SW,
GO_WINTERGRASP_FORTRESS_GATE,
GO_WINTERGRASP_VAULT_GATE,

GO_WINTERGRASP_FORTRESS_GATE,
GO_WINTERGRASP_VAULT_GATE,
GO_WINTERGRASP_FORTRESS_TOWER_NE,
GO_WINTERGRASP_FORTRESS_TOWER_NW,
GO_WINTERGRASP_FORTRESS_TOWER_SE,
GO_WINTERGRASP_FORTRESS_TOWER_SW,
0,
0,
0,
0,
0,
0
};

Position const WintergraspStalkerPos   = { 4948.985f, 2937.789f, 550.5172f,  1.815142f };

Position const WintergraspRelicPos     = { 5440.379f, 2840.493f, 430.2816f, -1.832595f };
QuaternionData const WintergraspRelicRot    = { 0.f, 0.f, -0.7933531f, 0.6087617f };

uint8 const WG_MAX_OBJ              = 32;
uint8 const WG_MAX_TELEPORTER       = 12;
uint8 const WG_MAX_WORKSHOP         = 6;
uint8 const WG_MAX_TOWER            = 7;

// *****************************************************
// ************ Destructible (Wall, Tower..) ***********
// *****************************************************

struct WintergraspBuildingSpawnData
{
    uint32 entry;
    uint32 WorldState;
    Position pos;
    QuaternionData rot;
    WintergraspGameObjectBuildingType type;
};

WintergraspBuildingSpawnData const WGGameObjectBuilding[WG_MAX_OBJ] =
{
    // Wall (Not spawned in db)
    // Entry  WS      X          Y          Z           O                rX   rY   rZ             rW             Type
    { 190219, 3749, { 5371.457f, 3047.472f, 407.5710f,  3.14159300f }, { 0.f, 0.f, -1.000000000f, 0.00000000f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 190220, 3750, { 5331.264f, 3047.105f, 407.9228f,  0.05235888f }, { 0.f, 0.f,  0.026176450f, 0.99965730f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 191795, 3764, { 5385.841f, 2909.490f, 409.7127f,  0.00872424f }, { 0.f, 0.f,  0.004362106f, 0.99999050f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 191796, 3772, { 5384.452f, 2771.835f, 410.2704f,  3.14159300f }, { 0.f, 0.f, -1.000000000f, 0.00000000f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 191799, 3762, { 5371.436f, 2630.610f, 408.8163f,  3.13285800f }, { 0.f, 0.f,  0.999990500f, 0.00436732f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 191800, 3766, { 5301.838f, 2909.089f, 409.8661f,  0.00872424f }, { 0.f, 0.f,  0.004362106f, 0.99999050f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 191801, 3770, { 5301.063f, 2771.411f, 409.9014f,  3.14159300f }, { 0.f, 0.f, -1.000000000f, 0.00000000f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 191802, 3751, { 5280.197f, 2995.583f, 408.8249f,  1.61442800f }, { 0.f, 0.f,  0.722363500f, 0.69151360f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 191803, 3752, { 5279.136f, 2956.023f, 408.6041f,  1.57079600f }, { 0.f, 0.f,  0.707106600f, 0.70710690f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 191804, 3767, { 5278.685f, 2882.513f, 409.5388f,  1.57079600f }, { 0.f, 0.f,  0.707106600f, 0.70710690f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 191806, 3769, { 5279.502f, 2798.945f, 409.9983f,  1.57079600f }, { 0.f, 0.f,  0.707106600f, 0.70710690f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 191807, 3759, { 5279.937f, 2724.766f, 409.9452f,  1.56207000f }, { 0.f, 0.f,  0.704014800f, 0.71018530f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 191808, 3760, { 5279.601f, 2683.786f, 409.8488f,  1.55334100f }, { 0.f, 0.f,  0.700908700f, 0.71325110f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 191809, 3761, { 5330.955f, 2630.777f, 409.2826f,  3.13285800f }, { 0.f, 0.f,  0.999990500f, 0.00436732f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 190369, 3753, { 5256.085f, 2933.963f, 409.3571f,  3.13285800f }, { 0.f, 0.f,  0.999990500f, 0.00436732f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 190370, 3758, { 5257.463f, 2747.327f, 409.7427f, -3.13285800f }, { 0.f, 0.f, -0.999990500f, 0.00436732f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 190371, 3754, { 5214.960f, 2934.089f, 409.1905f, -0.00872424f }, { 0.f, 0.f, -0.004362106f, 0.99999050f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 190372, 3757, { 5215.821f, 2747.566f, 409.1884f, -3.13285800f }, { 0.f, 0.f, -0.999990500f, 0.00436732f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 190374, 3755, { 5162.273f, 2883.043f, 410.2556f,  1.57952200f }, { 0.f, 0.f,  0.710185100f, 0.70401500f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 190376, 3756, { 5163.724f, 2799.838f, 409.2270f,  1.57952200f }, { 0.f, 0.f,  0.710185100f, 0.70401500f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },

    // Tower of keep (Not spawned in db)
    { 190221, 3711, { 5281.154f, 3044.588f, 407.8434f,  3.115388f }, { 0.f, 0.f,  0.9999142f, 0.013101960f }, BATTLEFIELD_WG_OBJECTTYPE_KEEP_TOWER }, // NW
    { 190373, 3713, { 5163.757f, 2932.228f, 409.1904f,  3.124123f }, { 0.f, 0.f,  0.9999619f, 0.008734641f }, BATTLEFIELD_WG_OBJECTTYPE_KEEP_TOWER }, // SW
    { 190377, 3714, { 5166.397f, 2748.368f, 409.1884f, -1.570796f }, { 0.f, 0.f, -0.7071066f, 0.707106900f }, BATTLEFIELD_WG_OBJECTTYPE_KEEP_TOWER }, // SE
    { 190378, 3712, { 5281.192f, 2632.479f, 409.0985f, -1.588246f }, { 0.f, 0.f, -0.7132492f, 0.700910500f }, BATTLEFIELD_WG_OBJECTTYPE_KEEP_TOWER }, // NE

    // Wall (with passage) (Not spawned in db)
    { 191797, 3765, { 5343.290f, 2908.860f, 409.5757f, 0.00872424f }, { 0.f, 0.f,  0.004362106f, 0.9999905f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 191798, 3771, { 5342.719f, 2771.386f, 409.6249f, 3.14159300f }, { 0.f, 0.f, -1.000000000f, 0.0000000f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },
    { 191805, 3768, { 5279.126f, 2840.797f, 409.7826f, 1.57952200f }, { 0.f, 0.f,  0.710185100f, 0.7040150f }, BATTLEFIELD_WG_OBJECTTYPE_WALL },

    // South tower (Not spawned in db)
    { 190356, 3704, { 4557.173f, 3623.943f, 395.8828f,  1.675516f }, { 0.f, 0.f,  0.7431450f, 0.669130400f }, BATTLEFIELD_WG_OBJECTTYPE_TOWER }, // W
    { 190357, 3705, { 4398.172f, 2822.497f, 405.6270f, -3.124123f }, { 0.f, 0.f, -0.9999619f, 0.008734641f }, BATTLEFIELD_WG_OBJECTTYPE_TOWER }, // S
    { 190358, 3706, { 4459.105f, 1944.326f, 434.9912f, -2.002762f }, { 0.f, 0.f, -0.8422165f, 0.539139500f }, BATTLEFIELD_WG_OBJECTTYPE_TOWER }, // E

    // Door of forteress (Not spawned in db)
    { GO_WINTERGRASP_FORTRESS_GATE, 3763, { 5162.991f, 2841.232f, 410.1892f, -3.132858f }, { 0.f, 0.f, -0.9999905f, 0.00436732f }, BATTLEFIELD_WG_OBJECTTYPE_DOOR },

    // Last door (Not spawned in db)
    { GO_WINTERGRASP_VAULT_GATE, 3773, { 5397.108f, 2841.54f, 425.9014f, 3.141593f }, { 0.f, 0.f, -1.f, 0.f }, BATTLEFIELD_WG_OBJECTTYPE_DOOR_LAST },
};

struct StaticWintergraspTowerInfo
{
    uint8 TowerId;

    struct
    {
        uint8 Damaged;
        uint8 Destroyed;
    } TextIds;
};

StaticWintergraspTowerInfo const TowerData[WG_MAX_TOWER] =
{
    { BATTLEFIELD_WG_TOWER_FORTRESS_NW,   { BATTLEFIELD_WG_TEXT_NW_KEEPTOWER_DAMAGE,   BATTLEFIELD_WG_TEXT_NW_KEEPTOWER_DESTROY   } },
    { BATTLEFIELD_WG_TOWER_FORTRESS_SW,   { BATTLEFIELD_WG_TEXT_SW_KEEPTOWER_DAMAGE,   BATTLEFIELD_WG_TEXT_SW_KEEPTOWER_DESTROY   } },
    { BATTLEFIELD_WG_TOWER_FORTRESS_SE,   { BATTLEFIELD_WG_TEXT_SE_KEEPTOWER_DAMAGE,   BATTLEFIELD_WG_TEXT_SE_KEEPTOWER_DESTROY   } },
    { BATTLEFIELD_WG_TOWER_FORTRESS_NE,   { BATTLEFIELD_WG_TEXT_NE_KEEPTOWER_DAMAGE,   BATTLEFIELD_WG_TEXT_NE_KEEPTOWER_DESTROY   } },
    { BATTLEFIELD_WG_TOWER_SHADOWSIGHT,   { BATTLEFIELD_WG_TEXT_WESTERN_TOWER_DAMAGE,  BATTLEFIELD_WG_TEXT_WESTERN_TOWER_DESTROY  } },
    { BATTLEFIELD_WG_TOWER_WINTER_S_EDGE, { BATTLEFIELD_WG_TEXT_SOUTHERN_TOWER_DAMAGE, BATTLEFIELD_WG_TEXT_SOUTHERN_TOWER_DESTROY } },
    { BATTLEFIELD_WG_TOWER_FLAMEWATCH,    { BATTLEFIELD_WG_TEXT_EASTERN_TOWER_DAMAGE,  BATTLEFIELD_WG_TEXT_EASTERN_TOWER_DESTROY  } }
};

struct WintergraspObjectPositionData
{
    Position Pos;
    uint32 HordeEntry;
    uint32 AllianceEntry;
};

struct WintergraspGameObjectData
{
    Position Pos;
    QuaternionData Rot;
    uint32 HordeEntry;
    uint32 AllianceEntry;
};

WintergraspGameObjectData const WGPortalDefenderData[WG_MAX_TELEPORTER] =
{
    // Player teleporter
    { { 5153.408f, 2901.349f, 409.1913f, -0.06981169f }, { 0.f, 0.f, -0.03489876f, 0.9993908f }, 190763, 191575 },
    { { 5268.698f, 2666.421f, 409.0985f, -0.71558490f }, { 0.f, 0.f, -0.35020730f, 0.9366722f }, 190763, 191575 },
    { { 5197.050f, 2944.814f, 409.1913f,  2.33874000f }, { 0.f, 0.f,  0.92050460f, 0.3907318f }, 190763, 191575 },
    { { 5196.671f, 2737.345f, 409.1892f, -2.93213900f }, { 0.f, 0.f, -0.99452110f, 0.1045355f }, 190763, 191575 },
    { { 5314.580f, 3055.852f, 408.8620f,  0.54105060f }, { 0.f, 0.f,  0.26723770f, 0.9636307f }, 190763, 191575 },
    { { 5391.277f, 2828.094f, 418.6752f, -2.16420600f }, { 0.f, 0.f, -0.88294700f, 0.4694727f }, 190763, 191575 },
    { { 5153.931f, 2781.671f, 409.2455f,  1.65806200f }, { 0.f, 0.f,  0.73727700f, 0.6755905f }, 190763, 191575 },
    { { 5311.445f, 2618.931f, 409.0916f, -2.37364400f }, { 0.f, 0.f, -0.92718320f, 0.3746083f }, 190763, 191575 },
    { { 5269.208f, 3013.838f, 408.8276f, -1.76278200f }, { 0.f, 0.f, -0.77162460f, 0.6360782f }, 190763, 191575 },

    { { 5401.634f, 2853.667f, 418.6748f,  2.63544400f }, { 0.f, 0.f,  0.96814730f, 0.2503814f }, 192819, 192819 }, // return portal inside fortress, neutral
    // Vehicle teleporter
    { { 5314.515f, 2703.687f, 408.5502f, -0.89011660f }, { 0.f, 0.f, -0.43051050f, 0.9025856f }, 192951, 192951 },
    { { 5316.252f, 2977.042f, 408.5385f, -0.82030330f }, { 0.f, 0.f, -0.39874840f, 0.9170604f }, 192951, 192951 }
};

struct WintergraspGameObjectWorkshopData
{
    Position Pos;
    QuaternionData Rot;
    uint32 entry;
};
uint8 const WG_MAX_WORKSHOPGO = 4;
WintergraspGameObjectWorkshopData const WGworkshopData[WG_MAX_WORKSHOPGO] =
{
    // workshop GO
    // SE
    { { 4398.08f, 2356.5f, 376.19f, 0.525406f }, { 0.f, 0.f, 0.259692f, 0.965692f }, 194959 },
    // SW
    { { 4390.78f, 3304.09f, 372.429f, 6.09702f }, { 0.f, 0.f, 0.0929482f, -0.995671f }, 194962 },
    // NE
    { { 4949.34f, 2432.59f, 320.177f, 1.38621f }, { 0.f, 0.f, 0.638929f, 0.769266f }, 192626 },
    // NW
    { { 4948.52f, 3342.34f, 376.875f, 4.40057f }, { 0.f, 0.f, 0.808329f, -0.588731f }, 192627 }
};

// *********************************************************
// **********Tower Element(GameObject, Creature)************
// *********************************************************

struct WintergraspTowerData
{
    uint32 towerEntry;                                   // Gameobject id of tower
    std::vector<WintergraspGameObjectData> GameObject;   // Gameobject position and entry (Horde/Alliance)
};

uint8 const WG_MAX_ATTACKTOWERS = 3;
// 192414 : 0 in sql, 1 in header
// 192278 : 0 in sql, 3 in header
WintergraspTowerData const AttackTowers[WG_MAX_ATTACKTOWERS] =
{
    // West tower
    {
        190356,
        {
            { { 4559.113f, 3606.216f, 419.9992f, 4.799657f }, { 0.f, 0.f, -0.67558960f, 0.73727790f }, 192488, 192501 },    // Flag on tower
            { { 4539.420f, 3622.490f, 420.0342f, 3.211419f }, { 0.f, 0.f, -0.99939060f, 0.03490613f }, 192488, 192501 },    // Flag on tower
            { { 4555.258f, 3641.648f, 419.9740f, 1.675514f }, { 0.f, 0.f,  0.74314400f, 0.66913150f }, 192488, 192501 },    // Flag on tower
            { { 4574.872f, 3625.911f, 420.0792f, 0.087266f }, { 0.f, 0.f,  0.04361916f, 0.99904820f }, 192488, 192501 },    // Flag on tower
            { { 4433.899f, 3534.142f, 360.2750f, 4.433136f }, { 0.f, 0.f, -0.79863550f, 0.60181500f }, 192276, 192278 },    // Flag near workshop
            { { 4572.933f, 3475.519f, 363.0090f, 1.422443f }, { 0.f, 0.f,  0.65275960f, 0.75756520f }, 192276, 192277 }     // Flag near bridge
        }
    },
    // South Tower
    {
        190357,
        {
            { { 4416.004f, 2822.666f, 429.8512f, 6.2657330f }, { 0.f, 0.f, -0.00872612f, 0.99996190f }, 192488, 192501 },    // Flag on tower
            { { 4398.819f, 2804.698f, 429.7920f, 4.6949370f }, { 0.f, 0.f, -0.71325020f, 0.70090960f }, 192488, 192501 },    // Flag on tower
            { { 4380.36f, 2822.38f, 429.882f, -3.10665f }, { 0.f, 0.f, -0.999847f, 0.0174704f }, 192488, 192501 },           // Flag on tower
            { { 4397.66f, 2840.3f, 429.922f, 1.58825f }, { 0.f, 0.f, 0.713251f, 0.700909f }, 192488, 192501 },               // Flag on tower

            { { 4425.516f, 2976.093f, 367.4235f, 3.2899610f }, { 0.f, 0.f, -0.99724960f, 0.07411628f }, 192276, 192278 },    // Flag in west side
            { { 4387.622f, 2719.566f, 389.9351f, 4.7385700f }, { 0.f, 0.f, -0.69779010f, 0.71630230f }, 192366, 192414 },    // Flag in east side
            { { 4452.76f, 2639.14f, 358.444f, 1.67552f }, { 0.f, 0.f, 0.743146f, 0.669129f }, 192267, 192266 },              // Flag in east side

            { { 4526.457f, 2810.181f, 391.1997f, 3.2899610f }, { 0.f, 0.f, -0.99724960f, 0.07411628f }, 192276, 192278 },    // Flag in north side (near bridge)

            { { 4349.9f, 2885.56f, 406.105f, 1.6057f }, { 0.f, 0.f,  0.719339f, 0.694659f }, 192366, 192429 },               // Flag big on west side
            { { 4517.75f, 2717.07f, 387.812f, -1.54462f }, { 0.f, 0.f, -0.697792f, 0.716301f }, 192449, 192415 },            // Flag big on east side
            { { 4434.285f, 2883.906f, 405.5880f, 0.8290324f }, { 0.f, 0.f,  0.40274720f, 0.91531130f }, 192366, 192429 },    // Flag big on north side
            { { 4464.124f, 2855.453f, 406.1106f, 0.8290324f }, { 0.f, 0.f,  0.40274720f, 0.91531130f }, 192366, 192429 }     // Flag big on north side            
        }
    },
    // East Tower
    {
        190358,
        {
            { { 4475.35f, 1937.03f, 459.07f, -0.436332f }, { 0.f, 0.f,  -0.216439f, 0.976296f }, 192502, 192501 },     // Flag on tower
            { { 4466.79f, 1960.42f, 459.144f, 1.15192f }, { 0.f, 0.f,  0.54464f, 0.83867f }, 192502, 192501 },         // Flag on tower
            { { 4442.99f, 1951.9f, 459.093f, 2.74016f }, { 0.f, 0.f,  0.979924f, 0.199371f }, 192502, 192501 },        // Flag on tower
            { { 4451.76f, 1928.1f, 459.076f, -2.00713f }, { 0.f, 0.f,  -0.843392f, 0.537299f }, 192502, 192501 },      // Flag on tower
            { { 4563.73f, 2171.15f, 367.68f, 1.30027f }, { 0.f, 0.f,  0.605294f, 0.796002f }, 192424, 192423 }         // Flag on west side
        }
    }
};

// *********************************************************
// *****************WorkShop Data & Element*****************
// *********************************************************

struct StaticWintergraspWorkshopInfo
{
    uint8 WorkshopId;
    uint32 WorldStateId;

    struct
    {
        uint8 AllianceCapture;
        uint8 AllianceAttack;
        uint8 HordeCapture;
        uint8 HordeAttack;
    } TextIds;
};

StaticWintergraspWorkshopInfo const WorkshopData[WG_MAX_WORKSHOP] =
{
    { BATTLEFIELD_WG_WORKSHOP_SE, WS_BATTLEFIELD_WG_WORKSHOP_SE, { BATTLEFIELD_WG_TEXT_EASTSPARK_CAPTURE_ALLIANCE,     BATTLEFIELD_WG_TEXT_EASTSPARK_ATTACK_ALLIANCE,     BATTLEFIELD_WG_TEXT_EASTSPARK_CAPTURE_HORDE,     BATTLEFIELD_WG_TEXT_EASTSPARK_ATTACK_HORDE     } },
    { BATTLEFIELD_WG_WORKSHOP_SW, WS_BATTLEFIELD_WG_WORKSHOP_SW, { BATTLEFIELD_WG_TEXT_WESTSPARK_CAPTURE_ALLIANCE,     BATTLEFIELD_WG_TEXT_WESTSPARK_ATTACK_ALLIANCE,     BATTLEFIELD_WG_TEXT_WESTSPARK_CAPTURE_HORDE,     BATTLEFIELD_WG_TEXT_WESTSPARK_ATTACK_HORDE     } },
    { BATTLEFIELD_WG_WORKSHOP_NE, WS_BATTLEFIELD_WG_WORKSHOP_NE, { BATTLEFIELD_WG_TEXT_SUNKEN_RING_CAPTURE_ALLIANCE,   BATTLEFIELD_WG_TEXT_SUNKEN_RING_ATTACK_ALLIANCE,   BATTLEFIELD_WG_TEXT_SUNKEN_RING_CAPTURE_HORDE,   BATTLEFIELD_WG_TEXT_SUNKEN_RING_ATTACK_HORDE   } },
    { BATTLEFIELD_WG_WORKSHOP_NW, WS_BATTLEFIELD_WG_WORKSHOP_NW, { BATTLEFIELD_WG_TEXT_BROKEN_TEMPLE_CAPTURE_ALLIANCE, BATTLEFIELD_WG_TEXT_BROKEN_TEMPLE_ATTACK_ALLIANCE, BATTLEFIELD_WG_TEXT_BROKEN_TEMPLE_CAPTURE_HORDE, BATTLEFIELD_WG_TEXT_BROKEN_TEMPLE_ATTACK_HORDE } },    
    // KEEP WORKSHOPS - It can't be taken, so it doesn't have a textids
    { BATTLEFIELD_WG_WORKSHOP_KEEP_WEST, WS_BATTLEFIELD_WG_WORKSHOP_K_W, { 0, 0, 0, 0 } },
    { BATTLEFIELD_WG_WORKSHOP_KEEP_EAST, WS_BATTLEFIELD_WG_WORKSHOP_K_E, { 0, 0, 0, 0 } }
};

struct WintergraspWorkshopData
{
    uint32 WorkshopEntry;                                // id of Workshop
    std::vector<WintergraspGameObjectData> GameObject;   // Gameobject position and entry (Horde/Alliance)
};

uint8 const WG_MAX_WORKSHOPS = 6;
WintergraspWorkshopData const WorksshopGO[WG_MAX_WORKSHOPS] =
{
    // South East Workshop
    {
        BATTLEFIELD_WG_WORKSHOP_SE,
        {
            { { 4416.59f, 2414.08f, 377.196f, 0 }, { 0.f, 0.f, 0, 1.f }, 192452, 192417 },                        // Flag on wall west
            { { 4408.57f, 2422.61f, 377.179f, 1.58825f }, { 0.f, 0.f, 0.713251f, 0.700909f }, 192451, 192416 },   // Flag on wall west
            { { 4417.94f, 2324.81f, 371.577f, 3.08051f }, { 0.f, 0.f, 0.999534f, 0.0305366f }, 192272, 192273 },  // small Flag
            { { 4417.25f, 2301.14f, 377.214f, 0.026179f }, { 0.f, 0.f, 0.0130891f, 0.999914f }, 192453, 192418 }  // Flag on wall east
        }
    },
    // South West Workshop
    {
        BATTLEFIELD_WG_WORKSHOP_SW,
        {
            { { 4399.64f, 3231.54f, 368.898f, 1.49226f }, { 0.f, 0.f, 0.678802f, 0.734321f }, 192408, 192409 },    // Flag on west side
            { { 4424.15f, 3286.54f, 371.546f, 3.12412f }, { 0.f, 0.f, 0.999962f, 0.00873622f }, 192275, 192274 },  // Flag on middle side
            { { 4401.62f, 3377.48f, 363.12f, 1.53589f }, { 0.f, 0.f, 0.694658f, 0.71934f }, 192432, 192433 },      // Flag on east side

            { { 4438.38f, 3361.01f, 371.814f, 0.0348707f }, { 0.f, 0.f, 0.0174345f, 0.999848f }, 192440, 192406 }, // banner on west side
            { { 4459.36f, 3273.83f, 370.175f, 0.0348707f }, { 0.f, 0.f, 0.0174345f, 0.999848f }, 192440, 192406 }, // banner on middle side
            { { 4448.15f, 3235.61f, 370.617f, -1.54462f }, { 0.f, 0.f, -0.704015f, 0.710185f }, 192441, 192407 }   // banner on ease side
        }
    },
    // North East Workshop
    {
        BATTLEFIELD_WG_WORKSHOP_NE,
        {
            { { 4991.08f, 2525.76f, 340.918f, 4.04044f }, { 0.f, 0.f, 0.900698f, -0.434447f }, 192290, 192291 },    // Flag on west side
            { { 5004.35f, 2486.36f, 358.449f, 2.17294f }, { 0.f, 0.f, 0.884989f, 0.465612f }, 192460, 192427 },     // banner on west side (north)
            { { 4983.22f, 2503.27f, 357.96f, -0.436332f }, { 0.f, 0.f, -0.216439f, 0.976296f }, 192461, 192428 },   // banner on west side (south)

            { { 4778.19f, 2438.06f, 345.644f, -2.94088f }, { 0.f, 0.f, -0.994969f, 0.100188f }, 192289, 192288 },   // Flag on south side
            { { 4811.44f, 2441.85f, 357.982f, -2.02458f }, { 0.f, 0.f, -0.848048f, 0.52992f }, 192458, 192425 },    // banner on west side (west)
            { { 4805.67f, 2407.48f, 358.191f, 1.78023f }, { 0.f, 0.f, 0.777144f, 0.629323f }, 192459, 192426 }      // banner on west side (east)
        }
    },
    // North West Workshop
    {
        BATTLEFIELD_WG_WORKSHOP_NW,
        {
            { { 4857.97f, 3335.44f, 368.881f, -2.94959f }, { 0.f, 0.f, -0.995395f, 0.0958539f }, 192280, 192281 },    // Flag on south side
            { { 4855.44f, 3297.6f, 376.496f, -3.11539f }, { 0.f, 0.f, -0.999914f, 0.0131009f }, 192435, 192401 },     // banner on south side
            { { 5006.32f, 3280.36f, 371.242f, 2.24275f }, { 0.f, 0.f, 0.900699f, 0.434444f }, 192283, 192282 },       // Flag on east side
            { { 5041.65f, 3294.32f, 381.92f, -1.6057f }, { 0.f, 0.f, -0.719339f, 0.694659f }, 192434, 192400 }        // banner on east side
        }
    },
    // fortness West Workshop
    {
        BATTLEFIELD_WG_WORKSHOP_KEEP_WEST,
        {

        }
    },
    // fortness West Workshop
    {
        BATTLEFIELD_WG_WORKSHOP_KEEP_EAST,
        {

        }
    }
};

BattlefieldWG::~BattlefieldWG()
{
    for (WintergraspWorkshop* workshop : Workshops)
        delete workshop;

    for (BfWGGameObjectBuilding* building : BuildingsInZone)
        delete building;

    m_CreatureMap.clear();
}

bool BattlefieldWG::SetupBattlefield()
{
    m_TypeId = BATTLEFIELD_WG;                              // See enum BattlefieldTypes
    m_BattleId = BATTLEFIELD_BATTLEID_WG;
    m_ZoneId = AREA_WINTERGRASP;
    m_MapId = BATTLEFIELD_WG_MAPID;
    m_Map = sMapMgr->FindMap(m_MapId, 0);

    InitStalker(BATTLEFIELD_WG_NPC_STALKER, WintergraspStalkerPos);

    m_MaxPlayer = sWorld->getIntConfig(CONFIG_WINTERGRASP_PLR_MAX);
    for (uint8 i = 0; i < PVP_TEAMS_COUNT; i++)
        m_freeslots[i] = m_MaxPlayer;

    m_IsEnabled = sWorld->getBoolConfig(CONFIG_WINTERGRASP_ENABLE);
    m_MinPlayer = sWorld->getIntConfig(CONFIG_WINTERGRASP_PLR_MIN);
    m_MinLevel = sWorld->getIntConfig(CONFIG_WINTERGRASP_PLR_MIN_LVL);
    m_BattleTime = sWorld->getIntConfig(CONFIG_WINTERGRASP_BATTLETIME) * MINUTE * IN_MILLISECONDS;
    m_NoWarBattleTime = sWorld->getIntConfig(CONFIG_WINTERGRASP_NOBATTLETIME) * MINUTE * IN_MILLISECONDS;
    m_RestartAfterCrash = sWorld->getIntConfig(CONFIG_WINTERGRASP_RESTART_AFTER_CRASH) * MINUTE * IN_MILLISECONDS;

    m_TimeForAcceptInvite = 20;
    m_StartGroupingTimer = 15 * MINUTE * IN_MILLISECONDS;
    m_StartGrouping = false;

    m_tenacityTeam = TEAM_NEUTRAL;
    m_tenacityStack = 0;

    KickPosition.Relocate(5728.117f, 2714.346f, 697.733f, 0);
    KickPosition.m_mapId = m_MapId;

    RegisterZone(m_ZoneId);

    m_Data32.resize(BATTLEFIELD_WG_DATA_MAX);

    m_saveTimer = 60000;

    // Init Graveyards
    SetGraveyardNumber(BATTLEFIELD_WG_GRAVEYARD_MAX);

    // Load from db
    if ((sWorld->getWorldState(WS_BATTLEFIELD_WG_ACTIVE) == 0) && (sWorld->getWorldState(WS_BATTLEFIELD_WG_DEFENDER) == 0)
            && (sWorld->getWorldState(ClockWorldState[0]) == 0))
    {
        sWorld->setWorldState(WS_BATTLEFIELD_WG_ACTIVE, uint64(false));
        sWorld->setWorldState(WS_BATTLEFIELD_WG_DEFENDER, uint64(urand(0, 1)));
        sWorld->setWorldState(ClockWorldState[0], uint64(m_NoWarBattleTime));
    }

    m_isActive = sWorld->getWorldState(WS_BATTLEFIELD_WG_ACTIVE) != 0;
    m_DefenderTeam = TeamId(sWorld->getWorldState(WS_BATTLEFIELD_WG_DEFENDER));

    m_Timer = sWorld->getWorldState(ClockWorldState[0]);
    if (m_isActive)
    {
        m_isActive = false;
        m_Timer = m_RestartAfterCrash;
    }

    SetData(BATTLEFIELD_WG_DATA_WON_A, uint32(sWorld->getWorldState(WS_BATTLEFIELD_WG_ATTACKED_A)));
    SetData(BATTLEFIELD_WG_DATA_DEF_A, uint32(sWorld->getWorldState(WS_BATTLEFIELD_WG_DEFENDED_A)));
    SetData(BATTLEFIELD_WG_DATA_WON_H, uint32(sWorld->getWorldState(WS_BATTLEFIELD_WG_ATTACKED_H)));
    SetData(BATTLEFIELD_WG_DATA_DEF_H, uint32(sWorld->getWorldState(WS_BATTLEFIELD_WG_DEFENDED_H)));

    for (uint8 i = 0; i < BATTLEFIELD_WG_GRAVEYARD_MAX; i++)
    {
        BfGraveyardWG* graveyard = new BfGraveyardWG(this);

        // When between games, the graveyard is controlled by the defending team
        if (WGGraveyard[i].StartControl == TEAM_NEUTRAL)
            graveyard->Initialize(m_DefenderTeam, WGGraveyard[i].GraveyardID);
        else
            graveyard->Initialize(WGGraveyard[i].StartControl, WGGraveyard[i].GraveyardID);

        graveyard->SetTextId(WGGraveyard[i].TextID);
        m_GraveyardList[i] = graveyard;
    }

    Workshops.resize(WG_MAX_WORKSHOP);
    // Spawn workshop creatures and gameobjects
    for (uint8 i = 0; i < WG_MAX_WORKSHOP; i++)
    {
        if (WintergraspWorkshop* workshop = new WintergraspWorkshop(this, i))
        {
            if (workshop->GetId() < BATTLEFIELD_WG_WORKSHOP_NE)
                workshop->InitialWorkshopAndCapturePoint(GetAttackerTeam(), workshop->GetId());
            else
                workshop->InitialWorkshopAndCapturePoint(GetDefenderTeam(), workshop->GetId());

            // Note: Capture point is added once the gameobject is created.
            Workshops[i] = workshop;
        }
    }

    BuildingsInZone.resize(WG_MAX_OBJ);
    // Spawn all gameobjects
    for (uint8 i = 0; i < WG_MAX_OBJ; i++)
    {
        if (GameObject* go = SpawnGameObject(WGGameObjectBuilding[i].entry, WGGameObjectBuilding[i].pos, WGGameObjectBuilding[i].rot))
        {
            BfWGGameObjectBuilding* b = new BfWGGameObjectBuilding(this, WGGameObjectBuilding[i].type, WGGameObjectBuilding[i].WorldState);
            b->Init(go);
            if (!IsEnabled() && go->GetEntry() == GO_WINTERGRASP_VAULT_GATE)
                go->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);

            BuildingsInZone[i] = b;
        }
    }

    // Spawning portal defender
    for (uint8 i = 0; i < WG_MAX_TELEPORTER; ++i)
    {
        WintergraspGameObjectData const& teleporter = WGPortalDefenderData[i];
        if (GameObject* go = SpawnGameObject(teleporter.AllianceEntry, teleporter.Pos, teleporter.Rot))
        {
            DefenderPortalList[TEAM_ALLIANCE].push_back(go->GetGUID());
            go->SetRespawnTime(GetDefenderTeam() == TEAM_ALLIANCE ? RESPAWN_IMMEDIATELY : RESPAWN_ONE_DAY);
        }

        if (GameObject* go = SpawnGameObject(teleporter.HordeEntry, teleporter.Pos, teleporter.Rot))
        {
            DefenderPortalList[TEAM_HORDE].push_back(go->GetGUID());
            go->SetRespawnTime(GetDefenderTeam() == TEAM_HORDE ? RESPAWN_IMMEDIATELY : RESPAWN_ONE_DAY);
        }
    }

    UpdateCounterVehicle(true);
    return true;
}

bool BattlefieldWG::Update(uint32 diff)
{
    bool m_return = Battlefield::Update(diff);
    if (m_saveTimer <= diff)
    {
        sWorld->setWorldState(WS_BATTLEFIELD_WG_ACTIVE, m_isActive);
        sWorld->setWorldState(WS_BATTLEFIELD_WG_DEFENDER, m_DefenderTeam);
        sWorld->setWorldState(ClockWorldState[0], m_Timer);
        sWorld->setWorldState(WS_BATTLEFIELD_WG_ATTACKED_A, GetData(BATTLEFIELD_WG_DATA_WON_A));
        sWorld->setWorldState(WS_BATTLEFIELD_WG_DEFENDED_A, GetData(BATTLEFIELD_WG_DATA_DEF_A));
        sWorld->setWorldState(WS_BATTLEFIELD_WG_ATTACKED_H, GetData(BATTLEFIELD_WG_DATA_WON_H));
        sWorld->setWorldState(WS_BATTLEFIELD_WG_DEFENDED_H, GetData(BATTLEFIELD_WG_DATA_DEF_H));
        m_saveTimer = 60 * IN_MILLISECONDS;
    }
    else
        m_saveTimer -= diff;

    return m_return;
}

void BattlefieldWG::OnBattleStart()
{
    // Spawn titan relic
    if (GameObject* relic = SpawnGameObject(GO_WINTERGRASP_TITAN_S_RELIC, WintergraspRelicPos, WintergraspRelicRot))
    {
        // Update faction of relic, only attacker can click on
        relic->SetFaction(WintergraspFaction[GetAttackerTeam()]);
        // Set in use (not allow to click on before last door is broken)
        relic->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE | GO_FLAG_NOT_SELECTABLE);
        m_titansRelicGUID = relic->GetGUID();
    }
    else
        TC_LOG_ERROR("bg.battlefield", "WG: Failed to spawn titan relic.");

    // Rebuild all wall
    for (BfWGGameObjectBuilding* building : BuildingsInZone)
    {
        building->Rebuild();
    }

    UpdateAllGuardsAndTurretsBeforeBattle();

    SetData(BATTLEFIELD_WG_DATA_BROKEN_TOWER_ATT, 0);
    SetData(BATTLEFIELD_WG_DATA_BROKEN_TOWER_DEF, 0);
    SetData(BATTLEFIELD_WG_DATA_DAMAGED_TOWER_ATT, 0);
    SetData(BATTLEFIELD_WG_DATA_DAMAGED_TOWER_DEF, 0);

    // Update graveyard (in no war time all graveyard is to deffender, in war time, depend of base)
    for (WintergraspWorkshop* workshop : Workshops)
        workshop->UpdateGraveyardAndWorkshop();

    for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
        {
            SendInitWorldStatesTo(player);

            if (itr->second.inZone)
            {
                float x, y, z;
                player->GetPosition(x, y, z);
                if (5500 > x && x > 5392 && y < 2880 && y > 2800 && z < 480)
                    player->TeleportTo(571, 5349.8686f, 2838.481f, 409.240f, 0.046328f);
            }
        }

    // Initialize vehicle counter
    UpdateCounterVehicle(true);
    // Send start warning to all players
    SendWarning(BATTLEFIELD_WG_TEXT_START_BATTLE);
}

void BattlefieldWG::UpdateCounterVehicle(bool init)
{
    if (init)
    {
        SetData(BATTLEFIELD_WG_DATA_VEHICLE_H, 0);
        SetData(BATTLEFIELD_WG_DATA_VEHICLE_A, 0);
    }
    SetData(BATTLEFIELD_WG_DATA_MAX_VEHICLE_H, 0);
    SetData(BATTLEFIELD_WG_DATA_MAX_VEHICLE_A, 0);

    for (WintergraspWorkshop* workshop : Workshops)
    {
        if (workshop->GetTeamControl() == TEAM_ALLIANCE)
            UpdateData(BATTLEFIELD_WG_DATA_MAX_VEHICLE_A, 4);
        else if (workshop->GetTeamControl() == TEAM_HORDE)
            UpdateData(BATTLEFIELD_WG_DATA_MAX_VEHICLE_H, 4);
    }

    UpdateVehicleCountWG();
}

void BattlefieldWG::OnBattleEnd(bool endByTimer)
{
    // Remove relic
    if (m_titansRelicGUID)
        if (GameObject* relic = GetGameObject(m_titansRelicGUID))
            relic->RemoveFromWorld();
    m_titansRelicGUID.Clear();

    // change collision wall state closed
    for (BfWGGameObjectBuilding* building : BuildingsInZone)
    {
        building->RebuildGate();
    }

    // successful defense
    if (endByTimer)
        UpdateData(GetDefenderTeam() == TEAM_HORDE ? BATTLEFIELD_WG_DATA_DEF_H : BATTLEFIELD_WG_DATA_DEF_A, 1);
    // successful attack (note that teams have already been swapped, so defender team is the one who won)
    else
        UpdateData(GetDefenderTeam() == TEAM_HORDE ? BATTLEFIELD_WG_DATA_WON_H : BATTLEFIELD_WG_DATA_WON_A, 1);

    // Update all graveyard, control is to defender when no wartime
    for (uint8 i = 0; i < BATTLEFIELD_WG_GY_HORDE; i++)
        if (BfGraveyard* graveyard = GetGraveyardById(i))
            graveyard->GiveControlTo(GetDefenderTeam());

    // Update portals
    for (auto itr = DefenderPortalList[GetDefenderTeam()].begin(); itr != DefenderPortalList[GetDefenderTeam()].end(); ++itr)
        if (GameObject* portal = GetGameObject(*itr))
            portal->SetRespawnTime(RESPAWN_IMMEDIATELY);

    for (auto itr = DefenderPortalList[GetAttackerTeam()].begin(); itr != DefenderPortalList[GetAttackerTeam()].end(); ++itr)
        if (GameObject* portal = GetGameObject(*itr))
            portal->SetRespawnTime(RESPAWN_ONE_DAY);

    // Saving data
    for (BfWGGameObjectBuilding* building : BuildingsInZone)
        building->Save();

    for (WintergraspWorkshop* workshop : Workshops)
        workshop->Save();

    for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
    {
        if (itr->second.inWar)
        {
            if (itr->second.team == GetDefenderTeam())
            {
                // section for defenders
                if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
                {
                    player->CastSpell(player, SPELL_ESSENCE_OF_WINTERGRASP, true);
                    player->CastSpell(player, SPELL_VICTORY_REWARD, true);
                    // Complete victory quests
                    player->AreaExploredOrEventHappens(QUEST_VICTORY_WINTERGRASP_A);
                    player->AreaExploredOrEventHappens(QUEST_VICTORY_WINTERGRASP_H);
                    // Send Wintergrasp victory achievement
                    DoCompleteOrIncrementAchievement(ACHIEVEMENTS_WIN_WG, player);
                    // Award achievement for succeeding in Wintergrasp in 10 minutes or less
                    if (!endByTimer && GetTimer() <= 10000)
                        DoCompleteOrIncrementAchievement(ACHIEVEMENTS_WIN_WG_TIMER_10, player);

                    RemoveAurasFromPlayer(player);
                }
            }
            else
            {
                // section for attackers
                if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
                {
                    player->CastSpell(player, SPELL_DEFEAT_REWARD, true);
                    RemoveAurasFromPlayer(player);
                }
            }

            itr->second.inWar = false;
        }

        if (!endByTimer)
            if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
            {
                player->RemoveAurasDueToSpell(m_DefenderTeam == TEAM_ALLIANCE ? SPELL_HORDE_CONTROL_PHASE_SHIFT : SPELL_ALLIANCE_CONTROL_PHASE_SHIFT, player->GetGUID());
                player->AddAura(m_DefenderTeam == TEAM_HORDE ? SPELL_HORDE_CONTROL_PHASE_SHIFT : SPELL_ALLIANCE_CONTROL_PHASE_SHIFT, player);
            }
    }

    for (uint8 team = 0; team < PVP_TEAMS_COUNT; ++team)
    {
        for (auto itr = m_vehicles[team].begin(); itr != m_vehicles[team].end(); ++itr)
            if (Creature* creature = GetCreature(*itr))
                if (creature->IsVehicle())
                    creature->DespawnOrUnsummon();

        m_vehicles[team].clear();
    }

    if (!endByTimer) // win alli/horde
        SendWarning(GetDefenderTeam() == TEAM_ALLIANCE ? BATTLEFIELD_WG_TEXT_FORTRESS_CAPTURE_ALLIANCE : BATTLEFIELD_WG_TEXT_FORTRESS_CAPTURE_HORDE);
    else // defend alli/horde
        SendWarning(GetDefenderTeam() == TEAM_ALLIANCE ? BATTLEFIELD_WG_TEXT_FORTRESS_DEFEND_ALLIANCE : BATTLEFIELD_WG_TEXT_FORTRESS_DEFEND_HORDE);
}

// *******************************************************
// ******************* Reward System *********************
// *******************************************************
void BattlefieldWG::DoCompleteOrIncrementAchievement(uint32 achievement, Player* player, uint8 /*incrementNumber*/)
{
    AchievementEntry const* achievementEntry = sAchievementMgr->GetAchievement(achievement);

    if (!achievementEntry)
        return;

    switch (achievement)
    {
        case ACHIEVEMENTS_WIN_WG_100:
        {
            // player->UpdateAchievementCriteria();
            break;
        }
        default:
        {
            if (player)
                player->CompletedAchievement(achievementEntry);
            break;
        }
    }

}

void BattlefieldWG::OnStartGrouping()
{
    SendWarning(BATTLEFIELD_WG_TEXT_START_GROUPING);
}

uint8 BattlefieldWG::GetSpiritGraveyardId(uint32 areaId) const
{
    switch (areaId)
    {
        case AREA_WINTERGRASP_FORTRESS:
            return BATTLEFIELD_WG_GY_KEEP;
        case AREA_THE_SUNKEN_RING:
            return BATTLEFIELD_WG_GY_WORKSHOP_NE;
        case AREA_THE_BROKEN_TEMPLATE:
            return BATTLEFIELD_WG_GY_WORKSHOP_NW;
        case AREA_WESTPARK_WORKSHOP:
            return BATTLEFIELD_WG_GY_WORKSHOP_SW;
        case AREA_EASTPARK_WORKSHOP:
            return BATTLEFIELD_WG_GY_WORKSHOP_SE;
        case AREA_WINTERGRASP:
            return BATTLEFIELD_WG_GY_ALLIANCE;
        case AREA_THE_CHILLED_QUAGMIRE:
            return BATTLEFIELD_WG_GY_HORDE;
        default:
            TC_LOG_ERROR("bg.battlefield", "BattlefieldWG::GetSpiritGraveyardId: Unexpected Area Id %u", areaId);
            break;
    }

    return 0;
}

void BattlefieldWG::OnCreatureCreate(Creature* creature)
{
    // Accessing to db spawned creatures
    switch (creature->GetEntry())
    {
        case NPC_DWARVEN_SPIRIT_GUIDE:
        case NPC_TAUNKA_SPIRIT_GUIDE:
        {
            TeamId teamId = (creature->GetEntry() == NPC_DWARVEN_SPIRIT_GUIDE ? TEAM_ALLIANCE : TEAM_HORDE);
            uint8 graveyardId = GetSpiritGraveyardId(creature->GetAreaId());
            if (m_GraveyardList[graveyardId])
                m_GraveyardList[graveyardId]->SetSpirit(creature, teamId);
            break;
        }
        case NPC_WORKSHOP_MECHANIC_HORDE:
        {
            bool registered = false;
            // SE workshop
            if (creature->GetScriptName() == "wg_se_workshop_mechanic")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_SE, TEAM_HORDE))
                    registered = true;
            }

            // SW workshop
            if (creature->GetScriptName() == "wg_sw_workshop_mechanic")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_SW, TEAM_HORDE))
                    registered = true;
            }

            // NE workshop
            if (creature->GetScriptName() == "wg_ne_workshop_mechanic")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_NE, TEAM_HORDE))
                    registered = true;
            }

            // NW workshop
            if (creature->GetScriptName() == "wg_nw_workshop_mechanic")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_NW, TEAM_HORDE))
                    registered = true;
            }

            if (!registered)
                TC_LOG_ERROR("system", "NPC_WINTERGRASP_TOWER_CANNON not registered for GUID : %u", creature->GetSpawnId());
            break;
        }
        case NPC_WORKSHOP_MECHANIC_ALLIANCE:
        {
            bool registered = false;
            // SE workshop
            if (creature->GetScriptName() == "wg_se_workshop_mechanic")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_SE, TEAM_ALLIANCE))
                    registered = true;
            }

            // SW workshop
            if (creature->GetScriptName() == "wg_sw_workshop_mechanic")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_SW, TEAM_ALLIANCE))
                    registered = true;
            }

            // NE workshop
            if (creature->GetScriptName() == "wg_ne_workshop_mechanic")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_NE, TEAM_ALLIANCE))
                    registered = true;
            }

            // NW workshop
            if (creature->GetScriptName() == "wg_nw_workshop_mechanic")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_NW, TEAM_ALLIANCE))
                    registered = true;
            }

            if (!registered)
                TC_LOG_ERROR("system", "NPC_WINTERGRASP_TOWER_CANNON not registered for GUID : %u", creature->GetSpawnId());
            break;
        }
        case NPC_WINTERGRASP_TOWER_CANNON:
        {
            bool registered = false;

            // Attacker section
            // West Tower
            if (creature->GetScriptName() == "wg_wt_assault_cannon")
            {
                if (AddCreatureInHolderByGUID(creature, WEST_TOWER_TURRET))
                    registered = true;
            }

            // South Tower
            if (creature->GetScriptName() == "wg_st_assault_cannon")
            {
                if (AddCreatureInHolderByGUID(creature, MIDDLE_TOWER_TURRET))
                    registered = true;
            }

            // East Tower
            if (creature->GetScriptName() == "wg_et_assault_cannon")
            {
                if (AddCreatureInHolderByGUID(creature, EAST_TOWER_TURRET))
                    registered = true;
            }

            // Defender Section
            // Fortress Gate
            if (creature->GetScriptName() == "npc_wg_fortress_gate_cannon")
            {
                if (AddCreatureInHolderByGUID(creature, FORTRESS_GATE_TURRET))
                    registered = true;
            }

            // Fortress
            if (creature->GetScriptName() == "npc_wg_fortress_cannon")
            {
                if (AddCreatureInHolderByGUID(creature, VAULT_GATE_TURRET))
                    registered = true;
            }

            // SE
            if (creature->GetScriptName() == "npc_wg_SE_cannon")
            {
                if (AddCreatureInHolderByGUID(creature, SE_TOWER_TURRET))
                    registered = true;
            }            

            // SW
            if (creature->GetScriptName() == "npc_wg_SW_cannon")
            {
                if (AddCreatureInHolderByGUID(creature, SW_TOWER_TURRET))
                    registered = true;
            }

            // NE
            if (creature->GetScriptName() == "npc_wg_NE_cannon")
            {
                if (AddCreatureInHolderByGUID(creature, NE_TOWER_TURRET))
                    registered = true;
            }

            // NW
            if (creature->GetScriptName() == "npc_wg_NW_cannon")
            {
                if (AddCreatureInHolderByGUID(creature, NW_TOWER_TURRET))
                    registered = true;
            }            

            creature->SetReactState(REACT_PASSIVE);
            if (!registered)
                TC_LOG_ERROR("system", "NPC_WINTERGRASP_TOWER_CANNON not registered for GUID : %u", creature->GetSpawnId());

            break;
        }
        case BATTLEFIELD_WG_NPC_GUARD_A:
        {
            bool registered = false;
            // ATTACK SIDE SECTION
            // West Tower
            if (creature->GetScriptName() == "wg_wt_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WEST_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_wt_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WEST_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            // South Tower
            if (creature->GetScriptName() == "wg_st_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, MIDDLE_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_st_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, MIDDLE_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            // East Tower
            if (creature->GetScriptName() == "wg_et_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, EAST_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_et_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, EAST_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            // COMMON SIDE SECTION
            // SE workshop
            if (creature->GetScriptName() == "wg_se_workshop_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_SE, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_se_workshop_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_SE, TEAM_ALLIANCE))
                    registered = true;
            }

            // SW workshop
            if (creature->GetScriptName() == "wg_sw_workshop_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_SW, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_sw_workshop_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_SW, TEAM_ALLIANCE))
                    registered = true;
            }

            // NE workshop
            if (creature->GetScriptName() == "wg_ne_workshop_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_NE, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_ne_workshop_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_NE, TEAM_ALLIANCE))
                    registered = true;
            }

            // NW workshop
            if (creature->GetScriptName() == "wg_nw_workshop_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_NW, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_nw_workshop_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_NW, TEAM_ALLIANCE))
                    registered = true;
            }

            // East Bridge
            if (creature->GetScriptName() == "wg_east_bridge_guard")
            {
                if (AddCreatureInHolderByGUID(creature, EAST_BRIDGE_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_east_roaming_bridge_guard")
            {
                if (AddCreatureInHolderByGUID(creature, EAST_BRIDGE_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            // Middle Bridge
            if (creature->GetScriptName() == "wg_middle_bridge_guard")
            {
                if (AddCreatureInHolderByGUID(creature, MIDDLE_BRIDGE_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_middle_roaming_bridge_guard")
            {
                if (AddCreatureInHolderByGUID(creature, MIDDLE_BRIDGE_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            // West Bridge
            if (creature->GetScriptName() == "wg_west_bridge_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WEST_BRIDGE_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_west_roaming_bridge_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WEST_BRIDGE_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            // DEFENDER SIDE SECTION
            if (creature->GetScriptName() == "wg_keep_NE_guard")
            {
                if (AddCreatureInHolderByGUID(creature, NE_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_keep_NW_guard")
            {
                if (AddCreatureInHolderByGUID(creature, NW_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_keep_SE_guard")
            {
                if (AddCreatureInHolderByGUID(creature, SE_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_keep_SW_guard")
            {
                if (AddCreatureInHolderByGUID(creature, SW_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_keep_fortress_gate_guard")
            {
                if (AddCreatureInHolderByGUID(creature, FORTRESS_GATE_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_keep_fortress_guard")
            {
                if (AddCreatureInHolderByGUID(creature, VAULT_GATE_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (!registered)
                TC_LOG_ERROR("system", "BATTLEFIELD_WG_NPC_GUARD_A not registered for GUID : %u", creature->GetSpawnId());
            break;
        }
        case BATTLEFIELD_WG_NPC_GUARD_H:
        {
            bool registered = false;
            // ATTACK SIDE SECTION
            // West Tower
            if (creature->GetScriptName() == "wg_wt_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WEST_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_wt_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WEST_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            // South Tower
            if (creature->GetScriptName() == "wg_st_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, MIDDLE_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_st_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, MIDDLE_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            // East Tower
            if (creature->GetScriptName() == "wg_et_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, EAST_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_et_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, EAST_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            // COMMON SIDE SECTION
            // SE workshop
            if (creature->GetScriptName() == "wg_se_workshop_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_SE, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_se_workshop_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_SE, TEAM_HORDE))
                    registered = true;
            }

            // SW workshop
            if (creature->GetScriptName() == "wg_sw_workshop_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_SW, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_sw_workshop_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_SW, TEAM_HORDE))
                    registered = true;
            }

            // NE workshop
            if (creature->GetScriptName() == "wg_ne_workshop_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_NE, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_ne_workshop_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_NE, TEAM_HORDE))
                    registered = true;
            }

            // NW workshop
            if (creature->GetScriptName() == "wg_nw_workshop_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_NW, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_nw_workshop_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_NW, TEAM_HORDE))
                    registered = true;
            }

            // East Bridge
            if (creature->GetScriptName() == "wg_east_bridge_guard")
            {
                if (AddCreatureInHolderByGUID(creature, EAST_BRIDGE_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_east_roaming_bridge_guard")
            {
                if (AddCreatureInHolderByGUID(creature, EAST_BRIDGE_GUARD, TEAM_HORDE))
                    registered = true;
            }

            // Middle Bridge
            if (creature->GetScriptName() == "wg_middle_bridge_guard")
            {
                if (AddCreatureInHolderByGUID(creature, MIDDLE_BRIDGE_GUARD, TEAM_HORDE))
                    registered = true;
            }
            if (creature->GetScriptName() == "wg_middle_roaming_bridge_guard")
            {
                if (AddCreatureInHolderByGUID(creature, MIDDLE_BRIDGE_GUARD, TEAM_HORDE))
                    registered = true;
            }

            // West Bridge
            if (creature->GetScriptName() == "wg_west_bridge_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WEST_BRIDGE_GUARD, TEAM_HORDE))
                    registered = true;
            }
            if (creature->GetScriptName() == "wg_west_roaming_bridge_guard")
            {
                if (AddCreatureInHolderByGUID(creature, WEST_BRIDGE_GUARD, TEAM_HORDE))
                    registered = true;
            }

            // DEFENDER SIDE SECTION
            if (creature->GetScriptName() == "wg_keep_NE_guard")
            {
                if (AddCreatureInHolderByGUID(creature, NE_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_keep_NW_guard")
            {
                if (AddCreatureInHolderByGUID(creature, NW_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_keep_SE_guard")
            {
                if (AddCreatureInHolderByGUID(creature, SE_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_keep_SW_guard")
            {
                if (AddCreatureInHolderByGUID(creature, SW_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_keep_fortress_gate_guard")
            {
                if (AddCreatureInHolderByGUID(creature, FORTRESS_GATE_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_keep_fortress_guard")
            {
                if (AddCreatureInHolderByGUID(creature, VAULT_GATE_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (!registered)
                TC_LOG_ERROR("system", "BATTLEFIELD_WG_NPC_GUARD_H not registered for GUID : %u", creature->GetSpawnId());
            break;
        }
    }

    // untested code - not sure if it is valid.
    if (IsWarTime())
    {
        switch (creature->GetEntry())
        {
            case NPC_WINTERGRASP_SIEGE_ENGINE_ALLIANCE:
            case NPC_WINTERGRASP_SIEGE_ENGINE_HORDE:
            case NPC_WINTERGRASP_CATAPULT:
            case NPC_WINTERGRASP_DEMOLISHER:
            {
                if (!creature->ToTempSummon() || !creature->ToTempSummon()->GetSummonerGUID() || !ObjectAccessor::FindPlayer(creature->ToTempSummon()->GetSummonerGUID()))
                {
                    creature->DespawnOrUnsummon();
                    return;
                }

                Player* creator = ObjectAccessor::FindPlayer(creature->ToTempSummon()->GetSummonerGUID());
                TeamId team = creator->GetTeamId();

                if (team == TEAM_HORDE)
                {
                    if (GetData(BATTLEFIELD_WG_DATA_VEHICLE_H) < GetData(BATTLEFIELD_WG_DATA_MAX_VEHICLE_H))
                    {
                        UpdateData(BATTLEFIELD_WG_DATA_VEHICLE_H, 1);
                        creature->AddAura(SPELL_HORDE_FLAG, creature);
                        m_vehicles[team].insert(creature->GetGUID());
                        UpdateVehicleCountWG();
                    }
                    else
                    {
                        creature->DespawnOrUnsummon();
                        return;
                    }
                }
                else
                {
                    if (GetData(BATTLEFIELD_WG_DATA_VEHICLE_A) < GetData(BATTLEFIELD_WG_DATA_MAX_VEHICLE_A))
                    {
                        UpdateData(BATTLEFIELD_WG_DATA_VEHICLE_A, 1);
                        creature->AddAura(SPELL_ALLIANCE_FLAG, creature);
                        m_vehicles[team].insert(creature->GetGUID());
                        UpdateVehicleCountWG();
                    }
                    else
                    {
                        creature->DespawnOrUnsummon();
                        return;
                    }
                }

                creature->CastSpell(creator, SPELL_GRAB_PASSENGER, true);
                break;
            }
        }
    }
}

void BattlefieldWG::OnCreatureRemove(Creature* creature)
{
/* possibly can be used later
    if (IsWarTime())
    {
        switch (creature->GetEntry())
        {
            case NPC_WINTERGRASP_SIEGE_ENGINE_ALLIANCE:
            case NPC_WINTERGRASP_SIEGE_ENGINE_HORDE:
            case NPC_WINTERGRASP_CATAPULT:
            case NPC_WINTERGRASP_DEMOLISHER:
            {
                uint8 team;
                if (creature->GetFaction() == WintergraspFaction[TEAM_ALLIANCE])
                    team = TEAM_ALLIANCE;
                else if (creature->GetFaction() == WintergraspFaction[TEAM_HORDE])
                    team = TEAM_HORDE;
                else
                    return;

                m_vehicles[team].erase(creature->GetGUID());
                if (team == TEAM_HORDE)
                    UpdateData(BATTLEFIELD_WG_DATA_VEHICLE_H, -1);
                else
                    UpdateData(BATTLEFIELD_WG_DATA_VEHICLE_A, -1);
                UpdateVehicleCountWG();

                break;
            }
        }
    }*/
}

void BattlefieldWG::OnGameObjectCreate(GameObject* go)
{
    /*
    uint8 workshopId = 0;

    switch (go->GetEntry())
    {
        case GO_WINTERGRASP_FACTORY_BANNER_NE:
            workshopId = BATTLEFIELD_WG_WORKSHOP_NE;
            break;
        case GO_WINTERGRASP_FACTORY_BANNER_NW:
            workshopId = BATTLEFIELD_WG_WORKSHOP_NW;
            break;
        case GO_WINTERGRASP_FACTORY_BANNER_SE:
            workshopId = BATTLEFIELD_WG_WORKSHOP_SE;
            break;
        case GO_WINTERGRASP_FACTORY_BANNER_SW:
            workshopId = BATTLEFIELD_WG_WORKSHOP_SW;
            break;
        default:
            return;
    }

    for (WintergraspWorkshop* workshop : Workshops)
    {
        if (workshop->GetId() == workshopId)
        {
            TeamId team = workshopId < BATTLEFIELD_WG_WORKSHOP_NE ? GetAttackerTeam() : GetDefenderTeam();
            WintergraspCapturePoint* capturePoint = new WintergraspCapturePoint(this, team);
            capturePoint->SetCapturePointData(go);
            capturePoint->LinkToWorkshop(workshop);
            capturePoint->SetInitialData(team);
            AddCapturePoint(capturePoint, workshopId);
        }
    }
    */
}

// Called when player kill a unit in wg zone
void BattlefieldWG::HandleKill(Player* killer, Unit* victim)
{
    if (killer == victim)
        return;

    if (victim->GetTypeId() == TYPEID_PLAYER)
    {
        HandlePromotion(killer, victim);

        // Allow to Skin non-released corpse
        victim->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE);
    }

    /// @todoRecent PvP activity worldstate
}

bool BattlefieldWG::FindAndRemoveVehicleFromList(Unit* vehicle)
{
    for (uint32 team = 0; team < PVP_TEAMS_COUNT; ++team)
    {
        auto itr = m_vehicles[team].find(vehicle->GetGUID());
        if (itr != m_vehicles[team].end())
        {
            m_vehicles[team].erase(itr);

            if (team == TEAM_HORDE)
                UpdateData(BATTLEFIELD_WG_DATA_VEHICLE_H, -1);
            else
                UpdateData(BATTLEFIELD_WG_DATA_VEHICLE_A, -1);
            return true;
        }
    }

    return false;
}

void BattlefieldWG::OnUnitDeath(Unit* unit)
{
    if (IsWarTime())
        if (unit->IsVehicle())
            if (FindAndRemoveVehicleFromList(unit))
                UpdateVehicleCountWG();
}

void BattlefieldWG::HandlePromotion(Player* playerKiller, Unit* unitKilled)
{
    uint32 teamId = playerKiller->GetTeamId();

    for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (itr->second.inWar && itr->second.team == teamId)
            if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
                if (player->GetDistance2d(unitKilled) < 40.0f)
                    PromotePlayer(player);
}

// Update rank for player
void BattlefieldWG::PromotePlayer(Player* killer)
{
    if (!m_isActive)
        return;
    // Updating rank of player
    if (Aura* auraRecruit = killer->GetAura(SPELL_RECRUIT))
    {
        if (auraRecruit->GetStackAmount() >= 5)
        {
            killer->RemoveAura(SPELL_RECRUIT);
            killer->CastSpell(killer, SPELL_CORPORAL, true);
            if (Creature* stalker = GetCreature(StalkerGuid))
                sCreatureTextMgr->SendChat(stalker, BATTLEFIELD_WG_TEXT_RANK_CORPORAL, killer, CHAT_MSG_ADDON, LANG_ADDON, TEXT_RANGE_NORMAL, 0, TEAM_OTHER, false, killer);
        }
        else
            killer->CastSpell(killer, SPELL_RECRUIT, true);
    }
    else if (Aura* auraCorporal = killer->GetAura(SPELL_CORPORAL))
    {
        if (auraCorporal->GetStackAmount() >= 5)
        {
            killer->RemoveAura(SPELL_CORPORAL);
            killer->CastSpell(killer, SPELL_LIEUTENANT, true);
            if (Creature* stalker = GetCreature(StalkerGuid))
                sCreatureTextMgr->SendChat(stalker, BATTLEFIELD_WG_TEXT_RANK_FIRST_LIEUTENANT, killer, CHAT_MSG_ADDON, LANG_ADDON, TEXT_RANGE_NORMAL, 0, TEAM_OTHER, false, killer);
        }
        else
            killer->CastSpell(killer, SPELL_CORPORAL, true);
    }
}

void BattlefieldWG::RemoveAurasFromPlayer(Player* player)
{
    player->RemoveAurasDueToSpell(SPELL_RECRUIT);
    player->RemoveAurasDueToSpell(SPELL_CORPORAL);
    player->RemoveAurasDueToSpell(SPELL_LIEUTENANT);
    player->RemoveAurasDueToSpell(SPELL_TOWER_CONTROL);
    player->RemoveAurasDueToSpell(SPELL_SPIRITUAL_IMMUNITY);
    player->RemoveAurasDueToSpell(SPELL_TENACITY);
    player->RemoveAurasDueToSpell(SPELL_ESSENCE_OF_WINTERGRASP);
    player->RemoveAurasDueToSpell(SPELL_WINTERGRASP_RESTRICTED_FLIGHT_AREA);
}

void BattlefieldWG::OnPlayerJoinWar(Player* player)
{
    RemoveAurasFromPlayer(player);

    player->CastSpell(player, SPELL_RECRUIT, true);

    if (player->GetZoneId() != m_ZoneId)
    {
        if (player->GetTeamId() == GetDefenderTeam())
            player->TeleportTo(571, 5345, 2842, 410, 3.14f);
        else
        {
            if (player->GetTeamId() == TEAM_HORDE)
                player->TeleportTo(571, 5025.857422f, 3674.628906f, 362.737122f, 4.135169f);
            else
                player->TeleportTo(571, 5101.284f, 2186.564f, 373.549f, 3.812f);
        }
    }

    UpdateTenacity();

    if (player->GetTeamId() == GetAttackerTeam())
    {
        if (GetData(BATTLEFIELD_WG_DATA_BROKEN_TOWER_ATT) < 3)
            player->SetAuraStack(SPELL_TOWER_CONTROL, player, 3 - GetData(BATTLEFIELD_WG_DATA_BROKEN_TOWER_ATT));
    }
    else
    {
        if (GetData(BATTLEFIELD_WG_DATA_BROKEN_TOWER_ATT) > 0)
           player->SetAuraStack(SPELL_TOWER_CONTROL, player, GetData(BATTLEFIELD_WG_DATA_BROKEN_TOWER_ATT));
    }
    SendInitWorldStatesTo(player);
}

void BattlefieldWG::OnPlayerLeaveWar(Player* player)
{
    // Remove all aura from WG /// @todo false we can go out of this zone on retail and keep Rank buff, remove on end of WG
    if (!player->GetSession()->PlayerLogout())
    {
        if (Creature* vehicle = player->GetVehicleCreatureBase())   // Remove vehicle of player if he go out.
            vehicle->DespawnOrUnsummon();

        RemoveAurasFromPlayer(player);
    }

    player->RemoveAurasDueToSpell(SPELL_HORDE_CONTROLS_FACTORY_PHASE_SHIFT);
    player->RemoveAurasDueToSpell(SPELL_ALLIANCE_CONTROLS_FACTORY_PHASE_SHIFT);
    player->RemoveAurasDueToSpell(SPELL_HORDE_CONTROL_PHASE_SHIFT);
    player->RemoveAurasDueToSpell(SPELL_ALLIANCE_CONTROL_PHASE_SHIFT);
    UpdateTenacity();
}

void BattlefieldWG::OnPlayerLeaveZone(Player* player)
{
    if (!m_isActive)
        RemoveAurasFromPlayer(player);

    player->RemoveAurasDueToSpell(SPELL_HORDE_CONTROLS_FACTORY_PHASE_SHIFT);
    player->RemoveAurasDueToSpell(SPELL_ALLIANCE_CONTROLS_FACTORY_PHASE_SHIFT);
    player->RemoveAurasDueToSpell(SPELL_HORDE_CONTROL_PHASE_SHIFT);
    player->RemoveAurasDueToSpell(SPELL_ALLIANCE_CONTROL_PHASE_SHIFT);
}

void BattlefieldWG::OnPlayerEnterZone(Player* player)
{
    if (!m_isActive)
        RemoveAurasFromPlayer(player);

    player->AddAura(m_DefenderTeam == TEAM_HORDE ? SPELL_HORDE_CONTROL_PHASE_SHIFT : SPELL_ALLIANCE_CONTROL_PHASE_SHIFT, player);
    // Send worldstate to player
    SendInitWorldStatesTo(player);
}

uint32 BattlefieldWG::GetData(uint32 data) const
{
    switch (data)
    {
        // Used to determine when the phasing spells must be cast
        // See: SpellArea::IsFitToRequirements
        case AREA_THE_SUNKEN_RING:
        case AREA_THE_BROKEN_TEMPLATE:
        case AREA_WESTPARK_WORKSHOP:
        case AREA_EASTPARK_WORKSHOP:
            // Graveyards and Workshops are controlled by the same team.
            if (BfGraveyard const* graveyard = GetGraveyardById(GetSpiritGraveyardId(data)))
                return graveyard->GetControlTeamId();
            break;
        default:
            break;
    }

    return Battlefield::GetData(data);
}

void BattlefieldWG::FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet)
{
    packet.Worldstates.emplace_back(WS_BATTLEFIELD_WG_DEFENDED_A, GetData(BATTLEFIELD_WG_DATA_DEF_A));
    packet.Worldstates.emplace_back(WS_BATTLEFIELD_WG_DEFENDED_H, GetData(BATTLEFIELD_WG_DATA_DEF_H));
    packet.Worldstates.emplace_back(WS_BATTLEFIELD_WG_ATTACKED_A, GetData(BATTLEFIELD_WG_DATA_WON_A));
    packet.Worldstates.emplace_back(WS_BATTLEFIELD_WG_ATTACKED_H, GetData(BATTLEFIELD_WG_DATA_WON_H));
    packet.Worldstates.emplace_back(WS_BATTLEFIELD_WG_ATTACKER, GetAttackerTeam());
    packet.Worldstates.emplace_back(WS_BATTLEFIELD_WG_DEFENDER, GetDefenderTeam());

    // Note: cleanup these two, their names look awkward
    packet.Worldstates.emplace_back(WS_BATTLEFIELD_WG_ACTIVE, IsWarTime() ? 0 : 1);
    packet.Worldstates.emplace_back(WS_BATTLEFIELD_WG_SHOW_WORLDSTATE, IsWarTime() ? 1 : 0);

    for (uint32 itr = 0; itr < 2; ++itr)
        packet.Worldstates.emplace_back(ClockWorldState[itr], int32(GameTime::GetGameTime()) + int32(m_Timer) / int32(1000));

    packet.Worldstates.emplace_back(WS_BATTLEFIELD_WG_VEHICLE_H, GetData(BATTLEFIELD_WG_DATA_VEHICLE_H));
    packet.Worldstates.emplace_back(WS_BATTLEFIELD_WG_MAX_VEHICLE_H, GetData(BATTLEFIELD_WG_DATA_MAX_VEHICLE_H));
    packet.Worldstates.emplace_back(WS_BATTLEFIELD_WG_VEHICLE_A, GetData(BATTLEFIELD_WG_DATA_VEHICLE_A));
    packet.Worldstates.emplace_back(WS_BATTLEFIELD_WG_MAX_VEHICLE_A, GetData(BATTLEFIELD_WG_DATA_MAX_VEHICLE_A));

    for (BfWGGameObjectBuilding* building : BuildingsInZone)
        building->FillInitialWorldStates(packet);

    for (WintergraspWorkshop* workshop : Workshops)
        workshop->FillInitialWorldStates(packet);
}

void BattlefieldWG::SendInitWorldStatesToAll()
{
    for (PlayerHolderContainer::const_iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
            SendInitWorldStatesTo(player);
}

void BattlefieldWG::BrokenWallOrTower(TeamId team, BfWGGameObjectBuilding* building)
{
    if (team == GetDefenderTeam())
    {
        for (PlayerHolderContainer::const_iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
            if (itr->second.inWar && itr->second.team == GetAttackerTeam())
                if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
                    if (player->GetDistance2d(ASSERT_NOTNULL(GetGameObject(building->GetGUID()))) < 50.0f)
                        player->KilledMonsterCredit(QUEST_CREDIT_DEFEND_SIEGE);
    }
}

// Called when a tower is broke
void BattlefieldWG::UpdatedDestroyedTowerCount(TeamId team)
{
    // Southern tower
    if (team == GetAttackerTeam())
    {
        // Update counter
        UpdateData(BATTLEFIELD_WG_DATA_DAMAGED_TOWER_ATT, -1);
        UpdateData(BATTLEFIELD_WG_DATA_BROKEN_TOWER_ATT, 1);

        for (PlayerHolderContainer::const_iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
            if (itr->second.inWar)
            {
                if (itr->second.team == GetAttackerTeam())
                {
                    // Remove buff stack on attackers
                    if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
                        player->RemoveAuraFromStack(SPELL_TOWER_CONTROL);
                }
                else
                {
                    // Add buff stack to defenders and give achievement/quest credit
                    if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
                    {
                        player->CastSpell(player, SPELL_TOWER_CONTROL, true);
                        player->KilledMonsterCredit(QUEST_CREDIT_TOWERS_DESTROYED);
                        DoCompleteOrIncrementAchievement(ACHIEVEMENTS_WG_TOWER_DESTROY, player);
                    }
                }
            }

        // If all three south towers are destroyed (ie. all attack towers), remove ten minutes from battle time
        if (GetData(BATTLEFIELD_WG_DATA_BROKEN_TOWER_ATT) == 3)
        {
            if (int32(m_Timer - 600000) < 0)
                m_Timer = 0;
            else
                m_Timer -= 600000;
            SendInitWorldStatesToAll();
        }
    }
    else // Keep tower
    {
        UpdateData(BATTLEFIELD_WG_DATA_DAMAGED_TOWER_DEF, -1);
        UpdateData(BATTLEFIELD_WG_DATA_BROKEN_TOWER_DEF, 1);
    }
}

void BattlefieldWG::ProcessEvent(WorldObject* obj, uint32 eventId)
{
    if (!obj || !IsWarTime())
        return;

    // We handle only gameobjects here
    GameObject* go = obj->ToGameObject();
    if (!go)
        return;

    // On click on titan relic
    if (go->GetEntry() == GO_WINTERGRASP_TITAN_S_RELIC)
    {
        if (CanInteractWithRelic())
            EndBattle(false);
        else if (GameObject* relic = GetRelic())
            relic->SetRespawnTime(RESPAWN_IMMEDIATELY);
    }

    // if destroy or damage event, search the wall/tower and update worldstate/send warning message
    for (BfWGGameObjectBuilding* building : BuildingsInZone)
    {
        if (go->GetGUID() == building->GetGUID())
        {
            if (GameObject* buildingGo = GetGameObject(building->GetGUID()))
            {
                if (buildingGo->GetGOInfo()->building.damagedEvent == eventId)
                    building->Damaged();
                else if (buildingGo->GetGOInfo()->building.destroyedEvent == eventId)
                    building->Destroyed();
                break;
            }
        }
    }
}

// Called when a tower is damaged, used for honor reward calcul
void BattlefieldWG::UpdateDamagedTowerCount(TeamId team)
{
    if (team == GetAttackerTeam())
        UpdateData(BATTLEFIELD_WG_DATA_DAMAGED_TOWER_ATT, 1);
    else
        UpdateData(BATTLEFIELD_WG_DATA_DAMAGED_TOWER_DEF, 1);
}

// Update vehicle count WorldState to player
void BattlefieldWG::UpdateVehicleCountWG()
{
    SendUpdateWorldState(WS_BATTLEFIELD_WG_VEHICLE_H,     GetData(BATTLEFIELD_WG_DATA_VEHICLE_H));
    SendUpdateWorldState(WS_BATTLEFIELD_WG_MAX_VEHICLE_H, GetData(BATTLEFIELD_WG_DATA_MAX_VEHICLE_H));
    SendUpdateWorldState(WS_BATTLEFIELD_WG_VEHICLE_A,     GetData(BATTLEFIELD_WG_DATA_VEHICLE_A));
    SendUpdateWorldState(WS_BATTLEFIELD_WG_MAX_VEHICLE_A, GetData(BATTLEFIELD_WG_DATA_MAX_VEHICLE_A));
}

void BattlefieldWG::UpdateTenacity()
{
    uint32 alliancePlayers = 0;
    uint32 hordePlayers = 0;
    for (PlayerHolderContainer::const_iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (itr->second.inWar)
        {
            if (itr->second.team == TEAM_ALLIANCE)
                alliancePlayers++;
            else if (itr->second.team == TEAM_HORDE)
                hordePlayers++;
        }
    int32 newStack = 0;

    if (alliancePlayers && hordePlayers)
    {
        if (alliancePlayers < hordePlayers)
            newStack = int32((float(hordePlayers / alliancePlayers) - 1) * 4);  // positive, should cast on alliance
        else if (alliancePlayers > hordePlayers)
            newStack = int32((1 - float(alliancePlayers / hordePlayers)) * 4);  // negative, should cast on horde
    }

    if (newStack == int32(m_tenacityStack))
        return;

    m_tenacityStack = newStack;

    // Apply new buff
    if (newStack)
    {
        m_tenacityTeam = newStack > 0 ? TEAM_ALLIANCE : TEAM_HORDE;

        if (newStack < 0)
            newStack = -newStack;
        if (newStack > 20)
            newStack = 20;

        uint32 buff_honor = SPELL_GREATEST_HONOR;
        if (newStack < 15)
            buff_honor = SPELL_GREATER_HONOR;
        if (newStack < 10)
            buff_honor = SPELL_GREAT_HONOR;
        if (newStack < 5)
            buff_honor = 0;

        for (PlayerHolderContainer::const_iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        {
            if (itr->second.team == m_tenacityTeam)
            {
                // Remove old buff
                if (m_tenacityTeam != TEAM_NEUTRAL)
                {
                    if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
                        if (player->GetLevel() >= m_MinLevel)
                            player->RemoveAurasDueToSpell(SPELL_TENACITY);

                }

                if (itr->second.inWar)
                    if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
                    {
                        player->SetAuraStack(SPELL_TENACITY, player, newStack);

                        if (buff_honor != 0)
                            player->CastSpell(player, buff_honor, true);
                    }
            }
        }

        // Remove old buff
        if (m_tenacityTeam != TEAM_NEUTRAL)
        {
            for (auto itr = m_vehicles[m_tenacityTeam].begin(); itr != m_vehicles[m_tenacityTeam].end(); ++itr)
                if (Creature* creature = GetCreature(*itr))
                    creature->RemoveAurasDueToSpell(SPELL_TENACITY_VEHICLE);
        }

        for (auto itr = m_vehicles[m_tenacityTeam].begin(); itr != m_vehicles[m_tenacityTeam].end(); ++itr)
            if (Creature* creature = GetCreature(*itr))
                creature->SetAuraStack(SPELL_TENACITY_VEHICLE, creature, newStack);

        if (buff_honor != 0)
        {
            for (auto itr = m_vehicles[m_tenacityTeam].begin(); itr != m_vehicles[m_tenacityTeam].end(); ++itr)
                if (Creature* creature = GetCreature(*itr))
                    creature->CastSpell(creature, buff_honor, true);
        }
    }
    else
        m_tenacityTeam = TEAM_NEUTRAL;
}

bool BattlefieldWG::IsCreatureInHolder(ObjectGuid guid)
{
    bool result = false;
    for (CreatureHolderContainer::const_iterator itr = m_CreatureMap.begin(); itr != m_CreatureMap.end(); ++itr)
        if (itr->second.m_GUID == guid)
        {
            result = true;
            if (Creature* creature = GetCreature(itr->second.m_GUID))
            {
                if (itr->second.m_isActive)
                    ShowNpc(creature, true);
                else
                    HideNpc(creature);
            }
        }

    return result;
}

bool BattlefieldWG::AddCreatureInHolderByGUID(Creature* creature, uint8 npcType, TeamId team)
{
    if (IsCreatureInHolder(creature->GetGUID()))
        return false;

    UpdateStatusForCreature(creature, npcType);

    // find max id
    uint32 new_id = 0;
    for (CreatureHolderContainer::const_iterator itr = m_CreatureMap.begin(); itr != m_CreatureMap.end(); ++itr)
        if (itr->first > new_id)
            new_id = itr->first;

    // use next
    ++new_id;

    CreatureHolder ch;
    ch.m_GUID = creature->GetGUID();
    ch.m_npcType = npcType;
    ch.m_team = team;
    ch.m_isActive = creature->IsVisible();
    m_CreatureMap[new_id] = ch;
    return true;
}

void BattlefieldWG::UpdateStatusForCreature(Creature* creature, uint8 npcType)
{
    switch (npcType)
    {
        // Turret sector
        case WEST_TOWER_TURRET:
        case MIDDLE_TOWER_TURRET:
        case EAST_TOWER_TURRET:        
        case FORTRESS_GATE_TURRET:
        case VAULT_GATE_TURRET:
        case NE_TOWER_TURRET:
        case NW_TOWER_TURRET:
        case SE_TOWER_TURRET:
        case SW_TOWER_TURRET:
        {
            for (BfWGGameObjectBuilding* building : BuildingsInZone)
            {
                if (building->GetID() == NPCGroup[npcType])
                {
                    if (!building->IsAlive())
                        HideNpc(creature);
                    else
                        creature->SetFaction(WintergraspFaction[building->GetTeamController()]);
                }
            }
            break;
        }

        // Bridge sector
        case WEST_BRIDGE_GUARD:
        case MIDDLE_BRIDGE_GUARD:
        case EAST_BRIDGE_GUARD:
        {
            if (creature->GetFaction() == NPCGuardFaction[GetAttackerTeam()])
                ShowNpc(creature, true);
            else
                HideNpc(creature);
            break;
        }

        // Guard sector
        case WEST_TOWER_GUARD:
        case MIDDLE_TOWER_GUARD:
        case EAST_TOWER_GUARD:        
        case NE_TOWER_GUARD:
        case NW_TOWER_GUARD:
        case SE_TOWER_GUARD:
        case SW_TOWER_GUARD:
        case FORTRESS_GATE_GUARD:
        case VAULT_GATE_GUARD:        
        {
            for (BfWGGameObjectBuilding* building : BuildingsInZone)
            {
                if (building->GetID() == NPCGroup[npcType])
                {
                    if (creature->GetFaction() == NPCGuardFaction[building->GetTeamController()])
                    {
                        if (building->IsAlive())
                            ShowNpc(creature, true);
                    }
                    else
                        HideNpc(creature);
                }
            }
            break;
        }

        //workshop sector
        case WG_WORKSHOP_SE:
        case WG_WORKSHOP_SW:
        case WG_WORKSHOP_NE:
        case WG_WORKSHOP_NW:
        case WG_WORKSHOP_KEEP_WEST:
        case WG_WORKSHOP_KEEP_EAST:
        {
            uint8 groupbyworkshopid = 0;
            for (WintergraspWorkshop* workshop : Workshops)
            {
                groupbyworkshopid = npcType - 21;
                if (workshop->GetId() == groupbyworkshopid)
                {
                    switch (creature->GetEntry())
                    {
                        case NPC_WORKSHOP_MECHANIC_HORDE:
                        case NPC_WORKSHOP_MECHANIC_ALLIANCE:
                        {
                            if (creature->GetFaction() == NPCMechanicFaction[workshop->GetTeamControl()])
                                ShowNpc(creature, true);
                            else
                                HideNpc(creature);
                            break;
                        }
                        case BATTLEFIELD_WG_NPC_GUARD_H:
                        case BATTLEFIELD_WG_NPC_GUARD_A:
                        {
                            if (creature->GetFaction() == NPCGuardFaction[workshop->GetTeamControl()])
                                ShowNpc(creature, true);
                            else
                                HideNpc(creature);
                            break;
                        }
                    }
                }
            }
            break;
        }
    }
}

void BattlefieldWG::ShowCreatureByNPCType(uint8 npcType, TeamId team)
{
    for (CreatureHolderContainer::iterator itr = m_CreatureMap.begin(); itr != m_CreatureMap.end(); ++itr)
        if (itr->second.m_npcType == npcType && itr->second.m_team == team)
        {
            if (Creature* creature = GetCreature(itr->second.m_GUID))
                ShowNpc(creature, true);
            itr->second.m_isActive = true;
        }
}

void BattlefieldWG::HideCreatureByNPCType(uint8 npcType, TeamId team)
{
    for (CreatureHolderContainer::iterator itr = m_CreatureMap.begin(); itr != m_CreatureMap.end(); ++itr)
        if (itr->second.m_npcType == npcType && itr->second.m_team == team)
        {
            if (Creature* creature = GetCreature(itr->second.m_GUID))
                HideNpc(creature);
            itr->second.m_isActive = false;
        }
}

void BattlefieldWG::UpdateCreatureTurretByNPCType(uint8 npcType, TeamId team)
{
    for (CreatureHolderContainer::iterator itr = m_CreatureMap.begin(); itr != m_CreatureMap.end(); ++itr)
        if (itr->second.m_npcType == npcType)
        {
            if (Creature* creature = GetCreature(itr->second.m_GUID))
            {
                ShowNpc(creature, true);
                creature->SetFaction(WintergraspFaction[team]);
            }
            itr->second.m_isActive = true;
        }
}

void BattlefieldWG::HideCreatureTurretByNPCType(uint8 npcType)
{
    for (CreatureHolderContainer::iterator itr = m_CreatureMap.begin(); itr != m_CreatureMap.end(); ++itr)
        if (itr->second.m_npcType == npcType)
        {
            if (Creature* creature = GetCreature(itr->second.m_GUID))
            {
                ShowNpc(creature, true);                
            }
            itr->second.m_isActive = false;
        }
}

void BattlefieldWG::UpdateAllGuardsAndTurretsBeforeBattle()
{
    //              Attack Towers
    // guards
    ShowCreatureByNPCType(EAST_TOWER_GUARD, GetAttackerTeam());
    HideCreatureByNPCType(EAST_TOWER_GUARD, GetDefenderTeam());

    ShowCreatureByNPCType(MIDDLE_TOWER_GUARD, GetAttackerTeam());
    HideCreatureByNPCType(MIDDLE_TOWER_GUARD, GetDefenderTeam());

    ShowCreatureByNPCType(WEST_TOWER_GUARD, GetAttackerTeam());
    HideCreatureByNPCType(WEST_TOWER_GUARD, GetDefenderTeam());

    // turrets
    UpdateCreatureTurretByNPCType(WEST_TOWER_TURRET, GetAttackerTeam());
    UpdateCreatureTurretByNPCType(MIDDLE_TOWER_TURRET, GetAttackerTeam());
    UpdateCreatureTurretByNPCType(EAST_TOWER_TURRET, GetAttackerTeam());

    //              bridges
    // guards
    ShowCreatureByNPCType(WEST_BRIDGE_GUARD, GetAttackerTeam());
    HideCreatureByNPCType(WEST_BRIDGE_GUARD, GetDefenderTeam());

    ShowCreatureByNPCType(MIDDLE_BRIDGE_GUARD, GetAttackerTeam());
    HideCreatureByNPCType(MIDDLE_BRIDGE_GUARD, GetDefenderTeam());

    ShowCreatureByNPCType(EAST_BRIDGE_GUARD, GetAttackerTeam());
    HideCreatureByNPCType(EAST_BRIDGE_GUARD, GetDefenderTeam());

    //              workshops
    // guards
    ShowCreatureByNPCType(WG_WORKSHOP_SE, GetAttackerTeam()); // workshop on south should be owned by attacker team by default
    HideCreatureByNPCType(WG_WORKSHOP_SE, GetDefenderTeam());

    ShowCreatureByNPCType(WG_WORKSHOP_SW, GetAttackerTeam()); // workshop on south should be owned by attacker team by default
    HideCreatureByNPCType(WG_WORKSHOP_SW, GetDefenderTeam());

    ShowCreatureByNPCType(WG_WORKSHOP_NE, GetDefenderTeam()); // workshop on north should be owned by defender team by default
    HideCreatureByNPCType(WG_WORKSHOP_NE, GetAttackerTeam());

    ShowCreatureByNPCType(WG_WORKSHOP_NW, GetDefenderTeam()); // workshop on north should be owned by defender team by default
    HideCreatureByNPCType(WG_WORKSHOP_NW, GetAttackerTeam());

    ShowCreatureByNPCType(WG_WORKSHOP_KEEP_WEST, GetDefenderTeam());
    HideCreatureByNPCType(WG_WORKSHOP_KEEP_WEST, GetAttackerTeam());

    ShowCreatureByNPCType(WG_WORKSHOP_KEEP_EAST, GetDefenderTeam());
    HideCreatureByNPCType(WG_WORKSHOP_KEEP_EAST, GetAttackerTeam());
}

WintergraspCapturePoint::WintergraspCapturePoint(BattlefieldWG* battlefield, TeamId teamInControl) : BfCapturePoint(battlefield)
{
    m_Bf = battlefield;
    m_team = teamInControl;
    m_Workshop = nullptr;
}

void WintergraspCapturePoint::ChangeTeam(TeamId newTeam)
{
    ASSERT(m_Workshop);
    m_Workshop->GiveControlTo(newTeam);
}

BfGraveyardWG::BfGraveyardWG(BattlefieldWG* battlefield) : BfGraveyard(battlefield)
{
    m_Bf = battlefield;
    m_GossipTextId = 0;
}

BfWGGameObjectBuilding::BfWGGameObjectBuilding(BattlefieldWG* wg, WintergraspGameObjectBuildingType type, uint32 worldState)
{
    ASSERT(wg);

    _wg = wg;
    _buildID = 0;
    _teamControl = TEAM_NEUTRAL;
    _type = type;
    _worldState = worldState;
    _state = BATTLEFIELD_WG_OBJECTSTATE_NONE;
    _staticTowerInfo = nullptr;
}

BfWGGameObjectBuilding::~BfWGGameObjectBuilding()
{
    for (int8 i = 0; i < PVP_TEAMS_COUNT; i++)
        m_GameObjectList[i].clear();
}

void BfWGGameObjectBuilding::Rebuild()
{
    switch (_type)
    {
        case BATTLEFIELD_WG_OBJECTTYPE_KEEP_TOWER:
        case BATTLEFIELD_WG_OBJECTTYPE_DOOR_LAST:
        case BATTLEFIELD_WG_OBJECTTYPE_DOOR:
        case BATTLEFIELD_WG_OBJECTTYPE_WALL:
            _teamControl = _wg->GetDefenderTeam();      // Objects that are part of the keep should be the defender's
            break;
        case BATTLEFIELD_WG_OBJECTTYPE_TOWER:
            _teamControl = _wg->GetAttackerTeam();      // The towers in the south should be the attacker's
            break;
        default:
            _teamControl = TEAM_NEUTRAL;
            break;
    }

    if (GameObject* build = _wg->GetGameObject(_buildGUID))
    {
        // Rebuild gameobject
        if (build->IsDestructibleBuilding())
        {
            build->SetDestructibleState(GO_DESTRUCTIBLE_REBUILDING, nullptr, true);
            if (build->GetEntry() == GO_WINTERGRASP_VAULT_GATE)
                if (GameObject* go = build->FindNearestGameObject(GO_WINTERGRASP_KEEP_COLLISION_WALL, 50.0f))
                    go->SetGoState(GO_STATE_ACTIVE);

            // Update worldstate
            _state = WintergraspGameObjectState(BATTLEFIELD_WG_OBJECTSTATE_ALLIANCE_INTACT - (_teamControl * 3));
            _wg->SendUpdateWorldState(_worldState, _state);
        }        
        build->SetFaction(WintergraspFaction[_teamControl]);
        UpdateGo();
    }
}

void BfWGGameObjectBuilding::RebuildGate()
{
    if (GameObject* build = _wg->GetGameObject(_buildGUID))
    {
        if (build->IsDestructibleBuilding() && build->GetEntry() == GO_WINTERGRASP_VAULT_GATE)
        {
            if (GameObject* go = build->FindNearestGameObject(GO_WINTERGRASP_KEEP_COLLISION_WALL, 50.0f))
                go->SetGoState(GO_STATE_READY); //not GO_STATE_ACTIVE
        }
    }
}

void BfWGGameObjectBuilding::Damaged()
{
    // Update worldstate
    _state = WintergraspGameObjectState(BATTLEFIELD_WG_OBJECTSTATE_ALLIANCE_DAMAGE - (_teamControl * 3));
    _wg->SendUpdateWorldState(_worldState, _state);

    // Send warning message
    if (_staticTowerInfo)
        _wg->SendWarning(_staticTowerInfo->TextIds.Damaged);

    switch (GetID())
    {
        // Attack Towers
        case GO_WINTERGRASP_SHADOWSIGHT_TOWER:
        {
            _wg->HideCreatureByNPCType(WEST_TOWER_GUARD, _teamControl);
            _wg->HideCreatureTurretByNPCType(WEST_TOWER_TURRET);
            break;
        }
        case GO_WINTERGRASP_WINTER_S_EDGE_TOWER:
        {
            _wg->HideCreatureByNPCType(MIDDLE_TOWER_GUARD, _teamControl);
            _wg->HideCreatureTurretByNPCType(MIDDLE_TOWER_TURRET);
            break;
        }
        case GO_WINTERGRASP_FLAMEWATCH_TOWER:
        {
            _wg->HideCreatureByNPCType(EAST_TOWER_GUARD, _teamControl);
            _wg->HideCreatureTurretByNPCType(EAST_TOWER_TURRET);
            break;
        }

        case GO_WINTERGRASP_FACTORY_BANNER_NE: break;
        case GO_WINTERGRASP_FACTORY_BANNER_NW: break;
        case GO_WINTERGRASP_FACTORY_BANNER_SE: break;
        case GO_WINTERGRASP_FACTORY_BANNER_SW: break;

        case GO_WINTERGRASP_TITAN_S_RELIC: break;

        case GO_WINTERGRASP_FORTRESS_TOWER_NW: break;
        case GO_WINTERGRASP_FORTRESS_TOWER_SW: break;
        case GO_WINTERGRASP_FORTRESS_TOWER_SE: break;
        case GO_WINTERGRASP_FORTRESS_TOWER_NE: break;

        case GO_WINTERGRASP_FORTRESS_GATE: break;
        case GO_WINTERGRASP_VAULT_GATE: break;

        case GO_WINTERGRASP_KEEP_COLLISION_WALL: break;
    }

    if (_type == BATTLEFIELD_WG_OBJECTTYPE_KEEP_TOWER)
        _wg->UpdateDamagedTowerCount(_wg->GetDefenderTeam());
    else if (_type == BATTLEFIELD_WG_OBJECTTYPE_TOWER)
        _wg->UpdateDamagedTowerCount(_wg->GetAttackerTeam());
}

void BfWGGameObjectBuilding::Destroyed()
{
    // Update worldstate
    _state = WintergraspGameObjectState(BATTLEFIELD_WG_OBJECTSTATE_ALLIANCE_DESTROY - (_teamControl * 3));
    _wg->SendUpdateWorldState(_worldState, _state);

    // Warn players
    if (_staticTowerInfo)
        _wg->SendWarning(_staticTowerInfo->TextIds.Destroyed);

    switch (_type)
    {
        // Inform the global wintergrasp script of the destruction of this object
        case BATTLEFIELD_WG_OBJECTTYPE_TOWER:
        case BATTLEFIELD_WG_OBJECTTYPE_KEEP_TOWER:
            _wg->UpdatedDestroyedTowerCount(_teamControl);
            break;
        case BATTLEFIELD_WG_OBJECTTYPE_DOOR_LAST:
            if (GameObject* build = _wg->GetGameObject(_buildGUID))
                if (GameObject* go = build->FindNearestGameObject(GO_WINTERGRASP_KEEP_COLLISION_WALL, 50.0f))
                    go->SetGoState(GO_STATE_ACTIVE);
            _wg->SetRelicInteractible(true);
            if (_wg->GetRelic())
                _wg->GetRelic()->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE | GO_FLAG_NOT_SELECTABLE);
            else
                TC_LOG_ERROR("bg.battlefield.wg", "Titan Relic not found.");
            break;
        default:
            break;
    }

    _wg->BrokenWallOrTower(_teamControl, this);
}

void BfWGGameObjectBuilding::Init(GameObject* go)
{
    if (!go)
        return;

    // GameObject associated to object
    _buildGUID = go->GetGUID();

    switch (_type)
    {
        case BATTLEFIELD_WG_OBJECTTYPE_KEEP_TOWER:
        case BATTLEFIELD_WG_OBJECTTYPE_DOOR_LAST:
        case BATTLEFIELD_WG_OBJECTTYPE_DOOR:
        case BATTLEFIELD_WG_OBJECTTYPE_WALL:
            _teamControl = _wg->GetDefenderTeam();           // Objects that are part of the keep should be the defender's
            break;
        case BATTLEFIELD_WG_OBJECTTYPE_TOWER:
            _teamControl = _wg->GetAttackerTeam();           // The towers in the south should be the attacker's
            break;
        default:
            _teamControl = TEAM_NEUTRAL;
            break;
    }

    _state = WintergraspGameObjectState(sWorld->getWorldState(_worldState));
    switch (_state)
    {
        case BATTLEFIELD_WG_OBJECTSTATE_NEUTRAL_INTACT:
        case BATTLEFIELD_WG_OBJECTSTATE_ALLIANCE_INTACT:
        case BATTLEFIELD_WG_OBJECTSTATE_HORDE_INTACT:
            go->SetDestructibleState(GO_DESTRUCTIBLE_REBUILDING, nullptr, true);
            break;
        case BATTLEFIELD_WG_OBJECTSTATE_NEUTRAL_DESTROY:
        case BATTLEFIELD_WG_OBJECTSTATE_ALLIANCE_DESTROY:
        case BATTLEFIELD_WG_OBJECTSTATE_HORDE_DESTROY:
            go->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
            break;
        case BATTLEFIELD_WG_OBJECTSTATE_NEUTRAL_DAMAGE:
        case BATTLEFIELD_WG_OBJECTSTATE_ALLIANCE_DAMAGE:
        case BATTLEFIELD_WG_OBJECTSTATE_HORDE_DAMAGE:
            go->SetDestructibleState(GO_DESTRUCTIBLE_DAMAGED);
            break;
        default:
            break;
    }

    int32 towerId = -1;
    _buildID = go->GetEntry();
    switch (go->GetEntry())
    {
        case GO_WINTERGRASP_FORTRESS_TOWER_NW:
            towerId = BATTLEFIELD_WG_TOWER_FORTRESS_NW;
            break;
        case GO_WINTERGRASP_FORTRESS_TOWER_SW:
            towerId = BATTLEFIELD_WG_TOWER_FORTRESS_SW;
            break;
        case GO_WINTERGRASP_FORTRESS_TOWER_SE:
            towerId = BATTLEFIELD_WG_TOWER_FORTRESS_SE;
            break;
        case GO_WINTERGRASP_FORTRESS_TOWER_NE:
            towerId = BATTLEFIELD_WG_TOWER_FORTRESS_NE;
            break;
        case GO_WINTERGRASP_SHADOWSIGHT_TOWER:
            towerId = BATTLEFIELD_WG_TOWER_SHADOWSIGHT;
            break;
        case GO_WINTERGRASP_WINTER_S_EDGE_TOWER:
            towerId = BATTLEFIELD_WG_TOWER_WINTER_S_EDGE;
            break;
        case GO_WINTERGRASP_FLAMEWATCH_TOWER:
            towerId = BATTLEFIELD_WG_TOWER_FLAMEWATCH;
            break;
    }

    if (towerId >= BATTLEFIELD_WG_TOWER_SHADOWSIGHT) // Attacker towers
    {
        // Spawn associate gameobjects
        for (WintergraspGameObjectData const& gobData : AttackTowers[towerId - 4].GameObject)
        {
            if (GameObject* goHorde = _wg->SpawnGameObject(gobData.HordeEntry, gobData.Pos, gobData.Rot))
                m_GameObjectList[TEAM_HORDE].push_back(goHorde->GetGUID());

            if (GameObject* goAlliance = _wg->SpawnGameObject(gobData.AllianceEntry, gobData.Pos, gobData.Rot))
                m_GameObjectList[TEAM_ALLIANCE].push_back(goAlliance->GetGUID());
        }
    }

    if (towerId >= 0)
    {
        ASSERT(towerId < WG_MAX_TOWER);
        _staticTowerInfo = &TowerData[towerId];        
        UpdateGo();
    }
}

void BfWGGameObjectBuilding::UpdateGo()
{
    if (!m_GameObjectList[_wg->GetDefenderTeam()].empty())
        for (ObjectGuid guid : m_GameObjectList[_wg->GetDefenderTeam()])
            if (GameObject* go = _wg->GetGameObject(guid))
                go->SetRespawnTime(RESPAWN_ONE_DAY);

    if (!m_GameObjectList[_wg->GetAttackerTeam()].empty())
        for (ObjectGuid guid : m_GameObjectList[_wg->GetAttackerTeam()])
            if (GameObject* go = _wg->GetGameObject(guid))
                go->SetRespawnTime(RESPAWN_IMMEDIATELY);
}

void BfWGGameObjectBuilding::FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet)
{
    packet.Worldstates.emplace_back(_worldState, _state);
}

void BfWGGameObjectBuilding::Save()
{
    sWorld->setWorldState(_worldState, _state);
}

WintergraspWorkshop::WintergraspWorkshop(BattlefieldWG* wg, uint8 type)
{
    ASSERT(wg && type < WG_MAX_WORKSHOP);

    _wg = wg;
    _state = BATTLEFIELD_WG_OBJECTSTATE_NONE;
    _teamControl = TEAM_NEUTRAL;
    _staticInfo = &WorkshopData[type];

    if (GetId() < BATTLEFIELD_WG_WORKSHOP_KEEP_WEST)
    {
        // Spawn associate gameobjects
        for (WintergraspGameObjectData const& gobData : WorksshopGO[GetId()].GameObject)
        {
            if (GameObject* goHorde = _wg->SpawnGameObject(gobData.HordeEntry, gobData.Pos, gobData.Rot))
                m_GOList[TEAM_HORDE].push_back(goHorde->GetGUID());

            if (GameObject* goAlliance = _wg->SpawnGameObject(gobData.AllianceEntry, gobData.Pos, gobData.Rot))
                m_GOList[TEAM_ALLIANCE].push_back(goAlliance->GetGUID());
        }
    }
}

WintergraspWorkshop::~WintergraspWorkshop()
{
    // note : in WintergraspWorkshop  in m_GameObjectList we have 3 team (TEAM_NEUTRALL) too
    for (int8 i = 0; i < 3; i++)
        m_GOList[i].clear();
    m_workshopGO.clear();
}

uint8 WintergraspWorkshop::GetId() const
{
    return _staticInfo->WorkshopId;
}

void WintergraspWorkshop::InitialWorkshopAndCapturePoint(TeamId teamId, uint8 workshopId)
{
    if (workshopId < BATTLEFIELD_WG_WORKSHOP_KEEP_WEST)
    {
        if (GameObject* goWorkshop = _wg->SpawnGameObject(WGworkshopData[workshopId].entry, WGworkshopData[workshopId].Pos, WGworkshopData[workshopId].Rot))
        {
            m_workshopGO.push_back(goWorkshop->GetGUID());

            if (WintergraspCapturePoint* capturePoint = new WintergraspCapturePoint(_wg, teamId))
            {
                capturePoint->SetCapturePointData(goWorkshop);
                capturePoint->LinkToWorkshop(this);
                capturePoint->SetInitialData(teamId);
                _wg->AddCapturePoint(capturePoint, workshopId);
            }
        }
    }

    GiveControlTo(teamId, true);
}

void WintergraspWorkshop::GiveControlTo(TeamId teamId, bool init /*= false*/)
{
    switch (teamId)
    {
        case TEAM_NEUTRAL:
        {
            // Updating worldstate
            _state = BATTLEFIELD_WG_OBJECTSTATE_NEUTRAL_INTACT;
            _wg->SendUpdateWorldState(_staticInfo->WorldStateId, _state);

            if (!init)
            {
                if (_teamControl == TEAM_ALLIANCE)
                    _wg->SendWarning(_staticInfo->TextIds.HordeAttack); // workshop taken - horde
                else
                    _wg->SendWarning(_staticInfo->TextIds.AllianceAttack); // workshop taken - alliance
            }                

            // Found associate graveyard and update it
            if (_staticInfo->WorkshopId < BATTLEFIELD_WG_WORKSHOP_KEEP_WEST)
                if (BfGraveyard* gy = _wg->GetGraveyardById(_staticInfo->WorkshopId))
                    gy->GiveControlTo(TEAM_NEUTRAL);

            _teamControl = teamId;
            break;
        }
        case TEAM_ALLIANCE:
        {
            // Updating worldstate
            _state = BATTLEFIELD_WG_OBJECTSTATE_ALLIANCE_INTACT;
            _wg->SendUpdateWorldState(_staticInfo->WorldStateId, _state);

            // Warning message
            if (!init)
                _wg->SendWarning(_staticInfo->TextIds.AllianceCapture); // workshop taken - alliance

            // Found associate graveyard and update it
            if (_staticInfo->WorkshopId < BATTLEFIELD_WG_WORKSHOP_KEEP_WEST)
                if (BfGraveyard* gy = _wg->GetGraveyardById(_staticInfo->WorkshopId))
                    gy->GiveControlTo(TEAM_ALLIANCE);

            _teamControl = teamId;
            break;
        }
        case TEAM_HORDE:
        {
            // Update worldstate
            _state = BATTLEFIELD_WG_OBJECTSTATE_HORDE_INTACT;
            _wg->SendUpdateWorldState(_staticInfo->WorldStateId, _state);

            // Warning message
            if (!init)
                _wg->SendWarning(_staticInfo->TextIds.HordeCapture); // workshop taken - horde

            // Update graveyard control
            if (_staticInfo->WorkshopId < BATTLEFIELD_WG_WORKSHOP_KEEP_WEST)
                if (BfGraveyard* gy = _wg->GetGraveyardById(_staticInfo->WorkshopId))
                    gy->GiveControlTo(TEAM_HORDE);

            _teamControl = teamId;
            break;
        }
    }    

    if (!init)
        _wg->UpdateCounterVehicle(false);
    else
    {
        if (BfCapturePoint* cp = _wg->GetCapturePoint(GetId()))
            cp->SetInitialData(_teamControl);
    }

    UpdateCreatureAndGo();
}

void WintergraspWorkshop::UpdateCreatureAndGo()
{
    switch (GetId())
    {
        case BATTLEFIELD_WG_WORKSHOP_SE:
        {
            _wg->ShowCreatureByNPCType(WG_WORKSHOP_SE, _teamControl);
            if (_teamControl != TEAM_NEUTRAL)
                _wg->HideCreatureByNPCType(WG_WORKSHOP_SE, _wg->GetOtherTeam(_teamControl));
            else
            {
                _wg->HideCreatureByNPCType(WG_WORKSHOP_SE, TEAM_ALLIANCE);
                _wg->HideCreatureByNPCType(WG_WORKSHOP_SE, TEAM_HORDE);
            }
            break;
        }
        case BATTLEFIELD_WG_WORKSHOP_SW:
        {
            _wg->ShowCreatureByNPCType(WG_WORKSHOP_SW, _teamControl);
            if (_teamControl != TEAM_NEUTRAL)
                _wg->HideCreatureByNPCType(WG_WORKSHOP_SW, _wg->GetOtherTeam(_teamControl));
            else
            {
                _wg->HideCreatureByNPCType(WG_WORKSHOP_SW, TEAM_ALLIANCE);
                _wg->HideCreatureByNPCType(WG_WORKSHOP_SW, TEAM_HORDE);
            }
            break;
        }
        case BATTLEFIELD_WG_WORKSHOP_NE:
        {
            _wg->ShowCreatureByNPCType(WG_WORKSHOP_NE, _teamControl);
            if (_teamControl != TEAM_NEUTRAL)
                _wg->HideCreatureByNPCType(WG_WORKSHOP_NE, _wg->GetOtherTeam(_teamControl));
            else
            {
                _wg->HideCreatureByNPCType(WG_WORKSHOP_NE, TEAM_ALLIANCE);
                _wg->HideCreatureByNPCType(WG_WORKSHOP_NE, TEAM_HORDE);
            }
            break;
        }
        case BATTLEFIELD_WG_WORKSHOP_NW:
        {
            _wg->ShowCreatureByNPCType(WG_WORKSHOP_NW, _teamControl);
            if (_teamControl != TEAM_NEUTRAL)
                _wg->HideCreatureByNPCType(WG_WORKSHOP_NW, _wg->GetOtherTeam(_teamControl));
            else
            {
                _wg->HideCreatureByNPCType(WG_WORKSHOP_NW, TEAM_ALLIANCE);
                _wg->HideCreatureByNPCType(WG_WORKSHOP_NW, TEAM_HORDE);
            }
            break;
        }
        case BATTLEFIELD_WG_WORKSHOP_KEEP_WEST:
        {
            _wg->ShowCreatureByNPCType(WG_WORKSHOP_KEEP_WEST, _teamControl);
            if (_teamControl != TEAM_NEUTRAL)
                _wg->HideCreatureByNPCType(WG_WORKSHOP_KEEP_WEST, _wg->GetOtherTeam(_teamControl));
            else
            {
                _wg->HideCreatureByNPCType(WG_WORKSHOP_KEEP_WEST, TEAM_ALLIANCE);
                _wg->HideCreatureByNPCType(WG_WORKSHOP_KEEP_WEST, TEAM_HORDE);
            }
            break;
        }
        case BATTLEFIELD_WG_WORKSHOP_KEEP_EAST:
        {
            _wg->ShowCreatureByNPCType(WG_WORKSHOP_KEEP_EAST, _teamControl);
            if (_teamControl != TEAM_NEUTRAL)
                _wg->HideCreatureByNPCType(WG_WORKSHOP_KEEP_EAST, _wg->GetOtherTeam(_teamControl));
            else
            {
                _wg->HideCreatureByNPCType(WG_WORKSHOP_KEEP_EAST, TEAM_ALLIANCE);
                _wg->HideCreatureByNPCType(WG_WORKSHOP_KEEP_EAST, TEAM_HORDE);
            }
            break;
        }
    }

    switch (_teamControl)
    {
        case TEAM_NEUTRAL:
        {
            if (!m_GOList[TEAM_HORDE].empty())
                for (ObjectGuid guid : m_GOList[TEAM_HORDE])
                    if (GameObject* go = _wg->GetGameObject(guid))
                        go->SetRespawnTime(RESPAWN_ONE_DAY);

            if (!m_GOList[TEAM_ALLIANCE].empty())
                for (ObjectGuid guid : m_GOList[TEAM_ALLIANCE])
                    if (GameObject* go = _wg->GetGameObject(guid))
                        go->SetRespawnTime(RESPAWN_ONE_DAY);
            break;
        }
        case TEAM_ALLIANCE:
        {
            if (!m_GOList[TEAM_HORDE].empty())
                for (ObjectGuid guid : m_GOList[TEAM_HORDE])
                    if (GameObject* go = _wg->GetGameObject(guid))
                        go->SetRespawnTime(RESPAWN_ONE_DAY);

            if (!m_GOList[TEAM_NEUTRAL].empty())
                for (ObjectGuid guid : m_GOList[TEAM_NEUTRAL])
                    if (GameObject* go = _wg->GetGameObject(guid))
                        go->SetRespawnTime(RESPAWN_ONE_DAY);
            break;
        }
        case TEAM_HORDE:
        {
            if (!m_GOList[TEAM_ALLIANCE].empty())
                for (ObjectGuid guid : m_GOList[TEAM_ALLIANCE])
                    if (GameObject* go = _wg->GetGameObject(guid))
                        go->SetRespawnTime(RESPAWN_ONE_DAY);

            if (!m_GOList[TEAM_NEUTRAL].empty())
                for (ObjectGuid guid : m_GOList[TEAM_NEUTRAL])
                    if (GameObject* go = _wg->GetGameObject(guid))
                        go->SetRespawnTime(RESPAWN_ONE_DAY);
            break;
        }
    }

    if (!m_GOList[_teamControl].empty())
        for (ObjectGuid guid : m_GOList[_teamControl])
            if (GameObject* go = _wg->GetGameObject(guid))
                go->SetRespawnTime(RESPAWN_IMMEDIATELY);
}

void WintergraspWorkshop::UpdateGraveyardAndWorkshop()
{
    if (_staticInfo->WorkshopId < BATTLEFIELD_WG_WORKSHOP_NE)
        GiveControlTo(_wg->GetAttackerTeam(), true);        
    else
        GiveControlTo(_wg->GetDefenderTeam(), true);
}

void WintergraspWorkshop::FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet)
{
    packet.Worldstates.emplace_back(_staticInfo->WorldStateId, _state);
}

void WintergraspWorkshop::Save()
{
    sWorld->setWorldState(_staticInfo->WorldStateId, _state);
}

class Battlefield_wintergrasp : public BattlefieldScript
{
public:
    Battlefield_wintergrasp() : BattlefieldScript("battlefield_wg") { }

    Battlefield* GetBattlefield() const override
    {
        return new BattlefieldWG();
    }
};

class npc_wg_give_promotion_credit : public CreatureScript
{
public:
    npc_wg_give_promotion_credit() : CreatureScript("npc_wg_give_promotion_credit") { }

    struct npc_wg_give_promotion_creditAI : public ScriptedAI
    {
        npc_wg_give_promotion_creditAI(Creature* creature) : ScriptedAI(creature) { }

        void JustDied(Unit* killer) override
        {
            if (!killer || killer->GetTypeId() != TYPEID_PLAYER)
                return;

            BattlefieldWG* wintergrasp = static_cast<BattlefieldWG*>(sBattlefieldMgr->GetBattlefieldByBattleId(BATTLEFIELD_BATTLEID_WG));
            if (!wintergrasp)
                return;

            wintergrasp->HandlePromotion(killer->ToPlayer(), me);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_wg_give_promotion_creditAI(creature);
    }
};

void AddSC_BF_wintergrasp() {
    new Battlefield_wintergrasp();
    new npc_wg_give_promotion_credit();
}
