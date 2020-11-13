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
}

void DBCStoresMgr::Initialize()
{
    _Load_Achievement();
    _Load_AchievementCriteria();
    _Load_AreaTable();
    _Load_AreaGroup();
    // unused
    //_Load_AreaPOI();
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
}

uint32 DBCStoresMgr::GetNumRows(DBCFileName type)
{
    ASSERT(type);
    uint32 result = 0;

    switch (type)
    {
        case Achievement_ENUM:
        {
            result =_achievementMap.size();
            break;
        }
        case AchievementCriteria_ENUM:
        {
            result = _achievementCriteriaMap.size();
            break;
        }
        case AreaTable_ENUM:
        {
            result = _areaTableMap.size();
            break;
        }
        case AreaGroup_ENUM:
        {
            result = _areaGroupMap.size();
            break;
        }
        case AreaPOI_ENUM:
        {
            result = _areaPOIMap.size();
            break;
        }
        case AreaTrigger_ENUM:
        {
            result = _areaTriggerMap.size();
            break;
        }
        case AuctionHouse_ENUM:
        {
            result = _auctionHouseMap.size();
            break;
        }
        case BankBagSlotPrices_ENUM:
        {
            result = _bankBagSlotPricesMap.size();
            break;
        }
        case BannedAddOns_ENUM:
        {
            result = _bannedAddonsMap.size();
            break;
        }
        case BattlemasterList_ENUM:
        {
            result = _battlemasterListMap.size();
            break;
        }
        case CharacterFacialHairStyles_ENUM:
        {
            result = _characterFacialHairStyleMap.size();
            break;
        }
        case CharSections_ENUM:
        {
            result = _charSectionMap.size();
            break;
        }
        case CharStartOutfit_ENUM:
        {
            result = _charStartOutfitMap.size();
            break;
        }
        case CharTitlesMap_ENUM:
        {
            result = _charTitlesMap.size();
            break;
        }
    }

    return result;
}

