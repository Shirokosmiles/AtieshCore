--
-- Table structure for table `guild_wars`
--

DROP TABLE IF EXISTS `guild_wars`;
CREATE TABLE `guild_wars`  (
  `id` int(10) UNSIGNED NOT NULL,
  `Attacker_Guild_ID` int(10) UNSIGNED NOT NULL,
  `Defender_Guild_ID` int(10) UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE = InnoDB CHARACTER SET = utf8;

--
-- Table structure for table `guild_wars_history`
--

DROP TABLE IF EXISTS `guild_wars_history`;
CREATE TABLE `guild_wars_history`  (
  `id` int(10) UNSIGNED NOT NULL,
  `Attacker_Guild_ID` int(10) UNSIGNED NOT NULL,
  `Attacker_Guild` varchar(90) NOT NULL,
  `Defender_Guild_ID` int(10) UNSIGNED NOT NULL,
  `Defender_Guild` varchar(90) NOT NULL,
  `Time_Of_Start` int(10) UNSIGNED NOT NULL,
  `Time_Of_End` int(10) UNSIGNED NOT NULL,
  `Winner` varchar(90) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE = InnoDB CHARACTER SET = utf8;