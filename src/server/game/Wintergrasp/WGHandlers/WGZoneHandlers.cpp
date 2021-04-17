/*
 * Copyright (C) 2021+ ATieshCore <https://at-wow.org/>
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

#include "WintergraspMgr.h"
#include "Group.h"
#include "WGCapturePoint.h"
#include "WGGraveyard.h"
#include "ScriptedCreature.h"
#include "TemporarySummon.h"
#include "Log.h"

 // Called when a player enters the zone
void WintergraspMgr::HandlePlayerEnterZone(Player* player, uint32 /*zone*/)
{
    if (PlayerInBFPlayerMap(player))
        UpdateZoneStatusInPlayerMap(player, true);
    else
    {
        if (IsWarTime())
        {
            if (GetFreeslot(player->GetCFSTeamId()))
            {
                // low level
                if (player->GetLevel() < m_MinLevel)
                {
                    BFLeaveReason reason = BF_LEAVE_REASON_LOW_LEVEL;
                    player->GetSession()->SendBattlefieldLeaveMessage(BATTLEFIELD_WG, reason);
                    AddPlayer(player, true, false, false, true, GameTime::GetGameTime() + m_TimeForAcceptInvite);
                    return;
                }

                InviteNewPlayerToWar(player, true);
            }
            else  // no free slots for player
            {
                player->GetSession()->SendBattlefieldEjectPending(BATTLEFIELD_WG, true);
                AddPlayer(player, true, false, false, true, GameTime::GetGameTime() + m_TimeForAcceptInvite);
            }
        }
        else
        {
            if (player->GetLevel() < m_MinLevel)
                AddPlayer(player, true, false, false, false);   // we should add him in playermap, when war will start, if level will lower - will be kicked
            else
            {
                if (m_StartGrouping && GetFreeslot(player->GetCFSTeamId()))
                    InviteNewPlayerToQueue(player, true);
                else
                    AddPlayer(player, true, false, false, false);   // we should add him in playermap, when war will start, we will try to add him in war and queue (if will exist free slot)
            }
        }
    }

    OnPlayerEnterZone(player);
}

// Called when a player leave the zone
void WintergraspMgr::HandlePlayerLeaveZone(Player* player, uint32 /*zone*/)
{
    if (PlayerInBFPlayerMap(player))
    {
        UpdateZoneStatusInPlayerMap(player, false);

        if (IsWarTime())
        {
            // If the player is participating to the battle
            player->GetSession()->SendBattlefieldLeaveMessage(1);
            RemovePlayer(player);

            if (Group* group = player->GetGroup()) // Remove the player from the raid group
                group->RemoveMember(player->GetGUID());

            OnPlayerLeaveWar(player);
        }
        else
        {
            bool needtoremove = false;
            // remove player in piece time if he not in queue
            PlayerHolderContainer::const_iterator itr = m_PlayerMap.find(player->GetGUID());
            if (itr != m_PlayerMap.end())
            {
                if (!itr->second.inQueue)
                    needtoremove = true;
            }

            if (needtoremove)
                RemovePlayer(player);
        }

        for (CapturePointContainer::iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
            itr->second->HandlePlayerLeave(player);
    }

    SendRemoveWorldStates(player);
    OnPlayerLeaveZone(player);
}

// Called when a Unit is kill in battlefield zone
void WintergraspMgr::HandleKill(Player* killer, Unit* victim)
{
    if (killer == victim)
        return;

    if (victim->GetTypeId() == TYPEID_PLAYER)
    {
        HandlePromotion(killer, victim);

        // Allow to Skin non-released corpse
        victim->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE);
    }
    else if (victim->GetTypeId() == TYPEID_UNIT)
    {
        if (victim->ToCreature() && victim->ToCreature()->GetCreatureType() == CREATURE_TYPE_HUMANOID)
            HandlePromotion(killer, victim);
    }

    /// @todoRecent PvP activity worldstate
}

// Helpers section
void WintergraspMgr::OnPlayerLeaveZone(Player* player)
{
    if (!m_isActive)
        RemoveAurasFromPlayer(player);
    /*
    player->RemoveAurasDueToSpell(SPELL_HORDE_CONTROLS_FACTORY_PHASE_SHIFT);
    player->RemoveAurasDueToSpell(SPELL_ALLIANCE_CONTROLS_FACTORY_PHASE_SHIFT);
    player->RemoveAurasDueToSpell(SPELL_HORDE_CONTROL_PHASE_SHIFT);
    player->RemoveAurasDueToSpell(SPELL_ALLIANCE_CONTROL_PHASE_SHIFT);*/
}

void WintergraspMgr::OnPlayerEnterZone(Player* player)
{
    if (!m_isActive)
        RemoveAurasFromPlayer(player);

    //player->AddAura(m_DefenderTeam == TEAM_HORDE ? SPELL_HORDE_CONTROL_PHASE_SHIFT : SPELL_ALLIANCE_CONTROL_PHASE_SHIFT, player);
    // Send worldstate to player
    SendInitWorldStatesTo(player);
}

