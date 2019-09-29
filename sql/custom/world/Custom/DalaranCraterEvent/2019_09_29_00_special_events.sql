--
-- Table structure for table `special_events`
--

DROP TABLE IF EXISTS `special_events`;
CREATE TABLE `special_events`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `eventId` int(10) UNSIGNED NOT NULL,
  `cooldownTimer` int(10) UNSIGNED NOT NULL,
  `durationTimer` int(10) UNSIGNED NOT NULL,
  `activeStatus` int(10) UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE = InnoDB CHARACTER SET = utf8;