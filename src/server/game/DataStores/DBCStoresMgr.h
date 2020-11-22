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

typedef std::unordered_map<uint32 /*ID*/, AchievementDBC> AchievementDBCMap;
typedef std::unordered_map<uint32 /*ID*/, AchievementCriteriaDBC> AchievementCriteriaDBCMap;
typedef std::unordered_map<uint32 /*ID*/, AreaTableDBC> AreaTableDBCMap;
typedef std::unordered_map<uint32 /*ID*/, AreaGroupDBC> AreaGroupDBCMap;
typedef std::unordered_map<uint32 /*ID*/, AreaPOIDBC> AreaPOIDBCMap;
typedef std::unordered_map<uint32 /*ID*/, AreaTriggerDBC> AreaTriggerDBCMap;
typedef std::unordered_map<uint32 /*ID*/, AuctionHouseDBC> AuctionHouseDBCMap;
typedef std::unordered_map<uint32 /*ID*/, BankBagSlotPricesDBC> BankBagSlotPricesDBCMap;
typedef std::unordered_map<uint32 /*ID*/, BannedAddOnsDBC> BannedAddOnsDBCMap;
typedef std::unordered_map<uint32 /*ID*/, BarberShopStyleDBC> BarberShopStyleDBCMap;
typedef std::unordered_map<uint32 /*ID*/, BattlemasterListDBC> BattlemasterListDBCMap;
typedef std::unordered_map<uint32 /*ID*/, CharacterFacialHairStylesDBC> CharacterFacialHairStylesDBCMap;
typedef std::unordered_map<uint32 /*ID*/, CharSectionsDBC> CharSectionsDBCMap;
typedef std::unordered_map<uint32 /*ID*/, CharStartOutfitDBC> CharStartOutfitDBCMap;
typedef std::unordered_map<uint32 /*ID*/, CharTitlesDBC> CharTitlesDBCMap;
typedef std::unordered_map<uint32 /*ID*/, ChatChannelsDBC> ChatChannelsDBCMap;
typedef std::unordered_map<uint32 /*ID*/, ChrClassesDBC> ChrClassesDBCMap;
typedef std::unordered_map<uint32 /*ID*/, ChrRacesDBC> ChrRacesDBCMap;
typedef std::unordered_map<uint32 /*ID*/, CinematicCameraDBC> CinematicCameraDBCMap;
typedef std::unordered_map<uint32 /*ID*/, CinematicSequencesDBC> CinematicSequencesDBCMap;
typedef std::unordered_map<uint32 /*ID*/, CreatureDisplayInfoDBC> CreatureDisplayInfoDBCMap;
typedef std::unordered_map<uint32 /*ID*/, CreatureDisplayInfoExtraDBC> CreatureDisplayInfoExtraDBCMap;
typedef std::unordered_map<uint32 /*ID*/, CreatureFamilyDBC> CreatureFamilyDBCMap;
typedef std::unordered_map<uint32 /*ID*/, CreatureModelDataDBC> CreatureModelDataDBCMap;
typedef std::unordered_map<uint32 /*ID*/, CreatureSpellDataDBC> CreatureSpellDataDBCMap;
typedef std::unordered_map<uint32 /*ID*/, CreatureTypeDBC> CreatureTypeDBCMap;
typedef std::unordered_map<uint32 /*ID*/, CurrencyCategoryDBC> CurrencyCategoryDBCMap;
typedef std::unordered_map<uint32 /*ItemID*/, CurrencyTypesDBC> CurrencyTypesDBCMap;
typedef std::unordered_map<uint32 /*ID*/, DestructibleModelDataDBC> DestructibleModelDataDBCMap;
typedef std::unordered_map<uint32 /*ID*/, DungeonEncounterDBC> DungeonEncounterDBCMap;
typedef std::unordered_map<uint32 /*ID*/, DurabilityCostsDBC> DurabilityCostsDBCMap;
typedef std::unordered_map<uint32 /*ID*/, DurabilityQualityDBC> DurabilityQualityDBCMap;
typedef std::unordered_map<uint32 /*ID*/, EmotesDBC> EmotesDBCMap;
typedef std::unordered_map<uint32 /*ID*/, EmotesTextDBC> EmotesTextDBCMap;
typedef std::unordered_map<uint32 /*ID*/, EmotesTextSoundDBC> EmotesTextSoundDBCMap;
typedef std::unordered_map<uint32 /*ID*/, FactionDBC> FactionDBCMap;

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
        AchievementDBCMap::const_iterator itr = _achievementMap.find(id);
        if (itr != _achievementMap.end())
            return &itr->second;
        return nullptr;
    }

    AchievementCriteriaDBCMap const& GetAchievementCriteriaDBCMap() const { return _achievementCriteriaMap; }
    uint32 GetAchievementCriteriaDBCSize() { return _achievementCriteriaMap.size(); }
    AchievementCriteriaDBC const* GetAchievementCriteriaDBC(uint32 id) const
    {
        AchievementCriteriaDBCMap::const_iterator itr = _achievementCriteriaMap.find(id);
        if (itr != _achievementCriteriaMap.end())
            return &itr->second;
        return nullptr;
    }

    AreaTableDBCMap const& GetAreaTableDBCMap() const { return _areaTableMap; }
    AreaTableDBC const* GetAreaTableDBC(uint32 id) const
    {
        AreaTableDBCMap::const_iterator itr = _areaTableMap.find(id);
        if (itr != _areaTableMap.end())
            return &itr->second;
        return nullptr;
    }

    AreaGroupDBC const* GetAreaGroupDBC(uint32 id) const
    {
        AreaGroupDBCMap::const_iterator itr = _areaGroupMap.find(id);
        if (itr != _areaGroupMap.end())
            return &itr->second;
        return nullptr;
    }

    AreaPOIDBC const* GetAreaPOIDBC(uint32 id) const
    {
        AreaPOIDBCMap::const_iterator itr = _areaPOIMap.find(id);
        if (itr != _areaPOIMap.end())
            return &itr->second;
        return nullptr;
    }

    AreaTriggerDBC const* GetAreaTriggerDBC(uint32 id) const
    {
        AreaTriggerDBCMap::const_iterator itr = _areaTriggerMap.find(id);
        if (itr != _areaTriggerMap.end())
            return &itr->second;
        return nullptr;
    }

    AuctionHouseDBC const* GetAuctionHouseDBC(uint32 id) const
    {
        AuctionHouseDBCMap::const_iterator itr = _auctionHouseMap.find(id);
        if (itr != _auctionHouseMap.end())
            return &itr->second;
        return nullptr;
    }

    BankBagSlotPricesDBC const* GetBankBagSlotPricesDBC(uint32 id) const
    {
        BankBagSlotPricesDBCMap::const_iterator itr = _bankBagSlotPricesMap.find(id);
        if (itr != _bankBagSlotPricesMap.end())
            return &itr->second;
        return nullptr;
    }

    uint32 GetBannedAddOnsSize() { return _bannedAddonsMap.size(); }
    BannedAddOnsDBC const* GetBannedAddOnsDBC(uint32 id) const
    {
        BannedAddOnsDBCMap::const_iterator itr = _bannedAddonsMap.find(id);
        if (itr != _bannedAddonsMap.end())
            return &itr->second;
        return nullptr;
    }

    BarberShopStyleDBC const* GetBarberShopStyleDBC(uint32 id) const
    {
        BarberShopStyleDBCMap::const_iterator itr = _barberShopStyleMap.find(id);
        if (itr != _barberShopStyleMap.end())
            return &itr->second;
        return nullptr;
    }

    BattlemasterListDBCMap const& GetBattlemasterListDBCMap() const { return _battlemasterListMap; }
    BattlemasterListDBC const* GetBattlemasterListDBC(uint32 id) const
    {
        BattlemasterListDBCMap::const_iterator itr = _battlemasterListMap.find(id);
        if (itr != _battlemasterListMap.end())
            return &itr->second;
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
        CharTitlesDBCMap::const_iterator itr = _charTitlesMap.find(id);
        if (itr != _charTitlesMap.end())
            return &itr->second;
        return nullptr;
    }

    ChatChannelsDBCMap const& GetChatChannelsDBCMap() const { return _chatChannelsMap; }
    ChatChannelsDBC const* GetChatChannelsDBC(uint32 id)
    {
        ChatChannelsDBCMap::const_iterator itr = _chatChannelsMap.find(id);
        if (itr != _chatChannelsMap.end())
            return &itr->second;
        return nullptr;
    }

    ChrClassesDBC const* GetChrClassesDBC(uint32 id)
    {
        ChrClassesDBCMap::const_iterator itr = _chrClassesMap.find(id);
        if (itr != _chrClassesMap.end())
                return &itr->second;
        return nullptr;
    }

    char const* GetChrClassName(uint8 class_, uint8 locale)
    {
        ChrClassesDBCMap::const_iterator itr = _chrClassesMap.find(class_);
        if (itr != _chrClassesMap.end())
            return itr->second.Name[locale].c_str();
        return nullptr;
    }

    ChrRacesDBC const* GetChrRacesDBC(uint32 id)
    {
        ChrRacesDBCMap::const_iterator itr = _chrRacesMap.find(id);
        if (itr != _chrRacesMap.end())
            return &itr->second;
        return nullptr;
    }

    char const* GetRaceName(uint8 race, uint8 locale)
    {
        ChrRacesDBCMap::const_iterator itr = _chrRacesMap.find(race);
        if (itr != _chrRacesMap.end())
            return itr->second.Name[locale].c_str();
        return nullptr;
    }

    CinematicCameraDBCMap const& GetCinematicCameraDBCMap() const { return _cinematicCameraMap; }

    CinematicSequencesDBC const* GetCinematicSequencesDBC(uint32 id)
    {
        CinematicSequencesDBCMap::const_iterator itr = _cinematicSequencesMap.find(id);
        if (itr != _cinematicSequencesMap.end())
            return &itr->second;
        return nullptr;
    }

    CreatureDisplayInfoDBC const* GetCreatureDisplayInfoDBC(uint32 id)
    {
        CreatureDisplayInfoDBCMap::const_iterator itr = _creatureDisplayInfoMap.find(id);
        if (itr != _creatureDisplayInfoMap.end())
            return &itr->second;
        return nullptr;
    }

    CreatureDisplayInfoExtraDBC const* GetCreatureDisplayInfoExtraDBC(uint32 id)
    {
        CreatureDisplayInfoExtraDBCMap::const_iterator itr = _creatureDisplayInfoExtraMap.find(id);
        if (itr != _creatureDisplayInfoExtraMap.end())
            return &itr->second;
        return nullptr;
    }

    CreatureFamilyDBCMap const& GetCreatureFamilyDBCMap() const { return _creatureFamilyMap; }
    CreatureFamilyDBC const* GetCreatureFamilyDBC(uint32 id)
    {
        CreatureFamilyDBCMap::const_iterator itr = _creatureFamilyMap.find(id);
        if (itr != _creatureFamilyMap.end())
            return &itr->second;
        return nullptr;
    }

    char const* GetPetName(uint32 petfamily, uint32 dbclang)
    {
        if (!petfamily)
            return nullptr;
        CreatureFamilyDBC const* pet_family = GetCreatureFamilyDBC(petfamily);
        if (!pet_family)
            return nullptr;
        return pet_family->Name[dbclang].c_str();
    }

    CreatureModelDataDBC const* GetCreatureModelDataDBC(uint32 id)
    {
        CreatureModelDataDBCMap::const_iterator itr = _creatureModelDataMap.find(id);
        if (itr != _creatureModelDataMap.end())
            return &itr->second;
        return nullptr;
    }

    CreatureSpellDataDBC const* GetCreatureSpellDataDBC(uint32 id)
    {
        CreatureSpellDataDBCMap::const_iterator itr = _creatureSpellDataMap.find(id);
        if (itr != _creatureSpellDataMap.end())
            return &itr->second;
        return nullptr;
    }

    CreatureTypeDBC const* GetCreatureTypeDBC(uint32 id)
    {
        CreatureTypeDBCMap::const_iterator itr = _creatureTypeMap.find(id);
        if (itr != _creatureTypeMap.end())
            return &itr->second;
        return nullptr;
    }

    CurrencyCategoryDBC const* GetCurrencyCategoryDBC(uint32 id)
    {
        CurrencyCategoryDBCMap::const_iterator itr = _currencyCategoryMap.find(id);
        if (itr != _currencyCategoryMap.end())
            return &itr->second;
        return nullptr;
    }

    CurrencyTypesDBC const* GetCurrencyTypesDBCByItemID(uint32 ItemID)
    {
        CurrencyTypesDBCMap::const_iterator itr = _currencyTypesMap.find(ItemID);
        if (itr != _currencyTypesMap.end())
            return &itr->second;
        return nullptr;
    }

    DestructibleModelDataDBC const* GetDestructibleModelDataDBC(uint32 ID)
    {
        DestructibleModelDataDBCMap::const_iterator itr = _destructibleModelDataMap.find(ID);
        if (itr != _destructibleModelDataMap.end())
            return &itr->second;
        return nullptr;
    }

    DungeonEncounterDBC const* GetDungeonEncounterDBC(uint32 ID)
    {
        DungeonEncounterDBCMap::const_iterator itr = _dungeonEncounterMap.find(ID);
        if (itr != _dungeonEncounterMap.end())
            return &itr->second;
        return nullptr;
    }

    DurabilityCostsDBC const* GetDurabilityCostsDBC(uint32 ID)
    {
        DurabilityCostsDBCMap::const_iterator itr = _durabilityCoastsMap.find(ID);
        if (itr != _durabilityCoastsMap.end())
            return &itr->second;
        return nullptr;
    }

    DurabilityQualityDBC const* GetDurabilityQualityDBC(uint32 ID)
    {
        DurabilityQualityDBCMap::const_iterator itr = _durabilityQualityMap.find(ID);
        if (itr != _durabilityQualityMap.end())
            return &itr->second;
        return nullptr;
    }

    EmotesDBC const* GetEmotesDBC(uint32 ID)
    {
        EmotesDBCMap::const_iterator itr = _emotesMap.find(ID);
        if (itr != _emotesMap.end())
            return &itr->second;
        return nullptr;
    }

    EmotesTextDBC const* GetEmotesTextDBC(uint32 ID)
    {
        EmotesTextDBCMap::const_iterator itr = _emotesTextMap.find(ID);
        if (itr != _emotesTextMap.end())
            return &itr->second;
        return nullptr;
    }

    EmotesTextSoundDBC const* GetEmotesTextSoundDBCWithParam(uint32 emote, uint8 race, uint8 gender)
    {
        for (EmotesTextSoundDBCMap::const_iterator itr = _emotesTextSoundMap.begin(); itr != _emotesTextSoundMap.end(); ++itr)
        {
            if (itr->second.EmotesTextID == emote &&
                itr->second.RaceID == race &&
                itr->second.SexID == gender)
                return &itr->second;
        }
        return nullptr;
    }

    FactionDBCMap const& GetFactionDBCMap() const { return _factionMap; }
    FactionDBC const* GetFactionDBC(uint32 ID)
    {
        FactionDBCMap::const_iterator itr = _factionMap.find(ID);
        if (itr != _factionMap.end())
            return &itr->second;
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
    void _Load_CreatureDisplayInfo();
    void _Load_CreatureDisplayInfoExtra();
    void _Load_CreatureFamily();
    void _Load_CreatureModelData();
    void _Load_CreatureSpellData();
    void _Load_CreatureType();
    void _Load_CurrencyCategory();
    void _Load_CurrencyTypes();
    void _Load_DestructibleModelData();
    void _Load_DungeonEncounter();
    void _Load_DurabilityCosts();
    void _Load_DurabilityQuality();
    void _Load_Emotes();
    void _Load_EmotesText();
    void _Load_EmotesTextSound();
    void _Load_Faction();

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
    CreatureDisplayInfoDBCMap _creatureDisplayInfoMap;
    CreatureDisplayInfoExtraDBCMap _creatureDisplayInfoExtraMap;
    CreatureFamilyDBCMap _creatureFamilyMap;
    CreatureModelDataDBCMap _creatureModelDataMap;
    CreatureSpellDataDBCMap _creatureSpellDataMap;
    CreatureTypeDBCMap _creatureTypeMap;
    CurrencyCategoryDBCMap _currencyCategoryMap;
    CurrencyTypesDBCMap _currencyTypesMap;
    DestructibleModelDataDBCMap _destructibleModelDataMap;
    DungeonEncounterDBCMap _dungeonEncounterMap;
    DurabilityCostsDBCMap _durabilityCoastsMap;
    DurabilityQualityDBCMap _durabilityQualityMap;
    EmotesDBCMap _emotesMap;
    EmotesTextDBCMap _emotesTextMap;
    EmotesTextSoundDBCMap _emotesTextSoundMap;
    FactionDBCMap _factionMap;
};

#define sDBCStoresMgr DBCStoresMgr::instance()

#endif // _DBCMGR_H
