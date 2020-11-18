-- ----------------------------
-- Table structure for dbc_cinematicsequences
-- ----------------------------
DROP TABLE IF EXISTS `dbc_cinematicsequences`;
CREATE TABLE `dbc_cinematicsequences`  (
  `ID` int(11) NOT NULL DEFAULT 0,
  `SoundID` int(11) NOT NULL DEFAULT 0,
  `Camera_1` int(11) NOT NULL DEFAULT 0,
  `Camera_2` int(11) NOT NULL DEFAULT 0,
  `Camera_3` int(11) NOT NULL DEFAULT 0,
  `Camera_4` int(11) NOT NULL DEFAULT 0,
  `Camera_5` int(11) NOT NULL DEFAULT 0,
  `Camera_6` int(11) NOT NULL DEFAULT 0,
  `Camera_7` int(11) NOT NULL DEFAULT 0,
  `Camera_8` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Fixed;

-- ----------------------------
-- Records of dbc_cinematicsequences
-- ----------------------------
INSERT INTO `dbc_cinematicsequences` VALUES
(1, 0, 1, 0, 0, 0, 0, 0, 0, 0),
(2, 0, 2, 0, 0, 0, 0, 0, 0, 0),
(21, 0, 235, 0, 0, 0, 0, 0, 0, 0),
(41, 0, 234, 0, 0, 0, 0, 0, 0, 0),
(61, 0, 122, 0, 0, 0, 0, 0, 0, 0),
(81, 0, 142, 0, 0, 0, 0, 0, 0, 0),
(101, 0, 162, 0, 0, 0, 0, 0, 0, 0),
(121, 0, 182, 0, 0, 0, 0, 0, 0, 0),
(141, 0, 202, 0, 0, 0, 0, 0, 0, 0),
(161, 0, 224, 0, 0, 0, 0, 0, 0, 0),
(162, 0, 243, 0, 0, 0, 0, 0, 0, 0),
(163, 0, 244, 0, 0, 0, 0, 0, 0, 0),
(164, 0, 245, 0, 0, 0, 0, 0, 0, 0),
(165, 0, 246, 0, 0, 0, 0, 0, 0, 0);