void WintergraspMgr::OnCreatureCreate(Creature* creature)
{
    // Accessing to db spawned creatures
    switch (creature->GetEntry())
    {
        case NPC_SPIRIT_HEALER:
        {
            HideNpc(creature);
            break;
        }
        case NPC_DWARVEN_SPIRIT_GUIDE:
        case NPC_TAUNKA_SPIRIT_GUIDE:
        {
            TeamId teamId = (creature->GetEntry() == NPC_DWARVEN_SPIRIT_GUIDE ? TEAM_ALLIANCE : TEAM_HORDE);
            WGGraveyardId graveyardId = GetSpiritGraveyardIdForCreature(creature);
            for (auto& graveID : m_graveyardMap)
            {
                if (graveID.first == _GetGraveyardIDByType(graveyardId))
                {
                    graveID.second->SetSpirit(creature, teamId);
                    switch (graveyardId)
                    {
                    case BATTLEFIELD_WG_GY_WORKSHOP_NE:
                        AddCreatureInHolderByGUID(creature, WG_WORKSHOP_NE, teamId);
                        creature->GetAI()->DoAction(graveID.first);
                        break;
                    case BATTLEFIELD_WG_GY_WORKSHOP_NW:
                        AddCreatureInHolderByGUID(creature, WG_WORKSHOP_NW, teamId);
                        creature->GetAI()->DoAction(graveID.first);
                        break;
                    case BATTLEFIELD_WG_GY_WORKSHOP_SE:
                        AddCreatureInHolderByGUID(creature, WG_WORKSHOP_SE, teamId);
                        creature->GetAI()->DoAction(graveID.first);
                        break;
                    case BATTLEFIELD_WG_GY_WORKSHOP_SW:
                        AddCreatureInHolderByGUID(creature, WG_WORKSHOP_SW, teamId);
                        creature->GetAI()->DoAction(graveID.first);
                        break;
                    case BATTLEFIELD_WG_GY_KEEP:
                        AddCreatureInHolderByGUID(creature, VAULT_KEEP, teamId);
                        creature->GetAI()->DoAction(graveID.first);
                        break;
                    case BATTLEFIELD_WG_GY_HORDE:
                        AddCreatureInHolderByGUID(creature, WG_HORDE_GRAVEYARD, teamId);
                        creature->GetAI()->DoAction(graveID.first);
                        break;
                    case BATTLEFIELD_WG_GY_ALLIANCE:
                        AddCreatureInHolderByGUID(creature, WG_ALLIANCE_GRAVEYARD, teamId);
                        creature->GetAI()->DoAction(graveID.first);
                        break;
                    }
                }
            }
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

            // KE workshop
            if (creature->GetScriptName() == "wg_ke_workshop_mechanic")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_KEEP_EAST, TEAM_HORDE))
                    registered = true;
            }

            // KW workshop
            if (creature->GetScriptName() == "wg_kw_workshop_mechanic")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_KEEP_WEST, TEAM_HORDE))
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

            // KE workshop
            if (creature->GetScriptName() == "wg_ke_workshop_mechanic")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_KEEP_EAST, TEAM_ALLIANCE))
                    registered = true;
            }

            // KW workshop
            if (creature->GetScriptName() == "wg_kw_workshop_mechanic")
            {
                if (AddCreatureInHolderByGUID(creature, WG_WORKSHOP_KEEP_WEST, TEAM_ALLIANCE))
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
            if (creature->GetScriptName() == "wg_ne_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, NE_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_ne_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, NE_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_nw_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, NW_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_nw_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, NW_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_se_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, SE_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_se_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, SE_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_sw_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, SW_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_sw_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, SW_TOWER_GUARD, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_vault_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, VAULT_KEEP, TEAM_ALLIANCE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_vault_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, VAULT_KEEP, TEAM_ALLIANCE))
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
            if (creature->GetScriptName() == "wg_ne_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, NE_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_ne_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, NE_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_nw_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, NW_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_nw_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, NW_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_se_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, SE_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_se_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, SE_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_sw_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, SW_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_sw_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, SW_TOWER_GUARD, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_vault_standing_guard")
            {
                if (AddCreatureInHolderByGUID(creature, VAULT_KEEP, TEAM_HORDE))
                    registered = true;
            }

            if (creature->GetScriptName() == "wg_vault_roaming_guard")
            {
                if (AddCreatureInHolderByGUID(creature, VAULT_KEEP, TEAM_HORDE))
                    registered = true;
            }

            if (!registered)
                TC_LOG_ERROR("system", "BATTLEFIELD_WG_NPC_GUARD_H not registered for GUID : %u", creature->GetSpawnId());
            break;
        }
        // Alliance keep not guard NPC
        case 15351:
        case 30488:
        case 30489:
        case 31036:
        case 31051:
        case 31052:
        case 31054:
        case 31108:
        case 31109:
        case 31153:
        case 32294:
        case 39172:
        {
            m_KeepAllianceNPCList.push_back(creature->GetGUID());
            if (GetDefenderTeam() == TEAM_HORDE)
                HideNpc(creature);
            else if (GetDefenderTeam() == TEAM_ALLIANCE)
                ShowNpc(creature, true);
            break;
        }
        // Horde keep not guard NPC
        case 15350:
        case 31053:
        case 31091:
        case 31101:
        case 31102:
        case 31106:
        case 31107:
        case 31151:
        case 32296:
        case 39173:
        {
            m_KeepHordeNPCList.push_back(creature->GetGUID());
            if (GetDefenderTeam() == TEAM_HORDE)
                ShowNpc(creature, true);
            else if (GetDefenderTeam() == TEAM_ALLIANCE)
                HideNpc(creature);
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

    creature->SetPhaseMask(1, true);
}

void WintergraspMgr::OnCreatureRemove(Creature* /*creature*/)
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

void WintergraspMgr::OnGameObjectCreate(GameObject* go)
{
    go->SetPhaseMask(1, true);
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
