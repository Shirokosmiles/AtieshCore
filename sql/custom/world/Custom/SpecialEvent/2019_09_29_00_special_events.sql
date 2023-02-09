--
-- Table structure for table `special_events`
--

DROP TABLE IF EXISTS `special_events`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `special_events` (
  `TypeId` tinyint(3) unsigned NOT NULL,
  `ScriptName` char(64) NOT NULL DEFAULT '',
  `isEnabled` int(10) UNSIGNED NOT NULL DEFAULT 1,
  `isActiveStatus` int(10) UNSIGNED NOT NULL DEFAULT 1,
  `isRepeatable` int(10) UNSIGNED NOT NULL DEFAULT 1,
  `cooldownTimer` int(10) UNSIGNED NOT NULL,
  `durationTimer` int(10) UNSIGNED NOT NULL,
  `comment` text,
  PRIMARY KEY (`TypeId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='special_events Templates';
/*!40101 SET character_set_client = @saved_cs_client */;

INSERT INTO `special_events`(`TypeId`, `ScriptName`, `isEnabled`, `isActiveStatus`, `isRepeatable`, `cooldownTimer`, `durationTimer`, `comment`) VALUES 
(1, 'dalaran_crater', 1, 0, 1, 45, 7, 'Dalaran Crater PVP Event'),
(2, 'the_light_of_dawn', 1, 0, 0, 60, 40, 'The Light of Dawn Event - Quest');