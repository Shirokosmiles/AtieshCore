-- ----------------------------
-- Table structure for dbc_battlemasterlist
-- ----------------------------
DROP TABLE IF EXISTS `dbc_battlemasterlist`;
CREATE TABLE `dbc_battlemasterlist`  (
  `ID` int(11) NOT NULL DEFAULT 0,
  `MapID_1` int(11) NOT NULL DEFAULT 0,
  `MapID_2` int(11) NOT NULL DEFAULT 0,
  `MapID_3` int(11) NOT NULL DEFAULT 0,
  `MapID_4` int(11) NOT NULL DEFAULT 0,
  `MapID_5` int(11) NOT NULL DEFAULT 0,
  `MapID_6` int(11) NOT NULL DEFAULT 0,
  `MapID_7` int(11) NOT NULL DEFAULT 0,
  `MapID_8` int(11) NOT NULL DEFAULT 0,
  `InstanceType` int(11) NOT NULL DEFAULT 0,
  `GroupsAllowed` int(11) NOT NULL DEFAULT 0,
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
  `MaxGroupSize` int(11) NOT NULL DEFAULT 0,
  `HolidayWorldState` int(11) NOT NULL DEFAULT 0,
  `Minlevel` int(11) NOT NULL DEFAULT 0,
  `Maxlevel` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of dbc_battlemasterlist
-- ----------------------------
INSERT INTO `dbc_battlemasterlist` VALUES
(1, 30, -1, -1, -1, -1, -1, -1, -1, 3, 1, 'Alterac Valley', '', '', 'Vallée d\\\'Alterac', 'Alteractal', '', '奥特兰克山谷', '', '', 'Valle de Alterac', '', 'Альтеракская долина', '', '', '', '', 16712190, 5, 1941, 51, 80),
(2, 489, -1, -1, -1, -1, -1, -1, -1, 3, 1, 'Warsong Gulch', '', '', 'Goulet des Chanteguerres', 'Kriegshymnenschlucht', '', '战歌峡谷', '', '', 'Garganta Grito de Guerra', '', 'Ущелье Песни Войны', '', '', '', '', 16712190, 10, 1942, 10, 80),
(3, 529, -1, -1, -1, -1, -1, -1, -1, 3, 1, 'Arathi Basin', '', '', 'Bassin d\\\'Arathi', 'Arathibecken', '', '阿拉希盆地', '', '', 'Cuenca de Arathi', '', 'Низина Арати', '', '', '', '', 16712190, 15, 1943, 20, 80),
(4, 559, -1, -1, -1, -1, -1, -1, -1, 4, 1, 'Nagrand Arena', '', '', 'Arène de Nagrand', 'Arena von Nagrand', '', '纳格兰竞技场', '', '', 'Arena de Nagrand', '', 'Арена Награнда', '', '', '', '', 16712190, 5, 0, 10, 80),
(5, 562, -1, -1, -1, -1, -1, -1, -1, 4, 1, 'Blade\\\'s Edge Arena', '', '', 'Arène des Tranchantes', 'Arena des Schergrats', '', '刀锋竞技场', '', '', 'Arena Filospada', '', 'Арена Острогорья', '', '', '', '', 16712190, 5, 0, 10, 80),
(6, 559, 562, 572, 617, 618, -1, -1, -1, 4, 1, 'All Arenas', '', '', 'Toutes les arènes', 'Alle Arenen', '', '所有竞技场', '', '', 'Todas las arenas', '', 'Все арены', '', '', '', '', 16712190, 5, 0, 10, 80),
(7, 566, -1, -1, -1, -1, -1, -1, -1, 3, 1, 'Eye of the Storm', '', '', 'L\\\'Œil du cyclone', 'Auge des Sturms', '', '风暴之眼', '', '', 'Ojo de la Tormenta', '', 'Око Бури', '', '', '', '', 16712190, 15, 2851, 61, 80),
(8, 572, -1, -1, -1, -1, -1, -1, -1, 4, 1, 'Ruins of Lordaeron', '', '', 'Ruines de Lordaeron', 'Ruinen von Lordaeron', '', '洛丹伦废墟', '', '', 'Ruinas de Lordaeron', '', 'Руины Лордерона', '', '', '', '', 16712190, 5, 0, 10, 80),
(9, 607, -1, -1, -1, -1, -1, -1, -1, 3, 1, 'Strand of the Ancients', '', '', 'Rivage des Anciens', 'Strand der Uralten', '', '远古海滩', '', '', 'Playa de los Ancestros', '', 'Берег Древних', '', '', '', '', 16712190, 15, 3695, 71, 80),
(10, 617, -1, -1, -1, -1, -1, -1, -1, 4, 1, 'Dalaran Sewers', '', '', 'Egouts de Dalaran', 'Abwasserkanäle von Dalaran', '', '达拉然下水道', '', '', 'Cloacas de Dalaran', '', 'Стоки Даларана', '', '', '', '', 16712190, 5, 0, 10, 80),
(11, 618, -1, -1, -1, -1, -1, -1, -1, 4, 1, 'The Ring of Valor', '', '', 'L\\\'arène des valeureux', 'Der Ring der Ehre', '', '勇气竞技场', '', '', 'El Círculo del Valor', '', 'Арена Доблести', '', '', '', '', 16712190, 5, 0, 10, 80),
(30, 628, -1, -1, -1, -1, -1, -1, -1, 3, 1, 'Isle of Conquest', '', '', 'Île des Conquérants', 'Insel der Eroberung', '', '征服之岛', '', '', 'Isla de la Conquista', '', 'Остров Завоеваний', '', '', '', '', 16712190, 5, 4273, 71, 80),
(32, 30, 489, 529, 566, 607, 628, -1, -1, 3, 1, 'Random Battleground', '', '', 'Champ de bataille aléatoire', 'Zufälliges Schlachtfeld', '', '随机战场', '', '', 'Campo de batalla aleatorio', '', 'Случайное поле боя', '', '', '', '', 16712190, 5, 0, 0, 0);
