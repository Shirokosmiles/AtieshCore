-- Table `creature_template`
-- UPDATE `creature_template` SET `ScriptName` = 'npc_queldelar_sunwell_plateau' WHERE (entry = 38056);
UPDATE `creature_template` SET `ScriptName` = 'npc_sunwell_warder' WHERE (entry = 37523);

-- Table `gameobject_template`
UPDATE `gameobject_template` SET `ScriptName` = 'go_dalaran_portal_sunwell' WHERE (entry = 201797);

DELETE FROM `gameobject` WHERE (id = 201797);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(9294, 201797, 580, 4075, 0, 1, 2048, 1663.81, 663.74, 28.0502, 5.55015, 0, 0, -0.358368, 0.933581, 7200, 255, 1, 0),
(9298, 201797, 580, 4075, 0, 1, 2048, 1733.57, 593.142, 28.0502, 3.49067, 0, 0, -0.984807, 0.173652, 7200, 255, 1, 0);

-- Table `item_template`
-- UPDATE `item_template` SET `ScriptName` = 'item_tainted_queldelar' WHERE `entry` IN (49879,49889);

-- Table `creature` 3 npc without condition on ended quests in location should be visible always
UPDATE `creature` SET `phaseMask` = 2049 WHERE `guid` IN (43498,121400,121399);

-- Table `creature_text` update missed texts
DELETE FROM `creature_text` WHERE CreatureID = 37781 AND `GroupID` = 5;
DELETE FROM `creature_text` WHERE CreatureID = 37765 AND `GroupID` = 6;
DELETE FROM `creature_text` WHERE CreatureID = 37765 AND `GroupID` = 7;
DELETE FROM `creature_text` WHERE CreatureID = 37763 AND `GroupID` = 8;
DELETE FROM `creature_text` WHERE CreatureID = 37763 AND `GroupID` = 9;
DELETE FROM `creature_text` WHERE CreatureID = 37765 AND `GroupID` = 10;

INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(37781, 5, 0, 'Drop your weapon and surrender, traitor.', 14, 0, 100, 1, 0, 0, 37390, 0, 'tainted_queldelar'),

(37765, 6, 0, 'This is not my doing, Rommath. There is no treachery here.', 14, 0, 100, 1, 0, 0, 37430, 0, 'tainted_queldelar'),
(37765, 7, 0, 'Call off your men. Lor\'themar\'s own foolishness caused his injuries. Quel\'Delar is not chosen; it chooses its master.', 14, 0, 100, 1, 0, 0, 37431, 0, 'tainted_queldelar'),

(37763, 8, 0, 'Guards, return to your posts.', 14, 0, 100, 1, 0, 0, 37432, 0, 'tainted_queldelar'),
(37763, 9, 0, 'You will have what you have come for, $n. Take the sword and begone. And you, Auric, have a care for what you say in this sacred place.', 14, 0, 100, 1, 0, 0, 37434, 0, 'tainted_queldelar'),

(37765, 10, 0, 'Carry the sword back to Dalaran through that portal, $n. You have done what many quel\'dorei have dreamt of for years. Quel\'Delar has been restored at last.', 14, 0, 100, 1, 0, 0, 37440, 0, 'tainted_queldelar');

-- Потертая рукоять quest texts
DELETE FROM `quest_greeting` WHERE (id = 14443);
DELETE FROM `quest_greeting_locale` WHERE (id = 14443);
DELETE FROM `quest_request_items` WHERE (id = 14443);
DELETE FROM `quest_request_items_locale` WHERE (id = 14443);
DELETE FROM `quest_offer_reward` WHERE (id = 14443);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 14443);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(14443, 0, 0, 0, 'This battered old sword hilt has seen better days. Before the hilt was snapped from the blade, it must\'ve been a magnificent example of the blacksmith\'s art.

The graceful symbols and exotic gemstones decorating the hilt suggest that the weapon may have belonged to a powerful person. Surely, the Silver Covenant members would be interested in hearing about the recovery of such an artifact. Seek out their representative at Quel\'Delar\'s Rest, south of the Argent Tournament Grounds.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(14443, 0, 'ruRU', 'Эта потертая рукоять меча знавала лучшие дни, но даже сейчас по ней можно сказать, что делал ее настоящий мастер.

Изящная гравировка и инкрустация драгоценными камнями свидетельствует о том, что оружие некогда принадлежало знатному человеку. Серебряный Союз наверняка заинтересуется этой находкой. Найдите его представителя в покое Кель\'Делара, он находится к югу от ристалища Серебряного турнира.', 0);

