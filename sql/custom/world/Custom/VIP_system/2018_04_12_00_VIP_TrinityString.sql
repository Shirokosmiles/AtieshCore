-- VIP
-- Check VIP
DELETE FROM `trinity_string` WHERE entry = 11110;
INSERT INTO `trinity_string` VALUES
(11110,'You are not vip.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Доступно только VIP игрокам.');
-- Disable VIP Command
DELETE FROM `trinity_string` WHERE entry = 11111;
INSERT INTO `trinity_string` VALUES
(11111,'Сommand disable',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Команда отключена.');	
-- VIP Error
DELETE FROM `trinity_string` WHERE entry = 11112;
INSERT INTO `trinity_string` VALUES
(11112,'error',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Произошла ошибка.');
-- VIP BG
DELETE FROM `trinity_string` WHERE entry = 11113;
INSERT INTO `trinity_string` VALUES
(11113,'You can not use this command on Battleground or the arena!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Вы не можете использовать данную команду на поле боя или на арене!');
-- VIP Stealth
DELETE FROM `trinity_string` WHERE entry = 11114;
INSERT INTO `trinity_string` VALUES
(11114,'You can not use this command in stealth mode!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Вы не можете использовать данную команду в режиме незаметности!');
-- Vip Dead
DELETE FROM `trinity_string` WHERE entry = 11115;
INSERT INTO `trinity_string` VALUES
(11115,'You are dead and you can not use this command!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Вы мертвы и не можете использовать данную команду!');
-- Vip Change race
DELETE FROM `trinity_string` WHERE entry = 11116;
INSERT INTO `trinity_string` VALUES
(11116,'Race Change will be requested at next login.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Смена расы будет предложена при следующем входе в игровой мир!');
-- Vip customize
DELETE FROM `trinity_string` WHERE entry = 11117;
INSERT INTO `trinity_string` VALUES
(11117,'Character customize will be requested at next login.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Смена внешности персонажа будет предложена при следующем входе в игровой мир!');
-- Vip group
DELETE FROM `trinity_string` WHERE entry = 11118;
INSERT INTO `trinity_string` VALUES
(11118,'You must be in the group',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Вы должны находится в группе!');
-- Vip not target and accid
DELETE FROM `trinity_string` WHERE entry = 11119;
INSERT INTO `trinity_string` VALUES
(11119,'Your target player has not vip privileges!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Указанный игрок не имеет ВИП привилегий!');