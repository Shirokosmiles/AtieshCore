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

 // load Achievement.dbc
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

// load Achievement_Criteria.dbc
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

// load AreaTable.dbc
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

// load AreaGroup.dbc
#define MAX_GROUP_AREA_IDS 6

struct AreaGroupDBC
{
    uint32 ID;                                              // 0
    uint32 AreaID[MAX_GROUP_AREA_IDS];                      // 1-6
    uint32 NextAreaID;                                      // 7 index of next group
};

// load AreaPOI.dbc (NOT USED)
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

// load AreaTrigger.dbc
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

// load AuctionHouse.dbc
struct AuctionHouseDBC
{
    uint32 ID;                                              // 0
    uint32 FactionID;                                       // 1 id of faction.dbc for player factions associated with city
    uint32 DepositRate;                                     // 2 1/3 from real
    uint32 ConsignmentRate;                                 // 3
    //char const* Name[16];                                 // 4-19
    //uint32 Name_lang_mask;                                // 20
};

// load BankBagSlotPrices.dbc
struct BankBagSlotPricesDBC
{
    uint32 ID;                                              // 0
    uint32 Cost;                                            // 1
};

// load BannedAddOns.dbc
struct BannedAddOnsDBC
{
    uint32 ID;                                              // 0
    //uint32 NameMD5[4];                                    // 1-4
    //uint32 VersionMD5[4];                                 // 5-8
    //uint32 LastModified;                                  // 9
    //uint32 Flags;                                         // 10
};

// load BarberShopStyle.dbc
struct BarberShopStyleDBC
{
    uint32 ID;                                              // 0
    uint32 Type;                                            // 1 value 0 -> hair, value 2 -> facialhair
    //char const* DisplayName[16];                          // 2-17
    //uint32 DisplayName_lang_mask;                         // 18
    //uint32 Description[16];                               // 19-34, all empty
    //uint32 Description_lang_mask;                         // 35
    //float CostModifier;                                   // 36
    uint32 Race;                                            // 37
    uint32 Sex;                                             // 38
    uint32 Data;                                            // 39 real ID to hair/facial hair
};

// load BattlemasterList.dbc
struct BattlemasterListDBC
{
    uint32 ID;                                              // 0
    int32 MapID[8];                                         // 1-8
    uint32 InstanceType;                                    // 9 map type (3 - BG, 4 - arena)
    //uint32 GroupsAllowed;                                 // 10
    std::string Name[TOTAL_LOCALES];                        // 11-26
    //uint32 Name_lang_mask;                                // 27
    uint32 MaxGroupSize;                                    // 28 used for checking if queue as group
    uint32 HolidayWorldState;                               // 29
    //uint32 MinLevel;                                      // 30
    //uint32 MaxLevel;                                      // 31
};

// load CharacterFacialHairStyles.dbc
struct CharacterFacialHairStylesDBC
{
    uint32 ID;                                              // 0
    uint8 RaceID;                                          // 1
    uint8 SexID;                                           // 2
    uint8 VariationID;                                     // 3
    //uint32 Geoset[5];                                     // 4-8
};

// load CharSections.dbc
enum CharSectionFlags
{
    SECTION_FLAG_PLAYER       = 0x01,
    SECTION_FLAG_DEATH_KNIGHT = 0x04
};

enum CharSectionType : uint8
{
    SECTION_TYPE_SKIN         = 0,
    SECTION_TYPE_FACE         = 1,
    SECTION_TYPE_FACIAL_HAIR  = 2,
    SECTION_TYPE_HAIR         = 3,
    SECTION_TYPE_UNDERWEAR    = 4
};

struct CharSectionsDBC
{
    uint32 ID;                                             // 0
    uint8 RaceID;                                          // 1
    uint8 SexID;                                           // 2
    uint8 BaseSection;                                     // 3
    //char const* TextureName[3];                          // 4-6
    uint8 Flags;                                           // 7
    uint8 VariationIndex;                                  // 8
    uint8 ColorIndex;                                      // 9

