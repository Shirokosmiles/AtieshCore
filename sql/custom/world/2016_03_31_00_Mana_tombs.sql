-- Ethereal Crypt Raider text
DELETE FROM `creature_text` WHERE `CreatureID` = 18311;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`, `BroadcastTextId`) VALUES
(18311, 0, 0, "If you hear the whisper, you're dying...", 12, 0, 50, 0, 0, 0, 0, "Ethereal Crypt Raider - talk 1", 0),
(18311, 0, 1, "You're far from home, stranger.", 12, 0, 50, 0, 0, 0, 0, "Ethereal Crypt Raider - talk 2", 0),
(18311, 0, 2, "What have the netherwinds brought us?", 12, 0, 50, 0, 0, 0, 0, "Ethereal Crypt Raider - talk 3", 0);

-- Ethereal Crypt Raider SAI
SET @ENTRY := 18311;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,7,8,25,0,0,11,22911,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereal Crypt Raider - Within 8-25 Range - Cast 'Charge' (Phase 1) (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,6,5800,13300,14000,18000,11,32315,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereal Crypt Raider - In Combat - Cast 'Soul Strike' (Phase 1) (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,6,5800,8400,25000,40000,11,31403,1,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Crypt Raider - In Combat - Cast 'Battle Shout' (Phase 1) (No Repeat)"),
(@ENTRY,0,3,4,2,0,100,7,0,30,0,0,11,8599,1,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Crypt Raider - Between 0-30% Health - Cast 'Enrage' (No Repeat) (Dungeon)"),
(@ENTRY,0,4,0,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Crypt Raider - Between 0-30% Health - Say Line 0 (No Repeat) (Dungeon)"),
(@ENTRY,0,5,0,4,0,30,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"etherial crypt raider - talk");

-- Ethereal Sorcerer text
DELETE FROM `creature_text` WHERE `CreatureID` = 18313;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`, `BroadcastTextId`) VALUES
(18313, 0, 0, "Welcome to the Void...", 12, 0, 50, 0, 0, 0, 0, "Ethereal Sorcerer - talk 1", 0),
(18313, 0, 1, "You're far from home, stranger.", 12, 0, 50, 0, 0, 0, 0, "Ethereal Sorcerer - talk 2", 0),
(18313, 0, 2, "If you hear the whisper, you're dying...", 12, 0, 50, 0, 0, 0, 0, "Ethereal Sorcerer - talk 3", 0);