-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(14443, 1, 0, 'What is it that you have there?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(14443, 'ruRU', 'Что это у тебя?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(14443, 0, 0, 0, 0, 0, 0, 0, 0, '<Caladis takes the hilt from you and slowly turns it over in his hands.>

This seems somehow familiar, as though I should know its origins. You say you recovered this in the citadel? Most intriguing.

There are few who possess the ability to make such a blade. Perhaps they can tell us something about your find.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(14443, 'ruRU', '<Каладис бережно забирает у вас рукоять и осматривает ее со всех сторон.>

Что-то знакомое видится мне в этой вещи... как будто я знаю, откуда она могла взяться. Говоришь, нашел ее в цитадели? Очень интересно.

Мало осталось кузнецов, способных выковать подобный клинок, но, возможно, они прольют свет на тайну твоей находки.', 0);


-- То, что знают драконы
DELETE FROM `quest_greeting` WHERE (id = 14444);
DELETE FROM `quest_greeting_locale` WHERE (id = 14444);
DELETE FROM `quest_offer_reward` WHERE (id = 14444);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 14444);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(14444, 0, 0, 0, 'There\'s no mistaking it - this hilt comes from a powerful, ancient weapon, but which one? I do not recall seeing or hearing of a sword with these markings, but that doesn\'t mean that all is lost.

Korialstrasz, better known as Krasus, has long been a friend to the quel\'dorei and the Kirin Tor. With his vast knowledge and resources, he\'s certain to know something. Travel to the top of Wyrmrest Temple and seek his counsel, then report to Arcanist Tybalin inside the Silver Enclave in Dalaran.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(14444, 0, 'ruRU', 'Ошибки быть не может – это рукоять могущественного древнего клинка. Вот только что это был за клинок? Я не могу вспомнить ни одного меча с такой гравировкой, но не все еще потеряно.

Мы должны обратиться к Кориалстразу, более известному тебе как Крас. Он – давний друг кель\'дорай и Кирин-Тора. За его плечами мудрость рода красных драконов; наверняка, он сможет нам помочь. Отправляйся за его советом на вершину Храма Драконьего Покоя.', 0);


-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(14444, 0, 0, 0, 0, 0, 0, 0, 0, 'We can\'t let that book remain in Sunreaver hands. If we hope to identify the sword and use it to our advantage, we have to find a way to capture the book Krasus lent them.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(14444, 'ruRU', 'Нельзя допустить, чтобы книга осталась в руках Похитителей Солнца. Если мы рассчитываем опознать этот меч и использовать его в наших целях, надо найти способ перехватить книгу, которую одолжил им Крас.', 0);

-- UPDATE `quest_template` SET `POIContinent` = 0, `POIx` = 0, `POIy` = 0, `POIPriority` = 0 WHERE `ID` = 14444;
UPDATE `quest_poi_points` SET `X` = 5747, `Y` = 723, `VerifiedBuild` = 0 WHERE `QuestID` = 14444;




-- План Похитителей Солнца quest texts
DELETE FROM `quest_greeting` WHERE (id = 14457);
DELETE FROM `quest_greeting_locale` WHERE (id = 14457);
DELETE FROM `quest_request_items` WHERE (id = 14457);
DELETE FROM `quest_request_items_locale` WHERE (id = 14457);
DELETE FROM `quest_offer_reward` WHERE (id = 14457);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 14457);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(14457, 0, 0, 0, 'One of my contacts in the Underbelly caught sight of a Sunreaver agent buying reagents from a dealer in the Black Market area. The Sunreavers normally aren\'t known for their interest in what goes on in the sewers, so that\'s a big indication they\'re planning something.

Head into the Underbelly, find this Sunreaver agent, and take care of them. Search the body for any information that might give us a lead on the location of that tome from Wyrmrest. We can\'t let them get it back to Icecrown first.
Progress', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(14457, 0, 'ruRU', 'Один из моих агентов в Клоаке заметил там посланника Похитителей Солнца... которые, как ты понимаешь, редко проявляют интерес к тому, что творится в канализации. А этот покупал реагенты у продавца с Черного рынка. Несомненно, они что-то затевают.

Отправляйся в Клоаку, найди этого типа из Похитителей Солнца и разберись с ним. Обыщи тело – может быть, у него найдется информация о местонахождении той книги из храма Драконьего Покоя. Нельзя допустить, чтобы она оказалась в Ледяной Короне.', 0);

-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(14457, 1, 0, 'Did you find anything of use on that agent?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(14457, 'ruRU', 'Ну что, у этого агента было с собой что-нибудь полезное?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(14457, 0, 0, 0, 0, 0, 0, 0, 0, '<Arcanist Tybalin examines the captured orders.>

The agent you intercepted was supposed to transport the Wyrmrest Tome to Icecrown, after meeting with one Magister Hathorel in Sunreaver\'s Sanctuary. We have to get that book, <name>, and this is our chance. It\'s not going to be easy, though.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(14457, 'ruRU', '<Чародей Тибалин изучает перехваченные приказы.>

Убитый тобой агент должен был доставить книгу из Храма Драконьего Покоя в Ледяную Корону, но сначала он собирался забрать ее у магистра Хатореля в Прибежище Похитителя Солнца. Это наш шанс перехватить книгу, Крастир! Хотя это будет непросто...', 0);

UPDATE `quest_poi_points` SET `X` = 5747, `Y` = 723, `VerifiedBuild` = 0 WHERE `QuestID` = 14457 AND `Idx1` = 1 AND `Idx2` = 0;
UPDATE `quest_poi_points` SET `X` = 5917, `Y` = 558, `VerifiedBuild` = 0 WHERE `QuestID` = 14457 AND `Idx1` = 2 AND `Idx2` = 0;





-- Подходящая маскировка quest texts
DELETE FROM `quest_greeting` WHERE (id = 20438);
DELETE FROM `quest_greeting_locale` WHERE (id = 20438);
DELETE FROM `quest_request_items` WHERE (id = 20438);
DELETE FROM `quest_request_items_locale` WHERE (id = 20438);
DELETE FROM `quest_offer_reward` WHERE (id = 20438);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 20438);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(20438, 0, 0, 0, 'Getting you inside the Sunreaver\'s Sanctuary will be tougher than it appears. Only those who possess Sunreaver tabards are permitted entry to sanctuary. If we can get our hands on one, a simple enchantment will do the rest of the work.

On the balcony above Threads of Fate, you\'ll find Shandy Glossgleam. I\'ve helped him a few times in the past, so he owes me a favor. He handles laundry for a wide variety of people in the city. Maybe he can find a way to \'lend\' you a tabard for a while.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(20438, 0, 'ruRU', 'Заслать тебя в Прибежище Похитителя Солнца будет нелегко. Туда допускаются только обладатели гербовых накидок Похитителей Солнца. Если бы нам только удалось заполучить одну из них, остальное можно было бы решить с помощью пары заклинаний.

Но у меня есть идея! На балконе над "Нитями судьбы" стоит некто Шанди Шикблеск. Я его пару раз выручал в прошлом, так что он задолжал мне ответную услугу. Он стирает одежду многих граждан этого города. Может быть, он согласится одолжить тебе гербовую накидку...', 0);

-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(20438, 1, 0, 'Was Shandy able to help you get a Sunreaver tabard?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(20438, 'ruRU', 'Ну что, Шанди помог тебе добыть гербовую накидку?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(20438, 0, 0, 0, 0, 0, 0, 0, 0, 'I knew Shandy would find a way to come through for us. Let me get this enchanted and ready for you to use. The sooner you get done with the tabard, the sooner we can get it back to Shandy and the better the chances that its owner will never have missed it.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(20438, 'ruRU', 'Я так и знал, что Шанди найдет выход из ситуации. Сейчас я наложу чары на эту накидку, и ты сможешь ее примерить. Чем быстрее ты вернешься, тем быстрее мы отдадим ее обратно Шанди. Возможно, за это время ее владелец не успеет хватиться своей гербовой накидки.', 0);

UPDATE `quest_poi_points` SET `X` = 5747, `Y` = 723, `VerifiedBuild` = 0 WHERE `QuestID` = 20438 AND `Idx1` = 1 AND `Idx2` = 0;
UPDATE `quest_poi_points` SET `X` = 5799, `Y` = 692, `VerifiedBuild` = 0 WHERE `QuestID` = 20438 AND `Idx1` = 2 AND `Idx2` = 0;





-- Встреча с магистром Хаторелем quest texts
DELETE FROM `quest_greeting` WHERE (id = 20439);
DELETE FROM `quest_greeting_locale` WHERE (id = 20439);
DELETE FROM `quest_request_items` WHERE (id = 20439);
DELETE FROM `quest_request_items_locale` WHERE (id = 20439);
DELETE FROM `quest_offer_reward` WHERE (id = 20439);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 20439);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(20439, 0, 0, 0, 'I\'ve placed an enchantment on the tabard that should allow you to slip past the Sunreaver Sanctuary\'s defenses for a short period of time. You should have enough time to find your way into The Filthy Animal and meet up with the Sunreaver contact there, one Magister Hathorel.

Obtain the copy of Ancient Dragonforged Blades that his men borrowed from Wyrmrest while your disguise holds, and return it to me.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(20439, 0, 'ruRU', 'Я зачаровал эту гербовую накидку особым заклинанием, которое позволит тебе пробраться мимо охранников Прибежища Похитителя Солнца. Оно будет действовать недолго, но за это время ты <должен/должна> успеть найти бар "Грязное животное" и встретиться там с представителем Похитителей Солнца, этим магистром Хаторелем.

Возьми у него копию "Древних клинков драконьей ковки", которую его люди одолжили в Храме Драконьего Покоя, и сразу же возвращайся ко мне.', 0);

-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(20439, 1, 0, 'Have you recovered that book?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(20439, 'ruRU', 'Книга у тебя?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(20439, 0, 0, 0, 0, 0, 0, 0, 0, 'Excellent work. Now that this is in our hands, we must get it to Caladis Brightspear as soon as possible. We can\'t risk the book falling back into Sunreaver hands.

I\'ll ensure that Shandy Glossgleam gets his tabard back without incident, along with a healthy reward for his help.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(20439, 'ruRU', 'Превосходно! Теперь, когда книга в наших руках, мы должны как можно скорее доставить ее Каладису Сияющему Копью. Нельзя допустить, чтобы она снова оказалась у Похитителей Солнца.

А я позабочусь о том, чтобы Шанди Шикблеск получил обратно свою накидку и солидную награду за помощь.', 0);

DELETE FROM `quest_poi` WHERE (QuestID = 20439);
DELETE FROM `quest_poi_points` WHERE (QuestID = 20439);

INSERT INTO `quest_poi` (`QuestID`, `id`, `ObjectiveIndex`, `MapID`, `WorldMapAreaId`, `Floor`, `Priority`, `Flags`, `VerifiedBuild`) VALUES 
(20439, 1, -1, 571, 504, 1, 0, 3, 0),
(20439, 2, 4, 571, 504, 1, 0, 3, 0);

INSERT INTO `quest_poi_points` (`QuestID`, `Idx1`, `Idx2`, `X`, `Y`, `VerifiedBuild`) VALUES 
(20439, 1, 0, 5747, 724, 0),
(20439, 2, 0, 5888, 509, 0);





-- Возвращение к Каладису Сияющему Копью. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24454);
DELETE FROM `quest_greeting_locale` WHERE (id = 24454);
DELETE FROM `quest_request_items` WHERE (id = 24454);
DELETE FROM `quest_request_items_locale` WHERE (id = 24454);
DELETE FROM `quest_offer_reward` WHERE (id = 24454);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24454);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24454, 0, 0, 0, 'We must get this book to Caladis Brightspear immediately. Would you bring it to him? I cannot rely on anyone else to transport the book and you have proven adept at keeping the Sunreavers at bay.

Take it with you to Quel\'Delar\'s rest, south of the Argent Tournament Grounds in Icecrown. Caladis and the sword will be waiting. The sooner we can identify the blade, the sooner we can claim it.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24454, 0, 'ruRU', 'Эту книгу надо немедленно отнести Каладису Сияющему Копью. Ты этим займешься? Никому другому я не могу доверить столь ценную ношу, а ты уже <доказал/доказала> свою верность, обхитрив Похитителей Солнца.

Твой путь лежит в Покой Кель\'Делара, что на юге от ристалища Серебряного Турнира в Ледяной Короне. Каладис будет ждать тебя вместе с мечом. Чем быстрее мы сможем распознать этот клинок, тем скорее сможем им овладеть.', 0);

-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24454, 1, 0, 'We\'ve been expecting your return. What has kept you?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24454, 'ruRU', 'Мы ожидали твоего возвращения. С чем ты прибыл?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24454, 0, 0, 0, 0, 0, 0, 0, 0, '<Caladis accepts the heavy book and begins leafing through it.>

I knew the symbols on the blade were familiar. The weapon was most certainly forged by the dragons and gifted to one of the mortal races, but which blade is this, and how did it come to rest in Icecrown?', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24454, 'ruRU', '<Каладис забирает у вас тяжелую книгу и начинает внимательно ее пролистывать.>

Ах вот почему символы на рукояти казались мне такими знакомыми... Да, этот меч был точно выкован драконами и передан в дар смертным, но что это был за клинок и как он оказался в Ледяной Короне?', 0);




-- Перековать меч. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24461);
DELETE FROM `quest_greeting_locale` WHERE (id = 24461);
DELETE FROM `quest_request_items` WHERE (id = 24461);
DELETE FROM `quest_request_items_locale` WHERE (id = 24461);
DELETE FROM `quest_offer_reward` WHERE (id = 24461);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24461);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24461, 0, 0, 0, 'We cannot allow Quel\'Delar to remain broken and disgraced. Take the remnants of the sword, along with the battered hilt you discovered, and venture into the Pit of Saron within Icecrown Citadel.

In the pit, the Lich King uses slaves to mine, process, and transform saronite ore. This infused saronite is what we will use to rebuild Quel\'Delar.

You must gather bars of infused saronite and capture the forgemaster\'s hammer, then bring them to the forgemaster\'s anvil and reforge the sword.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24461, 0, 'ruRU', 'Нельзя допустить, чтобы великий Кель\'Делар оставался расколотым и обесчещенным. Возьми фрагменты клинка вместе с потертой рукоятью и отправляйся в Яму Сарона, что в цитадели Ледяной Короны.

В этой яме слуги Короля-лича добывают и обрабатывают саронитовую руду. Только с помощью заряженного саронита можно перековать Кель\'Делар.

Ты <должен/должна> собрать саронитовые слитки и перековать меч, воспользовавшись молотом и наковальней начальника кузни.', 0);

-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24461, 1, 0, 'Were you able to reconstruct Quel\'Delar?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24461, 'ruRU', 'Тебе удалось воссоздать Кель\'Делар?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24461, 0, 0, 0, 0, 0, 0, 0, 0, 'You have remade the blade of Quel\'Delar, although Blood-Queen Lana\'thel proclaimed we could not! The blade must still be tempered, but she and her master will not stand in our way!', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24461, 'ruRU', 'Тебе удалось воссоздать Кель\'Делар вопреки предсказаниям королевы Лана\'тель! Да, клинок еще надо закалить... но она и ее повелитель больше не станут у нас на пути!', 0);



-- Закалить клинок. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24476);
DELETE FROM `quest_greeting_locale` WHERE (id = 24476);
DELETE FROM `quest_request_items` WHERE (id = 24476);
DELETE FROM `quest_request_items_locale` WHERE (id = 24476);
DELETE FROM `quest_offer_reward` WHERE (id = 24476);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24476);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24476, 0, 0, 0, 'At last, the pieces of Quel\'Delar are rejoined and the blade is whole, but it cannot see battle until you have tempered it. That jagged saronite edge is brittle and will shatter the moment it strikes anything.

Deep in Icecrown Citadel\'s Forge of Souls is a place where the blade can safely be tempered. Take Quel\'Delar with you to the abode of the Devourer of Souls and look for the crucible. Plunge the blade into the crucible to temper it and bring it back to me in The Frozen Halls.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24476, 0, 'ruRU', 'Наконец-то фрагменты Кель\'Делара воссоединились, и клинок снова стал целым. Но он еще не готов к битве, ибо для начала его надо закалить. Эти саронитовые зубцы очень хрупкие и могут отколоться в момент удара.

Но глубоко под цитаделью Ледяной Короны есть Кузня Душ, в которой можно закалить подобный клинок. Отнеси Кель\'Делар в обитель Пожирателя Душ и найди там горнило душ. Закали меч и принеси его мне. Я буду ждать тебя в Ледяных залах.', 0);

-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24476, 1, 0, 'Until the sword is tempered, it will be useless.', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24476, 'ruRU', 'Пока клинок не будет закален, он бесполезен.', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24476, 0, 0, 0, 0, 0, 0, 0, 0, 'I... I don\'t understand. Tempering the sword should\'ve restored the blade to its original condition. What has happened here?', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24476, 'ruRU', 'Я... ничего не понимаю. После закалки клинок должен был обрести свое былое могущество. В чем же дело?', 0);





