-- FULL `item_template` of entry 973
DELETE FROM `item_template` WHERE (entry = 973);
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `StatsCount`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `ScalingStatDistribution`, `ScalingStatValue`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `delay`, `ammo_type`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `block`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `RequiredDisenchantSkill`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `ScriptName`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `flagsCustom`, `VerifiedBuild`) VALUES
(973, 15, 0, -1, 'Уникальный помощник', 1103, 5, 0, 0, 1, 0, 0, 0, -1, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2000, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14208, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 'Нажми на меня!', 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 'custom_item', 0, 0, 0, 0, 0, 12340);

-- FULL `item_loot_template` of Entry 54218
DELETE FROM `item_loot_template` WHERE (Entry = 54218);
INSERT INTO `item_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
(54218, 36862, 0, 7, 0, 1, 1, 1, 1, 'кость'),
(54218, 44115, 0, 2, 0, 1, 1, 1, 2, 'Оло'),
(54218, 41163, 0, 1, 0, 1, 1, 2, 2, 'Титановый'),
(54218, 41599, 0, 8, 0, 1, 1, 1, 1, 'Сумка'),
(54218, 13926, 0, 12, 0, 1, 1, 1, 3, 'жемчужина'),
(54218, 45624, 0, 5, 0, 1, 1, 2, 5, 'Триумф'),
(54218, 45992, 0, 1, 0, 1, 1, 1, 1, 'удочка'),
(54218, 46783, 0, 22, 0, 1, 1, 5, 12, 'жвачка'),
(54218, 33223, 0, 0.3, 0, 1, 1, 1, 1, 'стул'),
(54218, 43102, 0, 0.3, 0, 1, 1, 1, 1, 'шар'),
(54218, 40087, 0, 12, 0, 1, 1, 1, 1, 'зелье'),
(54218, 40093, 0, 12, 0, 1, 1, 5, 10, 'несокрушимость'),
(54218, 40081, 0, 12, 0, 1, 1, 5, 10, 'фласка ночных кошмаров'),
(54218, 33448, 0, 12, 0, 1, 1, 2, 5, 'мана'),
(54218, 49908, 0, 1, 0, 1, 1, 1, 1, 'саронит'),
(54218, 33816, 0, 4, 0, 1, 1, 1, 1, 'Крокодил'),
(54218, 13379, 0, 4, 0, 1, 1, 1, 1, 'Флейта'),
(54218, 49426, 0, 3, 0, 1, 1, 2, 5, 'Эмблема льда'),
(54218, 10822, 0, 4, 0, 1, 1, 1, 1, 'Темный дракончик'),
(54218, 11474, 0, 4, 0, 1, 1, 1, 1, 'Хамелион'),
(54218, 45912, 0, 4, 0, 1, 1, 1, 1, 'Книга познания символов'),
(54218, 29960, 0, 4, 0, 1, 1, 1, 1, 'Светляк'),
(54218, 47241, 0, 4, 0, 1, 1, 2, 5, 'Эмблема Триумфа'),
(54218, 38233, 0, 4, 0, 1, 1, 1, 5, 'Путь иллидана'),
(54218, 23720, 0, 0.5, 0, 1, 2, 1, 1, 'Landro\'s Gift Box, Riding Turtle'),
(54218, 35223, 0, 36.36, 0, 1, 1, 1, 1, 'Landro\'s Gift Box, Papa Hummel\'s Old-Fashioned Pet Biscuit'),
(54218, 45047, 0, 27.28, 0, 1, 1, 1, 1, 'Landro\'s Gift Box, Sandbox Tiger'),
(54218, 46779, 0, 36.36, 0, 1, 1, 1, 1, 'Landro\'s Gift Box, Path of Cenarius'),
(54218, 49282, 0, 0.2, 0, 1, 2, 1, 1, 'Landro\'s Gift Box, Big Battle Bear'),
(54218, 49283, 0, 0.3, 0, 1, 2, 1, 1, 'Landro\'s Gift Box, Reins of the Spectral Tiger'),
(54218, 49284, 0, 0.3, 0, 1, 2, 1, 1, 'Landro\'s Gift Box, Reins of the Swift Spectral Tiger'),
(54218, 49285, 0, 0.1, 0, 1, 2, 1, 1, 'Landro\'s Gift Box, X-51 Nether-Rocket'),
(54218, 49286, 0, 0.3, 0, 1, 2, 1, 1, 'Landro\'s Gift Box, X-51 Nether-Rocket X-TREME');