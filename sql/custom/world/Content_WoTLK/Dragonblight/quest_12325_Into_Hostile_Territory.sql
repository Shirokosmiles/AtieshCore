DELETE FROM `creature_text` WHERE `CreatureID`=27662;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(27662,0,0,'Hang on to your hat, $n! To Scalawag we go!',12,0,100,0,0,0,27272,0,'start fly'),
(27662,1,0,'This is your stop, pal. Safe landing!',12,0,100,0,0,0,26924,0,'end fly');

UPDATE `creature_template` SET `ScriptName` = 'npc_sky_captain_cryoflight' WHERE (entry = 27661);