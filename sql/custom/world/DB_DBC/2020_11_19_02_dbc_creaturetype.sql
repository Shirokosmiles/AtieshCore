-- ----------------------------
-- Table structure for dbc_creaturetype
-- ----------------------------
DROP TABLE IF EXISTS `dbc_creaturetype`;
CREATE TABLE `dbc_creaturetype`  (
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
  `Flags` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of dbc_creaturetype
-- ----------------------------
INSERT INTO `dbc_creaturetype` VALUES
(1, 'Beast', '', '', 'Bête', 'Wildtier', '', '野兽', '', '', 'Bestia', '', 'Животное', '', '', '', '', 16712190, 0),
(2, 'Dragonkin', '', '', 'Draconien', 'Drachkin', '', '龙类', '', '', 'Dragonante', '', 'Дракон', '', '', '', '', 16712190, 0),
(3, 'Demon', '', '', 'Démon', 'Dämon', '', '恶魔', '', '', 'Demonio', '', 'Демон', '', '', '', '', 16712190, 0),
(4, 'Elemental', '', '', 'Elémentaire', 'Elementar', '', '元素生物', '', '', 'Elemental', '', 'Элементаль', '', '', '', '', 16712190, 0),
(5, 'Giant', '', '', 'Géant', 'Riese', '', '巨人', '', '', 'Gigante', '', 'Великан', '', '', '', '', 16712190, 0),
(6, 'Undead', '', '', 'Mort-vivant', 'Untoter', '', '亡灵', '', '', 'No-muerto', '', 'Нежить', '', '', '', '', 16712190, 0),
(7, 'Humanoid', '', '', 'Humanoïde', 'Humanoid', '', '人型生物', '', '', 'Humanoide', '', 'Гуманоид', '', '', '', '', 16712190, 0),
(8, 'Critter', '', '', 'Bestiole', 'Tier', '', '小动物', '', '', 'Alimaña', '', 'Существо', '', '', '', '', 16712190, 1),
(9, 'Mechanical', '', '', 'Machine', 'Mechanisch', '', '机械', '', '', 'Mecánico', '', 'Механизм', '', '', '', '', 16712190, 0),
(10, 'Not specified', '', '', 'Non spécifié', 'Nicht spezifiziert', '', '未指定', '', '', 'Sin especificar', '', 'Не указано', '', '', '', '', 16712190, 0),
(11, 'Totem', '', '', 'Totem', 'Totem', '', '图腾', '', '', 'Tótem', '', 'Тотем', '', '', '', '', 16712190, 0),
(12, 'Non-combat Pet', '', '', 'Familier pacifique', 'Haustier', '', '非战斗宠物', '', '', 'Mascota mansa', '', 'Спутник', '', '', '', '', 16712190, 1),
(13, 'Gas Cloud', '', '', 'Nuage de gaz', 'Gaswolke', '', '气体云雾', '', '', 'Nube de gas', '', 'Облако газа', '', '', '', '', 16712190, 1);
