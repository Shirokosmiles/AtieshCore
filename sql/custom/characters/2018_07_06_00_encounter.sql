ALTER TABLE `instance`
    ADD COLUMN `completedEncountersCount` INT(10) NOT NULL AFTER `completedEncounters`;