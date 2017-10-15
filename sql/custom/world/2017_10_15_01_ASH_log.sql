-- Strings for ASH + AFH allerts
DELETE FROM `trinity_string` where `entry` IN (6617);
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES ('6617', 'AntiCheat: SpeedHack Detected for %s, normal distance for this time and speed = %f, distance from packet = %f');