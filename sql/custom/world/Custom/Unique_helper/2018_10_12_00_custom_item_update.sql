-- Custom string
DELETE FROM `trinity_string` WHERE `entry` IN (11566, 11567, 11568, 11569, 11570, 11571, 11572, 11573, 11574);
INSERT INTO `trinity_string` VALUES
(11566,'You can not use it on BattleGround or Arena!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Вы не можете использовать его на БГ и Арене!'),
(11567,'You can not use it while you in stealth!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Вы не можете использовать его, пока находитесь в режиме незаметности!'),
(11568,'You can not use it while you dead!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Вы не можете использовать его, пока вы мертвы!'),
(11569,'|cff006699You successfully bought an item %u|r',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'|cff006699You successfully bought an item %u|r'),
(11570,'|cff006699Time of your VIP privileges has been increased for %u days!|r',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'|cff006699Time of your VIP privileges has been increased for %u days!|r'),
(11571,'|TInterface\\icons\\Ability_Mage_PotentSpirit:25:25:-15:0|tTrade Shop',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\Ability_Mage_PotentSpirit:25:25:-15:0|tМагазин'),
(11572,'|TInterface\\icons\\Achievement_BG_interruptX_flagcapture_attempts:25:25:-15:0|tYour Weekly PVP Bonus Cap : (',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\Achievement_BG_interruptX_flagcapture_attempts:25:25:-15:0|tYour Weekly PVP Bonus Cap : ('),
(11573,'|TInterface\\icons\\Achievement_BG_interruptX_flagcapture_attempts_1game:25:25:-15:0|tYour Weekly PVP Bonus Cap : (',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\Achievement_BG_interruptX_flagcapture_attempts_1game:25:25:-15:0|tYour Weekly PVP Bonus Cap : ('),
(11574,'|TInterface\\icons\\Spell_chargepositive:25:25:-15:0|tBank',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\Spell_chargepositive:25:25:-15:0|tБанк');

DELETE FROM `trinity_string` WHERE `entry` IN (11500, 11501, 11502, 11503, 11504, 11505, 11506, 11507, 11508, 11509, 11510, 11511, 11512, 11513, 11514, 11515, 11516, 11517, 11518, 11519, 11520, 11521, 11522, 11523, 11524, 11525, 11526, 11527, 11528, 11529, 11530, 11531, 11532, 11533, 11534, 11535, 11536, 11537, 11538, 11539, 11540, 11541, 11542, 11543, 11544, 11545, 11546, 11547, 11548, 11549, 11550, 11551, 11552, 11553, 11554, 11555, 11556, 11557, 11558, 11559, 11560, 11561, 11562, 11563, 11564, 11565);
-- LANG_ITEM_MSG_ALREADY_ITEM
INSERT INTO `trinity_string` VALUES
(11500,'|cff00ffffYou already have this item!|r',NULL,'|cff00ffffVous avez déjà cet objet !|r',NULL,NULL,NULL,NULL,NULL,'|cff00ffffУ вас уже имеется данная вещь!|r'),
-- LANG_ITEM_MSG_RENAME_COMPLETE
(11501,'|cff00ff00Payment complete. You need to do log-out by character and set a new name for character. Do not forget to clear folder Cache after rename!|r',NULL,'|cff00ff00Payment validé. Vous devez vous déconnecter de votre personnage et le renommer. N\'oubliez pas d\'effacer le dossier Cache après l\'avoir renommé !|r',NULL,NULL,NULL,NULL,NULL,'|cff00ff00Оплата успешно произведена. Сделайте логаут и введите новое имя своего персонажа.Не забудьте после смены имени, выйти из игры и удалить из клиента папку Cache!|r'),
-- LANG_ITEM_MSG_CUSTOMIZE_COMPLETE
(11502,'|cff00ff00Payment complete. You need to do log-out by character and set customize for character.Do not forget to clear folder Cache after rename!|r',NULL,'|cff00ff00Payment validé. Vous devez vous déconnecter de votre personnage et le personnaliser. N\'oubliez pas d\'effacer le dossier Cache après l\'avoir personnalisé !|r',NULL,NULL,NULL,NULL,NULL,'|cff00ff00Оплата успешно произведена. Сделайте логаут и измените внешность своего персонажа.Не забудьте после смены внешности, выйти из игры и удалить из клиента папку Cache!|r'),
-- LANG_ITEM_MSG_CHANGE_FACTION_COMPLETE
(11503,'|cff00ff00Payment complete. You need to do log-out by character and change faction for character.Do not forget to clear folder Cache after rename!|r',NULL,'|cff00ff00Payment validé. Vous devez vous déconnecter de votre personnage et changer de faction. N\'oubliez pas d\'effacer le dossier Cache après l\'avoir changé de faction !|r',NULL,NULL,NULL,NULL,NULL,'|cff00ff00Оплата успешно произведена. Сделайте логаут и измените фракцию своего персонажа.Не забудьте после смены фракции, выйти из игры и удалить из клиента папку Cache!|r'),
-- LANG_ITEM_MSG_CHANGE_RACE_COMPLETE
(11504,'|cff00ff00Payment complete. You need to do log-out by character and change race for character.Do not forget to clear folder Cache after change race!|r',NULL,'|cff00ff00Payment validé. Vous devez vous déconnecter de votre personnage et changer de race. N\'oubliez pas d\'effacer le dossier Cache après avoir changé de race !|r',NULL,NULL,NULL,NULL,NULL,'|cff00ff00Оплата успешно произведена. Сделайте логаут и измените расу своего персонажа.Не забудьте после смены расы, выйти из игры и удалить из клиента папку Cache!|r'),
-- LANG_ITEM_MSG_NO_ARENA_POINTS
(11505,'|cffff0000You have not enough A.P. for payment!|r',NULL,'|cffff0000Vous n\'avez pas assez d\'A.P pour le payement !|r',NULL,NULL,NULL,NULL,NULL,'|cffff0000У вас недостаточно A.P. для совершения покупки!|r'),
-- LANG_ITEM_MSG_RESET_COOLDOWN
(11506,'|cff0000ffAll your spell cooldowns has been reset!|r',NULL,'|cff0000ff Les temps de recharge de vos sorts ont été réinitialisés !|r',NULL,NULL,NULL,NULL,NULL,'|cff0000ffВремя перезарядки всех заклинаний и способностей сброшено!|r'),
-- LANG_ITEM_MSG_COOLDOWN
(11507,'|cff00ffffYou can not use this function so often!|r',NULL,'|cff00ffffVous ne pouvez pas utiliser cette fonction aussi souvent !|r',NULL,NULL,NULL,NULL,NULL,'|cff00ffffВы не можете использовать функцию так часто!|r'),
-- LANG_ITEM_MSG_RESET_QUEST_STATUS_COMPLETE
(11508,'|cff0000ffCooldown of quests has been reset!|r',NULL,'|cff0000ffQuêtes journalières réinitialisé !|r',NULL,NULL,NULL,NULL,NULL,'|cff0000ffКД заданий успешно сброшено!|r'),
-- LANG_ITEM_MSG_RESET_RAID_INSTANCES_COOLDOWN_COMPLETE
(11509,'|cff0000ffRaid dungeon binds and cooldowns has been reset!|r',NULL,'|cff0000ffRaids et donjons journaliers réinitialisés !|r',NULL,NULL,NULL,NULL,NULL,'|cff0000ffРейдовые подземелья успешно обновлены! КД сброшено!|r'),
-- LANG_ITEM_CURRENT_COINS
(11510,'|TInterface\\icons\\Inv_trinket_honorhold:25:25:-15:0|tAccount coins: ',NULL,'|TInterface\\icons\\Inv_misc_token_thrallmar:25:25:-15:0|tJetons du compte: ',NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\Inv_misc_token_thrallmar:25:25:-15:0|tБонусов на аккаунте : '),
-- LANG_ITEM_STORMWIND
(11511,'|TInterface/ICONS/Spell_Arcane_TeleportStormWind:25:25:-15:0|tStormwind',NULL,'|TInterface/ICONS/Spell_Arcane_TeleportStormWind:25:25:-15:0|tHurlevent',NULL,NULL,NULL,NULL,NULL,'|TInterface/ICONS/Spell_Arcane_TeleportStormWind:25:25:-15:0|tШтормград'),
-- LANG_ITEM_ORGRIMMAR
(11512,'|TInterface/ICONS/Spell_Arcane_TeleportOrgrimmar:25:25:-15:0|tOrgrimmar',NULL,'|TInterface/ICONS/Spell_Arcane_TeleportOrgrimmar:25:25:-15:0|tOrgrimmar',NULL,NULL,NULL,NULL,NULL,'|TInterface/ICONS/Spell_Arcane_TeleportOrgrimmar:25:25:-15:0|tОргриммар'),
-- LANG_ITEM_STORMWIND_SURE
(11513,'Are you sure you want to travel in Stormwind?',NULL,'Êtes-vous sûr de vouloir aller à Hurlevent ?',NULL,NULL,NULL,NULL,NULL,'Вы уверены, что вы хотите попасть в Штормград?'),
-- LANG_ITEM_ORGRIMMAR_SURE
(11514,'Are you sure you want to travel in Orgrimmar?',NULL,'Êtes-vous sûr de vouloir aller à Orgrimmar ?',NULL,NULL,NULL,NULL,NULL,'Вы уверены, что вы хотите попасть в Orgrimmar?'),
-- LANG_ITEM_VIP_MENU
(11515,'|TInterface\\icons\\Inv_inscription_pigment_bug07:25:25:-15:0|tVIP Account menu',NULL,'|TInterface\\icons\\Inv_inscription_pigment_bug07:25:25:-15:0|tMenu du compte VIP',NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\Inv_inscription_pigment_bug07:25:25:-15:0|tУправление Вип Аккаунтом'),
-- LANG_ITEM_SERVER_MENU
(11516,'|TInterface\\icons\\Inv_inscription_weaponscroll01:25:25:-15:0|t|cffD80000Server information|r',NULL,'|TInterface\\icons\\Inv_inscription_weaponscroll01:25:25:-15:0|t|cffD80000Informations sur le serveur|r',NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\Inv_inscription_weaponscroll01:25:25:-15:0|t|cffD80000Информация о сервере|r'),
-- LANG_ITEM_VIP_BUY
(11517,'|TInterface\\icons\\Inv_inscription_pigment_bug07:25:25:-15:0|tAccount: [|cffE80000buy VIP time|r]',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\Inv_inscription_pigment_bug07:25:25:-15:0|tАккаунт: [|cffE80000купить VIP время|r]'),
-- LANG_ITEM_VIP_INCREASE
(11518,'VIP account: [|cffE80000increase VIP time|r]',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'VIP Аккаунт: [|cffE80000Увеличить время действий привилегий|r]'),
-- LANG_ITEM_CLOSE
(11519,'|TInterface\\icons\\Spell_chargenegative:25:25:-15:0|tClose',NULL,'|TInterface\\icons\\Spell_chargenegative:25:25:-15:0|tFermer',NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\Spell_chargenegative:25:25:-15:0|tЗакрыть'),
-- LANG_ITEM_LEVELUP
(11520,'|cff006699You have successfully upgraded your level!|r',NULL,'|cff006699Vous avez amélioré votre niveau avec succès|r',NULL,NULL,NULL,NULL,NULL,'|cff006699Вы успешно повысили свой уровень!|r'),
-- LANG_ITEM_COMMAND_LIST
(11521,'|TInterface\\icons\\Inv_misc_note_02:25:25:-15:0|tList of available commands',NULL,'|TInterface\\icons\\Inv_misc_note_02:25:25:-15:0|tListe des commandes disponibles',NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\Inv_misc_note_02:25:25:-15:0|tСписок доступных комманд'),
-- LANG_ITEM_CHARACTER_MANAGMENT
(11522,'|TInterface\\icons\\Inv_misc_tournaments_banner_scourge:25:25:-15:0|tCharacter management',NULL,'|TInterface\\icons\\Inv_misc_tournaments_banner_scourge:25:25:-15:0|tGérer le personnage',NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\Inv_misc_tournaments_banner_scourge:25:25:-15:0|tУправление Персонажем'),
-- LANG_ITEM_CHARACTER_CHANGEING
(11523,'|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|tChanging the character',NULL,'|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|tChanger le personnage',NULL,NULL,NULL,NULL,NULL,'|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|tИзменение персонажа'),
-- LANG_ITEM_CLASS_SKILLS
(11524,'|TInterface\\icons\\achievement_level_80:25:25:-15:0|tClass skills',NULL,'|TInterface\\icons\\achievement_level_80:25:25:-15:0|tCompétences de classe',NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\achievement_level_80:25:25:-15:0|tКлассовые навыки'),
-- LANG_ITEM_REPAIR_EQUIP
(11525,'|TInterface\\icons\\Inv_throwingknife_02:25:25:-15:0|tRepair all equipment',NULL,'|TInterface\\icons\\Inv_throwingknife_02:25:25:-15:0|tRéparer tous les équipements',NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\Inv_throwingknife_02:25:25:-15:0|tПочинить всю экипировку'),
-- LANG_ITEM_REMOVE_DESERTER
(11526,'|TInterface/ICONS/ability_druid_cower:25:25:-15:0|tRemove Deserter',NULL,'|TInterface/ICONS/ability_druid_cower:25:25:-15:0|tSupprimer le débuff Déserteur',NULL,NULL,NULL,NULL,NULL,'|TInterface/ICONS/ability_druid_cower:25:25:-15:0|tСнять Дезертира'),
-- LANG_ITEM_REMOVE_WEAKNESS
(11527,'|TInterface\\icons\\spell_shadow_deathscream:25:25:-15:0|tRemove Weakness',NULL,'|TInterface\\icons\\spell_shadow_deathscream:25:25:-15:0|tSupprimer le débuff Faiblesse',NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\spell_shadow_deathscream:25:25:-15:0|tСнять Слабость'),
-- LANG_ITEM_GIVE_BUFFS
(11528,'|TInterface\\icons\\Spell_holy_wordfortitude:25:25:-15:0|tGet the buffs',NULL,'|TInterface\\icons\\Spell_holy_wordfortitude:25:25:-15:0|tObtenez les buffs',NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\Spell_holy_wordfortitude:25:25:-15:0|tПолучить баффы'),
-- LANG_ITEM_REMOVE_COOLDOWN
(11529,'|TInterface/ICONS/spell_holy_borrowedtime:25:25:-15:0|tRemove spell cooldowns',NULL,'|TInterface/ICONS/spell_holy_borrowedtime:25:25:-15:0|tSupprimer les temps de recharge des sorts',NULL,NULL,NULL,NULL,NULL,'|TInterface/ICONS/spell_holy_borrowedtime:25:25:-15:0|tСбросить КД на способности'),
-- LANG_ITEM_DUAL_SPEC
(11530,'|TInterface\\icons\\Ability_DualWield:25:25:-15:0|tDual specialization',NULL,'|TInterface\\icons\\Ability_DualWield:25:25:-15:0|tDouble spécialisation',NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\Ability_DualWield:25:25:-15:0|tДвойная специализация'),
-- LANG_ITEM_RESET_TALENT
(11531,'|TInterface\\icons\\ability_marksmanship:25:25:-15:0|tReset talents',NULL,'|TInterface\\icons\\ability_marksmanship:25:25:-15:0|tRéinitialiser vos talents',NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\ability_marksmanship:25:25:-15:0|tСброс талантов'),
-- LANG_ITEM_RESET_TALENT_SURE
(11532,'Are you sure you want to reset your talents?',NULL,'Êtes vous sur de vouloir réinitialiser vos talents ?',NULL,NULL,NULL,NULL,NULL,'Вы уверены, что хотите сбросить таланты?'),
-- LANG_ITEM_SKILLS_WEAPON
(11533,'|TInterface\\icons\\achievement_general:25:25:-15:0|tSkills weapon',NULL,'|TInterface\\icons\\achievement_general:25:25:-15:0|tCompétences d\'armes',NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\achievement_general:25:25:-15:0|tОружейные навыки'),
-- LANG_ITEM_MAXSKILL
(11534,'|TInterface\\icons\\trade_engineering:25:25:-15:0|tImprove skills of protecting and owning weapons to the maximum',NULL,'|TInterface\\icons\\trade_engineering:25:25:-15:0|tAméliorer les compétences de protection et de possession de type d\'armes au maximum',NULL,NULL,NULL,NULL,NULL,'|TInterface\\icons\\trade_engineering:25:25:-15:0|tУлучшить навыки защиты и владения оружием до максимума'),
-- LANG_ITEM_TALENT_RESET_CONFIRM
(11535,'Your talents have been successfully reset.',NULL,'Vos talents ont été réinitialisés avec succès.',NULL,NULL,NULL,NULL,NULL,'Ваши таланты успешно сброшены.'),
-- LANG_ITEM_SKILLS_WEAPON_CONFIRM
(11536,'You have successfully learned all the weapons skills for your class.',NULL,'Vous avez appris avec succès toutes les compétences d\'armes pour votre classe.',NULL,NULL,NULL,NULL,NULL,'Вы успешно изучили все оружейные навыки для своего класса.'),
-- LANG_ITEM_MAXSKILL_CONFIRM
(11537,'Your skills of defense and possession of weapons are improved to the maximum.',NULL,'Vos compétences de défense et de possession de type d\'armes sont améliorées au maximum.',NULL,NULL,NULL,NULL,NULL,'Ваши навыки защиты и владения оружием улучшены до максимума.'),
-- LANG_ITEM_REPAIR_CONFIRM
(11538,'All your equipment is repaired.',NULL,'Tout votre équipement a été réparé',NULL,NULL,NULL,NULL,NULL,'Вся ваша экипировка была подлатана!'),
-- LANG_ITEM_DESERTER_NOT_FOUND
(11539,'Aura Deserter not found!',NULL,'Le débuff Déserteur n\'est pas en cours',NULL,NULL,NULL,NULL,NULL,'Аура Дезертир не найдена!'),
-- LANG_ITEM_DESERTER_REMOVED
(11540,'Aura Deserter was successfully removed!',NULL,'Le débuff Déserteur a été retiré avec succès !',NULL,NULL,NULL,NULL,NULL,'Аура Дезертир успешно убрана!'),
-- LANG_ITEM_CHANGE_NAME
(11541,'|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|tChange name[|cffff0000100|r Arena Points]',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|tСмена имени[|cffff0000100|r Арена поинтов]'),
-- LANG_ITEM_CHANGE_OF_APPEARANCE
(11542,'|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|tChange of appearance[|cffff0000200|r Arena Points]',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|tСмена внешности [|cffff0000200|r Арена поинтов]'),
-- LANG_ITEM_CHANGE_FACTION
(11543,'|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|tChange faction[|cffff0000500|r Arena Points]',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|tСмена фракции[|cffff0000500|r Арена поинтов'),
-- LANG_ITEM_CHANGE_RACE
(11544,'|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|tChange race[|cffff0000250|r Arena Points]',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|tСмена расы[|cffff0000250|r Арена поинтов]'),
-- LANG_ITEM_RATES
(11545,'|cffD80000Rates|r',NULL,'Taux',NULL,NULL,NULL,NULL,NULL,'|cffD80000Рейты|r'),
-- LANG_ITEM_RATES_XP_KILL
(11546,'|cff660099Rates XP for kill|r x:',NULL,'|cff660099Taux d\'XP des ennemis tués|r x:',NULL,NULL,NULL,NULL,NULL,'|cff660099Рейты на опыт за убийство|r x:'),
-- LANG_ITEM_RATES_XP_QUEST
(11547,'|cff660099Rates XP for quest|r x:',NULL,'|cff660099Taux d\'XP des quêtes|r x:',NULL,NULL,NULL,NULL,NULL,'|cff660099Рейты на опыт за задания|r x:'),
-- LANG_ITEM_RATES_REP
(11548,'|cff660099Rate of reputation|r x:',NULL,'|cff660099Taux de réputation|r x:',NULL,NULL,NULL,NULL,NULL,'|cff660099Рейт репутации|r x:'),
-- LANG_ITEM_RATES_GOLD
(11549,'|cff660099Rate of gold|r x:',NULL,'|cff660099Taux d\'argent|r x:',NULL,NULL,NULL,NULL,NULL,'|cff660099Рейт золота|r x:'),
-- LANG_ITEM_RATES_HONOR
(11550,'|cff660099Rate of honor|r x:',NULL,'|cff660099Taux d\'honneur|r x:',NULL,NULL,NULL,NULL,NULL,'|cff660099Рейт Хонора|r x:'),
-- LANG_ITEM_BUY_7
(11551,'Buy VIP for [ |cffD800007|r ] Days [20 coins]',NULL,'Acheter [ |cffD800007|r ] jours de privilèges VIP pour [20 jetons]',NULL,NULL,NULL,NULL,NULL,'Купить VIP на [ |cffD800007|r ] Дней [20 Бонусов]'),
-- LANG_ITEM_BUY_14
(11552,'Buy VIP for [ |cffD8000014|r ] Days [40 coins]',NULL,'Acheter [ |cffD8000014|r ] jours de privilèges VIP pour [40 jetons]',NULL,NULL,NULL,NULL,NULL,'Купить VIP на [ |cffD8000014|r ] Дней [40 Бонусов]'),
-- LANG_ITEM_BUY_31
(11553,'Buy VIP for [ |cffD8000031|r ] Days [80 coins]',NULL,'Acheter [ |cffD8000031|r ] jours de privilèges VIP pour [80 jetons]',NULL,NULL,NULL,NULL,NULL,'Купить VIP на [ |cffD8000031|r ] День [80 Бонусов]'),
-- LANG_ITEM_BUY_7_SURE
(11554,'Are you sure you want to buy VIP time for 7 days ?',NULL,'Êtes vous sur de vouloir acheter 7 jours de privilèges VIP ?',NULL,NULL,NULL,NULL,NULL,'Вы уверены что хотите купить VIP аккаунт на 7 дней ?'),
-- LANG_ITEM_BUY_14_SURE
(11555,'Are you sure you want to buy VIP time for 14 days ?',NULL,'Êtes vous sur de vouloir acheter 14 jours de privilèges VIP ?',NULL,NULL,NULL,NULL,NULL,'Вы уверены что хотите купить VIP аккаунт на 14 дней ?'),
-- LANG_ITEM_BUY_31_SURE
(11556,'Are you sure you want to buy VIP time for 31 days ?',NULL,'Êtes vous sur de vouloir acheter 31 jours de privilèges VIP ?',NULL,NULL,NULL,NULL,NULL,'Вы уверены что хотите купить VIP аккаунт на 31 день ?'),
-- LANG_ITEM_INC_7
(11557,'Buy additional VIP time for [ |cffD800007|r ] Days [20 coins]',NULL,'Acheter [ |cffD800007|r ] jours de privilèges VIP [20 jetons]',NULL,NULL,NULL,NULL,NULL,'Увеличить время VIP привилегий на [ |cffD800007|r ] Дней [20 Бонусов]'),
-- LANG_ITEM_INC_14
(11558,'Buy additional VIP time for [ |cffD8000014|r ] Days [40 coins]',NULL,'Acheter [ |cffD8000014|r ] jours de privilèges VIP [40 jetons]',NULL,NULL,NULL,NULL,NULL,'Увеличить время VIP привилегий на [ |cffD8000014|r ] Дней [40 Бонусов]'),
-- LANG_ITEM_INC_31
(11559,'Buy additional VIP time for [ |cffD8000031|r ] Days [80 coins]',NULL,'Acheter [ |cffD8000031|r ] jours de privilèges VIP [80 jetons]',NULL,NULL,NULL,NULL,NULL,'Увеличить время VIP привилегий на [ |cffD8000031|r ] День [80 Бонусов]'),
-- LANG_ITEM_INC_7_SURE
(11560,'Are you sure you want to buy additional VIP time for 7 days ?',NULL,'Êtes-vous sûr de vouloir acheter 7 jours de privilèges VIP supplémentaire ?',NULL,NULL,NULL,NULL,NULL,'Вы уверены что хотите Увеличить время VIP привилегий на 7 дней ?'),
-- LANG_ITEM_INC_14_SURE
(11561,'Are you sure you want to buy additional VIP time for 14 days ?',NULL,'Êtes-vous sûr de vouloir acheter 14 jours de privilèges VIP supplémentaire ?',NULL,NULL,NULL,NULL,NULL,'Вы уверены что хотите Увеличить время VIP привилегий на 14 дней ?'),
-- LANG_ITEM_INC_31_SURE
(11562,'Are you sure you want to buy additional VIP time for 31 days ?',NULL,'Êtes-vous sûr de vouloir acheter 31 jours de privilèges VIP supplémentaire ?',NULL,NULL,NULL,NULL,NULL,'Вы уверены что хотите Увеличить время VIP привилегий на 31 день ?'),
-- LANG_ITEM_NOT_ENOUGH_COINS
(11563,'|cff006699Not enough coins|r',NULL,'|cff006699Pas assez de jetons|r',NULL,NULL,NULL,NULL,NULL,'|cff006699Недостаточно бонусов|r'),
-- LANG_ITEM_YOU_HAVE_COINS
(11564,'|cff006699You have: |cff00FF33%u coins|r',NULL,'|cff006699Vous avez: |cff00FF33%u jetons|r',NULL,NULL,NULL,NULL,NULL,'|cff006699У вас: |cff00FF33%u бонусов|r'),
-- LANG_ITEM_YOU_NEED_COINS
(11565,'|cff006699You need additional: |cffFF0000%u|r',NULL,'|cff006699Il vous manque: |cffFF0000%u|r',NULL,NULL,NULL,NULL,NULL,'|cff006699Нужно еще: |cffFF0000%u|r');
