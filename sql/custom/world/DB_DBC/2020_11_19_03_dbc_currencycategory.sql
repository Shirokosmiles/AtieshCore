-- ----------------------------
-- Table structure for dbc_currencycategory
-- ----------------------------
DROP TABLE IF EXISTS `dbc_currencycategory`;
CREATE TABLE `dbc_currencycategory`  (
  `ID` int(11) NOT NULL DEFAULT 0,
  `Flags` int(11) NOT NULL DEFAULT 0,
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
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of dbc_currencycategory
-- ----------------------------
INSERT INTO `dbc_currencycategory` VALUES
(1, 0, 'Miscellaneous', '', '', 'Divers', 'Verschiedenes', '', '其它', '', '', 'Miscelánea', '', 'Разное', '', '', '', '', 16712190),
(2, 0, 'Player vs. Player', '', '', 'JcJ', 'Spieler gegen Spieler', '', 'PvP', '', '', 'Jugador contra Jugador', '', 'PvP', '', '', '', '', 16712190),
(4, 0, 'Classic', '', '', 'Classique', 'Classic', '', '经典旧世', '', '', 'Clásico', '', 'World of Warcraft', '', '', '', '', 16712190),
(21, 0, 'Wrath of the Lich King', '', '', 'Wrath of the Lich King', 'Wrath of the Lich King', '', '巫妖王之怒', '', '', 'Wrath of the Lich King', '', 'Wrath of the Lich King', '', '', '', '', 16712190),
(22, 0, 'Dungeon and Raid', '', '', 'Raid', 'Dungeon und Schlachtzug', '', '地下城与团队', '', '', 'Mazmorra y banda', '', 'Подземелья и рейды', '', '', '', '', 16712190),
(23, 0, 'Burning Crusade', '', '', 'Burning Crusade', 'Burning Crusade', '', '燃烧的远征', '', '', 'Burning Crusade', '', 'Burning Crusade', '', '', '', '', 16712190),
(41, 0, 'Test', '', '', 'Test', 'Test', '', '测试', '', '', 'Prueba', '', 'Test', '', '', '', '', 16712190),
(3, 3, 'Unused', '', '', 'Inutilisées', 'Unbenutzt', '', '未使用', '', '', 'No las uso', '', 'Неактивно', '', '', '', '', 16712190);
