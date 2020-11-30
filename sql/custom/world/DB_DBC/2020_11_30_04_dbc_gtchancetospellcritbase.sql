-- ----------------------------
-- Table structure for dbc_gtchancetospellcritbase
-- ----------------------------
DROP TABLE IF EXISTS `dbc_gtchancetospellcritbase`;
CREATE TABLE `dbc_gtchancetospellcritbase`  (
  `ID` int(11) NOT NULL DEFAULT 0,
  `Data` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Fixed;

-- ----------------------------
-- Records of dbc_gtchancetospellcritbase
-- ----------------------------
INSERT INTO `dbc_gtchancetospellcritbase` VALUES
(1, 0),
(2, 0.033355),
(3, 0.03602),
(4, 0),
(5, 0.012375),
(6, 0),
(7, 0.02201),
(8, 0.009075),
(9, 0.017),
(10, 0.2),
(11, 0.018515);
