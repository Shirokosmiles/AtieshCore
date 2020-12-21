-- ----------------------------
-- Table structure for dbc_questfactionreward
-- ----------------------------
DROP TABLE IF EXISTS `dbc_questfactionreward`;
CREATE TABLE `dbc_questfactionreward`  (
  `ID` int(11) NOT NULL DEFAULT 0,
  `Difficulty_1` int(11) NOT NULL DEFAULT 0,
  `Difficulty_2` int(11) NOT NULL DEFAULT 0,
  `Difficulty_3` int(11) NOT NULL DEFAULT 0,
  `Difficulty_4` int(11) NOT NULL DEFAULT 0,
  `Difficulty_5` int(11) NOT NULL DEFAULT 0,
  `Difficulty_6` int(11) NOT NULL DEFAULT 0,
  `Difficulty_7` int(11) NOT NULL DEFAULT 0,
  `Difficulty_8` int(11) NOT NULL DEFAULT 0,
  `Difficulty_9` int(11) NOT NULL DEFAULT 0,
  `Difficulty_10` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Fixed;

-- ----------------------------
-- Records of dbc_questfactionreward
-- ----------------------------
INSERT INTO `dbc_questfactionreward` VALUES
(1, 0, 10, 25, 75, 150, 250, 350, 500, 1000, 5),
(2, 0, -10, -25, -75, -150, -250, -350, -500, -1000, -5);
