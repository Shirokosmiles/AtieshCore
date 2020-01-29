-- ----------------------------
-- Table structure for warden_log
-- ----------------------------
DROP TABLE IF EXISTS `warden_log`;
CREATE TABLE `warden_log`  (
  `entry` int(11) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Log entry ID',
  `check` smallint(5) UNSIGNED NOT NULL COMMENT 'Failed Warden check ID',
  `action` tinyint(3) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Action taken (enum WardenActions)',
  `account` int(11) UNSIGNED NOT NULL COMMENT 'The account ID of the player.',
  `guid` int(11) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Player GUID',
  `map` int(11) UNSIGNED NULL DEFAULT NULL COMMENT 'The map id. (See map.dbc)',
  `position_x` float NULL DEFAULT NULL COMMENT 'The x location of the player.',
  `position_y` float NULL DEFAULT NULL COMMENT 'The y location of the player.',
  `position_z` float NULL DEFAULT NULL COMMENT 'The z location of the player.',
  `date` timestamp(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT 'The date/time when the log entry was raised, in Unix time.',
  PRIMARY KEY (`entry`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = 'Warden log of failed checks' ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