-- Залы Отражений. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24480);
DELETE FROM `quest_greeting_locale` WHERE (id = 24480);
DELETE FROM `quest_request_items` WHERE (id = 24480);
DELETE FROM `quest_request_items_locale` WHERE (id = 24480);
DELETE FROM `quest_offer_reward` WHERE (id = 24480);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24480);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24480, 0, 0, 0, 'You have reforged and tempered the sword, yet it sits quietly in its sheath, showing no signs of the power it should possess. You say the sword pulls you, as though it possesses a will?

Dare you bring it where it wishes to go? It\'s not right that the sword should be this silent and this insistent, yet I fear that if you do not take the sword to its destination, we will never learn why. Take it into Icecrown Citadel\'s Halls of Reflection, but be on your guard! I\'ll be waiting for you in The Frozen Halls.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24480, 0, 'ruRU', 'Ты <перековал и закалил/перековала и закалила> клинок, но я не чувствую в нем былой силы. Правильно ли я понял, что клинок побуждает тебя к действию, словно он обладает собственной волей?

Осмелишься ли последовать его зову? Негоже великому мечу ржаветь в ножнах. Я боюсь, что мы никогда не узнаем его тайн, если не последуем велению его судьбы. Отнеси его в Залы Отражений, что в цитадели Ледяной Короны, но будь <готов/готова> ко всему. Я буду ждать твоего возвращения в Ледяных залах.', 0);

-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24480, 1, 0, 'What happened inside the Halls of Reflection?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24480, 'ruRU', 'Что произошло в Залах Отражений?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24480, 0, 0, 0, 0, 0, 0, 0, 0, 'I had not thought it possible for evil to take hold in such a sword, but I suppose it was naive of me. If the greatest of dragonkind\'s creations could be corrupted and turned against them, why not a mere sword?

Uther\'s advice is wise, <name>, and I would urge you to heed it quickly.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24480, 'ruRU', 'Я и не подозревал, что зло могло пустить корни в столь великом клинке, но это была наивная ошибка с моей стороны. Если даже самые могущественные представители рода драконов пали жертвами скверны, что уж говорить о простом оружии?

Утер дал тебе мудрый совет, Только, и ты должен немедленно ему последовать.', 0);





