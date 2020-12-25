-- ----------------------------
-- Table structure for dbc_talenttab
-- ----------------------------
DROP TABLE IF EXISTS `dbc_talenttab`;
CREATE TABLE `dbc_talenttab`  (
  `ID` int(11) NOT NULL DEFAULT 0,
  `Name_Lang_enUS` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_enGB` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_koKR` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_frFR` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_deDE` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_enCN` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_zhCN` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_enTW` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_zhTW` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_esES` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_esMX` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_ruRU` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_ptPT` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_ptBR` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_itIT` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_Unk` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Name_Lang_Mask` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `SpellIconID` int(11) NOT NULL DEFAULT 0,
  `RaceMask` int(11) NOT NULL DEFAULT 0,
  `ClassMask` int(11) NOT NULL DEFAULT 0,
  `PetTalentMask` int(11) NOT NULL DEFAULT 0,
  `OrderIndex` int(11) NOT NULL DEFAULT 0,
  `BackgroundFile` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of dbc_talenttab
-- ----------------------------
INSERT INTO `dbc_talenttab` VALUES
(81, 'Arcane', '', '', 'Arcanes', 'Arkan', '', '奥术', '', '', 'Arcano', '', 'Тайная магия', '', '', '', '', 16712190, 125, 2047, 128, 0, 0, 'MageArcane'),
(161, 'Arms', '', '', 'Armes', 'Waffen', '', '武器', '', '', 'Armas', '', 'Оружие', '', '', '', '', 16712190, 514, 2047, 1, 0, 0, 'WarriorArms'),
(182, 'Assassination', '', '', 'Assassinat', 'Meucheln', '', '刺杀', '', '', 'Asesinato', '', 'Ликвидация', '', '', '', '', 16712190, 514, 2047, 8, 0, 0, 'RogueAssassination'),
(201, 'Discipline', '', '', 'Discipline', 'Disziplin', '', '戒律', '', '', 'Disciplina', '', 'Послушание', '', '', '', '', 16712190, 685, 2047, 16, 0, 0, 'PriestDiscipline'),
(261, 'Elemental', '', '', 'Elémentaire', 'Elementar', '', '元素', '', '', 'Elemental', '', 'Стихии', '', '', '', '', 16712190, 62, 2047, 64, 0, 0, 'ShamanElementalCombat'),
(283, 'Balance', '', '', 'Equilibre', 'Gleichgewicht', '', '平衡', '', '', 'Equilibrio', '', 'Баланс', '', '', '', '', 16712190, 225, 2047, 1024, 0, 0, 'DruidBalance'),
(302, 'Affliction', '', '', 'Affliction', 'Gebrechen', '', '痛苦', '', '', 'Aflicción', '', 'Колдовство', '', '', '', '', 16712190, 88, 2047, 256, 0, 0, 'WarlockCurses'),
(361, 'Beast Mastery', '', '', 'Maîtrise des bêtes', 'Tierherrschaft', '', '野兽控制', '', '', 'Bestias', '', 'Повелитель зверей', '', '', '', '', 16712190, 255, 2047, 4, 0, 0, 'HunterBeastMastery'),
(382, 'Holy', '', '', 'Sacré', 'Heilig', '', '神圣', '', '', 'Sagrado', '', 'Свет', '', '', '', '', 16712190, 70, 2047, 2, 0, 0, 'PaladinHoly'),
(398, 'Blood', '', '', 'Sang', 'Blut', '', '鲜血', '', '', 'Sangre', '', 'Кровь', '', '', '', '', 16712190, 2636, -260097, 32, 0, 0, 'DeathKnightBlood'),
(409, 'Tenacity', '', '', 'Ténacité', 'Hartnäckigkeit', '', '坚韧', '', '', 'Tenacidad', '', 'Упорство', '', '', '', '', 16712190, 1559, 0, 0, 2, 0, 'HunterPetTenacity'),
(410, 'Ferocity', '', '', 'Férocité', 'Wildheit', '', '狂野', '', '', 'Ferocidad', '', 'Свирепость', '', '', '', '', 16712190, 496, 0, 0, 1, 0, 'HunterPetFerocity'),
(411, 'Cunning', '', '', 'Ruse', 'Gerissenheit', '', '狡诈', '', '', 'Astucia', '', 'Хитрость', '', '', '', '', 16712190, 2223, 0, 0, 4, 0, 'HunterPetCunning'),
(41, 'Fire', '', '', 'Feu', 'Feuer', '', '火焰', '', '', 'Fuego', '', 'Огонь', '', '', '', '', 16712190, 183, 2047, 128, 0, 1, 'MageFire'),
(164, 'Fury', '', '', 'Fureur', 'Furor', '', '狂怒', '', '', 'Furia', '', 'Неистовство', '', '', '', '', 16712190, 561, 2047, 1, 0, 1, 'WarriorFury'),
(181, 'Combat', '', '', 'Combat', 'Kampf', '', '战斗', '', '', 'Combate', '', 'Бой', '', '', '', '', 16712190, 243, 2047, 8, 0, 1, 'RogueCombat'),
(202, 'Holy', '', '', 'Sacré', 'Heilig', '', '神圣', '', '', 'Sagrado', '', 'Свет', '', '', '', '', 16712190, 2873, 2047, 16, 0, 1, 'PriestHoly'),
(263, 'Enhancement', '', '', 'Amélioration', 'Verstärk.', '', '增强', '', '', 'Mejora', '', 'Совершенствование', '', '', '', '', 16712190, 19, 2047, 64, 0, 1, 'ShamanEnhancement'),
(281, 'Feral Combat', '', '', 'Combat farouche', 'Wilder Kampf', '', '野性战斗', '', '', 'Combate feral', '', 'Сила зверя', '', '', '', '', 16712190, 107, 2047, 1024, 0, 1, 'DruidFeralCombat'),
(303, 'Demonology', '', '', 'Démonologie', 'Dämonologie', '', '恶魔学识', '', '', 'Demonología', '', 'Демонология', '', '', '', '', 16712190, 90, 2047, 256, 0, 1, 'WarlockSummoning'),
(363, 'Marksmanship', '', '', 'Précision', 'Treffsicherheit', '', '射击', '', '', 'Puntería', '', 'Стрельба', '', '', '', '', 16712190, 126, 2047, 4, 0, 1, 'HunterMarksmanship'),
(383, 'Protection', '', '', 'Protection', 'Schutz', '', '防护', '', '', 'Protección', '', 'Защита', '', '', '', '', 16712190, 291, 2047, 2, 0, 1, 'PaladinProtection'),
(399, 'Frost', '', '', 'Givre', 'Frost', '', '冰霜', '', '', 'Escarcha', '', 'Лед', '', '', '', '', 16712190, 2632, 2047, 32, 0, 1, 'DeathKnightFrost'),
(61, 'Frost', '', '', 'Givre', 'Frost', '', '冰霜', '', '', 'Escarcha', '', 'Лед', '', '', '', '', 16712190, 188, 2047, 128, 0, 2, 'MageFrost'),
(163, 'Protection', '', '', 'Protection', 'Schutz', '', '防护', '', '', 'Protección', '', 'Защита', '', '', '', '', 16712190, 1463, 2047, 1, 0, 2, 'WarriorProtection'),
(183, 'Subtlety', '', '', 'Finesse', 'Täuschung', '', '敏锐', '', '', 'Sutileza', '', 'Скрытность', '', '', '', '', 16712190, 250, 2047, 8, 0, 2, 'RogueSubtlety'),
(203, 'Shadow', '', '', 'Ombre', 'Schatten', '', '暗影', '', '', 'Sombra', '', 'Тьма', '', '', '', '', 16712190, 234, 2047, 16, 0, 2, 'PriestShadow'),
(262, 'Restoration', '', '', 'Restauration', 'Wiederherst.', '', '恢复', '', '', 'Restauración', '', 'Исцеление', '', '', '', '', 16712190, 13, 2047, 64, 0, 2, 'ShamanRestoration'),
(282, 'Restoration', '', '', 'Restauration', 'Wiederherst.', '', '恢复', '', '', 'Restauración', '', 'Исцеление', '', '', '', '', 16712190, 962, 2047, 1024, 0, 2, 'DruidRestoration'),
(301, 'Destruction', '', '', 'Destruction', 'Zerstörung', '', '毁灭', '', '', 'Destrucción', '', 'Разрушение', '', '', '', '', 16712190, 547, 2047, 256, 0, 2, 'WarlockDestruction'),
(362, 'Survival', '', '', 'Survie', 'Überleben', '', '生存', '', '', 'Supervivencia', '', 'Выживание', '', '', '', '', 16712190, 257, 2047, 4, 0, 2, 'HunterSurvival'),
(381, 'Retribution', '', '', 'Vindicte', 'Vergeltung', '', '惩戒', '', '', 'Reprensión', '', 'Воздаяние', '', '', '', '', 16712190, 555, 2047, 2, 0, 2, 'PaladinCombat'),
(400, 'Unholy', '', '', 'Impie', 'Unheilig', '', '邪恶', '', '', 'Profano', '', 'Нечестивость', '', '', '', '', 16712190, 2633, 2047, 32, 0, 2, 'DeathKnightUnholy');
