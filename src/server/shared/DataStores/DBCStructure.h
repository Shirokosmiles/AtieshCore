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

#ifndef TRINITY_DBCSTRUCTURE_H
#define TRINITY_DBCSTRUCTURE_H

#include "Define.h"
#include "DBCEnums.h"
#include "SharedDefines.h"
#include "Util.h"
#include <set>
#include <map>

// Structures used to access raw DBC data require packing for portability
#pragma pack(push, 1)

struct DurabilityCostsEntry
{
    uint32 ID;                                              // 0
    uint32 WeaponSubClassCost[21];                          // 1-21
    uint32 ArmorSubClassCost[8];                            // 22-29
};

struct DurabilityQualityEntry
{
    uint32 ID;                                              // 0
    float Data;                                             // 1
};

struct EmotesEntry
{
    uint32 ID;                                              // 0
    //char const* EmoteSlashCommand;                        // 1 internal name
    //uint32 AnimID;                                        // 2 ref to animationData
    uint32 EmoteFlags;                                      // 3 bitmask, may be unit_flags
    uint32 EmoteSpecProc;                                   // 4 Can be 0, 1 or 2 (determine how emote are shown)
    uint32 EmoteSpecProcParam;                              // 5 unconfirmed, may be enum UnitStandStateType
    //uint32 EventSoundID;                                  // 6
};

struct EmotesTextEntry
{
    uint32 ID;                                              // 0
    //char const* Name;                                     // 1
    uint32 EmoteID;                                         // 2
    //uint32 EmoteText[16];                                 // 3-18
};

struct EmotesTextSoundEntry
{
    uint32 ID;                                              // 0
    uint32 EmotesTextID;                                    // 1
    uint32 RaceID;                                          // 2
    uint32 SexID;                                           // 3 0 male / 1 female
    uint32 SoundID;                                         // 4
};

struct FactionEntry
{
    uint32 ID;                                              // 0
    int32 ReputationIndex;                                  // 1
    uint32 ReputationRaceMask[4];                           // 2-5
    uint32 ReputationClassMask[4];                          // 6-9
    int32 ReputationBase[4];                                // 10-13
    uint32 ReputationFlags[4];                              // 14-17
    uint32 ParentFactionID;                                 // 18
    float ParentFactionMod[2];                              // 19-20 [0] Faction gains incoming rep * spilloverRateIn
                                                            //       [1] Faction outputs rep * spilloverRateOut as spillover reputation
    uint32 ParentFactionCap[2];                             // 21-22 [0] The highest rank the faction will profit from incoming spillover
                                                            //       [1] It does not seem to be the max standing at which a faction outputs spillover ...so no idea
    char const* Name[16];                                   // 23-38
    //uint32 Name_lang_mask;                                // 39
    //char const* Description[16];                          // 40-55
    //uint32 Description_lang_mask;                         // 56

    // helpers
    bool CanHaveReputation() const
    {
        return ReputationIndex >= 0;
    }
};

#define MAX_FACTION_RELATIONS 4

struct FactionTemplateEntry
{
    uint32 ID;                                              // 0
    uint32 Faction;                                         // 1
    uint32 Flags;                                           // 2
    uint32 FactionGroup;                                    // 3
    uint32 FriendGroup;                                     // 4
    uint32 EnemyGroup;                                      // 5
    uint32 Enemies[MAX_FACTION_RELATIONS];                  // 6-9
    uint32 Friend[MAX_FACTION_RELATIONS];                   // 10-13

    // helpers
    bool IsFriendlyTo(FactionTemplateEntry const& entry) const
    {
        if (entry.Faction)
        {
            for (int i = 0; i < MAX_FACTION_RELATIONS; ++i)
                if (Enemies[i] == entry.Faction)
                    return false;
            for (int i = 0; i < MAX_FACTION_RELATIONS; ++i)
                if (Friend[i] == entry.Faction)
                    return true;
        }
        return (FriendGroup & entry.FactionGroup) || (FactionGroup & entry.FriendGroup);
    }
    bool IsHostileTo(FactionTemplateEntry const& entry) const
    {
        if (entry.Faction)
        {
            for (int i = 0; i < MAX_FACTION_RELATIONS; ++i)
                if (Enemies[i] == entry.Faction)
                    return true;
            for (int i = 0; i < MAX_FACTION_RELATIONS; ++i)
                if (Friend[i] == entry.Faction)
                    return false;
        }
        return (EnemyGroup & entry.FactionGroup) != 0;
    }
    bool IsHostileToPlayers() const { return (EnemyGroup & FACTION_MASK_PLAYER) !=0; }
    bool IsNeutralToAll() const
    {
        for (int i = 0; i < MAX_FACTION_RELATIONS; ++i)
            if (Enemies[i] != 0)
                return false;
        return EnemyGroup == 0 && FriendGroup == 0;
    }
    bool IsContestedGuardFaction() const { return (Flags & FACTION_TEMPLATE_FLAG_CONTESTED_GUARD) != 0; }
};

struct GameObjectArtKitEntry
{
    uint32 ID;                                              // 0
    //char const* TextureVariation[3]                       // 1-3 m_textureVariations[3]
    //char const* AttachModel[4]                            // 4-8 m_attachModels[4]
};

struct GameObjectDisplayInfoEntry
{
    uint32 ID;                                              // 0
    char const* ModelName;                                  // 1
    //uint32 Sound[10];                                     // 2-11
    DBCPosition3D GeoBoxMin;                                // 12-14
    DBCPosition3D GeoBoxMax;                                // 15-17
    //uint32 ObjectEffectPackageID;                         // 18
};

struct GemPropertiesEntry
{
    uint32 ID;                                              // 0
    uint32 EnchantID;                                       // 1
    //uint32 MaxCountInv;                                   // 2
    //uint32 MaxCountItem;                                  // 3
    uint32 Type;                                            // 4
};

struct GlyphPropertiesEntry
{
    uint32 ID;                                              // 0
    uint32 SpellID;                                         // 1
    uint32 GlyphSlotFlags;                                  // 2
    uint32 SpellIconID;                                     // 3
};

struct GlyphSlotEntry
{
    uint32 ID;                                              // 0
    uint32 Type;                                            // 1
    uint32 Tooltip;                                         // 2
};

// All Gt* DBC store data for 100 levels, some by 100 per class/race
#define GT_MAX_LEVEL    100
// gtOCTClassCombatRatingScalar.dbc stores data for 32 ratings, look at MAX_COMBAT_RATING for real used amount
#define GT_MAX_RATING   32

struct GtBarberShopCostBaseEntry
{
    float Data;                                             // 0
};

struct GtCombatRatingsEntry
{
    float Data;                                             // 0
};

struct GtChanceToMeleeCritBaseEntry
{
    float Data;                                             // 0
};

struct GtChanceToMeleeCritEntry
{
    float Data;                                             // 0
};

struct GtChanceToSpellCritBaseEntry
{
    float Data;                                             // 0
};

struct GtNPCManaCostScalerEntry
{
    float Data;                                             // 0
};

struct GtChanceToSpellCritEntry
{
    float Data;                                             // 0
};

