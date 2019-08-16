-- FULL `creature_template` of entry 190016
DELETE FROM `creature_template` where `entry` =190016;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(190016, 19646, 0, "Enchants-Gems", NULL, NULL, 0, 80, 80, 2, 35, 1, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, 'npc_enchantment');

-- vendors with gems
DELETE FROM `creature_template` where `entry` =400000;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400000, 19646, 0, "Meta gems", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
-- FULL `npc_vendor` of entry 400000 META
DELETE FROM `npc_vendor` WHERE (entry = 400000);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400000, 0, 41285, 0, 0, 0, 0),
(400000, 0, 41307, 0, 0, 0, 0),
(400000, 0, 41333, 0, 0, 0, 0),
(400000, 0, 41335, 0, 0, 0, 0),
(400000, 0, 41339, 0, 0, 0, 0),
(400000, 0, 41375, 0, 0, 0, 0),
(400000, 0, 41376, 0, 0, 0, 0),
(400000, 0, 41377, 0, 0, 0, 0),
(400000, 0, 41378, 0, 0, 0, 0),
(400000, 0, 41379, 0, 0, 0, 0),
(400000, 0, 41380, 0, 0, 0, 0),
(400000, 0, 41381, 0, 0, 0, 0),
(400000, 0, 41382, 0, 0, 0, 0),
(400000, 0, 41385, 0, 0, 0, 0),
(400000, 0, 41389, 0, 0, 0, 0),
(400000, 0, 41395, 0, 0, 0, 0),
(400000, 0, 41396, 0, 0, 0, 0),
(400000, 0, 41397, 0, 0, 0, 0),
(400000, 0, 41398, 0, 0, 0, 0),
(400000, 0, 41400, 0, 0, 0, 0),
(400000, 0, 41401, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400001 YELLOW
DELETE FROM `creature_template` where `entry` =400001;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400001, 19646, 0, "Yellow gems", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400001);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400001, 0, 40123, 0, 0, 0, 0),
(400001, 0, 40124, 0, 0, 0, 0),
(400001, 0, 40125, 0, 0, 0, 0),
(400001, 0, 40126, 0, 0, 0, 0),
(400001, 0, 40127, 0, 0, 0, 0),
(400001, 0, 40128, 0, 0, 0, 0),
(400001, 0, 42148, 0, 0, 0, 0),
(400001, 0, 42149, 0, 0, 0, 0),
(400001, 0, 42150, 0, 0, 0, 0),
(400001, 0, 42156, 0, 0, 0, 0),
(400001, 0, 42157, 0, 0, 0, 0),
(400001, 0, 42158, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400002 RED
DELETE FROM `creature_template` where `entry` =400002;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400002, 19646, 0, "Red gems", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400002);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400002, 0, 36766, 0, 0, 0, 0),
(400002, 0, 40111, 0, 0, 0, 0),
(400002, 0, 40112, 0, 0, 0, 0),
(400002, 0, 40113, 0, 0, 0, 0),
(400002, 0, 40114, 0, 0, 0, 0),
(400002, 0, 40115, 0, 0, 0, 0),
(400002, 0, 40116, 0, 0, 0, 0),
(400002, 0, 40117, 0, 0, 0, 0),
(400002, 0, 40118, 0, 0, 0, 0),
(400002, 0, 42142, 0, 0, 0, 0),
(400002, 0, 42143, 0, 0, 0, 0),
(400002, 0, 42144, 0, 0, 0, 0),
(400002, 0, 42151, 0, 0, 0, 0),
(400002, 0, 42152, 0, 0, 0, 0),
(400002, 0, 42153, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400003 BLUE
DELETE FROM `creature_template` where `entry` =400003;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400003, 19646, 0, "Blue gems", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400003);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400003, 0, 36767, 0, 0, 0, 0),
(400003, 0, 40119, 0, 0, 0, 0),
(400003, 0, 40120, 0, 0, 0, 0),
(400003, 0, 40121, 0, 0, 0, 0),
(400003, 0, 40122, 0, 0, 0, 0),
(400003, 0, 42145, 0, 0, 0, 0),
(400003, 0, 42146, 0, 0, 0, 0),
(400003, 0, 42155, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400004 PURPLE
DELETE FROM `creature_template` where `entry` =400004;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400004, 19646, 0, "Purple gems", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400004);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400004, 0, 40129, 0, 0, 0, 0),
(400004, 0, 40130, 0, 0, 0, 0),
(400004, 0, 40131, 0, 0, 0, 0),
(400004, 0, 40132, 0, 0, 0, 0),
(400004, 0, 40133, 0, 0, 0, 0),
(400004, 0, 40134, 0, 0, 0, 0),
(400004, 0, 40135, 0, 0, 0, 0),
(400004, 0, 40136, 0, 0, 0, 0),
(400004, 0, 40137, 0, 0, 0, 0),
(400004, 0, 40138, 0, 0, 0, 0),
(400004, 0, 40139, 0, 0, 0, 0),
(400004, 0, 40140, 0, 0, 0, 0),
(400004, 0, 40141, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400005 ORANGE
DELETE FROM `creature_template` where `entry` =400005;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400005, 19646, 0, "Orange gems", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400005);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400005, 0, 40142, 0, 0, 0, 0),
(400005, 0, 40143, 0, 0, 0, 0),
(400005, 0, 40144, 0, 0, 0, 0),
(400005, 0, 40145, 0, 0, 0, 0),
(400005, 0, 40146, 0, 0, 0, 0),
(400005, 0, 40147, 0, 0, 0, 0),
(400005, 0, 40148, 0, 0, 0, 0),
(400005, 0, 40149, 0, 0, 0, 0),
(400005, 0, 40150, 0, 0, 0, 0),
(400005, 0, 40151, 0, 0, 0, 0),
(400005, 0, 40152, 0, 0, 0, 0),
(400005, 0, 40153, 0, 0, 0, 0),
(400005, 0, 40154, 0, 0, 0, 0),
(400005, 0, 40155, 0, 0, 0, 0),
(400005, 0, 40156, 0, 0, 0, 0),
(400005, 0, 40157, 0, 0, 0, 0),
(400005, 0, 40158, 0, 0, 0, 0),
(400005, 0, 40159, 0, 0, 0, 0),
(400005, 0, 40160, 0, 0, 0, 0),
(400005, 0, 40161, 0, 0, 0, 0),
(400005, 0, 40162, 0, 0, 0, 0),
(400005, 0, 40163, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400006 GREEN
DELETE FROM `creature_template` where `entry` =400006;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400006, 19646, 0, "Green gems", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400006);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400006, 0, 40164, 0, 0, 0, 0),
(400006, 0, 40165, 0, 0, 0, 0),
(400006, 0, 40166, 0, 0, 0, 0),
(400006, 0, 40167, 0, 0, 0, 0),
(400006, 0, 40168, 0, 0, 0, 0),
(400006, 0, 40169, 0, 0, 0, 0),
(400006, 0, 40170, 0, 0, 0, 0),
(400006, 0, 40171, 0, 0, 0, 0),
(400006, 0, 40172, 0, 0, 0, 0),
(400006, 0, 40173, 0, 0, 0, 0),
(400006, 0, 40174, 0, 0, 0, 0),
(400006, 0, 40175, 0, 0, 0, 0),
(400006, 0, 40176, 0, 0, 0, 0),
(400006, 0, 40177, 0, 0, 0, 0),
(400006, 0, 40178, 0, 0, 0, 0),
(400006, 0, 40179, 0, 0, 0, 0),
(400006, 0, 40180, 0, 0, 0, 0),
(400006, 0, 40181, 0, 0, 0, 0),
(400006, 0, 40182, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400007 радужные
DELETE FROM `creature_template` where `entry` =400007;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400007, 19646, 0, "Rainbow gems", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400007);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400007, 0, 49110, 0, 0, 0, 0);

