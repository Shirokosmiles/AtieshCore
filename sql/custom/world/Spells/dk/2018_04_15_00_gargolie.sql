DELETE FROM `creature_template_movement` where `CreatureId` IN (27829);
INSERT INTO `creature_template_movement`(`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Chase`, `Random`) VALUES 
(27829, 1, 1, 2, 0, 0, 0);

DELETE FROM `spell_script_names` where `spell_id` IN (49206);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(49206, 'spell_dk_summon_gargoyle');