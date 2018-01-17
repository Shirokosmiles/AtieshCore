-- The Black Knight's Orders https://dbwotlk.com/?quest=13663
UPDATE `smart_scripts` SET `target_type` = 23 WHERE `entryorguid` = 33519 and `id` = 1;

-- A Rough Ride https://dbwotlk.com/?quest=12536
UPDATE `smart_scripts` SET `target_type` = 23 WHERE `entryorguid` = 28308 and `id` = 2;

-- Disrupt Their Reinforcements https://dbwotlk.com/?quest=13133
DELETE FROM conditions WHERE SourceTypeOrReferenceId=13 AND SourceEntry=34387;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId) VALUES
(13, 2, 34387, 0, 0, 31, 0, 3, 19717, 0, 0, 0, 0),
(13, 2, 34387, 0, 1, 31, 0, 3, 19652, 0, 0, 0, 0);
