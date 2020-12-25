/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
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

#include "DBCStores.h"
#include "DBCFileLoader.h"
#include "DBCfmt.h"
#include "DBCStoresMgr.h"
#include "Errors.h"
#include "IteratorPair.h"
#include "Log.h"
#include "ObjectDefines.h"
#include "Regex.h"
#include "SharedDefines.h"
#include "SpellMgr.h"
#include "Timer.h"

// temporary hack until includes are sorted out (don't want to pull in Windows.h)
#ifdef GetClassName
#undef GetClassName
#endif

typedef std::map<uint16, uint32> AreaFlagByAreaID;
typedef std::map<uint32, uint32> AreaFlagByMapID;

typedef std::tuple<int16, int8, int32> WMOAreaTableKey;
typedef std::map<WMOAreaTableKey, WMOAreaTableEntry const*> WMOAreaInfoByTripple;

//DBCStorage <AreaTableEntry> sAreaTableStore(AreaTableEntryfmt);
//DBCStorage <AreaGroupEntry> sAreaGroupStore(AreaGroupEntryfmt);
//DBCStorage <AreaPOIEntry> sAreaPOIStore(AreaPOIEntryfmt);

static WMOAreaInfoByTripple sWMOAreaInfoByTripple;

//DBCStorage <AchievementEntry> sAchievementStore(Achievementfmt);
//DBCStorage <AchievementCriteriaEntry> sAchievementCriteriaStore(AchievementCriteriafmt);
//DBCStorage <AreaTriggerEntry> sAreaTriggerStore(AreaTriggerEntryfmt);
//DBCStorage <AuctionHouseEntry> sAuctionHouseStore(AuctionHouseEntryfmt);
//DBCStorage <BankBagSlotPricesEntry> sBankBagSlotPricesStore(BankBagSlotPricesEntryfmt);
//DBCStorage <BannedAddOnsEntry> sBannedAddOnsStore(BannedAddOnsfmt);
//DBCStorage <BattlemasterListEntry> sBattlemasterListStore(BattlemasterListEntryfmt);
//DBCStorage <BarberShopStyleEntry> sBarberShopStyleStore(BarberShopStyleEntryfmt);
//DBCStorage <CharacterFacialHairStylesEntry> sCharacterFacialHairStylesStore(CharacterFacialHairStylesfmt);
//std::unordered_map<uint32, CharacterFacialHairStylesEntry const*> sCharFacialHairMap;
//DBCStorage <CharSectionsEntry> sCharSectionsStore(CharSectionsEntryfmt);
//std::unordered_multimap<uint32, CharSectionsEntry const*> sCharSectionMap;
//DBCStorage <CharStartOutfitEntry> sCharStartOutfitStore(CharStartOutfitEntryfmt);
//std::map<uint32, CharStartOutfitEntry const*> sCharStartOutfitMap;
//DBCStorage <CharTitlesEntry> sCharTitlesStore(CharTitlesEntryfmt);
//DBCStorage <ChatChannelsEntry> sChatChannelsStore(ChatChannelsEntryfmt);
//DBCStorage <ChrClassesEntry> sChrClassesStore(ChrClassesEntryfmt);
//DBCStorage <ChrRacesEntry> sChrRacesStore(ChrRacesEntryfmt);
//DBCStorage <CinematicCameraEntry> sCinematicCameraStore(CinematicCameraEntryfmt);
//DBCStorage <CinematicSequencesEntry> sCinematicSequencesStore(CinematicSequencesEntryfmt);
//DBCStorage <CreatureDisplayInfoEntry> sCreatureDisplayInfoStore(CreatureDisplayInfofmt);
//DBCStorage <CreatureDisplayInfoExtraEntry> sCreatureDisplayInfoExtraStore(CreatureDisplayInfoExtrafmt);
//DBCStorage <CreatureFamilyEntry> sCreatureFamilyStore(CreatureFamilyfmt);
//DBCStorage <CreatureModelDataEntry> sCreatureModelDataStore(CreatureModelDatafmt);
//DBCStorage <CreatureSpellDataEntry> sCreatureSpellDataStore(CreatureSpellDatafmt);
//DBCStorage <CreatureTypeEntry> sCreatureTypeStore(CreatureTypefmt);
//DBCStorage <CurrencyTypesEntry> sCurrencyTypesStore(CurrencyTypesfmt);

//DBCStorage <DestructibleModelDataEntry> sDestructibleModelDataStore(DestructibleModelDatafmt);
//DBCStorage <DungeonEncounterEntry> sDungeonEncounterStore(DungeonEncounterfmt);
//DBCStorage <DurabilityQualityEntry> sDurabilityQualityStore(DurabilityQualityfmt);
//DBCStorage <DurabilityCostsEntry> sDurabilityCostsStore(DurabilityCostsfmt);

//DBCStorage <EmotesEntry> sEmotesStore(EmotesEntryfmt);
//DBCStorage <EmotesTextEntry> sEmotesTextStore(EmotesTextEntryfmt);
//typedef std::tuple<uint32, uint32, uint32> EmotesTextSoundKey;
//static std::map<EmotesTextSoundKey, EmotesTextSoundEntry const*> sEmotesTextSoundMap;
//DBCStorage <EmotesTextSoundEntry> sEmotesTextSoundStore(EmotesTextSoundEntryfmt);