struct GtOCTClassCombatRatingScalarEntry
{
    float Data;                                             // 0
};

struct GtOCTRegenHPEntry
{
    float Data;                                             // 0
};

/*
struct GtOCTRegenMPEntry
{
    float Data;                                             // 0
};
*/

struct GtRegenHPPerSptEntry
{
    float Data;                                             // 0
};

struct GtRegenMPPerSptEntry
{
    float Data;                                             // 0
};

/*
struct HolidayDescriptionsEntry
{
    uint32 ID;                                              // 0
    char const* Description[16];                            // 1-16
    uint32 Description_lang_mask;                           // 17
};
*/

/*
struct HolidayNamesEntry
{
    uint32 ID;                                              // 0
    char const* Name[16];                                   // 1-16
    uint32 Name_lang_mask;                                  // 17
};
*/

#define MAX_HOLIDAY_DURATIONS 10
#define MAX_HOLIDAY_DATES 26
#define MAX_HOLIDAY_FLAGS 10

struct HolidaysEntry
{
    uint32 ID;                                              // 0
    uint32 Duration[MAX_HOLIDAY_DURATIONS];                 // 1-10
    uint32 Date[MAX_HOLIDAY_DATES];                         // 11-36 dates in unix time starting at January, 1, 2000
    uint32 Region;                                          // 37 WoW region
    uint32 Looping;                                         // 38
    uint32 CalendarFlags[MAX_HOLIDAY_FLAGS];                // 39-48
    //uint32 HolidayNameID;                                 // 49 HolidayNames.dbc
    //uint32 HolidayDescriptionID;                          // 50 HolidayDescriptions.dbc
    char const* TextureFilename;                            // 51
    uint32 Priority;                                        // 52
    int32 CalendarFilterType;                               // 53
    //uint32 Flags;                                         // 54 0 = Darkmoon Faire, Fishing Contest and Wotlk Launch, rest is 1
};

struct ItemEntry
{
   uint32 ID;                                               // 0
   uint32 ClassID;                                          // 1
   uint32 SubclassID;                                       // 2
   int32 SoundOverrideSubclassID;                           // 3
   int32 Material;                                          // 4
   uint32 DisplayInfoID;                                    // 5
   uint32 InventoryType;                                    // 6
   uint32 SheatheType;                                      // 7
};

struct ItemBagFamilyEntry
{
    uint32 ID;                                              // 0
    //char const* Name[16];                                 // 1-16
    //uint32 Name_lang_mask;                                // 17
};

struct ItemDisplayInfoEntry
{
    uint32 ID;                                              // 0
    char const* ModelName[2];                               // 1-2
    char const* ModelTexture[2];                            // 3-4
    char const* InventoryIcon[2];                           // 5-6
    uint32 GeosetGroup[3];                                  // 7-9
    uint32 Flags;                                           // 10
    uint32 SpellVisualID;                                   // 11
    uint32 GroupSoundIndex;                                 // 12
    uint32 HelmetGeosetVisID[2];                            // 13-14
    char const* Texture[8];                                 // 15-22
    int32 ItemVisual;                                       // 23
    uint32 ParticleColorID;                                 // 24
};

/*
struct ItemCondExtCostsEntry
{
    uint32 ID;                                              // 0
    uint32 CondExtendedCost;                                // 1 ItemTemplate::CondExtendedCost
    uint32 ItemExtendedCostEntry;                           // 2 ItemTemplate::ExtendedCost
    uint32 ArenaSeason;                                     // 3 arena season number (1-4)
};
*/

#define MAX_ITEM_EXTENDED_COST_REQUIREMENTS 5

struct ItemExtendedCostEntry
{
    uint32 ID;                                              // 0
    uint32 HonorPoints;                                     // 1 required honor points
    uint32 ArenaPoints;                                     // 2 required arena points
    uint32 ArenaBracket;                                    // 3 arena slot restrictions (min slot value)
    uint32 ItemID[MAX_ITEM_EXTENDED_COST_REQUIREMENTS];     // 4-8 required item id
    uint32 ItemCount[MAX_ITEM_EXTENDED_COST_REQUIREMENTS];  // 9-13 required count of item
    uint32 RequiredArenaRating;                             // 14 required personal arena rating
    //uint32 ItemPurchaseGroup;                             // 15
};

struct ItemLimitCategoryEntry
{
    uint32 ID;                                              // 0
    //char const* Name[16]                                  // 1-16
    //uint32 Name_lang_mask;                                // 17
    uint32 Quantity;                                        // 18 max allowed equipped as item or in gem slot
    uint32 Flags;                                           // 19 enum ItemLimitCategoryMode
};

#define MAX_ITEM_ENCHANTMENT_EFFECTS 3

struct ItemRandomPropertiesEntry
{
    uint32 ID;                                                          // 0
    //char const* InternalName;                                         // 1
    std::array<uint32, MAX_ITEM_ENCHANTMENT_EFFECTS> Enchantment;       // 2-4
    //std::array<uint32, 2> UnusedEnchantment;                          // 5-6
    std::array<char const*, 16> Name;                                   // 7-22
    //uint32 Name_lang_mask;                                            // 23
};

struct ItemRandomSuffixEntry
{
    uint32 ID;                                                          // 0
    std::array<char const*, 16> Name;                                   // 1-16
    //uint32 Name_lang_mask;                                            // 17
    //char const* InternalName;                                         // 18
    std::array<uint32, MAX_ITEM_ENCHANTMENT_EFFECTS> Enchantment;       // 19-21
    //std::array<uint32, 2> UnusedEnchantment;                          // 22-23
    std::array<uint32, MAX_ITEM_ENCHANTMENT_EFFECTS> AllocationPct;     // 24-26
    //std::array<uint32, 2> UnusedAllocationPct;                        // 27-28
};

#define MAX_ITEM_SET_ITEMS 10
#define MAX_ITEM_SET_SPELLS 8

struct ItemSetEntry
{
    //uint32 ID;                                            // 0
    char const* Name[16];                                   // 1-16
    //uint32 Name_lang_mask;                                // 17
    uint32 ItemID[MAX_ITEM_SET_ITEMS];                      // 18-27
    //uint32 UnusedItemID[7];                               // 28-34
    uint32 SetSpellID[MAX_ITEM_SET_SPELLS];                 // 35-42
    uint32 SetThreshold[MAX_ITEM_SET_SPELLS];               // 43-50
    uint32 RequiredSkill;                                   // 51
    uint32 RequiredSkillRank;                               // 52
};

struct LFGDungeonEntry
{
    uint32 ID;                                              // 0
    char const* Name[16];                                   // 1-16
    //uint32 Name_lang_mask;                                // 17
    uint32 MinLevel;                                        // 18
    uint32 MaxLevel;                                        // 19
    uint32 TargetLevel;                                     // 20
    uint32 TargetLevelMin;                                  // 21
    uint32 TargetLevelMax;                                  // 22
    int32 MapID;                                            // 23
    uint32 Difficulty;                                      // 24
    uint32 Flags;                                           // 25
    uint32 TypeID;                                          // 26
    //int32 Faction;                                        // 27
    //char const* TextureFilename;                          // 28
    uint32 ExpansionLevel;                                  // 29
    //uint32 OrderIndex;                                    // 30
    uint32 GroupID;                                         // 31
    //char const* Description[16];                          // 32-47
    //uint32 Description_lang_mask;                         // 48

