-- Disrupt Their Reinforcements https://dbwotlk.com/?quest=13133
DELETE FROM conditions WHERE SourceTypeOrReferenceId=13 AND SourceEntry=34387;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId) VALUES
(13, 2, 34387, 0, 0, 31, 0, 3, 19717, 0, 0, 0, 0),
(13, 2, 34387, 0, 1, 31, 0, 3, 19652, 0, 0, 0, 0);
