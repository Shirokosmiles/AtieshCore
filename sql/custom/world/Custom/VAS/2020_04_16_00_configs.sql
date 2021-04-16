DELETE FROM `world_config` WHERE `Type` = 'rate' AND `IDInTypeGroup` = 70;
DELETE FROM `world_config` WHERE `Type` = 'rate' AND `IDInTypeGroup` = 71;
DELETE FROM `world_config` WHERE `Type` = 'rate' AND `IDInTypeGroup` = 72;
DELETE FROM `world_config` WHERE `Type` = 'rate' AND `IDInTypeGroup` = 73;

INSERT INTO `world_config`(`OptionName`, `Type`, `IDInTypeGroup`, `DefaultValue`, `CustomValue`, `Description`) VALUES 
('VAS.Creature.InZone.Damage', 'rate', 70, '1', NULL, 'Change HP and Damage value for Units in Dungeons in % #Default: 100 - (full HP and Damage) 10 - (units have only 10% of HP or can deal damage 10% of base damage value)'),
('VAS.Creature.InZone.SpellDamage', 'rate', 71, '1', NULL, 'Change HP and Damage value for Units in Dungeons in % #Default: 100 - (full HP and Damage) 10 - (units have only 10% of HP or can deal damage 10% of base damage value)'),
('VAS.Creature.InZone.Health', 'rate', 72, '1', NULL, 'Change HP and Damage value for Units in Dungeons in % #Default: 100 - (full HP and Damage) 10 - (units have only 10% of HP or can deal damage 10% of base damage value)');
