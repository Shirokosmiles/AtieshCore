UPDATE `creature_template` SET `speed_walk` = 0.8, `speed_run` = 0.8 WHERE `entry` = 36954;

DELETE FROM `creature_template_movement` WHERE (CreatureId = 36954);
INSERT INTO `creature_template_movement`(`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Chase`, `Random`) VALUES 
(36954, 1, 1, 0, 0, 2, 0);