-- Ethereal Sorcerer SAI
SET @ENTRY := 18313;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,7,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Sorcerer - Out of Combat - Disable Combat Movement (No Repeat) (Dungeon)"),
(@ENTRY,0,1,2,4,0,100,3,0,0,0,0,11,15791,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereal Sorcerer - On Aggro - Cast 'Arcane Missiles' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Sorcerer - On Aggro - Increment Phase By 1 (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,3,0,9,1,100,2,0,30,2400,3800,11,15791,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereal Sorcerer - Within 0-30 Range - Cast 'Arcane Missiles' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,4,5,4,0,100,5,0,0,0,0,11,22273,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereal Sorcerer - On Aggro - Cast 'Arcane Missiles' (No Repeat) (Heroic Dungeon)"),
(@ENTRY,0,5,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Sorcerer - On Aggro - Increment Phase By 1 (No Repeat) (Heroic Dungeon)"),
(@ENTRY,0,6,0,9,1,100,4,0,30,2400,3800,11,22273,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereal Sorcerer - Within 0-30 Range - Cast 'Arcane Missiles' (No Repeat) (Heroic Dungeon)"),
(@ENTRY,0,7,8,3,1,100,7,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Sorcerer - Between 0-15% Mana - Enable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,8,0,61,1,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Sorcerer - Between 0-15% Mana - Increment Phase By 1 (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,9,0,9,1,100,7,25,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Sorcerer - Within 25-80 Range - Enable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,10,0,9,1,100,7,5,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Sorcerer - Within 5-15 Range - Disable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,11,0,9,1,100,7,0,5,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Sorcerer - Within 0-5 Range - Enable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,12,0,3,0,100,6,30,100,100,100,23,0,1,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Sorcerer - Between 30-100% Mana - Decrement Phase By 1 (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,13,0,0,0,100,6,14000,22700,22300,22300,11,32349,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Sorcerer - In Combat - Cast 'Summon Arcane Fiend' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,14,0,0,0,100,6,14000,22700,22300,22300,11,32353,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Sorcerer - In Combat - Cast 'Summon Arcane Fiend' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,15,0,0,0,100,6,5100,10800,10800,15700,11,25603,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereal Sorcerer - In Combat - Cast 'Slow' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,16,0,4,0,30,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Ethereal Sorcerer - talk");

-- Ethereal Priest text
DELETE FROM `creature_text` WHERE `CreatureID` = 18317;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`, `BroadcastTextId`) VALUES
(18317, 0, 0, "What have the netherwinds brought us?", 12, 0, 50, 0, 0, 0, 0, "Ethereal Priest - talk 1", 0),
(18317, 0, 1, "Welcome to the Void...", 12, 0, 50, 0, 0, 0, 0, "Ethereal Priest - talk 2", 0);

-- Ethereal Priest SAI
SET @ENTRY := 18317;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,1000,6400,8400,15400,11,17139,1,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Priest - In Combat - Cast 'Power Word: Shield' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,1,0,0,0,100,4,1000,6400,8400,15400,11,35944,1,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Priest - In Combat - Cast 'Power Word: Shield' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,4800,7700,10800,20500,11,34944,1,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Priest - In Combat - Cast 'Holy Nova' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,3,0,0,0,100,4,4800,7700,10800,20500,11,37669,1,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Priest - In Combat - Cast 'Holy Nova' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,4,0,14,0,100,2,5500,40,25000,30000,11,22883,1,0,0,0,0,7,0,0,0,0,0,0,0,"Ethereal Priest - Friendly At 5500 Health - Cast 'Heal' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,5,0,14,0,100,4,9500,40,20000,30000,11,34945,1,0,0,0,0,7,0,0,0,0,0,0,0,"Ethereal Priest - Friendly At 9500 Health - Cast 'Heal' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,6,0,4,0,30,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Ethereal Priest - talk");

-- Ethereal Darkcaster text
DELETE FROM `creature_text` WHERE `CreatureID` = 18331;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`, `BroadcastTextId`) VALUES
(18331, 0, 0, "You're far from home, stranger.", 12, 0, 50, 0, 0, 0, 0, "Ethereal Darkcaster - talk 1", 0),
(18331, 0, 1, "What have the netherwinds brought us?", 12, 0, 50, 0, 0, 0, 0, "Ethereal Darkcaster - talk 2", 0),
(18331, 0, 2, "Welcome to the Void...", 12, 0, 50, 0, 0, 0, 0, "Ethereal Darkcaster - talk 3", 0),
(18331, 0, 3, "If you hear the whisper, you're dying...", 12, 0, 50, 0, 0, 0, 0, "Ethereal Darkcaster - talk 4", 0);

-- Ethereal Darkcaster SAI
SET @ENTRY := 18331;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,7,0,0,0,0,11,38061,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Darkcaster - On Aggro - Cast 'Vampiric Aura' (No Repeat) (Heroic Dungeon)"),
(@ENTRY,0,1,0,0,0,100,6,2500,6100,9600,12000,11,34942,32,0,0,0,0,5,0,0,0,0,0,0,0,"Ethereal Darkcaster - In Combat - Cast 'Shadow Word: Pain' (No Repeat) (Heroic Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,3700,7600,6000,6900,11,34930,1,0,0,0,0,6,0,0,0,0,0,0,0,"Ethereal Darkcaster - In Combat - Cast 'Mana Burn' (No Repeat) (Heroic Dungeon)"),
(@ENTRY,0,3,0,0,0,100,4,3700,7600,6000,6900,11,34931,1,0,0,0,0,6,0,0,0,0,0,0,0,"Ethereal Darkcaster - In Combat - Cast 'Mana Burn' (No Repeat) (Heroic Dungeon)"),
(@ENTRY,0,4,0,2,0,100,7,0,50,0,0,11,16592,1,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Darkcaster - Between 0-50% Health - Cast 'Shadowform' (No Repeat) (Heroic Dungeon)"),
(@ENTRY,0,5,0,4,0,30,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Ethereal Darkcaster - talk");

-- Nexus Stalker text
DELETE FROM `creature_text` WHERE `CreatureID` = 18314;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`, `BroadcastTextId`) VALUES
(18314, 0, 0, "What have the netherwinds brought us?", 12, 0, 50, 0, 0, 0, 0, "Nexus Stalker - talk 1", 0),
(18314, 0, 1, "If you hear the whisper, you're dying...", 12, 0, 50, 0, 0, 0, 0, "Nexus Stalker - talk 2", 0);

-- Nexus Stalker SAI
SET @ENTRY := 18314;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,5000,7900,9700,22100,11,34940,0,0,0,0,0,5,0,0,0,0,0,0,0,"Nexus Stalker - In Combat - Cast 'Gouge' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,3000,10400,12200,18600,11,33925,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nexus Stalker - In Combat - Cast 'Phantom Strike' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,2,0,0,0,100,4,3000,10400,12200,18600,11,39332,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nexus Stalker - In Combat - Cast 'Phantom Strike' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,3,0,4,0,30,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Nexus Stalker - talk");

-- Ethereal Spellbinder text
DELETE FROM `creature_text` WHERE `CreatureID` = 18312;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`, `BroadcastTextId`) VALUES
(18312, 0, 0, "Welcome to the Void...", 12, 0, 50, 0, 0, 0, 0, "Ethereal Spellbinder - talk 1", 0),
(18312, 0, 1, "You're far from home, stranger.", 12, 0, 50, 0, 0, 0, 0, "Ethereal Spellbinder - talk 2", 0);

-- Ethereal Spellbinder SAI
SET @ENTRY := 18312;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,3,15700,18100,0,0,11,32316,1,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Spellbinder - In Combat - Cast 'Summon Ethereal Wraith' (No Repeat) (Dungeon)"),
(@ENTRY,0,1,0,0,0,100,5,15700,18100,0,0,11,32316,1,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Spellbinder - In Combat - Cast 'Summon Ethereal Wraith' (No Repeat) (Dungeon)"),
(@ENTRY,0,2,0,0,0,100,5,15700,18100,0,0,11,32316,1,0,0,0,0,1,0,0,0,0,0,0,0,"Ethereal Spellbinder - In Combat - Cast 'Summon Ethereal Wraith' (No Repeat) (Dungeon)"),
(@ENTRY,0,3,0,0,0,100,2,500,1500,2300,8500,11,17883,0,0,0,0,0,5,0,0,0,0,0,0,0,"Ethereal Spellbinder - In Combat - Cast 'Immolate' (No Repeat) (Dungeon)"),
(@ENTRY,0,4,0,0,0,100,4,500,1500,2300,8500,11,37668,0,0,0,0,0,5,0,0,0,0,0,0,0,"Ethereal Spellbinder - In Combat - Cast 'Immolate' (No Repeat) (Dungeon)"),
(@ENTRY,0,5,0,13,0,100,6,8300,13300,0,0,11,37470,1,0,0,0,0,7,0,0,0,0,0,0,0,"Ethereal Spellbinder - Target Casting - Cast 'Counterspell' (No Repeat) (Dungeon)"),
(@ENTRY,0,6,0,4,0,30,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Etherel Spellbinder - talk");

-- Ethereal Theurgist text
DELETE FROM `creature_text` WHERE `CreatureID` = 18315;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`, `BroadcastTextId`) VALUES
(18315, 0, 0, "What have the netherwinds brought us?", 12, 0, 50, 0, 0, 0, 0, "Ethereal Theurgist - talk 1", 0);

-- Ethereal Theurgist SAI
SET @ENTRY := 18315;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,5,5000,8500,11,15580,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereal Theurgist - Within 0-5 Range - Cast 'Strike' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,1,0,9,0,100,4,0,5,5000,8500,11,34920,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereal Theurgist - Within 0-5 Range - Cast 'Strike' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,4200,6500,8000,12000,11,17145,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereal Theurgist - In Combat - Cast 'Blast Wave' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,3,0,0,0,100,4,4200,6500,8000,12000,11,38064,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ethereal Theurgist - In Combat - Cast 'Blast Wave' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,4,0,0,0,100,6,2400,7200,18000,24000,11,13323,1,0,0,0,0,5,0,0,0,0,0,0,0,"Ethereal Theurgist - In Combat - Cast 'Polymorph' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,5,0,4,0,30,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Ethereal Theurgist - talk");