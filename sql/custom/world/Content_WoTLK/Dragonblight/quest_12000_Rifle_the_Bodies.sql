DELETE FROM `smart_scripts` WHERE `entryorguid`=26477;
UPDATE `creature_template` SET `AIName` = '' WHERE (entry = 26477);
UPDATE `creature_template` SET `ScriptName` = 'npc_body_magehunter' WHERE (entry = 26477);