-- Путешествие к Солнечному Колодцу. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24522);
DELETE FROM `quest_greeting_locale` WHERE (id = 24522);
DELETE FROM `quest_request_items` WHERE (id = 24522);
DELETE FROM `quest_request_items_locale` WHERE (id = 24522);
DELETE FROM `quest_offer_reward` WHERE (id = 24522);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24522);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24522, 0, 0, 0, 'Take Quel\'Delar to the Sunwell as quickly as possible, <name>. Trust in Uther\'s words when he says that you will not always be able to control the blade while it is subject to the evil of the Lich King\'s influence. You must travel to the Isle of Quel\'Danas, and there, seek entry to the Sunwell itself, where you can cleanse the sword.

The guardians of the Sunwell will not simply allow you to walk in, so you must find Halduron Brightwing, who will be inspecting the guards there.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24522, 0, 'ruRU', 'Как можно быстрее отнеси Кель\'Делар к Солнечному Колодцу! Мы должны поверить словам Утера о том, что оскверненный могуществом Короля-лича клинок не всегда будет тебе подвластен. Ты <должен/должна> отправиться на Остров Кель\'Данас и найти вход в сам Солнечный Колодец. Только он обладает силой очистить меч.

Учти, что стражники Солнечного Колодца не позволят тебе пройти без разрешения, поэтому тебе придется заручиться поддержкой Халдарона Светлого Крыла, начальника охраны.', 0);

-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24522, 1, 0, 'What brings you here?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24522, 'ruRU', 'Что привело тебя сюда?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24522, 0, 0, 0, 0, 0, 0, 0, 0, 'Admit you to the Sunwell? That\'s impossible! The Sunwell is the most sacred and important site of our people. We have only recently reclaimed it with the help of the Shattered Sun Offensive. It is not a place for tourists or travelers.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24522, 'ruRU', 'Пропустить тебя в Солнечный Колодец? Это невозможно! Это самое священное и важное место для нашего народа. И мы только недавно смогли вернуть его себе при помощи Армии Расколотого Солнца. Здесь не место туристам и путешественникам.', 0);






-- Талориен Искатель Рассвета. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24535);
DELETE FROM `quest_greeting_locale` WHERE (id = 24535);
DELETE FROM `quest_request_items` WHERE (id = 24535);
DELETE FROM `quest_request_items_locale` WHERE (id = 24535);
DELETE FROM `quest_offer_reward` WHERE (id = 24535);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24535);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24535, 0, 0, 0, 'If you truly bear Quel\'Delar, <name>, I might be able to admit you to the Sunwell. If you know the blade\'s history, you recall that it was borne by Thalorien Dawnseeker in defense of the Sunwell against the Scourge. He fell in what is now the Dead Scar, buying time for his men to make their own preparations. You will find his remains near the southern end of the Dead Scar on this isle. Visit them, and if his spirit gives you its blessing, I will allow you to enter the Sunwell.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24535, 0, 'ruRU', 'Если Кель\'Делар действительно у тебя, <имя>, я, возможно, смогу пропустить тебя в Солнечный Колодец. Как ты помнишь, этим мечом когда-то сражался Талориен Искатель Рассвета, защищая Колодец от Плети. Талориен пал на том месте, которое мы сейчас называем Тропой Мертвых. Ценой своей жизни он выиграл время, необходимое для того, чтобы его люди сумели подготовиться и встретить врага во всеоружии. Останки Талориена покоятся на этом острове в южном конце Тропы. Наведайся туда, и, если дух героя благословит тебя, я разрешу тебе пройти в Солнечный Колодец.', 0);

-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24535, 1, 0, 'What brings you here?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24535, 'ruRU', 'Что привело тебя сюда?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24535, 0, 0, 0, 0, 0, 0, 0, 0, 'I confess that I did not expect Thalorien\'s spirit to recognize you as the heir to Quel\'Delar, but I defer to his judgment. You may enter the Sunwell, but I remind you that you are a guest in our most sacred of precincts, and you should act accordingly.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24535, 'ruRU', 'Честно говоря, я не ожидал, что дух Талориена признает в тебе наследного владельца Кель\'Делара, но я склоняю голову перед его решением. Дорога в Солнечный Колодец свободна для тебя. Но помни: эти земли для нас святые, и ты, наш гость, должен вести себя подобающим образом.', 0);




-- Очищение Кель'Делара. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24595);
DELETE FROM `quest_greeting_locale` WHERE (id = 24595);
DELETE FROM `quest_request_items` WHERE (id = 24595);
DELETE FROM `quest_request_items_locale` WHERE (id = 24595);
DELETE FROM `quest_offer_reward` WHERE (id = 24595);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24595);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24595, 0, 0, 0, 'I admit, I was skeptical that you had actually re-forged Quel\'Delar and I did not expect Thalorien\'s spirit to reveal itself to you. You cannot understand what it means to my people that Quel\'Delar has been recovered.

As promised, I will admit you to the Sunwell and you will find the leaders of Silvermoon within. Carry the sword to the chamber of the Sunwell and immerse it. Once the blade is restored, return with it to Caladis Brightspear at Quel\'Delar\'s Rest.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24595, 0, 'ruRU', 'Признаюсь, я сомневался в том, что тебе удалось перековать Кель\'Делар и что дух Талориена удостоит тебя вниманием. Ты не представляешь, что означает для меня и моего народа возвращение легендарного меча.

Как и было обещано, я разрешаю тебе пройти к Солнечному Колодцу и встретиться с властителями Луносвета. Погрузи меч в Солнечный Колодец. После очищения его сила будет навеки связана с тобой. Затем отнеси меч Каладису Сияющему Копью в Покой Кель\'Делара.', 0);

-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24595, 1, 0, 'Tell me of what happened in the Sunwell, $n.', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24595, 'ruRU', 'Расскажи мне, что произошло в Солнечном колодце, $n.', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24595, 0, 0, 0, 0, 0, 0, 0, 0, 'This is unbelievable, $n. You\'ve really done it! All of the quel\'dorei have heard of Thalorien Dawnseeker and Quel\'Delar, but no one ever thought the sword would be restored.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24595, 'ruRU', 'This is unbelievable, $n. You\'ve really done it! All of the quel\'dorei have heard of Thalorien Dawnseeker and Quel\'Delar, but no one ever thought the sword would be restored.', 0);





-- Победа Серебряного Союза. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24795);
DELETE FROM `quest_greeting_locale` WHERE (id = 24795);
DELETE FROM `quest_request_items` WHERE (id = 24795);
DELETE FROM `quest_request_items_locale` WHERE (id = 24795);
DELETE FROM `quest_offer_reward` WHERE (id = 24795);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24795);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24795, 0, 0, 0, 'In spite of Queen Lana\'thel\'s boasting, you have restored Quel\'Delar, $n. Long have we dreamt of reclaiming Quel\'Delar.

The Silver Covenant, and indeed all quel\'dorei owe you a debt of gratitude.

As a $c, the sword seems to know you lack the training to wield it and hasn\'t bonded to you. Where, then, will its next master come from? Perhaps the Argent Crusade can find one. Go north to the Argent Tournament Grounds and present the sword to Justicar Mariel Trueheart on behalf of the Silver Covenant.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24795, 0, 'ruRU', 'Несмотря на дерзкие слова королевы Лана\'тель, тебе удалось восстановить Кель\'Делар. О, $n, как же долго мы ждали этого момента!

Серебряный Союз и все кель\'дорай у тебя в неоплатном долгу.

Увы, клинок почувствовал, что ты <неопытен/неопытна> в обращении с мечами, и потому не связал с тобой свою силу. Кто же станет его истинным хозяином? Только Серебряный Авангард сможет это определить. Отправляйся к ристалищу Серебряного турнира и передай этот клинок вершительнице правосудия Мариэль Чистосердечной.', 0);

-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24795, 1, 0, 'Is it true that you have restored Quel\'Delar?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24795, 'ruRU', 'Это и правда восстановленный Кель\'Делар?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24795, 0, 0, 0, 0, 0, 0, 0, 0, 'That a weapon of such power has been redeemed from the clutches of evil is a great omen in these times, $n. With Quel\'Delar and staunch Silver Covenant allies at our side, the Lich King will have good reason to fear.

