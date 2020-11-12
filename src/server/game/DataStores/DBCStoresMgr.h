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
typedef std::unordered_map<uint32 /*guid*/, AreaPOIDBC> AreaPOIDBCMap;
typedef std::unordered_map<uint32 /*guid*/, AreaTriggerDBC> AreaTriggerDBCMap;
typedef std::unordered_map<uint32 /*guid*/, AuctionHouseDBC> AuctionHouseDBCMap;
typedef std::unordered_map<uint32 /*guid*/, BankBagSlotPricesDBC> BankBagSlotPricesDBCMap;
typedef std::unordered_map<uint32 /*guid*/, BannedAddOnsDBC> BannedAddOnsDBCMap;
typedef std::unordered_map<uint32 /*guid*/, BarberShopStyleDBC> BarberShopStyleDBCMap;
typedef std::unordered_map<uint32 /*guid*/, BattlemasterListDBC> BattlemasterListDBCMap;

enum DBCFileName : uint8
{
    Achievement_ENUM         = 1,
    AchievementCriteria_ENUM,
    AreaTable_ENUM,
    AreaGroup_ENUM,
    AreaPOI_ENUM,
    AreaTrigger_ENUM,
    AuctionHouse_ENUM,
    BankBagSlotPrices_ENUM,
    BannedAddOns_ENUM,
    BattlemasterList_ENUM,
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

    AreaTableDBCMap const& GetAreaTableDBCMap() const { return _areaTableMap; }
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

    AreaPOIDBC const* GetAreaPOIDBC(uint32 id) const
    {
        for (AreaPOIDBCMap::const_iterator itr = _areaPOIMap.begin(); itr != _areaPOIMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    AreaTriggerDBC const* GetAreaTriggerDBC(uint32 id) const
    {
        for (AreaTriggerDBCMap::const_iterator itr = _areaTriggerMap.begin(); itr != _areaTriggerMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    AuctionHouseDBC const* GetAuctionHouseDBC(uint32 id) const
    {
        for (AuctionHouseDBCMap::const_iterator itr = _auctionHouseMap.begin(); itr != _auctionHouseMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    BankBagSlotPricesDBC const* GetBankBagSlotPricesDBC(uint32 id) const
    {
        for (BankBagSlotPricesDBCMap::const_iterator itr = _bankBagSlotPricesMap.begin(); itr != _bankBagSlotPricesMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    BannedAddOnsDBC const* GetBannedAddOnsDBC(uint32 id) const
    {
        for (BannedAddOnsDBCMap::const_iterator itr = _bannedAddonsMap.begin(); itr != _bannedAddonsMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    BarberShopStyleDBC const* GetBarberShopStyleDBC(uint32 id) const
    {
        for (BarberShopStyleDBCMap::const_iterator itr = _barberShopStyleMap.begin(); itr != _barberShopStyleMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    BattlemasterListDBC const* GetBattlemasterListDBC(uint32 id) const
    {
        for (BattlemasterListDBCMap::const_iterator itr = _battlemasterListMap.begin(); itr != _battlemasterListMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    uint32 GetNumRows(DBCFileName type);    

protected:
    void _Load_Achievement();
    void _Load_AchievementCriteria();
    void _Load_AreaTable();
    void _Load_AreaGroup();
    void _Load_AreaPOI();
    void _Load_AreaTrigger();
    void _Load_AuctionHouse();
    void _Load_BankBagSlotPrices();
    void _Load_BannedAddOns();
    void _Load_BarberShopStyle();
    void _Load_BattlemasterList();

private:
    AchievementDBCMap _achievementMap;
    AchievementCriteriaDBCMap _achievementCriteriaMap;
    AreaTableDBCMap _areaTableMap;
    AreaGroupDBCMap _areaGroupMap;
    AreaPOIDBCMap _areaPOIMap;
    AreaTriggerDBCMap _areaTriggerMap;
    AuctionHouseDBCMap _auctionHouseMap;
    BankBagSlotPricesDBCMap _bankBagSlotPricesMap;
    BannedAddOnsDBCMap _bannedAddonsMap;
    BarberShopStyleDBCMap _barberShopStyleMap;
    BattlemasterListDBCMap _battlemasterListMap;
};

#define sDBCStoresMgr DBCStoresMgr::instance()

#endif // _DBCMGR_H
