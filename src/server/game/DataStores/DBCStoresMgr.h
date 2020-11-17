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
typedef std::unordered_map<uint32 /*guid*/, CharacterFacialHairStylesDBC> CharacterFacialHairStylesDBCMap;
typedef std::unordered_map<uint32 /*guid*/, CharSectionsDBC> CharSectionsDBCMap;
typedef std::unordered_map<uint32 /*guid*/, CharStartOutfitDBC> CharStartOutfitDBCMap;
typedef std::unordered_map<uint32 /*guid*/, CharTitlesDBC> CharTitlesDBCMap;
typedef std::unordered_map<uint32 /*guid*/, ChatChannelsDBC> ChatChannelsDBCMap;
typedef std::unordered_map<uint32 /*guid*/, ChrClassesDBC> ChrClassesDBCMap;
typedef std::unordered_map<uint32 /*guid*/, ChrRacesDBC> ChrRacesDBCMap;
typedef std::unordered_map<uint32 /*guid*/, CinematicCameraDBC> CinematicCameraDBCMap;
typedef std::unordered_map<uint32 /*guid*/, CinematicSequencesDBC> CinematicSequencesDBCMap;

class TC_GAME_API DBCStoresMgr
{
private:
    DBCStoresMgr() {}
    ~DBCStoresMgr();

public:
    static DBCStoresMgr* instance();

    void Initialize();

    AchievementDBCMap const& GetAchievementDBCMap() const { return _achievementMap; }
    uint32 GetAchievementDBCSize() { return _achievementMap.size(); }
    AchievementDBC const* GetAchievementDBC(uint32 id) const
    {
        for (AchievementDBCMap::const_iterator itr = _achievementMap.begin(); itr != _achievementMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    AchievementCriteriaDBCMap const& GetAchievementCriteriaDBCMap() const { return _achievementCriteriaMap; }
    uint32 GetAchievementCriteriaDBCSize() { return _achievementCriteriaMap.size(); }
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

    uint32 GetBannedAddOnsSize() { return _bannedAddonsMap.size(); }
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

    BattlemasterListDBCMap const& GetBattlemasterListDBCMap() const { return _battlemasterListMap; }
    BattlemasterListDBC const* GetBattlemasterListDBC(uint32 id) const
    {
        for (BattlemasterListDBCMap::const_iterator itr = _battlemasterListMap.begin(); itr != _battlemasterListMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    CharacterFacialHairStylesDBC const* GetCharFacialHairDBC(uint8 race, uint8 gender, uint8 facialHairID)
    {
        for (CharacterFacialHairStylesDBCMap::const_iterator itr = _characterFacialHairStyleMap.begin(); itr != _characterFacialHairStyleMap.end(); ++itr)
        {
            if (itr->second.RaceID == race &&
                itr->second.SexID == gender &&
                itr->second.VariationID == facialHairID)
                return &itr->second;
        }
        return nullptr;
    }

    CharSectionsDBC const* GetCharSectionsDBC(uint8 race, CharSectionType genType, uint8 gender, uint8 type, uint8 color)
    {
        for (CharSectionsDBCMap::const_iterator itr = _charSectionMap.begin(); itr != _charSectionMap.end(); ++itr)
        {
            if (itr->second.RaceID == race &&
                itr->second.BaseSection == genType &&
                itr->second.SexID == gender &&                
                itr->second.VariationIndex == type &&
                itr->second.ColorIndex == color)
                return &itr->second;
        }
        return nullptr;
    }

    CharStartOutfitDBCMap const& GetCharStartOutfitDBCMap() const { return _charStartOutfitMap; }
    CharStartOutfitDBC const* GetCharStartOutfitDBC(uint32 id)
    {
        for (CharStartOutfitDBCMap::const_iterator itr = _charStartOutfitMap.begin(); itr != _charStartOutfitMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    CharStartOutfitDBC const* GetCharStartOutfitDBCWithParam(uint8 race, uint8 classID, uint8 gender)
    {
        for (CharStartOutfitDBCMap::const_iterator itr = _charStartOutfitMap.begin(); itr != _charStartOutfitMap.end(); ++itr)
        {
            if (itr->second.RaceID == race &&
                itr->second.ClassID == classID &&
                itr->second.SexID == gender)
                return &itr->second;
        }
        return nullptr;
    }

    CharTitlesDBCMap const& GetCharTitlesDBCMap() const { return _charTitlesMap; }
    CharTitlesDBC const* GetCharTitlesDBC(uint32 id)
    {
        for (CharTitlesDBCMap::const_iterator itr = _charTitlesMap.begin(); itr != _charTitlesMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    ChatChannelsDBCMap const& GetChatChannelsDBCMap() const { return _chatChannelsMap; }
    ChatChannelsDBC const* GetChatChannelsDBC(uint32 id)
    {
        for (ChatChannelsDBCMap::const_iterator itr = _chatChannelsMap.begin(); itr != _chatChannelsMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    ChrClassesDBC const* GetChrClassesDBC(uint32 id)
    {
        for (ChrClassesDBCMap::const_iterator itr = _chrClassesMap.begin(); itr != _chrClassesMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    char const* GetChrClassName(uint8 class_, uint8 locale)
    {
        for (ChrClassesDBCMap::const_iterator itr = _chrClassesMap.begin(); itr != _chrClassesMap.end(); ++itr)
        {
            if (itr->second.ID == class_)
                return itr->second.Name[locale].c_str();
        }
        return nullptr;
    }

    ChrRacesDBC const* GetChrRacesDBC(uint32 id)
    {
        for (ChrRacesDBCMap::const_iterator itr = _chrRacesMap.begin(); itr != _chrRacesMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

    char const* GetRaceName(uint8 race, uint8 locale)
    {
        for (ChrRacesDBCMap::const_iterator itr = _chrRacesMap.begin(); itr != _chrRacesMap.end(); ++itr)
        {
            if (itr->second.ID == race)
                return itr->second.Name[locale].c_str();
        }
        return nullptr;
    }

    CinematicCameraDBCMap const& GetCinematicCameraDBCMap() const { return _cinematicCameraMap; }

    CinematicSequencesDBC const* GetCinematicSequencesDBC(uint32 id)
    {
        for (CinematicSequencesDBCMap::const_iterator itr = _cinematicSequencesMap.begin(); itr != _cinematicSequencesMap.end(); ++itr)
        {
            if (itr->second.ID == id)
                return &itr->second;
        }
        return nullptr;
    }

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
    void _Load_CharacterFacialHairStyles();
    void _Load_CharSections();
    void _Load_CharStartOutfit();
    void _Load_CharTitles();
    void _Load_ChatChannels();
    void _Load_ChrClasses();
    void _Load_ChrRaces();
    void _Load_CinematicCamera();
    void _Load_CinematicSequences();

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
    CharacterFacialHairStylesDBCMap _characterFacialHairStyleMap;
    CharSectionsDBCMap _charSectionMap;
    CharStartOutfitDBCMap _charStartOutfitMap;
    CharTitlesDBCMap _charTitlesMap;
    ChatChannelsDBCMap _chatChannelsMap;
    ChrClassesDBCMap _chrClassesMap;
    ChrRacesDBCMap _chrRacesMap;
    CinematicCameraDBCMap _cinematicCameraMap;
    CinematicSequencesDBCMap _cinematicSequencesMap;
};

#define sDBCStoresMgr DBCStoresMgr::instance()

#endif // _DBCMGR_H