    // Helpers
    uint32 Entry() const { return ID + (TypeID << 24); }
};

struct LightEntry
{
    uint32 ID;                                              // 0
    uint32 ContinentID;                                     // 1
    DBCPosition3D GameCoords;                               // 2-4
    //float GameFalloffStart;                               // 5
    //float GameFalloffEnd;                                 // 6
    //uint32 LightParamsID[8];                              // 7-14
};

struct LiquidTypeEntry
{
    uint32 ID;                                              // 0
    //char const* Name;                                     // 1
    //uint32 Flags;                                         // 2
    uint32 SoundBank;                                       // 3
    //uint32 SoundID;                                       // 4
    uint32 SpellID;                                         // 5
    //float MaxDarkenDepth;                                 // 6
    //float FogDarkenIntensity;                             // 7
    //float AmbDarkenIntensity;                             // 8
    //float DirDarkenIntensity;                             // 9
    //uint32 LightID;                                       // 10
    //float ParticleScale;                                  // 11
    //uint32 ParticleMovement;                              // 12
    //uint32 ParticleTexSlots;                              // 13
    //uint32 MaterialID;                                    // 14
    //char const* Texture[6];                               // 15-20
    //uint32 Color[2];                                      // 21-22
    //float Unk1[18];                                       // 23-40
    //uint32 Unk2[4];                                       // 41-44
};

#define MAX_LOCK_CASE 8

struct LockEntry
{
    uint32 ID;                                              // 0
    uint32 Type[MAX_LOCK_CASE];                             // 1-8
    uint32 Index[MAX_LOCK_CASE];                            // 9-16
    uint32 Skill[MAX_LOCK_CASE];                            // 17-24
    //uint32 Action[MAX_LOCK_CASE];                         // 25-32
};

struct MailTemplateEntry
{
    uint32 ID;                                              // 0
    //char const* Subject[16];                              // 1-16
    //uint32 Subject_lang_mask;                             // 17
    char const* Body[16];                                   // 18-33
    //uint32 Body_lang_mask;                                // 34
};

struct MapEntry
{
    uint32 ID;                                              // 0
    //char const* Directory;                                // 1
    uint32 InstanceType;                                    // 2
    uint32 Flags;                                           // 3
    //uint32 MapType;                                       // 4 0 or 1 for battlegrounds (not arenas)
    char const* MapName[16];                                // 5-20
    //uint32 MapName_lang_mask;                             // 21
    uint32 AreaTableID;                                     // 22 common zone for instance and continent map
    //char const* MapDescription0[16];                      // 23-38 text for PvP Zones (Horde)
    //uint32 MapDescription0_lang_mask;                     // 39
    //char const* MapDescription1[16];                      // 40-55 text for PvP Zones (Alliance)
    //uint32 MapDescription1_lang_mask;                     // 56
    uint32 LoadingScreenID;                                 // 57
    //float MinimapIconScale;                               // 58
    int32 CorpseMapID;                                      // 59 MapID of entrance map
    DBCPosition2D Corpse;                                   // 60-61 entrance coordinate (if exist single entry)
    //uint32 TimeOfDayOverride;                             // 62 -1, 0 and 720
    uint32 ExpansionID;                                     // 63
    uint32 RaidOffset;                                      // 64
    uint32 MaxPlayers;                                      // 65 max players, fallback if not present in MapDifficulty.dbc

    // Helpers
    uint32 Expansion() const { return ExpansionID; }

    bool IsDungeon() const { return InstanceType == MAP_INSTANCE || InstanceType == MAP_RAID; }
    bool IsNonRaidDungeon() const { return InstanceType == MAP_INSTANCE; }
    bool Instanceable() const { return InstanceType == MAP_INSTANCE || InstanceType == MAP_RAID || InstanceType == MAP_BATTLEGROUND || InstanceType == MAP_ARENA; }
    bool IsRaid() const { return InstanceType == MAP_RAID; }
    bool IsBattleground() const { return InstanceType == MAP_BATTLEGROUND; }
    bool IsBattleArena() const { return InstanceType == MAP_ARENA; }
    bool IsBattlegroundOrArena() const { return InstanceType == MAP_BATTLEGROUND || InstanceType == MAP_ARENA; }
    bool IsWorldMap() const { return InstanceType == MAP_COMMON; }

    bool GetEntrancePos(int32 &mapid, float &x, float &y) const
    {
        if (CorpseMapID < 0)
            return false;
        mapid = CorpseMapID;
        x = Corpse.X;
        y = Corpse.Y;
        return true;
    }

    bool IsContinent() const
    {
        return ID == 0 || ID == 1 || ID == 530 || ID == 571;
    }

    bool IsDynamicDifficultyMap() const { return (Flags & MAP_FLAG_DYNAMIC_DIFFICULTY) != 0; }
};

struct MapDifficultyEntry
{
    //uint32 ID;                                            // 0
    uint32 MapID;                                           // 1
    uint32 Difficulty;                                      // 2 (for arenas: arena slot)
    char const* Message;                                    // 3-18 text showed when transfer to map failed (missing requirements)
    //uint32 Message_lang_mask;                             // 19
    uint32 RaidDuration;                                    // 20
    uint32 MaxPlayers;                                      // 21
    //char const* Difficultystring;                         // 22
};

struct MovieEntry
{
    uint32 ID;                                              // 0
    //char const* Filename;                                 // 1
    //uint32 Volume;                                        // 2 always 100
};

struct NamesProfanityEntry
{
    //uint32 ID;                                            // 0
    char const* Name;                                       // 1
    int32 Language;                                         // 2
};

struct NamesReservedEntry
{
    //uint32 ID;                                            // 0
    char const* Name;                                       // 1
    int32 Language;                                         // 2
};

#define MAX_OVERRIDE_SPELL 10

struct OverrideSpellDataEntry
{
    uint32 ID;                                              // 0
    uint32 Spells[MAX_OVERRIDE_SPELL];                      // 1-10
    //uint32 Flags;                                         // 11
};

struct PowerDisplayEntry
{
    uint32 ID;                                              // 0
    uint32 ActualType;                                      // 1
    //char const* GlobalStringBaseTag;                      // 2
    //uint8 Red;                                            // 3
    //uint8 Green;                                          // 4
    //uint8 Blue;                                           // 5
};

struct PvPDifficultyEntry
{
    //uint32 ID;                                            // 0
    uint32 MapID;                                           // 1
    uint32 RangeIndex;                                      // 2
    uint32 MinLevel;                                        // 3
    uint32 MaxLevel;                                        // 4
    uint32 Difficulty;                                      // 5

    // helpers
    BattlegroundBracketId GetBracketId() const { return BattlegroundBracketId(RangeIndex); }
};

