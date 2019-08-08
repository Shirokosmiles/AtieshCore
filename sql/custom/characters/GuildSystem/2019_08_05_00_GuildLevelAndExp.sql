ALTER TABLE `guild`
    ADD COLUMN `GuildLevel` INT(10) NOT NULL DEFAULT '1' AFTER `BankMoney`;
	
ALTER TABLE `guild`
	ADD COLUMN `GuildExperience` INT(10) NOT NULL DEFAULT '0' AFTER `GuildLevel`;