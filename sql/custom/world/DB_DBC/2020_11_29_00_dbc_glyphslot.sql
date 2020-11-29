-- ----------------------------
-- Table structure for dbc_glyphslot
-- ----------------------------
DROP TABLE IF EXISTS `dbc_glyphslot`;
CREATE TABLE `dbc_glyphslot`  (
  `ID` int(11) NOT NULL DEFAULT 0,
  `Type` int(11) NOT NULL DEFAULT 0,
  `Tooltip` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Fixed;

-- ----------------------------
-- Records of dbc_glyphslot
-- ----------------------------
INSERT INTO `dbc_glyphslot` VALUES
(1, 4, 0),
(2, 2, 0),
(3, 3, 0),
(4, 0, 0),
(21, 0, 1),
(22, 1, 2),
(23, 1, 3),
(24, 0, 4),
(25, 1, 5),
(26, 0, 6);
