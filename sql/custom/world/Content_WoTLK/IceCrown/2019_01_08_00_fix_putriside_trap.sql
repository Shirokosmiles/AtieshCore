DELETE FROM `creature_template_movement` where `CreatureId` IN (37782);
INSERT INTO `creature_template_movement`(`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Chase`, `Random`) VALUES 
(37782, 1, 1, 0, 0, 2, 2);