//typedef std::map<uint32, SimpleFactionsList> FactionTeamMap;
//static FactionTeamMap sFactionTeamMap;
//DBCStorage <FactionEntry> sFactionStore(FactionEntryfmt);
//DBCStorage <FactionTemplateEntry> sFactionTemplateStore(FactionTemplateEntryfmt);

// Used exclusively for data validation
//DBCStorage <GameObjectArtKitEntry> sGameObjectArtKitStore(GameObjectArtKitfmt);

//DBCStorage <GameObjectDisplayInfoEntry> sGameObjectDisplayInfoStore(GameObjectDisplayInfofmt);
//DBCStorage <GemPropertiesEntry> sGemPropertiesStore(GemPropertiesEntryfmt);
//DBCStorage <GlyphPropertiesEntry> sGlyphPropertiesStore(GlyphPropertiesfmt);
//DBCStorage <GlyphSlotEntry> sGlyphSlotStore(GlyphSlotfmt);

//DBCStorage <GtBarberShopCostBaseEntry>    sGtBarberShopCostBaseStore(GtBarberShopCostBasefmt);
//DBCStorage <GtCombatRatingsEntry>         sGtCombatRatingsStore(GtCombatRatingsfmt);
//DBCStorage <GtChanceToMeleeCritBaseEntry> sGtChanceToMeleeCritBaseStore(GtChanceToMeleeCritBasefmt);
//DBCStorage <GtChanceToMeleeCritEntry>     sGtChanceToMeleeCritStore(GtChanceToMeleeCritfmt);
//DBCStorage <GtChanceToSpellCritBaseEntry> sGtChanceToSpellCritBaseStore(GtChanceToSpellCritBasefmt);
//DBCStorage <GtChanceToSpellCritEntry>     sGtChanceToSpellCritStore(GtChanceToSpellCritfmt);
//DBCStorage <GtNPCManaCostScalerEntry>     sGtNPCManaCostScalerStore(GtNPCManaCostScalerfmt);
//DBCStorage <GtOCTClassCombatRatingScalarEntry> sGtOCTClassCombatRatingScalarStore(GtOCTClassCombatRatingScalarfmt);
//DBCStorage <GtOCTRegenHPEntry>            sGtOCTRegenHPStore(GtOCTRegenHPfmt);
//DBCStorage <GtOCTRegenMPEntry>            sGtOCTRegenMPStore(GtOCTRegenMPfmt);  -- not used currently
//DBCStorage <GtRegenHPPerSptEntry>         sGtRegenHPPerSptStore(GtRegenHPPerSptfmt);
//DBCStorage <GtRegenMPPerSptEntry>         sGtRegenMPPerSptStore(GtRegenMPPerSptfmt);

//DBCStorage <HolidaysEntry>                sHolidaysStore(Holidaysfmt);

//DBCStorage <ItemEntry>                    sItemStore(Itemfmt);
//DBCStorage <ItemBagFamilyEntry>           sItemBagFamilyStore(ItemBagFamilyfmt);
//DBCStorage <ItemCondExtCostsEntry> sItemCondExtCostsStore(ItemCondExtCostsEntryfmt);
//DBCStorage <ItemDisplayInfoEntry> sItemDisplayInfoStore(ItemDisplayTemplateEntryfmt);
//DBCStorage <ItemExtendedCostEntry> sItemExtendedCostStore(ItemExtendedCostEntryfmt);
//DBCStorage <ItemLimitCategoryEntry> sItemLimitCategoryStore(ItemLimitCategoryEntryfmt);
//DBCStorage <ItemRandomPropertiesEntry> sItemRandomPropertiesStore(ItemRandomPropertiesfmt);
//DBCStorage <ItemRandomSuffixEntry> sItemRandomSuffixStore(ItemRandomSuffixfmt);
//DBCStorage <ItemSetEntry> sItemSetStore(ItemSetEntryfmt);

//DBCStorage <LFGDungeonEntry> sLFGDungeonStore(LFGDungeonEntryfmt);
//DBCStorage <LightEntry> sLightStore(LightEntryfmt);
//DBCStorage <LiquidTypeEntry> sLiquidTypeStore(LiquidTypefmt);
//DBCStorage <LockEntry> sLockStore(LockEntryfmt);

//DBCStorage <MailTemplateEntry> sMailTemplateStore(MailTemplateEntryfmt);
//DBCStorage <MapEntry> sMapStore(MapEntryfmt);

// DBC used only for initialization sMapDifficultyMap at startup.
//DBCStorage <MapDifficultyEntry> sMapDifficultyStore(MapDifficultyEntryfmt); // only for loading
//MapDifficultyMap sMapDifficultyMap;

//DBCStorage <MovieEntry> sMovieStore(MovieEntryfmt);

//DBCStorage<NamesProfanityEntry> sNamesProfanityStore(NamesProfanityEntryfmt);
//DBCStorage<NamesReservedEntry> sNamesReservedStore(NamesReservedEntryfmt);
//typedef std::array<std::vector<Trinity::wregex>, TOTAL_LOCALES> NameValidationRegexContainer;
//NameValidationRegexContainer NamesProfaneValidators;
//NameValidationRegexContainer NamesReservedValidators;

//DBCStorage <OverrideSpellDataEntry> sOverrideSpellDataStore(OverrideSpellDatafmt);