struct QuestSortEntry
{
    uint32 ID;                                              // 0
    //char const* SortName[16];                             // 1-16
    //uint32 SortName_lang;                                 // 17
};

struct QuestXPEntry
{
    uint32 ID;                                              // 0
    uint32 Difficulty[10];                                  // 1-10
};

struct QuestFactionRewEntry
{
    uint32 ID;                                              // 0
    int32 Difficulty[10];                                   // 1
};

struct RandPropPointsEntry
{
    uint32 ID;                                              // 0 item level
    uint32 Epic[5];                                         // 1-5
    uint32 Superior[5];                                     // 6-10
    uint32 Good[5];                                         // 11-15
};

struct ScalingStatDistributionEntry
{
    uint32 ID;                                              // 0
    int32 StatID[10];                                       // 1-10
    uint32 Bonus[10];                                       // 11-20
    uint32 Maxlevel;                                        // 21
};

struct ScalingStatValuesEntry
{
    uint32 ID;                                              // 0
    uint32 Charlevel;                                       // 1
    uint32 ShoulderBudget;                                  // 2
    uint32 TrinketBudget;                                   // 3
    uint32 WeaponBudget1H;                                  // 4
    uint32 RangedBudget;                                    // 5
    uint32 ClothShoulderArmor;                              // 6
    uint32 LeatherShoulderArmor;                            // 7
    uint32 MailShoulderArmor;                               // 8
    uint32 PlateShoulderArmor;                              // 9
    uint32 WeaponDPS1H;                                     // 10
    uint32 WeaponDPS2H;                                     // 11
    uint32 SpellcasterDPS1H;                                // 12
    uint32 SpellcasterDPS2H;                                // 13
    uint32 RangedDPS;                                       // 14
    uint32 WandDPS;                                         // 15
    uint32 SpellPower;                                      // 16
    uint32 PrimaryBudget;                                   // 17
    uint32 TertiaryBudget;                                  // 18
    uint32 ClothCloakArmor;                                 // 19
    uint32 ClothChestArmor;                                 // 20
    uint32 LeatherChestArmor;                               // 21
    uint32 MailChestArmor;                                  // 22
    uint32 PlateChestArmor;                                 // 23

    uint32 getssdMultiplier(uint32 mask) const
    {
        if (mask & 0x4001F)
        {
            if (mask & 0x00000001) return ShoulderBudget;
            if (mask & 0x00000002) return TrinketBudget;
            if (mask & 0x00000004) return WeaponBudget1H;
            if (mask & 0x00000008) return PrimaryBudget;
            if (mask & 0x00000010) return RangedBudget;
            if (mask & 0x00040000) return TertiaryBudget;
        }
        return 0;
    }

    uint32 getArmorMod(uint32 mask) const
    {
        if (mask & 0x00F001E0)
        {
            if (mask & 0x00000020) return ClothShoulderArmor;
            if (mask & 0x00000040) return LeatherShoulderArmor;
            if (mask & 0x00000080) return MailShoulderArmor;
            if (mask & 0x00000100) return PlateShoulderArmor;

            if (mask & 0x00080000) return ClothCloakArmor;
            if (mask & 0x00100000) return ClothChestArmor;
            if (mask & 0x00200000) return LeatherChestArmor;
            if (mask & 0x00400000) return MailChestArmor;
            if (mask & 0x00800000) return PlateChestArmor;
        }
        return 0;
    }

    uint32 getDPSMod(uint32 mask) const
    {
        if (mask & 0x7E00)
        {
            if (mask & 0x00000200) return WeaponDPS1H;
            if (mask & 0x00000400) return WeaponDPS2H;
            if (mask & 0x00000800) return SpellcasterDPS1H;
            if (mask & 0x00001000) return SpellcasterDPS2H;
            if (mask & 0x00002000) return RangedDPS;
            if (mask & 0x00004000) return WandDPS;
        }
        return 0;
    }

    uint32 getSpellBonus(uint32 mask) const
    {
        if (mask & 0x00008000) return SpellPower;
        return 0;
    }

    uint32 getFeralBonus(uint32 /*mask*/) const                 // removed in 3.2.x?
    {
        //if (mask & 0x00010000) return 0;                  // not used?
        return 0;
    }
};

struct SkillLineEntry
{
    uint32 ID;                                              // 0
    int32 CategoryID;                                       // 1
    //uint32 SkillCostsID;                                  // 2
    char const* DisplayName[16];                            // 3-18
    //uint32 DisplayName_lang_mask;                         // 19
    //char const* Description[16];                          // 20-35
    //uint32 Description_lang_mask;                         // 36
    uint32 SpellIconID;                                     // 37
    //char const* AlternateVerb[16];                        // 38-53
    //uint32 AlternateVerb_lang_mask;                       // 54
    uint32 CanLink;                                         // 55
};

struct SkillLineAbilityEntry
{
    uint32 ID;                                              // 0
    uint32 SkillLine;                                       // 1
    uint32 Spell;                                           // 2
    uint32 RaceMask;                                        // 3
    uint32 ClassMask;                                       // 4
    //uint32 ExcludeRace;                                   // 5
    //uint32 ExcludeClass;                                  // 6
    uint32 MinSkillLineRank;                                // 7
    uint32 SupercededBySpell;                               // 8
    uint32 AcquireMethod;                                   // 9
    uint32 TrivialSkillLineRankHigh;                        // 10
    uint32 TrivialSkillLineRankLow;                         // 11
    //uint32 CharacterPoints[2];                            // 12-13
};

/*
struct SkillLineCategoryEntry
{
    uint32 ID;                                              // 0
    char const* Name[16];                                   // 1-17
    uint32 Name_lang_mask;                                  // 18
    uint32 SortIndex;                                       // 19
};
*/

struct SkillRaceClassInfoEntry
{
    //uint32 ID;                                            // 0
    uint32 SkillID;                                         // 1
    uint32 RaceMask;                                        // 2
    uint32 ClassMask;                                       // 3
    uint32 Flags;                                           // 4
    //uint32 MinLevel;                                      // 5
    uint32 SkillTierID;                                     // 6
    //uint32 SkillCostIndex;                                // 7
};

#define MAX_SKILL_STEP 16

struct SkillTiersEntry
{
    uint32 ID;                                              // 0
    //uint32 Cost[MAX_SKILL_STEP];                          // 1-16
    uint32 Value[MAX_SKILL_STEP];                           // 17-32
};

struct SoundEntriesEntry
{
    uint32 ID;                                              // 0
    //uint32 SoundType;                                     // 1
    //char const* Name;                                     // 2
    //char const* File[10];                                 // 3-12
    //uint32 Freq[10];                                      // 13-22
    //char const* DirectoryBase;                            // 23
    //float VolumeFloat;                                    // 24
    //uint32 Flags;                                         // 25
    //float MinDistance;                                    // 26
    //float DistanceCutoff;                                 // 27
    //uint32 EAXDef;                                        // 28
    //uint32 SoundEntriesAdvancedID;                        // 29
};

