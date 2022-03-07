-- ----------------------------
-- Table structure for account_gm_log
-- ----------------------------
DROP TABLE IF EXISTS `account_gm_log`;
CREATE TABLE `account_gm_log` (
  `id` int(9) NOT NULL AUTO_INCREMENT,
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `player` varchar(12) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `account` int(9) NOT NULL,
  `command` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `position` varchar(96) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `selected` varchar(96) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `realmId` int(9) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `account` (`account`),
  KEY `player` (`player`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Table structure for account_gm_log_item
-- ----------------------------
DROP TABLE IF EXISTS `account_gm_log_item`;
CREATE TABLE `account_gm_log_item` (
  `id` int(9) NOT NULL AUTO_INCREMENT,
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `guid` int(9) NOT NULL,
  `player` varchar(12) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `account` int(9) NOT NULL,
  `item` int(6) NOT NULL,
  `item_guid` int(6) NOT NULL,
  `count` int(32) NOT NULL DEFAULT '0',
  `position` varchar(96) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `target` varchar(96) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `realmId` int(9) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `guid` (`guid`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
