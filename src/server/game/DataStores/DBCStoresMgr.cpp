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
}

void DBCStoresMgr::Initialize()
{
    _Load_Achievement();
    _Load_AchievementCriteria();
    _Load_AreaTable();
}

uint32 DBCStoresMgr::GetNumRows(DBCFileName type)
{
    ASSERT(type);
    uint32 result = 0;

    switch (type)
    {
        case Achievement:
        {
            result =_achievementMap.size();
            break;
        }
        case AchievementCriteria:
        {
            result = _achievementCriteriaMap.size();
            break;
        }
        case AreaTable:
        {
            result = _areaTableMap.size();
            break;
        }
        case AreaGroup:
        {
            result = _areaGroupMap.size();
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
    //                                                0     1     2         3           4           5          6            7           8           9           10          11         12          13       14     15       16                  17
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, Faction, InstanceID, title_enUS, title_koKR, title_frFR, title_deDE, title_zhCN, title_zhTW, title_esES, title_esMX, title_ruRU, Category, Points, Flags, MinimumCriteria, SharesCriteria FROM dbc_achievement");
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
        ach.ID              = fields[1].GetInt32();
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
    //                                                0     1    2       3       4       5       6       7       8       9       10       11       12       13       14      15        16       17      18        19       20      21
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, field1, field2, field3, field4, field5, field6, field7, field8, field9, field10, field12, field13, field14, field15, field16, field17, field26, field27, field28, field29 FROM dbc_achievement_criteria");
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

        achc.Flags = fields[18].GetUInt32();
        achc.StartEvent = fields[19].GetUInt32();
        achc.StartAsset = fields[20].GetUInt32();
        achc.StartTimer = fields[21].GetUInt32();

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
    //                                                0     1    2       3       4       5       6           7          8            9          10          11          12          13          14          15         16       17      18       19       20
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, field1, field2, field3, field4, field10, title_enUS, title_koKR, title_frFR, title_deDE, title_zhCN, title_zhTW, title_esES, title_esMX, title_ruRU, field28, field29, field30, field31, field32 FROM dbc_areatable");
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
    //                                                0     1    2
    QueryResult result = WorldDatabase.Query("SELECT guid, ID, field1 FROM dbc_achievement_criteria");
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
        //AreaGroupDBC ag;
        

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u DBC_achievement_criteria in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}