struct SpellEntry
{
    uint32 ID;                                                          // 0
    uint32 Category;                                                    // 1
    uint32 DispelType;                                                  // 2
    uint32 Mechanic;                                                    // 3
    uint32 Attributes;                                                  // 4
    uint32 AttributesEx;                                                // 5
    uint32 AttributesExB;                                               // 6
    uint32 AttributesExC;                                               // 7
    uint32 AttributesExD;                                               // 8
    uint32 AttributesExE;                                               // 9
    uint32 AttributesExF;                                               // 10
    uint32 AttributesExG;                                               // 11
    std::array<uint32, 2> ShapeshiftMask;                               // 12-13
    std::array<uint32, 2> ShapeshiftExclude;                            // 14-15
    uint32 Targets;                                                     // 16
    uint32 TargetCreatureType;                                          // 17
    uint32 RequiresSpellFocus;                                          // 18
    uint32 FacingCasterFlags;                                           // 19
    uint32 CasterAuraState;                                             // 20
    uint32 TargetAuraState;                                             // 21
    uint32 ExcludeCasterAuraState;                                      // 22
    uint32 ExcludeTargetAuraState;                                      // 23
    uint32 CasterAuraSpell;                                             // 24
    uint32 TargetAuraSpell;                                             // 25
    uint32 ExcludeCasterAuraSpell;                                      // 26
    uint32 ExcludeTargetAuraSpell;                                      // 27
    uint32 CastingTimeIndex;                                            // 28
    uint32 RecoveryTime;                                                // 29
    uint32 CategoryRecoveryTime;                                        // 30
    uint32 InterruptFlags;                                              // 31
    uint32 AuraInterruptFlags;                                          // 32
    uint32 ChannelInterruptFlags;                                       // 33
    uint32 ProcTypeMask;                                                // 34
    uint32 ProcChance;                                                  // 35
    uint32 ProcCharges;                                                 // 36
    uint32 MaxLevel;                                                    // 37
    uint32 BaseLevel;                                                   // 38
    uint32 SpellLevel;                                                  // 39
    uint32 DurationIndex;                                               // 40
    uint32 PowerType;                                                   // 41
    uint32 ManaCost;                                                    // 42
    uint32 ManaCostPerLevel;                                            // 43
    uint32 ManaPerSecond;                                               // 44
    uint32 ManaPerSecondPerLevel;                                       // 45
    uint32 RangeIndex;                                                  // 46
    float Speed;                                                        // 47
    //uint32 ModalNextSpell;                                            // 48
    uint32 CumulativeAura;                                              // 49
    std::array<uint32, 2> Totem;                                        // 50-51
    std::array<int32, MAX_SPELL_REAGENTS> Reagent;                      // 52-59
    std::array<uint32, MAX_SPELL_REAGENTS> ReagentCount;                // 60-67
    int32 EquippedItemClass;                                            // 68
    int32 EquippedItemSubclass;                                         // 69
    int32 EquippedItemInvTypes;                                         // 70
    std::array<uint32, MAX_SPELL_EFFECTS> Effect;                       // 71-73
    std::array<int32, MAX_SPELL_EFFECTS> EffectDieSides;                // 74-76
    std::array<float, MAX_SPELL_EFFECTS> EffectRealPointsPerLevel;      // 77-79
    std::array<int32, MAX_SPELL_EFFECTS> EffectBasePoints;              // 80-82
    std::array<uint32, MAX_SPELL_EFFECTS> EffectMechanic;               // 83-85
    std::array<uint32, MAX_SPELL_EFFECTS> EffectImplicitTargetA;        // 86-88
    std::array<uint32, MAX_SPELL_EFFECTS> EffectImplicitTargetB;        // 89-91
    std::array<uint32, MAX_SPELL_EFFECTS> EffectRadiusIndex;            // 92-94
    std::array<uint32, MAX_SPELL_EFFECTS> EffectAura;                   // 95-97
    std::array<uint32, MAX_SPELL_EFFECTS> EffectAuraPeriod;             // 98-100
    std::array<float, MAX_SPELL_EFFECTS> EffectAmplitude;               // 101-103
    std::array<uint32, MAX_SPELL_EFFECTS> EffectChainTargets;           // 104-106
    std::array<uint32, MAX_SPELL_EFFECTS> EffectItemType;               // 107-109
    std::array<int32, MAX_SPELL_EFFECTS> EffectMiscValue;               // 110-112
    std::array<int32, MAX_SPELL_EFFECTS> EffectMiscValueB;              // 113-115
    std::array<uint32, MAX_SPELL_EFFECTS> EffectTriggerSpell;           // 116-118
    std::array<float, MAX_SPELL_EFFECTS> EffectPointsPerCombo;          // 119-121
    std::array<flag96, MAX_SPELL_EFFECTS> EffectSpellClassMask;         // 122-130
    std::array<uint32, 2> SpellVisualID;                                // 131-132
    uint32 SpellIconID;                                                 // 133
    uint32 ActiveIconID;                                                // 134
    uint32 SpellPriority;                                               // 135
    std::array<char const*, 16> Name;                                   // 136-151
    //uint32 Name_lang_mask;                                            // 152
    std::array<char const*, 16> NameSubtext;                            // 153-168
    //uint32 NameSubtext_lang_mask;                                     // 169
    //std::array<char const*, 16> Description;                          // 170-185
    //uint32 Description_lang_mask;                                     // 186
    //std::array<char const*, 16> AuraDescription;                      // 187-202
    //uint32 AuraDescription_lang_mask;                                 // 203
    uint32 ManaCostPct;                                                 // 204
    uint32 StartRecoveryCategory;                                       // 205
    uint32 StartRecoveryTime;                                           // 206
    uint32 MaxTargetLevel;                                              // 207
    uint32 SpellClassSet;                                               // 208
    flag96 SpellClassMask;                                              // 209-211
    uint32 MaxTargets;                                                  // 212
    uint32 DefenseType;                                                 // 213
    uint32 PreventionType;                                              // 214
    //uint32 StanceBarOrder;                                            // 215
    std::array<float, MAX_SPELL_EFFECTS> EffectChainAmplitude;          // 216-218
    //uint32 MinFactionID;                                              // 219
    //uint32 MinReputation;                                             // 220
    //uint32 RequiredAuraVision;                                        // 221
    std::array<uint32, 2> RequiredTotemCategoryID;                      // 222-223
    int32 RequiredAreasID;                                              // 224
    uint32 SchoolMask;                                                  // 225
    uint32 RuneCostID;                                                  // 226
    //uint32 SpellMissileID;                                            // 227
    //uint32 PowerDisplayID;                                            // 228
    std::array<float, MAX_SPELL_EFFECTS> EffectBonusCoefficient;        // 229-231
    //uint32 DescriptionVariablesID;                                    // 232
    //uint32 Difficulty;                                                // 233
};

typedef std::set<uint32> PetFamilySpellsSet;
typedef std::map<uint32, PetFamilySpellsSet> PetFamilySpellsStore;

struct SpellCastTimesEntry
{
    uint32 ID;                                              // 0
    int32 Base;                                             // 1
    //int32 PerLevel;                                       // 2
    //int32 Minimum;                                        // 3
};