    inline bool HasFlag(CharSectionFlags flag) const { return (Flags & flag) != 0; }
};

// load CharStartOutfit.dbc
#define MAX_OUTFIT_ITEMS 24

struct CharStartOutfitDBC
{
    uint32 ID;                                              // 0
    uint8 RaceID;                                           // 1
    uint8 ClassID;                                          // 2
    uint8 SexID;                                            // 3
    //uint8 OutfitID;                                       // 4
    int32 ItemID[MAX_OUTFIT_ITEMS];                         // 5-28
    //int32 DisplayItemID[MAX_OUTFIT_ITEMS];                // 29-52 not required at server side
    //int32 InventoryType[MAX_OUTFIT_ITEMS];                // 53-76 not required at server side
};

// load CharTitles.dbc
struct CharTitlesDBC
{
    uint32 ID;                                              // 0, title ids, for example in Quest::GetCharTitleId()
    //uint32 ConditionID;                                   // 1
    std::string Name[TOTAL_LOCALES];                        // 2-17 male
    //uint32 Name_lang_mask;                                // 18
    std::string Name1[TOTAL_LOCALES];                       // 19-34 female
    //uint32 Name1_lang_mask;                               // 35
    uint32 MaskID;                                          // 36 used in PLAYER_CHOSEN_TITLE and 1<<index in PLAYER__FIELD_KNOWN_TITLES
};

// load ChatChannels.dbc
struct ChatChannelsDBC
{
    uint32 ID;                                              // 0
    uint32 Flags;                                           // 1
    //uint32 FactionGroup;                                  // 2
    std::string Name[TOTAL_LOCALES];                        // 3-18
    //uint32 Name_lang_mask;                                // 19
    //std::string Shortcut[TOTAL_LOCALES];                  // 20-35
    //uint32 Shortcut_lang_mask;                            // 36
};

// load ChrClasses.dbc
struct ChrClassesDBC
{
    uint32 ID;                                              // 0
    //uint32 DamageBonusStat;                               // 1
    uint32 DisplayPower;                                    // 2
    //char const* PetNameToken;                             // 3
    std::string Name[TOTAL_LOCALES];                        // 4-19
    //uint32 Name_lang_mask;                                // 20
    //char const* NameFemale[16];                           // 21-36
    //uint32 NameFemale_lang_mask;                          // 37
    //char const* NameMale[16];                             // 38-53
    //uint32 NameMale_lang_mask;                            // 54
    //char const* Filename;                                 // 55
    uint32 SpellClassSet;                                   // 56
    //uint32 Flags;                                         // 57
    uint32 CinematicSequenceID;                             // 58 ID from CinematicSequences.dbc
    uint32 RequiredExpansion;                               // 59
};

// load ChrRaces.dbc
enum ChrRacesAllianceType
{
    CHRRACES_ALLIANCE_TYPE_ALLIANCE     = 0,
    CHRRACES_ALLIANCE_TYPE_HORDE        = 1,
    CHRRACES_ALLIANCE_TYPE_NOT_PLAYABLE = 2,
};

enum ChrRacesFlags
{
    CHRRACES_FLAGS_NOT_PLAYABLE = 0x01,
    CHRRACES_FLAGS_BARE_FEET    = 0x02,
    CHRRACES_FLAGS_CAN_MOUNT    = 0x04
};

struct ChrRacesDBC
{
    uint32 ID;                                              // 0
    uint32 Flags;                                           // 1
    uint32 FactionID;                                       // 2
    //uint32 ExplorationSoundID;                            // 3
    uint32 MaleDisplayID;                                   // 4
    uint32 FemaleDisplayID;                                 // 5
    //char const* ClientPrefix;                             // 6
    uint32 BaseLanguage;                                    // 7 (7-Alliance 1-Horde)
    uint32 CreatureType;                                    // 8
    uint32 ResSicknessSpellID;                              // 9
    //uint32 SplashSoundID;                                 // 10
    //char const* ClientFileString;                         // 11
    uint32 CinematicSequenceID;                             // 12 ID from CinematicSequences.dbc
    uint32 Alliance;                                        // 13
    std::string Name[TOTAL_LOCALES];                        // 14-29
    //uint32 Name_lang_mask;                                // 30
    //char const* NameFemale[16];                           // 31-46
    //uint32 NameFemale_lang_mask;                          // 47
    //char const* NameMale[16];                             // 48-63
    //uint32 NameMale_lang_mask;                            // 64
    //char const* FacialHairCustomization[2];               // 65-66
    //char const* HairCustomization;                        // 67
    uint32 RequiredExpansion;                               // 68

