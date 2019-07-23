--
-- Table structure for table `item_present_slot`
--

DROP TABLE IF EXISTS `item_present_slot`;
CREATE TABLE `item_present_slot`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `PresentSlotID` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ItemId` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Counts` int(10) UNSIGNED NOT NULL DEFAULT 1,
  `description` tinytext CHARACTER SET utf8 ,
  PRIMARY KEY (`id`)
) ENGINE = InnoDB AUTO_INCREMENT = 0 CHARACTER SET = utf8;

-- ----------------------------
-- Records of warrior set
-- ----------------------------
DELETE FROM `item_present_slot` WHERE `PresentSlotID` = '1';
INSERT INTO `item_present_slot` (`PresentSlotID`, `ItemId`, `Counts`, `description`) VALUES 
(1, 40816, 1, 'set warrior'),
(1, 40856, 1, 'set warrior'),
(1, 40797, 1, 'set warrior'),
(1, 40836, 1, 'set warrior'),
(1, 40878, 1, 'set warrior'),
(1, 40877, 1, 'set warrior'),
(1, 40887, 1, 'set warrior'),
(1, 42060, 1, 'set warrior'),
(1, 42020, 1, 'set warrior'),
(1, 42112, 1, 'set warrior ring1'),
(1, 39401, 1, 'set warrior ring1'),
(1, 42989, 1, 'set warrior ring t1'),
(1, 42122, 1, 'set warrior ring t2'),
(1, 42331, 2, 'set warrior w1'),
(1, 42449, 1, 'set warrior w2'),
(1, 42558, 1, 'set warrior shield');

-- ----------------------------
-- Records of hunter set
-- ----------------------------
DELETE FROM `item_present_slot` WHERE `PresentSlotID` = '3';
INSERT INTO `item_present_slot` (`PresentSlotID`, `ItemId`, `Counts`, `description`) VALUES 
(3, 41154, 1, 'set hunter helm'),
(3, 41214, 1, 'set hunter shoulder'),
(3, 41084, 1, 'set hunter chest'),
(3, 41140, 1, 'set hunter gauntlet'),
(3, 41202, 1, 'set hunter legs'),
(3, 41228, 1, 'set hunter feet'),
(3, 41233, 1, 'set hunter waist'),
(3, 41223, 1, 'set hunter wrist'),
(3, 42060, 1, 'set hunter cloak'),
(3, 42020, 1, 'set hunter neck'),
(3, 42112, 1, 'set hunter ring1'),
(3, 42642, 1, 'set hunter ring2'),
(3, 42122, 1, 'set hunter t1'),
(3, 42123, 2, 'set hunter t11'),
(3, 42989, 1, 'set hunter t2'),
(3, 42284, 1, 'set hunter w1'),
(3, 42289, 1, 'set hunter w2'),
(3, 41165, 6000, 'set hunter arrows'),
(3, 42489, 1, 'set hunter bow');

-- ----------------------------
-- Records of rogue set
-- ----------------------------
DELETE FROM `item_present_slot` WHERE `PresentSlotID` = '4';
INSERT INTO `item_present_slot` (`PresentSlotID`, `ItemId`, `Counts`, `description`) VALUES 
(4, 41644, 1, 'set rogue'),
(4, 41646, 1, 'set rogue'),
(4, 41647, 1, 'set rogue'),
(4, 41643, 1, 'set rogue'),
(4, 41645, 1, 'set rogue'),
(4, 42241, 1, 'set rogue'),
(4, 42247, 1, 'set rogue'),
(4, 42449, 1, 'set rogue'),
(4, 42060, 1, 'set rogue'),
(4, 41830, 1, 'set rogue'),
(4, 41827, 1, 'set rogue'),
(4, 41828, 1, 'set rogue'),
(4, 42020, 1, 'set rogue'),
(4, 42122, 1, 'set rogue'),
(4, 42123, 1, 'set rogue'),
(4, 42989, 1, 'set rogue'),
(4, 42112, 1, 'set rogue ring1'),
(4, 42642, 1, 'set rogue ring2');
