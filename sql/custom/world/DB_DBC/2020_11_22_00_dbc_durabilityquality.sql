-- ----------------------------
-- Table structure for dbc_durabilityquality
-- ----------------------------
DROP TABLE IF EXISTS `dbc_durabilityquality`;
CREATE TABLE `dbc_durabilityquality`  (
  `ID` int(11) NOT NULL DEFAULT 0,
  `Data` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Fixed;

-- ----------------------------
-- Records of dbc_durabilityquality
-- ----------------------------
INSERT INTO `dbc_durabilityquality` VALUES
(1, 1),
(2, 0.6),
(3, 1),
(4, 0.8),
(5, 1),
(6, 1),
(7, 1.2),
(8, 1.25),
(9, 1.44),
(10, 2.5),
(11, 1.728),
(12, 3),
(13, 0),
(14, 0),
(15, 1.2),
(16, 1.25);