//DBCStorage <PowerDisplayEntry> sPowerDisplayStore(PowerDisplayfmt);
//DBCStorage <PvPDifficultyEntry> sPvPDifficultyStore(PvPDifficultyfmt);

//DBCStorage <QuestSortEntry> sQuestSortStore(QuestSortEntryfmt);
//DBCStorage <QuestXPEntry>   sQuestXPStore(QuestXPfmt);
//DBCStorage <QuestFactionRewEntry>  sQuestFactionRewardStore(QuestFactionRewardfmt);
//DBCStorage <RandPropPointsEntry> sRandPropPointsStore(RandPropPointsfmt);
//DBCStorage <ScalingStatDistributionEntry> sScalingStatDistributionStore(ScalingStatDistributionfmt);
//DBCStorage <ScalingStatValuesEntry> sScalingStatValuesStore(ScalingStatValuesfmt);

//DBCStorage <SkillLineEntry> sSkillLineStore(SkillLinefmt);
//DBCStorage <SkillLineAbilityDBC> sSkillLineAbilityStore(SkillLineAbilityfmt);
//DBCStorage <SkillRaceClassInfoEntry> sSkillRaceClassInfoStore(SkillRaceClassInfofmt);
//SkillRaceClassInfoMap SkillRaceClassInfoBySkill;
//DBCStorage <SkillTiersEntry> sSkillTiersStore(SkillTiersfmt);

//DBCStorage <SoundEntriesEntry> sSoundEntriesStore(SoundEntriesfmt);

//DBCStorage <SpellItemEnchantmentEntry> sSpellItemEnchantmentStore(SpellItemEnchantmentfmt);
//DBCStorage <SpellItemEnchantmentConditionEntry> sSpellItemEnchantmentConditionStore(SpellItemEnchantmentConditionfmt);
//DBCStorage <SpellEntry> sSpellStore(SpellEntryfmt);
//PetFamilySpellsStore sPetFamilySpellsStore;

//DBCStorage <SpellCastTimesEntry> sSpellCastTimesStore(SpellCastTimefmt);
//DBCStorage <SpellCategoryEntry> sSpellCategoryStore(SpellCategoryfmt);
//DBCStorage <SpellDifficultyEntry> sSpellDifficultyStore(SpellDifficultyfmt);
//DBCStorage <SpellDurationEntry> sSpellDurationStore(SpellDurationfmt);
//DBCStorage <SpellFocusObjectEntry> sSpellFocusObjectStore(SpellFocusObjectfmt);
//DBCStorage <SpellRadiusEntry> sSpellRadiusStore(SpellRadiusfmt);
//DBCStorage <SpellRangeEntry> sSpellRangeStore(SpellRangefmt);
//DBCStorage <SpellRuneCostEntry> sSpellRuneCostStore(SpellRuneCostfmt);
//DBCStorage <SpellShapeshiftFormEntry> sSpellShapeshiftFormStore(SpellShapeshiftFormfmt);
//DBCStorage <SpellVisualEntry> sSpellVisualStore(SpellVisualfmt);
//DBCStorage <StableSlotPricesEntry> sStableSlotPricesStore(StableSlotPricesfmt);
//DBCStorage <SummonPropertiesEntry> sSummonPropertiesStore(SummonPropertiesfmt);
//DBCStorage <TalentEntry> sTalentStore(TalentEntryfmt);
//DBCStorage <TalentTabEntry> sTalentTabStore(TalentTabEntryfmt);

// store absolute bit position for first rank for talent inspect
//static uint32 sTalentTabPages[MAX_CLASSES][3];

DBCStorage <TaxiNodesEntry> sTaxiNodesStore(TaxiNodesEntryfmt);
TaxiMask sTaxiNodesMask;
TaxiMask sOldContinentsNodesMask;
TaxiMask sHordeTaxiNodesMask;
TaxiMask sAllianceTaxiNodesMask;
TaxiMask sDeathKnightTaxiNodesMask;

// DBC used only for initialization sTaxiPathSetBySource at startup.
TaxiPathSetBySource sTaxiPathSetBySource;
DBCStorage <TaxiPathEntry> sTaxiPathStore(TaxiPathEntryfmt);

// DBC used only for initialization sTaxiPathNodeStore at startup.
TaxiPathNodesByPath sTaxiPathNodesByPath;
static DBCStorage <TaxiPathNodeEntry> sTaxiPathNodeStore(TaxiPathNodeEntryfmt);

DBCStorage <TeamContributionPointsEntry> sTeamContributionPointsStore(TeamContributionPointsfmt);
DBCStorage <TotemCategoryEntry> sTotemCategoryStore(TotemCategoryEntryfmt);
DBCStorage <TransportAnimationEntry> sTransportAnimationStore(TransportAnimationfmt);
DBCStorage <TransportRotationEntry> sTransportRotationStore(TransportRotationfmt);
DBCStorage <VehicleEntry> sVehicleStore(VehicleEntryfmt);
DBCStorage <VehicleSeatEntry> sVehicleSeatStore(VehicleSeatEntryfmt);
DBCStorage <WMOAreaTableEntry> sWMOAreaTableStore(WMOAreaTableEntryfmt);
DBCStorage <WorldMapAreaEntry> sWorldMapAreaStore(WorldMapAreaEntryfmt);
DBCStorage <WorldMapOverlayEntry> sWorldMapOverlayStore(WorldMapOverlayEntryfmt);
DBCStorage <WorldSafeLocsEntry> sWorldSafeLocsStore(WorldSafeLocsEntryfmt);

