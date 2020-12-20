-- ----------------------------
-- Table structure for dbc_movie
-- ----------------------------
DROP TABLE IF EXISTS `dbc_movie`;
CREATE TABLE `dbc_movie`  (
  `ID` int(11) NOT NULL DEFAULT 0,
  `Filename` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Volume` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of dbc_movie
-- ----------------------------
INSERT INTO `dbc_movie` VALUES
(1, 'Interface\\Cinematics\\Logo', 100),
(2, 'Interface\\Cinematics\\WOW_Intro', 100),
(14, '', 100),
(16, '', 100);
