-- Float Type 
DELETE FROM `world_config` WHERE (OptionName = 'Visibility.Distance.BGArenas');
INSERT INTO `world_config`(`OptionName`, `Type`, `IDInTypeGroup`, `DefaultValue`, `CustomValue`, `Description`) VALUES
('Visibility.Distance.BG', 'float', 22, '533', NULL, 'Max limited by grid size: 533.33333'),
('Visibility.Distance.Arenas', 'float', 23, '533', NULL, 'Max limited by grid size: 533.33333');

-- INT Type 
SET SQL_SAFE_UPDATES = 0;
UPDATE world_config SET IDInTypeGroup = IDInTypeGroup + 1 WHERE IDInTypeGroup > 186 AND Type = 'int';
SET SQL_SAFE_UPDATES = 1;

DELETE FROM `world_config` WHERE (OptionName = 'Visibility.Notify.Period.InBGArenas');
INSERT INTO `world_config`(`OptionName`, `Type`, `IDInTypeGroup`, `DefaultValue`, `CustomValue`, `Description`) VALUES
('Visibility.Notify.Period.InBG', 'int', 186, '1000', NULL, 'Time (in milliseconds) for visibility update period. Lower values may have performance impact.'),
('Visibility.Notify.Period.InArenas', 'int', 187, '1000', NULL, 'Time (in milliseconds) for visibility update period. Lower values may have performance impact.');
