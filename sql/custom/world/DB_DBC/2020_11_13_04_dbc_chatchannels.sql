-- ----------------------------
-- Table structure for dbc_chatchannels
-- ----------------------------
DROP TABLE IF EXISTS `dbc_chatchannels`;
CREATE TABLE `dbc_chatchannels`  (
  `guid` int(11) NOT NULL AUTO_INCREMENT,
  `ID` int(11) NOT NULL DEFAULT 0,
  `Flags` int(11) NOT NULL DEFAULT 0,
  `FactionGroup` int(11) NOT NULL DEFAULT 0,
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
  `Shortcut_Lang_enUS` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_enGB` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_koKR` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_frFR` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_deDE` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_enCN` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_zhCN` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_enTW` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_zhTW` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_esES` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_esMX` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_ruRU` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_ptPT` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_ptBR` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_itIT` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_Unk` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Shortcut_Lang_Mask` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`guid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 7 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of dbc_chatchannels
-- ----------------------------
INSERT INTO `dbc_chatchannels` VALUES
(1, 1, 524291, 0, 'General - %s', '', '', 'Général - %s', 'Allgemein - %s', '', '综合 - %s', '', '', 'General: %s', '', 'Общий: %s', '', '', '', '', 16712190, 'General', '', '', 'Général', 'Allgemein', '', '综合', '', '', 'General', '', 'Общий', '', '', '', '', 16712190),
(2, 2, 59, 0, 'Trade - %s', '', '', 'Commerce - %s', 'Handel - %s', '', '交易 - %s', '', '', 'Comercio: %s', '', 'Торговля: %s', '', '', '', '', 16712190, 'Trade', '', '', 'Commerce', 'Handel', '', '交易', '', '', 'Comercio', '', 'Торговля', '', '', '', '', 16712190),
(3, 22, 65539, 0, 'LocalDefense - %s', '', '', 'DéfenseLocale - %s', 'LokaleVerteidigung - %s', '', '本地防务 - %s', '', '', 'Defensa local: %s', '', 'Оборона: %s', '', '', '', '', 16712190, 'LocalDefense', '', '', 'DéfenseLocale', 'LokaleVerteidigung', '', '本地防务', '', '', 'DefensaLocal', '', 'ОборонаЛокальный', '', '', '', '', 16712190),
(4, 23, 65540, 0, 'WorldDefense', '', '', 'DéfenseUniverselle', 'WeltVerteidigung', '', '世界防务', '', '', 'Defensa general', '', 'Оборона: глобальный', '', '', '', '', 16712190, 'WorldDefense', '', '', 'DéfenseUniverselle', 'WeltVerteidigung', '', '世界防务', '', '', 'DefensaGeneral', '', 'ОборонаГлобальный', '', '', '', '', 16712190),
(5, 25, 131122, 0, 'GuildRecruitment - %s', '', '', 'RecrutementDeGuilde - %s', 'Gildenrekrutierung - %s', '', '公会招募 - %s', '', '', 'BuscaHermandad: %s', '', 'Гильдии: %s', '', '', '', '', 16712190, 'GuildRecruitment', '', '', 'RecrutementDeGuilde', 'Gildenrekrutierung', '', '公会招募', '', '', 'BuscaHermandad', '', 'Гильдии', '', '', '', '', 16712190),
(6, 26, 262201, 0, 'LookingForGroup', '', '', 'RechercheDeGroupe', 'SucheNachGruppe', '', '寻求组队', '', '', 'BuscarGrupo', '', 'Поиск спутников', '', '', '', '', 16712190, 'LookingForGroup', '', '', 'RechercheDeGroupe', 'SucheNachGruppe', '', '寻求组队', '', '', 'BuscarGrupo', '', 'ПоискСпутников', '', '', '', '', 16712190);
