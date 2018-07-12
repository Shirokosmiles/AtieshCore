ALTER TABLE `characters`
    ADD COLUMN `pvpweeklycap` INT(10) NOT NULL DEFAULT '0' AFTER `grantableLevels`;