struct SpellCategoryEntry
{
    uint32 ID;                                              // 0
    uint32 Flags;                                           // 1
};

struct SpellDifficultyEntry
{
    uint32 ID;                                              // 0
    int32 DifficultySpellID[MAX_DIFFICULTY];                // 1-4 instance modes: 10N, 25N, 10H, 25H or Normal/Heroic if only 1-2 is set, if 3-4 is 0 then Mode-2
};

struct SpellDurationEntry
{
    uint32 ID;                                              // 0
    int32 Duration;                                         // 1
    int32 DurationPerLevel;                                 // 2
    int32 MaxDuration;                                      // 3
};

struct SpellFocusObjectEntry
{
    uint32 ID;                                              // 0
    //char const* Name[16];                                 // 1-15
    //uint32 Name_lang_mask;                                // 16
};

struct SpellItemEnchantmentEntry
{
    uint32 ID;                                              // 0
    //uint32 Charges;                                       // 1
    uint32 Effect[MAX_ITEM_ENCHANTMENT_EFFECTS];            // 2-4
    uint32 EffectPointsMin[MAX_ITEM_ENCHANTMENT_EFFECTS];   // 5-7
    //uint32 EffectPointsMax[MAX_ITEM_ENCHANTMENT_EFFECTS]  // 8-10
    uint32 EffectArg[MAX_ITEM_ENCHANTMENT_EFFECTS];         // 11-13
    char const* Name[16];                                   // 14-29
    //uint32 Name_lang_mask;                                // 30
    uint32 ItemVisual;                                      // 31
    uint32 Flags;                                           // 32
    uint32 SrcItemID;                                       // 33
    uint32 ConditionID;                                     // 34
    uint32 RequiredSkillID;                                 // 35
    uint32 RequiredSkillRank;                               // 36
    uint32 MinLevel;                                        // 37
};

struct SpellItemEnchantmentConditionEntry
{
    uint32 ID;                                              // 0
    uint8 LtOperandType[5];                                 // 1-5
    //uint32 LtOperand[5];                                  // 6-10
    uint8 Operator[5];                                      // 11-15
    uint8 RtOperandType[5];                                 // 15-20
    uint32 RtOperand[5];                                    // 21-25
    //uint8 Logic[5];                                       // 25-30
};

struct SpellRadiusEntry
{
    uint32 ID;                                              // 0
    float Radius;                                           // 1
    float RadiusPerLevel;                                   // 2
    float RadiusMax;                                        // 3
};

struct SpellRangeEntry
{
    uint32 ID;                                              // 0
    float RangeMin[2];                                      // 1-2 [0] Hostile [1] Friendly
    float RangeMax[2];                                      // 3-4 [0] Hostile [1] Friendly
    uint32 Flags;                                           // 5
    //char const* DisplayName[16];                          // 6-21
    //uint32 DisplayName_lang_mask;                         // 22
    //char const* DisplayNameShort[16];                     // 23-38
    //uint32 DisplayNameShort_lang_mask;                    // 39
};

struct SpellRuneCostEntry
{
    uint32 ID;                                              // 0
    uint32 RuneCost[3];                                     // 1-3 [0] Blood [1] Unholy [2] Frost
    uint32 RunicPower;                                      // 4

    bool NoRuneCost() const { return RuneCost[0] == 0 && RuneCost[1] == 0 && RuneCost[2] == 0; }
    bool NoRunicPowerGain() const { return RunicPower == 0; }
};

#define MAX_SHAPESHIFT_SPELLS 8

struct SpellShapeshiftFormEntry
{
    uint32 ID;                                              // 0
    //uint32 BonusActionBar;                                // 1
    //char const* Name[16];                                 // 2-17
    //uint32 Name_lang_mask;                                // 18
    uint32 Flags;                                           // 19
    int32 CreatureType;                                     // 20 <= 0 humanoid, other normal creature types
    //uint32 AttackIconID;                                  // 21
    uint32 CombatRoundTime;                                 // 22
    uint32 CreatureDisplayID[4];                            // 23-26 [0] Alliance [1] Horde [2] Unk [3] Unk
    uint32 PresetSpellID[MAX_SHAPESHIFT_SPELLS];            // 27-34
};

struct SpellVisualEntry
{
    //uint32 ID;                                            // 0
    //uint32 PrecastKit;                                    // 1
    //uint32 CastKit;                                       // 2
    //uint32 ImpactKit;                                     // 3
    //uint32 StateKit;                                      // 4
    //uint32 StateDoneKit;                                  // 5
    //uint32 ChannelKit;                                    // 6
    uint32 HasMissile;                                      // 7
    int32 MissileModel;                                     // 8
    //uint32 MissilePathType;                               // 9
    //uint32 MissileDestinationAttachment;                  // 10
    //uint32 MissileSound;                                  // 11
    //uint32 AnimEventSoundID;                              // 12
    //uint32 Flags;                                         // 13
    //uint32 CasterImpactKit;                               // 14
    //uint32 TargetImpactKit;                               // 15
    //int32 MissileAttachment;                              // 16
    //uint32 MissileFollowGroundHeight;                     // 17
    //uint32 MissileFollowGroundDropSpeed;                  // 18
    //uint32 MissileFollowGroundApproach;                   // 19
    //uint32 MissileFollowGroundFlags;                      // 20
    //uint32 MissileMotion;                                 // 21
    //uint32 MissileTargetingKit;                           // 22
    //uint32 InstantAreaKit;                                // 23
    //uint32 ImpactAreaKit;                                 // 24
    //uint32 PersistentAreaKit;                             // 25
    //DBCPosition3D MissileCastOffset;                      // 26-28
    //DBCPosition3D MissileImpactOffset;                    // 29-31
};

struct StableSlotPricesEntry
{
    uint32 ID;                                              // 0
    uint32 Cost;                                            // 1
};

struct SummonPropertiesEntry
{
    uint32 ID;                                              // 0
    uint32 Control;                                         // 1
    uint32 Faction;                                         // 2
    uint32 Title;                                           // 3
    uint32 Slot;                                            // 4
    uint32 Flags;                                           // 5
};

struct TalentEntry
{
    uint32 ID;                                              // 0
    uint32 TabID;                                           // 1 index in TalentTab.dbc (TalentTabEntry)
    uint32 TierID;                                          // 2
    uint32 ColumnIndex;                                     // 3
    std::array<uint32, MAX_TALENT_RANK> SpellRank;          // 4-8
    //std::array<uint32, 4> SpellRankUnused;                // 9-12
    uint32 PrereqTalent;                                    // 13 index in Talent.dbc (TalentEntry)
    //std::array<uint32, 2> PrereqTalentUnused;             // 14-15
    uint32 PrereqRank;                                      // 16
    //std::array<uint32, 2> PrereqRankUnused;               // 17-18
    //uint32 Flags;                                         // 19
    //uint32 RequiredSpellID;                               // 20 all 0
    //std::array<uint32, 2> CategoryMask;                   // 21 its a 64 bit mask for pet 1<<CategoryEnumID in CreatureFamily.dbc
};

