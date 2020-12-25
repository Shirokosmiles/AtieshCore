-- ----------------------------
-- Table structure for dbc_totemcategory
-- ----------------------------
DROP TABLE IF EXISTS `dbc_totemcategory`;
CREATE TABLE `dbc_totemcategory`  (
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
  `TotemCategoryType` int(11) NOT NULL DEFAULT 0,
  `TotemCategoryMask` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of dbc_totemcategory
-- ----------------------------
INSERT INTO `dbc_totemcategory` VALUES
(1, 'Skinning Knife (OLD)', '', '', 'Couteau à dépecer (OLD)', 'Kürschnermesser (alt)', '', '剥皮刀', '', '', 'Cuchillo para desollar', '', 'Нож для снятия шкур', '', '', '', '', 16712190, 1, 1),
(2, 'Earth Totem', '', '', 'Totem de terre', 'Erdtotem', '', '大地图腾', '', '', 'Tótem de tierra', '', 'Тотем земли', '', '', '', '', 16712190, 2, 1),
(3, 'Air Totem', '', '', 'Totem d\'air', 'Lufttotem', '', '空气图腾', '', '', 'Tótem de aire', '', 'Тотем воздуха', '', '', '', '', 16712190, 2, 2),
(4, 'Fire Totem', '', '', 'Totem de feu', 'Feuertotem', '', '火焰图腾', '', '', 'Tótem de fuego', '', 'Тотем огня', '', '', '', '', 16712190, 2, 4),
(5, 'Water Totem', '', '', 'Totem d\'eau', 'Wassertotem', '', '水之图腾', '', '', 'Tótem de agua', '', 'Тотем воды', '', '', '', '', 16712190, 2, 8),
(6, 'Runed Copper Rod', '', '', 'Bâtonnet runique en cuivre', 'Runenverzierte Kupferrute', '', '符文铜棒', '', '', 'Vara rúnica de cobre', '', 'Рунический медный жезл', '', '', '', '', 16712190, 3, 1),
(7, 'Runed Silver Rod', '', '', 'Bâtonnet runique en argent', 'Runenverzierte Silberrute', '', '符文银棒', '', '', 'Vara rúnica de plata', '', 'Рунический серебряный жезл', '', '', '', '', 16712190, 3, 3),
(8, 'Runed Golden Rod', '', '', 'Bâtonnet runique en or', 'Runenverzierte Goldrute', '', '符文金棒', '', '', 'Vara rúnica de oro', '', 'Рунический золотой жезл', '', '', '', '', 16712190, 3, 7),
(9, 'Runed Truesilver Rod', '', '', 'Bâtonnet runique en vrai-argent', 'Runenverzierte Echtsilberrute', '', '符文真银棒', '', '', 'Vara rúnica de veraplata', '', 'Рунический жезл истинного серебра', '', '', '', '', 16712190, 3, 15),
(10, 'Runed Arcanite Rod', '', '', 'Bâtonnet runique en arcanite', 'Runenverzierte Arkanitrute', '', '符文奥金棒', '', '', 'Vara rúnica de arcanita', '', 'Рунический арканитовый жезл', '', '', '', '', 16712190, 3, 31),
(11, 'Mining Pick (OLD)', '', '', 'Pioche de mineur (OLD)', 'Spitzhacke (alt)', '', '矿工锄', '', '', 'Pico de minería', '', 'Шахтерская кирка', '', '', '', '', 16712190, 21, 1),
(12, 'Philosopher\'s Stone', '', '', 'Pierre philosophale', 'Stein der Weisen', '', '点金石', '', '', 'Piedra filosofal', '', 'Философский камень', '', '', '', '', 16712190, 22, 1),
(13, 'Blacksmith Hammer (OLD)', '', '', 'Marteau de forgeron (VIEUX)', 'Schmiedehammer', '', '铁匠锤', '', '', 'Martillo de herrero', '', 'Кузнечный молот', '', '', '', '', 16712190, 23, 1),
(14, 'Arclight Spanner', '', '', 'Clé plate', 'Bogenlichtschraubenschlüssel', '', '扳手', '', '', 'Llave de tuerca arcoluz', '', 'Тангенциальный вращатель', '', '', '', '', 16712190, 24, 1),
(15, 'Gyromatic Micro-Adjustor', '', '', 'Micro-ajusteur gyromatique', 'Gyromatischer Mikroregler', '', '侏儒微调器', '', '', 'Microajustador giromático', '', 'Шлицевой гироинструмент', '', '', '', '', 16712190, 24, 2),
(21, 'Master Totem', '', '', 'Totem maître', 'Meistertotem', '', '大师图腾', '', '', 'Tótem maestro', '', 'Тотем власти', '', '', '', '', 16712190, 2, 15),
(41, 'Runed Fel Iron Rod', '', '', 'Bâtonnet runique en gangrefer', 'Runenverzierte Teufelseisenrute', '', '符文魔铁棒', '', '', 'Vara rúnica de hierro vil', '', 'Рунический жезл оскверненного железа', '', '', '', '', 16712190, 3, 63),
(62, 'Runed Adamantite Rod', '', '', 'Bâtonnet runique en adamantite', 'Runenverzierte Adamantitrute', '', '符文精金棒', '', '', 'Vara rúnica de adamantita', '', 'Рунический адамантитовый жезл', '', '', '', '', 16712190, 3, 127),
(63, 'Runed Eternium Rod', '', '', 'Bâtonnet runique en éternium', 'Runenverzierte Eterniumrute', '', '符文恒金棒', '', '', 'Vara rúnica de eternio', '', 'Рунический этерниевый жезл', '', '', '', '', 16712190, 3, 255),
(81, 'Hollow Quill', '', '', 'Plume creuse', 'Hohler Federkiel', '', '羽毛笔', '', '', 'Pluma hueca', '', 'Священное перо', '', '', '', '', 16712190, 22, 4),
(101, 'Runed Azurite Rod', '', '', 'Bâtonnet runique en azurite', 'Runenverzierte Azuritrute', '', '符文蓝铜棒', '', '', 'Vara rúnica de azurita', '', 'Рунический азуритовый жезл', '', '', '', '', 16712190, 3, 511),
(121, 'Virtuoso Inking Set', '', '', 'Coffret de calligraphie de virtuose', 'Schreibzeug des Virtuosen', '', '学者的书写工具', '', '', 'Juego de caligrafía de virtuoso', '', 'Набор виртуозного начертателя', '', '', '', '', 16712190, 24, -2147483648),
(141, 'Drums', '', '', 'Tambours', 'Trommeln', '', '战鼓', '', '', 'Tambores', '', 'Барабаны', '', '', '', '', 16712190, 24, 1073741824),
(161, 'Gnomish Army Knife', '', '', 'Couteau de l\'armée gnome', 'Gnomisches Armeemesser', '', '侏儒军刀', '', '', 'Navaja gnómica', '', 'Гномский армейский нож', '', '', '', '', 16712190, 24, 63),
(162, 'Blacksmith Hammer', '', '', 'Marteau de forgeron', 'Schmiedehammer', '', '铁匠锤', '', '', 'Martillo de herrero', '', 'Кузнечный молот', '', '', '', '', 16712190, 24, 4),
(165, 'Mining Pick', '', '', 'Pioche de mineur', 'Spitzhacke', '', '矿工锄', '', '', 'Pico de minería', '', 'Шахтерская кирка', '', '', '', '', 16712190, 24, 8),
(166, 'Skinning Knife', '', '', 'Couteau à dépecer', 'Kürschnermesser', '', '剥皮刀', '', '', 'Cuchillo para desollar', '', 'Нож для снятия шкур', '', '', '', '', 16712190, 24, 16),
(167, 'Hammer Pick', '', '', 'Pioche-marteau', 'Spitzhammer', '', '锤头锄', '', '', 'Martillo pico', '', 'Тяжелая кирка', '', '', '', '', 16712190, 24, 12),
(168, 'Bladed Pickaxe', '', '', 'Pioche à lame', 'Klingenhacke', '', '锋刃锄', '', '', 'Hacha pico afilada', '', 'Острая мотыга', '', '', '', '', 16712190, 24, 24),
(169, 'Flint and Tinder', '', '', 'Silex et amadou', 'Feuerstein und Zunder', '', '燧石和火绒', '', '', 'Sílex y yesca', '', 'Кремень и трут', '', '', '', '', 16712190, 24, 32),
(189, 'Runed Cobalt Rod (DO NOT USE)', '', '', 'Bâtonnet runique en cobalt (NE PAS UTILISER)', 'Runenverzierte Kobaltrute', '', 'Runed Cobalt Rod (DO NOT USE)', '', '', 'Vara rúnica de cobalto (DO NOT USE)', '', 'Рунический кобальтовый жезл (DO NOT USE)', '', '', '', '', 16712190, 3, 511),
(190, 'Runed Titanium Rod', '', '', 'Bâtonnet runique en titane', 'Runenverzierte Titanrute', '', '符文泰坦神铁棒', '', '', 'Vara rúnica de titanio', '', 'Рунический титановый жезл', '', '', '', '', 16712190, 3, 1023);