The crusade maintains an arsenal of exceptional weapons for our strongest allies. Allow me to offer you your choice from among them in return for entrusting us with the care of Quel\'Delar.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24795, 'ruRU', 'То, что оружие такой силы было вырвано из лап зла, является великим предзнаименованием в эти времена, $n. С Кель\'Деларом и верными союзниками у Короля Лича есть веские причины бояться.

Серебряный союз обладает арсеналом исключительного оружия для наших самых сильных союзников. Позвольте мне предложить вам выбрать из них в обмен на то, что вы доверите нам заботу о Кел\'Деларе.', 0);



-- HORDE quests
-- Потертая рукоять. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24554);
DELETE FROM `quest_greeting_locale` WHERE (id = 24554);
DELETE FROM `quest_request_items` WHERE (id = 24554);
DELETE FROM `quest_request_items_locale` WHERE (id = 24554);
DELETE FROM `quest_offer_reward` WHERE (id = 24554);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24554);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24554, 0, 0, 0, 'This battered old sword hilt has seen better days. Before the hilt was snapped from the blade, it must\'ve been a magnificent example of the blacksmith\'s art.

The graceful symbols and exotic gemstones decorating the hilt suggest that the weapon may have belonged to a powerful person. Surely, the Sunreavers would be interested in hearing about the recovery of such an artifact. Seek out their representatives at Quel\'Delar\'s Rest, to the south of the Argent Tournament Grounds.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24554, 0, 'ruRU', 'Эта потертая рукоять меча знавала лучшие дни, но даже сейчас по ней можно сказать, что делал ее настоящий мастер.

Изящная гравировка и инкрустация драгоценными камнями свидетельствует о том, что оружие некогда принадлежало знатному человеку. Похитителей Солнца наверняка заинтересует эта находка. Найдите их представителя в Покое Кель\'Делара к югу от ристалища Серебряного Турнира.', 0);

-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24554, 1, 0, 'What have you discovered?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24554, 'ruRU', 'Что ты обнаружил?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24554, 0, 0, 0, 0, 0, 0, 0, 0, '<Myralion takes the hilt from you and scrutinizes the artifact.>

This came from the citadel? What was it doing there? This blade is certainly not of Scourge manufacture.

Weapons of this quality can only be crafted by a few of Azeroth\'s creatures. We will have to consult them and see if they can help us identify it.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24554, 'ruRU', '<Миралий принимает рукоять из ваших рук и внимательно ее изучает.>

Говоришь, это было в цитадели? Как эта рукоять могла там оказаться? Этот меч не мог быть сделан руками Плети.

Лишь немногие обитатели Азерота способны создать оружие такого качества. Мы должны обратиться к ним за советом.', 0);





-- Потертая рукоять. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24555);
DELETE FROM `quest_greeting_locale` WHERE (id = 24555);
DELETE FROM `quest_offer_reward` WHERE (id = 24555);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24555);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24555, 0, 0, 0, 'There\'s no mistaking it - this hilt comes from a powerful, ancient weapon, but which one? I do not recognize these particular markings, but we haven\'t hit a dead end yet.

Korialstrasz, better known as Krasus, has long been a friend to the quel\'dorei and the Kirin Tor. With his vast knowledge and resources, he\'s certain to know something. Travel to the top of Wyrmrest Temple and seek his counsel, then report to Magister Hathorel inside Sunreaver\'s Sanctuary in Dalaran.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24555, 0, 'ruRU', 'Ошибки быть не может – это рукоять могущественного древнего клинка. Вот только что это был за клинок? Я не могу вспомнить ни одного меча с такой гравировкой, но не все еще потеряно.

Мы должны обратиться к Кориалстразу, более известному тебе как Крас. Он – давний друг кель\'дорай и Кирин-Тора. За его плечами мудрость рода красных драконов; наверняка, он сможет нам помочь. Отправляйся за его советом на вершину Храма Драконьего Покоя, после чего поговори с Магистром Хаторелем в даларанском Прибежище Похитителя Солнца.', 0);


-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24555, 0, 0, 0, 0, 0, 0, 0, 0, 'We must recover that book from the Silver Covenant. Without that book from Krasus, we stand little chance of solving the mystery of the sword in Icecrown or unlocking its power.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24555, 'ruRU', 'Мы должны забрать книгу Краса из рук Серебряного союза. Без нее нам никогда не разгадать тайну клинка и не узнать его подлинной силы.', 0);

UPDATE `quest_poi_points` SET `X` = 5895, `Y` = 471, `VerifiedBuild` = 0 WHERE `QuestID` = 24555 AND `Idx1` = 0 AND `Idx2` = 0;


-- Планы Серебряного Союза. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24557);
DELETE FROM `quest_greeting_locale` WHERE (id = 24557);
DELETE FROM `quest_request_items` WHERE (id = 24557);
DELETE FROM `quest_request_items_locale` WHERE (id = 24557);
DELETE FROM `quest_offer_reward` WHERE (id = 24557);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24557);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24557, 0, 0, 0, 'One of my contacts in the Underbelly caught sight of a Silver Covenant agent gathering information at the Cantrips and Crows Tavern. Silver Covenant members aren\'t normally found in the sewers, so they must be plotting something.

Go into the Underbelly, find this Silver Covenant agent, and eliminate him. Search the body for any information that might give us a lead on the location of that tome from Wyrmrest. We can\'t let those simpering Silver Covenant weaklings get it back to Icecrown before we do.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24557, 0, 'ruRU', 'Один из моих шпионов в Клоаке заметил представителя Серебряного Союза, которые, как ты понимаешь, редко проявляют интерес к тому, что творится в канализации. А этот околачивался вокруг таверны "Ведьма ворон". Несомненно, они что-то затевают.

Отправляйся в Клоаку, найди этого прихвостня Серебряного Союза и разберись с ним. Обыщи его тело – может быть, у него найдется информация о местонахождении той книги из Храма Драконьего Покоя. Нельзя допустить, чтобы она оказалась в Ледяной Короне.', 0);


-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24557, 1, 0, 'Did you find anything of use on that agent?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24557, 'ruRU', 'Ну что, у этого агента было с собой что-нибудь полезное?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24557, 0, 0, 0, 0, 0, 0, 0, 0, '<Magister Hathorel reads the captured orders.>

The agent you intercepted was supposed to deliver the Wyrmrest tome to Icecrown, after meeting with one Arcanist Tybalin inside the Silver Enclave. We have to reclaim that book, <name>, and we only have one chance before it leaves the city. We have to work quickly.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24557, 'ruRU', '<Магистр Хаторель изучает перехваченные приказы.>

Убитый тобой агент должен был доставить книгу из Храма Драконьего Покоя в Ледяную Корону, но сначала он собирался забрать ее у чародея Тибалина в Серебряном Анклаве. Это наш шанс перехватить книгу, Волторин! И мы должны действовать быстро...', 0);

UPDATE `quest_poi_points` SET `X` = 5895, `Y` = 471, `VerifiedBuild` = 0 WHERE `QuestID` = 24557 AND `Idx1` = 1 AND `Idx2` = 0;
UPDATE `quest_poi_points` SET `X` = 5761, `Y` = 714, `VerifiedBuild` = 0 WHERE `QuestID` = 24557 AND `Idx1` = 2 AND `Idx2` = 0;





-- Подходящая маскировка. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24556);
DELETE FROM `quest_greeting_locale` WHERE (id = 24556);
DELETE FROM `quest_request_items` WHERE (id = 24556);
DELETE FROM `quest_request_items_locale` WHERE (id = 24556);
DELETE FROM `quest_offer_reward` WHERE (id = 24556);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24556);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24556, 0, 0, 0, 'Getting you inside the Silver Enclave will be tougher than it appears. Only those who possess Silver Covenant tabards are permitted entry to sanctuary. If we can get our hands on one, a simple enchantment will do the rest of the work.

