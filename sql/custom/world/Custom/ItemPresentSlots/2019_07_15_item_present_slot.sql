--
-- Table structure for table `item_present_slot`
--

DROP TABLE IF EXISTS `item_present_slot`;
CREATE TABLE `item_present_slot`  (
  `PresentSlotID` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ItemId` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `description` tinytext CHARACTER SET utf8
) ENGINE = InnoDB CHARACTER SET = utf8;