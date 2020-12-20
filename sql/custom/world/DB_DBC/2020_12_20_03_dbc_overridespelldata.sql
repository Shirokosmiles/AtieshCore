-- ----------------------------
-- Table structure for dbc_overridespelldata
-- ----------------------------
DROP TABLE IF EXISTS `dbc_overridespelldata`;
CREATE TABLE `dbc_overridespelldata`  (
  `ID` int(11) NOT NULL DEFAULT 0,
  `Spells_1` int(11) NOT NULL DEFAULT 0,
  `Spells_2` int(11) NOT NULL DEFAULT 0,
  `Spells_3` int(11) NOT NULL DEFAULT 0,
  `Spells_4` int(11) NOT NULL DEFAULT 0,
  `Spells_5` int(11) NOT NULL DEFAULT 0,
  `Spells_6` int(11) NOT NULL DEFAULT 0,
  `Spells_7` int(11) NOT NULL DEFAULT 0,
  `Spells_8` int(11) NOT NULL DEFAULT 0,
  `Spells_9` int(11) NOT NULL DEFAULT 0,
  `Spells_10` int(11) NOT NULL DEFAULT 0,
  `Flags` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Fixed;

-- ----------------------------
-- Records of dbc_overridespelldata
-- ----------------------------
INSERT INTO `dbc_overridespelldata` VALUES
(1, 40430, 59351, 31262, 61721, 0, 0, 0, 0, 0, 0, 5),
(61, 62634, 62479, 62473, 62471, 0, 62428, 0, 0, 0, 0, 0),
(121, 66905, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1),
(141, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(221, 69667, 69668, 69671, 69669, 0, 0, 0, 0, 0, 0, 0),
(241, 70946, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(266, 73491, 73492, 73499, 0, 0, 0, 0, 0, 0, 0, 0),
(271, 33912, 31289, 24331, 0, 0, 0, 0, 0, 0, 0, 0);
