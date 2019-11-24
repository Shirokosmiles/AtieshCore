--
-- Table structure for table `battlefields`
--

DROP TABLE IF EXISTS `battlefields`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `battlefields` (
  `TypeId` tinyint(3) unsigned NOT NULL,
  `ScriptName` char(64) NOT NULL DEFAULT '',
  `cooldownTimer` int(10) UNSIGNED NOT NULL,
  `durationTimer` int(10) UNSIGNED NOT NULL,
  `enabled` int(10) UNSIGNED NOT NULL,
  `active` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `minlevel` int(10) UNSIGNED NOT NULL DEFAULT 1,
  `maxplayers` int(10) UNSIGNED NOT NULL DEFAULT 120,
  `controlteam` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `remainingtime` int(10) UNSIGNED NOT NULL,
  `comment` text,
  PRIMARY KEY (`TypeId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='battlefields Templates';
/*!40101 SET character_set_client = @saved_cs_client */;

INSERT INTO `battlefields`(`TypeId`, `ScriptName`, `cooldownTimer`, `durationTimer`, `enabled`, `active`, `minlevel`, `maxplayers`, `controlteam`, `remainingtime`, `comment`) VALUES 
(1, 'Wintergrasp', 150, 30, 1, 0, 75, 120, 0, 0, 'Wintergrasp battlefield');