-- ----------------------------
-- Table structure for dbc_stableslotprices
-- ----------------------------
DROP TABLE IF EXISTS `dbc_stableslotprices`;
CREATE TABLE `dbc_stableslotprices`  (
  `ID` int(11) NOT NULL DEFAULT 0,
  `Cost` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Fixed;

-- ----------------------------
-- Records of dbc_stableslotprices
-- ----------------------------
INSERT INTO `dbc_stableslotprices` VALUES
(1, 500),
(2, 50000),
(3, 500000),
(4, 1500000);
