UPDATE creature_template SET `ScriptName`="npc_pet_dk_rune_weapon" WHERE entry=27893;

DELETE FROM `spell_script_names` where `spell_id` IN (49028);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(49028, 'spell_dk_dancing_rune_weapon');