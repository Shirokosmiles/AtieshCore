DELETE FROM `smart_scripts` WHERE `entryorguid`=28202;
UPDATE `creature_template` SET `AIName` = '' WHERE (entry = 28202);
UPDATE `creature_template` SET `ScriptName` = 'npc_body_rabbit' WHERE (entry = 28202);

DELETE FROM `smart_scripts` WHERE `entryorguid`=28203;
UPDATE `creature_template` SET `AIName` = '' WHERE (entry = 28203);
UPDATE `creature_template` SET `ScriptName` = 'npc_body_basilisk' WHERE (entry = 28203);