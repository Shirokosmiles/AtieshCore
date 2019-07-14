--
-- Table structure for table `item_present_slot`
--

DROP TABLE IF EXISTS `item_present_slot`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `item_present_slot` (
  `PresentSlotID` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `ItemId` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `description` text NOT NULL,
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;
/*!40101 SET character_set_client = @saved_cs_client */;