-- vendors with glyphs
DELETE FROM `creature_template` where `entry` =400021;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400021, 19646, 0, "Paladin glyphs", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
-- FULL `npc_vendor` of entry 400021 paladin
DELETE FROM `npc_vendor` WHERE (entry = 400021);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400021, 0, 41092, 0, 0, 0, 0),
(400021, 0, 41094, 0, 0, 0, 0),
(400021, 0, 41095, 0, 0, 0, 0),
(400021, 0, 41096, 0, 0, 0, 0),
(400021, 0, 41097, 0, 0, 0, 0),
(400021, 0, 41098, 0, 0, 0, 0),
(400021, 0, 41099, 0, 0, 0, 0),
(400021, 0, 41100, 0, 0, 0, 0),
(400021, 0, 41101, 0, 0, 0, 0),
(400021, 0, 41102, 0, 0, 0, 0),
(400021, 0, 41103, 0, 0, 0, 0),
(400021, 0, 41104, 0, 0, 0, 0),
(400021, 0, 41105, 0, 0, 0, 0),
(400021, 0, 41106, 0, 0, 0, 0),
(400021, 0, 41107, 0, 0, 0, 0),
(400021, 0, 41108, 0, 0, 0, 0),
(400021, 0, 41109, 0, 0, 0, 0),
(400021, 0, 41110, 0, 0, 0, 0),
(400021, 0, 43340, 0, 0, 0, 0),
(400021, 0, 43365, 0, 0, 0, 0),
(400021, 0, 43366, 0, 0, 0, 0),
(400021, 0, 43367, 0, 0, 0, 0),
(400021, 0, 43368, 0, 0, 0, 0),
(400021, 0, 43369, 0, 0, 0, 0),
(400021, 0, 43867, 0, 0, 0, 0),
(400021, 0, 43868, 0, 0, 0, 0),
(400021, 0, 43869, 0, 0, 0, 0),
(400021, 0, 45741, 0, 0, 0, 0),
(400021, 0, 45742, 0, 0, 0, 0),
(400021, 0, 45743, 0, 0, 0, 0),
(400021, 0, 45744, 0, 0, 0, 0),
(400021, 0, 45745, 0, 0, 0, 0),
(400021, 0, 45746, 0, 0, 0, 0),
(400021, 0, 45747, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400022 warrior
DELETE FROM `creature_template` where `entry` =400022;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400022, 19646, 0, "Warrior glyphs", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400022);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400022, 0, 43395, 0, 0, 0, 0),
(400022, 0, 43396, 0, 0, 0, 0),
(400022, 0, 43397, 0, 0, 0, 0),
(400022, 0, 43398, 0, 0, 0, 0),
(400022, 0, 43399, 0, 0, 0, 0),
(400022, 0, 43400, 0, 0, 0, 0),
(400022, 0, 43412, 0, 0, 0, 0),
(400022, 0, 43413, 0, 0, 0, 0),
(400022, 0, 43414, 0, 0, 0, 0),
(400022, 0, 43415, 0, 0, 0, 0),
(400022, 0, 43416, 0, 0, 0, 0),
(400022, 0, 43417, 0, 0, 0, 0),
(400022, 0, 43418, 0, 0, 0, 0),
(400022, 0, 43419, 0, 0, 0, 0),
(400022, 0, 43420, 0, 0, 0, 0),
(400022, 0, 43421, 0, 0, 0, 0),
(400022, 0, 43422, 0, 0, 0, 0),
(400022, 0, 43423, 0, 0, 0, 0),
(400022, 0, 43424, 0, 0, 0, 0),
(400022, 0, 43425, 0, 0, 0, 0),
(400022, 0, 43426, 0, 0, 0, 0),
(400022, 0, 43427, 0, 0, 0, 0),
(400022, 0, 43428, 0, 0, 0, 0),
(400022, 0, 43429, 0, 0, 0, 0),
(400022, 0, 43430, 0, 0, 0, 0),
(400022, 0, 43431, 0, 0, 0, 0),
(400022, 0, 43432, 0, 0, 0, 0),
(400022, 0, 45790, 0, 0, 0, 0),
(400022, 0, 45792, 0, 0, 0, 0),
(400022, 0, 45793, 0, 0, 0, 0),
(400022, 0, 45794, 0, 0, 0, 0),
(400022, 0, 45795, 0, 0, 0, 0),
(400022, 0, 45797, 0, 0, 0, 0),
(400022, 0, 49084, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400023 hunter
DELETE FROM `creature_template` where `entry` =400023;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400023, 19646, 0, "Hunter glyphs", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400023);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400023, 0, 42897, 0, 0, 0, 0),
(400023, 0, 42898, 0, 0, 0, 0),
(400023, 0, 42899, 0, 0, 0, 0),
(400023, 0, 42900, 0, 0, 0, 0),
(400023, 0, 42901, 0, 0, 0, 0),
(400023, 0, 42902, 0, 0, 0, 0),
(400023, 0, 42903, 0, 0, 0, 0),
(400023, 0, 42904, 0, 0, 0, 0),
(400023, 0, 42905, 0, 0, 0, 0),
(400023, 0, 42906, 0, 0, 0, 0),
(400023, 0, 42907, 0, 0, 0, 0),
(400023, 0, 42908, 0, 0, 0, 0),
(400023, 0, 42909, 0, 0, 0, 0),
(400023, 0, 42910, 0, 0, 0, 0),
(400023, 0, 42911, 0, 0, 0, 0),
(400023, 0, 42912, 0, 0, 0, 0),
(400023, 0, 42913, 0, 0, 0, 0),
(400023, 0, 42914, 0, 0, 0, 0),
(400023, 0, 42915, 0, 0, 0, 0),
(400023, 0, 42916, 0, 0, 0, 0),
(400023, 0, 42917, 0, 0, 0, 0),
(400023, 0, 43338, 0, 0, 0, 0),
(400023, 0, 43350, 0, 0, 0, 0),
(400023, 0, 43351, 0, 0, 0, 0),
(400023, 0, 43354, 0, 0, 0, 0),
(400023, 0, 43355, 0, 0, 0, 0),
(400023, 0, 43356, 0, 0, 0, 0),
(400023, 0, 45625, 0, 0, 0, 0),
(400023, 0, 45731, 0, 0, 0, 0),
(400023, 0, 45732, 0, 0, 0, 0),
(400023, 0, 45733, 0, 0, 0, 0),
(400023, 0, 45734, 0, 0, 0, 0),
(400023, 0, 45735, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400024 rogue
DELETE FROM `creature_template` where `entry` =400024;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400024, 19646, 0, "Rogue glyphs", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400024);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400024, 0, 42954, 0, 0, 0, 0),
(400024, 0, 42955, 0, 0, 0, 0),
(400024, 0, 42956, 0, 0, 0, 0),
(400024, 0, 42957, 0, 0, 0, 0),
(400024, 0, 42958, 0, 0, 0, 0),
(400024, 0, 42959, 0, 0, 0, 0),
(400024, 0, 42960, 0, 0, 0, 0),
(400024, 0, 42961, 0, 0, 0, 0),
(400024, 0, 42962, 0, 0, 0, 0),
(400024, 0, 42963, 0, 0, 0, 0),
(400024, 0, 42964, 0, 0, 0, 0),
(400024, 0, 42965, 0, 0, 0, 0),
(400024, 0, 42966, 0, 0, 0, 0),
(400024, 0, 42967, 0, 0, 0, 0),
(400024, 0, 42968, 0, 0, 0, 0),
(400024, 0, 42969, 0, 0, 0, 0),
(400024, 0, 42970, 0, 0, 0, 0),
(400024, 0, 42971, 0, 0, 0, 0),
(400024, 0, 42972, 0, 0, 0, 0),
(400024, 0, 42973, 0, 0, 0, 0),
(400024, 0, 42974, 0, 0, 0, 0),
(400024, 0, 43343, 0, 0, 0, 0),
(400024, 0, 43376, 0, 0, 0, 0),
(400024, 0, 43377, 0, 0, 0, 0),
(400024, 0, 43378, 0, 0, 0, 0),
(400024, 0, 43379, 0, 0, 0, 0),
(400024, 0, 43380, 0, 0, 0, 0),
(400024, 0, 45761, 0, 0, 0, 0),
(400024, 0, 45762, 0, 0, 0, 0),
(400024, 0, 45764, 0, 0, 0, 0),
(400024, 0, 45766, 0, 0, 0, 0),
(400024, 0, 45767, 0, 0, 0, 0),
(400024, 0, 45768, 0, 0, 0, 0),
(400024, 0, 45769, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400025 priest
DELETE FROM `creature_template` where `entry` =400025;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400025, 19646, 0, "Priest glyphs", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400025);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400025, 0, 42396, 0, 0, 0, 0),
(400025, 0, 42397, 0, 0, 0, 0),
(400025, 0, 42398, 0, 0, 0, 0),
(400025, 0, 42399, 0, 0, 0, 0),
(400025, 0, 42400, 0, 0, 0, 0),
(400025, 0, 42401, 0, 0, 0, 0),
(400025, 0, 42402, 0, 0, 0, 0),
(400025, 0, 42403, 0, 0, 0, 0),
(400025, 0, 42404, 0, 0, 0, 0),
(400025, 0, 42405, 0, 0, 0, 0),
(400025, 0, 42406, 0, 0, 0, 0),
(400025, 0, 42407, 0, 0, 0, 0),
(400025, 0, 42408, 0, 0, 0, 0),
(400025, 0, 42409, 0, 0, 0, 0),
(400025, 0, 42410, 0, 0, 0, 0),
(400025, 0, 42411, 0, 0, 0, 0),
(400025, 0, 42412, 0, 0, 0, 0),
(400025, 0, 42414, 0, 0, 0, 0),
(400025, 0, 42415, 0, 0, 0, 0),
(400025, 0, 42416, 0, 0, 0, 0),
(400025, 0, 42417, 0, 0, 0, 0),
(400025, 0, 43342, 0, 0, 0, 0),
(400025, 0, 43370, 0, 0, 0, 0),
(400025, 0, 43371, 0, 0, 0, 0),
(400025, 0, 43372, 0, 0, 0, 0),
(400025, 0, 43373, 0, 0, 0, 0),
(400025, 0, 43374, 0, 0, 0, 0),
(400025, 0, 45753, 0, 0, 0, 0),
(400025, 0, 45755, 0, 0, 0, 0),
(400025, 0, 45756, 0, 0, 0, 0),
(400025, 0, 45757, 0, 0, 0, 0),
(400025, 0, 45758, 0, 0, 0, 0),
(400025, 0, 45760, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400026 DK
DELETE FROM `creature_template` where `entry` =400026;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400026, 19646, 0, "DK glyphs", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400026);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400026, 0, 43533, 0, 0, 0, 0),
(400026, 0, 43534, 0, 0, 0, 0),
(400026, 0, 43535, 0, 0, 0, 0),
(400026, 0, 43536, 0, 0, 0, 0),
(400026, 0, 43537, 0, 0, 0, 0),
(400026, 0, 43538, 0, 0, 0, 0),
(400026, 0, 43539, 0, 0, 0, 0),
(400026, 0, 43541, 0, 0, 0, 0),
(400026, 0, 43542, 0, 0, 0, 0),
(400026, 0, 43543, 0, 0, 0, 0),
(400026, 0, 43544, 0, 0, 0, 0),
(400026, 0, 43545, 0, 0, 0, 0),
(400026, 0, 43546, 0, 0, 0, 0),
(400026, 0, 43547, 0, 0, 0, 0),
(400026, 0, 43548, 0, 0, 0, 0),
(400026, 0, 43549, 0, 0, 0, 0),
(400026, 0, 43550, 0, 0, 0, 0),
(400026, 0, 43551, 0, 0, 0, 0),
(400026, 0, 43552, 0, 0, 0, 0),
(400026, 0, 43553, 0, 0, 0, 0),
(400026, 0, 43554, 0, 0, 0, 0),
(400026, 0, 43671, 0, 0, 0, 0),
(400026, 0, 43672, 0, 0, 0, 0),
(400026, 0, 43673, 0, 0, 0, 0),
(400026, 0, 43825, 0, 0, 0, 0),
(400026, 0, 43826, 0, 0, 0, 0),
(400026, 0, 43827, 0, 0, 0, 0),
(400026, 0, 45799, 0, 0, 0, 0),
(400026, 0, 45800, 0, 0, 0, 0),
(400026, 0, 45803, 0, 0, 0, 0),
(400026, 0, 45804, 0, 0, 0, 0),
(400026, 0, 45805, 0, 0, 0, 0),
(400026, 0, 45806, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400027 shaman
DELETE FROM `creature_template` where `entry` =400027;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400027, 19646, 0, "Shaman glyphs", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400027);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400027, 0, 41517, 0, 0, 0, 0),
(400027, 0, 41518, 0, 0, 0, 0),
(400027, 0, 41524, 0, 0, 0, 0),
(400027, 0, 41526, 0, 0, 0, 0),
(400027, 0, 41527, 0, 0, 0, 0),
(400027, 0, 41529, 0, 0, 0, 0),
(400027, 0, 41530, 0, 0, 0, 0),
(400027, 0, 41531, 0, 0, 0, 0),
(400027, 0, 41532, 0, 0, 0, 0),
(400027, 0, 41533, 0, 0, 0, 0),
(400027, 0, 41534, 0, 0, 0, 0),
(400027, 0, 41535, 0, 0, 0, 0),
(400027, 0, 41536, 0, 0, 0, 0),
(400027, 0, 41537, 0, 0, 0, 0),
(400027, 0, 41538, 0, 0, 0, 0),
(400027, 0, 41539, 0, 0, 0, 0),
(400027, 0, 41540, 0, 0, 0, 0),
(400027, 0, 41541, 0, 0, 0, 0),
(400027, 0, 41542, 0, 0, 0, 0),
(400027, 0, 41547, 0, 0, 0, 0),
(400027, 0, 41552, 0, 0, 0, 0),
(400027, 0, 43344, 0, 0, 0, 0),
(400027, 0, 43381, 0, 0, 0, 0),
(400027, 0, 43385, 0, 0, 0, 0),
(400027, 0, 43386, 0, 0, 0, 0),
(400027, 0, 43388, 0, 0, 0, 0),
(400027, 0, 43725, 0, 0, 0, 0),
(400027, 0, 44923, 0, 0, 0, 0),
(400027, 0, 45770, 0, 0, 0, 0),
(400027, 0, 45771, 0, 0, 0, 0),
(400027, 0, 45772, 0, 0, 0, 0),
(400027, 0, 45775, 0, 0, 0, 0),
(400027, 0, 45776, 0, 0, 0, 0),
(400027, 0, 45777, 0, 0, 0, 0),
(400027, 0, 45778, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400028 mage
DELETE FROM `creature_template` where `entry` =400028;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400028, 19646, 0, "Mage glyphs", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400028);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400028, 0, 42734, 0, 0, 0, 0),
(400028, 0, 42735, 0, 0, 0, 0),
(400028, 0, 42736, 0, 0, 0, 0),
(400028, 0, 42737, 0, 0, 0, 0),
(400028, 0, 42738, 0, 0, 0, 0),
(400028, 0, 42739, 0, 0, 0, 0),
(400028, 0, 42740, 0, 0, 0, 0),
(400028, 0, 42741, 0, 0, 0, 0),
(400028, 0, 42742, 0, 0, 0, 0),
(400028, 0, 42743, 0, 0, 0, 0),
(400028, 0, 42744, 0, 0, 0, 0),
(400028, 0, 42745, 0, 0, 0, 0),
(400028, 0, 42746, 0, 0, 0, 0),
(400028, 0, 42747, 0, 0, 0, 0),
(400028, 0, 42748, 0, 0, 0, 0),
(400028, 0, 42749, 0, 0, 0, 0),
(400028, 0, 42750, 0, 0, 0, 0),
(400028, 0, 42751, 0, 0, 0, 0),
(400028, 0, 42752, 0, 0, 0, 0),
(400028, 0, 42753, 0, 0, 0, 0),
(400028, 0, 42754, 0, 0, 0, 0),
(400028, 0, 43339, 0, 0, 0, 0),
(400028, 0, 43357, 0, 0, 0, 0),
(400028, 0, 43359, 0, 0, 0, 0),
(400028, 0, 43360, 0, 0, 0, 0),
(400028, 0, 43361, 0, 0, 0, 0),
(400028, 0, 43364, 0, 0, 0, 0),
(400028, 0, 44684, 0, 0, 0, 0),
(400028, 0, 44920, 0, 0, 0, 0),
(400028, 0, 44955, 0, 0, 0, 0),
(400028, 0, 45736, 0, 0, 0, 0),
(400028, 0, 45737, 0, 0, 0, 0),
(400028, 0, 45738, 0, 0, 0, 0),
(400028, 0, 45739, 0, 0, 0, 0),
(400028, 0, 45740, 0, 0, 0, 0),
(400028, 0, 50045, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400029 warlock
DELETE FROM `creature_template` where `entry` =400029;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400029, 19646, 0, "Warlock glyphs", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400029);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400029, 0, 42453, 0, 0, 0, 0),
(400029, 0, 42454, 0, 0, 0, 0),
(400029, 0, 42455, 0, 0, 0, 0),
(400029, 0, 42456, 0, 0, 0, 0),
(400029, 0, 42457, 0, 0, 0, 0),
(400029, 0, 42458, 0, 0, 0, 0),
(400029, 0, 42459, 0, 0, 0, 0),
(400029, 0, 42460, 0, 0, 0, 0),
(400029, 0, 42461, 0, 0, 0, 0),
(400029, 0, 42462, 0, 0, 0, 0),
(400029, 0, 42463, 0, 0, 0, 0),
(400029, 0, 42464, 0, 0, 0, 0),
(400029, 0, 42465, 0, 0, 0, 0),
(400029, 0, 42466, 0, 0, 0, 0),
(400029, 0, 42467, 0, 0, 0, 0),
(400029, 0, 42468, 0, 0, 0, 0),
(400029, 0, 42469, 0, 0, 0, 0),
(400029, 0, 42470, 0, 0, 0, 0),
(400029, 0, 42471, 0, 0, 0, 0),
(400029, 0, 42472, 0, 0, 0, 0),
(400029, 0, 42473, 0, 0, 0, 0),
(400029, 0, 43389, 0, 0, 0, 0),
(400029, 0, 43390, 0, 0, 0, 0),
(400029, 0, 43391, 0, 0, 0, 0),
(400029, 0, 43392, 0, 0, 0, 0),
(400029, 0, 43393, 0, 0, 0, 0),
(400029, 0, 43394, 0, 0, 0, 0),
(400029, 0, 45779, 0, 0, 0, 0),
(400029, 0, 45780, 0, 0, 0, 0),
(400029, 0, 45781, 0, 0, 0, 0),
(400029, 0, 45782, 0, 0, 0, 0),
(400029, 0, 45783, 0, 0, 0, 0),
(400029, 0, 45785, 0, 0, 0, 0),
(400029, 0, 45789, 0, 0, 0, 0),
(400029, 0, 50077, 0, 0, 0, 0);