struct TalentTabEntry
{
    uint32 ID;                                              // 0
    //char const* Name[16];                                 // 1-16
    //uint32 Name_lang_mask;                                // 17
    //unit32 SpellIconID;                                   // 18
    //uint32 RaceMask;                                      // 19
    uint32 ClassMask;                                       // 20
    uint32 PetTalentMask;                                   // 21
    uint32 OrderIndex;                                      // 22
    //char const* BackgroundFile;                           // 23
};

struct TaxiNodesEntry
{
    uint32 ID;                                              // 0
    uint32 ContinentID;                                     // 1
    DBCPosition3D Pos;                                      // 2-4
    char const* Name[16];                                   // 5-21
    //uint32 Name_lang_mask;                                // 22
    uint32 MountCreatureID[2];                              // 23-24
};

struct TaxiPathEntry
{
    uint32 ID;                                              // 0
    uint32 FromTaxiNode;                                    // 1
    uint32 ToTaxiNode;                                      // 2
    uint32 Cost;                                            // 3
};

struct TaxiPathNodeEntry
{
    //uint32 ID;                                            // 0
    uint32 PathID;                                          // 1
    uint32 NodeIndex;                                       // 2
    uint32 ContinentID;                                     // 3
    DBCPosition3D Loc;                                      // 4-6
    uint32 Flags;                                           // 7
    uint32 Delay;                                           // 8
    uint32 ArrivalEventID;                                  // 9
    uint32 DepartureEventID;                                // 10
};

struct TeamContributionPointsEntry
{
    //uint32 ID;                                            // 0
    float Data;                                             // 1
};

struct TotemCategoryEntry
{
    uint32 ID;                                              // 0
    //char const* Name[16];                                 // 1-16
    //uint32 Name_lang_mask;                                // 17
    uint32 TotemCategoryType;                               // 18 (one for specialization)
    uint32 TotemCategoryMask;                               // 19 (compatibility mask for same type: different for totems, compatible from high to low for rods)
};

struct TransportAnimationEntry
{
    //uint32 ID;                                            // 0
    uint32 TransportID;                                     // 1
    uint32 TimeIndex;                                       // 2
    DBCPosition3D Pos;                                      // 3
    //uint32 SequenceID;                                    // 4
};

struct TransportRotationEntry
{
    //uint32 ID;                                            // 0
    uint32 GameObjectsID;                                   // 1
    uint32 TimeIndex;                                       // 2
    float X;                                                // 3
    float Y;                                                // 4
    float Z;                                                // 5
    float W;                                                // 6
};

#define MAX_VEHICLE_SEATS 8

struct VehicleEntry
{
    uint32 ID;                                              // 0
    uint32 Flags;                                           // 1
    float TurnSpeed;                                        // 2
    float PitchSpeed;                                       // 3
    float PitchMin;                                         // 4
    float PitchMax;                                         // 5
    uint32 SeatID[MAX_VEHICLE_SEATS];                       // 6-13
    float MouseLookOffsetPitch;                             // 14
    float CameraFadeDistScalarMin;                          // 15
    float CameraFadeDistScalarMax;                          // 16
    float CameraPitchOffset;                                // 17
    float FacingLimitRight;                                 // 18
    float FacingLimitLeft;                                  // 19
    float MsslTrgtTurnLingering;                            // 20
    float MsslTrgtPitchLingering;                           // 21
    float MsslTrgtMouseLingering;                           // 22
    float MsslTrgtEndOpacity;                               // 23
    float MsslTrgtArcSpeed;                                 // 24
    float MsslTrgtArcRepeat;                                // 25
    float MsslTrgtArcWidth;                                 // 26
    float MsslTrgtImpactRadius[2];                          // 27-28
    char const* MsslTrgtArcTexture;                         // 29
    char const* MsslTrgtImpactTexture;                      // 30
    char const* MsslTrgtImpactModel[2];                     // 31-32
    float CameraYawOffset;                                  // 33
    uint32 UiLocomotionType;                                // 34
    float MsslTrgtImpactTexRadius;                          // 35
    uint32 VehicleUIIndicatorID;                            // 36
    uint32 PowerDisplayID;                                  // 37
    //uint32 PowerDisplayIDUnused[2];                       // 38-39
};

struct VehicleSeatEntry
{
    uint32 ID;                                              // 0
    uint32 Flags;                                           // 1
    int32 AttachmentID;                                     // 2
    DBCPosition3D AttachmentOffset;                         // 3-5
    float EnterPreDelay;                                    // 6
    float EnterSpeed;                                       // 7
    float EnterGravity;                                     // 8
    float EnterMinDuration;                                 // 9
    float EnterMaxDuration;                                 // 10
    float EnterMinArcHeight;                                // 11
    float EnterMaxArcHeight;                                // 12
    int32 EnterAnimStart;                                   // 13
    int32 EnterAnimLoop;                                    // 14
    int32 RideAnimStart;                                    // 15
    int32 RideAnimLoop;                                     // 16
    int32 RideUpperAnimStart;                               // 17
    int32 RideUpperAnimLoop;                                // 18
    float ExitPreDelay;                                     // 19
    float ExitSpeed;                                        // 20
    float ExitGravity;                                      // 21
    float ExitMinDuration;                                  // 22
    float ExitMaxDuration;                                  // 23
    float ExitMinArcHeight;                                 // 24
    float ExitMaxArcHeight;                                 // 25
    int32 ExitAnimStart;                                    // 26
    int32 ExitAnimLoop;                                     // 27
    int32 ExitAnimEnd;                                      // 28
    float PassengerYaw;                                     // 29
    float PassengerPitch;                                   // 30
    float PassengerRoll;                                    // 31
    int32 PassengerAttachmentID;                            // 32
    int32 VehicleEnterAnim;                                 // 33
    int32 VehicleExitAnim;                                  // 34
    int32 VehicleRideAnimLoop;                              // 35
    int32 VehicleEnterAnimBone;                             // 36
    int32 VehicleExitAnimBone;                              // 37
    int32 VehicleRideAnimLoopBone;                          // 38
    float VehicleEnterAnimDelay;                            // 39
    float VehicleExitAnimDelay;                             // 40
    uint32 VehicleAbilityDisplay;                           // 41
    uint32 EnterUISoundID;                                  // 42
    uint32 ExitUISoundID;                                   // 43
    int32 UiSkin;                                           // 44
    uint32 FlagsB;                                          // 45
    //float CameraEnteringDelay;                            // 46
    //float CameraEnteringDuration;                         // 47
    //float CameraExitingDelay;                             // 48
    //float CameraExitingDuration;                          // 49
    //DBCPosition3D CameraOffset;                           // 50-52
    //float CameraPosChaseRate;                             // 53
    //float CameraFacingChaseRate;                          // 54
    //float CameraEnteringZoom;                             // 55
    //float CameraSeatZoomMin;                              // 56
    //float CameraSeatZoomMax;                              // 57

    inline bool HasFlag(VehicleSeatFlags flag) const { return (Flags & flag) != 0; }
    inline bool HasFlag(VehicleSeatFlagsB flag) const { return (FlagsB & flag) != 0; }

