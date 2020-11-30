-- ----------------------------
-- Table structure for dbc_gtchancetomeleecritbase
-- ----------------------------
DROP TABLE IF EXISTS `dbc_gtchancetomeleecritbase`;
CREATE TABLE `dbc_gtchancetomeleecritbase`  (
  `ID` int(11) NOT NULL DEFAULT 0,
  `Data` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Fixed;

-- ----------------------------
-- Records of dbc_gtchancetomeleecritbase
-- ----------------------------
INSERT INTO `dbc_gtchancetomeleecritbase` VALUES
(1, 0.031891),
(2, 0.032685),
(3, -0.01532),
(4, -0.00295),
(5, 0.031765),
(6, 0.031891),
(7, 0.02922),
(8, 0.03454),
(9, 0.02622),
(10, 0.2),
(11, 0.074755);
