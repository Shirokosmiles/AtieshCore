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
#include "Regex.h"

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
typedef std::unordered_map<uint32 /*ID*/, FactionTemplateDBC> FactionTemplateDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GameObjectArtKitDBC> GameObjectArtKitDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GameObjectDisplayInfoDBC> GameObjectDisplayInfoDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GemPropertiesDBC> GemPropertiesDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GlyphPropertiesDBC> GlyphPropertiesDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GlyphSlotDBC> GlyphSlotDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GtBarberShopCostBaseDBC> GtBarberShopCostBaseDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GtCombatRatingsDBC> GtCombatRatingsDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GtChanceToMeleeCritBaseDBC> GtChanceToMeleeCritBaseDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GtChanceToMeleeCritDBC> GtChanceToMeleeCritDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GtChanceToSpellCritBaseDBC> GtChanceToSpellCritBaseDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GtChanceToSpellCritDBC> GtChanceToSpellCritDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GtNPCManaCostScalerDBC> GtNPCManaCostScalerDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GtOCTClassCombatRatingScalarDBC> GtOCTClassCombatRatingScalarDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GtOCTRegenHPDBC> GtOCTRegenHPDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GtOCTRegenMPDBC> GtOCTRegenMPDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GtRegenHPPerSptDBC> GtRegenHPPerSptDBCMap;
typedef std::unordered_map<uint32 /*ID*/, GtRegenMPPerSptDBC> GtRegenMPPerSptDBCMap;
typedef std::unordered_map<uint32 /*ID*/, HolidaysDBC> HolidaysDBCMap;

typedef std::unordered_map<uint32 /*ID*/, ItemDBC> ItemDBCMap;
typedef std::unordered_map<uint32 /*ID*/, ItemBagFamilyDBC> ItemBagFamilyDBCMap;
typedef std::unordered_map<uint32 /*ID*/, ItemDisplayInfoDBC> ItemDisplayInfoDBCMap;
typedef std::unordered_map<uint32 /*ID*/, ItemExtendedCostDBC> ItemExtendedCostDBCMap;
typedef std::unordered_map<uint32 /*ID*/, ItemLimitCategoryDBC> ItemLimitCategoryDBCMap;
typedef std::unordered_map<uint32 /*ID*/, ItemRandomPropertiesDBC> ItemRandomPropertiesDBCMap;
typedef std::unordered_map<uint32 /*ID*/, ItemRandomSuffixDBC> ItemRandomSuffixDBCMap;
typedef std::unordered_map<uint32 /*ID*/, ItemSetDBC> ItemSetDBCMap;
typedef std::unordered_map<uint32 /*ID*/, LFGDungeonDBC> LFGDungeonDBCMap;
typedef std::unordered_map<uint32 /*ID*/, LightDBC> LightDBCMap;
typedef std::unordered_map<uint32 /*ID*/, LiquidTypeDBC> LiquidTypeDBCMap;
typedef std::unordered_map<uint32 /*ID*/, LockDBC> LockDBCMap;
typedef std::unordered_map<uint32 /*ID*/, MailTemplateDBC> MailTemplateDBCMap;
typedef std::unordered_map<uint32 /*ID*/, MapDBC> MapDBCMap;
typedef std::unordered_map<uint32 /*ID*/, MapDifficultyDBC> MapDifficultyDBCMap;
typedef std::unordered_map<uint32 /*ID*/, MovieDBC> MovieDBCMap;
typedef std::unordered_map<uint32 /*ID*/, NamesProfanityDBC> NamesProfanityDBCMap;
typedef std::unordered_map<uint32 /*ID*/, NamesReservedDBC> NamesReservedDBCMap;
typedef std::unordered_map<uint32 /*ID*/, OverrideSpellDataDBC> OverrideSpellDataDBCMap;
typedef std::unordered_map<uint32 /*ID*/, PowerDisplayDBC> PowerDisplayDBCMap;
typedef std::unordered_map<uint32 /*ID*/, PvPDifficultyDBC> PvPDifficultyDBCMap;
typedef std::unordered_map<uint32 /*ID*/, QuestSortDBC> QuestSortDBCMap;
typedef std::unordered_map<uint32 /*ID*/, QuestXPDBC> QuestXPDBCMap;
typedef std::unordered_map<uint32 /*ID*/, QuestFactionRewardDBC> QuestFactionRewardDBCMap;
typedef std::unordered_map<uint32 /*ID*/, RandPropPointsDBC> RandPropPointsDBCMap;
typedef std::unordered_map<uint32 /*ID*/, ScalingStatDistributionDBC> ScalingStatDistributionDBCMap;
typedef std::unordered_map<uint32 /*ID*/, ScalingStatValuesDBC> ScalingStatValuesDBCMap;
typedef std::unordered_map<uint32 /*ID*/, SkillLineDBC> SkillLineDBCMap;
typedef std::unordered_map<uint32 /*ID*/, SkillLineAbilityDBC> SkillLineAbilityDBCMap;
typedef std::unordered_map<uint32 /*ID*/, SkillRaceClassInfoDBC> SkillRaceClassInfoDBCMap;