// load Achievement.dbc
void DBCStoresMgr::_Load_Achievement()
{
    uint32 oldMSTime = getMSTime();

    _achievementMap.clear();
    //                                                0     1     2         3           4                    5                6                7                8                9                10               11              12            13       14     15           16                17
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, Faction, Instance_Id, Title_Lang_enUS, Title_Lang_koKR, Title_Lang_frFR, Title_Lang_deDE, Title_Lang_zhCN, Title_Lang_zhTW, Title_Lang_esES, Title_Lang_esMX, Title_Lang_ruRU, Category, Points, Flags, Minimum_Criteria, Shares_Criteria FROM dbc_achievement");
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
        ach.ID              = fields[1].GetUInt32();
        ach.Faction         = fields[2].GetInt32();
        ach.InstanceID      = fields[3].GetInt32();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
        {
            const char* test = fields[4+i].GetCString();
            std::array<const char*, 16> name;
            std::memcpy(name.data(), test, 16);

            ach.Title[i] = name;
        }

        ach.Category        = fields[13].GetUInt32();
        ach.Points          = fields[14].GetUInt32();
        ach.Flags           = fields[15].GetUInt32();
        ach.MinimumCriteria = fields[16].GetUInt32();
        ach.SharesCriteria  = fields[17].GetUInt32();

        _achievementMap[id] = ach;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_achievements in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load Achievement_Criteria.dbc
void DBCStoresMgr::_Load_AchievementCriteria()
{
    uint32 oldMSTime = getMSTime();

    _achievementCriteriaMap.clear();
    //                                                0     1        2           3       4        5           6            7            8           9                10                      11                   12                      13                       14                   15                       16                  17                      18             19           20                21           22
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, Achievement_Id, Type, Asset_Id, Quantity, Start_Event, Start_Asset, Fail_Event, Fail_Asset, Description_Lang_enUS, Description_Lang_koKR, Description_Lang_frFR, Description_Lang_deDE, Description_Lang_zhCN, Description_Lang_zhTW, Description_Lang_esES, Description_Lang_esMX, Description_Lang_ruRU, Flags, Timer_Start_Event, Timer_Asset_Id, Timer_Time FROM dbc_achievement_criteria");
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
        achc.ID                  = fields[1].GetUInt32();
        achc.AchievementID       = fields[2].GetUInt32();
        achc.Type                = fields[3].GetUInt32();

        achc.Asset.ID            = fields[4].GetUInt32();
        achc.Quantity            = fields[5].GetUInt32();

        achc.AdditionalRequirements[0].Type = fields[6].GetUInt32();
        achc.AdditionalRequirements[0].Asset = fields[7].GetUInt32();
        achc.AdditionalRequirements[1].Type = fields[8].GetUInt32();
        achc.AdditionalRequirements[1].Asset = fields[9].GetUInt32();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
        {
            const char* test = fields[10 + i].GetCString();
            std::array<const char*, 16> name;
            std::memcpy(name.data(), test, 16);

            achc.name[i] = name;
        }

        achc.Flags      = fields[19].GetUInt32();
        achc.StartEvent = fields[20].GetUInt32();
        achc.StartAsset = fields[21].GetUInt32();
        achc.StartTimer = fields[22].GetUInt32();

        _achievementCriteriaMap[id] = achc;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_achievement_criteria in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load AreaTable.dbc
void DBCStoresMgr::_Load_AreaTable()
{
    uint32 oldMSTime = getMSTime();

    _areaTableMap.clear();
    //                                                0     1       2             3          4       5           6                  7                    8                   9                   10                  11                  12                  13                14                   15                16               17               18              19              20
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, ContinentID, ParentAreaID, AreaBit, Flags, ExplorationLevel, AreaName_Lang_enUS, AreaName_Lang_koKR, AreaName_Lang_frFR, AreaName_Lang_deDE, AreaName_Lang_zhCN, AreaName_Lang_zhTW, AreaName_Lang_esES, AreaName_Lang_esMX, AreaName_Lang_ruRU, FactionGroupMask, LiquidTypeID_1, LiquidTypeID_2, LiquidTypeID_3, LiquidTypeID_4 FROM dbc_areatable");
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
        at.ID               = fields[1].GetUInt32();
        at.ContinentID      = fields[2].GetUInt32();
        at.ParentAreaID     = fields[3].GetUInt32();
        at.AreaBit          = fields[4].GetUInt32();
        at.Flags            = fields[5].GetUInt32();
        at.ExplorationLevel = fields[6].GetInt32();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            at.AreaName[i] = fields[7 + i].GetString();

        at.FactionGroupMask = fields[16].GetUInt32();
        at.LiquidTypeID[0]  = fields[17].GetUInt32();
        at.LiquidTypeID[1]  = fields[18].GetUInt32();
        at.LiquidTypeID[2]  = fields[19].GetUInt32();
        at.LiquidTypeID[3]  = fields[20].GetUInt32();

        _areaTableMap[id] = at;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_areatable in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load AreaGroup.dbc
void DBCStoresMgr::_Load_AreaGroup()
{
    uint32 oldMSTime = getMSTime();

    _areaGroupMap.clear();
    //                                                0     1     2         3         4         5         6         7         8
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, AreaID_1, AreaID_2, AreaID_3, AreaID_4, AreaID_5, AreaID_6, NextAreaID FROM dbc_areagroup");
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
        ag.ID = fields[1].GetUInt32();

        for (uint8 i = 0; i < MAX_GROUP_AREA_IDS; i++)
            ag.AreaID[i] = fields[2 + i].GetUInt32();

        ag.NextAreaID = fields[8].GetUInt32();
        _areaGroupMap[id] = ag;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_areagroup in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load AreaPOI.dbc
void DBCStoresMgr::_Load_AreaPOI()
{
    uint32 oldMSTime = getMSTime();

    _areaPOIMap.clear();
    //                                                0     1       2        3        4       5      6       7       8        9      10      11       12     13 14 15       16        17         18
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, Importance, Icon_1, Icon_2, Icon_3, Icon_4, Icon_5, Icon_6, Icon_7, Icon_8, Icon_9, FactionID, X, Y, Z, ContinentID, AreaID, WorldStateID FROM dbc_areapoi");
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
        ap.ID         = fields[1].GetUInt32();
        ap.Importance = fields[2].GetUInt32();

        for (uint8 i = 0; i < 9; i++)
            ap.Icon[i] = fields[3 + i].GetUInt32();

        ap.FactionID    = fields[12].GetUInt32();
        ap.Pos.X        = fields[13].GetFloat();
        ap.Pos.Y        = fields[14].GetFloat();
        ap.Pos.Z        = fields[15].GetFloat();
        ap.ContinentID  = fields[16].GetUInt32();
        ap.AreaID       = fields[17].GetUInt32();
        ap.WorldStateID = fields[18].GetUInt32();

        _areaPOIMap[id] = ap;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_areapoi in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load AreaTrigger.dbc
void DBCStoresMgr::_Load_AreaTrigger()
{
    uint32 oldMSTime = getMSTime();

    _areaTriggerMap.clear();
    //                                                0     1       2       3  4  5     6         7          8          9         10
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, ContinentID, X, Y, Z, Radius, Box_Length, Box_Width, Box_Height, Box_Yaw FROM dbc_areatrigger");
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
        at.ID          = fields[1].GetUInt32();
        at.ContinentID = fields[2].GetUInt32();
        at.Pos.X       = fields[3].GetFloat();
        at.Pos.Y       = fields[4].GetFloat();
        at.Pos.Z       = fields[5].GetFloat();
        at.Radius      = fields[6].GetFloat();
        at.BoxLength   = fields[7].GetFloat();
        at.BoxWidth    = fields[8].GetFloat();
        at.BoxHeight   = fields[9].GetFloat();

        _areaTriggerMap[id] = at;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_areatrigger in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load AuctionHouse.dbc
void DBCStoresMgr::_Load_AuctionHouse()
{
    uint32 oldMSTime = getMSTime();

    _auctionHouseMap.clear();
    //                                                0     1       2          3               4
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, FactionID, DepositRate, ConsignmentRate FROM dbc_auctionhouse");
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
        ah.ID              = fields[1].GetUInt32();
        ah.FactionID       = fields[2].GetUInt32();
        ah.DepositRate     = fields[3].GetUInt32();
        ah.ConsignmentRate = fields[4].GetUInt32();

        _auctionHouseMap[id] = ah;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_auctionhouse in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load BankBagSlotPrices.dbc
void DBCStoresMgr::_Load_BankBagSlotPrices()
{
    uint32 oldMSTime = getMSTime();

    _bankBagSlotPricesMap.clear();
    //                                                0     1    2
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, Cost FROM dbc_bankbagslotprices");
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
        bsp.ID   = fields[1].GetUInt32();
        bsp.Cost = fields[2].GetUInt32();

        _bankBagSlotPricesMap[id] = bsp;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_bankbagslotprices in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load BannedAddOns.dbc
void DBCStoresMgr::_Load_BannedAddOns()
{
    uint32 oldMSTime = getMSTime();

    _bannedAddonsMap.clear();
    //                                                0     1
    QueryResult result = WorldDatabase.Query("SELECT guid, ID FROM dbc_bannedaddons");
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
        ba.ID = fields[1].GetUInt32();

        _bannedAddonsMap[id] = ba;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_bannedaddons in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load BarberShopStyle.dbc
void DBCStoresMgr::_Load_BarberShopStyle()
{
    uint32 oldMSTime = getMSTime();

    _barberShopStyleMap.clear();
    //                                                0     1    2    3     4    5
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, Type, Race, Sex, Data FROM dbc_barbershopstyle");
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
        bs.ID   = fields[1].GetUInt32();
        bs.Type = fields[2].GetUInt32();
        bs.Race = fields[3].GetUInt32();
        bs.Sex  = fields[4].GetUInt32();
        bs.Data = fields[5].GetUInt32();

        _barberShopStyleMap[id] = bs;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_barbershopstyle in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load BattlemasterList.dbc
void DBCStoresMgr::_Load_BattlemasterList()
{
    uint32 oldMSTime = getMSTime();

    _battlemasterListMap.clear();
    //                                                0     1    2          3        4        5        6        7       8       9           10              11              12              13              14              15              16              17              18              19              20              21
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, MapID_1, MapID_2, MapID_3, MapID_4, MapID_5, MapID_6, MapID_7, MapID_8, InstanceType, Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU, MaxGroupSize, HolidayWorldState FROM dbc_battlemasterlist");
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
        bl.ID = fields[1].GetUInt32();

        for (uint8 i = 0; i < 8; i++)
            bl.MapID[i] = fields[2 + i].GetInt32();

        bl.InstanceType = fields[10].GetUInt32();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            bl.Name[i] = fields[11 + i].GetInt32();

        bl.MaxGroupSize      = fields[20].GetUInt32();
        bl.HolidayWorldState = fields[21].GetUInt32();

        _battlemasterListMap[id] = bl;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_battlemasterlist in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CharacterFacialHairStyles.dbc
void DBCStoresMgr::_Load_CharacterFacialHairStyles()
{
    uint32 oldMSTime = getMSTime();

    _characterFacialHairStyleMap.clear();
    //                                                 0    1     2      3         4
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, RaceID, SexID, VariationID FROM dbc_characterfacialhairstyles");
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
        cfhs.ID          = fields[1].GetUInt32();
        cfhs.RaceID      = fields[2].GetUInt8();
        cfhs.SexID       = fields[3].GetUInt8();
        cfhs.VariationID = fields[4].GetUInt8();

        _characterFacialHairStyleMap[id] = cfhs;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_characterfacialhairstyles in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CharSections.dbc
void DBCStoresMgr::_Load_CharSections()
{
    uint32 oldMSTime = getMSTime();

    _charSectionMap.clear();
    //                                                 0    1     2      3         4         5          6              7
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, RaceID, SexID, BaseSection, Flags, VariationIndex, ColorIndex FROM dbc_charsections");
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
        cs.ID             = fields[1].GetUInt32();
        cs.RaceID         = fields[2].GetUInt8();
        cs.SexID          = fields[3].GetUInt8();
        cs.BaseSection    = fields[4].GetUInt8();
        cs.Flags          = fields[5].GetUInt8();
        cs.VariationIndex = fields[6].GetUInt8();
        cs.ColorIndex     = fields[7].GetUInt8();

        _charSectionMap[id] = cs;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_charsections in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CharStartOutfit.dbc
void DBCStoresMgr::_Load_CharStartOutfit()
{
    uint32 oldMSTime = getMSTime();

    _charStartOutfitMap.clear();
    //                                                 0    1     2      3         4      5         6         7         8         9         10        11        12        13        14          15        16          17        18          19         20         21        22          23         24         25        26          27        28
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, RaceID, ClassID, SexID, ItemID_1, ItemID_2, ItemID_3, ItemID_4, ItemID_5, ItemID_6, ItemID_7, ItemID_8, ItemID_9, ItemID_10, ItemID_11, ItemID_12, ItemID_13, ItemID_14, ItemID_15, ItemID_16, ItemID_17, ItemID_18, ItemID_19, ItemID_20, ItemID_21, ItemID_22, ItemID_23, ItemID_24 FROM dbc_charstartoutfit");
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
        cso.ID      = fields[1].GetUInt32();
        cso.RaceID  = fields[2].GetUInt8();
        cso.ClassID = fields[3].GetUInt8();
        cso.SexID   = fields[4].GetUInt8();

        for (uint8 i = 0; i < MAX_OUTFIT_ITEMS; i++)
            cso.ItemID[i] = fields[5 + i].GetInt32();        

        _charStartOutfitMap[id] = cso;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_charstartoutfit in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

// load CharTitles.dbc
void DBCStoresMgr::_Load_CharTitles()
{
    uint32 oldMSTime = getMSTime();

    _charTitlesMap.clear();
    //                                                 0    1       2               3               4               5               6               7               8               9               10              11              12                13                14              15              16              17                  18              19             20
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, Name_Lang_enUS, Name_Lang_koKR, Name_Lang_frFR, Name_Lang_deDE, Name_Lang_zhCN, Name_Lang_zhTW, Name_Lang_esES, Name_Lang_esMX, Name_Lang_ruRU, Name1_Lang_enUS, Name1_Lang_koKR, Name1_Lang_frFR, Name1_Lang_deDE, Name1_Lang_zhCN, Name1_Lang_zhTW, Name1_Lang_esES, Name1_Lang_esMX, Name1_Lang_ruRU, Mask_ID FROM dbc_chartitles");
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
        ct.ID = fields[1].GetUInt32();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            ct.Name[i] = fields[2 + i].GetString();

        for (uint8 i = 0; i < TOTAL_LOCALES; i++)
            ct.Name1[i] = fields[11 + i].GetString();

        ct.MaskID = fields[20].GetUInt32();

        _charTitlesMap[id] = ct;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_chartitles in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}
