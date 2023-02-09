ALTER TABLE `character_stats`
    ADD COLUMN `spellDamage` INT(10) NOT NULL DEFAULT '0' AFTER `mp5base`;

ALTER TABLE `character_stats`
    ADD COLUMN `spellHealing` INT(10) NOT NULL DEFAULT '0' AFTER `spellDamage`;