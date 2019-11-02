--
-- Table structure for table `player_spells_for_level`
--

DROP TABLE IF EXISTS `player_spells_for_level`;
CREATE TABLE `player_spells_for_level`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `SpellId` int(10) UNSIGNED NOT NULL,
  `ReqLevel` int(10) UNSIGNED NOT NULL DEFAULT 1,
  `ReqClass` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ReqRace` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE = InnoDB AUTO_INCREMENT = 0 CHARACTER SET = utf8;