typedef std::list<std::string> StoreProblemList;

uint32 DBCFileCount = 0;

static bool LoadDBC_assert_print(uint32 fsize, uint32 rsize, const std::string& filename)
{
    TC_LOG_ERROR("misc", "Size of '%s' set by format string (%u) not equal size of C++ structure (%u).", filename.c_str(), fsize, rsize);

    // ASSERT must fail after function call
    return false;
}

template<class T>
inline void LoadDBC(uint32& availableDbcLocales, StoreProblemList& errors, DBCStorage<T>& storage, std::string const& dbcPath, std::string const& filename,
                    char const* dbTable = nullptr, char const* dbFormat = nullptr, char const* dbIndexName = nullptr)
{
    // compatibility format and C++ structure sizes
    ASSERT(DBCFileLoader::GetFormatRecordSize(storage.GetFormat()) == sizeof(T) || LoadDBC_assert_print(DBCFileLoader::GetFormatRecordSize(storage.GetFormat()), sizeof(T), filename));

    ++DBCFileCount;
    std::string dbcFilename = dbcPath + filename;

    if (storage.Load(dbcFilename.c_str()))
    {
        for (uint8 i = 0; i < TOTAL_LOCALES; ++i)
        {
            if (!(availableDbcLocales & (1 << i)))
                continue;

            std::string localizedName(dbcPath);
            localizedName.append(localeNames[i]);
            localizedName.push_back('/');
            localizedName.append(filename);

            if (!storage.LoadStringsFrom(localizedName.c_str()))
                availableDbcLocales &= ~(1 << i);             // mark as not available for speedup next checks
        }

        if (dbTable)
            storage.LoadFromDB(dbTable, dbFormat, dbIndexName);
    }
    else
    {
        // sort problematic dbc to (1) non compatible and (2) non-existed
        if (FILE* f = fopen(dbcFilename.c_str(), "rb"))
        {
            std::ostringstream stream;
            stream << dbcFilename << " exists, and has " << storage.GetFieldCount() << " field(s) (expected " << strlen(storage.GetFormat()) << "). Extracted file might be from wrong client version or a database-update has been forgotten. Search on forum for TCE00008 for more info.";
            std::string buf = stream.str();
            errors.push_back(buf);
            fclose(f);
        }
        else
            errors.push_back(dbcFilename);
    }
}

