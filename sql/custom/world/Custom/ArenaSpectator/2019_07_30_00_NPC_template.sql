-- Arena Spectator
-- NPC
DELETE FROM `creature_template` WHERE (entry = 190040);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`,
 `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`,
 `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`,
 `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, 
 `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, 
 `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(190040, 0, 0, 0, 0, 0, 19646, 0, 0, 0, 'Arena spectator', NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 1.14286, 1, 0, 0, 2000, 0, 1, 1, 1, 0, 0, 0, 0, 7, 138936390, 0, 0, 0, 0, 0, 0, 0, '',0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'npc_arena_spectator', 0);

DELETE FROM `creature_template_locale` WHERE `entry` IN (190040);
INSERT INTO `creature_template_locale`(`entry`, `locale`, `Name`, `Title`, `VerifiedBuild`) VALUES 
(190040, 'ruRU', 'Наблюдатель арен', 'Мастер наблюдений', 0);

DELETE FROM `creature_template_movement` where `CreatureId` IN (190040);
INSERT INTO `creature_template_movement`(`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Chase`, `Random`) VALUES 
(190040, 1, 1, 0, 0, 0, 1);

DELETE FROM `creature` WHERE `guid` IN (310000, 310001, 310002, 310003, 310004, 310005);
INSERT INTO `creature`(`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES 
(310000, 190040, 0, 0, 0, 1, 1, 0, 0, -9133.92, 395.389, 91.4308, 5.41645, 300, 0, 0, 12600, 0, 0, 0, 0, 0, '', 0),
(310001, 190040, 1, 0, 0, 1, 1, 0, 0, 1336.83, -4394.09, 28.3689, 1.7508, 300, 0, 0, 12600, 0, 0, 0, 0, 0, '', 0),
(310002, 18895, 0, 0, 0, 1, 1, 0, 0, -9119.36, 412.506, 93.9425, 4.94287, 300, 0, 0, 349300, 0, 0, 0, 0, 0, '', 0),
(310003, 18895, 1, 0, 0, 1, 1, 0, 0, 1327.99, -4364.52, 28.0399, 4.82074, 300, 0, 0, 349300, 0, 0, 0, 0, 0, '', 0),
(310004, 18897, 0, 0, 0, 1, 1, 0, 1, -9115.43, 414.441, 93.9319, 5.20204, 300, 0, 0, 6986, 0, 0, 0, 0, 0, '', 0),
(310005, 18897, 1, 0, 0, 1, 1, 0, 1, 1331.4, -4362.85, 28.5736, 5.54724, 300, 0, 0, 6986, 0, 0, 0, 0, 0, '', 0);