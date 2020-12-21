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

#include "DBCStoresMgr.h"
#include "DatabaseEnv.h"

DBCStoresMgr* DBCStoresMgr::instance()
{
    static DBCStoresMgr instance;
    return &instance;
}

DBCStoresMgr::~DBCStoresMgr()
{
    _achievementMap.clear();
    _achievementCriteriaMap.clear();
    _areaTableMap.clear();
    _areaGroupMap.clear();
    _areaPOIMap.clear();
    _areaTriggerMap.clear();
    _auctionHouseMap.clear();
    _bankBagSlotPricesMap.clear();
    _bannedAddonsMap.clear();
    _barberShopStyleMap.clear();
    _battlemasterListMap.clear();
    _characterFacialHairStyleMap.clear();
    _charSectionMap.clear();
    _charStartOutfitMap.clear();
    _charTitlesMap.clear();
    _chatChannelsMap.clear();
    _chrClassesMap.clear();
    _chrRacesMap.clear();
    _cinematicCameraMap.clear();
    _cinematicSequencesMap.clear();
    _creatureDisplayInfoMap.clear();
    _creatureDisplayInfoExtraMap.clear();
    _creatureFamilyMap.clear();
    _creatureModelDataMap.clear();
    _creatureSpellDataMap.clear();
    _creatureTypeMap.clear();
    _currencyCategoryMap.clear();
    _currencyTypesMap.clear();
    _destructibleModelDataMap.clear();
    _dungeonEncounterMap.clear();
    _durabilityCoastsMap.clear();
    _durabilityQualityMap.clear();
    _emotesMap.clear();
    _emotesTextMap.clear();
    _emotesTextSoundMap.clear();
    _factionMap.clear();
    _factionTemplateMap.clear();
    _gameobjectArtKitMap.clear();
    _gameobjectDisplayInfoMap.clear();
    _gemPropertiesMap.clear();
    _glyphPropertiesMap.clear();
    _glyphSlotMap.clear();
    _gtBarberShopCostBaseMap.clear();
    _gtCombatRatingsMap.clear();
    _gtChanceToMeleeCritBaseMap.clear();
    _gtChanceToMeleeCritMap.clear();
    _gtChanceToSpellCritBaseMap.clear();
    _gtChanceToSpellCritMap.clear();
    _gtNPCManaCostScalerMap.clear();
    _gtOCTClassCombatRatingScalarMap.clear();
    _gtOCTRegenHPMap.clear();
    _gtOCTRegenMPMap.clear();
    _gtRegenHPPerSptMap.clear();
    _gtRegenMPPerSptMap.clear();
    _holidaysMap.clear();
    _itemMap.clear();
    _itemBagFamilyMap.clear();
    _itemDisplayInfoMap.clear();
    _itemExtendedCostMap.clear();
    _itemLimitCategoryMap.clear();
    _itemRandomPropertiesMap.clear();
    _itemRandomSuffixMap.clear();
    _itemSetMap.clear();
    _lfgDungeonMap.clear();
    _lightMap.clear();
    _liquidTypeMap.clear();
    _lockMap.clear();
    _mailTemplateMap.clear();
    _mapMap.clear();
    _mapDifficultyMap.clear();
    _movieMap.clear();
    _namesProfanityMap.clear();
    _namesReservedMap.clear();
    for (uint32 i = 0; i < TOTAL_LOCALES; i++)
        NamesProfaneValidators[i].clear();
    for (uint32 i = 0; i < TOTAL_LOCALES; i++)
        NamesReservedValidators[i].clear();
    _overrideSpellDataMap.clear();
    _powerDisplayMap.clear();
    _pvpDifficultyMap.clear();
    _questSortMap.clear();
    _questXPMap.clear();
    _questFactionRewardMap.clear();
    _randPropPointsMap.clear();
    _scalingStatDistributionMap.clear();
}

void DBCStoresMgr::Initialize()
{
    _Load_Achievement();
    _Load_AchievementCriteria();
    _Load_AreaTable();
    _Load_AreaGroup();
    //_Load_AreaPOI(); // unused
    _Load_AreaTrigger();
    _Load_AuctionHouse();
    _Load_BankBagSlotPrices();
    _Load_BannedAddOns();
    _Load_BarberShopStyle();
    _Load_BattlemasterList();
    _Load_CharacterFacialHairStyles();
    _Load_CharSections();
    _Load_CharStartOutfit();
    _Load_CharTitles();
    _Load_ChatChannels();
    _Load_ChrClasses();
    _Load_ChrRaces();
    _Load_CinematicCamera();
    _Load_CinematicSequences();
    _Load_CreatureDisplayInfo();
    _Load_CreatureDisplayInfoExtra();
    _Load_CreatureFamily();
    _Load_CreatureModelData();
    _Load_CreatureSpellData();
    _Load_CreatureType();
    //_Load_CurrencyCategory(); // unused
    _Load_CurrencyTypes();
    _Load_DestructibleModelData();
    _Load_DungeonEncounter();
    _Load_DurabilityCosts();
    _Load_DurabilityQuality();
    _Load_Emotes();
    _Load_EmotesText();
    _Load_EmotesTextSound();
    _Load_Faction();
    _Load_FactionTemplate();
    _Load_GameObjectArtKit();
    _Load_GameObjectDisplayInfo();
    _Load_GemProperties();
    _Load_GlyphProperties();
    _Load_GlyphSlot();
    _Load_gtBarberShopCostBase();
    _Load_gtCombatRatings();
    _Load_gtChanceToMeleeCritBase();
    _Load_gtChanceToMeleeCrit();
    _Load_gtChanceToSpellCritBase();
    _Load_gtChanceToSpellCrit();
    _Load_gtNPCManaCostScaler();
    _Load_gtOCTClassCombatRatingScalar();
    _Load_gtOCTRegenHP();
    //_Load_gtOCTRegenMP(); // unused
    _Load_gtRegenHPPerSpt();
    _Load_gtRegenMPPerSpt();
    _Load_Holidays();
    _Load_Item();
    _Load_ItemBagFamily();
    _Load_ItemDisplayInfo();
    _Load_ItemExtendedCost();
    _Load_ItemLimitCategory();
    _Load_ItemRandomProperties();
    _Load_ItemRandomSuffix();
    _Load_ItemSet();
    _Load_LFGDungeons();
    _Load_Light();
    _Load_LiquidType();
    _Load_Lock();
    _Load_MailTemplate();
    _Load_Map();
    _Load_MapDifficulty();
    _Load_Movie();
    _Load_NamesProfanity();
    _Load_NamesReserved();
    _Load_OverrideSpellData();
    _Load_PowerDisplay();
    _Load_PvpDifficulty();
    _Load_QuestSort();
    _Load_QuestXP();
    _Load_QuestFactionReward();
    _Load_RandPropPoints();
    _Load_ScalingStatDistribution();
}

