DELETE FROM `smart_scripts` WHERE `entryorguid`=27430;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2743000;
UPDATE `creature_template` SET `ScriptName` = 'npc_destructive_ward_kill' WHERE (entry = 27430);
UPDATE `creature_template` SET `AIName` = '' WHERE (entry = 27430);