    inline bool CanEnterOrExit() const { return HasFlag(VehicleSeatFlags(VEHICLE_SEAT_FLAG_CAN_ENTER_OR_EXIT | VEHICLE_SEAT_FLAG_CAN_CONTROL | VEHICLE_SEAT_FLAG_SHOULD_USE_VEH_SEAT_EXIT_ANIM_ON_VOLUNTARY_EXIT)); }
    inline bool CanSwitchFromSeat() const { return HasFlag(VEHICLE_SEAT_FLAG_CAN_SWITCH); }
    inline bool IsUsableByOverride() const { return HasFlag(VehicleSeatFlags(VEHICLE_SEAT_FLAG_UNCONTROLLED | VEHICLE_SEAT_FLAG_UNK18))
                                    || HasFlag(VehicleSeatFlagsB(VEHICLE_SEAT_FLAG_B_USABLE_FORCED | VEHICLE_SEAT_FLAG_B_USABLE_FORCED_2 |
                                        VEHICLE_SEAT_FLAG_B_USABLE_FORCED_3 | VEHICLE_SEAT_FLAG_B_USABLE_FORCED_4)); }
    inline bool IsEjectable() const { return HasFlag(VEHICLE_SEAT_FLAG_B_EJECTABLE); }
};

struct WMOAreaTableEntry
{
    uint32 ID;                                              // 0 index
    int32 WMOID;                                            // 1 used in root WMO
    int32 NameSetID;                                        // 2 used in adt file
    int32 WMOGroupID;                                       // 3 used in group WMO
    //uint32 SoundProviderPref;                             // 4
    //uint32 SoundProviderPrefUnderwater;                   // 5
    //uint32 AmbienceID;                                    // 6
    //uint32 ZoneMusic;                                     // 7
    //uint32 IntroSound;                                    // 8
    uint32 Flags;                                           // 9 used for indoor/outdoor determination
    uint32 AreaTableID;                                     // 10 link to AreaTableEntry.ID
    //char const* AreaName[16];                             // 11
    //uint32 AreaName_lang_mask;                            // 12
};

struct WorldMapAreaEntry
{
    //uint32 ID;                                            // 0
    uint32 MapID;                                           // 1
    uint32 AreaID;                                          // 2
    //char const* AreaName                                  // 3
    float LocLeft;                                          // 4
    float LocRight;                                         // 5
    float LocTop;                                           // 6
    float LocBottom;                                        // 7
    int32 DisplayMapID;                                     // 8 -1 (map_id have correct map) other: virtual map where zone show (map_id - where zone in fact internally)
    //int32 DefaultDungeonFloor;                            // 9 pointer to DungeonMap.dbc (override x1, x2, y1, y2 coordinates)
    //uint32 ParentWorldMapID;                              // 10
};

#define MAX_WORLD_MAP_OVERLAY_AREA_IDX 4

struct WorldMapOverlayEntry
{
    uint32 ID;                                              // 0
    //uint32 MapAreaID;                                     // 1 ID in WorldMapArea.dbc
    uint32 AreaID[MAX_WORLD_MAP_OVERLAY_AREA_IDX];          // 2-5
    //uint32 MapPointX;                                     // 6
    //uint32 MapPointY;                                     // 7
    //char const* TextureName                               // 8
    //uint32 TextureWidth;                                  // 9
    //uint32 TextureHeight;                                 // 10
    //uint32 OffsetX;                                       // 11
    //uint32 OffsetY;                                       // 12
    //uint32 HitRectTop;                                    // 13
    //uint32 HitRectLeft;                                   // 14
    //uint32 HitRectBottom;                                 // 15
    //uint32 HitRectRight;                                  // 16
};

struct WorldSafeLocsEntry
{
    uint32 ID;                                              // 0
    uint32 Continent;                                       // 1
    DBCPosition3D Loc;                                      // 2-4
    //char const* AreaName[16]                              // 5-20
    //uint32 AreaName_lang_mask;                            // 21
};

/*
struct WorldStateUI
{
    uint32 ID;                                              // 0
    uint32 MapID;                                           // 1 Can be -1 to show up everywhere.
    uint32 AreaID;                                          // 2 Can be zero for "everywhere".
    uint32 PhaseShift;                                      // 3 Phase this WorldState is avaliable in
    char const* Icon;                                       // 4 The icon that is used in the interface.
    char const* String;                                     // 5-20
    uint32 String_lang_mask;                                // 21
    char const* Tooltip;                                    // 22-37
    uint32 Tooltip_lang_mask;                               // 38
    uint32 StateVariable;                                   // 39
    uint32 Type;                                            // 40 0 = unknown, 1 = unknown, 2 = not shown in ui, 3 = wintergrasp
    char const* DynamicIcon;                                // 41
    char const* DynamicTooltip[16];                         // 42-57
    uint32 DynamicTooltip_lang_mask;                        // 58
    char const* ExtendedUI;                                 // 59
    uint32 ExtendedUIStateVariable[3];                      // 60-62
};
*/

/*
struct WorldStateZoneSounds
{
    uint32 WorldStateID;                                    // 0
    uint32 WorldStateValue;                                 // 1
    uint32 AreaID;                                          // 2
    uint32 WMOAreaID;                                       // 3
    uint32 ZoneIntroMusicID;                                // 4
    uint32 ZoneMusicID;                                     // 5
    uint32 SoundAmbienceID;                                 // 6
    uint32 SoundProviderPreferencesID;                      // 7
};
*/

#pragma pack(pop)

// Structures not used for casting to loaded DBC data and not required then packing
struct MapDifficulty
{
    MapDifficulty() : resetTime(0), maxPlayers(0), hasErrorMessage(false) { }
    MapDifficulty(uint32 _resetTime, uint32 _maxPlayers, bool _hasErrorMessage) : resetTime(_resetTime), maxPlayers(_maxPlayers), hasErrorMessage(_hasErrorMessage) { }

    uint32 resetTime;
    uint32 maxPlayers;
    bool hasErrorMessage;
};

struct TalentSpellPos
{
    TalentSpellPos() : talent_id(0), rank(0) { }
    TalentSpellPos(uint16 _talent_id, uint8 _rank) : talent_id(_talent_id), rank(_rank) { }

    uint16 talent_id;
    uint8  rank;
};

typedef std::map<uint32, TalentSpellPos> TalentSpellPosMap;

struct TaxiPathBySourceAndDestination
{
    TaxiPathBySourceAndDestination() : ID(0), price(0) { }
    TaxiPathBySourceAndDestination(uint32 _id, uint32 _price) : ID(_id), price(_price) { }

    uint32    ID;
    uint32    price;
};
typedef std::map<uint32, TaxiPathBySourceAndDestination> TaxiPathSetForSource;
typedef std::map<uint32, TaxiPathSetForSource> TaxiPathSetBySource;

typedef std::vector<TaxiPathNodeEntry const*> TaxiPathNodeList;
typedef std::vector<TaxiPathNodeList> TaxiPathNodesByPath;

#endif