    inline bool HasFlag(ChrRacesFlags flag) const { return (Flags & flag) != 0; }
};

// load CinematicCamera.dbc
struct CinematicCameraDBC
{
    uint32 ID;                                              // 0
    std::string Model;                                      // 1 Model filename (translate .mdx to .m2)
    uint32 SoundID;                                         // 2 Sound ID (voiceover for cinematic)
    float OriginX;                                          // 3 Position X in map used for basis for M2 co-ordinates
    float OriginY;                                          // 4 Position Y in map used for basis for M2 co-ordinates
    float OriginZ;                                          // 5 Position Z in map used for basis for M2 co-ordinates
    float OriginFacing;                                     // 6 Orientation in map used for basis for M2 co-ordinates
};

// load CinematicSequences.dbc
struct CinematicSequencesDBC
{
    uint32 ID;                                              // 0
    //uint32 SoundID;                                       // 1
    uint32 Camera[8];                                       // 2-9 ID in CinematicCamera.dbc
};

// load CreatureDisplayInfo.dbc
struct CreatureDisplayInfoDBC
{
    uint32 ID;                                              // 0
    uint32 ModelID;                                         // 1
    //uint32 SoundID;                                       // 2
    uint32 ExtendedDisplayInfoID;                           // 3
    float CreatureModelScale;                               // 4
    //uint32 CreatureModelAlpha;                            // 5
    //char const* TextureVariation[3];                      // 6-8
    //char const* PortraitTextureName;                      // 9
    //uint32 SizeClass;                                     // 10
    //uint32 BloodID;                                       // 11
    //uint32 NPCSoundID;                                    // 12
    //uint32 ParticleColorID;                               // 13
    //uint32 CreatureGeosetData;                            // 14
    //uint32 ObjectEffectPackageID;                         // 15
};

// load CreatureDisplayInfoExtra.dbc
struct CreatureDisplayInfoExtraDBC
{
    uint32 ID;                                              // 0
    uint32 DisplayRaceID;                                   // 1
    uint32 DisplaySexID;                                    // 2
    //uint32 SkinID;                                        // 3
    //uint32 FaceID;                                        // 4
    //uint32 HairStyleID;                                   // 5
    //uint32 HairColorID;                                   // 6
    //uint32 FacialHairID;                                  // 7
    //uint32 NPCItemDisplay[11];                            // 8-18
    //uint32 Flags;                                         // 19
    //char const* BakeName;                                 // 20
};

// load CreatureFamily.dbc
struct CreatureFamilyDBC
{
    uint32 ID;                                              // 0
    float MinScale;                                         // 1
    uint32 MinScaleLevel;                                   // 2
    float MaxScale;                                         // 3
    uint32 MaxScaleLevel;                                   // 4
    uint32 SkillLine[2];                                    // 5-6
    uint32 PetFoodMask;                                     // 7
    int32 PetTalentType;                                    // 8
    //int32 CategoryEnumID;                                 // 9
    std::string Name[TOTAL_LOCALES];                        // 10-25
    //uint32 Name_lang_mask;                                // 26
    //char const* IconFile;                                 // 27
};

// load CreatureModelData.dbc
enum CreatureModelDataFlags
{
    CREATURE_MODEL_DATA_FLAGS_CAN_MOUNT = 0x00000080
};

