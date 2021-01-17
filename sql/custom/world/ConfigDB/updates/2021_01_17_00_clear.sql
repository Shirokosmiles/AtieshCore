DELETE FROM `world_config` WHERE (OptionName = 'UI.ShowQuestLevelsInDialogs_DELETED');

SET SQL_SAFE_UPDATES = 0;
UPDATE world_config SET IDInTypeGroup = IDInTypeGroup - 1 WHERE IDInTypeGroup > 67 AND Type = 'bool';
SET SQL_SAFE_UPDATES = 1;