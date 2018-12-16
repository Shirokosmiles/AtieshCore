-- Antispam mail
DELETE FROM `trinity_string` where `entry` IN (11124);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES ('11124', 'You have sent too many mails than available %d in a short time interval.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
