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
-- Records of commom paladin set
-- ----------------------------
DELETE FROM `item_present_slot` WHERE `PresentSlotID` = '2';
INSERT INTO `item_present_slot` (`PresentSlotID`, `ItemId`, `Counts`, `description`) VALUES
(2, 42112, 1, 'set paladin'),
(2, 42110, 1, 'set paladin'),

(2, 42122, 1, 'set paladin'),
(2, 42123, 1, 'set paladin'),

(2, 42987, 1, 'set paladin'),
(2, 42988, 1, 'set paladin'),

(2, 42851, 1, 'set paladin'),
(2, 42613, 1, 'set paladin');
-- ----------------------------
-- Records of retribution paladin set
-- ----------------------------
DELETE FROM `item_present_slot` WHERE `PresentSlotID` = '21';
INSERT INTO `item_present_slot` (`PresentSlotID`, `ItemId`, `Counts`, `description`) VALUES
(21, 40818, 1, 'set paladin helm'),
(21, 40858, 1, 'set paladin shoulder'),
(21, 40780, 1, 'set paladin chest'),
(21, 40798, 1, 'set paladin hands'),
(21, 40838, 1, 'set paladin legs'),

(21, 40887, 1, 'set paladin wrist'),
(21, 40877, 1, 'set paladin'),
(21, 40878, 1, 'set paladin'),
(21, 42060, 1, 'set paladin'),
(21, 42020, 1, 'set paladin'),

(21, 42331, 1, 'set paladin weapon');

-- ----------------------------
-- Records of holy paladin set
-- ----------------------------
DELETE FROM `item_present_slot` WHERE `PresentSlotID` = '22';
INSERT INTO `item_present_slot` (`PresentSlotID`, `ItemId`, `Counts`, `description`) VALUES
(22, 40930, 1, 'set paladin helm'),
(22, 40960, 1, 'set paladin shoulder'),
(22, 40898, 1, 'set paladin chest'),
(22, 40918, 1, 'set paladin hands'),
(22, 40936, 1, 'set paladin legs'),

(22, 40972, 1, 'set paladin wrist'),
(22, 40966, 1, 'set paladin'),
(22, 40973, 1, 'set paladin'),
(22, 42055, 1, 'set paladin'),
(22, 42022, 1, 'set paladin'),

(22, 42351, 1, 'set paladin'),
(22, 42563, 1, 'set paladin');
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

-- ----------------------------
-- Records of common priest set
-- ----------------------------
DELETE FROM `item_present_slot` WHERE `PresentSlotID` = '5';
INSERT INTO `item_present_slot` (`PresentSlotID`, `ItemId`, `Counts`, `description`) VALUES 
(5, 42110, 1, 'set priest'),
(5, 39407, 1, 'set priest'),
(5, 42122, 1, 'set priest'),
(5, 42123, 1, 'set priest');

-- ----------------------------
-- Records of shadow priest set
-- ----------------------------
DELETE FROM `item_present_slot` WHERE `PresentSlotID` = '51';
INSERT INTO `item_present_slot` (`PresentSlotID`, `ItemId`, `Counts`, `description`) VALUES 
(51, 41912, 1, 'set priest shadow'),
(51, 41930, 1, 'set priest shadow'),
(51, 41918, 1, 'set priest shadow'),
(51, 41937, 1, 'set priest shadow'),
(51, 41924, 1, 'set priest shadow'),
(51, 41907, 1, 'set priest shadow'),
(51, 41896, 1, 'set priest shadow'),
(51, 41901, 1, 'set priest shadow'),
(51, 42022, 1, 'set priest shadow'),
(51, 42055, 1, 'set priest shadow'),
(51, 42988, 1, 'set priest shadow'),
(51, 42359, 1, 'set priest shadow'),
(51, 42501, 1, 'set priest shadow');

-- ----------------------------
-- Records of healer priest set
-- ----------------------------
DELETE FROM `item_present_slot` WHERE `PresentSlotID` = '52';
INSERT INTO `item_present_slot` (`PresentSlotID`, `ItemId`, `Counts`, `description`) VALUES 
(52, 41848, 1, 'set priest heal'),
(52, 41850, 1, 'set priest heal'),
(52, 41851, 1, 'set priest heal'),
(52, 41847, 1, 'set priest heal'),
(52, 41849, 1, 'set priest heal'),
(52, 41878, 1, 'set priest heal'),
(52, 41877, 1, 'set priest heal'),
(52, 41879, 1, 'set priest heal'),
(52, 42025, 1, 'set priest heal'),
(52, 42059, 1, 'set priest heal'),
(52, 40685, 1, 'set priest heal'),
(52, 42512, 1, 'set priest heal'),
(52, 42351, 1, 'set priest heal'),
(52, 42530, 1, 'set priest heal');

-- ----------------------------
-- Records of DK set
-- ----------------------------
DELETE FROM `item_present_slot` WHERE `PresentSlotID` = '6';
INSERT INTO `item_present_slot` (`PresentSlotID`, `ItemId`, `Counts`, `description`) VALUES 
(6, 40817, 1, 'set dk'),
(6, 40857, 1, 'set dk'),
(6, 40779, 1, 'set dk'),
(6, 40799, 1, 'set dk'),
(6, 40837, 1, 'set dk'),
(6, 40887, 1, 'set dk'),
(6, 40877, 1, 'set dk'),
(6, 40878, 1, 'set dk'),
(6, 42020, 1, 'set dk'),
(6, 42112, 1, 'set dk'),
(6, 39401, 1, 'set dk'),
(6, 42122, 1, 'set dk'),
(6, 42123, 1, 'set dk'),
(6, 42989, 1, 'set dk'),
(6, 42060, 1, 'set dk'),
(6, 42619, 1, 'set dk'),
(6, 42331, 1, 'set dk');