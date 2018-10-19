-- Quest Loyal Companions (12865)
DELETE FROM `conditions` WHERE `SourceEntry`=56393 AND `SourceTypeOrReferenceId` IN (13, 17);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 56393, 0, 0, 31, 0, 3, 29854, 0, 0, 0, 0, '', NULL),
(13, 1, 56393, 0, 0, 1, 0, 56393, 0, 0, 1, 0, 0, '', NULL),
(17, 0, 56393, 0, 0, 29, 0, 29854, 40, 0, 0, 0, 0, '', NULL);

UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName`='' WHERE `entry`=29854; -- Stormcrest Eagle

DELETE FROM `smart_scripts` WHERE `entryorguid`=29854 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(29854, 0, 0, 0, 8, 0, 100, 0, 0, 0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormcrest Eagle - Spellhit - Death'),
(29854, 0, 1, 0, 6, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormcrest Eagle - Death - Despawn');