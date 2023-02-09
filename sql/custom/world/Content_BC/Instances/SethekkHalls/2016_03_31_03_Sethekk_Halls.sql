-- Time-Lost Controller SAI
SET @ENTRY := 18327;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,10000,20000,30000,11,32764,0,0,0,0,0,1,0,0,0,0,0,0,0,"Time-Lost Controller - totem"),
(@ENTRY,0,1,0,0,0,100,0,0,10000,15000,30000,11,35013,0,0,0,0,0,5,0,0,0,0,0,0,0,"Time-Lost Controller - shrink");

-- Charming Totem SAI
SET @ENTRY := 20343;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,37,0,100,0,0,0,5000,10000,11,35120,0,0,0,0,0,25,0,0,0,0,0,0,0,"charming totem - Charm");

-- Sethekk Shaman SAI
SET @ENTRY := 18326;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,13,0,100,2,8000,8000,0,0,11,15501,0,0,0,0,0,5,0,0,0,0,0,0,0,"Sethekk Shaman - Target Casting - Cast 'Earth Shock'  (Normal Dungeon)"),
(@ENTRY,0,1,0,13,0,100,4,8000,8000,0,0,11,22885,0,0,0,0,0,5,0,0,0,0,0,0,0,"Sethekk Shaman - Target Casting - Cast 'Earth Shock'  (Heroic Dungeon)"),
(@ENTRY,0,2,0,4,0,100,7,0,0,0,0,11,32663,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sethekk Shaman - On Aggro - Cast 'Summon Dark Vortex' (No Repeat) (Heroic Dungeon)");

-- Dark Vortex SAI
SET @ENTRY := 18701;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,7,0,0,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dark Vortex - Out of Combat - Disable Combat Movement (No Repeat)"),
(@ENTRY,0,1,2,4,0,100,7,0,0,0,0,11,12471,0,0,0,0,0,25,0,0,0,0,0,0,0,"Dark Vortex - On Aggro - Cast 'Shadow Bolt' (No Repeat) (Dungeon)"),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dark Vortex - On Aggro - Increment Phase By 1 (No Repeat) (Dungeon)"),
(@ENTRY,0,3,0,9,1,100,6,0,40,2400,3800,11,12471,0,0,0,0,0,5,0,0,0,0,0,0,0,"Dark Vortex - Within 0-40 Range - Cast 'Shadow Bolt' (No Repeat) (Dungeon)"),
(@ENTRY,0,4,5,3,1,100,7,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dark Vortex - Between 0-15% Mana - Enable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,5,0,61,1,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dark Vortex - Between 0-15% Mana - Increment Phase By 1 (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,6,0,9,1,100,7,35,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dark Vortex - Within 35-80 Range - Enable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,7,0,9,1,100,7,5,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dark Vortex - Within 5-15 Range - Disable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,8,0,9,1,100,7,0,5,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dark Vortex - Within 0-5 Range - Enable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,0,9,0,3,0,100,6,30,100,100,100,23,0,1,0,0,0,0,1,0,0,0,0,0,0,0,"Dark Vortex - Between 30-100% Mana - Decrement Phase By 1 (Phase 1) (No Repeat) (Dungeon)");
