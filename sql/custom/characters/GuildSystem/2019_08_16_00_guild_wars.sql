--
-- Table structure for table `guild_wars`
--

DROP TABLE IF EXISTS `guild_wars`;
CREATE TABLE `guild_wars`  (
  `id` int(10) UNSIGNED NOT NULL,
  `Attacker_guild_Id` int(10) UNSIGNED NOT NULL,
  `Defender_guild_Id` int(10) UNSIGNED NOT NULL,
  `time_of_start` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `time_of_end` timestamp,
  `winner` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE = InnoDB CHARACTER SET = utf8;