DELETE FROM `smart_scripts` WHERE `entryorguid`=28379;
UPDATE `creature_template` SET `AIName` = '' WHERE (entry = 28379);
UPDATE `creature_template` SET `ScriptName` = 'npc_mammoth' WHERE (entry = 28379);