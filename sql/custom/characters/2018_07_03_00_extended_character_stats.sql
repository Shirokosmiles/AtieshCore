ALTER TABLE `character_stats`
    ADD COLUMN `expertiseBaseAttackPct` float unsigned NOT NULL DEFAULT '0' AFTER `resilience`,
    ADD COLUMN `expertiseOffAttackPct` float unsigned NOT NULL DEFAULT '0' AFTER `expertiseBaseAttackPct`,
    ADD COLUMN `hitMelee` INT(10) NOT NULL DEFAULT '0' AFTER `expertiseOffAttackPct`,
    ADD COLUMN `hitRanged` INT(10) NOT NULL DEFAULT '0' AFTER `hitMelee`,
    ADD COLUMN `hitSpell` INT(10) NOT NULL DEFAULT '0' AFTER `hitRanged`,
    ADD COLUMN `hasteMelee` INT(10) NOT NULL DEFAULT '0' AFTER `hitSpell`,
    ADD COLUMN `hasteRanged` INT(10) NOT NULL DEFAULT '0' AFTER `hasteMelee`,
    ADD COLUMN `hasteSpell` INT(10) NOT NULL DEFAULT '0' AFTER `hasteRanged`;