DROP TABLE IF EXISTS promotion_codes;
CREATE TABLE `promotion_codes` (
  `id` int(11) unsigned NOT NULL,
  `collection` int(11) unsigned,
  `code` varchar(19) NOT NULL DEFAULT '',
  `honor` int(11) unsigned,
  `arena` int(11) unsigned,
  `money` int(11) unsigned,
  `item_1` int(11) unsigned,
  `item_2` int(11) unsigned,
  `item_3` int(11) unsigned,
  `item_count_1` int(11) unsigned,
  `item_count_2` int(11) unsigned,
  `item_count_3` int(11) unsigned,
  `aura` int(11) unsigned,
  `spell_1` int(11) unsigned,
  `spell_2` int(11) unsigned,
  `spell_3` int(11) unsigned,
  `coin` int(11) unsigned,
  `count_of_exists` int(11) unsigned NOT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE KEY `code` (`code`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

DROP TABLE IF EXISTS promotion_codes_history;
CREATE TABLE `promotion_codes_history` (
  `id` int(11) unsigned NOT NULL,
  `codeID` int(11) unsigned NOT NULL,
  `code` varchar(19) NOT NULL DEFAULT '',
  `accountID` int(11) unsigned NOT NULL,
  `playerID` int(11) unsigned,
  `use_time` varchar(19) NOT NULL DEFAULT '',
  `use_unix_time` int(11) unsigned,
PRIMARY KEY (`id`)
) ENGINE = InnoDB CHARACTER SET = utf8;