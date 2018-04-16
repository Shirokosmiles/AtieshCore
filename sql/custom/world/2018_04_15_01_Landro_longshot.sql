-- Create table
DROP TABLE IF EXISTS promotion_codes;
CREATE TABLE IF NOT EXISTS `promotion_codes` (
`id` int(11) NOT NULL,
  `collection` int(11) NOT NULL,
  `item` int(11) NOT NULL,
  `code` int(11) NOT NULL,
  `used` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Update text
DELETE FROM `creature_text` WHERE `comment` = 'Landro not correct';
INSERT INTO `creature_text`(`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `comment`) VALUES (17249,3,0,'I can see that you are not interesting, come back if you will change your mind',12,0,100,0,0,0,'Landro not interested'),
(17249,2,2,'Here is your gift',12,0,100,0,0,0,'Landro correct'),
(17249,1,1,'Someone probably cheated on you, next time try not to buy anything from strangers',12,0,100,0,0,0,'Landro not correct');

UPDATE `creature_template` SET `ScriptName` = 'landro_longshot' WHERE `creature_template`.`entry` = 17249;