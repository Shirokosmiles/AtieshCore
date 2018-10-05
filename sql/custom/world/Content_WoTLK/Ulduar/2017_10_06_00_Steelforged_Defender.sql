-- converted to creatureAI scripts

DELETE FROM `smart_scripts` WHERE (source_type = 0 AND entryorguid = 33236);
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_steelforged_defender' WHERE (entry = 33236);