-- FULL `npc_vendor` of entry 400030 druid
DELETE FROM `creature_template` where `entry` =400030;
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(400030, 19646, 0, "Druid glyphs", NULL, NULL, 0, 80, 80, 2, 35, 129, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, '');
DELETE FROM `npc_vendor` WHERE (entry = 400030);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `VerifiedBuild`) VALUES
(400030, 0, 40896, 0, 0, 0, 0),
(400030, 0, 40897, 0, 0, 0, 0),
(400030, 0, 40899, 0, 0, 0, 0),
(400030, 0, 40900, 0, 0, 0, 0),
(400030, 0, 40901, 0, 0, 0, 0),
(400030, 0, 40902, 0, 0, 0, 0),
(400030, 0, 40903, 0, 0, 0, 0),
(400030, 0, 40906, 0, 0, 0, 0),
(400030, 0, 40908, 0, 0, 0, 0),
(400030, 0, 40909, 0, 0, 0, 0),
(400030, 0, 40912, 0, 0, 0, 0),
(400030, 0, 40913, 0, 0, 0, 0),
(400030, 0, 40914, 0, 0, 0, 0),
(400030, 0, 40915, 0, 0, 0, 0),
(400030, 0, 40916, 0, 0, 0, 0),
(400030, 0, 40919, 0, 0, 0, 0),
(400030, 0, 40920, 0, 0, 0, 0),
(400030, 0, 40921, 0, 0, 0, 0),
(400030, 0, 40922, 0, 0, 0, 0),
(400030, 0, 40923, 0, 0, 0, 0),
(400030, 0, 40924, 0, 0, 0, 0),
(400030, 0, 43316, 0, 0, 0, 0),
(400030, 0, 43331, 0, 0, 0, 0),
(400030, 0, 43332, 0, 0, 0, 0),
(400030, 0, 43334, 0, 0, 0, 0),
(400030, 0, 43335, 0, 0, 0, 0),
(400030, 0, 43674, 0, 0, 0, 0),
(400030, 0, 44922, 0, 0, 0, 0),
(400030, 0, 44928, 0, 0, 0, 0),
(400030, 0, 45601, 0, 0, 0, 0),
(400030, 0, 45602, 0, 0, 0, 0),
(400030, 0, 45603, 0, 0, 0, 0),
(400030, 0, 45604, 0, 0, 0, 0),
(400030, 0, 45622, 0, 0, 0, 0),
(400030, 0, 45623, 0, 0, 0, 0),
(400030, 0, 46372, 0, 0, 0, 0),
(400030, 0, 48720, 0, 0, 0, 0),
(400030, 0, 50125, 0, 0, 0, 0);
