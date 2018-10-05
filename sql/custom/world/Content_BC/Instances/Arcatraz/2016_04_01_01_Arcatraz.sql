-- Table smart_scripts
DELETE FROM smart_scripts WHERE (source_type = 0 AND entryorguid = 20859);
INSERT INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, event_param5, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_param1, target_param2, target_param3, target_param4, target_x, target_y, target_z, target_o, comment) VALUES
(20859, 0, 0, 1, 1, 0, 100, 1, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Out of Combat - Disable Combat Movement (No Repeat)'),
(20859, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Out of Combat - Stop Attacking (No Repeat)'),
(20859, 0, 2, 3, 4, 0, 100, 0, 0, 0, 0, 0, 0, 11, 15620, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - On Aggro - Cast \'Shoot\''),
(20859, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - On Aggro - Increment Phase'),
(20859, 0, 4, 5, 9, 0, 100, 0, 5, 30, 2300, 5000, 0, 11, 15620, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 5-30 Range - Cast \'Shoot\''),
(20859, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 5-30 Range - Set Sheath Ranged'),
(20859, 0, 6, 7, 4, 0, 100, 0, 0, 0, 0, 0, 0, 11, 22907, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - On Aggro - Cast \'Shoot\''),
(20859, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - On Aggro - Increment Phase'),
(20859, 0, 8, 9, 9, 0, 100, 0, 5, 30, 2300, 5000, 0, 11, 22907, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 5-30 Range - Cast \'Shoot\''),
(20859, 0, 9, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 5-30 Range - Set Sheath Ranged'),
(20859, 0, 10, 11, 9, 0, 100, 1, 25, 80, 0, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 25-80 Range - Enable Combat Movement (No Repeat)'),
(20859, 0, 11, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 25-80 Range - Start Attacking (No Repeat)'),
(20859, 0, 12, 13, 9, 0, 100, 1, 0, 5, 0, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 0-5 Range - Enable Combat Movement (No Repeat)'),
(20859, 0, 13, 14, 61, 0, 100, 0, 0, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 0-5 Range - Set Sheath Melee (No Repeat)'),
(20859, 0, 14, 25, 61, 0, 100, 0, 0, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 0-5 Range - Start Attacking (No Repeat)'),
(20859, 0, 15, 16, 9, 0, 100, 1, 5, 15, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 5-15 Range - Disable Combat Movement (No Repeat)'),
(20859, 0, 16, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 5-15 Range - Stop Attacking (No Repeat)'),
(20859, 0, 21, 22, 9, 0, 100, 0, 5, 30, 5000, 8000, 0, 11, 36609, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 5-30 Range - Cast \'Arcane Shot\''),
(20859, 0, 22, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 40, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 5-30 Range - Set Sheath Ranged'),
(20859, 0, 23, 0, 7, 0, 100, 0, 0, 0, 0, 0, 0, 40, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - On Evade - Set Sheath Melee'),
(20859, 0, 24, 22, 9, 0, 100, 0, 5, 30, 5000, 8000, 0, 11, 38807, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 5-30 Range - Cast \'Arcane Shot\''),
(20859, 0, 25, 26, 61, 0, 100, 1, 0, 0, 0, 0, 0, 11, 35963, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 0-5 Range - Cast \'Improved Wing Clip\' (No Repeat)'),
(20859, 0, 26, 27, 61, 0, 100, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 0-5 Range - Disable Combat Movement (No Repeat)'),
(20859, 0, 27, 5, 61, 0, 100, 0, 0, 0, 0, 0, 0, 89, 15, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Arcatraz Warder - Within 0-5 Range - Start Random Movement (No Repeat)');

-- Arcatraz Defender SAI
SET @ENTRY := 20857;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,1000,5000,15000,20000,11,36638,0,0,0,0,0,2,0,0,0,0,0,0,0,"inner fire (normal)"),
(@ENTRY,0,1,0,0,0,100,4,1000,6000,10000,15000,11,38812,0,0,0,0,0,2,0,0,0,0,0,0,0,"blood"),
(@ENTRY,0,2,0,0,0,100,4,1000,5000,15000,20000,11,38806,0,0,0,0,0,2,0,0,0,0,0,0,0,"inner fire (heroicl)");

-- Protean Nightmare SAI
SET @ENTRY := 20864;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1000,10000,10000,20000,11,36622,0,0,0,0,0,2,0,0,0,0,0,0,0,"poison 1"),
(@ENTRY,0,1,0,0,0,100,2,1000,3000,4000,10000,11,36617,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gaping Maw (normal)"),
(@ENTRY,0,2,0,0,0,100,2,1000,3000,4000,10000,11,38810,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gaping Maw (heroic)"),
(@ENTRY,0,3,0,0,0,100,2,1000,5000,10000,15000,11,36619,0,0,0,0,0,2,0,0,0,0,0,0,0,"Infectious Poison(normal)"),
(@ENTRY,0,4,0,0,0,100,2,1000,5000,10000,15000,11,38811,0,0,0,0,0,2,0,0,0,0,0,0,0,"Infectious Poison(heroic)");

-- Arcatraz Sentinel SAI
SET @ENTRY := 20869;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,1000,1000,1000,1500,11,36716,0,0,0,0,0,5,0,0,0,0,0,0,0,"Arcatraz Sentinel - Energy Discharge"),
(@ENTRY,0,1,0,0,0,100,4,1000,1000,1000,1500,11,38828,0,0,0,0,0,5,0,0,0,0,0,0,0,"Arcatraz Sentinel - Energy Discharge heroic"),
(@ENTRY,0,2,0,2,0,100,3,0,50,0,0,11,36719,0,0,0,0,0,1,0,0,0,0,0,0,0,"Arcatraz Sentinel - Explode normal"),
(@ENTRY,0,3,0,2,0,100,5,0,50,0,0,11,38830,0,0,0,0,0,1,0,0,0,0,0,0,0,"Arcatraz Sentinel - Explode heroic");

-- Negaton Warp-Master SAI
SET @ENTRY := 20873;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1000,2000,10000,15000,11,36813,0,0,0,0,0,8,0,0,0,0,0,0,0,"Negaton Warp-Master - cast Summon Negaton Field");

-- Eredar Deathbringer SAI
SET @ENTRY := 20880;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,37,0,100,2,0,0,0,0,11,27987,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eredar Deathbringer - castUnholy Aura - normal"),
(@ENTRY,0,1,0,37,0,100,4,0,0,0,0,11,38844,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eredar Deathbringer - castUnholy Aura - heroic"),
(@ENTRY,0,2,0,0,0,100,2,1000,1000,3000,7000,11,36789,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eredar Deathbringer - castDiminish Soul - normal"),
(@ENTRY,0,3,0,0,0,100,4,1000,1000,3000,7000,11,38848,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eredar Deathbringer - castDiminish Soul - heroic"),
(@ENTRY,0,4,0,0,0,100,2,1000,3000,3000,10000,11,36787,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eredar Deathbringer - castForceful Cleavel - normal"),
(@ENTRY,0,5,0,0,0,100,4,1000,3000,3000,10000,11,38846,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eredar Deathbringer - castForceful Cleavel - heroic");

-- Eredar Soul-Eater SAI
SET @ENTRY := 20879;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,37,0,100,0,0,0,0,0,11,36784,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eredar Soul-Eater - aura"),
(@ENTRY,0,1,0,0,0,100,2,3000,10000,10000,20000,11,36786,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eredar soul-eater - Soul Chill normal"),
(@ENTRY,0,3,0,0,0,100,4,3000,10000,10000,20000,11,38843,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eredar soul-eater - Soul Chill heroic"),
(@ENTRY,0,4,0,0,0,100,0,5000,12000,15000,25000,11,36778,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eredar soul-eater - Soul Stea");

-- Spiteful Temptress SAI
SET @ENTRY := 20883;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,8000,18000,25000,11,36866,0,0,0,0,0,5,0,0,0,0,0,0,0,"Spiteful Temptress - Domination"),
(@ENTRY,0,1,0,0,0,100,2,1000,3000,1500,3000,11,36866,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spiteful Temptress - Shadow Bolt normal"),
(@ENTRY,0,2,0,0,0,100,4,1000,3000,1500,3000,11,38892,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spiteful Temptress - Shadow Bolt heroic");

-- Skulking Witch SAI
SET @ENTRY := 20882;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1000,3000,8000,10000,11,36862,0,0,0,0,0,6,0,0,0,0,0,0,0,"Skulking Witch - Gouge"),
(@ENTRY,0,1,0,0,0,100,2,1000,6000,2000,6000,11,36863,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skulking Witch - Chastise normal"),
(@ENTRY,0,2,0,0,0,100,4,1000,6000,2000,6000,11,38851,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skulking Witch - Chastise heroic"),
(@ENTRY,0,3,0,0,0,100,4,1000,5000,1000,5000,11,38852,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skulking Witch - lash of pain heroic"),
(@ENTRY,0,4,0,0,0,100,2,1000,5000,1000,5000,11,36864,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skulking Witch - lash of pain normal");

-- Unchained Doombringer SAI
SET @ENTRY := 20900;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,4000,6000,50000,60000,11,36836,1,0,0,0,0,2,0,0,0,0,0,0,0,"Unchained Doombringer - In Combat - Cast 'Agonizing Armor' (Phase 1) (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,6,10000,13000,25000,30000,11,36833,1,0,0,0,0,6,0,0,0,0,0,0,0,"Unchained Doombringer - In Combat - Cast 'Berserker Charge' (Phase 1) (No Repeat)"),
(@ENTRY,0,2,0,0,0,100,2,7000,10000,25000,30000,11,36835,1,0,0,0,0,1,0,0,0,0,0,0,0,"Unchained Doombringer - In Combat - Cast 'War Stomp' (Phase 1) (No Repeat)"),
(@ENTRY,0,3,0,0,0,100,4,7000,10000,25000,30000,11,38911,1,0,0,0,0,1,0,0,0,0,0,0,0,"Unchained Doombringer - In Combat - Cast 'War Stomp' (Phase 1) (No Repeat)");

-- Gargantuan Abyssal SAI
SET @ENTRY := 20898;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,2,0,0,0,0,11,38855,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gargantuan Abyssal - fire shield normal"),
(@ENTRY,0,1,0,0,0,100,2,1000,10000,10000,15000,11,36837,0,0,0,0,0,5,0,0,0,0,0,0,0,"Gargantuan Abyssal - meteor normal"),
(@ENTRY,0,2,0,4,0,100,4,0,0,0,0,11,38901,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gargantuan Abyssal - fire shield heroic"),
(@ENTRY,0,3,0,0,0,100,4,1000,10000,10000,15000,11,38903,0,0,0,0,0,5,0,0,0,0,0,0,0,"Gargantuan Abyssal - meteor heroic");
