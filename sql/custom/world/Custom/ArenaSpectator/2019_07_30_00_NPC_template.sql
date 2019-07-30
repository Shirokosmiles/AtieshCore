-- Arena Spectator
-- NPC
DELETE FROM `creature_template` WHERE (entry = 190040);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`,
 `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`,
 `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`,
 `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, 
 `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, 
 `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(190040, 0, 0, 0, 0, 0, 19646, 0, 0, 0, 'Наблюдатель арен', NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 1.14286, 1, 0, 0, 2000, 0, 1, 1, 1, 0, 0, 0, 0, 7, 138936390, 0, 0, 0, 0, 0, 0, 0, '',3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 'npc_arena_spectator', 0);
