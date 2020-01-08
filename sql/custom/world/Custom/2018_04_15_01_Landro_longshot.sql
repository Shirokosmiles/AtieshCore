-- Create table
DROP TABLE IF EXISTS promotion_codes;

-- Update text
DELETE FROM `creature_text` WHERE `CreatureID` = 17249;
INSERT INTO `creature_text`(`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `comment`) VALUES (17249,3,0,'I can see that you are not interesting, come back if you will change your mind',12,0,100,0,0,0,'Landro not interested'),
(17249,2,2,'Here is your gift',12,0,100,0,0,0,'Landro correct'),
(17249,1,1,'Someone probably cheated on you, next time try not to buy anything from strangers',12,0,100,0,0,0,'Landro not correct');

UPDATE `creature_template` SET `ScriptName` = 'landro_longshot' WHERE `creature_template`.`entry` = 17249;