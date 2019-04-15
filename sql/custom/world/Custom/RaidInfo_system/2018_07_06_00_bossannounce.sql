-- Strings for Boss Announce
DELETE FROM `trinity_string` where `entry` IN (788, 789, 790, 791);
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES ('788', '|cffff0000[RAID INFO]|r |cffe6cc80%s %s %s defeated by the %s with leader:|r |cFFDCDCDC%s|r %s|cffe6cc80. Players (%i / %i) is alive|r');
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES ('789', '|cffff0000Members:|r |cffe6cc80Tanks -|r |cFF7CFC00%i|r|cffe6cc80, Healers -|r |cFF7CFC00%i|r|cffe6cc80, Damagers -|r |cFF7CFC00%i|r |cffe6cc80 (Avg GS: %u)|r');
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES ('790', '|cffff0000Status:|r |cffe6cc80(%u / %u) boss completed|r');
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES ('791', '|cffff0000Boss|r |cffe6cc80 has been defeated for %s|r');