-- ----------------------------
-- Table structure for dbс_auctionhouse
-- ----------------------------
DROP TABLE IF EXISTS `dbc_auctionhouse`;
CREATE TABLE `dbc_auctionhouse`  (
  `guid` int(11) NOT NULL AUTO_INCREMENT,
  `ID` int(11) NOT NULL DEFAULT 0,
  `FactionID` int(11) NOT NULL DEFAULT 0,
  `DepositRate` int(11) NOT NULL DEFAULT 0,
  `ConsignmentRate` int(11) NOT NULL DEFAULT 0,
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
  PRIMARY KEY (`guid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 8 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of dbс_auctionhouse
-- ----------------------------
INSERT INTO `dbс_auctionhouse` VALUES 
(1, 1, 1, 5, 5, 'Stormwind Auction House', '', '', 'Hôtel des ventes de Hurlevent', 'Auktionshaus von Sturmwind', '', '暴风城拍卖行', '', '', 'Casa de subastas: Ventormenta', '', 'Аукционный дом Штормграда', '', '', '', '', 16712190),
(2, 2, 3, 5, 5, 'Alliance Auction House', '', '', 'Hôtel des ventes de l\\\'Alliance', 'Auktionshaus der Allianz', '', '联盟拍卖行', '', '', 'Casa de subastas: Alianza', '', 'Аукционный дом Альянса', '', '', '', '', 16712190),
(3, 3, 4, 5, 5, 'Darnassus Auction House', '', '', 'Hôtel des ventes de Darnassus', 'Auktionshaus von Darnassus', '', '达纳苏斯拍卖行', '', '', 'Casa de subastas: Darnassus', '', 'Аукционный дом Дарнаса', '', '', '', '', 16712190),
(4, 4, 5, 5, 5, 'Undercity Auction House', '', '', 'Hôtel des ventes de Fossoyeuse', 'Auktionshaus von Unterstadt', '', '幽暗城拍卖行', '', '', 'Casa de subastas: Entrañas', '', 'Аукционный дом Подгорода', '', '', '', '', 16712190),
(5, 5, 6, 5, 5, 'Thunder Bluff  Auction House', '', '', 'Hôtel des ventes des Pitons du Tonnerre', 'Auktionshaus von Donnerfels', '', '雷霆崖拍卖行', '', '', 'Casa de subastas: Cima del Trueno', '', 'Аукционный дом Громового Утеса', '', '', '', '', 16712190),
(6, 6, 2, 5, 5, 'Horde Auction House', '', '', 'Hôtel des ventes de la Horde', 'Auktionshaus der Horde', '', '部落拍卖行', '', '', 'Casa de subastas: Horda', '', 'Аукционный дом Орды', '', '', '', '', 16712190),
(7, 7, 369, 25, 15, 'Blackwater Auction House', '', '', 'Hôtel des ventes des Flots noirs', 'Auktionshaus der Schwarzmeerräuber', '', '黑水拍卖行', '', '', 'Casa de subastas: Aguasnegras', '', 'Аукционный дом Черноводья', '', '', '', '', 16712190);
