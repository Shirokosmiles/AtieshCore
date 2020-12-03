-- ----------------------------
-- Table structure for dbc_itembagfamily
-- ----------------------------
DROP TABLE IF EXISTS `dbc_itembagfamily`;
CREATE TABLE `dbc_itembagfamily`  (
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
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of dbc_itembagfamily
-- ----------------------------
INSERT INTO `dbc_itembagfamily` VALUES
(0, 'NONE', '', '', 'AUCUNE', 'NICHTS', '', '无', '', '', 'NADA', '', 'НЕТ', '', '', '', '', 16712190),
(1, 'Arrows', '', '', 'Flèches', 'Pfeile', '', '箭矢', '', '', 'Flechas', '', 'Стрелы', '', '', '', '', 16712190),
(2, 'Bullets', '', '', 'Balles', 'Kugeln', '', '弹药', '', '', 'Balas', '', 'Пули', '', '', '', '', 16712190),
(3, 'Soul Shards', '', '', 'Fragments d\'âme', 'Seelensplitter', '', '灵魂碎片', '', '', 'Fragmentos de almas', '', 'Камни душ', '', '', '', '', 16712190),
(4, 'Leatherworking Supplies', '', '', 'Fournitures de travail du cuir', 'Lederverarbeitungsbedarf', '', '制皮', '', '', 'Suministros de peletería', '', 'Товары для кожевников', '', '', '', '', 16712190),
(5, 'Inscription Supplies', '', '', 'Fournitures de calligraphie', 'Inschriftenkundebedarf', '', '铭文材料', '', '', 'Suministros de inscripción', '', 'Письменные принадлежности', '', '', '', '', 16712191),
(6, 'Herbs', '', '', 'Herbes', 'Kräuter', '', '草药', '', '', 'Hierbas', '', 'Травы', '', '', '', '', 16712190),
(7, 'Enchanting Supplies', '', '', 'Fournitures d\'enchanteur', 'Verzauberkunstbedarf', '', '附魔材料', '', '', 'Encantamiento', '', 'Товары для наложения чар', '', '', '', '', 16712190),
(8, 'Engineering Supplies', '', '', 'Fournitures d\'ingénieur', 'Ingenieursbedarf', '', '工程学材料', '', '', 'Ingeniería', '', 'Инженерные материалы', '', '', '', '', 16712190),
(9, 'Keys', '', '', 'Clés', 'Schlüssel', '', '钥匙', '', '', 'Llaves', '', 'Ключи', '', '', '', '', 16712190),
(10, 'Gems', '', '', 'Gemmes', 'Edelsteine', '', '宝石', '', '', 'Gemas', '', 'Самоцветы', '', '', '', '', 16712190),
(11, 'Mining Supplies', '', '', 'Fournitures de mineur', 'Bergbaubedarf', '', '矿物', '', '', 'Suministros de minería', '', 'Товары для горного дела', '', '', '', '', 16712190),
(12, 'Soulbound Equipment', '', '', 'Équipement lié', 'Seelengebundene Ausrüstung', '', '已绑定装备', '', '', 'Equipo ligado al alma', '', 'Персональное снаряжение', '', '', '', '', 16712190),
(13, 'Vanity Pets', '', '', 'Mascottes', 'Haustiere', '', '小宠物', '', '', 'Mascotas de vanidad', '', 'Спутники', '', '', '', '', 16712190),
(14, 'Currency Tokens', '', '', 'Monnaies', 'Währungsmarken', '', '货币物品', '', '', 'Monedas', '', 'Обменные жетоны', '', '', '', '', 16712190),
(15, 'Quest Items', '', '', 'Objets de quêtes', 'Questgegenstände', '', '任务物品', '', '', 'Objetos de misión', '', 'Предм. для заданий', '', '', '', '', 16712190);
