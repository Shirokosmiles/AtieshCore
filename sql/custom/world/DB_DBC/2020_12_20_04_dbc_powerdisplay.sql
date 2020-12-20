-- ----------------------------
-- Table structure for dbc_powerdisplay
-- ----------------------------
DROP TABLE IF EXISTS `dbc_powerdisplay`;
CREATE TABLE `dbc_powerdisplay`  (
  `ID` int(11) NOT NULL DEFAULT 0,
  `ActualType` int(11) NOT NULL DEFAULT 0,
  `GlobalstringBaseTag` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `Red` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `Green` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `Blue` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of dbc_powerdisplay
-- ----------------------------
INSERT INTO `dbc_powerdisplay` VALUES
(1, 0, 'AMMOSLOT', 255, 128, 0),
(41, 3, 'POWER_TYPE_PYRITE', 0, 202, 255),
(61, 3, 'POWER_TYPE_STEAM', 242, 242, 242),
(101, 3, 'POWER_TYPE_HEAT', 255, 125, 0),
(121, 3, 'POWER_TYPE_OOZE', 193, 255, 0),
(141, 3, 'POWER_TYPE_BLOOD_POWER', 188, 0, 255),
(142, 3, 'POWER_TYPE_WRATH', 255, 176, 0);
