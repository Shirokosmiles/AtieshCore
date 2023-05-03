-- ----------------------------
-- Table structure for world_config
-- ----------------------------
DROP TABLE IF EXISTS `world_custom_config`;
CREATE TABLE `world_custom_config`  (
  `OptionName` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Type` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT 'Support types - bool, int, float',
  `IDInTypeGroup` int(10) NOT NULL,
  `DefaultValue` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `CustomValue` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `Description` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  PRIMARY KEY (`OptionName`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = DYNAMIC;

DELETE FROM `world_custom_config` WHERE `Type` = 'bool' AND `IDInTypeGroup` between 0 and 50;
INSERT INTO `world_custom_config`(`OptionName`, `Type`, `IDInTypeGroup`, `DefaultValue`, `CustomValue`, `Description`) VALUES 
-- AT configs
('AntiCheats.FakeJumper.Enabled', 'bool', 0, '1', NULL, 'Enable AntiCheat.FakeJumper : when player sent a move opcode (with new Z higher) when has flag falling (client can\'t sent any new packets when falling) It\'s normal for Gagarin hacks and with Air Mode + \"space\" click = \"falling\" mode (player can\'t change orientation of flying, but it move up)'),
('AntiCheats.FakeFlyingmode.Enabled', 'bool', 1, '1', NULL, 'Enable AntiCheat.FakeFlyingmode : when player sent a move opcode with added fly flag but on server this flag doesn\'t restricted for player. It\'s normal for Hitchhiker\'s Hack with Air Mode'),
('AntiCheats.DoubleJump.Enabled', 'bool', 2, '1', NULL, 'Enable AntiCheat.DoubleJump Kick when player sent opcode jump when has flag falling (client can\'t do this)'),
('AntiCheats.FlyHack.Enabled', 'bool', 3, '1', NULL, 'Enable AntiCheat.FlyHack'),
('AntiCheats.SpeedHack.Enabled', 'bool', 4, '1', NULL, 'Enable AntiCheat.SpeedHack'),
('AntiCheats.IgnoreControlMovement.Enabled', 'bool', 5, '1', NULL, 'Enable AntiCheat.IgnoreControlMovement : when player in root state - client can\'t send a new movement packets'),
('AntiCheats.SpeedHack.Kick.Enabled', 'bool', 6, '1', NULL, 'Enable AntiCheat.SpeedHack Kick when detected'),
('AntiCheats.FlyHack.Kick.Enabled', 'bool', 7, '1', NULL, 'Enable AntiCheat.FlyHack Kick when detected'),
('AntiCheats.FakeJumper.Kick.Enabled', 'bool', 8, '1', NULL, 'Enable AntiCheats.FakeJumper Kick when detected'),
('AntiCheats.FakeFlyingmode.Kick.Enabled', 'bool', 9, '1', NULL, 'Enable AntiCheats.FakeFlyingmode Kick when detected'),
('AntiCheats.NoFallingDmg.Kick.Enabled', 'bool', 10, '1', NULL, 'Enable AntiCheats.NoFallingDmg Kick when detected'),
('Config.Vip.Debuff.Command', 'bool', 11, '0', NULL, 'Enable/Disable custom vip command'),
('Config.Vip.Bank.Command', 'bool', 12, '0', NULL, 'Enable/Disable custom vip command'),
('Config.Vip.Mail.Command', 'bool', 13, '1', NULL, 'Enable/Disable custom vip command'),
('Config.Vip.Repair.Command', 'bool', 14, '1', NULL, 'Enable/Disable custom vip command'),
('Config.Vip.Reset.Talents.Command', 'bool', 15, '1', NULL, 'Enable/Disable custom vip command'),
('Config.Vip.Taxi.Command', 'bool', 16, '1', NULL, 'Enable/Disable custom vip command'),
('Config.Vip.Home.Command', 'bool', 17, '1', NULL, 'Enable/Disable custom vip command'),
('Config.Vip.Change.Race.Command', 'bool', 18, '0', NULL, 'Enable/Disable custom vip command'),
('Config.Vip.Customize.Command', 'bool', 19, '0', NULL, 'Enable/Disable custom vip command'),
('Config.Vip.Capital.Command', 'bool', 20, '1', NULL, 'Enable/Disable custom vip command'),
('Config.Vip.Appear.Command', 'bool', 21, '1', NULL, 'Enable/Disable custom vip command'),
('Config.Vip.Item.Helper', 'bool', 22, '1', NULL, 'Enable/Disable Item helper in game'),
('CheckM2ObjectLoS', 'bool', 23, '1', NULL, 'Include M2 objects (trees etc.) in line of sight checks.'),
('CrossfactionBG.enable', 'bool', 24, '0', NULL, 'Mixed battleground'),
('Chat.StrictMessages.Enabled', 'bool', 25, '1', NULL, 'Limit player message to language specific symbol set. Prevents character messages and ignore request if not allowed symbols are used'),
('DalaranGEvent.InstantReviveAndReturn.Enable', 'bool', 26, '0', NULL, NULL),
('DalaranGEvent.Squad.Enable', 'bool', 27, '0', NULL, NULL),
('GSystem.LootBroadcast.Enabled', 'bool', 28, '1', NULL, 'Guild announce when member take a loot with Quality >= EPIC'),
('GSystem.GuildLevel.Enabled', 'bool', 29, '1', NULL, 'Make a possible guild level system'),
('GSystem.GuildWars.Enabled', 'bool', 30, '1', NULL, 'Give possibility to make Guild Wars between guilds'),
('GSystem.GuildWars.BetweenBothFaction.Enabled', 'bool', 31, '1', NULL, 'Give possibility to make Guild Wars between guilds from both faction (Alliance and Horde)'),
('GSystem.GuildLevel.ShowLevelGuild.WhoList.Enabled', 'bool', 32, '1', NULL, 'Make a visible guild level in whoList'),
('GSystem.GuildLevel.ShowLevelGuild.QueryList.Enabled', 'bool', 33, '1', NULL, 'Make a visible guild level in query opcode (visible name/guild above character)'),
('GSystem.GuildWars.ShowLevelGuild.EnemyList.Enabled', 'bool', 34, '1', NULL, 'Show Enemy Guild Level in GW enemy list'),
('LFG.Channel.Everywhere', 'bool', 35, '1', NULL, 'Allow access at LookupForGroup channel to characters without condition of LFG state.'),
('LFG.CrossFaction.Groups', 'bool', 36, '0', NULL, 'Enable/Disable custom system for crossfaction DungeonFinder groups'),
('Mail.Antispam.Enabled', 'bool', 37, '1', NULL, 'When player will receive this limit, he just can\'t bid or bidout from auction. Calendar will not sent mail him.  And another player can\'t sent mail to him, just will see error overloaded mailbox of receiver.'),
('Mail.External.Enabled', 'bool', 38, '1', NULL, 'MailMgr will look in External table for receive a new mails from site ot something else'),
('Player.AutoLearnSpells.Enabled', 'bool', 39, '0', NULL, 'Player will auto learn spell when reach a level (table player_spells_for_level)'),
('Player.UniversalLanguage.Enabled', 'bool', 40, '0', NULL, 'Player talking on Universal language (need for different chatMgr and 1 language for SAY and etc)'),
('Player.PVPBonusCapReward.Enabled', 'bool', 41, '1', NULL, 'Enable/Disable custom PVP bonus cap reward for arena. It give bonus weekly reward when cap is complited (1500/1500 by default)'),
('Player.DuelPhase.Enabled', 'bool', 42, '1', NULL, 'Make a special phase for duel members, they will see only oponent, and can\'t see others units'),
('Player.BAGScript.Enabled', 'bool', 43, '0', NULL, 'Created character will receive a bags bonus'),
('Player.StartPack.Enabled', 'bool', 44, '0', NULL, 'Give a possibility to receive start-pack items from item helper'),
('Player.FLABScript.Enabled', 'bool', 45, '1', NULL, 'First character on account will receive a money bonus'),
('RaidInfo.Enabled', 'bool', 46, '0', NULL, 'Enable/Disable custom raid info system for world announce of killed bosses'),
('OSXPlayers.Enabled', 'bool', 47, '1', NULL, 'We can block connect for players from OSX OS system'),
('VAS.Unit.Enabled', 'bool', 48, '0', NULL, 'VAS Auto Balance system'),
('vmap.enableLOS', 'bool', 49, '1', NULL, 'VMmap support for line of sight and height calculation.'),
('vmap.enableHeight', 'bool', 50, '1', NULL, 'VMmap support for line of sight and height calculation.');

DELETE FROM `world_custom_config` WHERE `Type` = 'int' AND `IDInTypeGroup` between 0 and 24;
INSERT INTO `world_custom_config`(`OptionName`, `Type`, `IDInTypeGroup`, `DefaultValue`, `CustomValue`, `Description`) VALUES 
-- AT configs
('VanishVisionTimer', 'int', 0, '600', NULL, 'Vanish Fade Delay (vanish evade all spells without CC control in this time) (in ms)'),
('VanishCCbreakTimer', 'int', 1, '300', NULL, 'Vanish Should evade CC spells too, when casted, but it\'s a little lime.'),
('AntiCheats.FlyHackTimer', 'int', 2, '3000', NULL, 'Timer for AntiCheat FlyHack check #Default: 3000 - 1 check in 1 second'),
('FLAB.Script.MaxChars', 'int', 3, '0', NULL, 'Count of characters for give a bonus #Default:     0 - it should be a first character on acc, right?'),
('FLAB.Script.BonusMoney', 'int', 4, '10000000', NULL, 'Count of money ( 1000 gold )'),
('PVPBonusCapReward.MaxCap', 'int', 5, '1500', NULL, 'Max values for Weekly Cap'),
('PVPBonusCapReward.CapChanges.Win', 'int', 6, '180', NULL, 'Value for cap after Win'),
('PVPBonusCapReward.CapChanges.Lose', 'int', 7, '60', NULL, 'Value for cap after Lose'),
('Antispam.Mail.Timer', 'int', 8, '3600', NULL, 'Timer for possible next sending count of mails by mailbox'),
('Antispam.Mail.Count', 'int', 9, '10', NULL, 'How many mails you can sent in game in 1 period of timer'),
('Antispam.Mail.Controller', 'int', 10, '100', NULL, 'How many mails player can hold in mailbox, include mail in future (from auctionhouse and calendar).'),
('BAG.Script.BonusBagsID', 'int', 11, '51809', NULL, 'itemid of bags ( 51809 )'),
('GSystem.GuildWars.Minimal.PlayerCount', 'int', 12, '10', NULL, 'minimal count of members in guild for participation in GW'),
('GSystem.GuildWars.Minimal.Delta.PreviousStartTimer', 'int', 13, '3600', NULL, 'minimal timer for guild from previous start war time for starting a new war'),
('GSystem.GuildWars.Minimal.Delta.PreviousEndTimer', 'int', 14, '3600', NULL, 'minimal timer for guild from previous end war time for starting a new war'),
('GSystem.GuildLevel.Exp.ForArena', 'int', 15, '5', NULL, 'exp of guild for Win on Arena of each guild member'),
('GSystem.GuildLevel.Exp.ForBG', 'int', 16, '1', NULL, 'exp of guild for Win on BG of each guild member'),
('GSystem.GuildLevel.Exp.ForLFG', 'int', 17, '1', NULL, 'exp of guild for Win on LFG of each guild member'),
('GSystem.GuildWars.Exp.ForEnemyGuildKill', 'int', 18, '1', NULL, 'reward guild by exp for killing members of enemy guild (in GW status). Depend from GSystem.GuildLevel.Enabled'),
('GSystem.GuildWars.Exp.ForWinnerOfGW', 'int', 19, '250', NULL, 'reward winner guild by exp for Win in Guild Wars'),
('GSystem.GuildWars.Exp.ForLoserOfGW', 'int', 20, '100', NULL, 'reward winner guild by exp for Lose in Guild Wars'),
('GSystem.GuildLevel.LvL.ForMyBank', 'int', 21, '5', NULL, 'Level of guild for opening MyBank func'),
('GSystem.GuildLevel.LvL.ForRepair', 'int', 22, '3', NULL, 'Level of guild for opening Repair func'),
('DalaranGEvent.Min.Players', 'int', 23, '5', NULL, 'DalaranCrater Event minimal players');

DELETE FROM `world_custom_config` WHERE `Type` = 'rate' AND `IDInTypeGroup` between 0 and 7;
INSERT INTO `world_custom_config`(`OptionName`, `Type`, `IDInTypeGroup`, `DefaultValue`, `CustomValue`, `Description`) VALUES 
-- AT configs
('Rate.XP.Kill.Premium', 'rate', 0, '1', NULL, 'Individual rate for vip player'),
('Rate.XP.Quest.Premium', 'rate', 1, '1', NULL, 'Individual rate for vip player'),
('Rate.Honor.Premium', 'rate', 2, '1', NULL, 'Individual rate for vip player'),
('Rate.Reputation.Gain.Premium', 'rate', 3, '1', NULL, 'Individual rate for vip player'),
('GSystem.GuildLevel.Rate.XP.Bonus', 'rate', 4, '2', NULL, 'Rate for character experience when guild >= 2 level'),
('VAS.Creature.InZone.Damage', 'rate', 5, '1', NULL, 'Change HP and Damage value for Units in Dungeons in % #Default: 100 - (full HP and Damage) 10 - (units have only 10% of HP or can deal damage 10% of base damage value)'),
('VAS.Creature.InZone.SpellDamage', 'rate', 6, '1', NULL, 'Change HP and Damage value for Units in Dungeons in % #Default: 100 - (full HP and Damage) 10 - (units have only 10% of HP or can deal damage 10% of base damage value)'),
('VAS.Creature.InZone.Health', 'rate', 7, '1', NULL, 'Change HP and Damage value for Units in Dungeons in % #Default: 100 - (full HP and Damage) 10 - (units have only 10% of HP or can deal damage 10% of base damage value)');