// load Achievement.dbc
void DBCStoresMgr::_Load_Achievement()
{
    uint32 oldMSTime = getMSTime();

    _achievementMap.clear();
    //                                                0      1         2               3           4                    5                6                7                8                9                10               11           12       13      14         15                16
    QueryResult result = WorldDatabase.Query("SELECT ID, Faction, Instance_Id, Title_Lang_enUS, Title_Lang_koKR, Title_Lang_frFR, Title_Lang_deDE, Title_Lang_zhCN, Title_Lang_zhTW, Title_Lang_esES, Title_Lang_esMX, Title_Lang_ruRU, Category, Points, Flags, Minimum_Criteria, Shares_Criteria FROM dbc_achievement");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_achievements. DB table `dbc_achievement` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        AchievementDBC ach;
        ach.ID              = id;
        ach.Faction         = fields[1].GetInt32();
        ach.InstanceID      = fields[2].GetInt32();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
        {
            const char* test = fields[3+i].GetCString();
            std::array<const char*, 16> name;
            std::memcpy(name.data(), test, 16);

            ach.Title[i] = name;
        }

        ach.Category        = fields[12].GetUInt32();
        ach.Points          = fields[13].GetUInt32();
        ach.Flags           = fields[14].GetUInt32();
        ach.MinimumCriteria = fields[15].GetUInt32();
        ach.SharesCriteria  = fields[16].GetUInt32();

        _achievementMap[id] = ach;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_achievements                  %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load Achievement_Criteria.dbc
void DBCStoresMgr::_Load_AchievementCriteria()
{
    uint32 oldMSTime = getMSTime();

    _achievementCriteriaMap.clear();
    //                                                0          1        2         3       4           5           6            7            8                9                10                      11                   12                      13                       14                   15                       16                  17                    18            19           20                21
    QueryResult result = WorldDatabase.Query("SELECT ID, Achievement_Id, Type, Asset_Id, Quantity, Start_Event, Start_Asset, Fail_Event, Fail_Asset, Description_Lang_enUS, Description_Lang_koKR, Description_Lang_frFR, Description_Lang_deDE, Description_Lang_zhCN, Description_Lang_zhTW, Description_Lang_esES, Description_Lang_esMX, Description_Lang_ruRU, Flags, Timer_Start_Event, Timer_Asset_Id, Timer_Time FROM dbc_achievement_criteria");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_achievement_criteria. DB table `dbc_achievement_criteria` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        AchievementCriteriaDBC achc;
        achc.ID                  = id;
        achc.AchievementID       = fields[1].GetUInt32();
        achc.Type                = fields[2].GetUInt32();

        achc.Asset.ID            = fields[3].GetUInt32();
        achc.Quantity            = fields[4].GetUInt32();

        achc.AdditionalRequirements[0].Type = fields[5].GetUInt32();
        achc.AdditionalRequirements[0].Asset = fields[6].GetUInt32();
        achc.AdditionalRequirements[1].Type = fields[7].GetUInt32();
        achc.AdditionalRequirements[1].Asset = fields[8].GetUInt32();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
        {
            const char* test = fields[9 + i].GetCString();
            std::array<const char*, 16> name;
            std::memcpy(name.data(), test, 16);

            achc.name[i] = name;
        }

        achc.Flags      = fields[18].GetUInt32();
        achc.StartEvent = fields[19].GetUInt32();
        achc.StartAsset = fields[20].GetUInt32();
        achc.StartTimer = fields[21].GetUInt32();

        _achievementCriteriaMap[id] = achc;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_achievement_criteria          %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load AreaTable.dbc
void DBCStoresMgr::_Load_AreaTable()
{
    uint32 oldMSTime = getMSTime();

    _areaTableMap.clear();
    //                                                0       1            2           3       4           5                  6                  7                    8                   9                   10                  11                  12                  13                14                   15                16               17               18              19
    QueryResult result = WorldDatabase.Query("SELECT ID, ContinentID, ParentAreaID, AreaBit, Flags, ExplorationLevel, AreaName_Lang_enUS, AreaName_Lang_koKR, AreaName_Lang_frFR, AreaName_Lang_deDE, AreaName_Lang_zhCN, AreaName_Lang_zhTW, AreaName_Lang_esES, AreaName_Lang_esMX, AreaName_Lang_ruRU, FactionGroupMask, LiquidTypeID_1, LiquidTypeID_2, LiquidTypeID_3, LiquidTypeID_4 FROM dbc_areatable");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_areatable. DB table `dbc_areatable` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        AreaTableDBC at;
        at.ID               = id;
        at.ContinentID      = fields[1].GetUInt32();
        at.ParentAreaID     = fields[2].GetUInt32();
        at.AreaBit          = fields[3].GetUInt32();
        at.Flags            = fields[4].GetUInt32();
        at.ExplorationLevel = fields[5].GetInt32();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            at.AreaName[i] = fields[6 + i].GetString();

        at.FactionGroupMask = fields[15].GetUInt32();
        at.LiquidTypeID[0]  = fields[16].GetUInt32();
        at.LiquidTypeID[1]  = fields[17].GetUInt32();
        at.LiquidTypeID[2]  = fields[18].GetUInt32();
        at.LiquidTypeID[3]  = fields[19].GetUInt32();

        _areaTableMap[id] = at;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_areatable                     %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load AreaGroup.dbc
void DBCStoresMgr::_Load_AreaGroup()
{
    uint32 oldMSTime = getMSTime();

    _areaGroupMap.clear();
    //                                                0     1         2         3         4         5         6         7
    QueryResult result = WorldDatabase.Query("SELECT ID, AreaID_1, AreaID_2, AreaID_3, AreaID_4, AreaID_5, AreaID_6, NextAreaID FROM dbc_areagroup");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_areagroup. DB table `dbc_areagroup` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        AreaGroupDBC ag;
        ag.ID = id;

        for (uint8 i = 0; i < MAX_GROUP_AREA_IDS; i++)
            ag.AreaID[i] = fields[1 + i].GetUInt32();

        ag.NextAreaID = fields[7].GetUInt32();
        _areaGroupMap[id] = ag;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_areagroup                     %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load AreaPOI.dbc  (NOT USED)
void DBCStoresMgr::_Load_AreaPOI()
{
    uint32 oldMSTime = getMSTime();

    _areaPOIMap.clear();
    //                                                0     1          2        3       4       5      6       7       8        9      10      11       12 13 14      15       16        17
    QueryResult result = WorldDatabase.Query("SELECT ID, Importance, Icon_1, Icon_2, Icon_3, Icon_4, Icon_5, Icon_6, Icon_7, Icon_8, Icon_9, FactionID, X, Y, Z, ContinentID, AreaID, WorldStateID FROM dbc_areapoi");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_areapoi. DB table `dbc_areapoi` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        AreaPOIDBC ap;
        ap.ID         = id;
        ap.Importance = fields[1].GetUInt32();

        for (uint8 i = 0; i < 9; i++)
            ap.Icon[i] = fields[2 + i].GetUInt32();

        ap.FactionID    = fields[11].GetUInt32();
        ap.Pos.X        = fields[12].GetFloat();
        ap.Pos.Y        = fields[13].GetFloat();
        ap.Pos.Z        = fields[14].GetFloat();
        ap.ContinentID  = fields[15].GetUInt32();
        ap.AreaID       = fields[16].GetUInt32();
        ap.WorldStateID = fields[17].GetUInt32();

        _areaPOIMap[id] = ap;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_areapoi                       %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load AreaTrigger.dbc
void DBCStoresMgr::_Load_AreaTrigger()
{
    uint32 oldMSTime = getMSTime();

    _areaTriggerMap.clear();
    //                                                0     1         2  3  4     5        6          7          8           9
    QueryResult result = WorldDatabase.Query("SELECT ID, ContinentID, X, Y, Z, Radius, Box_Length, Box_Width, Box_Height, Box_Yaw FROM dbc_areatrigger");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_areatrigger. DB table `dbc_areatrigger` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        AreaTriggerDBC at;
        at.ID          = id;
        at.ContinentID = fields[1].GetUInt32();
        at.Pos.X       = fields[2].GetFloat();
        at.Pos.Y       = fields[3].GetFloat();
        at.Pos.Z       = fields[4].GetFloat();
        at.Radius      = fields[5].GetFloat();
        at.BoxLength   = fields[6].GetFloat();
        at.BoxWidth    = fields[7].GetFloat();
        at.BoxHeight   = fields[8].GetFloat();

        _areaTriggerMap[id] = at;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_areatrigger                   %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load AuctionHouse.dbc
void DBCStoresMgr::_Load_AuctionHouse()
{
    uint32 oldMSTime = getMSTime();

    _auctionHouseMap.clear();
    //                                                0     1             2             3
    QueryResult result = WorldDatabase.Query("SELECT ID, FactionID, DepositRate, ConsignmentRate FROM dbc_auctionhouse");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_auctionhouse. DB table `dbc_auctionhouse` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        AuctionHouseDBC ah;
        ah.ID              = id;
        ah.FactionID       = fields[1].GetUInt32();
        ah.DepositRate     = fields[2].GetUInt32();
        ah.ConsignmentRate = fields[3].GetUInt32();

        _auctionHouseMap[id] = ah;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_auctionhouse                  %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load BankBagSlotPrices.dbc
void DBCStoresMgr::_Load_BankBagSlotPrices()
{
    uint32 oldMSTime = getMSTime();

    _bankBagSlotPricesMap.clear();
    //                                                0   1
    QueryResult result = WorldDatabase.Query("SELECT ID, Cost FROM dbc_bankbagslotprices");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_bankbagslotprices. DB table `dbc_bankbagslotprices` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        BankBagSlotPricesDBC bsp;
        bsp.ID   = id;
        bsp.Cost = fields[1].GetUInt32();

        _bankBagSlotPricesMap[id] = bsp;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_bankbagslotprices             %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load BannedAddOns.dbc
void DBCStoresMgr::_Load_BannedAddOns()
{
    uint32 oldMSTime = getMSTime();

    _bannedAddonsMap.clear();
    //                                                0
    QueryResult result = WorldDatabase.Query("SELECT ID FROM dbc_bannedaddons");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_bannedaddons. DB table `dbc_bannedaddons` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        BannedAddOnsDBC ba;
        ba.ID = id;

        _bannedAddonsMap[id] = ba;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_bannedaddons                  %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load BarberShopStyle.dbc
void DBCStoresMgr::_Load_BarberShopStyle()
{
    uint32 oldMSTime = getMSTime();

    _barberShopStyleMap.clear();
    //                                                0    1    2     3     4
    QueryResult result = WorldDatabase.Query("SELECT ID, Type, Race, Sex, Data FROM dbc_barbershopstyle");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_barbershopstyle. DB table `dbc_barbershopstyle` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        BarberShopStyleDBC bs;
        bs.ID   = id;
        bs.Type = fields[1].GetUInt32();
        bs.Race = fields[2].GetUInt32();
        bs.Sex  = fields[3].GetUInt32();
        bs.Data = fields[4].GetUInt32();

        _barberShopStyleMap[id] = bs;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_barbershopstyle               %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load BattlemasterList.dbc
void DBCStoresMgr::_Load_BattlemasterList()
{
    uint32 oldMSTime = getMSTime();

    _battlemasterListMap.clear();
    //                                                0     1        2        3        4        5        6        7       8             9           10              11              12              13              14              15              16              17              18              19              20
    QueryResult result = WorldDatabase.Query("SELECT ID, MapID_1, MapID_2, MapID_3, MapID_4, MapID_5, MapID_6, MapID_7, MapID_8, InstanceType, Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU, MaxGroupSize, HolidayWorldState FROM dbc_battlemasterlist");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_battlemasterlist. DB table `dbc_battlemasterlist` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        BattlemasterListDBC bl;
        bl.ID = id;

        for (uint8 i = 0; i < 8; i++)
            bl.MapID[i] = fields[1 + i].GetInt32();

        bl.InstanceType = fields[9].GetUInt32();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            bl.Name[i] = fields[10 + i].GetInt32();

        bl.MaxGroupSize      = fields[19].GetUInt32();
        bl.HolidayWorldState = fields[20].GetUInt32();

        _battlemasterListMap[id] = bl;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_battlemasterlist              %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CharacterFacialHairStyles.dbc
void DBCStoresMgr::_Load_CharacterFacialHairStyles()
{
    uint32 oldMSTime = getMSTime();

    _characterFacialHairStyleMap.clear();
    //                                                0    1       2        3
    QueryResult result = WorldDatabase.Query("SELECT ID, RaceID, SexID, VariationID FROM dbc_characterfacialhairstyles");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_characterfacialhairstyles. DB table `dbc_characterfacialhairstyles` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        CharacterFacialHairStylesDBC cfhs;
        cfhs.ID          = id;
        cfhs.RaceID      = fields[1].GetUInt8();
        cfhs.SexID       = fields[2].GetUInt8();
        cfhs.VariationID = fields[3].GetUInt8();

        _characterFacialHairStyleMap[id] = cfhs;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_characterfacialhairstyles     %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CharSections.dbc
void DBCStoresMgr::_Load_CharSections()
{
    uint32 oldMSTime = getMSTime();

    _charSectionMap.clear();
    //                                                0    1       2         3         4         5             6
    QueryResult result = WorldDatabase.Query("SELECT ID, RaceID, SexID, BaseSection, Flags, VariationIndex, ColorIndex FROM dbc_charsections");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_charsections. DB table `dbc_charsections` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        CharSectionsDBC cs;
        cs.ID             = id;
        cs.RaceID         = fields[1].GetUInt8();
        cs.SexID          = fields[2].GetUInt8();
        cs.BaseSection    = fields[3].GetUInt8();
        cs.Flags          = fields[4].GetUInt8();
        cs.VariationIndex = fields[5].GetUInt8();
        cs.ColorIndex     = fields[6].GetUInt8();

        _charSectionMap[id] = cs;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_charsections                  %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CharStartOutfit.dbc
void DBCStoresMgr::_Load_CharStartOutfit()
{
    uint32 oldMSTime = getMSTime();

    _charStartOutfitMap.clear();
    //                                                0    1        2       3       4         5         6         7         8         9         10        11        12        13        14          15        16          17        18          19         20         21        22          23         24         25        26          27
    QueryResult result = WorldDatabase.Query("SELECT ID, RaceID, ClassID, SexID, ItemID_1, ItemID_2, ItemID_3, ItemID_4, ItemID_5, ItemID_6, ItemID_7, ItemID_8, ItemID_9, ItemID_10, ItemID_11, ItemID_12, ItemID_13, ItemID_14, ItemID_15, ItemID_16, ItemID_17, ItemID_18, ItemID_19, ItemID_20, ItemID_21, ItemID_22, ItemID_23, ItemID_24 FROM dbc_charstartoutfit");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_charstartoutfit. DB table `dbc_charstartoutfit` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        CharStartOutfitDBC cso;
        cso.ID      = id;
        cso.RaceID  = fields[1].GetUInt8();
        cso.ClassID = fields[2].GetUInt8();
        cso.SexID   = fields[3].GetUInt8();

        for (uint8 i = 0; i < MAX_OUTFIT_ITEMS; i++)
            cso.ItemID[i] = fields[4 + i].GetInt32();        

        _charStartOutfitMap[id] = cso;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_charstartoutfit               %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CharTitles.dbc
void DBCStoresMgr::_Load_CharTitles()
{
    uint32 oldMSTime = getMSTime();

    _charTitlesMap.clear();
    //                                                0        1               2               3               4               5               6               7               8               9               10              11              12                13                14              15              16              17                  18           19
    QueryResult result = WorldDatabase.Query("SELECT ID, Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU, Name1_Lang_enUS, Name1_Lang_koKR, Name1_Lang_frFR, Name1_Lang_deDE, Name1_Lang_zhCN, Name1_Lang_zhTW, Name1_Lang_esES, Name1_Lang_esMX, Name1_Lang_ruRU, Mask_ID FROM dbc_chartitles");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_chartitles. DB table `dbc_chartitles` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        CharTitlesDBC ct;
        ct.ID = id;

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            ct.Name[i] = fields[1 + i].GetString();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            ct.Name1[i] = fields[10 + i].GetString();

        ct.MaskID = fields[19].GetUInt32();

        _charTitlesMap[id] = ct;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_chartitles                    %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load ChatChannels.dbc
void DBCStoresMgr::_Load_ChatChannels()
{
    uint32 oldMSTime = getMSTime();

    _chatChannelsMap.clear();
    //                                                0    1             2           3               4               5               6               7               8               9               10
    QueryResult result = WorldDatabase.Query("SELECT ID, Flags, Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU FROM dbc_chatchannels");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_chatchannels. DB table `dbc_chatchannels` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        ChatChannelsDBC cc;
        cc.ID = id;
        cc.Flags = fields[1].GetUInt32();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            cc.Name[i] = fields[2 + i].GetString();

        _chatChannelsMap[id] = cc;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_chatchannels                  %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load ChrClasses.dbc
void DBCStoresMgr::_Load_ChrClasses()
{
    uint32 oldMSTime = getMSTime();

    _chrClassesMap.clear();
    //                                                0       1              2               3               4               5               6               7               8               9               10              11              12                   13
    QueryResult result = WorldDatabase.Query("SELECT ID, DisplayPower, Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU, SpellClassSet, CinematicSequenceID, Required_Expansion FROM dbc_chrclasses");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_chrclasses. DB table `dbc_chrclasses` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        ChrClassesDBC cc;
        cc.ID           = id;
        cc.DisplayPower = fields[1].GetUInt32();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            cc.Name[i] = fields[2 + i].GetString();

        cc.SpellClassSet       = fields[11].GetUInt32();
        cc.CinematicSequenceID = fields[12].GetUInt32();
        cc.RequiredExpansion   = fields[13].GetUInt32();

        _chrClassesMap[id] = cc;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_chrclasses                    %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load ChrRaces.dbc
void DBCStoresMgr::_Load_ChrRaces()
{
    uint32 oldMSTime = getMSTime();

    _chrRacesMap.clear();
    //                                                0    1         2          3                4               5            6               7                     8               9            10           11              12              13              14               15              16              17               18              19
    QueryResult result = WorldDatabase.Query("SELECT ID, Flags, FactionID, MaleDisplayId, FemaleDisplayId, BaseLanguage, CreatureType, ResSicknessSpellID, CinematicSequenceID, Alliance, Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU, Required_Expansion FROM dbc_chrraces");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_chrraces. DB table `dbc_chrraces` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        ChrRacesDBC cr;
        cr.ID                  = id;
        cr.Flags               = fields[1].GetUInt32();
        cr.FactionID           = fields[2].GetUInt32();
        cr.MaleDisplayID       = fields[3].GetUInt32();
        cr.FemaleDisplayID     = fields[4].GetUInt32();
        cr.BaseLanguage        = fields[5].GetUInt32();
        cr.CreatureType        = fields[6].GetUInt32();
        cr.ResSicknessSpellID  = fields[7].GetUInt32();
        cr.CinematicSequenceID = fields[8].GetUInt32();
        cr.Alliance            = fields[9].GetUInt32();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            cr.Name[i] = fields[10 + i].GetString();

        cr.RequiredExpansion   = fields[19].GetUInt32();

        _chrRacesMap[id] = cr;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_chrraces                      %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CinematicCamera.dbc
void DBCStoresMgr::_Load_CinematicCamera()
{
    uint32 oldMSTime = getMSTime();

    _cinematicCameraMap.clear();
    //                                               0     1       2        3        4         5       6
    QueryResult result = WorldDatabase.Query("SELECT ID, Model, SoundID, OriginX, OriginY, OriginZ, OriginFacing FROM dbc_cinematiccamera");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_cinematiccamera. DB table `dbc_cinematiccamera` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        CinematicCameraDBC cc;
        cc.ID           = id;
        cc.Model        = fields[1].GetString();
        cc.SoundID      = fields[2].GetUInt32();
        cc.OriginX      = fields[3].GetFloat();
        cc.OriginY      = fields[4].GetFloat();
        cc.OriginZ      = fields[5].GetFloat();
        cc.OriginFacing = fields[6].GetFloat();

        _cinematicCameraMap[id] = cc;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_cinematiccamera               %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CinematicSequences.dbc
void DBCStoresMgr::_Load_CinematicSequences()
{
    uint32 oldMSTime = getMSTime();

    _cinematicSequencesMap.clear();
    //                                                0      1        2         3         4         5          6        7         8
    QueryResult result = WorldDatabase.Query("SELECT ID, Camera_1, Camera_2, Camera_3, Camera_4, Camera_5, Camera_6, Camera_7, Camera_8 FROM dbc_cinematicsequences");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_cinematicsequences. DB table `dbc_cinematicsequences` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        CinematicSequencesDBC cs;
        cs.ID = id;

        for (uint8 i = 0; i < 8; i++)
            cs.Camera[i] = fields[1 + i].GetUInt32();

        _cinematicSequencesMap[id] = cs;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_cinematicsequences            %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CreatureDisplayInfo.dbc
void DBCStoresMgr::_Load_CreatureDisplayInfo()
{
    uint32 oldMSTime = getMSTime();

    _creatureDisplayInfoMap.clear();
    //                                                0    1                2                     3
    QueryResult result = WorldDatabase.Query("SELECT ID, ModelID, ExtendedDisplayInfoID, CreatureModelScale FROM dbc_creaturedisplayinfo");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_creaturedisplayinfo. DB table `dbc_creaturedisplayinfo` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();        
        CreatureDisplayInfoDBC cdi;
        cdi.ID = id;
        cdi.ModelID               = fields[1].GetUInt32();
        cdi.ExtendedDisplayInfoID = fields[2].GetUInt32();
        cdi.CreatureModelScale    = fields[3].GetFloat();

        _creatureDisplayInfoMap[id] = cdi;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_creaturedisplayinfo           %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CreatureDisplayInfoExtra.dbc
void DBCStoresMgr::_Load_CreatureDisplayInfoExtra()
{
    uint32 oldMSTime = getMSTime();

    _creatureDisplayInfoExtraMap.clear();
    //                                                0       1              2
    QueryResult result = WorldDatabase.Query("SELECT ID, DisplayRaceID, DisplaySexID FROM dbc_creaturedisplayinfoextra");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_creaturedisplayinfoextra. DB table `dbc_creaturedisplayinfoextra` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        CreatureDisplayInfoExtraDBC cdie;
        cdie.ID = id;
        cdie.DisplayRaceID = fields[1].GetUInt32();
        cdie.DisplaySexID  = fields[2].GetUInt32();

        _creatureDisplayInfoExtraMap[id] = cdie;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_creaturedisplayinfoextra      %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CreatureFamily.dbc
void DBCStoresMgr::_Load_CreatureFamily()
{
    uint32 oldMSTime = getMSTime();

    _creatureFamilyMap.clear();
    //                                                0       1          2            3            4            5            6            7             8               9               10              11              12              13              14              15              16              17
    QueryResult result = WorldDatabase.Query("SELECT ID, MinScale, MinScaleLevel, MaxScale, MaxScaleLevel, SkillLine_1, SkillLine_2, PetFoodMask, PetTalentType, Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU FROM dbc_creaturefamily");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_creaturefamily. DB table `dbc_creaturefamily` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        CreatureFamilyDBC cf;
        cf.ID = id;
        cf.MinScale      = fields[1].GetFloat();
        cf.MinScaleLevel = fields[2].GetUInt32();
        cf.MaxScale      = fields[3].GetFloat();
        cf.MaxScaleLevel = fields[4].GetUInt32();
        cf.SkillLine[0]  = fields[5].GetUInt32();
        cf.SkillLine[1]  = fields[6].GetUInt32();
        cf.PetFoodMask   = fields[7].GetUInt32();
        cf.PetTalentType = fields[8].GetInt32();
        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            cf.Name[i] = fields[9 + i].GetString();

        _creatureFamilyMap[id] = cf;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_creaturefamily                %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CreatureModelData.dbc
void DBCStoresMgr::_Load_CreatureModelData()
{
    uint32 oldMSTime = getMSTime();

    _creatureModelDataMap.clear();
    //                                                0     1       2           3              4              5
    QueryResult result = WorldDatabase.Query("SELECT ID, Flags, ModelName, ModelScale, CollisionHeight, MountHeight FROM dbc_creaturemodeldata");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_creaturemodeldata. DB table `dbc_creaturemodeldata` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        CreatureModelDataDBC cmd;
        cmd.ID = id;
        cmd.Flags           = fields[1].GetUInt32();
        cmd.ModelName       = fields[2].GetString();
        cmd.ModelScale      = fields[3].GetFloat();
        cmd.CollisionHeight = fields[4].GetFloat();
        cmd.MountHeight     = fields[5].GetFloat();

        _creatureModelDataMap[id] = cmd;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_creaturemodeldata             %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CreatureSpellData.dbc
void DBCStoresMgr::_Load_CreatureSpellData()
{
    uint32 oldMSTime = getMSTime();

    _creatureSpellDataMap.clear();
    //                                                0     1         2         3         4
    QueryResult result = WorldDatabase.Query("SELECT ID, Spells_1, Spells_1, Spells_1, Spells_1 FROM dbc_creaturespelldata");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_creaturespelldata. DB table `dbc_creaturespelldata` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        CreatureSpellDataDBC csd;
        csd.ID = id;
        for (uint8 i = 0; i < MAX_CREATURE_SPELL_DATA_SLOT; i++)
            csd.Spells[i] = fields[1 + i].GetUInt32();

        _creatureSpellDataMap[id] = csd;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_creaturespelldata             %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CreatureSpellData.dbc
void DBCStoresMgr::_Load_CreatureType()
{
    uint32 oldMSTime = getMSTime();

    _creatureTypeMap.clear();
    //                                                0
    QueryResult result = WorldDatabase.Query("SELECT ID FROM dbc_creaturetype");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_creaturetype. DB table `dbc_creaturetype` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        CreatureTypeDBC ct;
        ct.ID = id;

        _creatureTypeMap[id] = ct;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_creaturetype                  %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CurrencyCategory.dbc (NOT USED)
void DBCStoresMgr::_Load_CurrencyCategory()
{
    uint32 oldMSTime = getMSTime();

    _currencyCategoryMap.clear();
    //                                                0    1           2               3               4               5               6               7               8               9               10
    QueryResult result = WorldDatabase.Query("SELECT ID, Flags,  Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU FROM dbc_currencycategory");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_currencycategory. DB table `dbc_currencycategory` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        CurrencyCategoryDBC cc;
        cc.ID = id;
        cc.Flags = fields[1].GetUInt32();
        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            cc.Name[i] = fields[2 + i].GetString();

        _currencyCategoryMap[id] = cc;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_currencycategory              %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CurrencyTypes.dbc
void DBCStoresMgr::_Load_CurrencyTypes()
{
    uint32 oldMSTime = getMSTime();

    _currencyTypesMap.clear();
    //                                                0    1        2
    QueryResult result = WorldDatabase.Query("SELECT ID, ItemID, BitIndex FROM dbc_currencytypes");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_currencytypes. DB table `dbc_currencytypes` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 itemID = fields[1].GetUInt32();
        CurrencyTypesDBC ct;
        ct.ID       = fields[0].GetUInt32();
        ct.ItemID   = itemID;
        ct.BitIndex = fields[2].GetUInt32();

        _currencyTypesMap[itemID] = ct;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_currencytypes                 %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load DestructibleModelData.dbc
void DBCStoresMgr::_Load_DestructibleModelData()
{
    uint32 oldMSTime = getMSTime();

    _destructibleModelDataMap.clear();
    //                                                0       1         2           3           4
    QueryResult result = WorldDatabase.Query("SELECT ID, State1Wmo, State2Wmo, State3Wmo, RepairGroundFx FROM dbc_destructiblemodeldata");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_destructiblemodeldata. DB table `dbc_destructiblemodeldata` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        DestructibleModelDataDBC dmd;
        dmd.ID = id;
        dmd.State1Wmo      = fields[1].GetUInt32();
        dmd.State2Wmo      = fields[2].GetUInt32();
        dmd.State3Wmo      = fields[3].GetUInt32();
        dmd.RepairGroundFx = fields[4].GetUInt32();

        _destructibleModelDataMap[id] = dmd;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_destructiblemodeldata         %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load DungeonEncounter.dbc
void DBCStoresMgr::_Load_DungeonEncounter()
{
    uint32 oldMSTime = getMSTime();

    _dungeonEncounterMap.clear();
    //                                                0     1       2        3          4               5               6               7               8               9               10               11               12
    QueryResult result = WorldDatabase.Query("SELECT ID, MapID, Difficulty, Bit, Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU FROM dbc_dungeonencounter");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_dungeonencounter. DB table `dbc_dungeonencounter` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        DungeonEncounterDBC de;
        de.ID = id;
        de.MapID      = fields[1].GetUInt32();
        de.Difficulty = fields[2].GetUInt32();
        de.Bit        = fields[3].GetUInt32();
        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            de.Name[i] = fields[4 + i].GetString();

        _dungeonEncounterMap[id] = de;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_dungeonencounter              %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load DurabilityCosts.dbc
void DBCStoresMgr::_Load_DurabilityCosts()
{
    uint32 oldMSTime = getMSTime();

    _durabilityCoastsMap.clear();
    //                                                0           1                    2                       3                    4                   5                      6                        7                   8                     9                     10                    11                        12                  13                      14                      15                  16                      17                      18                      19                     20                       21                  22                   23                   24                    25                  26                  27                  28                      29
    QueryResult result = WorldDatabase.Query("SELECT ID, WeaponSubClassCost_1, WeaponSubClassCost_2, WeaponSubClassCost_3, WeaponSubClassCost_4, WeaponSubClassCost_5, WeaponSubClassCost_6, WeaponSubClassCost_7, WeaponSubClassCost_8, WeaponSubClassCost_9, WeaponSubClassCost_10, WeaponSubClassCost_11, WeaponSubClassCost_12, WeaponSubClassCost_13, WeaponSubClassCost_14, WeaponSubClassCost_15, WeaponSubClassCost_16, WeaponSubClassCost_17, WeaponSubClassCost_18, WeaponSubClassCost_19, WeaponSubClassCost_20, WeaponSubClassCost_21, ArmorSubClassCost_1, ArmorSubClassCost_2, ArmorSubClassCost_3, ArmorSubClassCost_4, ArmorSubClassCost_5, ArmorSubClassCost_6, ArmorSubClassCost_7, ArmorSubClassCost_8 FROM dbc_durabilitycosts");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_durabilitycosts. DB table `dbc_durabilitycosts` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        DurabilityCostsDBC dc;
        dc.ID = id;
        for (uint8 i = 0; i < 21; i++)
            dc.WeaponSubClassCost[i] = fields[1 + i].GetUInt32();

        for (uint8 i = 0; i < 8; i++)
            dc.ArmorSubClassCost[i] = fields[22 + i].GetUInt32();

        _durabilityCoastsMap[id] = dc;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_durabilitycosts               %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load DurabilityQuality.dbc
void DBCStoresMgr::_Load_DurabilityQuality()
{
    uint32 oldMSTime = getMSTime();

    _durabilityQualityMap.clear();
    //                                                0   1
    QueryResult result = WorldDatabase.Query("SELECT ID, Data FROM dbc_durabilityquality");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_durabilityquality. DB table `dbc_durabilityquality` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        DurabilityQualityDBC dq;
        dq.ID = id;
        dq.Data = fields[1].GetFloat();

        _durabilityQualityMap[id] = dq;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_durabilityquality             %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load Emotes.dbc
void DBCStoresMgr::_Load_Emotes()
{
    uint32 oldMSTime = getMSTime();

    _emotesMap.clear();
    //                                                0      1              2               3
    QueryResult result = WorldDatabase.Query("SELECT ID, EmoteFlags, EmoteSpecProc, EmoteSpecProcParam FROM dbc_emotes");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_emotes. DB table `dbc_emotes` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        EmotesDBC e;
        e.ID = id;
        e.EmoteFlags         = fields[1].GetUInt32();
        e.EmoteSpecProc      = fields[2].GetUInt32();
        e.EmoteSpecProcParam = fields[3].GetUInt32();

        _emotesMap[id] = e;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_emotes                        %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load EmotesText.dbc
void DBCStoresMgr::_Load_EmotesText()
{
    uint32 oldMSTime = getMSTime();

    _emotesTextMap.clear();
    //                                                0      1
    QueryResult result = WorldDatabase.Query("SELECT ID, EmoteID FROM dbc_emotestext");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_emotestext. DB table `dbc_emotestext` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        EmotesTextDBC et;
        et.ID = id;
        et.EmoteID = fields[1].GetUInt32();

        _emotesTextMap[id] = et;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_emotestext                    %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load EmotesTextSound.dbc
void DBCStoresMgr::_Load_EmotesTextSound()
{
    uint32 oldMSTime = getMSTime();

    _emotesTextSoundMap.clear();
    //                                                0      1            2      3       4
    QueryResult result = WorldDatabase.Query("SELECT ID, EmotesTextID, RaceID, SexID, SoundID FROM dbc_emotestextsound");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_emotestextsound. DB table `dbc_emotestextsound` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        EmotesTextSoundDBC ets;
        ets.ID = id;
        ets.EmotesTextID = fields[1].GetUInt32();
        ets.RaceID       = fields[2].GetUInt8();
        ets.SexID        = fields[3].GetUInt8();
        ets.SoundID      = fields[4].GetUInt32();

        _emotesTextSoundMap[id] = ets;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_emotestextsound               %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load Faction.dbc
void DBCStoresMgr::_Load_Faction()
{
    uint32 oldMSTime = getMSTime();

    _factionMap.clear();
    //                                                0          1                  2                    3                    4                     5                       6                       7                     8                     9                   10                  11                12               13               14                    15                16                17                18                  19                  20                  21               22                  23               24              25             26             27                28               29           30                31
    QueryResult result = WorldDatabase.Query("SELECT ID, ReputationIndex, ReputationRaceMask_1, ReputationRaceMask_2, ReputationRaceMask_3, ReputationRaceMask_4, ReputationClassMask_1, ReputationClassMask_2, ReputationClassMask_3, ReputationClassMask_4, ReputationBase_1, ReputationBase_2, ReputationBase_3, ReputationBase_4, ReputationFlags_1, ReputationFlags_2, ReputationFlags_3, ReputationFlags_4, ParentFactionID, ParentFactionMod_1, ParentFactionMod_2, ParentFactionCap_1, ParentFactionCap_2, Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU FROM dbc_faction");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_faction. DB table `dbc_faction` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        FactionDBC f;
        f.ID = id;
        f.ReputationIndex = fields[1].GetInt32();
        for (uint8 i = 0; i < 4; i++)
            f.ReputationRaceMask[i] = fields[2 + i].GetUInt32();
        for (uint8 i = 0; i < 4; i++)
            f.ReputationClassMask[i] = fields[6 + i].GetUInt32();
        for (uint8 i = 0; i < 4; i++)
            f.ReputationBase[i] = fields[10 + i].GetInt32();
        for (uint8 i = 0; i < 4; i++)
            f.ReputationFlags[i] = fields[14 + i].GetUInt32();

        f.ParentFactionID = fields[18].GetInt32();

        for (uint8 i = 0; i < 2; i++)
            f.ParentFactionMod[i] = fields[19 + i].GetFloat();

        for (uint8 i = 0; i < 2; i++)
            f.ParentFactionCap[i] = fields[21 + i].GetUInt32();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            f.Name[i] = fields[23 + i].GetString();

        _factionMap[id] = f;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_faction                       %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load FactionTemplate.dbc
void DBCStoresMgr::_Load_FactionTemplate()
{
    uint32 oldMSTime = getMSTime();

    _factionTemplateMap.clear();
    //                                                0     1       2         3             4            5          6           7         8         9          10        11        12         13
    QueryResult result = WorldDatabase.Query("SELECT ID, Faction, Flags, FactionGroup, FriendGroup, EnemyGroup, Enemies_1, Enemies_2, Enemies_3, Enemies_4, Friend_1, Friend_2, Friend_3, Friend_4  FROM dbc_factiontemplate");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_factiontemplate. DB table `dbc_factiontemplate` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        FactionTemplateDBC ft;
        ft.ID = id;
        ft.Faction      = fields[1].GetUInt32();
        ft.Flags        = fields[2].GetUInt32();
        ft.FactionGroup = fields[3].GetUInt32();
        ft.FriendGroup  = fields[4].GetUInt32();
        ft.EnemyGroup   = fields[5].GetUInt32();
        for (uint8 i = 0; i < MAX_FACTION_RELATIONS; i++)
            ft.Enemies[i] = fields[6 + i].GetUInt32();
        for (uint8 i = 0; i < MAX_FACTION_RELATIONS; i++)
            ft.Friend[i] = fields[10 + i].GetUInt32();

        _factionTemplateMap[id] = ft;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_factiontemplate               %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load GameObjectArtKit.dbc
void DBCStoresMgr::_Load_GameObjectArtKit()
{
    uint32 oldMSTime = getMSTime();

    _gameobjectArtKitMap.clear();
    //                                                0
    QueryResult result = WorldDatabase.Query("SELECT ID FROM dbc_gameobjectartkit");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gameobjectartkit. DB table `dbc_gameobjectartkit` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GameObjectArtKitDBC gak;
        gak.ID = id;

        _gameobjectArtKitMap[id] = gak;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_gameobjectartkit              %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load GameObjectDisplayInfo.dbc
void DBCStoresMgr::_Load_GameObjectDisplayInfo()
{
    uint32 oldMSTime = getMSTime();

    _gameobjectDisplayInfoMap.clear();
    //                                                0     1           2           3           4            5          6            7
    QueryResult result = WorldDatabase.Query("SELECT ID, ModelName, GeoBoxMinX, GeoBoxMinY, GeoBoxMinZ, GeoBoxMaxX, GeoBoxMaxY, GeoBoxMaxZ FROM dbc_gameobjectdisplayinfo");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gameobjectdisplayinfo. DB table `dbc_gameobjectdisplayinfo` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GameObjectDisplayInfoDBC gdi;
        gdi.ID = id;
        gdi.ModelName   = fields[1].GetString();
        gdi.GeoBoxMin.X = fields[2].GetFloat();
        gdi.GeoBoxMin.Y = fields[3].GetFloat();
        gdi.GeoBoxMin.Z = fields[4].GetFloat();
        gdi.GeoBoxMax.X = fields[5].GetFloat();
        gdi.GeoBoxMax.Y = fields[6].GetFloat();
        gdi.GeoBoxMax.Z = fields[7].GetFloat();

        _gameobjectDisplayInfoMap[id] = gdi;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_gameobjectdisplayinfo         %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load GemProperties.dbc
void DBCStoresMgr::_Load_GemProperties()
{
    uint32 oldMSTime = getMSTime();

    _gemPropertiesMap.clear();
    //                                                0     1          2
    QueryResult result = WorldDatabase.Query("SELECT ID, Enchant_Id, Type FROM dbc_gemproperties");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gemproperties. DB table `dbc_gemproperties` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GemPropertiesDBC gp;
        gp.ID = id;
        gp.EnchantID = fields[1].GetUInt32();
        gp.Type      = fields[2].GetUInt32();

        _gemPropertiesMap[id] = gp;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_gemproperties                 %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load GlyphProperties.dbc
void DBCStoresMgr::_Load_GlyphProperties()
{
    uint32 oldMSTime = getMSTime();

    _glyphPropertiesMap.clear();
    //                                                0     1          2                3
    QueryResult result = WorldDatabase.Query("SELECT ID, SpellID, GlyphSlotFlags, SpellIconID FROM dbc_glyphproperties");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_glyphproperties. DB table `dbc_glyphproperties` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GlyphPropertiesDBC gp;
        gp.ID = id;
        gp.SpellID        = fields[1].GetUInt32();
        gp.GlyphSlotFlags = fields[2].GetUInt32();
        gp.SpellIconID    = fields[3].GetUInt32();

        _glyphPropertiesMap[id] = gp;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_glyphproperties               %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load GlyphSlot.dbc
void DBCStoresMgr::_Load_GlyphSlot()
{
    uint32 oldMSTime = getMSTime();

    _glyphSlotMap.clear();
    //                                                0     1     2
    QueryResult result = WorldDatabase.Query("SELECT ID, Type, Tooltip FROM dbc_glyphslot");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_glyphslot. DB table `dbc_glyphslot` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GlyphSlotDBC gs;
        gs.ID = id;
        gs.Type    = fields[1].GetUInt32();
        gs.Tooltip = fields[2].GetUInt32();

        _glyphSlotMap[id] = gs;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_glyphslot                     %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load gtBarberShopCostBase.dbc
void DBCStoresMgr::_Load_gtBarberShopCostBase()
{
    uint32 oldMSTime = getMSTime();

    _gtBarberShopCostBaseMap.clear();
    //                                                0   1
    QueryResult result = WorldDatabase.Query("SELECT ID, Data FROM dbc_gtbarbershopcostbase");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gtbarbershopcostbase. DB table `dbc_gtbarbershopcostbase` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GtBarberShopCostBaseDBC gtbsc;
        gtbsc.ID = id;
        gtbsc.Data = fields[1].GetFloat();

        _gtBarberShopCostBaseMap[id] = gtbsc;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_gtbarbershopcostbase          %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load gtCombatRatings.dbc
void DBCStoresMgr::_Load_gtCombatRatings()
{
    uint32 oldMSTime = getMSTime();

    _gtCombatRatingsMap.clear();
    //                                                0   1
    QueryResult result = WorldDatabase.Query("SELECT ID, Data FROM dbc_gtcombatratings");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gtcombatratings. DB table `dbc_gtcombatratings` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GtCombatRatingsDBC gtcr;
        gtcr.ID = id;
        gtcr.Data = fields[1].GetFloat();

        _gtCombatRatingsMap[id] = gtcr;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_gtcombatratings               %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load gtChanceToMeleeCritBase.dbc
void DBCStoresMgr::_Load_gtChanceToMeleeCritBase()
{
    uint32 oldMSTime = getMSTime();

    _gtChanceToMeleeCritBaseMap.clear();
    //                                                0   1
    QueryResult result = WorldDatabase.Query("SELECT ID, Data FROM dbc_gtchancetomeleecritbase");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gtchancetomeleecritbase. DB table `dbc_gtchancetomeleecritbase` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GtChanceToMeleeCritBaseDBC gtcmcb;
        gtcmcb.ID = id;
        gtcmcb.Data = fields[1].GetFloat();

        _gtChanceToMeleeCritBaseMap[id] = gtcmcb;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_gtchancetomeleecritbase       %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load gtChanceToMeleeCrit.dbc
void DBCStoresMgr::_Load_gtChanceToMeleeCrit()
{
    uint32 oldMSTime = getMSTime();

    _gtChanceToMeleeCritMap.clear();
    //                                                0   1
    QueryResult result = WorldDatabase.Query("SELECT ID, Data FROM dbc_gtchancetomeleecrit");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gtchancetomeleecrit. DB table `dbc_gtchancetomeleecrit` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GtChanceToMeleeCritDBC gtcmc;
        gtcmc.ID = id;
        gtcmc.Data = fields[1].GetFloat();

        _gtChanceToMeleeCritMap[id] = gtcmc;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_gtchancetomeleecrit           %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load gtChanceToSpellCritBase.dbc
void DBCStoresMgr::_Load_gtChanceToSpellCritBase()
{
    uint32 oldMSTime = getMSTime();

    _gtChanceToSpellCritBaseMap.clear();
    //                                                0   1
    QueryResult result = WorldDatabase.Query("SELECT ID, Data FROM dbc_gtchancetospellcritbase");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gtchancetospellcritbase. DB table `dbc_gtchancetospellcritbase` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GtChanceToSpellCritBaseDBC gtcscb;
        gtcscb.ID = id;
        gtcscb.Data = fields[1].GetFloat();

        _gtChanceToSpellCritBaseMap[id] = gtcscb;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_gtchancetospellcritbase       %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load gtChanceToSpellCrit.dbc
void DBCStoresMgr::_Load_gtChanceToSpellCrit()
{
    uint32 oldMSTime = getMSTime();

    _gtChanceToSpellCritMap.clear();
    //                                                0   1
    QueryResult result = WorldDatabase.Query("SELECT ID, Data FROM dbc_gtchancetospellcrit");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gtchancetospellcrit. DB table `dbc_gtchancetospellcrit` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GtChanceToSpellCritDBC gtcsc;
        gtcsc.ID = id;
        gtcsc.Data = fields[1].GetFloat();

        _gtChanceToSpellCritMap[id] = gtcsc;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_gtchancetospellcrit           %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load gtNPCManaCostScaler.dbc
void DBCStoresMgr::_Load_gtNPCManaCostScaler()
{
    uint32 oldMSTime = getMSTime();

    _gtNPCManaCostScalerMap.clear();
    //                                                0   1
    QueryResult result = WorldDatabase.Query("SELECT ID, Data FROM dbc_gtnpcmanacostscaler");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gtnpcmanacostscaler. DB table `dbc_gtnpcmanacostscaler` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GtNPCManaCostScalerDBC gtnpcMCS;
        gtnpcMCS.ID = id;
        gtnpcMCS.Data = fields[1].GetFloat();

        _gtNPCManaCostScalerMap[id] = gtnpcMCS;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_gtnpcmanacostscaler           %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load gtOCTClassCombatRatingScalar.dbc
void DBCStoresMgr::_Load_gtOCTClassCombatRatingScalar()
{
    uint32 oldMSTime = getMSTime();

    _gtOCTClassCombatRatingScalarMap.clear();
    //                                                0   1
    QueryResult result = WorldDatabase.Query("SELECT ID, Data FROM dbc_gtoctclasscombatratingscalar");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gtoctclasscombatratingscalar. DB table `dbc_gtoctclasscombatratingscalar` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GtOCTClassCombatRatingScalarDBC gtOCTccrs;
        gtOCTccrs.ID = id;
        gtOCTccrs.Data = fields[1].GetFloat();

        _gtOCTClassCombatRatingScalarMap[id] = gtOCTccrs;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_gtoctclasscombatratingscalar  %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load gtOCTRegenHP.dbc
void DBCStoresMgr::_Load_gtOCTRegenHP()
{
    uint32 oldMSTime = getMSTime();

    _gtOCTRegenHPMap.clear();
    //                                                0   1
    QueryResult result = WorldDatabase.Query("SELECT ID, Data FROM dbc_gtoctregenhp");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gtoctregenhp. DB table `dbc_gtoctregenhp` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GtOCTRegenHPDBC gtOCTrhp;
        gtOCTrhp.ID = id;
        gtOCTrhp.Data = fields[1].GetFloat();

        _gtOCTRegenHPMap[id] = gtOCTrhp;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_gtoctregenhp                  %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load gtOCTRegenMP.dbc
void DBCStoresMgr::_Load_gtOCTRegenMP()
{
    uint32 oldMSTime = getMSTime();

    _gtOCTRegenMPMap.clear();
    //                                                0   1
    QueryResult result = WorldDatabase.Query("SELECT ID, Data FROM dbc_gtoctregenmp");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gtoctregenmp. DB table `dbc_gtoctregenmp` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GtOCTRegenMPDBC gtOCTrmp;
        gtOCTrmp.ID = id;
        gtOCTrmp.Data = fields[1].GetFloat();

        _gtOCTRegenMPMap[id] = gtOCTrmp;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_gtoctregenmp                  %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load gtRegenHPPerSpt.dbc
void DBCStoresMgr::_Load_gtRegenHPPerSpt()
{
    uint32 oldMSTime = getMSTime();

    _gtRegenHPPerSptMap.clear();
    //                                                0   1
    QueryResult result = WorldDatabase.Query("SELECT ID, Data FROM dbc_gtregenhpperspt");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gtregenhpperspt. DB table `dbc_gtregenhpperspt` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GtRegenHPPerSptDBC gtrhpps;
        gtrhpps.ID = id;
        gtrhpps.Data = fields[1].GetFloat();

        _gtRegenHPPerSptMap[id] = gtrhpps;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_gtregenhpperspt               %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load gtRegenMPPerSpt.dbc
void DBCStoresMgr::_Load_gtRegenMPPerSpt()
{
    uint32 oldMSTime = getMSTime();

    _gtRegenMPPerSptMap.clear();
    //                                                0   1
    QueryResult result = WorldDatabase.Query("SELECT ID, Data FROM dbc_gtregenmpperspt");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_gtregenmpperspt. DB table `dbc_gtregenmpperspt` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        GtRegenMPPerSptDBC gtrmpps;
        gtrmpps.ID = id;
        gtrmpps.Data = fields[1].GetFloat();

        _gtRegenMPPerSptMap[id] = gtrmpps;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_gtregenmpperspt               %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load Holidays.dbc
void DBCStoresMgr::_Load_Holidays()
{
    uint32 oldMSTime = getMSTime();

    _holidaysMap.clear();
    //                                                0      1           2           3           4           5           6           7           8            9         10         11       12      13      14      15      16      17      18      19      20      21        22        23      24        25      26        27      28        29      30        31      32        33       34       35      36       37       38          39                 40             41              42                  43             44               45              46               47                 48               49            50               51   
    QueryResult result = WorldDatabase.Query("SELECT ID, Duration_1, Duration_2, Duration_3, Duration_4, Duration_5, Duration_6, Duration_7, Duration_8, Duration_9, Duration_10, Date_1, Date_2, Date_3, Date_4, Date_5, Date_6, Date_7, Date_8, Date_9, Date_10, Date_11, Date_12, Date_13, Date_14, Date_15, Date_16, Date_17, Date_18, Date_19, Date_20, Date_21, Date_22, Date_23, Date_24, Date_25, Date_26, Region, Looping, CalendarFlags_1, CalendarFlags_2, CalendarFlags_3, CalendarFlags_4, CalendarFlags_5, CalendarFlags_6, CalendarFlags_7, CalendarFlags_8, CalendarFlags_9, CalendarFlags_10, TextureFilename, Priority, CalendarFilterType FROM dbc_holidays");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_holidays. DB table `dbc_holidays` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        HolidaysDBC h;
        h.ID = id;
        for (uint8 i = 0; i < MAX_HOLIDAY_DURATIONS; i++)
            h.Duration[i] = fields[1 + i].GetUInt32();
        for (uint8 i = 0; i < MAX_HOLIDAY_DATES; i++)
            h.Date[i] = fields[11 + i].GetUInt32();
        h.Region  = fields[37].GetUInt32();
        h.Looping = fields[38].GetUInt32();
        for (uint8 i = 0; i < MAX_HOLIDAY_FLAGS; i++)
            h.CalendarFlags[i] = fields[39 + i].GetUInt32();
        h.TextureFilename    = fields[49].GetString();
        h.Priority           = fields[50].GetUInt32();
        h.CalendarFilterType = fields[51].GetInt32();

        _holidaysMap[id] = h;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_holidays                      %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load Item.dbc
void DBCStoresMgr::_Load_Item()
{
    uint32 oldMSTime = getMSTime();

    _itemMap.clear();
    //                                                0      1          2               3                   4            5              6             7
    QueryResult result = WorldDatabase.Query("SELECT ID, ClassID, SubclassID, Sound_Override_Subclassid, Material, DisplayInfoID, InventoryType, SheatheType FROM dbc_item");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_item. DB table `dbc_item` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        ItemDBC i;
        i.ID = id;
        i.ClassID                 = fields[1].GetUInt32();
        i.SubclassID              = fields[2].GetUInt32();
        i.SoundOverrideSubclassID = fields[3].GetInt32();
        i.Material                = fields[4].GetInt32();
        i.DisplayInfoID           = fields[5].GetUInt32();
        i.InventoryType           = fields[6].GetUInt32();
        i.SheatheType             = fields[7].GetUInt32();

        _itemMap[id] = i;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_item                          %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load ItemBagFamily.dbc
void DBCStoresMgr::_Load_ItemBagFamily()
{
    uint32 oldMSTime = getMSTime();

    _itemBagFamilyMap.clear();
    //                                                0
    QueryResult result = WorldDatabase.Query("SELECT ID FROM dbc_itembagfamily");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_itembagfamily. DB table `dbc_itembagfamily` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        ItemBagFamilyDBC ibf;
        ibf.ID = id;

        _itemBagFamilyMap[id] = ibf;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_itembagfamily                 %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load ItemDisplayInfo.dbc
void DBCStoresMgr::_Load_ItemDisplayInfo()
{
    uint32 oldMSTime = getMSTime();

    _itemDisplayInfoMap.clear();
    //                                                0       1            2              3               4                5               6               7              8             9           10      11                  12              13                  14             15         16        17         18          19         20        21          22         23           24
    QueryResult result = WorldDatabase.Query("SELECT ID, ModelName_1, ModelName_2, ModelTexture_1, ModelTexture_2, InventoryIcon_1, InventoryIcon_2, GeosetGroup_1, GeosetGroup_2, GeosetGroup_3, Flags, SpellVisualID, GroupSoundIndex, HelmetGeosetVis_1, HelmetGeosetVis_2, Texture_1, Texture_2, Texture_3, Texture_4, Texture_5, Texture_6, Texture_7, Texture_8, ItemVisual, ParticleColorID FROM dbc_itemdisplayinfo");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_itemdisplayinfo. DB table `dbc_itemdisplayinfo` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        ItemDisplayInfoDBC idi;
        idi.ID = id;
        for (uint8 i = 0; i < 2; i++)
            idi.ModelName[i] = fields[1 + i].GetString();
        for (uint8 i = 0; i < 2; i++)
            idi.ModelTexture[i] = fields[3 + i].GetString();
        for (uint8 i = 0; i < 2; i++)
            idi.InventoryIcon[i] = fields[5 + i].GetString();
        for (uint8 i = 0; i < 3; i++)
            idi.GeosetGroup[i] = fields[7 + i].GetUInt32();

        idi.Flags           = fields[10].GetUInt32();
        idi.SpellVisualID   = fields[11].GetUInt32();
        idi.GroupSoundIndex = fields[12].GetUInt32();

        for (uint8 i = 0; i < 2; i++)
            idi.HelmetGeosetVisID[i] = fields[13+i].GetUInt32();
        for (uint8 i = 0; i < 8; i++)
            idi.Texture[i] = fields[15 + i].GetString();

        idi.ItemVisual      = fields[23].GetInt32();
        idi.ParticleColorID = fields[24].GetUInt32();

        _itemDisplayInfoMap[id] = idi;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_itemdisplayinfo               %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load ItemExtendedCost.dbc
void DBCStoresMgr::_Load_ItemExtendedCost()
{
    uint32 oldMSTime = getMSTime();

    _itemExtendedCostMap.clear();
    //                                                0       1            2              3          4        5         6         7         8           9           10           11            12          13                14
    QueryResult result = WorldDatabase.Query("SELECT ID, HonorPoints, ArenaPoints, ArenaBracket, ItemID_1, ItemID_2, ItemID_3, ItemID_4, ItemID_5, ItemCount_1, ItemCount_2, ItemCount_3, ItemCount_4, ItemCount_5, RequiredArenaRating FROM dbc_itemextendedcost");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_itemextendedcost. DB table `dbc_itemextendedcost` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        ItemExtendedCostDBC iec;
        iec.ID = id;
        iec.HonorPoints = fields[1].GetUInt32();
        iec.ArenaPoints = fields[2].GetUInt32();
        iec.ArenaBracket = fields[3].GetUInt32();
        for (uint8 i = 0; i < MAX_ITEM_EXTENDED_COST_REQUIREMENTS; i++)
            iec.ItemID[i] = fields[4 + i].GetUInt32();
        for (uint8 i = 0; i < MAX_ITEM_EXTENDED_COST_REQUIREMENTS; i++)
            iec.ItemCount[i] = fields[10 + i].GetUInt32();
        iec.RequiredArenaRating = fields[14].GetUInt32();

        _itemExtendedCostMap[id] = iec;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_itemextendedcost              %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load ItemLimitCategory.dbc
void DBCStoresMgr::_Load_ItemLimitCategory()
{
    uint32 oldMSTime = getMSTime();

    _itemLimitCategoryMap.clear();
    //                                                0     1        2
    QueryResult result = WorldDatabase.Query("SELECT ID, Quantity, Flags FROM dbc_itemlimitcategory");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_itemlimitcategory. DB table `dbc_itemlimitcategory` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        ItemLimitCategoryDBC ilc;
        ilc.ID = id;
        ilc.Quantity = fields[1].GetUInt32();
        ilc.Flags    = fields[2].GetUInt32();

        _itemLimitCategoryMap[id] = ilc;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_itemlimitcategory             %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load ItemRandomProperties.dbc
void DBCStoresMgr::_Load_ItemRandomProperties()
{
    uint32 oldMSTime = getMSTime();

    _itemRandomPropertiesMap.clear();
    //                                                0       1              2              3                4              5               6               7               8               9               10              11              12
    QueryResult result = WorldDatabase.Query("SELECT ID, Enchantment_1, Enchantment_2, Enchantment_3, Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU FROM dbc_itemrandomproperties");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_itemrandomproperties. DB table `dbc_itemrandomproperties` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        ItemRandomPropertiesDBC irp;
        irp.ID = id;
        for (uint8 i = 0; i < MAX_ITEM_ENCHANTMENT_EFFECTS; i++)
            irp.Enchantment[i] = fields[1 + i].GetUInt32();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            irp.Name[i] = fields[4 + i].GetString();

        _itemRandomPropertiesMap[id] = irp;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_itemrandomproperties          %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load ItemRandomSuffix.dbc
void DBCStoresMgr::_Load_ItemRandomSuffix()
{
    uint32 oldMSTime = getMSTime();

    _itemRandomSuffixMap.clear();
    //                                                0          1              2              3                4              5               6               7               8               9                10           11             12              13              14                15
    QueryResult result = WorldDatabase.Query("SELECT ID, Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU, Enchantment_1, Enchantment_2, Enchantment_3, AllocationPct_1, AllocationPct_2, AllocationPct_3 FROM dbc_itemrandomsuffix");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_itemrandomsuffix. DB table `dbc_itemrandomsuffix` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        ItemRandomSuffixDBC irs;
        irs.ID = id;
        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            irs.Name[i] = fields[1 + i].GetString();

        for (uint8 i = 0; i < MAX_ITEM_ENCHANTMENT_EFFECTS; i++)
            irs.Enchantment[i] = fields[10 + i].GetUInt32();

        for (uint8 i = 0; i < MAX_ITEM_ENCHANTMENT_EFFECTS; i++)
            irs.AllocationPct[i] = fields[13 + i].GetUInt32();

        _itemRandomSuffixMap[id] = irs;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_itemrandomsuffix              %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load ItemSet.dbc
void DBCStoresMgr::_Load_ItemSet()
{
    uint32 oldMSTime = getMSTime();

    _itemSetMap.clear();
    //                                                0          1              2              3                4              5               6               7               8               9            10        11        12        13        14        15        16        17        18        19           20             21             22             23          24            25           26            27             28             29             30                31              32              33              34              35              36              37
    QueryResult result = WorldDatabase.Query("SELECT ID, Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU, ItemID_1, ItemID_2, ItemID_3, ItemID_4, ItemID_5, ItemID_6, ItemID_7, ItemID_8, ItemID_9, ItemID_10, SetSpellID_1, SetSpellID_2, SetSpellID_3, SetSpellID_4, SetSpellID_5, SetSpellID_6, SetSpellID_7, SetSpellID_8, SetThreshold_1, SetThreshold_2, SetThreshold_3, SetThreshold_4, SetThreshold_5, SetThreshold_6, SetThreshold_7, SetThreshold_8, RequiredSkill, RequiredSkillRank FROM dbc_itemset");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_itemset. DB table `dbc_itemset` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        ItemSetDBC is;
        is.ID = id;
        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            is.Name[i] = fields[1 + i].GetString();

        for (uint8 i = 0; i < MAX_ITEM_SET_ITEMS; i++)
            is.ItemID[i] = fields[10 + i].GetUInt32();

        for (uint8 i = 0; i < MAX_ITEM_SET_SPELLS; i++)
            is.SetSpellID[i] = fields[20 + i].GetUInt32();

        for (uint8 i = 0; i < MAX_ITEM_SET_SPELLS; i++)
            is.SetThreshold[i] = fields[28 + i].GetUInt32();

        is.RequiredSkill     = fields[36].GetUInt32();
        is.RequiredSkillRank = fields[37].GetUInt32();

        _itemSetMap[id] = is;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded dbc_itemset                       %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load LFGDungeons.dbc
void DBCStoresMgr::_Load_LFGDungeons()
{
    uint32 oldMSTime = getMSTime();

    _lfgDungeonMap.clear();
    //                                                0          1              2              3                4              5               6               7               8               9            10        11          12             13                 14          15        16        17     18        19           20
    QueryResult result = WorldDatabase.Query("SELECT ID, Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU, MinLevel, MaxLevel, Target_Level, Target_Level_Min, Target_Level_Max, MapID, Difficulty, Flags, TypeID, ExpansionLevel, Group_Id FROM dbc_lfgdungeons");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_lfgdungeons. DB table `dbc_lfgdungeons` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        LFGDungeonDBC ld;
        ld.ID = id;
        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            ld.Name[i] = fields[1 + i].GetString();

        ld.MinLevel       = fields[10].GetUInt32();
        ld.MaxLevel       = fields[11].GetUInt32();
        ld.TargetLevel    = fields[12].GetUInt32();
        ld.TargetLevelMin = fields[13].GetUInt32();
        ld.TargetLevelMax = fields[14].GetUInt32();
        ld.MapID          = fields[15].GetInt32();
        ld.Difficulty     = fields[16].GetUInt32();
        ld.Flags          = fields[17].GetUInt32();
        ld.TypeID         = fields[18].GetUInt32();
        ld.ExpansionLevel = fields[19].GetUInt32();
        ld.GroupID        = fields[20].GetUInt32();

        _lfgDungeonMap[id] = ld;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_lfgdungeons                   %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load Light.dbc
void DBCStoresMgr::_Load_Light()
{
    uint32 oldMSTime = getMSTime();

    _lightMap.clear();
    //                                                0        1      2  3  4
    QueryResult result = WorldDatabase.Query("SELECT ID, ContinentID, X, Y, Z FROM dbc_light");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_light. DB table `dbc_light` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        LightDBC l;
        l.ID = id;
        l.ContinentID  = fields[1].GetUInt32();
        l.GameCoords.X = fields[2].GetFloat();
        l.GameCoords.Y = fields[3].GetFloat();
        l.GameCoords.Z = fields[4].GetFloat();

        _lightMap[id] = l;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_light                         %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load LiquidType.dbc
void DBCStoresMgr::_Load_LiquidType()
{
    uint32 oldMSTime = getMSTime();

    _liquidTypeMap.clear();
    //                                                0    1      2
    QueryResult result = WorldDatabase.Query("SELECT ID, Type, SpellID FROM dbc_liquidtype");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_liquidtype. DB table `dbc_liquidtype` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        LiquidTypeDBC lt;
        lt.ID = id;
        lt.SoundBank = fields[1].GetUInt32();
        lt.SpellID   = fields[2].GetUInt32();

        _liquidTypeMap[id] = lt;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_liquidtype                    %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load Lock.dbc
void DBCStoresMgr::_Load_Lock()
{
    uint32 oldMSTime = getMSTime();

    _lockMap.clear();
    //                                                0    1      2         3        4      5       6       7       8       9       10       11         12      13      14        15        16      17      18       19       20        21      22       23       24
    QueryResult result = WorldDatabase.Query("SELECT ID, Type_1, Type_2, Type_3, Type_4, Type_5, Type_6, Type_7, Type_8, Index_1, Index_2, Index_3, Index_4, Index_5, Index_6, Index_7, Index_8, Skill_1, Skill_2, Skill_3, Skill_4, Skill_5, Skill_6, Skill_7, Skill_8 FROM dbc_lock");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_lock. DB table `dbc_lock` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        LockDBC l;
        l.ID = id;
        for (uint8 i = 0; i < MAX_LOCK_CASE; i++)
            l.Type[i] = fields[1 + i].GetUInt32();

        for (uint8 i = 0; i < MAX_LOCK_CASE; i++)
            l.Index[i] = fields[9 + i].GetUInt32();

        for (uint8 i = 0; i < MAX_LOCK_CASE; i++)
            l.Skill[i] = fields[17 + i].GetUInt32();

        _lockMap[id] = l;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_lock                          %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load MailTemplate.dbc
void DBCStoresMgr::_Load_MailTemplate()
{
    uint32 oldMSTime = getMSTime();

    _mailTemplateMap.clear();
    //                                                0         1               2               3               4               5               6               7               8               9
    QueryResult result = WorldDatabase.Query("SELECT ID, Body_Lang_enUS, Body_Lang_koKR, Body_Lang_frFR, Body_Lang_deDE, Body_Lang_zhCN, Body_Lang_zhTW, Body_Lang_esES, Body_Lang_esMX, Body_Lang_ruRU FROM dbc_mailtemplate");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_mailtemplate. DB table `dbc_mailtemplate` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        MailTemplateDBC mt;
        mt.ID = id;
        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            mt.Body[i] = fields[1 + i].GetString();

        _mailTemplateMap[id] = mt;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_mailtemplate                  %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load Map.dbc
void DBCStoresMgr::_Load_Map()
{
    uint32 oldMSTime = getMSTime();

    _mapMap.clear();
    //                                                0         1         2            3                  4               5                   6                   7                  8                  9                10                    11             12           13              14          15       16         17          18           19
    QueryResult result = WorldDatabase.Query("SELECT ID, InstanceType, Flags, MapName_Lang_enUS, MapName_Lang_koKR, MapName_Lang_frFR, MapName_Lang_deDE, MapName_Lang_zhCN, MapName_Lang_zhTW, MapName_Lang_esES, MapName_Lang_esMX, MapName_Lang_ruRU, AreaTableID, LoadingScreenID, CorpseMapID, CorpseX, CorpseY, ExpansionID, RaidOffset, MaxPlayers FROM dbc_map");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_map. DB table `dbc_map` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        MapDBC m;
        m.ID = id;
        m.InstanceType = fields[1].GetUInt32();
        m.Flags        = fields[2].GetUInt32();
        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            m.MapName[i] = fields[3 + i].GetString();

        m.AreaTableID     = fields[12].GetUInt32();
        m.LoadingScreenID = fields[13].GetUInt32();
        m.CorpseMapID     = fields[14].GetInt32();
        m.Corpse.X        = fields[15].GetFloat();
        m.Corpse.Y        = fields[16].GetFloat();
        m.ExpansionID     = fields[17].GetUInt32();
        m.RaidOffset      = fields[18].GetUInt32();
        m.MaxPlayers      = fields[19].GetUInt32();

        _mapMap[id] = m;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_map                           %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load MapDifficulty.dbc
void DBCStoresMgr::_Load_MapDifficulty()
{
    uint32 oldMSTime = getMSTime();

    _mapDifficultyMap.clear();
    //                                                0    1        2                3                  4                  5                   6                   7                 8                  9                  10               11              12          13
    QueryResult result = WorldDatabase.Query("SELECT ID, MapID, Difficulty,  Message_Lang_enUS, Message_Lang_koKR, Message_Lang_frFR, Message_Lang_deDE, Message_Lang_zhCN, Message_Lang_zhTW, Message_Lang_esES, Message_Lang_esMX, Message_Lang_ruRU, RaidDuration, MaxPlayers FROM dbc_mapdifficulty");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_mapdifficulty. DB table `dbc_mapdifficulty` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        MapDifficultyDBC md;
        md.ID = id;
        md.MapID      = fields[1].GetUInt32();
        md.Difficulty = fields[2].GetUInt32();
        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            md.Message[i] = fields[3 + i].GetString();

        md.RaidDuration = fields[12].GetUInt32();
        md.MaxPlayers   = fields[13].GetUInt32();

        _mapDifficultyMap[id] = md;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_mapdifficulty                 %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load Movie.dbc
void DBCStoresMgr::_Load_Movie()
{
    uint32 oldMSTime = getMSTime();

    _movieMap.clear();
    //                                                0
    QueryResult result = WorldDatabase.Query("SELECT ID FROM dbc_movie");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_movie. DB table `dbc_movie` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        MovieDBC m;
        m.ID = id;

        _movieMap[id] = m;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_movie                         %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load NamesProfanity.dbc
void DBCStoresMgr::_Load_NamesProfanity()
{
    uint32 oldMSTime = getMSTime();

    _namesProfanityMap.clear();
    //                                                0    1       2
    QueryResult result = WorldDatabase.Query("SELECT ID, Name, Language FROM dbc_namesprofanity");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_namesprofanity. DB table `dbc_namesprofanity` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        NamesProfanityDBC np;
        np.ID = id;
        np.Name     = fields[1].GetString();
        np.Language = fields[2].GetInt32();

        _namesProfanityMap[id] = np;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_namesprofanity                %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));

    // Separate namesprofanity for languages
    for (NamesProfanityDBCMap::const_iterator itr = _namesProfanityMap.begin(); itr != _namesProfanityMap.end(); ++itr)
    {
        ASSERT(itr->second.Language < TOTAL_LOCALES || itr->second.Language == -1);
        std::wstring wname;
        bool conversionResult = Utf8toWStr(itr->second.Name, wname);
        ASSERT(conversionResult);

        if (itr->second.Language != -1)
            NamesProfaneValidators[itr->second.Language].emplace_back(wname, Trinity::regex::perl | Trinity::regex::icase | Trinity::regex::optimize);
        else
            for (uint32 i = 0; i < TOTAL_LOCALES; ++i)
                NamesProfaneValidators[i].emplace_back(wname, Trinity::regex::perl | Trinity::regex::icase | Trinity::regex::optimize);
    }

    // clear this datamap (UNUSED)
    _namesProfanityMap.clear();
}

// load NamesReserved.dbc
void DBCStoresMgr::_Load_NamesReserved()
{
    uint32 oldMSTime = getMSTime();

    _namesReservedMap.clear();
    //                                                0    1       2
    QueryResult result = WorldDatabase.Query("SELECT ID, Name, Language FROM dbc_namesreserved");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_namesreserved. DB table `dbc_namesreserved` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        NamesReservedDBC nr;
        nr.ID = id;
        nr.Name = fields[1].GetString();
        nr.Language = fields[2].GetInt32();

        _namesReservedMap[id] = nr;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_namesreserved                 %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));

    // Separate namesreserved for languages
    for (NamesReservedDBCMap::const_iterator itr = _namesReservedMap.begin(); itr != _namesReservedMap.end(); ++itr)
    {
        ASSERT(itr->second.Language < TOTAL_LOCALES || itr->second.Language == -1);
        std::wstring wname;
        bool conversionResult = Utf8toWStr(itr->second.Name, wname);
        ASSERT(conversionResult);

        if (itr->second.Language != -1)
            NamesReservedValidators[itr->second.Language].emplace_back(wname, Trinity::regex::perl | Trinity::regex::icase | Trinity::regex::optimize);
        else
            for (uint32 i = 0; i < TOTAL_LOCALES; ++i)
                NamesReservedValidators[i].emplace_back(wname, Trinity::regex::perl | Trinity::regex::icase | Trinity::regex::optimize);
    }

    // clear this datamap (UNUSED)
    _namesReservedMap.clear();
}

// load OverrideSpellData.dbc
void DBCStoresMgr::_Load_OverrideSpellData()
{
    uint32 oldMSTime = getMSTime();

    _overrideSpellDataMap.clear();
    //                                                0     1          2        3         4         5         6         7           8       9         10
    QueryResult result = WorldDatabase.Query("SELECT ID, Spells_1, Spells_2, Spells_3, Spells_4, Spells_5, Spells_6, Spells_7, Spells_8, Spells_9, Spells_10 FROM dbc_overridespelldata");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_overridespelldata. DB table `dbc_overridespelldata` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        OverrideSpellDataDBC osd;
        osd.ID = id;
        for (uint8 i = 0; i < MAX_OVERRIDE_SPELL; i++)
            osd.Spells[i] = fields[1 + i].GetUInt32();

        _overrideSpellDataMap[id] = osd;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_overridespelldata             %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load PowerDisplay.dbc
void DBCStoresMgr::_Load_PowerDisplay()
{
    uint32 oldMSTime = getMSTime();

    _powerDisplayMap.clear();
    //                                                0     1
    QueryResult result = WorldDatabase.Query("SELECT ID, ActualType FROM dbc_powerdisplay");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_powerdisplay. DB table `dbc_powerdisplay` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        PowerDisplayDBC pd;
        pd.ID = id;
        pd.ActualType = fields[1].GetUInt32();

        _powerDisplayMap[id] = pd;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_powerdisplay                  %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load PvpDifficulty.dbc
void DBCStoresMgr::_Load_PvpDifficulty()
{
    uint32 oldMSTime = getMSTime();

    _pvpDifficultyMap.clear();
    //                                                0     1       2           3         4         5
    QueryResult result = WorldDatabase.Query("SELECT ID, MapID, RangeIndex, MinLevel, MaxLevel, Difficulty FROM dbc_pvpdifficulty");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_pvpdifficulty. DB table `dbc_pvpdifficulty` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        PvPDifficultyDBC pd;
        pd.ID = id;
        pd.MapID      = fields[1].GetUInt32();
        pd.RangeIndex = fields[2].GetUInt32();
        pd.MinLevel   = fields[3].GetUInt32();
        pd.MaxLevel   = fields[4].GetUInt32();
        pd.Difficulty = fields[5].GetUInt32();

        ASSERT(pd.RangeIndex < MAX_BATTLEGROUND_BRACKETS, "PvpDifficulty bracket (%d) exceeded max allowed value (%d)", pd.RangeIndex, MAX_BATTLEGROUND_BRACKETS);

        _pvpDifficultyMap[id] = pd;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_pvpdifficulty                 %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load QuestSort.dbc
void DBCStoresMgr::_Load_QuestSort()
{
    uint32 oldMSTime = getMSTime();

    _questSortMap.clear();
    //                                                0
    QueryResult result = WorldDatabase.Query("SELECT ID FROM dbc_questsort");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_questsort. DB table `dbc_questsort` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        QuestSortDBC qs;
        qs.ID = id;

        _questSortMap[id] = qs;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_questsort                     %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load QuestXP.dbc
void DBCStoresMgr::_Load_QuestXP()
{
    uint32 oldMSTime = getMSTime();

    _questXPMap.clear();
    //                                                0         1           2              3            4               5           6               7           8              9            10
    QueryResult result = WorldDatabase.Query("SELECT ID, Difficulty_1, Difficulty_2, Difficulty_3, Difficulty_4, Difficulty_5, Difficulty_6, Difficulty_7, Difficulty_8, Difficulty_9, Difficulty_10 FROM dbc_questxp");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_questxp. DB table `dbc_questxp` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        QuestXPDBC qxp;
        qxp.ID = id;
        for (uint8 i = 0; i < 10; i++)
            qxp.Difficulty[i] = fields[1 + i].GetUInt32();

        _questXPMap[id] = qxp;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_questxp                       %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load QuestFactionReward.dbc
void DBCStoresMgr::_Load_QuestFactionReward()
{
    uint32 oldMSTime = getMSTime();

    _questFactionRewardMap.clear();
    //                                                0         1           2              3            4               5           6               7           8              9            10
    QueryResult result = WorldDatabase.Query("SELECT ID, Difficulty_1, Difficulty_2, Difficulty_3, Difficulty_4, Difficulty_5, Difficulty_6, Difficulty_7, Difficulty_8, Difficulty_9, Difficulty_10 FROM dbc_questfactionreward");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_questfactionreward. DB table `dbc_questfactionreward` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        QuestFactionRewardDBC qfr;
        qfr.ID = id;
        for (uint8 i = 0; i < 10; i++)
            qfr.Difficulty[i] = fields[1 + i].GetInt32();

        _questFactionRewardMap[id] = qfr;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_questfactionreward            %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load RandPropPoints.dbc
void DBCStoresMgr::_Load_RandPropPoints()
{
    uint32 oldMSTime = getMSTime();

    _randPropPointsMap.clear();
    //                                                0     1       2       3       4      5          6          7           8           9          10        11      12      13      14      15
    QueryResult result = WorldDatabase.Query("SELECT ID, Epic_1, Epic_2, Epic_3, Epic_4, Epic_5, Superior_1, Superior_2, Superior_3, Superior_4, Superior_5, Good_1, Good_2, Good_3, Good_4, Good_5 FROM dbc_randproppoints");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_randproppoints. DB table `dbc_randproppoints` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        RandPropPointsDBC rpp;
        rpp.ID = id;
        for (uint8 i = 0; i < 5; i++)
            rpp.Epic[i] = fields[1 + i].GetUInt32();

        for (uint8 i = 0; i < 5; i++)
            rpp.Superior[i] = fields[6 + i].GetUInt32();

        for (uint8 i = 0; i < 5; i++)
            rpp.Good[i] = fields[11 + i].GetUInt32();

        _randPropPointsMap[id] = rpp;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_randproppoints                %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load ScalingStatDistribution.dbc
void DBCStoresMgr::_Load_ScalingStatDistribution()
{
    uint32 oldMSTime = getMSTime();

    _scalingStatDistributionMap.clear();
    //                                                0     1          2        3          4         5          6       7         8          9         10       11      12         13       14      15      16        17       18       19        20        21
    QueryResult result = WorldDatabase.Query("SELECT ID, StatID_1, StatID_2, StatID_3, StatID_4, StatID_5, StatID_6, StatID_7, StatID_8, StatID_9, StatID_10, Bonus_1, Bonus_2, Bonus_3, Bonus_4, Bonus_5, Bonus_6, Bonus_7, Bonus_8, Bonus_9, Bonus_10, Maxlevel FROM dbc_scalingstatdistribution");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 DBC_scalingstatdistribution. DB table `dbc_scalingstatdistribution` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        ScalingStatDistributionDBC ssd;
        ssd.ID = id;
        for (uint8 i = 0; i < 10; i++)
            ssd.StatID[i] = fields[1 + i].GetInt32();

        for (uint8 i = 0; i < 10; i++)
            ssd.Bonus[i] = fields[11 + i].GetUInt32();

        ssd.Maxlevel = fields[21].GetUInt32();

        _scalingStatDistributionMap[id] = ssd;

        ++count;
    } while (result->NextRow());

    //                                       1111111111111111111111111111111111
    TC_LOG_INFO("server.loading", ">> Loaded DBC_scalingstatdistribution       %u in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}
