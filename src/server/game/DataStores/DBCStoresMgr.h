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

#ifndef _DBCMGR_H
#define _DBCMGR_H

#include "Common.h"
#include "DBCStoresMgrStructure.h"
#include <unordered_map>

typedef std::unordered_map<uint32 /*guid*/, AchievementDBC> AchievementDBCMap;
typedef std::unordered_map<uint32 /*guid*/, AchievementCriteriaDBC> AchievementCriteriaDBCMap;

typedef std::unordered_map<uint32 /*guid*/, AreaTableDBC> AreaTableDBCMap;
typedef std::unordered_map<uint32 /*guid*/, AreaGroupDBC> AreaGroupDBCMap;

enum DBCFileName : uint8
{
    Achievement = 1,
    AchievementCriteria,
    AreaTable,
    AreaGroup,
};

class TC_GAME_API DBCStoresMgr
{
private:
    DBCStoresMgr() {}
    ~DBCStoresMgr();

public:
    static DBCStoresMgr* instance();

    void Initialize();

    AchievementDBC const* GetAchievementDBC(uint32 id) const
    {
        for (AchievementDBCMap::const_iterator itr = _achievementMap.begin(); itr != _achievementMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    AchievementCriteriaDBC const* GetAchievementCriteriaDBC(uint32 id) const
    {
        for (AchievementCriteriaDBCMap::const_iterator itr = _achievementCriteriaMap.begin(); itr != _achievementCriteriaMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    AreaTableDBC const* GetAreaTableDBC(uint32 id) const
    {
        for (AreaTableDBCMap::const_iterator itr = _areaTableMap.begin(); itr != _areaTableMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    AreaGroupDBC const* GetAreaGroupDBC(uint32 id) const
    {
        for (AreaGroupDBCMap::const_iterator itr = _areaGroupMap.begin(); itr != _areaGroupMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    uint32 GetNumRows(DBCFileName type);
    AreaTableDBCMap const& GetAreaTableDBCMap() const { return _areaTableMap; }

protected:
    void _Load_Achievement();
    void _Load_AchievementCriteria();
    void _Load_AreaTable();
    void _Load_AreaGroup();

private:
    AchievementDBCMap _achievementMap;
    AchievementCriteriaDBCMap _achievementCriteriaMap;
    AreaTableDBCMap _areaTableMap;
    AreaGroupDBCMap _areaGroupMap;
};

#define sDBCStoresMgr DBCStoresMgr::instance()

#endif // _DBCMGR_H
