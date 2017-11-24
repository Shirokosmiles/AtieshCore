DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_illidan_find_target');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (41081, 'spell_illidan_find_target');

UPDATE `gameobject_template` SET `ScriptName` = '' WHERE (`entry`='194675');