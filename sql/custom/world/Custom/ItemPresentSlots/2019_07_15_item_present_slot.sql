--
-- Table structure for table `item_present_slot`
--

DROP TABLE IF EXISTS `item_present_slot`;
CREATE TABLE `item_present_slot`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `PresentSlotID` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ItemId` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `description` tinytext CHARACTER SET utf8 ,
  PRIMARY KEY (`id`)
) ENGINE = InnoDB AUTO_INCREMENT = 0 CHARACTER SET = utf8;

-- ----------------------------
-- Records of warrior set
-- ----------------------------
DELETE FROM `item_present_slot` WHERE `PresentSlotID` = '1';
INSERT INTO `item_present_slot` (`PresentSlotID`, `ItemId`, `description`) VALUES 
(1, 40816, 'set warrior'),
(1, 40856, 'set warrior'),
(1, 40797, 'set warrior'),
(1, 40836, 'set warrior'),
(1, 40878, 'set warrior'),
(1, 40877, 'set warrior'),
(1, 40887, 'set warrior'),
(1, 42060, 'set warrior'),
(1, 42020, 'set warrior'),
(1, 42112, 'set warrior ring1'),
(1, 39401, 'set warrior ring1'),
(1, 42989, 'set warrior ring t1'),
(1, 42122, 'set warrior ring t2'),
(1, 42331, 'set warrior w1'),
(1, 42331, 'set warrior w2'),
(1, 42449, 'set warrior w3'),
(1, 42558, 'set warrior shield');
-- ----------------------------
-- Records of rogue set
-- ----------------------------
DELETE FROM `item_present_slot` WHERE `PresentSlotID` = '4';
INSERT INTO `item_present_slot` (`PresentSlotID`, `ItemId`, `description`) VALUES 
(4, 41644, 'set rogue'),
(4, 41646, 'set rogue'),
(4, 41647, 'set rogue'),
(4, 41643, 'set rogue'),
(4, 41645, 'set rogue'),
(4, 42241, 'set rogue'),
(4, 42247, 'set rogue'),
(4, 42449, 'set rogue'),
(4, 42060, 'set rogue'),
(4, 41830, 'set rogue'),
(4, 41827, 'set rogue'),
(4, 41828, 'set rogue'),
(4, 42020, 'set rogue'),
(4, 42122, 'set rogue'),
(4, 42123, 'set rogue'),
(4, 42989, 'set rogue'),
(4, 42112, 'set rogue ring1'),
(4, 42642, 'set rogue ring2');