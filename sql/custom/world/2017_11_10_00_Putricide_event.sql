UPDATE `creature_template` SET `ScriptName`='npc_flesh_eating_insect' WHERE  `entry`=37782;
UPDATE `creature_template` SET `ScriptName`='npc_putricide_trap' WHERE  `entry`=38879;
DELETE FROM `spell_script_names` where `spell_id` IN (70484,70485,70475);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(70484, 'spell_icc_summon_plagued_insect'),
(70475, 'spell_icc_giant_swarm');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry`= 70485;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorType`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13,1,70485,0,0,31,0,3,38879,0,0,0,0,'','Leap to a Random Location (to event npc)'),
(13,1,70485,0,1,31,0,4,0,0,0,0,0,'','Leap to a Random Location (to player)');

DELETE FROM `areatrigger_scripts` WHERE `entry` = 5647;
INSERT INTO `areatrigger_scripts` (`entry`,`ScriptName`) VALUES
(5647,'at_icc_start_putricide_pre_event');