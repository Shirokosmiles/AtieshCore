UPDATE `creature_template_movement` SET `Flight` = 1 WHERE `CreatureID` = 27829;

DELETE FROM `spell_script_names` where `spell_id` IN (49206);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(49206, 'spell_dk_summon_gargoyle');