On the balcony above Threads of Fate, you\'ll find Shandy Glossgleam. I\'ve helped him a few times in the past, so he owes me a favor. He handles laundry for a wide variety of people in the city. Maybe he can find a way to \'lend\' you a tabard for a while.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24556, 0, 'ruRU', 'Заслать тебя в Серебряный Анклав будет нелегко. Туда допускаются только обладатели гербовых накидок Серебряного Союза. Если бы нам только удалось заполучить одну из них, остальное можно было бы решить с помощью пары заклинаний.

Но у меня есть идея! На балконе над "Нитями судьбы" стоит некто Шанди Шикблеск. Я его пару раз выручал в прошлом, так что он задолжал мне ответную услугу. Он стирает одежду многих граждан этого города. Может быть, он согласится одолжить тебе гербовую накидку...', 0);


-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24556, 1, 0, 'Was Shandy able to help you get a Silver Covenant tabard?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24556, 'ruRU', 'Ну что, Шанди помог тебе добыть гербовую накидку Серебряного союза?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24556, 0, 0, 0, 0, 0, 0, 0, 0, 'I knew Shandy would find a way to make it work. Let me get this enchanted and ready for you to use. With any luck, the tabard\'s owner won\'t even know it\'s missing and Shandy will cover the rest of our tracks.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24556, 'ruRU', 'Я так и знал, что Шанди найдет выход из ситуации. Сейчас я наложу чары на эту накидку, и ты сможешь ее примерить. Чем быстрее ты вернешься, тем быстрее мы отдадим ее обратно Шанди. Возможно, за это время ее владелец не успеет хватиться своей гербовой накидки.', 0);

UPDATE `quest_poi_points` SET `X` = 5895, `Y` = 471, `VerifiedBuild` = 0 WHERE `QuestID` = 24556 AND `Idx1` = 1 AND `Idx2` = 0;
UPDATE `quest_poi_points` SET `X` = 5799, `Y` = 692, `VerifiedBuild` = 0 WHERE `QuestID` = 24556 AND `Idx1` = 2 AND `Idx2` = 0;



-- Встреча с чародеем. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24451);
DELETE FROM `quest_greeting_locale` WHERE (id = 24451);
DELETE FROM `quest_request_items` WHERE (id = 24451);
DELETE FROM `quest_request_items_locale` WHERE (id = 24451);
DELETE FROM `quest_offer_reward` WHERE (id = 24451);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24451);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24451, 0, 0, 0, 'I\'ve placed an enchantment on the tabard that should allow you to slip past the Silver Enclave\'s defenses for a short period of time. You should have enough time to find your way up to the top level of the Silver Enclave and meet up with the Silver Covenant\'s man there, known as Arcanist Tybalin.

While disguised, obtain the copy of Ancient Dragonforged Blades that his men borrowed from Wyrmrest, and return the book to me.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24451, 0, 'ruRU', 'Я зачаровал эту гербовую накидку особым заклинанием, которое позволит тебе пробраться мимо охранников даларанского Серебряного Анклава. Оно будет действовать недолго, но за это время ты <должен/должна> добраться до верхних этажей штаб-квартиры Серебряного Анклава и встретиться там с представителем Серебряного Союза, этим чародеем Тибалином.

Возьми у него копию "Древних клинков драконьей ковки", которую его люди одолжили в Храме Драконьего Покоя, и сразу же возвращайся ко мне.', 0);


-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24451, 1, 0, 'Did you recover the book from Wyrmrest?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24451, 'ruRU', 'Ты забрал книгу из Храма Драконьего Покоя?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24451, 0, 0, 0, 0, 0, 0, 0, 0, 'Excellent work. Now that this is in our hands, we must get it to Myralion Sunblaze as soon as possible. We can\'t risk the Silver Covenant taking the book from us again.

I\'ll get that tabard back to Shandy and see that he\'s well compensated for his assistance. Once the book is in Myralion\'s hands, the Silver Covenant won\'t be a threat anymore.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24451, 'ruRU', 'Превосходно! Теперь, когда книга в наших руках, мы должны как можно скорее доставить ее Миралию Блеску Солнца. Нельзя допустить, чтобы она снова оказалась у Серебряного союза.

А я позабочусь о том, чтобы Шанди Шикблеск получил обратно свою накидку и солидную награду за помощь. Как только мы передадим книгу Миралию, Серебряный союз останется не у дел.', 0);

DELETE FROM `quest_poi` WHERE (QuestID = 24451);
DELETE FROM `quest_poi_points` WHERE (QuestID = 24451);

INSERT INTO `quest_poi` (`QuestID`, `id`, `ObjectiveIndex`, `MapID`, `WorldMapAreaId`, `Floor`, `Priority`, `Flags`, `VerifiedBuild`) VALUES 
(24451, 1, -1, 571, 504, 1, 0, 3, 0),
(24451, 2, 4, 571, 504, 1, 0, 3, 0);

INSERT INTO `quest_poi_points` (`QuestID`, `Idx1`, `Idx2`, `X`, `Y`, `VerifiedBuild`) VALUES 
(24451, 1, 0, 5892, 473, 0),
(24451, 2, 0, 5746, 724, 0);




-- Возвращение к Миралию Блеску Солнца. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24558);
DELETE FROM `quest_greeting_locale` WHERE (id = 24558);
DELETE FROM `quest_request_items` WHERE (id = 24558);
DELETE FROM `quest_request_items_locale` WHERE (id = 24558);
DELETE FROM `quest_offer_reward` WHERE (id = 24558);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24558);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24558, 0, 0, 0, 'We must get this book to Myralion Sunblade. Would you bring it to him? I cannot rely on anyone else to transport the book and you have proven adept at evading the Silver Covenant\'s men.

Take it with you to Quel\'Delar\'s Rest, south of the Argent Tournament Grounds in Icecrown. Myralion will be waiting for you. If he can identify that blade, we may be able to claim it in the name of Aethas Sunreaver and show Dalaran and the Alliance that we will lead the charge against the Lich King.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24558, 0, 'ruRU', 'Эту книгу надо немедленно отнести Миралию Блеску Солнца. Ты этим займешься? Никому другому я не могу доверить столь ценную ношу, а ты уже <доказал/доказала> свою верность, обхитрив Серебряный Союз.

Твой путь лежит в покой Кель\'Делара, что на юге от ристалища Серебряного Турнира в Ледяной Короне. Миралий будет ждать тебя вместе с мечом. Чем быстрее мы сможем распознать этот клинок, тем скорее сможем им овладеть и обратить против Короля-лича во имя Этаса Похитителя Солнца. Мы должны показать Даларану и Альянсу, кто достоин возглавить эту битву.', 0);


-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24558, 1, 0, 'We\'ve been expecting your return. What has kept you?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24558, 'ruRU', 'Мы ожидали твоего возвращения. Что тебя задержало?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24558, 0, 0, 0, 0, 0, 0, 0, 0, '<Myralion accepts the heavy book and begins leafing through it.>

Those symbols on the blade seemed familiar and now there\'s little wonder why. This is certainly a dragon blade, gifted to one of the mortal races, but which blade is this, and how did it come to rest in Icecrown?', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24558, 'ruRU', '<Миралий забирает у вас тяжелую книгу и начинает внимательно ее пролистывать.>

Ах вот почему символы на рукояти казались мне такими знакомыми... Да, этот меч был точно выкован драконами и передан в дар смертным, но что это был за клинок и как он оказался в Ледяной Короне?', 0);




-- Перековать меч. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24559);
DELETE FROM `quest_greeting_locale` WHERE (id = 24559);
DELETE FROM `quest_request_items` WHERE (id = 24559);
DELETE FROM `quest_request_items_locale` WHERE (id = 24559);
DELETE FROM `quest_offer_reward` WHERE (id = 24559);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24559);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24559, 0, 0, 0, 'We cannot allow Quel\'Delar to remain broken and disgraced. Take the remnants of the sword, along with the battered hilt you discovered, and venture into the Pit of Saron within Icecrown Citadel.

