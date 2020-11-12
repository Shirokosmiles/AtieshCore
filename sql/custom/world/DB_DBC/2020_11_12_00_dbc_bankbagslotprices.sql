-- ----------------------------
-- Table structure for dbc_bankbagslotprices
-- ----------------------------
DROP TABLE IF EXISTS `dbc_bankbagslotprices`;
CREATE TABLE `dbc_bankbagslotprices`  (
  `guid` int(11) NOT NULL AUTO_INCREMENT,
  `ID` int(11) NOT NULL DEFAULT 0,
  `Cost` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`guid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 13 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Fixed;

-- ----------------------------
-- Records of dbc_bankbagslotprices
-- ----------------------------
INSERT INTO `dbc_bankbagslotprices` VALUES 
(1, 1, 1000),
(2, 2, 10000),
(3, 3, 100000),
(4, 4, 250000),
(5, 5, 250000),
(6, 6, 250000),
(7, 7, 250000),
(8, 8, 999999999),
(9, 9, 999999999),
(10, 10, 999999999),
(11, 11, 999999999),
(12, 12, 999999999);
