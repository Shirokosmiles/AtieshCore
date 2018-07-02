ALTER TABLE `account_gm_log`
    ADD COLUMN `basecmd` VARCHAR(255) NOT NULL AFTER `command`,
    ADD COLUMN `subcmd` VARCHAR(255) NOT NULL AFTER `basecmd`,
    ADD COLUMN `valuescmd` INT(10) NOT NULL AFTER `subcmd`;