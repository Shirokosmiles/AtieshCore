ALTER TABLE `guild`
	ADD COLUMN `GuildFaction` INT(10) NOT NULL DEFAULT '0' AFTER `GuildExperience`;