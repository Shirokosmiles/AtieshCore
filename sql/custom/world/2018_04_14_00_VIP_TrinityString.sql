-- Vip LANG_PINFO_CHR_VIP_MODE
DELETE FROM `trinity_string` WHERE entry = 883;
INSERT INTO `trinity_string` VALUES
(883,'The character has VIP privileges: %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Игрок имеет VIP привилегии: %s');

-- Vip LANG_PLAYER_VIP_TIME_EXIST
DELETE FROM `trinity_string` WHERE entry = 11120;
INSERT INTO `trinity_string` VALUES
(11120,'The remaining VIP time will expire in: %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Оставшееся VIP время истечет через: %s');
-- Vip LANG_PLAYER_VIP_TIME_NEAR_END
DELETE FROM `trinity_string` WHERE entry = 11121;
INSERT INTO `trinity_string` VALUES
(11121,'The remaining VIP time is less than 5 minutes!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Оставшееся время VIP привилегий составляет менее 5 минут!');
-- Vip LANG_PLAYER_VIP_TIME_EXPIRED
DELETE FROM `trinity_string` WHERE entry = 11122;
INSERT INTO `trinity_string` VALUES
(11122,'Your VIP time has been expired!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Время VIP привилегий истекло!');
-- Vip LANG_TARGETPLAYER_VIP_TIME_EXIST
DELETE FROM `trinity_string` WHERE entry = 11123;
INSERT INTO `trinity_string` VALUES
(11123,'The remaining VIP time of this target will expire in: %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Оставшееся VIP время указанного игрока истечет через: %s');