-- ----------------------------
-- Table structure for dbc_bankbagslotprices
-- ----------------------------
DROP TABLE IF EXISTS `dbc_bankbagslotprices`;
CREATE TABLE `dbc_bankbagslotprices`  (
  `ID` int(11) NOT NULL DEFAULT 0,
  `Cost` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Fixed;

-- ----------------------------
-- Records of dbc_bankbagslotprices
-- ----------------------------
INSERT INTO `dbc_bankbagslotprices` VALUES
(1, 1000),
(2, 10000),
(3, 100000),
(4, 250000),
(5, 250000),
(6, 250000),
(7, 250000),
(8, 999999999),
(9, 999999999),
(10, 999999999),
(11, 999999999),
(12, 999999999);
