-- ----------------------------
-- Table structure for playercreateinfo_spell
-- ----------------------------
DROP TABLE IF EXISTS `playercreateinfo_spell`;
CREATE TABLE `playercreateinfo_spell`  (
  `racemask` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `classmask` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Spell` mediumint(8) UNSIGNED NOT NULL DEFAULT 0,
  `Note` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`racemask`, `classmask`, `Spell`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci;
