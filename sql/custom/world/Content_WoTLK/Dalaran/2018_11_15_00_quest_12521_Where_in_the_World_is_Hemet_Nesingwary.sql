DELETE FROM `smart_scripts` WHERE `entryorguid`=28160;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2816000;
UPDATE `creature_template` SET `AIName` = '' WHERE (entry = 28160);
UPDATE `creature_template` SET `ScriptName` = 'npc_archimage_Pentarus' WHERE (entry = 28160);

DELETE FROM `smart_scripts` WHERE `entryorguid`=28192;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2819200;
UPDATE `creature_template` SET `AIName` = '' WHERE (entry = 28192);
UPDATE `creature_template` SET `ScriptName` = 'npc_archimage_flying_machine' WHERE (entry = 28192);

DELETE FROM `waypoint_data` WHERE `id`=28192;
DELETE FROM `waypoints` WHERE `entry`=28192;