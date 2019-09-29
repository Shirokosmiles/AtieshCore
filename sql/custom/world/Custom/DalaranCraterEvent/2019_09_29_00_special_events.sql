--
-- Table structure for table `special_events`
--

DROP TABLE IF EXISTS `special_events`;
CREATE TABLE `special_events`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `eventId` int(10) UNSIGNED NOT NULL,
  `cooldownTimer` int(10) UNSIGNED NOT NULL,
  `durationTimer` int(10) UNSIGNED NOT NULL,
  `activeStatus` int(10) UNSIGNED NOT NULL DEFAULT 1,
  `description` tinytext CHARACTER SET utf8 ,
  PRIMARY KEY (`id`)
) ENGINE = InnoDB CHARACTER SET = utf8;

INSERT INTO `special_events`(`id`, `eventId`, `cooldownTimer`, `durationTimer`, `activeStatus`, `description`) VALUES 
(1, 1, 2, 1, 1, 'Wintergrasp (WIP)'),
(2, 2, 2, 1, 1, 'Dalaran Crater');