In the pit, the Lich King uses slaves to mine, process, and transform saronite ore. This infused saronite is what we will use to rebuild Quel\'Delar.

You must gather bars of infused saronite and capture the forgemaster\'s hammer, then bring them to the forgemaster\'s anvil and reforge the sword.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24559, 0, 'ruRU', 'Нельзя допустить, чтобы великий Кель\'Делар оставался расколотым и обесчещенным. Возьми фрагменты клинка вместе с потертой рукоятью и отправляйся в Яму Сарона, что в цитадели Ледяной Короны.

В этой яме слуги Короля-лича добывают и обрабатывают саронитовую руду. Только с помощью заряженного саронита можно перековать Кель\'Делар.

Ты <должен/должна> собрать саронитовые слитки и перековать меч, вопользовавшись молотом и наковальней начальника кузни.', 0);


-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24559, 1, 0, 'Were you able to reconstruct Quel\Delar?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24559, 'ruRU', 'Тебе удалось воссоздать Кель\'Делар?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24559, 0, 0, 0, 0, 0, 0, 0, 0, 'You have remade the blade of Quel\'Delar in defiance of that Blood-Queen Lana\'thel\'s pronouncement! Now, the blade must be tempered before we can show her the folly of her words.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24559, 'ruRU', 'Значит, несмотря на дерзкие речи королевы Лана\'тель, ты все же воссоздал Кель\'Делар! Осталось лишь закалить клинок – и мы покажем ей, как были неосмотрительны ее слова.', 0);



-- Закалить клинок. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24560);
DELETE FROM `quest_greeting_locale` WHERE (id = 24560);
DELETE FROM `quest_request_items` WHERE (id = 24560);
DELETE FROM `quest_request_items_locale` WHERE (id = 24560);
DELETE FROM `quest_offer_reward` WHERE (id = 24560);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24560);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24560, 0, 0, 0, 'At last, the pieces of Quel\'Delar are rejoined and the blade is whole, but it cannot see battle until you have tempered it. That jagged saronite edge is brittle and will shatter the moment it strikes anything.

Deep in Icecrown Citadel\'s Forge of Souls is a place where the blade can safely be tempered. Take Quel\'Delar with you to the abode of the Devourer of Souls and look for the crucible. Plunge the blade into the crucible to temper it and bring it back to me. I\'ll be waiting in The Frozen Halls.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24560, 0, 'ruRU', 'Наконец-то фрагменты Кель\'Делара воссоединились, и клинок снова стал целым. Но он еще не готов к битве, ибо для начала его надо закалить. Эти саронитовые зубцы очень хрупкие и могут отколоться в момент удара.

Но глубоко под цитаделью Ледяной Короны есть Кузня Душ, в которой можно закалить подобный клинок. Отнеси Кель\'Делар в обитель Пожирателя Душ и найди там горнило душ. Закали меч и принеси его мне. Я буду ждать тебя в Ледяных залах.', 0);


-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24560, 1, 0, 'Until the sword is tempered, it will be useless.', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24560, 'ruRU', 'Пока клинок не будет закален, он бесполезен.', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24560, 0, 0, 0, 0, 0, 0, 0, 0, 'Tempering the sword should\'ve restored the blade. Why hasn\'t it worked?', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24560, 'ruRU', 'После закалки клинок должен был восстановиться во всем своем былом могуществе. Что же случилось?', 0);




-- Закалить клинок. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24561);
DELETE FROM `quest_greeting_locale` WHERE (id = 24561);
DELETE FROM `quest_request_items` WHERE (id = 24561);
DELETE FROM `quest_request_items_locale` WHERE (id = 24561);
DELETE FROM `quest_offer_reward` WHERE (id = 24561);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24561);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24561, 0, 0, 0, 'You have re-forged and tempered the sword, yet it sits quietly in its sheath, little different from a mundane blade. You say the sword pulls you, as though it possesses a will?

Dare you bring it where it wishes to go? It is not right that the sword should be this silent and this insistent, yet I fear that if you do not take the sword to its destination, we will never learn why. Bear it with you to Icecrown Citadel\'s Halls of Reflection, but be on your guard. I will wait for you in The Frozen Halls.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24561, 0, 'ruRU', 'Ты <перековал и закалил/перековала и закалила> клинок, но я не чувствую в нем былой силы. Правильно ли я понял, что клинок побуждает тебя к действию, словно он обладает собственной волей?

Осмелишься ли последовать его зову? Негоже великому мечу ржаветь в ножнах. Я боюсь, что мы никогда не узнаем его тайн, если не последуем велению его судьбы. Отнеси его в Залы Отражений, что в цитадели Ледяной Короны, но будь <готов/готова> ко всему. Я буду ждать тебя в Ледяных залах.', 0);


-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24561, 1, 0, 'What happened inside the Halls of Reflection?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24561, 'ruRU', 'Что произошло в Залах Отражений?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24561, 0, 0, 0, 0, 0, 0, 0, 0, 'How can evil take root in such a sword? I would not have thought it possible if the evidence wasn\'t here before my eyes. If the greatest of dragonkind\'s creations could be corrupted and turned against them, why not a mere sword?

I believe Uther is right. You must heed his advice quickly, $n.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24561, 'ruRU', 'Я и не подозревал, что зло могло пустить корни в столь великом клинке, но это была наивная ошибка с моей стороны. Если даже самые могущественные представители рода драконов пали жертвами скверны, что уж говорить о простом оружии?

Утер дал тебе мудрый совет, $n, и ты должен немедленно ему последовать.', 0);



-- Путешествие к Солнечному Колодцу. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24562);
DELETE FROM `quest_greeting_locale` WHERE (id = 24562);
DELETE FROM `quest_request_items` WHERE (id = 24562);
DELETE FROM `quest_request_items_locale` WHERE (id = 24562);
DELETE FROM `quest_offer_reward` WHERE (id = 24562);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24562);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24562, 0, 0, 0, 'Take Quel\'Delar to the Sunwell as quickly as possible, $n. Trust in Uther\'s words when he says that you will not always be able to control the blade while it is subject to the evil of the Lich King\'s influence. You must travel to the Isle of Quel\'Danas, and there, seek entry to the Sunwell itself, where you can cleanse the sword.

The guardians will try to stop you from entering the Sunwell Plateau, but make yourself known to Halduron Brightwing, who will be inspecting the guards there.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24562, 0, 'ruRU', 'Как можно быстрее отнеси Кель\'Делар к Солнечному Колодцу, $n! Мы должны поверить словам Утера о том, что оскверненный могуществом Короля-лича клинок не всегда будет тебе подвластен. Ты <должен/должна> отправиться на остров Кель\'Данас и найти вход в сам Солнечный Колодец. Только он обладает силой очистить меч.

Учти, что стражники Солнечного Колодца не позволят тебе пройти без разрешения, поэтому тебе придется заручиться поддержкой Халдарона Светлого Крыла, начальника охраны.', 0);


-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24562, 1, 0, 'What brings you here?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24562, 'ruRU', 'Что привело тебя сюда?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24562, 0, 0, 0, 0, 0, 0, 0, 0, 'I hope you understand that I can\'t just admit you to the Sunwell, $n. This is the most sacred place known to the sin\'dorei and we have only recently regained control over it.

You would raise the hopes of our people with tales of Quel\'Delar? Without proof of the truth of your claims, I see no reason to take you at your word.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24562, 'ruRU', 'Надеюсь, ты понимаешь, почему я не могу пропустить тебя к Солнечному Колодцу, $n. Это священное место для всех син\'дорай, и мы лишь недавно вернули его под свое покровительство.

К тому же, я не могу допустить распространения ложных слухов о возрождении Кель\'Делара. Если ты не докажешь мне истинность своих слов, нам не о чем разговаривать.', 0);




-- Талориен Искатель Рассвета. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24563);
DELETE FROM `quest_greeting_locale` WHERE (id = 24563);
DELETE FROM `quest_request_items` WHERE (id = 24563);
DELETE FROM `quest_request_items_locale` WHERE (id = 24563);
DELETE FROM `quest_offer_reward` WHERE (id = 24563);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24563);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24563, 0, 0, 0, 'You are the one working with Myralion Sunblaze, arent you? I know of a way we can test the sword.

