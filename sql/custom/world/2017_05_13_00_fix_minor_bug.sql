-- not use fo characters
DELETE FROM `disables` WHERE `sourceType` = 0 and `entry` = 51804;
INSERT INTO `disables` (`sourceType`,`entry`,`flags`,`comment`) VALUES
(0, 51804, 8, 'Power Siphon');

-- fix area spell 
DELETE FROM `spell_area` WHERE `spell` IN (30562,30557,30550,30567);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
(30562, 3457, 0, 0, 0, 0, 2, 0, 0, 0), -- Legacy of the Mountain King
(30557, 3457, 0, 0, 0, 0, 2, 0, 0, 0), -- Wrath of the Titans
(30550, 3457, 0, 0, 0, 0, 2, 0, 0, 0), -- Redemption of the Fallen
(30567, 3457, 0, 0, 0, 0, 2, 0, 0, 0); -- Torment of the Worgen
