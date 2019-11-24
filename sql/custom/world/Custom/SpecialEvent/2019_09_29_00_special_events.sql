--
-- Table structure for table `special_events`
--

DROP TABLE IF EXISTS `special_events`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `special_events` (
  `TypeId` tinyint(3) unsigned NOT NULL,
  `ScriptName` char(64) NOT NULL DEFAULT '',
  `cooldownTimer` int(10) UNSIGNED NOT NULL,
  `durationTimer` int(10) UNSIGNED NOT NULL,
  `activeStatus` int(10) UNSIGNED NOT NULL DEFAULT 1,
  `comment` text,
  PRIMARY KEY (`TypeId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='special_events Templates';
/*!40101 SET character_set_client = @saved_cs_client */;

INSERT INTO `special_events`(`TypeId`, `ScriptName`, `cooldownTimer`, `durationTimer`, `activeStatus`, `comment`) VALUES 
(1, 'dalaran_crater', 45, 7, 1, 'Dalaran Crater PVP Event');