If you know the blade\'s history, you recall that it was borne by Thalorien Dawnseeker in defense of the Sunwell against the Scourge. He fell in what is now the Dead Scar, buying time for his men to make their own preparations. You will find his remains near the southern end of the Dead Scar on this isle. Visit them, and if his spirit gives you its blessing, I will allow you to enter the Sunwell.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24563, 0, 'ruRU', 'Ты ведь работаешь на Миралия Блеска Солнца, верно? Думаю, я знают способ испытать, что за клинок у тебя в руках. Полагаю, тебе известна история этого меча? Им владел Талориен Искатель Рассвета, что защищал Колодец от нашествия Плети. Талориен пал на том месте, что мы сейчас называем Тропой Мертвых. Ценой своей жизни он выиграл время, необходимое для того, чтобы его люди сумели подготовиться и встретить врага во всеоружии. Останки Талориена покоятся на этом острове в южном конце Тропы. Наведайся туда, и, если дух героя благословит тебя, я разрешу тебе пройти в Солнечный Колодец.', 0);


-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24563, 1, 0, 'What brings you here?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24563, 'ruRU', 'Что привело тебя сюда?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24563, 0, 0, 0, 0, 0, 0, 0, 0, 'You truly do carry Quel\'Delar. This is a great day for all of Quel\'Thalas and the sin\'dorei. You have my leave to enter the Sunwell and finish the sword\'s restoration. Keep your head high, $n. The children of Silvermoon have dreamt of this day for years.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24563, 'ruRU', 'Истинно, в твоих руках Кель\'Делар! Что за великий день для Кель\'Таласа и всех син\'дорай. Теперь ты можешь пройти к Солнечному Колодцу и завершить восстановление меча. Ступай с гордостью, $n. Дети Луносвета ждали этого момента долгие годы.', 0);




-- Очищение Кель'Делара. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24564);
DELETE FROM `quest_greeting_locale` WHERE (id = 24564);
DELETE FROM `quest_request_items` WHERE (id = 24564);
DELETE FROM `quest_request_items_locale` WHERE (id = 24564);
DELETE FROM `quest_offer_reward` WHERE (id = 24564);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24564);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24564, 0, 0, 0, 'The Sunwell and the end of Quel\'Delar\'s exile await, $n.

You will find Lor\'themar Theron, the regent of Quel\'Thalas, and Grand Magister Rommath standing within. Be wary and do not allow them to entrap you in their political scheming.

Instead, remain focused on your task here. Speak to a Warden of the Sunwell when you are ready to enter the Sunwell. Immerse the reformed Quel\'Delar in the Sunwell to complete the restoration. Afterward, show the blade to Myralion Sunblaze at Quel\'Delar\'s Rest.', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24564, 0, 'ruRU', 'Истекают часы изгнания Кель\'Делара. Тебя ждет Солнечный Колодец, $n.

Там ты встретишь Лор\'темара Терона, регента Кель\'Таласа и Верховного магистра Роммата. Будь <осторожен/осторожна> с ними, не давай вовлечь себя в политические махинации.

Сосредоточься на своей миссии. Когда ты будешь <готов/готова> завершить восстановление Кель\'Делара, поговори с хранителем Солнечного Колодца. Окуни меч в Солнечный Колодец, а затем отнеси его Миралию Блеску Солнца в Покой Кель\'Делара.', 0);


-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24564, 1, 0, 'What happened inside the Sunwell?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24564, 'ruRU', 'Что произошло во время твоего путешествия к Солнечному Колодцу?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24564, 0, 0, 0, 0, 0, 0, 0, 0, 'Am I truly laying my eyes upon the weapon of Thalorien Dawnseeker? This is a wondrous day for the Sunreavers and for all sin\'dorei!', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24564, 'ruRU', 'Неужели я действительно вижу перед собой оружие Талориена Искателя Рассвета? Это великий день для Похитителей Солнца и всех син\'дорай.', 0);



-- Победа похитителей солнца. quest texts
DELETE FROM `quest_greeting` WHERE (id = 24801);
DELETE FROM `quest_greeting_locale` WHERE (id = 24801);
DELETE FROM `quest_request_items` WHERE (id = 24801);
DELETE FROM `quest_request_items_locale` WHERE (id = 24801);
DELETE FROM `quest_offer_reward` WHERE (id = 24801);
DELETE FROM `quest_offer_reward_locale` WHERE (id = 24801);

-- Начало квеста
INSERT INTO `quest_greeting` (`ID`, `Type`, `GreetEmoteType`, `GreetEmoteDelay`, `Greeting`, `VerifiedBuild`) VALUES 
(24801, 0, 0, 0, 'At last, Quel\'Delar is restored for the glory of the Sunreavers and the Horde! This is a blessing for our efforts against the Lich King.$B$BArchmage Aethas Sunreaver, the leader of the Sunreavers, asked to see you after you returned from the Sunwell. Travel to the Violet Citadel in Dalaran as soon as you can, $N and bring Quel\'Delar with you. The archmage wishes to congratulate you personally!', 0);

INSERT INTO `quest_greeting_locale` (`ID`, `Type`, `locale`, `Greeting`, `VerifiedBuild`) VALUES 
(24801, 0, 'ruRU', 'Наконец-то Кел\'Делар восстановлен во славу Похитителей Солнца и Орды! Это благословение для наших усилий против Короля-Лича. $B$ Архимаг Аэтас Похититель Солнца, лидер Похитителей Солнца, просил о встрече с вами после того, как вы вернулись из Солнечного Колодца. Отправляйся в Фиолетовую цитадель в Даларане, как только сможешь, и возьми с собой Кел\'Делар. Верховный маг желает поздравить вас лично!', 0);


-- Кв в процессе
INSERT INTO `quest_request_items` (`ID`, `EmoteOnComplete`, `EmoteOnIncomplete`, `CompletionText`, `VerifiedBuild`) VALUES 
(24801, 1, 0, 'Is it true that you have restored Quel\'Delar?', 0);

INSERT INTO `quest_request_items_locale` (`ID`, `locale`, `CompletionText`, `VerifiedBuild`) VALUES 
(24801, 'ruRU', 'Это правда, что ты восстановил Кель\'Делар?', 0);

-- Кв окончание
INSERT INTO `quest_offer_reward` (`ID`, `Emote1`, `Emote2`, `Emote3`, `Emote4`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `EmoteDelay4`, `RewardText`, `VerifiedBuild`) VALUES 
(24801, 0, 0, 0, 0, 0, 0, 0, 0, 'Quel\'Delar rises again, as the sin\'dorei have risen from the ashes of defeat and betrayal. Yet, somehow, the weapon of Thalorien Dawnseeker has chosen to serve an outsider.

Be at ease, $n. I do not mean to diminish your accomplishment, for you have done what none of my brothers could, although I do not know why. You are clearly meant to be its bearer; the blade is already adapting itself to your abilities. Wield Quel\'Delar proudly against our common foes.', 0);

INSERT INTO `quest_offer_reward_locale` (`ID`, `locale`, `RewardText`, `VerifiedBuild`) VALUES 
(24801, 'ruRU', 'Кел\'Делар восстает снова, как син\'дореи восстали из пепла поражения и предательства. И все же, каким-то образом, оружие Отважного Искателя Рассвета решило служить чужаку.

Будь спокоен, $n. Я не хочу умалять твоих достижений, ибо ты сделал то, чего не смог ни один из моих братьев, хотя я и не знаю почему. Вы явно предназначены для того, чтобы быть его носителем; клинок уже приспосабливается к вашим способностям. Гордо владей Кель\'Деларом против наших общих врагов.', 0);

UPDATE `quest_poi_points` SET `X` = 5798, `Y` = 789, `VerifiedBuild` = 0 WHERE `QuestID` = 24801 AND `Idx1` = 0 AND `Idx2` = 0;
