-- Pet Scaling
DELETE FROM `spell_script_names` WHERE `spell_id` IN ('34902', '34903', '34904', '61017');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('34902', 'spell_hun_pet_scaling'),
('34903', 'spell_hun_pet_scaling'),
('34904', 'spell_hun_pet_scaling'),
('61017', 'spell_hun_pet_scaling');

-- Pet Scaling
DELETE FROM spell_script_names WHERE spell_id IN(35661, 35662, 35663, 35664, -35661, -35662, -35663, -35664);
INSERT INTO spell_script_names VALUES (35661, 'spell_pri_pet_scaling');
INSERT INTO spell_script_names VALUES (35662, 'spell_pri_pet_scaling');
INSERT INTO spell_script_names VALUES (35663, 'spell_pri_pet_scaling');
INSERT INTO spell_script_names VALUES (35664, 'spell_pri_pet_scaling');