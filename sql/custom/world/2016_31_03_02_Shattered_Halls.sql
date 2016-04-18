-- Shattered Hand Legionnaire SAI
SET @ENTRY := 16700;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,11,30472,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shattered Hand Legionnaire - Aura"),
(@ENTRY,0,1,0,2,0,100,0,20,50,10000,20000,11,30485,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shattered Hand Legionnaire - Enrage"),
(@ENTRY,0,2,0,13,0,100,0,10000,20000,0,0,11,15615,0,0,0,0,0,5,0,0,0,0,0,0,0,"Shattered Hand Legionnaire - Pummel");
