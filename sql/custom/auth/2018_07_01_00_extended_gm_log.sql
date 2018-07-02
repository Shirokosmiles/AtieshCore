ALTER TABLE `account_gm_log`
    ADD COLUMN `basecmd` VARCHAR(255) NOT NULL AFTER `command`,
    ADD COLUMN `cmdparameters` VARCHAR(255) NOT NULL AFTER `basecmd`,
    ADD COLUMN `cmdvalues` INT(10) NOT NULL AFTER `cmdparameters`;