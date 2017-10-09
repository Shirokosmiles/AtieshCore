-- Transport to Mimiron button
UPDATE `gameobject_template` SET `ScriptName`='go_mimiron_activate_tram' WHERE `entry`=194437;

-- gobject move spawn
UPDATE `gameobject` SET `position_x`=2306.87, `position_y`=274.237, `position_z`=424.288, `orientation`=1.52255, `rotation2`=0.689847, `rotation3`=0.723956 WHERE `guid`=45164;

-- Transport Tram - for future
UPDATE `gameobject_template` SET `ScriptName`='go_transport_to_mimiron' WHERE `entry`='194675';
DELETE FROM `trinity_string` where `entry` IN (179);
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES ('179', 'TransOffsetX: %f TransOffsetY: %f TransOffsetZ: %f TransOffsetO: %f');