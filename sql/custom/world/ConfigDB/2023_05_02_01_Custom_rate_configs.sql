DELETE FROM `world_custom_config` WHERE `Type` = 'rate' AND `IDInTypeGroup` between 0 and 7;
INSERT INTO `world_custom_config`(`OptionName`, `Type`, `IDInTypeGroup`, `DefaultValue`, `CustomValue`, `Description`) VALUES 
-- AT configs
('Rate.XP.Kill.Premium', 'rate', 0, '1', NULL, 'Individual rate for vip player'),
('Rate.XP.Quest.Premium', 'rate', 1, '1', NULL, 'Individual rate for vip player'),
('Rate.Honor.Premium', 'rate', 2, '1', NULL, 'Individual rate for vip player'),
('Rate.Reputation.Gain.Premium', 'rate', 3, '1', NULL, 'Individual rate for vip player'),
('GSystem.GuildLevel.Rate.XP.Bonus', 'rate', 4, '2', NULL, 'Rate for character experience when guild >= 2 level'),
('VAS.Creature.InZone.Damage', 'rate', 5, '1', NULL, 'Change HP and Damage value for Units in Dungeons in % #Default: 100 - (full HP and Damage) 10 - (units have only 10% of HP or can deal damage 10% of base damage value)'),
('VAS.Creature.InZone.SpellDamage', 'rate', 6, '1', NULL, 'Change HP and Damage value for Units in Dungeons in % #Default: 100 - (full HP and Damage) 10 - (units have only 10% of HP or can deal damage 10% of base damage value)'),
('VAS.Creature.InZone.Health', 'rate', 7, '1', NULL, 'Change HP and Damage value for Units in Dungeons in % #Default: 100 - (full HP and Damage) 10 - (units have only 10% of HP or can deal damage 10% of base damage value)');
