DELETE FROM `spell_group_stack_rules` where `group_id` IN (1199);
INSERT INTO `spell_group_stack_rules` (`group_id`, `stack_rule`) VALUES ('1199', '1');

DELETE FROM `spell_group` where `id` IN (1199);
INSERT INTO `spell_group` (`id`, `spell_id`) VALUES ('1199', '47930');