void LoadDBCStores(const std::string& dataPath)
{
    uint32 oldMSTime = getMSTime();

    std::string dbcPath = dataPath + "dbc/";

    StoreProblemList bad_dbc_files;
    uint32 availableDbcLocales = 0xFFFFFFFF;

#define LOAD_DBC(store, file) LoadDBC(availableDbcLocales, bad_dbc_files, store, dbcPath, file)

    //LOAD_DBC(sAreaTableStore,                     "AreaTable.dbc");
    //LOAD_DBC(sAchievementCriteriaStore,           "Achievement_Criteria.dbc");
    //LOAD_DBC(sAreaTriggerStore,                   "AreaTrigger.dbc");
    //LOAD_DBC(sAreaGroupStore,                     "AreaGroup.dbc");
    //LOAD_DBC(sAreaPOIStore,                       "AreaPOI.dbc");
    //LOAD_DBC(sAuctionHouseStore,                  "AuctionHouse.dbc");
    //LOAD_DBC(sBankBagSlotPricesStore,             "BankBagSlotPrices.dbc");
    //LOAD_DBC(sBannedAddOnsStore,                  "BannedAddOns.dbc");
    //LOAD_DBC(sBattlemasterListStore,              "BattlemasterList.dbc");
    //LOAD_DBC(sBarberShopStyleStore,               "BarberShopStyle.dbc");
    //LOAD_DBC(sCharacterFacialHairStylesStore,     "CharacterFacialHairStyles.dbc");
    //LOAD_DBC(sCharSectionsStore,                  "CharSections.dbc");
    //LOAD_DBC(sCharStartOutfitStore,               "CharStartOutfit.dbc");
    //LOAD_DBC(sCharTitlesStore,                    "CharTitles.dbc");
    //LOAD_DBC(sChatChannelsStore,                  "ChatChannels.dbc");
    //LOAD_DBC(sChrClassesStore,                    "ChrClasses.dbc");
    //LOAD_DBC(sChrRacesStore,                      "ChrRaces.dbc");
    //LOAD_DBC(sCinematicCameraStore,               "CinematicCamera.dbc");
    //LOAD_DBC(sCinematicSequencesStore,            "CinematicSequences.dbc");
    //LOAD_DBC(sCreatureDisplayInfoStore,           "CreatureDisplayInfo.dbc");
    //LOAD_DBC(sCreatureDisplayInfoExtraStore,      "CreatureDisplayInfoExtra.dbc");
    //LOAD_DBC(sCreatureFamilyStore,                "CreatureFamily.dbc");
    //LOAD_DBC(sCreatureModelDataStore,             "CreatureModelData.dbc");
    //LOAD_DBC(sCreatureSpellDataStore,             "CreatureSpellData.dbc");
    //LOAD_DBC(sCreatureTypeStore,                  "CreatureType.dbc");
    //LOAD_DBC(sCurrencyTypesStore,                 "CurrencyTypes.dbc");
    //LOAD_DBC(sDestructibleModelDataStore,         "DestructibleModelData.dbc");
    //LOAD_DBC(sDungeonEncounterStore,              "DungeonEncounter.dbc");
    //LOAD_DBC(sDurabilityCostsStore,               "DurabilityCosts.dbc");
    //LOAD_DBC(sDurabilityQualityStore,             "DurabilityQuality.dbc");
    //LOAD_DBC(sEmotesStore,                        "Emotes.dbc");
    //LOAD_DBC(sEmotesTextStore,                    "EmotesText.dbc");
    //LOAD_DBC(sEmotesTextSoundStore,               "EmotesTextSound.dbc");
    //LOAD_DBC(sFactionStore,                       "Faction.dbc");
    //LOAD_DBC(sFactionTemplateStore,               "FactionTemplate.dbc");
    //LOAD_DBC(sGameObjectArtKitStore,              "GameObjectArtKit.dbc");
    //LOAD_DBC(sGameObjectDisplayInfoStore,         "GameObjectDisplayInfo.dbc");
    //LOAD_DBC(sGemPropertiesStore,                 "GemProperties.dbc");
    //LOAD_DBC(sGlyphPropertiesStore,               "GlyphProperties.dbc");
    //LOAD_DBC(sGlyphSlotStore,                     "GlyphSlot.dbc");
    //LOAD_DBC(sGtBarberShopCostBaseStore,          "gtBarberShopCostBase.dbc");
    //LOAD_DBC(sGtCombatRatingsStore,               "gtCombatRatings.dbc");
    //LOAD_DBC(sGtChanceToMeleeCritBaseStore,       "gtChanceToMeleeCritBase.dbc");
    //LOAD_DBC(sGtChanceToMeleeCritStore,           "gtChanceToMeleeCrit.dbc");
    //LOAD_DBC(sGtChanceToSpellCritBaseStore,       "gtChanceToSpellCritBase.dbc");
    //LOAD_DBC(sGtChanceToSpellCritStore,           "gtChanceToSpellCrit.dbc");
    //LOAD_DBC(sGtNPCManaCostScalerStore,           "gtNPCManaCostScaler.dbc");
    //LOAD_DBC(sGtOCTClassCombatRatingScalarStore,  "gtOCTClassCombatRatingScalar.dbc");
    //LOAD_DBC(sGtOCTRegenHPStore,                  "gtOCTRegenHP.dbc");
    //LOAD_DBC(sGtOCTRegenMPStore,                  "gtOCTRegenMP.dbc");       -- not used currently
    //LOAD_DBC(sGtRegenHPPerSptStore,               "gtRegenHPPerSpt.dbc");
    //LOAD_DBC(sGtRegenMPPerSptStore,               "gtRegenMPPerSpt.dbc");
    //LOAD_DBC(sHolidaysStore,                      "Holidays.dbc");
    //LOAD_DBC(sItemStore,                          "Item.dbc");
    //LOAD_DBC(sItemBagFamilyStore,                 "ItemBagFamily.dbc");
    //LOAD_DBC(sItemDisplayInfoStore,               "ItemDisplayInfo.dbc");
    //LOAD_DBC(sItemCondExtCostsStore,              "ItemCondExtCosts.dbc");
    //LOAD_DBC(sItemExtendedCostStore,              "ItemExtendedCost.dbc");
    //LOAD_DBC(sItemLimitCategoryStore,             "ItemLimitCategory.dbc");
    //LOAD_DBC(sItemRandomPropertiesStore,          "ItemRandomProperties.dbc");
    //LOAD_DBC(sItemRandomSuffixStore,              "ItemRandomSuffix.dbc");
    //LOAD_DBC(sItemSetStore,                       "ItemSet.dbc");
    //LOAD_DBC(sLFGDungeonStore,                    "LFGDungeons.dbc");
    //LOAD_DBC(sLightStore,                         "Light.dbc");
    //LOAD_DBC(sLiquidTypeStore,                    "LiquidType.dbc");
    //LOAD_DBC(sLockStore,                          "Lock.dbc");
    //LOAD_DBC(sMailTemplateStore,                  "MailTemplate.dbc");
    //LOAD_DBC(sMapStore,                           "Map.dbc");
    //LOAD_DBC(sMapDifficultyStore,                 "MapDifficulty.dbc");
    //LOAD_DBC(sMovieStore,                         "Movie.dbc");
    //LOAD_DBC(sNamesProfanityStore,                "NamesProfanity.dbc");
    //LOAD_DBC(sNamesReservedStore,                 "NamesReserved.dbc");
    //LOAD_DBC(sOverrideSpellDataStore,             "OverrideSpellData.dbc");
    //LOAD_DBC(sPowerDisplayStore,                  "PowerDisplay.dbc");
    //LOAD_DBC(sPvPDifficultyStore,                 "PvpDifficulty.dbc");
    //LOAD_DBC(sQuestXPStore,                       "QuestXP.dbc");
    //LOAD_DBC(sQuestFactionRewardStore,            "QuestFactionReward.dbc");
    //LOAD_DBC(sQuestSortStore,                     "QuestSort.dbc");
    //LOAD_DBC(sRandPropPointsStore,                "RandPropPoints.dbc");
    //LOAD_DBC(sScalingStatDistributionStore,       "ScalingStatDistribution.dbc");
    //LOAD_DBC(sScalingStatValuesStore,             "ScalingStatValues.dbc");
    //LOAD_DBC(sSkillLineStore,                     "SkillLine.dbc");
    //LOAD_DBC(sSkillLineAbilityStore,              "SkillLineAbility.dbc");
    //LOAD_DBC(sSkillRaceClassInfoStore,            "SkillRaceClassInfo.dbc");
    //LOAD_DBC(sSkillTiersStore,                    "SkillTiers.dbc");
    //LOAD_DBC(sSoundEntriesStore,                  "SoundEntries.dbc");
    //LOAD_DBC(sSpellCastTimesStore,                "SpellCastTimes.dbc");
    //LOAD_DBC(sSpellCategoryStore,                 "SpellCategory.dbc");
    //LOAD_DBC(sSpellDurationStore,                 "SpellDuration.dbc");
    //LOAD_DBC(sSpellFocusObjectStore,              "SpellFocusObject.dbc");
    //LOAD_DBC(sSpellItemEnchantmentStore,          "SpellItemEnchantment.dbc");
    //LOAD_DBC(sSpellItemEnchantmentConditionStore, "SpellItemEnchantmentCondition.dbc");
    //LOAD_DBC(sSpellRadiusStore,                   "SpellRadius.dbc");
    //LOAD_DBC(sSpellRangeStore,                    "SpellRange.dbc");
    //LOAD_DBC(sSpellRuneCostStore,                 "SpellRuneCost.dbc");
    //LOAD_DBC(sSpellShapeshiftFormStore,           "SpellShapeshiftForm.dbc");
    //LOAD_DBC(sSpellVisualStore,                   "SpellVisual.dbc");
    //LOAD_DBC(sStableSlotPricesStore,              "StableSlotPrices.dbc");
    //LOAD_DBC(sSummonPropertiesStore,              "SummonProperties.dbc");
    //LOAD_DBC(sTalentStore,                        "Talent.dbc");
    //LOAD_DBC(sTalentTabStore,                     "TalentTab.dbc");
    LOAD_DBC(sTaxiNodesStore,                     "TaxiNodes.dbc");
    LOAD_DBC(sTaxiPathStore,                      "TaxiPath.dbc");
    LOAD_DBC(sTaxiPathNodeStore,                  "TaxiPathNode.dbc");
    LOAD_DBC(sTeamContributionPointsStore,        "TeamContributionPoints.dbc");
    LOAD_DBC(sTotemCategoryStore,                 "TotemCategory.dbc");
    LOAD_DBC(sTransportAnimationStore,            "TransportAnimation.dbc");
    LOAD_DBC(sTransportRotationStore,             "TransportRotation.dbc");
    LOAD_DBC(sVehicleStore,                       "Vehicle.dbc");
    LOAD_DBC(sVehicleSeatStore,                   "VehicleSeat.dbc");
    LOAD_DBC(sWMOAreaTableStore,                  "WMOAreaTable.dbc");
    LOAD_DBC(sWorldMapAreaStore,                  "WorldMapArea.dbc");
    LOAD_DBC(sWorldMapOverlayStore,               "WorldMapOverlay.dbc");
    LOAD_DBC(sWorldSafeLocsStore,                 "WorldSafeLocs.dbc");

#undef LOAD_DBC

#define LOAD_DBC_EXT(store, file, dbtable, dbformat, dbpk) LoadDBC(availableDbcLocales, bad_dbc_files, store, dbcPath, file, dbtable, dbformat, dbpk)

    //LOAD_DBC_EXT(sAchievementStore,     "Achievement.dbc",      "achievement_dbc",      CustomAchievementfmt,     CustomAchievementIndex);
    //LOAD_DBC_EXT(sSpellStore,           "Spell.dbc",            "spell_dbc",            CustomSpellEntryfmt,      CustomSpellEntryIndex);
    //LOAD_DBC_EXT(sSpellDifficultyStore, "SpellDifficulty.dbc",  "spelldifficulty_dbc",  CustomSpellDifficultyfmt, CustomSpellDifficultyIndex);

#undef LOAD_DBC_EXT

    /*for (SpellEntry const* spellEntry : sSpellStore)
    {
        if (SpellDBC const* spellDBC = sDBCStoresMgr->GetSpellDBC(spellEntry->ID))
        {
            if (spellEntry->EffectSpellClassMask[0].operator!=(spellDBC->EffectSpellClassMask[0]))
                TC_LOG_ERROR("server", "SpellDBC : (ID : %u) has EffectSpellClassMask 0 = %u", spellEntry->ID, spellEntry->EffectSpellClassMask[0]);
            if (spellEntry->EffectSpellClassMask[1].operator!=(spellDBC->EffectSpellClassMask[1]))
                TC_LOG_ERROR("server", "SpellDBC : (ID : %u) has EffectSpellClassMask 1 = %u", spellEntry->ID, spellEntry->EffectSpellClassMask[1]);
            if (spellEntry->EffectSpellClassMask[2].operator!=(spellDBC->EffectSpellClassMask[2]))
                TC_LOG_ERROR("server", "SpellDBC : (ID : %u) has EffectSpellClassMask 2 = %u", spellEntry->ID, spellEntry->EffectSpellClassMask[2]);
        }
    }*/

    // fill data
    //for (MapDifficultyEntry const* entry : sMapDifficultyStore)
    //    sMapDifficultyMap[MAKE_PAIR32(entry->MapID, entry->Difficulty)] = MapDifficulty(entry->RaidDuration, entry->MaxPlayers, entry->Message[0] != '\0');

    //for (SkillRaceClassInfoEntry const* entry : sSkillRaceClassInfoStore)
    //    if (sDBCStoresMgr->GetSkillLineDBC(entry->SkillID))
    //        SkillRaceClassInfoBySkill.emplace(entry->SkillID, entry);

    


    // prepare fast data access to bit pos of talent ranks for use at inspecting
    /*{
        // now have all max ranks (and then bit amount used for store talent ranks in inspect)
        for (TalentTabDBC const* talentTabInfo : sTalentTabStore)
        {
            // prevent memory corruption; otherwise cls will become 12 below
            if ((talentTabInfo->ClassMask & CLASSMASK_ALL_PLAYABLE) == 0)
                continue;

            // store class talent tab pages
            for (uint32 cls = 1; cls < MAX_CLASSES; ++cls)
                if (talentTabInfo->ClassMask & (1 << (cls - 1)))
                    sTalentTabPages[cls][talentTabInfo->OrderIndex] = talentTabInfo->ID;
        }
    }*/

    for (TaxiPathEntry const* entry : sTaxiPathStore)
        sTaxiPathSetBySource[entry->FromTaxiNode][entry->ToTaxiNode] = TaxiPathBySourceAndDestination(entry->ID, entry->Cost);

    uint32 pathCount = sTaxiPathStore.GetNumRows();
    // Calculate path nodes count
    std::vector<uint32> pathLength;
    pathLength.resize(pathCount);                           // 0 and some other indexes not used
    for (TaxiPathNodeEntry const* entry : sTaxiPathNodeStore)
    {
        if (pathLength[entry->PathID] < entry->NodeIndex + 1)
            pathLength[entry->PathID] = entry->NodeIndex + 1;
    }

    // Set path length
    sTaxiPathNodesByPath.resize(pathCount);                 // 0 and some other indexes not used
    for (uint32 i = 1; i < sTaxiPathNodesByPath.size(); ++i)
        sTaxiPathNodesByPath[i].resize(pathLength[i]);
    // fill data
    for (TaxiPathNodeEntry const* entry : sTaxiPathNodeStore)
        sTaxiPathNodesByPath[entry->PathID][entry->NodeIndex] = entry;

    // Initialize global taxinodes mask
    // include existed nodes that have at least single not spell base (scripted) path
    {
        std::set<uint32> spellPaths;
        SpellDBCMap const& spellMap = sDBCStoresMgr->GetSpellDBCMap();
        for (const auto& sID : spellMap)
            if (SpellDBC const* sInfo = &sID.second)
                for (uint8 j = 0; j < MAX_SPELL_EFFECTS; ++j)
                    if (sInfo->Effect[j] == SPELL_EFFECT_SEND_TAXI)
                        spellPaths.insert(sInfo->EffectMiscValue[j]);

        sTaxiNodesMask.fill(0);
        sOldContinentsNodesMask.fill(0);
        sHordeTaxiNodesMask.fill(0);
        sAllianceTaxiNodesMask.fill(0);
        sDeathKnightTaxiNodesMask.fill(0);
        for (TaxiNodesEntry const* node : sTaxiNodesStore)
        {
            TaxiPathSetBySource::const_iterator src_i = sTaxiPathSetBySource.find(node->ID);
            if (src_i != sTaxiPathSetBySource.end() && !src_i->second.empty())
            {
                bool ok = false;
                for (TaxiPathSetForSource::const_iterator dest_i = src_i->second.begin(); dest_i != src_i->second.end(); ++dest_i)
                {
                    // not spell path
                    if (dest_i->second.price || spellPaths.find(dest_i->second.ID) == spellPaths.end())
                    {
                        ok = true;
                        break;
                    }
                }

                if (!ok)
                    continue;
            }

            // valid taxi network node
            uint8  field   = (uint8)((node->ID - 1) / 32);
            uint32 submask = 1  <<  ((node->ID - 1) % 32);
            sTaxiNodesMask[field] |= submask;

            if (node->MountCreatureID[0] && node->MountCreatureID[0] != 32981)
                sHordeTaxiNodesMask[field] |= submask;
            if (node->MountCreatureID[1] && node->MountCreatureID[1] != 32981)
                sAllianceTaxiNodesMask[field] |= submask;
            if (node->MountCreatureID[0] == 32981 || node->MountCreatureID[1] == 32981)
                sDeathKnightTaxiNodesMask[field] |= submask;

            // old continent node (+ nodes virtually at old continents, check explicitly to avoid loading map files for zone info)
            if (node->ContinentID < 2 || node->ID == 82 || node->ID == 83 || node->ID == 93 || node->ID == 94)
                sOldContinentsNodesMask[field] |= submask;

            // fix DK node at Ebon Hold and Shadow Vault flight master
            if (node->ID == 315 || node->ID == 333)
                const_cast<TaxiNodesEntry*>(node)->MountCreatureID[1] = 32981;
        }
    }

    for (WMOAreaTableEntry const* entry : sWMOAreaTableStore)
        sWMOAreaInfoByTripple[WMOAreaTableKey(entry->WMOID, entry->NameSetID, entry->WMOGroupID)] = entry;

    // error checks
    if (bad_dbc_files.size() >= DBCFileCount)
    {
        TC_LOG_ERROR("misc", "Incorrect DataDir value in worldserver.conf or ALL required *.dbc files (%d) not found by path: %sdbc", DBCFileCount, dataPath.c_str());
        exit(1);
    }
    else if (!bad_dbc_files.empty())
    {
        std::string str;
        for (StoreProblemList::iterator i = bad_dbc_files.begin(); i != bad_dbc_files.end(); ++i)
            str += *i + "\n";

        TC_LOG_ERROR("misc", "Some required *.dbc files (%u from %d) not found or not compatible:\n%s", (uint32)bad_dbc_files.size(), DBCFileCount, str.c_str());
        exit(1);
    }

    // Check loaded DBC files proper version
    /*if (!sAreaTableStore.LookupEntry(4987)         ||       // last area added in 3.3.5a
        !sCharTitlesStore.LookupEntry(177)         ||       // last char title added in 3.3.5a
        !sGemPropertiesStore.LookupEntry(1629)     ||       // last gem property added in 3.3.5a
        !sItemStore.LookupEntry(56806)             ||       // last client known item added in 3.3.5a
        !sItemExtendedCostStore.LookupEntry(2997)  ||       // last item extended cost added in 3.3.5a
        !sMapStore.LookupEntry(724)                ||       // last map added in 3.3.5a
        !sSpellStore.LookupEntry(80864)            )        // last added spell in 3.3.5a
    {
        TC_LOG_ERROR("misc", "You have _outdated_ DBC files. Please extract correct versions from current using client.");
        exit(1);
    }*/

    TC_LOG_INFO("server.loading", ">> Initialized %d data stores in %u ms", DBCFileCount, GetMSTimeDiffToNow(oldMSTime));

}