typedef std::array<std::vector<Trinity::wregex>, TOTAL_LOCALES> NameValidationRegexContainer;
typedef std::set<uint32> PetFamilySpellsSet;
typedef std::map<uint32, PetFamilySpellsSet> PetFamilySpellsStore;

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

    FactionTemplateDBC const* GetFactionTemplateDBC(uint32 ID)
    {
        FactionTemplateDBCMap::const_iterator itr = _factionTemplateMap.find(ID);
        if (itr != _factionTemplateMap.end())
            return &itr->second;
        return nullptr;
    }

    GameObjectArtKitDBC const* GetGameObjectArtKitDBC(uint32 ID)
    {
        GameObjectArtKitDBCMap::const_iterator itr = _gameobjectArtKitMap.find(ID);
        if (itr != _gameobjectArtKitMap.end())
            return &itr->second;
        return nullptr;
    }

    GameObjectDisplayInfoDBC const* GetGameObjectDisplayInfoDBC(uint32 ID)
    {
        GameObjectDisplayInfoDBCMap::const_iterator itr = _gameobjectDisplayInfoMap.find(ID);
        if (itr != _gameobjectDisplayInfoMap.end())
            return &itr->second;
        return nullptr;
    }

    GemPropertiesDBC const* GetGemPropertiesDBC(uint32 ID)
    {
        GemPropertiesDBCMap::const_iterator itr = _gemPropertiesMap.find(ID);
        if (itr != _gemPropertiesMap.end())
            return &itr->second;
        return nullptr;
    }

    GlyphPropertiesDBC const* GetGlyphPropertiesDBC(uint32 ID)
    {
        GlyphPropertiesDBCMap::const_iterator itr = _glyphPropertiesMap.find(ID);
        if (itr != _glyphPropertiesMap.end())
            return &itr->second;
        return nullptr;
    }

    GlyphSlotDBCMap const& GetGlyphSlotDBCMap() const { return _glyphSlotMap; }
    GlyphSlotDBC const* GetGlyphSlotDBC(uint32 ID)
    {
        GlyphSlotDBCMap::const_iterator itr = _glyphSlotMap.find(ID);
        if (itr != _glyphSlotMap.end())
            return &itr->second;
        return nullptr;
    }

    GtBarberShopCostBaseDBC const* GetGtBarberShopCostBaseDBC(uint32 ID)
    {
        GtBarberShopCostBaseDBCMap::const_iterator itr = _gtBarberShopCostBaseMap.find(ID);
        if (itr != _gtBarberShopCostBaseMap.end())
            return &itr->second;
        return nullptr;
    }

    GtCombatRatingsDBC const* GetGtCombatRatingsDBC(uint32 ID)
    {
        GtCombatRatingsDBCMap::const_iterator itr = _gtCombatRatingsMap.find(ID);
        if (itr != _gtCombatRatingsMap.end())
            return &itr->second;
        return nullptr;
    }

    GtChanceToMeleeCritBaseDBC const* GetGtChanceToMeleeCritBaseDBC(uint32 ID)
    {
        GtChanceToMeleeCritBaseDBCMap::const_iterator itr = _gtChanceToMeleeCritBaseMap.find(ID);
        if (itr != _gtChanceToMeleeCritBaseMap.end())
            return &itr->second;
        return nullptr;
    }

    GtChanceToMeleeCritDBC const* GetGtChanceToMeleeCritDBC(uint32 ID)
    {
        GtChanceToMeleeCritDBCMap::const_iterator itr = _gtChanceToMeleeCritMap.find(ID);
        if (itr != _gtChanceToMeleeCritMap.end())
            return &itr->second;
        return nullptr;
    }

    GtChanceToSpellCritBaseDBC const* GetGtChanceToSpellCritBaseDBC(uint32 ID)
    {
        GtChanceToSpellCritBaseDBCMap::const_iterator itr = _gtChanceToSpellCritBaseMap.find(ID);
        if (itr != _gtChanceToSpellCritBaseMap.end())
            return &itr->second;
        return nullptr;
    }

    GtChanceToSpellCritDBC const* GetGtChanceToSpellCritDBC(uint32 ID)
    {
        GtChanceToSpellCritDBCMap::const_iterator itr = _gtChanceToSpellCritMap.find(ID);
        if (itr != _gtChanceToSpellCritMap.end())
            return &itr->second;
        return nullptr;
    }

    GtNPCManaCostScalerDBC const* GetGtNPCManaCostScalerDBC(uint32 ID)
    {
        GtNPCManaCostScalerDBCMap::const_iterator itr = _gtNPCManaCostScalerMap.find(ID);
        if (itr != _gtNPCManaCostScalerMap.end())
            return &itr->second;
        return nullptr;
    }

    GtOCTClassCombatRatingScalarDBC const* GetGtOCTClassCombatRatingScalarDBC(uint32 ID)
    {
        GtOCTClassCombatRatingScalarDBCMap::const_iterator itr = _gtOCTClassCombatRatingScalarMap.find(ID);
        if (itr != _gtOCTClassCombatRatingScalarMap.end())
            return &itr->second;
        return nullptr;
    }

    GtOCTRegenHPDBC const* GetGtOCTRegenHPDBC(uint32 ID)
    {
        GtOCTRegenHPDBCMap::const_iterator itr = _gtOCTRegenHPMap.find(ID);
        if (itr != _gtOCTRegenHPMap.end())
            return &itr->second;
        return nullptr;
    }

    GtOCTRegenMPDBC const* GetGtOCTRegenMPDBC(uint32 ID)
    {
        GtOCTRegenMPDBCMap::const_iterator itr = _gtOCTRegenMPMap.find(ID);
        if (itr != _gtOCTRegenMPMap.end())
            return &itr->second;
        return nullptr;
    }

    GtRegenHPPerSptDBC const* GetGtRegenHPPerSptDBC(uint32 ID)
    {
        GtRegenHPPerSptDBCMap::const_iterator itr = _gtRegenHPPerSptMap.find(ID);
        if (itr != _gtRegenHPPerSptMap.end())
            return &itr->second;
        return nullptr;
    }

    GtRegenMPPerSptDBC const* GetGtRegenMPPerSptDBC(uint32 ID)
    {
        GtRegenMPPerSptDBCMap::const_iterator itr = _gtRegenMPPerSptMap.find(ID);
        if (itr != _gtRegenMPPerSptMap.end())
            return &itr->second;
        return nullptr;
    }

    HolidaysDBC const* GetHolidaysDBC(uint32 ID)
    {
        HolidaysDBCMap::const_iterator itr = _holidaysMap.find(ID);
        if (itr != _holidaysMap.end())
            return &itr->second;
        return nullptr;
    }

    ItemDBCMap const& GetItemDBCMap() const { return _itemMap; }
    ItemDBC const* GetItemDBC(uint32 ID)
    {
        ItemDBCMap::const_iterator itr = _itemMap.find(ID);
        if (itr != _itemMap.end())
            return &itr->second;
        return nullptr;
    }

    ItemBagFamilyDBC const* GetItemBagFamilyDBC(uint32 ID)
    {
        ItemBagFamilyDBCMap::const_iterator itr = _itemBagFamilyMap.find(ID);
        if (itr != _itemBagFamilyMap.end())
            return &itr->second;
        return nullptr;
    }

    ItemDisplayInfoDBC const* GetItemDisplayInfoDBC(uint32 ID)
    {
        ItemDisplayInfoDBCMap::const_iterator itr = _itemDisplayInfoMap.find(ID);
        if (itr != _itemDisplayInfoMap.end())
            return &itr->second;
        return nullptr;
    }

    ItemExtendedCostDBC const* GetItemExtendedCostDBC(uint32 ID)
    {
        ItemExtendedCostDBCMap::const_iterator itr = _itemExtendedCostMap.find(ID);
        if (itr != _itemExtendedCostMap.end())
            return &itr->second;
        return nullptr;
    }

    ItemLimitCategoryDBC const* GetItemLimitCategoryDBC(uint32 ID)
    {
        ItemLimitCategoryDBCMap::const_iterator itr = _itemLimitCategoryMap.find(ID);
        if (itr != _itemLimitCategoryMap.end())
            return &itr->second;
        return nullptr;
    }

    ItemRandomPropertiesDBC const* GetItemRandomPropertiesDBC(uint32 ID)
    {
        ItemRandomPropertiesDBCMap::const_iterator itr = _itemRandomPropertiesMap.find(ID);
        if (itr != _itemRandomPropertiesMap.end())
            return &itr->second;
        return nullptr;
    }

    uint32 GetNumRowItemRandomSuffixMap() const { return _itemRandomSuffixTheLastIndex; }
    ItemRandomSuffixDBC const* GetItemRandomSuffixDBC(uint32 ID)
    {
        ItemRandomSuffixDBCMap::const_iterator itr = _itemRandomSuffixMap.find(ID);
        if (itr != _itemRandomSuffixMap.end())
            return &itr->second;
        return nullptr;
    }

    ItemSetDBCMap const& GetItemSetMap() const { return _itemSetMap; }
    ItemSetDBC const* GetItemSetDBC(uint32 ID)
    {
        ItemSetDBCMap::const_iterator itr = _itemSetMap.find(ID);
        if (itr != _itemSetMap.end())
            return &itr->second;
        return nullptr;
    }

    LFGDungeonDBCMap const& GetLFGDungeonDBCMap() const { return _lfgDungeonMap; }
    LFGDungeonDBC const* GetLFGDungeonDBC(uint32 ID)
    {
        LFGDungeonDBCMap::const_iterator itr = _lfgDungeonMap.find(ID);
        if (itr != _lfgDungeonMap.end())
            return &itr->second;
        return nullptr;
    }

    LightDBC const* GetLightDBC(uint32 ID)
    {
        LightDBCMap::const_iterator itr = _lightMap.find(ID);
        if (itr != _lightMap.end())
            return &itr->second;
        return nullptr;
    }

    uint32 GetDefaultMapLight(uint32 mapId) // UNUSED
    {
        for (LightDBCMap::const_iterator itr = _lightMap.begin(); itr != _lightMap.end(); ++itr)
        {
            if (itr->second.ContinentID == mapId &&
                itr->second.GameCoords.X == 0.0f &&
                itr->second.GameCoords.Y == 0.0f &&
                itr->second.GameCoords.Z == 0.0f)
                return itr->second.ID;
        }
        return 0;
    }

    LFGDungeonDBC const* GetLFGDungeon(uint32 mapId, Difficulty difficulty)
    {
        for (LFGDungeonDBCMap::const_iterator itr = _lfgDungeonMap.begin(); itr != _lfgDungeonMap.end(); ++itr)
        {
            if (itr->second.MapID == int32(mapId) &&
                Difficulty(itr->second.Difficulty) == difficulty)
                return &itr->second;
        }
        return nullptr;
    }

    LiquidTypeDBCMap const& GetLiquidTypeDBCMap() const { return _liquidTypeMap; }
    LiquidTypeDBC const* GetLiquidTypeDBC(uint32 ID)
    {
        LiquidTypeDBCMap::const_iterator itr = _liquidTypeMap.find(ID);
        if (itr != _liquidTypeMap.end())
            return &itr->second;
        return nullptr;
    }

    LockDBC const* GetLockDBC(uint32 ID)
    {
        LockDBCMap::const_iterator itr = _lockMap.find(ID);
        if (itr != _lockMap.end())
            return &itr->second;
        return nullptr;
    }

    MailTemplateDBCMap const& GetMailTemplateDBCMap() const { return _mailTemplateMap; }
    MailTemplateDBC const* GetMailTemplateDBC(uint32 ID)
    {
        MailTemplateDBCMap::const_iterator itr = _mailTemplateMap.find(ID);
        if (itr != _mailTemplateMap.end())
            return &itr->second;
        return nullptr;
    }

    MapDBCMap const& GetMapDBCMap() const { return _mapMap; }
    MapDBC const* GetMapDBC(uint32 ID)
    {
        MapDBCMap::const_iterator itr = _mapMap.find(ID);
        if (itr != _mapMap.end())
            return &itr->second;
        return nullptr;
    }

    MapDifficultyDBCMap const& GetMapDifficultyDBCMap() const { return _mapDifficultyMap; }
    MapDifficultyDBC const* GetMapDifficultyData(uint32 mapId, Difficulty difficulty)
    {
        for (MapDifficultyDBCMap::const_iterator itr = _mapDifficultyMap.begin(); itr != _mapDifficultyMap.end(); ++itr)
        {
            if (itr->second.MapID == mapId &&
                Difficulty(itr->second.Difficulty) == difficulty)
                return &itr->second;
        }
        return nullptr;
    }

    MapDifficultyDBC const* GetDownscaledMapDifficultyData(uint32 mapId, Difficulty& difficulty)
    {
        uint32 tmpDiff = difficulty;
        MapDifficultyDBC const* mapDiff = GetMapDifficultyData(mapId, Difficulty(tmpDiff));
        if (!mapDiff)
        {
            if (tmpDiff > RAID_DIFFICULTY_25MAN_NORMAL) // heroic, downscale to normal
                tmpDiff -= 2;
            else
                tmpDiff -= 1;   // any non-normal mode for raids like tbc (only one mode)

            // pull new data
            mapDiff = GetMapDifficultyData(mapId, Difficulty(tmpDiff)); // we are 10 normal or 25 normal
            if (!mapDiff)
            {
                tmpDiff -= 1;
                mapDiff = GetMapDifficultyData(mapId, Difficulty(tmpDiff)); // 10 normal
            }
        }

        difficulty = Difficulty(tmpDiff);
        return mapDiff;
    }

    MovieDBC const* GetMovieDBC(uint32 ID)
    {
        MovieDBCMap::const_iterator itr = _movieMap.find(ID);
        if (itr != _movieMap.end())
            return &itr->second;
        return nullptr;
    }

    OverrideSpellDataDBC const* GetOverrideSpellDataDBC(uint32 ID)
    {
        OverrideSpellDataDBCMap::const_iterator itr = _overrideSpellDataMap.find(ID);
        if (itr != _overrideSpellDataMap.end())
            return &itr->second;
        return nullptr;
    }

    PowerDisplayDBC const* GetPowerDisplayDBC(uint32 ID)
    {
        PowerDisplayDBCMap::const_iterator itr = _powerDisplayMap.find(ID);
        if (itr != _powerDisplayMap.end())
            return &itr->second;
        return nullptr;
    }

    PvPDifficultyDBC const* GetBattlegroundBracketByLevel(uint32 mapid, uint32 level)
    {
        PvPDifficultyDBC const* maxEntry = nullptr;              // used for level > max listed level case
        for (PvPDifficultyDBCMap::const_iterator itr = _pvpDifficultyMap.begin(); itr != _pvpDifficultyMap.end(); ++itr)
        {
            // skip unrelated and too-high brackets
            if (itr->second.MapID != mapid || itr->second.MinLevel > level)
                continue;

            // exactly fit
            if (itr->second.MaxLevel >= level)
                return &itr->second;

            // remember for possible out-of-range case (search higher from existed)
            if (!maxEntry || maxEntry->MaxLevel < itr->second.MaxLevel)
                maxEntry = &itr->second;
        }
        return maxEntry;
    }

    PvPDifficultyDBC const* GetBattlegroundBracketById(uint32 mapid, BattlegroundBracketId id)
    {
        for (PvPDifficultyDBCMap::const_iterator itr = _pvpDifficultyMap.begin(); itr != _pvpDifficultyMap.end(); ++itr)
        {
            if (itr->second.MapID == mapid && itr->second.GetBracketId() == id)
                return &itr->second;
        }
        return nullptr;
    }

    QuestSortDBC const* GetQuestSortDBC(uint32 ID)
    {
        QuestSortDBCMap::const_iterator itr = _questSortMap.find(ID);
        if (itr != _questSortMap.end())
            return &itr->second;
        return nullptr;
    }

    QuestXPDBC const* GetQuestXPDBC(uint32 ID)
    {
        QuestXPDBCMap::const_iterator itr = _questXPMap.find(ID);
        if (itr != _questXPMap.end())
            return &itr->second;
        return nullptr;
    }

    QuestFactionRewardDBC const* GetQuestFactionRewardDBC(uint32 ID)
    {
        QuestFactionRewardDBCMap::const_iterator itr = _questFactionRewardMap.find(ID);
        if (itr != _questFactionRewardMap.end())
            return &itr->second;
        return nullptr;
    }

    RandPropPointsDBC const* GetRandPropPointsDBC(uint32 ID)
    {
        RandPropPointsDBCMap::const_iterator itr = _randPropPointsMap.find(ID);
        if (itr != _randPropPointsMap.end())
            return &itr->second;
        return nullptr;
    }

    ScalingStatDistributionDBC const* GetScalingStatDistributionDBC(uint32 ID)
    {
        ScalingStatDistributionDBCMap::const_iterator itr = _scalingStatDistributionMap.find(ID);
        if (itr != _scalingStatDistributionMap.end())
            return &itr->second;
        return nullptr;
    }

    ScalingStatValuesDBC const* GetScalingStatValuesDBC(uint32 ID)
    {
        ScalingStatValuesDBCMap::const_iterator itr = _scalingStatValuesMap.find(ID);
        if (itr != _scalingStatValuesMap.end())
            return &itr->second;
        return nullptr;
    }

    SkillLineDBCMap const& GetSkillLineDBCMap() const { return _skillLineMap; }
    SkillLineDBC const* GetSkillLineDBC(uint32 ID)
    {
        SkillLineDBCMap::const_iterator itr = _skillLineMap.find(ID);
        if (itr != _skillLineMap.end())
            return &itr->second;
        return nullptr;
    }

    SkillLineAbilityDBCMap const& GetSkillLineAbilityDBCMap() const { return _skillLineAbilityMap; }
    SkillLineAbilityDBC const* GetSkillLineAbilityDBC(uint32 ID)
    {
        SkillLineAbilityDBCMap::const_iterator itr = _skillLineAbilityMap.find(ID);
        if (itr != _skillLineAbilityMap.end())
            return &itr->second;
        return nullptr;
    }

    SkillRaceClassInfoDBC const* GetSkillRaceClassInfo(uint32 skill, uint8 race, uint8 class_)
    {
        for (SkillRaceClassInfoDBCMap::const_iterator itr = _skillRaceClassInfoMap.begin(); itr != _skillRaceClassInfoMap.end(); ++itr)
        {
            if (itr->second.SkillID != skill)
                continue;
            if (itr->second.RaceMask && !(itr->second.RaceMask & (1 << (race - 1))))
                continue;
            if (itr->second.ClassMask && !(itr->second.ClassMask & (1 << (class_ - 1))))
                continue;

            return &itr->second;
        }
        return nullptr;
    }

    // Handlers for working with DBC data
    ResponseCodes ValidateName(std::wstring const& name, LocaleConstant locale)
    {
        if (locale >= TOTAL_LOCALES)
            return RESPONSE_FAILURE;

        for (Trinity::wregex const& regex : NamesProfaneValidators[locale])
            if (Trinity::regex_search(name, regex))
                return CHAR_NAME_PROFANE;

        // regexes at TOTAL_LOCALES are loaded from NamesReserved which is not locale specific
        for (Trinity::wregex const& regex : NamesReservedValidators[locale])
            if (Trinity::regex_search(name, regex))
                return CHAR_NAME_RESERVED;

        return CHAR_NAME_SUCCESS;
    }

    PetFamilySpellsStore const& GetPetFamilySpellsStore() { return _petFamilySpellsStore; }

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
    void _Load_FactionTemplate();
    void _Load_GameObjectArtKit();
    void _Load_GameObjectDisplayInfo();
    void _Load_GemProperties();
    void _Load_GlyphProperties();
    void _Load_GlyphSlot();
    void _Load_gtBarberShopCostBase();
    void _Load_gtCombatRatings();
    void _Load_gtChanceToMeleeCritBase();
    void _Load_gtChanceToMeleeCrit();
    void _Load_gtChanceToSpellCritBase();
    void _Load_gtChanceToSpellCrit();
    void _Load_gtNPCManaCostScaler();
    void _Load_gtOCTClassCombatRatingScalar();
    void _Load_gtOCTRegenHP();
    void _Load_gtOCTRegenMP();
    void _Load_gtRegenHPPerSpt();
    void _Load_gtRegenMPPerSpt();
    void _Load_Holidays();
    void _Load_Item();
    void _Load_ItemBagFamily();
    void _Load_ItemDisplayInfo();
    void _Load_ItemExtendedCost();
    void _Load_ItemLimitCategory();
    void _Load_ItemRandomProperties();
    void _Load_ItemRandomSuffix();
    void _Load_ItemSet();
    void _Load_LFGDungeons();
    void _Load_Light();
    void _Load_LiquidType();
    void _Load_Lock();
    void _Load_MailTemplate();
    void _Load_Map();
    void _Load_MapDifficulty();
    void _Load_Movie();
    void _Load_NamesProfanity();
    void _Load_NamesReserved();
    void _Load_OverrideSpellData();
    void _Load_PowerDisplay();
    void _Load_PvpDifficulty();
    void _Load_QuestSort();
    void _Load_QuestXP();
    void _Load_QuestFactionReward();
    void _Load_RandPropPoints();
    void _Load_ScalingStatDistribution();
    void _Load_ScalingStatValues();
    void _Load_SkillLine();
    void _Load_SkillLineAbility();
    void _Load_SkillRaceClassInfo();

    // Handle others containers
    void _Handle_NamesProfanityRegex();
    void _Handle_NamesReservedRegex();
    void _Handle_PetFamilySpellsStore();

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
    FactionTemplateDBCMap _factionTemplateMap;
    GameObjectArtKitDBCMap _gameobjectArtKitMap;
    GameObjectDisplayInfoDBCMap _gameobjectDisplayInfoMap;
    GemPropertiesDBCMap _gemPropertiesMap;
    GlyphPropertiesDBCMap _glyphPropertiesMap;
    GlyphSlotDBCMap _glyphSlotMap;
    GtBarberShopCostBaseDBCMap _gtBarberShopCostBaseMap;
    GtCombatRatingsDBCMap _gtCombatRatingsMap;
    GtChanceToMeleeCritBaseDBCMap _gtChanceToMeleeCritBaseMap;
    GtChanceToMeleeCritDBCMap _gtChanceToMeleeCritMap;
    GtChanceToSpellCritBaseDBCMap _gtChanceToSpellCritBaseMap;
    GtChanceToSpellCritDBCMap _gtChanceToSpellCritMap;
    GtNPCManaCostScalerDBCMap _gtNPCManaCostScalerMap;
    GtOCTClassCombatRatingScalarDBCMap _gtOCTClassCombatRatingScalarMap;
    GtOCTRegenHPDBCMap _gtOCTRegenHPMap;
    GtOCTRegenMPDBCMap _gtOCTRegenMPMap;
    GtRegenHPPerSptDBCMap _gtRegenHPPerSptMap;
    GtRegenMPPerSptDBCMap _gtRegenMPPerSptMap;
    HolidaysDBCMap _holidaysMap;
    ItemDBCMap _itemMap;
    ItemBagFamilyDBCMap _itemBagFamilyMap;
    ItemDisplayInfoDBCMap _itemDisplayInfoMap;
    ItemExtendedCostDBCMap _itemExtendedCostMap;
    ItemLimitCategoryDBCMap _itemLimitCategoryMap;
    ItemRandomPropertiesDBCMap _itemRandomPropertiesMap;
    ItemRandomSuffixDBCMap _itemRandomSuffixMap;
    uint32 _itemRandomSuffixTheLastIndex;
    ItemSetDBCMap _itemSetMap;
    LFGDungeonDBCMap _lfgDungeonMap;
    LightDBCMap _lightMap;
    LiquidTypeDBCMap _liquidTypeMap;
    LockDBCMap _lockMap;
    MailTemplateDBCMap _mailTemplateMap;
    MapDBCMap _mapMap;
    MapDifficultyDBCMap _mapDifficultyMap;
    MovieDBCMap _movieMap;
    NamesProfanityDBCMap _namesProfanityMap;
    NamesReservedDBCMap _namesReservedMap;
    OverrideSpellDataDBCMap _overrideSpellDataMap;
    PowerDisplayDBCMap _powerDisplayMap;
    PvPDifficultyDBCMap _pvpDifficultyMap;
    QuestSortDBCMap _questSortMap;
    QuestXPDBCMap _questXPMap;
    QuestFactionRewardDBCMap _questFactionRewardMap;
    RandPropPointsDBCMap _randPropPointsMap;
    ScalingStatDistributionDBCMap _scalingStatDistributionMap;
    ScalingStatValuesDBCMap _scalingStatValuesMap;
    SkillLineDBCMap _skillLineMap;
    SkillLineAbilityDBCMap _skillLineAbilityMap;
    SkillRaceClassInfoDBCMap _skillRaceClassInfoMap;

    // handler containers
    NameValidationRegexContainer NamesProfaneValidators;
    NameValidationRegexContainer NamesReservedValidators;

    PetFamilySpellsStore _petFamilySpellsStore;
};

#define sDBCStoresMgr DBCStoresMgr::instance()

#endif // _DBCMGR_H
