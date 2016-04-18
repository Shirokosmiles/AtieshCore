-- Tempest-Forge Peacekeeper SAI
SET @ENTRY := 18405;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,90,6,0,0,17800,21200,11,34785,0,0,0,0,0,5,0,0,0,0,0,0,0,"Tempest-Forge Peacekeeper - In Combat - Cast 'Arcane Volley' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,6,5000,7100,7600,14500,11,34791,0,0,0,0,0,1,0,0,0,0,0,0,0,"Tempest-Forge Peacekeeper - In Combat - Cast 'Arcane Explosion' (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,2,10000,20000,10000,30000,11,34793,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tempest-Forge Peacekeeper - Arcane Blast");

-- Bloodwarder Falconer SAI
SET @ENTRY := 17994;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,3200,3200,20000,25000,11,34852,0,0,0,0,0,5,0,0,0,0,0,0,0,"Bloodwarder Falconer - In Combat - Cast 'Call of the Falcon' (No Repeat) (Dungeon)"),
(@ENTRY,0,1,0,0,0,100,0,0,15000,3000,20000,11,34879,0,0,0,0,0,6,0,0,0,0,0,0,0,"Bloodwarder Falconer - Multi-Shot"),
(@ENTRY,0,2,0,2,0,100,2,30,60,15000,30000,11,31567,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodwarder Falconer - Detterence (Normal dungeon)");

-- Greater Frayer SAI
SET @ENTRY := 19557;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,10000,5000,15000,11,34644,0,0,0,0,0,2,0,0,0,0,0,0,0,"Greater Frayer - Lash");

-- Sunseeker Researcher SAI
SET @ENTRY := 18421;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,6,1000,1000,60000,60000,11,34355,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunseeker Researcher - On aggro - Cast 'Poison Shield' (No Repeat)"),
(@ENTRY,0,1,0,0,0,70,6,2000,2000,10000,14000,11,34352,0,0,0,0,0,5,0,0,0,0,0,0,0,"Sunseeker Researcher - In Combat - Cast 'Mind Shock' (No Repeat)"),
(@ENTRY,0,2,0,0,0,70,6,5000,5000,10000,14000,11,34353,0,0,0,0,0,5,0,0,0,0,0,0,0,"Sunseeker Researcher - In Combat - Cast 'Frost Shock' (No Repeat)"),
(@ENTRY,0,3,0,0,0,70,6,8000,8000,10000,14000,11,34354,0,0,0,0,0,5,0,0,0,0,0,0,0,"Sunseeker Researcher - In Combat - Cast 'Flame Shock' (No Repeat)"),
(@ENTRY,0,4,0,0,0,100,0,1000,10000,5000,30000,11,16427,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sunseeker Researcher - In Combat - Cast Virulent Poison'");

-- Sunseeker Botanist SAI
SET @ENTRY := 18422;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,2,0,2,0,100,0,0,70,6000,15000,11,34254,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunseeker Botanist - Between 0-60% Health - Cast 'Regrowth (for all dungeon) "),
(@ENTRY,0,3,0,0,0,40,0,6000,20000,15000,30000,11,34350,0,0,0,0,0,9,19557,0,15,0,0,0,0,"Sunseeker Botanist - natural enrage for Big tree"),
(@ENTRY,0,4,0,0,0,100,0,3000,10000,10000,20000,11,18587,0,0,0,0,0,9,19557,0,15,0,0,0,0,"Sunseeker Botanist - natural enrage for Low tree"),
(@ENTRY,0,5,0,2,0,100,2,0,60,7000,20000,11,34361,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunseeker Botanist - Between 0-60% Regrowth (Normal)"),
(@ENTRY,0,6,0,2,0,100,4,0,60,7000,20000,11,39125,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunseeker Botanist - Between 0-60% Regrowth (Heroicl)"),
(@ENTRY,0,7,0,2,0,100,5,0,60,0,0,11,39126,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunseeker Botanist - Between 0-60% Additional Regrowth (Heroicl)");

-- Mutate Fleshlasher SAI
SET @ENTRY := 19598;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,15000,5000,15000,11,34351,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mutate Fleshlasher - Vicious Bite");
