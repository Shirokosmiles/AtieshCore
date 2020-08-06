DROP TABLE IF EXISTS `character_instance_completed`;
CREATE TABLE `character_instance_completed`  (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `guid` int(10) NOT NULL COMMENT 'Global Unique Identifier',
  `map` smallint(5) NOT NULL,
  `difficulty` tinyint(3) NOT NULL,
  `data` tinytext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE = InnoDB CHARACTER SET = utf8;