/*
 * Copyright (C) 2019+ ATieshCore <https://at-wow.org/>
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

struct AchievementDBC
{
    uint32 ID;                                              // 0
    int32 Faction;                                          // 1 -1=all, 0=horde, 1=alliance
    int32 InstanceID;                                       // 2 -1=none
    //uint32 Supercedes;                                    // 3 its Achievement parent (can`t start while parent uncomplete, use its Criteria if don`t have own, use its progress on begin)
    std::array<char const*, 16> Title[TOTAL_LOCALES];       // 12
    //uint32 Title_lang_mask;                               // 20
    //char const* Description[16];                          // 21-36
    //uint32 Description_lang_mask;                         // 37
    uint32 Category;                                        // 38
    uint32 Points;                                          // 39 reward points
    //uint32 UiOrder;                                       // 40 icon (from SpellIcon.dbc)
    uint32 Flags;                                           // 41
    //uint32 IconID;                                        // 42
    //char const* Reward[16];                               // 43-58
    //uint32 Reward_lang_mask;                              // 59
    uint32 MinimumCriteria;                                 // 60 - need this count of completed criterias (own or referenced achievement criterias)
    uint32 SharesCriteria;                                  // 61 - referenced achievement (counting of all completed criterias)
};

struct AchievementCriteriaDBC
{
    uint32 ID;                                              // 0
    uint32 AchievementID;                                   // 1
    uint32 Type;                                            // 2
    union
    {
        uint32 ID;
        // ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE          = 0
        // ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_CREATURE     = 20
        uint32 CreatureID;

        // ACHIEVEMENT_CRITERIA_TYPE_WIN_BG                 = 1
        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_BATTLEGROUND  = 15
        // ACHIEVEMENT_CRITERIA_TYPE_DEATH_AT_MAP           = 16
        // ACHIEVEMENT_CRITERIA_TYPE_WIN_ARENA              = 32
        // ACHIEVEMENT_CRITERIA_TYPE_PLAY_ARENA             = 33
        uint32 MapID;

        // ACHIEVEMENT_CRITERIA_TYPE_REACH_SKILL_LEVEL      = 7
        // ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LEVEL      = 40
        // ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILLLINE_SPELLS = 75
        // ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LINE       = 112
        uint32 SkillID;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ACHIEVEMENT   = 8
        uint32 AchievementID;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUESTS_IN_ZONE = 11
        uint32 ZoneID;

        // ACHIEVEMENT_CRITERIA_TYPE_CURRENCY = 12
        uint32 CurrencyID;

        // ACHIEVEMENT_CRITERIA_TYPE_DEATH_IN_DUNGEON       = 18
        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_RAID          = 19
        uint32 GroupSize;

        // ACHIEVEMENT_CRITERIA_TYPE_DEATHS_FROM            = 26
        uint32 DamageType;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST         = 27
        uint32 QuestID;

        // ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET        = 28
        // ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2       = 69
        // ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL             = 29
        // ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL2            = 110
        // ACHIEVEMENT_CRITERIA_TYPE_LEARN_SPELL            = 34
        uint32 SpellID;

        // ACHIEVEMENT_CRITERIA_TYPE_BG_OBJECTIVE_CAPTURE
        uint32 ObjectiveId;

        // ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL_AT_AREA = 31
        uint32 AreaID;

        // ACHIEVEMENT_CRITERIA_TYPE_OWN_ITEM               = 36
        // ACHIEVEMENT_CRITERIA_TYPE_USE_ITEM               = 41
        // ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM              = 42
        // ACHIEVEMENT_CRITERIA_TYPE_EQUIP_ITEM             = 57
        uint32 ItemID;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_TEAM_RATING    = 38
        // ACHIEVEMENT_CRITERIA_TYPE_REACH_TEAM_RATING      = 39
        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_PERSONAL_RATING = 39
        uint32 TeamType;

        // ACHIEVEMENT_CRITERIA_TYPE_EXPLORE_AREA           = 43
        uint32 WorldMapOverlayID;

        // ACHIEVEMENT_CRITERIA_TYPE_GAIN_REPUTATION        = 46
        uint32 FactionID;

        // ACHIEVEMENT_CRITERIA_TYPE_EQUIP_EPIC_ITEM        = 49
        uint32 ItemSlot;

        // ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED_ON_LOOT      = 50
        // ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED_ON_LOOT     = 51
        uint32 RollValue;

        // ACHIEVEMENT_CRITERIA_TYPE_HK_CLASS               = 52
        uint32 ClassID;

        // ACHIEVEMENT_CRITERIA_TYPE_HK_RACE                = 53
        uint32 RaceID;

        // ACHIEVEMENT_CRITERIA_TYPE_DO_EMOTE               = 54
        uint32 EmoteID;

        // ACHIEVEMENT_CRITERIA_TYPE_USE_GAMEOBJECT         = 68
        // ACHIEVEMENT_CRITERIA_TYPE_FISH_IN_GAMEOBJECT     = 72
        uint32 GameObjectID;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_POWER          = 96
        uint32 PowerType;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_STAT           = 97
        uint32 StatType;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_SPELLPOWER     = 98
        uint32 SpellSchool;

        // ACHIEVEMENT_CRITERIA_TYPE_LOOT_TYPE              = 109
        uint32 LootType;
    } Asset;                                                // 3

    uint32 Quantity;                                        // 4

    struct
    {
        uint32 Type;
        uint32 Asset;
    } AdditionalRequirements[MAX_CRITERIA_REQUIREMENTS];    // 5-8

    std::array<char const*, 16> name[TOTAL_LOCALES];        // 9-17
    //uint32 Description_lang_mask;                         // 25
    uint32 Flags;                                           // 26
    uint32 StartEvent;                                      // 27 AchievementCriteriaTimedTypes
    uint32 StartAsset;                                      // 28 Always appears with timed events, used internally to start the achievement, store
    uint32 StartTimer;                                      // 29 time limit in seconds
    //uint32 UiOrder;                                       // 30
};

struct AreaTableDBC
{
    uint32 ID;                                              // 0
    uint32 ContinentID;                                     // 1
    uint32 ParentAreaID;                                    // 2 if 0 then it's zone, else it's zone id of this area
    uint32 AreaBit;                                         // 3
    uint32 Flags;                                           // 4
    //uint32 SoundProviderPref;                             // 5
    //uint32 SoundProviderPrefUnderwater;                   // 6
    //uint32 AmbienceID;                                    // 7
    //uint32 ZoneMusic;                                     // 8
    //uint32 IntroSound;                                    // 9
    int32 ExplorationLevel;                                 // 10
    std::string AreaName[TOTAL_LOCALES];                    // 11-19
    //uint32 AreaName_lang_mask;                            // 27
    uint32 FactionGroupMask;                                // 28
    uint32 LiquidTypeID[4];                                 // 29-32 liquid override by type
    //float MinElevation;                                   // 33
    //float AmbientMultiplier;                              // 34
    //uint32 LightID;                                       // 35

    // helpers
    bool IsSanctuary() const
    {
        if (ContinentID == 609)
            return true;
        return (Flags & AREA_FLAG_SANCTUARY) != 0;
    }

    bool IsFlyable() const
    {
        if (Flags & AREA_FLAG_OUTLAND)
        {
            if (!(Flags & AREA_FLAG_NO_FLY_ZONE))
                return true;
        }

        return false;
    }
};

#define MAX_GROUP_AREA_IDS 6

struct AreaGroupDBC
{
    uint32 ID;                                              // 0
    uint32 AreaID[MAX_GROUP_AREA_IDS];                      // 1-6
    uint32 NextAreaID;                                      // 7 index of next group
};

struct AreaPOIDBC
{
    uint32 ID;                                              // 0
    uint32 Importance;                                      // 1
    uint32 Icon[9];                                         // 2-10
    uint32 FactionID;                                       // 11
    DBCPosition3D Pos;                                      // 12-14
    uint32 ContinentID;                                     // 15
    //uint32 Flags;                                         // 16
    uint32 AreaID;                                          // 17
    //char const* Name[16];                                 // 18-33
    //uint32 Name_lang_mask;                                // 34
    //char const* Description[16];                          // 35-50
    //uint32 Description_lang_mask;                         // 51
    uint32 WorldStateID;                                    // 52
    //uint32 WorldMapLink;                                  // 53
};

struct AreaTriggerDBC
{
    uint32 ID;                                              // 0
    uint32 ContinentID;                                     // 1
    DBCPosition3D Pos;                                      // 2-4
    float Radius;                                           // 5
    float BoxLength;                                        // 6
    float BoxWidth;                                         // 7
    float BoxHeight;                                        // 8
    float BoxYaw;                                           // 9
};

struct AuctionHouseDBC
{
    uint32 ID;                                              // 0
    uint32 FactionID;                                       // 1 id of faction.dbc for player factions associated with city
    uint32 DepositRate;                                     // 2 1/3 from real
    uint32 ConsignmentRate;                                 // 3
    //char const* Name[16];                                 // 4-19
    //uint32 Name_lang_mask;                                // 20
};