struct CreatureModelDataDBC
{
    uint32 ID;                                              // 0
    uint32 Flags;                                           // 1
    std::string ModelName;                                  // 2
    //uint32 SizeClass;                                     // 3
    float ModelScale;                                       // 4 Used in calculation of unit collision data
    //int32 BloodID;                                        // 5
    //int32 FootprintTextureID;                             // 6
    //uint32 FootprintTextureLength;                        // 7
    //uint32 FootprintTextureWidth;                         // 8
    //float FootprintParticleScale;                         // 9
    //uint32 FoleyMaterialID;                               // 10
    //float FootstepShakeSize;                              // 11
    //uint32 DeathThudShakeSize;                            // 12
    //uint32 SoundID;                                       // 13
    //float CollisionWidth;                                 // 14
    float CollisionHeight;                                  // 15
    float MountHeight;                                      // 16 Used in calculation of unit collision data when mounted
    //float GeoBoxMin[3];                                   // 17-19
    //float GeoBoxMax[3];                                   // 20-22
    //float WorldEffectScale;                               // 23
    //float AttachedEffectScale;                            // 24
    //float MissileCollisionRadius;                         // 25
    //float MissileCollisionPush;                           // 26
    //float MissileCollisionRaise;                          // 27

    inline bool HasFlag(CreatureModelDataFlags flag) const { return (Flags & flag) != 0; }
};

// load CreatureSpellData.dbc
struct CreatureSpellDataDBC
{
    uint32 ID;                                              // 0
    uint32 Spells[MAX_CREATURE_SPELL_DATA_SLOT];            // 1-4
    //uint32 Availability[MAX_CREATURE_SPELL_DATA_SLOT];    // 4-7
};

// load CreatureType.dbc
enum CreatureTypeEntryFlags
{
    CREATURE_TYPE_ENTRY_FLAGS_IGNORED_TAB_TARGETING = 0x01 // Means do not include in tab targeting.
};

struct CreatureTypeDBC
{
    uint32 ID;                                              // 0
    //char const* Name[16];                                 // 1-16
    //uint32 Name_lang_mask;                                // 17
    //uint32 Flags;                                         // 18
};

// load CurrencyCategory.dbc (NOT USED)
struct CurrencyCategoryDBC
{
    uint32 ID;                                              // 0
    uint32 Flags;                                           // 1
    std::string Name[TOTAL_LOCALES];                        // 2-17
    //uint32 Name_lang_mask;                                // 18
};

// load CurrencyTypes.dbc
struct CurrencyTypesDBC
{
    uint32 ID;                                              // 0
    uint32 ItemID;                                          // 1
    //uint32 CategoryID;                                    // 2
    uint32 BitIndex;                                        // 3 bit index in PLAYER_FIELD_KNOWN_CURRENCIES (1 << (index-1))
};

// load DestructibleModelData.dbc
struct DestructibleModelDataDBC
{
    uint32 ID;                                              // 0
    //uint32 State0ImpactEffectDoodadSet;                   // 1
    //uint32 State0AmbientDoodadSet;                        // 2
    uint32 State1Wmo;                                       // 3
    //uint32 State1DestructionDoodadSet;                    // 4
    //uint32 State1ImpactEffectDoodadSet;                   // 5
    //uint32 State1AmbientDoodadSet;                        // 6
    uint32 State2Wmo;                                       // 7
    //uint32 State2DestructionDoodadSet;                    // 8
    //uint32 State2ImpactEffectDoodadSet;                   // 9
    //uint32 State2AmbientDoodadSet;                        // 10
    uint32 State3Wmo;                                       // 11
    //uint32 State3InitDoodadSet;                           // 12
    //uint32 State3AmbientDoodadSet;                        // 13
    //uint32 EjectDirection;                                // 14
    uint32 RepairGroundFx;                                  // 15
    //uint32 DoNotHighlight;                                // 16
    //uint32 HealEffect;                                    // 17
    //uint32 HealEffectSpeed;                               // 18
};

