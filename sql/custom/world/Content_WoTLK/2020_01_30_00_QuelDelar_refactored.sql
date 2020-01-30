-- Table `creature_template`
UPDATE `creature_template` SET `ScriptName` = 'npc_queldelar_sunwell_plateau' WHERE (entry = 38056);
UPDATE `creature_template` SET `ScriptName` = 'npc_sunwell_warder' WHERE (entry = 37523);

-- Table `gameobject_template`
UPDATE `gameobject_template` SET `ScriptName` = 'go_dalaran_portal_sunwell' WHERE (entry = 201797);

DELETE FROM `gameobject` WHERE (id = 201797);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(9294, 201797, 580, 4075, 0, 1, 2048, 1663.81, 663.74, 28.0502, 5.55015, 0, 0, -0.358368, 0.933581, 7200, 255, 1, 0),
(9298, 201797, 580, 4075, 0, 1, 2048, 1733.57, 593.142, 28.0502, 3.49067, 0, 0, -0.984807, 0.173652, 7200, 255, 1, 0);

-- Table `item_template`
UPDATE `item_template` SET `ScriptName` = 'item_tainted_queldelar' WHERE `entry` IN (49879,49889);

-- Table `creature` 3 npc without condition on ended quests in location should be visible always
UPDATE `creature` SET `phaseMask` = 2049 WHERE `guid` IN (43498,121400,121399);

-- Table `creature_text` update missed texts
DELETE FROM `creature_text` WHERE CreatureID = 37781 AND `GroupID` = 5;
DELETE FROM `creature_text` WHERE CreatureID = 37765 AND `GroupID` = 6;
DELETE FROM `creature_text` WHERE CreatureID = 37765 AND `GroupID` = 7;
DELETE FROM `creature_text` WHERE CreatureID = 37763 AND `GroupID` = 8;
DELETE FROM `creature_text` WHERE CreatureID = 37763 AND `GroupID` = 9;
DELETE FROM `creature_text` WHERE CreatureID = 37765 AND `GroupID` = 10;

INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(37781, 5, 0, 'Drop your weapon and surrender, traitor.', 14, 0, 100, 1, 0, 0, 37390, 0, 'tainted_queldelar'),

(37765, 6, 0, 'This is not my doing, Rommath. There is no treachery here.', 14, 0, 100, 1, 0, 0, 37430, 0, 'tainted_queldelar'),
(37765, 7, 0, 'Call off your men. Lor\'themar\'s own foolishness caused his injuries. Quel\'Delar is not chosen; it chooses its master.', 14, 0, 100, 1, 0, 0, 37431, 0, 'tainted_queldelar'),

(37763, 8, 0, 'Guards, return to your posts.', 14, 0, 100, 1, 0, 0, 37432, 0, 'tainted_queldelar'),
(37763, 9, 0, 'You will have what you have come for, $n. Take the sword and begone. And you, Auric, have a care for what you say in this sacred place.', 14, 0, 100, 1, 0, 0, 37434, 0, 'tainted_queldelar'),

(37765, 10, 0, 'Carry the sword back to Dalaran through that portal, $n. You have done what many quel\'dorei have dreamt of for years. Quel\'Delar has been restored at last.', 14, 0, 100, 1, 0, 0, 37440, 0, 'tainted_queldelar');
