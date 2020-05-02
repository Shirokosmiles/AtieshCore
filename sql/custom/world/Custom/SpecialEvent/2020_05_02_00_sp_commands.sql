DELETE FROM `trinity_string` where `entry` IN (11125, 11126, 11127);
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES
('11125', '%s: %s'),
('11126', '%s: has been started'),
('11127', '%s: has been ended');