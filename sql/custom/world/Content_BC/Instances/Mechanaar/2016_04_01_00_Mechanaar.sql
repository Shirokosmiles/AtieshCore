-- Bloodwarder Centurion SAI
SET @ENTRY := 19510;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,6000,6000,8000,9000,11,35178,0,0,0,0,0,5,0,0,0,0,0,0,0,"Bloodwarder Centurion - In Combat - Cast 'Shield Bash' (No Repeat) (Dungeon)"),
(@ENTRY,0,1,0,0,0,100,0,3000,10000,15000,30000,11,35185,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodwarder Centurion - In Combat - Cast 'Melt Armor'");

-- Bloodwarder Physician SAI
SET @ENTRY := 20990;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1000,1000,5000,6000,11,36333,0,0,0,0,0,6,0,0,0,0,0,0,0,"Bloodwarder Physician - In Combat - Cast 'Anesthetic'"),
(@ENTRY,0,1,0,0,0,100,2,4000,4000,9000,10000,11,36340,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodwarder Physician - In Combat - Cast 'Holy Shock' (No Repeat) (Dungeon)"),
(@ENTRY,0,2,0,0,0,100,4,4000,4000,9000,10000,11,38921,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodwarder Physician - In Combat - Cast 'Holy Shock' (No Repeat) (Dungeon)"),
(@ENTRY,0,3,0,2,0,100,2,0,50,10000,10000,11,36348,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodwarder Physician - Between 0-50% Health - Cast 'Bandage' (No Repeat) (Dungeon)"),
(@ENTRY,0,4,0,2,0,100,4,0,50,10000,10000,11,38919,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodwarder Physician - Between 0-50% Health - Cast 'Bandage' (No Repeat) (Dungeon)");

-- Sunseeker Netherbinder SAI
SET @ENTRY := 20059;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,1,0,0,0,100,4,6000,6000,11000,13000,11,38936,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunseeker Netherbinder - In Combat - Cast 'Arcane Nova' "),
(@ENTRY,0,2,0,0,0,100,6,6000,6000,12000,17000,11,17201,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunseeker Netherbinder - In Combat - Cast 'Dispel Magic' "),
(@ENTRY,0,3,0,0,0,100,0,5000,6000,8000,15000,11,21668,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sunseeker Netherbinder - In Combat - Cast 'Starfire' "),
(@ENTRY,0,4,5,0,0,100,0,6000,10000,25000,40000,11,35251,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cast summon first minion"),
(@ENTRY,0,5,0,61,0,100,0,0,0,0,0,11,35260,0,0,0,0,0,1,0,0,0,0,0,0,0,"cast summon secont minion"),
(@ENTRY,0,6,0,0,0,100,2,6000,6000,11000,13000,11,35261,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunseeker Netherbinder - In Combat - Cast 'Arcane Nova' (Normal)");

-- Arcane Servant SAI
SET @ENTRY := 20478;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1000,1000,0,2000,11,35255,0,0,0,0,0,2,0,0,0,0,0,0,0,"cast - Arcane Volley"),
(@ENTRY,0,1,0,0,0,100,0,3000,6000,6000,12000,11,22271,0,0,0,0,0,2,0,0,0,0,0,0,0,"cast - arcane explosion");

-- Bloodwarder Slayer SAI
SET @ENTRY := 19167;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,6000,6000,12000,14000,11,13736,1,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodwarder Slayer - In Combat - Cast 'Whirlwind' (Phase 1) (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,6,10000,10000,15000,17000,11,15708,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodwarder Slayer - In Combat - Cast 'Mortal Strike' (Phase 1) (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,6,3000,3000,18000,20000,11,35189,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodwarder Slayer - In Combat - Cast 'Solar Strike' (Phase 1) (No Repeat)"),
(@ENTRY,0,3,0,0,0,100,6,1000,10000,17000,20000,11,35231,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodwarder Slayer - In Combat - Cast 'Melt Armor' ");

-- Mechanar Wrecker SAI
SET @ENTRY := 19713;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,6000,6000,18000,20000,11,35049,0,0,0,0,0,5,0,0,0,0,0,0,0,"Mechanar Wrecker - In Combat - Cast 'Pound' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,3000,7000,10000,15000,11,35056,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mechanar Wrecker - cast Glob of Machine Fluid (normal)"),
(@ENTRY,0,2,0,0,0,100,0,3000,7000,10000,15000,11,38923,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mechanar Wrecker - cast Glob of Machine Fluid (Heroicl)");