WMOAreaTableEntry const* GetWMOAreaTableEntryByTripple(int32 rootid, int32 adtid, int32 groupid)
{
    auto i = sWMOAreaInfoByTripple.find(WMOAreaTableKey(int16(rootid), int8(adtid), groupid));
    if (i != sWMOAreaInfoByTripple.end())
        return i->second;

    return nullptr;
}

uint32 GetVirtualMapForMapAndZone(uint32 mapid, uint32 zoneId)
{
    if (mapid != 530 && mapid != 571)                        // speed for most cases
        return mapid;

    if (WorldMapAreaEntry const* wma = sWorldMapAreaStore.LookupEntry(zoneId))
        return wma->DisplayMapID >= 0 ? wma->DisplayMapID : wma->MapID;

    return mapid;
}

ContentLevels GetContentLevelsForMapAndZone(uint32 mapid, uint32 zoneId)
{
    mapid = GetVirtualMapForMapAndZone(mapid, zoneId);
    if (mapid < 2)
        return CONTENT_1_60;

    MapDBC const* mapEntry = sDBCStoresMgr->GetMapDBC(mapid);
    if (!mapEntry)
        return CONTENT_1_60;

    switch (mapEntry->Expansion())
    {
        default: return CONTENT_1_60;
        case 1:  return CONTENT_61_70;
        case 2:  return CONTENT_71_80;
    }
}