// load DungeonEncounter.dbc
struct DungeonEncounterDBC
{
    uint32 ID;                                              // 0
    uint32 MapID;                                           // 1
    uint32 Difficulty;                                      // 2
    //uint32 OrderIndex;                                    // 3
    uint32 Bit;                                             // 4 encounter index for creating completed mask
    std::string Name[TOTAL_LOCALES];                        // 5-20
    //uint32 Name_lang_mask;                                // 21
    //uint32 SpellIconID;                                   // 22
};

// load DurabilityCosts.dbc
struct DurabilityCostsDBC
{
    uint32 ID;                                              // 0
    uint32 WeaponSubClassCost[21];                          // 1-21
    uint32 ArmorSubClassCost[8];                            // 22-29
};

// load DurabilityQuality.dbc
struct DurabilityQualityDBC
{
    uint32 ID;                                              // 0
    float Data;                                             // 1
};

// load Emotes.dbc
struct EmotesDBC
{
    uint32 ID;                                              // 0
    //char const* EmoteSlashCommand;                        // 1 internal name
    //uint32 AnimID;                                        // 2 ref to animationData
    uint32 EmoteFlags;                                      // 3 bitmask, may be unit_flags
    uint32 EmoteSpecProc;                                   // 4 Can be 0, 1 or 2 (determine how emote are shown)
    uint32 EmoteSpecProcParam;                              // 5 unconfirmed, may be enum UnitStandStateType
    //uint32 EventSoundID;                                  // 6
};

// load EmotesText.dbc
struct EmotesTextDBC
{
    uint32 ID;                                              // 0
    //char const* Name;                                     // 1
    uint32 EmoteID;                                         // 2
    //uint32 EmoteText[16];                                 // 3-18
};

// load EmotesTextSound.dbc
struct EmotesTextSoundDBC
{
    uint32 ID;                                              // 0
    uint32 EmotesTextID;                                    // 1
    uint8 RaceID;                                           // 2
    uint8 SexID;                                            // 3 0 male / 1 female
    uint32 SoundID;                                         // 4
};

// load Faction.dbc
struct FactionDBC
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
    std::string Name[TOTAL_LOCALES];                        // 23-38
    //uint32 Name_lang_mask;                                // 39
    //char const* Description[16];                          // 40-55
    //uint32 Description_lang_mask;                         // 56

    // helpers
    bool CanHaveReputation() const
    {
        return ReputationIndex >= 0;
    }
};

// load FactionTemplate.dbc
#define MAX_FACTION_RELATIONS 4

struct FactionTemplateDBC
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
    bool IsFriendlyTo(FactionTemplateDBC const& entry) const
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
    bool IsHostileTo(FactionTemplateDBC const& entry) const
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
    bool IsHostileToPlayers() const { return (EnemyGroup & FACTION_MASK_PLAYER) != 0; }
    bool IsNeutralToAll() const
    {
        for (int i = 0; i < MAX_FACTION_RELATIONS; ++i)
            if (Enemies[i] != 0)
                return false;
        return EnemyGroup == 0 && FriendGroup == 0;
    }
    bool IsContestedGuardFaction() const { return (Flags & FACTION_TEMPLATE_FLAG_CONTESTED_GUARD) != 0; }
};

// load GameObjectArtKit.dbc
struct GameObjectArtKitDBC
{
    uint32 ID;                                              // 0
    //char const* TextureVariation[3]                       // 1-3 m_textureVariations[3]
    //char const* AttachModel[4]                            // 4-8 m_attachModels[4]
};

// load GameObjectDisplayInfo.dbc
struct GameObjectDisplayInfoDBC
{
    uint32 ID;                                              // 0
    std::string ModelName;                                  // 1
    //uint32 Sound[10];                                     // 2-11
    DBCPosition3D GeoBoxMin;                                // 12-14
    DBCPosition3D GeoBoxMax;                                // 15-17
    //uint32 ObjectEffectPackageID;                         // 18
};

// load GemProperties.dbc
struct GemPropertiesDBC
{
    uint32 ID;                                              // 0
    uint32 EnchantID;                                       // 1
    //uint32 MaxCountInv;                                   // 2
    //uint32 MaxCountItem;                                  // 3
    uint32 Type;                                            // 4
};
