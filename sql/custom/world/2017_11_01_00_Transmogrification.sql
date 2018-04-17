DELETE FROM `trinity_string` WHERE `entry` BETWEEN 12100 AND 12140;

SET @STRING_ENTRY := 12100;
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc8`) VALUES
(@STRING_ENTRY+0, 'Item transmogrified', 'Предмет трансморгрифицирован'),
(@STRING_ENTRY+1, 'Equipment slot is empty', 'Слот экипировки пуст'),
(@STRING_ENTRY+2, 'Invalid source item selected', 'Некорректный исходный предмет выбран.'),
(@STRING_ENTRY+3, 'Source item does not exist', 'Исходный предмет не существует'),
(@STRING_ENTRY+4, 'Destination item does not exist', 'Целевой предмет не существует'),
(@STRING_ENTRY+5, 'Selected items are invalid', 'Выбранные предметы некорректны'),
(@STRING_ENTRY+6, 'Not enough money', 'Недостаточно денег'),
(@STRING_ENTRY+7, 'You don\'t have enough tokens', 'У вас недостаточно токенов'),
(@STRING_ENTRY+8, 'Transmogrifications removed', 'Трансморгрификация удалена'),
(@STRING_ENTRY+9, 'There are no transmogrifications', 'Трансморгрификации отсутствуют'),
(@STRING_ENTRY+10, 'Head', 'Голова'),
(@STRING_ENTRY+11, 'Shoulders', 'Плечи'),
(@STRING_ENTRY+12, 'Shirt', 'Рубашка'),
(@STRING_ENTRY+13, 'Chest', 'Тело'),
(@STRING_ENTRY+14, 'Waist', 'Пояс'),
(@STRING_ENTRY+15, 'Legs', 'Ноги'),
(@STRING_ENTRY+16, 'Feet', 'Обувь'),
(@STRING_ENTRY+17, 'Wrists', 'Запястья'),
(@STRING_ENTRY+18, 'Hands', 'Руки'),
(@STRING_ENTRY+19, 'Back', 'Спина'),
(@STRING_ENTRY+20, 'Main Hand', 'Правая рука'),
(@STRING_ENTRY+21, 'Off Hand', 'Левая рука'),
(@STRING_ENTRY+22, 'Ranged', 'Оружие дальнего боя'),
(@STRING_ENTRY+23, 'Tabard', 'Гербовая накидка'),
(@STRING_ENTRY+24, '|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|tHow transmogrification works', '|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|tКак трансморгрификация работает'),
(@STRING_ENTRY+25, '|TInterface/ICONS/INV_Enchant_Disenchant:30:30:-18:0|tRemove all transmogrifications', '|TInterface/ICONS/INV_Enchant_Disenchant:30:30:-18:0|tУдалить все трансморгрификации'),
(@STRING_ENTRY+26, 'Remove transmogrifications from all equipped items?', 'Удалить трансморгрификацию со всех одетых предметов?'),
(@STRING_ENTRY+27, '|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:30:30:-18:0|tUpdate menu', '|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:30:30:-18:0|tОбновить меню'),
(@STRING_ENTRY+28, '|TInterface/ICONS/Ability_Spy:30:30:-18:0|tBack...', '|TInterface/ICONS/Ability_Spy:30:30:-18:0|tНазад...'),
(@STRING_ENTRY+29, '|TInterface/ICONS/INV_Enchant_Disenchant:30:30:-18:0|tRemove transmogrification', '|TInterface/ICONS/INV_Enchant_Disenchant:30:30:-18:0|tУдалить трансморгрификацию'),
(@STRING_ENTRY+30, 'Remove transmogrification from the slot?', 'Удалить трансморгрификацию с этого предмета?'),
(@STRING_ENTRY+31, 'Invalid name inserted', 'Введено некорректное имя'),
(@STRING_ENTRY+32, '|TInterface/RAIDFRAME/UI-RAIDFRAME-MAINASSIST:30:30:-18:0|tManage sets', '|TInterface/RAIDFRAME/UI-RAIDFRAME-MAINASSIST:30:30:-18:0|tУправления комплектами'),
(@STRING_ENTRY+33, '|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|tHow sets work', '|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|tКак комплекты работают'),
(@STRING_ENTRY+34, '|TInterface/GuildBankFrame/UI-GuildBankFrame-NewTab:30:30:-18:0|tSave set', '|TInterface/GuildBankFrame/UI-GuildBankFrame-NewTab:30:30:-18:0|tСохранить комплект'),
(@STRING_ENTRY+35, 'Insert set name', 'Введите название комплекта'),
(@STRING_ENTRY+36, '|TInterface/ICONS/INV_Misc_Statue_02:30:30:-18:0|tUse set', '|TInterface/ICONS/INV_Misc_Statue_02:30:30:-18:0|tИспользовать комплект'),
(@STRING_ENTRY+37, 'Using this set for transmogrify will bind transmogrified items to you and make them non-refundable and non-tradeable.\nDo you wish to continue?\n\n', 'После трансморгрификации вы не сможете вернуть предметы торговцу, передать и они будут привязаны к вам.\nВы хотите продолжить?\n\n'),
(@STRING_ENTRY+38, '|TInterface/PaperDollInfoFrame/UI-GearManager-LeaveItem-Opaque:30:30:-18:0|tDelete set', '|TInterface/PaperDollInfoFrame/UI-GearManager-LeaveItem-Opaque:30:30:-18:0|tУдалить комплект'),
(@STRING_ENTRY+39, 'Are you sure you want to delete', 'Вы действительно хотите удалить'),
(@STRING_ENTRY+40, 'Using this item for transmogrify will bind it to you and make it non-refundable and non-tradeable.\nDo you wish to continue?\n\n', 'Использование этого итема для трансформирования свяжет его с вами и сделает его персональным и не подлежащим торговле.\nВы хотите продолжить?\n\n');

DELETE FROM `npc_text` WHERE `ID` BETWEEN 65000 AND 65001;
INSERT INTO `npc_text` (`ID`, `text0_0`, `VerifiedBuild`) VALUES
(65000, 'Transmogrification allows you to change how your items look like without changing the stats of the items.\r\nItems used in transmogrification are no longer refundable, tradeable and are bound to you.\r\nUpdating a menu updates the view and prices.\r\n\r\nNot everything can be transmogrified with eachother.\r\nRestrictions include but are not limited to:\r\nOnly armor and weapons can be transmogrified\r\nGuns, bows and crossbows can be transmogrified with eachother\r\nFishing poles can not be transmogrified\r\nYou must be able to equip both items used in the process.\r\n\r\nTransmogrifications stay on your items as long as you own them.\r\nIf you try to put the item in guild bank or mail it to someone else, the transmogrification is stripped.\r\n\r\nYou can also remove transmogrifications for free at the transmogrifier.', 1),
(65001, 'You can save your own transmogrification sets.\r\n\r\nTo save, first you must transmogrify your equipped items.\r\nThen when you go to the set management menu and go to save set menu,\r\nall items you have transmogrified are displayed so you see what you are saving.\r\nIf you think the set is fine, you can click to save the set and name it as you wish.\r\n\r\nTo use a set you can click the saved set in the set management menu and then select use set.\r\nIf the set has a transmogrification for an item that is already transmogrified, the old transmogrification is lost.\r\nNote that same transmogrification restrictions apply when trying to use a set as in normal transmogrification.\r\n\r\nTo delete a set you can go to the set\'s menu and select delete set.', 1);

DELETE FROM `npc_text_locale` WHERE `ID` BETWEEN 65000 AND 65001;
INSERT INTO `npc_text_locale` (`ID`, `Locale`, `Text0_0`) VALUES 
(65000, 'ruRU', 'Трансморгрификация позволяет вам изменить внешний вид вещи, не изменяя характеристик самой вещи.\r\nТрансморгрифицированные предметы нельзя вернуть торговцу, передать другому игроку и такой предмет станет персональным.\r\nОбновление меню обновляет вид и цены.\r\n\r\nНе любая вещь может быть трансморгрифицирована.\r\nОграничения включают (но не ограничиваются):\r\nТолько броня и оружие может быть трансморгрифицирована.\r\nОружия, луки и арбалеты могут быть трансморгрифицированы друг в друга.\r\nУдочки для рыбной ловли не могут быть трансморгрифицированы.\r\nВы должны иметь возможность экипировать обе вещи, используемые для трансморгрифицикации.\r\nТрансморгрификация сохраняется на вещи, пока вы ей владеете.\r\nЕсли вы попытаетесь поместить вещь в банк гильдии, отправить по почте или передать кому либо еще, то трансморгрификация будет отменена.\r\nВы можете бесплатно отменить трансморгрификацию у NPC.'),
(65001, 'ruRU', 'Вы можете сохранять наборы трансморгрификации.\r\n\r\nЧтобы сохранить набор трансморгрификации, вы должны сначала трансморгрифицировать вещи.\r\nПосле этого перейдите в меню управления комплектами трансморгрификации,\r\nвсе предметы, которые были трансморгрифицированы будут отображены, так что, вы увидите что сохраняете.\r\nЕсли вы думаете, что набор выглядит хорошо, вы можете кликнуть на кнопку сохранения и назвать комплект как пожелаете.\r\n\r\nЧтобы использовать набор вы можете нажать по названию сохраненного сета и использовать его.\r\nЕсли предмет уже трансморгрифицирован, то старая трансморгрификация будет утеряна.\r\nПри использовании наборов трансморгрификации помните про ограничения, они те же, что и при трансморгрификации одной вещи.\r\nДля удаления набора вы можете перейти в меню наборов и удалить набор.');

DELETE FROM `creature_template` WHERE `entry` = 190010;
DELETE FROM `creature_template_locale` WHERE `entry` = 190010;
SET @Entry = 190010, @Name = "Warpweaver";
INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(@Entry, 19646, 0, @Name, "Transmogrifier", NULL, 0, 80, 80, 2, 35, 1, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, 'Creature_Transmogrify');
INSERT INTO `creature_template_locale` (`entry`, `locale`, `Name`, `Title`) VALUES ('190010', 'ruRU', 'Искажающий пространство', 'Трансмогрификатор');