bool IsTotemCategoryCompatiableWith(uint32 itemTotemCategoryId, uint32 requiredTotemCategoryId)
{
    if (requiredTotemCategoryId == 0)
        return true;
    if (itemTotemCategoryId == 0)
        return false;

    TotemCategoryEntry const* itemEntry = sTotemCategoryStore.LookupEntry(itemTotemCategoryId);
    if (!itemEntry)
        return false;
    TotemCategoryEntry const* reqEntry = sTotemCategoryStore.LookupEntry(requiredTotemCategoryId);
    if (!reqEntry)
        return false;

    if (itemEntry->TotemCategoryType != reqEntry->TotemCategoryType)
        return false;

    return (itemEntry->TotemCategoryMask & reqEntry->TotemCategoryMask) == reqEntry->TotemCategoryMask;
}

void Zone2MapCoordinates(float& x, float& y, uint32 zone)
{
    WorldMapAreaEntry const* maEntry = sWorldMapAreaStore.LookupEntry(zone);

    // if not listed then map coordinates (instance)
    if (!maEntry)
        return;

    std::swap(x, y);                                         // at client map coords swapped
    x = x*((maEntry->LocBottom-maEntry->LocTop)/100)+maEntry->LocTop;
    y = y*((maEntry->LocRight-maEntry->LocLeft)/100)+maEntry->LocLeft;      // client y coord from top to down
}

void Map2ZoneCoordinates(float& x, float& y, uint32 zone)
{
    WorldMapAreaEntry const* maEntry = sWorldMapAreaStore.LookupEntry(zone);

    // if not listed then map coordinates (instance)
    if (!maEntry)
        return;

    x = (x-maEntry->LocTop)/((maEntry->LocBottom-maEntry->LocTop)/100);
    y = (y-maEntry->LocLeft)/((maEntry->LocRight-maEntry->LocLeft)/100);    // client y coord from top to down
    std::swap(x, y);                                         // client have map coords swapped
}
