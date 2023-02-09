DELETE FROM `smart_scripts` WHERE `entryorguid`=26477;
UPDATE `creature_template` SET `AIName` = '' WHERE (entry = 26477);
UPDATE `creature_template` SET `ScriptName` = 'npc_body_magehunter' WHERE (entry = 26477);
UPDATE `item_loot_template` SET `Chance`=10 WHERE `Item`=35783 AND `Entry`=35792;
UPDATE `item_loot_template` SET `Chance`=33 WHERE `Item`=35788 AND `Entry`=35792;
UPDATE `item_loot_template` SET `Chance`=33 WHERE `Item`=35790 AND `Entry`=35792;
UPDATE `item_loot_template` SET `Chance`=33 WHERE `Item`=35791 AND `Entry`=35792;