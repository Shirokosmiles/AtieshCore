/*
* Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
* Copyright (C) 2016-2017 RustEmu <https://gitlab.com/healthstone/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "AccountMgr.h"
#include "Chat.h"
#include "DatabaseEnv.h"
#include "GossipDef.h"
#include "GameTime.h"
#include "GameEventMgr.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "Map.h"
#include "World.h"
#include "WorldSession.h"
#include "ObjectMgr.h"
#include "Item.h"
#include "Language.h"
#include "Log.h"

#include <sstream>
#include <string>
#include <vector>

//#define EMOTE_ALREADY_ITEM "|cff00ffffУ вас уже имеется данная вещь!|r"
#define CONST_ARENA_RENAME 100
#define CONST_ARENA_CUSTOMIZE 100
#define CONST_ARENA_CHANGE_FACTION 500
#define CONST_ARENA_CHANGE_RACE 250
//#define MSG_RENAME_COMPLETE "|cff00ff00Оплата успешно произведена. Сделайте логаут и введите новое имя своего персонажа.Не забудьте после смены имени, выйти из игры и удалить из клиента папку 'Cache'!|r"
//#define MSG_CUSTOMIZE_COMPLETE "|cff00ff00Оплата успешно произведена. Сделайте логаут и измените внешность своего персонажа.Не забудьте после смены внешности, выйти из игры и удалить из клиента папку 'Cache'!|r"
//#define MSG_CHANGE_FACTION_COMPLETE "|cff00ff00Оплата успешно произведена. Сделайте логаут и измените фракцию своего персонажа.Не забудьте после смены фракции, выйти из игры и удалить из клиента папку 'Cache'!|r" 
//#define MSG_CHANGE_RACE_COMPLETE "|cff00ff00Оплата успешно произведена. Сделайте логаут и измените расу своего персонажа.Не забудьте после смены расы, выйти из игры и удалить из клиента папку 'Cache'!|r"
//#define EMOTE_NO_ARENA_POINTS "|cffff0000У вас недостаточно О.А. для совершения покупки!|r"
//#define MSG_RESET_COOLDOWN "|cff0000ffВсе заклинания и способности успешно обновлены! КД сброшено!|r"
//#define EMOTE_COOLDOWN "|cff00ffffВы не можете использовать функцию так часто!|r"
//#define MSG_RESET_QUEST_STATUS_COMPLETE "|cff0000ffКД заданий успешно сброшено!|r"
//#define MSG_RESET_RAID_INSTANCES_COOLDOWN_COMPLETE "|cff0000ffРейдовые подземелья успешно обновлены! КД сброшено!|r"
#define CONST_ARENA_POINT 100
#define CONST_ARENA_POINT2 1000
#define CONST_HONOR_POINT 2000
#define CONST_HONOR_POINT2 20000
#define CONST_HONOR_POINT3 10000
#define CONST_HONOR_POINT4 100000
#define CONST_HONOR_POINT5 200000

std::string getString(std::string string, uint32 number)
{
    std::ostringstream oss;
    oss << string << number;
    return oss.str();
}

uint32 aurass[] = { 15366, 16609, 48162, 48074, 48170, 43223, 36880, 69994, 33081, 26035, 48469,57623, 47440 };

class custom_item : public ItemScript
{
private:
public:
    custom_item() : ItemScript("custom_item") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        if (player->GetMap()->IsBattlegroundOrArena())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You can not use it on BattleGround or Arena!");
            CloseGossipMenuFor(player);
            return false;
        }
        if (player->IsInCombat()) 
        {
            ChatHandler(player->GetSession()).PSendSysMessage(LANG_YOU_IN_COMBAT);
            CloseGossipMenuFor(player);
            return false;
        }
        if (player->IsInFlight())
        {
            ChatHandler(player->GetSession()).PSendSysMessage(LANG_YOU_IN_FLIGHT);
            CloseGossipMenuFor(player);
            return false;
        }
        if (player->HasStealthAura())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You can not use it while you in stealth!");
            CloseGossipMenuFor(player);
            return false;
        }
        if (player->isDead() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You can not use it while you dead!");
            CloseGossipMenuFor(player);
            return false;
        }

        player->PlayerTalkClass->ClearMenus();

        // показатель бонусов с системой определение кол.бонусов (бонус, бонуса, бонусов)
        AddGossipItemFor(player,GOSSIP_ICON_MONEY_BAG, getString(player->GetSession()->GetTrinityString(LANG_ITEM_CURRENT_COINS), player->GetCoins()).c_str(), GOSSIP_SENDER_MAIN, 300000);

        if (player->GetCFSTeam() == ALLIANCE)       
            AddGossipItemFor(player, GOSSIP_ICON_TAXI, std::string("|TInterface/ICONS/Spell_Arcane_TeleportStormWind:25:25:-15:0|t ") + player->GetSession()->GetTrinityString(LANG_ITEM_STORMWIND), GOSSIP_SENDER_MAIN, 1277, player->GetSession()->GetTrinityString(LANG_ITEM_STORMWIND_SURE), 0, false);
        else
            AddGossipItemFor(player, GOSSIP_ICON_TAXI, std::string("|TInterface/ICONS/Spell_Arcane_TeleportOrgrimmar:25:25:-15:0|t ") + player->GetSession()->GetTrinityString(LANG_ITEM_ORGRIMMAR), GOSSIP_SENDER_MAIN, 1278, player->GetSession()->GetTrinityString(LANG_ITEM_ORGRIMMAR_SURE), 0, false);

        if (player->IsGameMaster())
        {
            AddGossipItemFor(player, 0, "|TInterface\\icons\\achievement_level_80:25:25:-15:0|t Class skills - GM|r", GOSSIP_SENDER_MAIN, 101);
            AddGossipItemFor(player, 0, "|TInterface/ICONS/inv_crate_04:25:25:-15:0|t Delivery of bags", GOSSIP_SENDER_MAIN, 218);

            if (player->getLevel() < 80)
                AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface\\icons\\Inv_misc_coin_01:25:25:-15:0|t Level up at 80", GOSSIP_SENDER_MAIN, 300222);
        }

        if (player->IsPremium())
            AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\Inv_inscription_pigment_bug07:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_VIP_MENU), GOSSIP_SENDER_MAIN, 170);

        AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\Inv_inscription_weaponscroll01:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_SERVER_MENU), GOSSIP_SENDER_MAIN, 777);
        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
        return false;
    }

    void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action)
    {
        //uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(action);
        //uint32 action = player->PlayerTalkClass->GetGossipOptionAction(action);
        //return OnGossipSelect(player, me, sender, action);

        std::string XP = "|cff660099" + std::string(player->GetSession()->GetTrinityString(LANG_ITEM_RATES_XP_KILL)) + "|r x";
        std::string XP_quest = "|cff660099" + std::string(player->GetSession()->GetTrinityString(LANG_ITEM_RATES_XP_QUEST)) + "|r x";
        std::string rep   = "|cff660099" + std::string(player->GetSession()->GetTrinityString(LANG_ITEM_RATES_REP)) + "|r x";
        std::string gold  = "|cff660099" + std::string(player->GetSession()->GetTrinityString(LANG_ITEM_RATES_GOLD)) + "|r x";
        std::string honor = "|cff660099" + std::string(player->GetSession()->GetTrinityString(LANG_ITEM_RATES_HONOR)) + "|r x";
        uint32 trainerentry;
        player->PlayerTalkClass->ClearMenus();

        if (sender == GOSSIP_SENDER_MAIN)
        {
            switch (action)
            {
            case 1277:
                    CloseGossipMenuFor(player);
                    player->TeleportTo(0, -8831.966797f, 632.503906f, 94.210480f, 4.61f);
                    player->CastSpell(player, 45523, true);
                break;
            case 102: // Двойная специализация
                if (player->GetSpecsCount() == 1 && !(player->getLevel() < sWorld->getIntConfig(CONFIG_MIN_DUALSPEC_LEVEL)))
                    player->CastSpell(player, 63680, true);
                player->CastSpell(player, 63624, true);
                CloseGossipMenuFor(player);
                break;
            case 101: // Классовые навыки
                switch (player->getClass())
                {
                case CLASS_WARRIOR:
                    player->LearnSpell(7384, false);
                    player->LearnSpell(47436, false);
                    player->LearnSpell(47450, false);
                    player->LearnSpell(11578, false);
                    player->LearnSpell(47465, false);
                    player->LearnSpell(47502, false);
                    player->LearnSpell(34428, false);
                    player->LearnSpell(1715, false);
                    player->LearnSpell(2687, false);
                    player->LearnSpell(71, false);
                    player->LearnSpell(7386, false);
                    player->LearnSpell(355, false);
                    player->LearnSpell(72, false);
                    player->LearnSpell(47437, false);
                    player->LearnSpell(57823, false);
                    player->LearnSpell(694, false);
                    player->LearnSpell(2565, false);
                    player->LearnSpell(676, false);
                    player->LearnSpell(47520, false);
                    player->LearnSpell(20230, false);
                    player->LearnSpell(12678, false);
                    player->LearnSpell(47471, false);
                    player->LearnSpell(1161, false);
                    player->LearnSpell(871, false);
                    player->LearnSpell(2458, false);
                    player->LearnSpell(20252, false);
                    player->LearnSpell(47475, false);
                    player->LearnSpell(18499, false);
                    player->LearnSpell(1680, false);
                    player->LearnSpell(6552, false);
                    player->LearnSpell(47488, false);
                    player->LearnSpell(1719, false);
                    player->LearnSpell(23920, false);
                    player->LearnSpell(47440, false);
                    player->LearnSpell(3411, false);
                    player->LearnSpell(64382, false);
                    player->LearnSpell(55694, false);
                    player->LearnSpell(57755, false);
                    player->LearnSpell(42459, false);
                    player->LearnSpell(750, false);
                    player->LearnSpell(5246, false);
                    player->LearnSpell(3127, false);
                    if (player->HasSpell(12294))
                        player->LearnSpell(47486, false);
                    if (player->HasSpell(20243))
                        player->LearnSpell(47498, false);
                    player->SaveToDB();
                    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                case CLASS_PALADIN:
                    player->LearnSpell(3127, false);
                    player->LearnSpell(19746, false);
                    player->LearnSpell(19752, false);
                    player->LearnSpell(750, false);
                    player->LearnSpell(48942, false);
                    player->LearnSpell(48782, false);
                    player->LearnSpell(48932, false);
                    player->LearnSpell(20271, false);
                    player->LearnSpell(498, false);
                    player->LearnSpell(10308, false);
                    player->LearnSpell(1152, false);
                    player->LearnSpell(10278, false);
                    player->LearnSpell(48788, false);
                    player->LearnSpell(53408, false);
                    player->LearnSpell(48950, false);
                    player->LearnSpell(48936, false);
                    player->LearnSpell(31789, false);
                    player->LearnSpell(62124, false);
                    player->LearnSpell(54043, false);
                    player->LearnSpell(25780, false);
                    player->LearnSpell(1044, false);
                    player->LearnSpell(20217, false);
                    player->LearnSpell(48819, false);
                    player->LearnSpell(48801, false);
                    player->LearnSpell(48785, false);
                    player->LearnSpell(5502, false);
                    player->LearnSpell(20164, false);
                    player->LearnSpell(10326, false);
                    player->LearnSpell(1038, false);
                    player->LearnSpell(53407, false);
                    player->LearnSpell(48943, false);
                    player->LearnSpell(20165, false);
                    player->LearnSpell(48945, false);
                    player->LearnSpell(642, false);
                    player->LearnSpell(48947, false);
                    player->LearnSpell(20166, false);
                    player->LearnSpell(4987, false);
                    player->LearnSpell(48806, false);
                    player->LearnSpell(6940, false);
                    player->LearnSpell(48817, false);
                    player->LearnSpell(48934, false);
                    player->LearnSpell(48938, false);
                    player->LearnSpell(25898, false);
                    player->LearnSpell(32223, false);
                    player->LearnSpell(31884, false);
                    player->LearnSpell(54428, false);
                    player->LearnSpell(61411, false);
                    player->LearnSpell(53601, false);
                    player->LearnSpell(33388, false);
                    player->LearnSpell(33391, false);
                    if (player->HasSpell(20925))
                        player->LearnSpell(48952, false);
                    if (player->HasSpell(31935))
                        player->LearnSpell(48827, false);
                    if (player->HasSpell(20911))
                        player->LearnSpell(25899, false);
                    if (player->HasSpell(20473))
                        player->LearnSpell(48825, false);
                    if (player->GetCFSTeam() == ALLIANCE)
                    {
                        player->LearnSpell(31801, false);
                        player->LearnSpell(13819, false);
                        player->LearnSpell(23214, false);
                    }
                    if (player->GetCFSTeam() == HORDE)
                    {
                        player->LearnSpell(53736, false);
                        player->LearnSpell(34769, false);
                        player->LearnSpell(34767, false);
                    }
                    player->SaveToDB();
                    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                case CLASS_HUNTER:
                    player->LearnSpell(3043, false);
                    player->LearnSpell(3127, false);
                    player->LearnSpell(3045, false);
                    player->LearnSpell(3034, false);
                    player->LearnSpell(8737, false);
                    player->LearnSpell(1494, false);
                    player->LearnSpell(13163, false);
                    player->LearnSpell(48996, false);
                    player->LearnSpell(49001, false);
                    player->LearnSpell(49045, false);
                    player->LearnSpell(53338, false);
                    player->LearnSpell(5116, false);
                    player->LearnSpell(27044, false);
                    player->LearnSpell(883, false);
                    player->LearnSpell(2641, false);
                    player->LearnSpell(6991, false);
                    player->LearnSpell(982, false);
                    player->LearnSpell(1515, false);
                    player->LearnSpell(19883, false);
                    player->LearnSpell(20736, false);
                    player->LearnSpell(48990, false);
                    player->LearnSpell(2974, false);
                    player->LearnSpell(6197, false);
                    player->LearnSpell(1002, false);
                    player->LearnSpell(14327, false);
                    player->LearnSpell(5118, false);
                    player->LearnSpell(49056, false);
                    player->LearnSpell(53339, false);
                    player->LearnSpell(49048, false);
                    player->LearnSpell(19884, false);
                    player->LearnSpell(34074, false);
                    player->LearnSpell(781, false);
                    player->LearnSpell(14311, false);
                    player->LearnSpell(1462, false);
                    player->LearnSpell(19885, false);
                    player->LearnSpell(19880, false);
                    player->LearnSpell(13809, false);
                    player->LearnSpell(13161, false);
                    player->LearnSpell(5384, false);
                    player->LearnSpell(1543, false);
                    player->LearnSpell(19878, false);
                    player->LearnSpell(49067, false);
                    player->LearnSpell(3034, false);
                    player->LearnSpell(13159, false);
                    player->LearnSpell(19882, false);
                    player->LearnSpell(58434, false);
                    player->LearnSpell(49071, false);
                    player->LearnSpell(49052, false);
                    player->LearnSpell(19879, false);
                    player->LearnSpell(19263, false);
                    player->LearnSpell(19801, false);
                    player->LearnSpell(34026, false);
                    player->LearnSpell(34600, false);
                    player->LearnSpell(34477, false);
                    player->LearnSpell(61006, false);
                    player->LearnSpell(61847, false);
                    player->LearnSpell(53271, false);
                    player->LearnSpell(60192, false);
                    player->LearnSpell(62757, false);
                    if (player->HasSpell(19386))
                        player->LearnSpell(49012, false);
                    if (player->HasSpell(53301))
                        player->LearnSpell(60053, false);
                    if (player->HasSpell(19306))
                        player->LearnSpell(48999, false);
                    if (player->HasSpell(19434))
                        player->LearnSpell(49050, false);
                    player->SaveToDB();
                    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                case CLASS_MAGE:
                    player->LearnSpell(42921, false);
                    player->LearnSpell(42842, false);
                    player->LearnSpell(42995, false);
                    player->LearnSpell(42833, false);
                    player->LearnSpell(27090, false);
                    player->LearnSpell(33717, false);
                    player->LearnSpell(42873, false);
                    player->LearnSpell(42846, false);
                    player->LearnSpell(12826, false);
                    player->LearnSpell(28271, false);
                    player->LearnSpell(61780, false);
                    player->LearnSpell(61721, false);
                    player->LearnSpell(28272, false);
                    player->LearnSpell(42917, false);
                    player->LearnSpell(43015, false);
                    player->LearnSpell(130, false);
                    player->LearnSpell(42926, false);
                    player->LearnSpell(43017, false);
                    player->LearnSpell(475, false);
                    player->LearnSpell(1953, false);
                    player->LearnSpell(42940, false);
                    player->LearnSpell(12051, false);
                    player->LearnSpell(43010, false);
                    player->LearnSpell(43020, false);
                    player->LearnSpell(43012, false);
                    player->LearnSpell(42859, false);
                    player->LearnSpell(2139, false);
                    player->LearnSpell(42931, false);
                    player->LearnSpell(42985, false);
                    player->LearnSpell(43008, false);
                    player->LearnSpell(45438, false);
                    player->LearnSpell(43024, false);
                    player->LearnSpell(43002, false);
                    player->LearnSpell(43046, false);
                    player->LearnSpell(42897, false);
                    player->LearnSpell(42914, false);
                    player->LearnSpell(66, false);
                    player->LearnSpell(58659, false);
                    player->LearnSpell(30449, false);
                    player->LearnSpell(42956, false);
                    player->LearnSpell(47610, false);
                    player->LearnSpell(61316, false);
                    player->LearnSpell(61024, false);
                    player->LearnSpell(55342, false);
                    player->LearnSpell(53142, false);
                    player->LearnSpell(7301, false);
                    if (player->GetCFSTeam() == ALLIANCE)
                    {
                        player->LearnSpell(32271, false); // Teleport: Exodar.
                        player->LearnSpell(49359, false); // Teleport: Theramore.
                        player->LearnSpell(3565, false); // Teleport: Darnassus.
                        player->LearnSpell(33690, false); // Teleport: Shattrath.
                        player->LearnSpell(3562, false); // Teleport: Ironforge.
                        player->LearnSpell(3561, false); // Teleport: Stormwind.
                        player->LearnSpell(53140, false); // Teleport: Dalaran.
                        player->LearnSpell(53142, false); // Portal: Dalaran.
                        player->LearnSpell(10059, false); // Portal: Stormwind.
                        player->LearnSpell(11419, false); // Portal: Darnassus.
                        player->LearnSpell(32266, false); // Portal: Exodar.
                        player->LearnSpell(11416, false); // Portal: Ironforge.
                        player->LearnSpell(33691, false); // Portal: Shattrath.
                        player->LearnSpell(49360, false); // Portal: Theramore.
                    }
                    if (player->GetCFSTeam() == HORDE)
                    {
                        player->LearnSpell(3567, false); // Teleport: Orgrimmar.
                        player->LearnSpell(35715, false); // Teleport: Shattrath.
                        player->LearnSpell(3566, false); // Teleport: Thunder Bluff.
                        player->LearnSpell(49358, false); // Teleport: Stonard.
                        player->LearnSpell(32272, false); // Teleport: Silvermoon.
                        player->LearnSpell(3563, false); // Teleport: Undercity.
                        player->LearnSpell(53140, false); // Teleport: Dalaran.
                        player->LearnSpell(53142, false); // Portal: Dalaran.
                        player->LearnSpell(11417, false); // Portal: Orgrimmar.
                        player->LearnSpell(35717, false); // Portal: Shattrath.
                        player->LearnSpell(32267, false); // Portal: Silvermoon.
                        player->LearnSpell(49361, false); // Portal: Stonard.
                        player->LearnSpell(11420, false); // Portal: Thunder Bluff.
                        player->LearnSpell(11418, false); // Portal: Undercity.
                    }
                    if (player->HasSpell(11366))
                        player->LearnSpell(42891, false);
                    if (player->HasSpell(11426))
                        player->LearnSpell(43039, false);
                    if (player->HasSpell(44457))
                        player->LearnSpell(55360, false);
                    if (player->HasSpell(31661))
                        player->LearnSpell(42950, false);
                    if (player->HasSpell(11113))
                        player->LearnSpell(42945, false);
                    if (player->HasSpell(44425))
                        player->LearnSpell(44781, false);
                    player->SaveToDB();
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                case CLASS_WARLOCK:
                    player->LearnSpell(696, false);
                    player->LearnSpell(47811, false);
                    player->LearnSpell(47809, false);
                    player->LearnSpell(688, false);
                    player->LearnSpell(47813, false);
                    player->LearnSpell(50511, false);
                    player->LearnSpell(57946, false);
                    player->LearnSpell(47864, false);
                    player->LearnSpell(6215, false);
                    player->LearnSpell(47878, false);
                    player->LearnSpell(47855, false);
                    player->LearnSpell(697, false);
                    player->LearnSpell(47856, false);
                    player->LearnSpell(47857, false);
                    player->LearnSpell(5697, false);
                    player->LearnSpell(47884, false);
                    player->LearnSpell(47815, false);
                    player->LearnSpell(47889, false);
                    player->LearnSpell(47820, false);
                    player->LearnSpell(698, false);
                    player->LearnSpell(712, false);
                    player->LearnSpell(126, false);
                    player->LearnSpell(5138, false);
                    player->LearnSpell(5500, false);
                    player->LearnSpell(11719, false);
                    player->LearnSpell(132, false);
                    player->LearnSpell(60220, false);
                    player->LearnSpell(18647, false);
                    player->LearnSpell(61191, false);
                    player->LearnSpell(47823, false);
                    player->LearnSpell(691, false);
                    player->LearnSpell(47865, false);
                    player->LearnSpell(47891, false);
                    player->LearnSpell(47888, false);
                    player->LearnSpell(17928, false);
                    player->LearnSpell(47860, false);
                    player->LearnSpell(47825, false);
                    player->LearnSpell(1122, false);
                    player->LearnSpell(47867, false);
                    player->LearnSpell(18540, false);
                    player->LearnSpell(47893, false);
                    player->LearnSpell(47838, false);
                    player->LearnSpell(29858, false);
                    player->LearnSpell(58887, false);
                    player->LearnSpell(47836, false);
                    player->LearnSpell(61290, false);
                    player->LearnSpell(48018, false);
                    player->LearnSpell(48020, false);
                    player->LearnSpell(33388, false);
                    player->LearnSpell(33391, false);
                    player->LearnSpell(23161, false);
                    if (player->HasSpell(17877))
                        player->LearnSpell(47827, false);
                    if (player->HasSpell(30283))
                        player->LearnSpell(47847, false);
                    if (player->HasSpell(30108))
                        player->LearnSpell(47843, false);
                    if (player->HasSpell(50796))
                        player->LearnSpell(59172, false);
                    if (player->HasSpell(48181))
                        player->LearnSpell(59164, false);
                    if (player->HasSpell(18220))
                        player->LearnSpell(59092, false);
                    player->SaveToDB();
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                case CLASS_ROGUE:
                    player->LearnSpell(3127, false);
                    player->LearnSpell(42459, false);
                    player->LearnSpell(48668, false);
                    player->LearnSpell(48638, false);
                    player->LearnSpell(1784, false);
                    player->LearnSpell(48657, false);
                    player->LearnSpell(921, false);
                    player->LearnSpell(1776, false);
                    player->LearnSpell(26669, false);
                    player->LearnSpell(51724, false);
                    player->LearnSpell(6774, false);
                    player->LearnSpell(11305, false);
                    player->LearnSpell(1766, false);
                    player->LearnSpell(48676, false);
                    player->LearnSpell(48659, false);
                    player->LearnSpell(1804, false);
                    player->LearnSpell(8647, false);
                    player->LearnSpell(48691, false);
                    player->LearnSpell(51722, false);
                    player->LearnSpell(48672, false);
                    player->LearnSpell(1725, false);
                    player->LearnSpell(26889, false);
                    player->LearnSpell(2836, false);
                    player->LearnSpell(1833, false);
                    player->LearnSpell(1842, false);
                    player->LearnSpell(8643, false);
                    player->LearnSpell(2094, false);
                    player->LearnSpell(1860, false);
                    player->LearnSpell(57993, false);
                    player->LearnSpell(48674, false);
                    player->LearnSpell(31224, false);
                    player->LearnSpell(5938, false);
                    player->LearnSpell(57934, false);
                    player->LearnSpell(51723, false);
                    if (player->HasSpell(16511))
                        player->LearnSpell(48660, false);
                    if (player->HasSpell(1329))
                        player->LearnSpell(48666, false);
                    player->SaveToDB();
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                case CLASS_PRIEST:
                    player->LearnSpell(528, false);
                    player->LearnSpell(2053, false);
                    player->LearnSpell(48161, false);
                    player->LearnSpell(48123, false);
                    player->LearnSpell(48125, false);
                    player->LearnSpell(48066, false);
                    player->LearnSpell(586, false);
                    player->LearnSpell(48068, false);
                    player->LearnSpell(48127, false);
                    player->LearnSpell(48171, false);
                    player->LearnSpell(48168, false);
                    player->LearnSpell(10890, false);
                    player->LearnSpell(6064, false);
                    player->LearnSpell(988, false);
                    player->LearnSpell(48300, false);
                    player->LearnSpell(6346, false);
                    player->LearnSpell(48071, false);
                    player->LearnSpell(48135, false);
                    player->LearnSpell(48078, false);
                    player->LearnSpell(453, false);
                    player->LearnSpell(10955, false);
                    player->LearnSpell(10909, false);
                    player->LearnSpell(8129, false);
                    player->LearnSpell(48073, false);
                    player->LearnSpell(605, false);
                    player->LearnSpell(48072, false);
                    player->LearnSpell(48169, false);
                    player->LearnSpell(552, false);
                    player->LearnSpell(1706, false);
                    player->LearnSpell(48063, false);
                    player->LearnSpell(48162, false);
                    player->LearnSpell(48170, false);
                    player->LearnSpell(48074, false);
                    player->LearnSpell(48158, false);
                    player->LearnSpell(48120, false);
                    player->LearnSpell(34433, false);
                    player->LearnSpell(48113, false);
                    player->LearnSpell(32375, false);
                    player->LearnSpell(64843, false);
                    player->LearnSpell(64901, false);
                    player->LearnSpell(53023, false);
                    if (player->HasSpell(34914))
                        player->LearnSpell(48160, false);
                    if (player->HasSpell(47540))
                        player->LearnSpell(53007, false);
                    if (player->HasSpell(724))
                        player->LearnSpell(48087, false);
                    if (player->HasSpell(19236))
                        player->LearnSpell(48173, false);
                    if (player->HasSpell(34861))
                        player->LearnSpell(48089, false);
                    if (player->HasSpell(15407))
                        player->LearnSpell(48156, false);
                    player->SaveToDB();
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                case CLASS_DEATH_KNIGHT:
                    player->LearnSpell(3127, false);
                    player->LearnSpell(50842, false);
                    player->LearnSpell(49941, false);
                    player->LearnSpell(49930, false);
                    player->LearnSpell(47476, false);
                    player->LearnSpell(45529, false);
                    player->LearnSpell(3714, false);
                    player->LearnSpell(56222, false);
                    player->LearnSpell(48743, false);
                    player->LearnSpell(48263, false);
                    player->LearnSpell(49909, false);
                    player->LearnSpell(47528, false);
                    player->LearnSpell(45524, false);
                    player->LearnSpell(48792, false);
                    player->LearnSpell(57623, false);
                    player->LearnSpell(56815, false);
                    player->LearnSpell(47568, false);
                    player->LearnSpell(49895, false);
                    player->LearnSpell(50977, false);
                    player->LearnSpell(49576, false);
                    player->LearnSpell(49921, false);
                    player->LearnSpell(46584, false);
                    player->LearnSpell(49938, false);
                    player->LearnSpell(48707, false);
                    player->LearnSpell(48265, false);
                    player->LearnSpell(61999, false);
                    player->LearnSpell(42650, false);
                    player->LearnSpell(53428, false);
                    player->LearnSpell(53331, false);
                    player->LearnSpell(54447, false);
                    player->LearnSpell(53342, false);
                    player->LearnSpell(54446, false);
                    player->LearnSpell(53323, false);
                    player->LearnSpell(53344, false);
                    player->LearnSpell(70164, false);
                    player->LearnSpell(62158, false);
                    player->LearnSpell(33391, false);
                    player->LearnSpell(48778, false);
                    player->LearnSpell(51425, false);
                    player->LearnSpell(49924, false);
                    if (player->HasSpell(55050))
                        player->LearnSpell(55262, false);
                    if (player->HasSpell(49143))
                        player->LearnSpell(55268, false);
                    if (player->HasSpell(49184))
                        player->LearnSpell(51411, false);
                    if (player->HasSpell(55090))
                        player->LearnSpell(55271, false);
                    if (player->HasSpell(49158))
                        player->LearnSpell(51328, false);
                    player->SaveToDB();
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                case CLASS_SHAMAN:
                    player->LearnSpell(2062, false);
                    player->LearnSpell(8737, false);
                    player->LearnSpell(49273, false);
                    player->LearnSpell(49238, false);
                    player->LearnSpell(10399, false);
                    player->LearnSpell(49231, false);
                    player->LearnSpell(58753, false);
                    player->LearnSpell(2484, false);
                    player->LearnSpell(49281, false);
                    player->LearnSpell(58582, false);
                    player->LearnSpell(49233, false);
                    player->LearnSpell(58790, false);
                    player->LearnSpell(58704, false);
                    player->LearnSpell(58643, false);
                    player->LearnSpell(49277, false);
                    player->LearnSpell(61657, false);
                    player->LearnSpell(8012, false);
                    player->LearnSpell(526, false);
                    player->LearnSpell(2645, false);
                    player->LearnSpell(57994, false);
                    player->LearnSpell(8143, false);
                    player->LearnSpell(49236, false);
                    player->LearnSpell(58796, false);
                    player->LearnSpell(58757, false);
                    player->LearnSpell(49276, false);
                    player->LearnSpell(57960, false);
                    player->LearnSpell(131, false);
                    player->LearnSpell(58745, false);
                    player->LearnSpell(6196, false);
                    player->LearnSpell(58734, false);
                    player->LearnSpell(58774, false);
                    player->LearnSpell(58739, false);
                    player->LearnSpell(58656, false);
                    player->LearnSpell(546, false);
                    player->LearnSpell(556, false);
                    player->LearnSpell(66842, false);
                    player->LearnSpell(51994, false);
                    player->LearnSpell(8177, false);
                    player->LearnSpell(58749, false);
                    player->LearnSpell(20608, false);
                    player->LearnSpell(36936, false);
                    player->LearnSpell(36936, false);
                    player->LearnSpell(58804, false);
                    player->LearnSpell(49271, false);
                    player->LearnSpell(8512, false);
                    player->LearnSpell(6495, false);
                    player->LearnSpell(8170, false);
                    player->LearnSpell(66843, false);
                    player->LearnSpell(55459, false);
                    player->LearnSpell(66844, false);
                    player->LearnSpell(3738, false);
                    player->LearnSpell(2894, false);
                    player->LearnSpell(60043, false);
                    player->LearnSpell(51514, false);
                    if (player->GetCFSTeam() == ALLIANCE)
                        player->LearnSpell(32182, false);
                    if (player->GetCFSTeam() == HORDE)
                        player->LearnSpell(2825, false);
                    if (player->HasSpell(61295))
                        player->LearnSpell(61301, false);
                    if (player->HasSpell(974))
                        player->LearnSpell(49284, false);
                    if (player->HasSpell(30706))
                        player->LearnSpell(57722, false);
                    if (player->HasSpell(51490))
                        player->LearnSpell(59159, false);
                    player->SaveToDB();
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                case CLASS_DRUID:
                    player->LearnSpell(48378, false);
                    player->LearnSpell(48469, false);
                    player->LearnSpell(48461, false);
                    player->LearnSpell(48463, false);
                    player->LearnSpell(48441, false);
                    player->LearnSpell(53307, false);
                    player->LearnSpell(53308, false);
                    player->LearnSpell(5487, false);
                    player->LearnSpell(48560, false);
                    player->LearnSpell(6795, false);
                    player->LearnSpell(48480, false);
                    player->LearnSpell(53312, false);
                    player->LearnSpell(18960, false);
                    player->LearnSpell(5229, false);
                    player->LearnSpell(48443, false);
                    player->LearnSpell(50763, false);
                    player->LearnSpell(8983, false);
                    player->LearnSpell(8946, false);
                    player->LearnSpell(1066, false);
                    player->LearnSpell(48562, false);
                    player->LearnSpell(783, false);
                    player->LearnSpell(770, false);
                    player->LearnSpell(16857, false);
                    player->LearnSpell(18658, false);
                    player->LearnSpell(768, false);
                    player->LearnSpell(1082, false);
                    player->LearnSpell(5215, false);
                    player->LearnSpell(48477, false);
                    player->LearnSpell(49800, false);
                    player->LearnSpell(48465, false);
                    player->LearnSpell(48572, false);
                    player->LearnSpell(26995, false);
                    player->LearnSpell(48574, false);
                    player->LearnSpell(2782, false);
                    player->LearnSpell(50213, false);
                    player->LearnSpell(2893, false);
                    player->LearnSpell(33357, false);
                    player->LearnSpell(5209, false);
                    player->LearnSpell(48575, false);
                    player->LearnSpell(48447, false);
                    player->LearnSpell(48577, false);
                    player->LearnSpell(48579, false);
                    player->LearnSpell(5225, false);
                    player->LearnSpell(22842, false);
                    player->LearnSpell(49803, false);
                    player->LearnSpell(9634, false);
                    player->LearnSpell(20719, false);
                    player->LearnSpell(48467, false);
                    player->LearnSpell(29166, false);
                    player->LearnSpell(62600, false);
                    player->LearnSpell(22812, false);
                    player->LearnSpell(48470, false);
                    player->LearnSpell(33943, false);
                    player->LearnSpell(49802, false);
                    player->LearnSpell(48451, false);
                    player->LearnSpell(48568, false);
                    player->LearnSpell(33786, false);
                    player->LearnSpell(40120, false);
                    player->LearnSpell(62078, false);
                    player->LearnSpell(52610, false);
                    player->LearnSpell(50464, false);
                    player->LearnSpell(48570, false);
                    if (player->HasSpell(50516))
                        player->LearnSpell(61384, false);
                    if (player->HasSpell(48505))
                        player->LearnSpell(53201, false);
                    if (player->HasSpell(48438))
                        player->LearnSpell(53251, false);
                    if (player->HasSpell(5570))
                        player->LearnSpell(48468, false);
                    player->SaveToDB();
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
                break;
            case 104: // Тренер классов
                CloseGossipMenuFor(player);                
                switch (player->getClass())
                {
                    case CLASS_WARRIOR:
                            trainerentry = 985;
                        break;
                    case CLASS_PALADIN:
                            trainerentry = 927;
                        break;
                    case CLASS_HUNTER:
                            trainerentry = 987;
                        break;
                    case CLASS_ROGUE:
                            trainerentry = 917;
                        break;
                    case CLASS_PRIEST:
                            trainerentry = 376;
                        break;
                    case CLASS_DEATH_KNIGHT:
                            trainerentry = 28472;
                        break;
                    case CLASS_SHAMAN:
                            trainerentry = 986;
                        break;
                    case CLASS_MAGE:
                            trainerentry = 328;
                        break;
                    case CLASS_WARLOCK:
                            trainerentry = 906;
                        break;
                    case CLASS_DRUID:
                            trainerentry = 3033;
                        break;
                }
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
                player->PlayerTalkClass->SendCloseGossip();
                if (trainerentry)
                    player->GetSession()->SendTrainerList(ObjectGuid::Empty, trainerentry);
                break;
            case 1278:
                    CloseGossipMenuFor(player);
                    player->TeleportTo(1, 1569.170410f, -4433.635742f, 6.718508f, 0.f);
                    player->CastSpell(player, 45523, true);
                break;
            case 150:
                if (player->HasAura(45523))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    player->GetSession()->SendAreaTriggerMessage(player->GetSession()->GetTrinityString(LANG_ITEM_MSG_COOLDOWN));
                }
                else
                {
                    player->RemoveAurasByType(SPELL_AURA_MOUNTED);
                    for (int i = 0; i < 16; i++)
                        player->AddAura(aurass[i], player);
                    player->GetSession()->SendNotification("|cffC67171Buffs received!");
                    player->CastSpell(player, 45523, true);
                    player->PlayerTalkClass->SendCloseGossip();
                }
                break;
            case 300000:
                {
                    std::string iconvip = "|TInterface\\icons\\Inv_inscription_pigment_bug07:25:25:-15:0|t";
                    player->PlayerTalkClass->ClearMenus();
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, getString(player->GetSession()->GetTrinityString(LANG_ITEM_CURRENT_COINS), player->GetCoins()).c_str(), GOSSIP_SENDER_MAIN, 200110);
                    if (!player->IsPremium())
                        AddGossipItemFor(player, 0, iconvip + "Account: [|cffE80000" + player->GetSession()->GetTrinityString(LANG_ITEM_VIP_BUY) + "|r]", GOSSIP_SENDER_MAIN, 160);
                    else
                        AddGossipItemFor(player, 0, iconvip + "VIP account: [|cffE80000" + player->GetSession()->GetTrinityString(LANG_ITEM_VIP_INCREASE) + "|r]", GOSSIP_SENDER_MAIN, 161);
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, std::string("|TInterface\\icons\\Spell_chargenegative:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_CLOSE), GOSSIP_SENDER_MAIN, 200110);
                    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
                }
                break;
            case 300222:
                //{
                    //QueryResult result1 = LoginDatabase.PQuery("SELECT coin FROM account WHERE id = %u", player->GetSession()->GetAccountId());
                    //if (result1)
                   // {
                    //    Field *fields = result1->Fetch();
                    //    uint32 coins = fields[0].GetUInt32();
                   //     uint32 ostatok = 250 - coins; 			

                       // if (coins >= 250)
                      //  {
                            player->GiveLevel(80);
                            //LoginDatabase.PQuery("UPDATE account SET coin = coin-50 WHERE id = %u", player->GetSession()->GetAccountId());
                            player->SaveToDB();
                            ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_LEVELUP);
                            player->PlayerTalkClass->SendCloseGossip();
                     //   }
                        /*
                        else
                        {
                            ChatHandler(player->GetSession()).PSendSysMessage("|cff006699Недостаточно бонусов|r");
                            ChatHandler(player->GetSession()).PSendSysMessage("|cff006699У вас: |cff00FF33%u|r", coins);
                            ChatHandler(player->GetSession()).PSendSysMessage("|cff006699Нужно еще: |cffFF0000%u|r", ostatok);
                            player->PlayerTalkClass->SendCloseGossip();
                        }*/
                   // }
               // }
                break;
            case 170:
                {
                    AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\Inv_misc_note_02:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_COMMAND_LIST), GOSSIP_SENDER_MAIN, 210);
                    AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\Inv_misc_tournaments_banner_scourge:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_CHARACTER_MANAGEMENT), GOSSIP_SENDER_MAIN, 1245);
                    AddGossipItemFor(player, 0, std::string("|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_CHARACTER_CHANGEING), GOSSIP_SENDER_MAIN, 1205);
                    AddGossipItemFor(player, GOSSIP_ICON_TRAINER, std::string("|TInterface\\icons\\achievement_level_80:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_CLASS_SKILLS), GOSSIP_SENDER_MAIN, 104);
                    AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\Inv_throwingknife_02:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_REPAIR_EQUIP), GOSSIP_SENDER_MAIN, 216);
                    AddGossipItemFor(player, 0, std::string("|TInterface/ICONS/ability_druid_cower:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_REMOVE_DESERTER), GOSSIP_SENDER_MAIN, 217);
                    AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\spell_shadow_deathscream:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_REMOVE_WEAKNESS), GOSSIP_SENDER_MAIN, 215);
                    AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\Spell_holy_wordfortitude:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_GIVE_BUFFS), GOSSIP_SENDER_MAIN, 150);
                    AddGossipItemFor(player, 0, "|TInterface\\icons\\Spell_chargepositive:25:25:-15:0|tBank", GOSSIP_SENDER_MAIN, 214);
                    //AddGossipItemFor(player, 0, "|TInterface\\icons\\Ability_mount_rocketmountblue:25:25:-15:0|tПолучить Вип Маунта", GOSSIP_SENDER_MAIN, 212); 
                    if (!player->IsInCombat() || !player->IsInFlight() || !player->GetMap()->IsBattlegroundOrArena() || !player->HasStealthAura() || !player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || !player->isDead())
                        AddGossipItemFor(player, 0, std::string("|TInterface/ICONS/spell_holy_borrowedtime:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_REMOVE_COOLDOWN), GOSSIP_SENDER_MAIN, 1212);

                    //AddGossipItemFor(player, 0, "|TInterface/ICONS/spell_holy_borrowedtime:25:25:-15:0|t Сбросить 'КД' заданий", GOSSIP_SENDER_MAIN, 1215);
                    //AddGossipItemFor(player, 0, "|TInterface/icons/Spell_chargepositive:25:25:-15:0|tСменить Цвет Чата", GOSSIP_SENDER_MAIN, 196);
                    AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\Spell_chargenegative:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_CLOSE), GOSSIP_SENDER_MAIN, 200110);
                    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
                }
                break;
            case 1245:
                player->PlayerTalkClass->ClearMenus();
                AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\Ability_DualWield:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_DUAL_SPEC), GOSSIP_SENDER_MAIN, 102);
                AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\ability_marksmanship:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_RESET_TALENT), GOSSIP_SENDER_MAIN, 103, player->GetSession()->GetTrinityString(LANG_ITEM_RESET_TALENT_SURE), 0, false);
                AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\achievement_general:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_SKILLS_WEAPON), GOSSIP_SENDER_MAIN, 106);
                AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\trade_engineering:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_MAXSKILL), GOSSIP_SENDER_MAIN, 107);
                AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\Spell_chargenegative:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_CLOSE), GOSSIP_SENDER_MAIN, 200110);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
                break;
            case 200110:
                CloseGossipMenuFor(player);
                break;
            case 103: // Сброс талантов
                player->ResetTalents(true);
                player->SendTalentsInfoData(false);
                CloseGossipMenuFor(player);
                ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_TALENT_RESET_CONFIRM);
                break;
            case 106: // Оружейные навыки
                switch (player->getClass())
                {
                case CLASS_WARRIOR:
                    CloseGossipMenuFor(player);
                    player->LearnSpell(5011, false); // Арбалеты
                    player->LearnSpell(200, false); // Древковое оружие
                    player->LearnSpell(15590, false); // Кулачное оружие
                    player->LearnSpell(264, false); // Луки
                    player->LearnSpell(266, false); // Ружья
                    player->LearnSpell(227, false); // Посохи
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_SKILLS_WEAPON_CONFIRM);
                    break;
                case CLASS_PALADIN:
                    CloseGossipMenuFor(player);
                    player->LearnSpell(197, false); // Двуручные топоры
                    player->LearnSpell(200, false); // Древковое оружие
                    player->LearnSpell(196, false); // Одноручные топоры
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_SKILLS_WEAPON_CONFIRM);
                    break;
                case CLASS_WARLOCK:
                    CloseGossipMenuFor(player);
                    player->LearnSpell(201, false); // Одноручные мечи
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_SKILLS_WEAPON_CONFIRM);
                    break;
                case CLASS_PRIEST:
                    CloseGossipMenuFor(player);
                    player->LearnSpell(1180, false); // Кинжалы
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_SKILLS_WEAPON_CONFIRM);
                    break;
                case CLASS_HUNTER:
                    CloseGossipMenuFor(player);
                    player->LearnSpell(5011, false); // Арбалеты
                    player->LearnSpell(202, false); // Двуручные мечи
                    player->LearnSpell(200, false); // Древковое оружие
                    player->LearnSpell(15590, false); // Кулачное оружие
                    player->LearnSpell(264, false); // Луки
                    player->LearnSpell(2567, false); // Метательное оружие
                    player->LearnSpell(227, false); // Посохи
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_SKILLS_WEAPON_CONFIRM);
                    break;
                case CLASS_MAGE:
                    CloseGossipMenuFor(player);
                    player->LearnSpell(1180, false); // Кинжалы
                    player->LearnSpell(201, false); // Одноручные мечи
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_SKILLS_WEAPON_CONFIRM);
                    break;
                case CLASS_SHAMAN:
                    CloseGossipMenuFor(player);
                    player->LearnSpell(199, false); // Двуручное дробящее оружие
                    player->LearnSpell(197, false); // Двуручные топоры
                    player->LearnSpell(1180, false); // Кинжалы
                    player->LearnSpell(15590, false); // Кулачное оружие
                    player->LearnSpell(196, false); // Одноручные топоры
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_SKILLS_WEAPON_CONFIRM);
                    break;
                case CLASS_ROGUE:
                    CloseGossipMenuFor(player);
                    player->LearnSpell(5011, false); // Арбалеты
                    player->LearnSpell(198, false); // Одноручное дробящее оружие
                    player->LearnSpell(15590, false); // Кулачное оружие
                    player->LearnSpell(264, false); // Луки
                    player->LearnSpell(201, false); // Одноручные мечи
                    player->LearnSpell(266, false); // Ружья
                    player->LearnSpell(196, false); // Одноручные топоры
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_SKILLS_WEAPON_CONFIRM);
                    break;
                case CLASS_DEATH_KNIGHT:
                    CloseGossipMenuFor(player);
                    player->LearnSpell(199, false); // Двуручное дробящее оружие
                    player->LearnSpell(198, false); // Одноручное дробящее оружие
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_SKILLS_WEAPON_CONFIRM);
                    break;
                case CLASS_DRUID:
                    CloseGossipMenuFor(player);
                    player->LearnSpell(199, false); // Двуручное дробящее оружие
                    player->LearnSpell(200, false); // Древковое оружие
                    player->LearnSpell(15590, false); // Кулачное оружие
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_SKILLS_WEAPON_CONFIRM);
                    break;
                }
            case 107: // Улучшить навыки защиты и владения оружием до максимума
                CloseGossipMenuFor(player);
                player->UpdateWeaponsSkillsToMaxSkillsForLevel();
                ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_MAXSKILL_CONFIRM);
                break;
                /*
            case 196:
                {
                    AddGossipItemFor(player,0, "|TInterface\\icons\\Spell_chargepositive:25|t|cffD00000Красный|r", GOSSIP_SENDER_MAIN, 1010);
                    AddGossipItemFor(player,0, "|TInterface\\icons\\Spell_chargepositive:25|t|cff3333CCСиний|r", GOSSIP_SENDER_MAIN, 1011);	
                    AddGossipItemFor(player,0, "|TInterface\\icons\\Spell_chargepositive:25|t|cff009900Зелёный|r", GOSSIP_SENDER_MAIN, 1012);	
                    AddGossipItemFor(player,0, "|TInterface\\icons\\Spell_chargepositive:25|t|cff0099FFГолубой|r", GOSSIP_SENDER_MAIN, 1013);	
                    AddGossipItemFor(player,0, "|TInterface\\icons\\Spell_chargepositive:25|t|cffFF99FFРозовый|r", GOSSIP_SENDER_MAIN, 1014); 
                    AddGossipItemFor(player,0, "|TInterface\\icons\\Spell_chargepositive:25|t|cff9192a1Серый|r", GOSSIP_SENDER_MAIN, 1015); 
                    AddGossipItemFor(player,0, "|TInterface\\icons\\Spell_chargepositive:25|t|cffb37700Коричневый|r", GOSSIP_SENDER_MAIN, 1016); 
                    AddGossipItemFor(player,0, "|TInterface\\icons\\Spell_chargepositive:25|t|cffffd9b3Бежевый|r", GOSSIP_SENDER_MAIN, 1017); 
                    AddGossipItemFor(player,0, "|TInterface\\icons\\Spell_chargenegative:25|t|Вернуть обычный цвет", GOSSIP_SENDER_MAIN, 1018); 
                    SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, item->GetGUID());			
                }
                break;   
            case 1010: // Красный
                {
                    LoginDatabase.PExecute("UPDATE account SET color = '1' WHERE id = %u", player->GetSession()->GetAccountId());	// |cffD00000 цвет
                    ChatHandler(player->GetSession()).PSendSysMessage("|cffD00000Вы успешно изменили свой цвет чата на: Красный");
                    player->PlayerTalkClass->SendCloseGossip();
                }
                break;
            case 1011: // Синий
                {
                    LoginDatabase.PExecute("UPDATE account SET color = '2' WHERE id = %u", player->GetSession()->GetAccountId());	// |cff3300CC цвет
                    ChatHandler(player->GetSession()).PSendSysMessage("|cff3333CCВы успешно изменили свой цвет чата на: Синий");
                    player->PlayerTalkClass->SendCloseGossip();
                }
                break;
            case 1012: // Зелёный
                {
                    LoginDatabase.PExecute("UPDATE account SET color = '3' WHERE id = %u", player->GetSession()->GetAccountId());	// |cff009900 цвет
                    ChatHandler(player->GetSession()).PSendSysMessage("|cff009900Вы успешно изменили свой цвет чата на: Зелёный");
                    player->PlayerTalkClass->SendCloseGossip();
                }
                break;
            case 1013: // Голубой
                {
                    LoginDatabase.PExecute("UPDATE account SET color = '4' WHERE id = %u", player->GetSession()->GetAccountId()); // |cff0099FF цвет
                    ChatHandler(player->GetSession()).PSendSysMessage("|cff0099FFВы успешно изменили свой цвет чата на: Голубой");				
                    player->PlayerTalkClass->SendCloseGossip();
                }
                break;
            case 1014: // Розовый
                {
                    LoginDatabase.PExecute("UPDATE account SET color = '5' WHERE id = %u", player->GetSession()->GetAccountId()); // |cffFF99FF цвет
                    ChatHandler(player->GetSession()).PSendSysMessage("|cffFF99FFВы успешно изменили свой цвет чата на: Розовый");				
                    player->PlayerTalkClass->SendCloseGossip();
                }
                break;
            case 1015: // серый
                {
                    LoginDatabase.PExecute("UPDATE account SET color = '7' WHERE id = %u", player->GetSession()->GetAccountId());
                    ChatHandler(player->GetSession()).PSendSysMessage("|cff9192a1Вы успешно изменили свой цвет чата на: Серый");
                    player->PlayerTalkClass->SendCloseGossip();
                }
                break;	
            case 1016: // Коричневый
                {
                    LoginDatabase.PExecute("UPDATE account SET color = '8' WHERE id = %u", player->GetSession()->GetAccountId());
                    ChatHandler(player->GetSession()).PSendSysMessage("|cffb37700Вы успешно изменили свой цвет чата на: Коричневый");
                    player->PlayerTalkClass->SendCloseGossip();
                }
                break;	
            case 1017: // Бежевый
                {
                    LoginDatabase.PExecute("UPDATE account SET color = '9' WHERE id = %u", player->GetSession()->GetAccountId());
                    ChatHandler(player->GetSession()).PSendSysMessage("|cffffd9b3Вы успешно изменили свой цвет чата на: Бежевый");
                    player->PlayerTalkClass->SendCloseGossip();
                }
                break;	
            case 1018: // обычный
                {
                    LoginDatabase.PExecute("UPDATE account SET color = '0' WHERE id = %u", player->GetSession()->GetAccountId()); 
                    ChatHandler(player->GetSession()).PSendSysMessage("Вы успешно изменили свой цвет чата на: Обычный");				
                    player->PlayerTalkClass->SendCloseGossip();
                }
                break;
                */
            case 214:
                player->PlayerTalkClass->SendCloseGossip();
                player->GetSession()->SendShowBank(player->GetGUID());
                break;
            case 215:
                player->RemoveAura(15007);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 216: 
                player->DurabilityRepairAll(false, 0.0f, true);
                ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_REPAIR_CONFIRM);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 217:
                if (player->HasAura(58712))
                {
                    player->GetSession()->SendAreaTriggerMessage(player->GetSession()->GetTrinityString(LANG_ITEM_MSG_COOLDOWN));
                    CloseGossipMenuFor(player);
                }
                else if (!player->HasAura(26013))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_DESERTER_NOT_FOUND);
                }
                else
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    player->RemoveAurasDueToSpell(26013);
                    player->CastSpell(player, 34461, true);
                    player->CastSpell(player, 58712, true);
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_DESERTER_REMOVED);
                }
                break;
            case 218: // Выдача сумок
                if (player->HasItemCount(23162, 4))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_MSG_ALREADY_ITEM);
                }
                else
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    player->AddItem(23162, 4);
                }
                break;
            case 1205:
                player->PlayerTalkClass->ClearMenus();
                AddGossipItemFor(player, 0, std::string("|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|t ") + player->GetSession()->GetTrinityString(LANG_ITEM_CHANGE_NAME) + " [|cffff0000100|r Arena Points]", GOSSIP_SENDER_MAIN, 2000);
                AddGossipItemFor(player, 0, std::string("|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|t ") + player->GetSession()->GetTrinityString(LANG_ITEM_CHANGE_OF_APPEARANCE) + " [|cffff0000200|r Arena Points]", GOSSIP_SENDER_MAIN, 2001);
                AddGossipItemFor(player, 0, std::string("|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|t ") + player->GetSession()->GetTrinityString(LANG_ITEM_CHANGE_FACTION) + " [|cffff0000500|r Arena Points]", GOSSIP_SENDER_MAIN, 2002);
                AddGossipItemFor(player, 0, std::string("|TInterface/ICONS/spell_holy_rapture:25:25:-15:0|t ") + player->GetSession()->GetTrinityString(LANG_ITEM_CHANGE_RACE) + " [|cffff0000250|r Arena Points]", GOSSIP_SENDER_MAIN, 2003);
                AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\Spell_chargenegative:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_CLOSE), GOSSIP_SENDER_MAIN, 200110);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
                break;
            case 2000: // Смена имени
                if (player->GetArenaPoints() < CONST_ARENA_RENAME)
                {
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_MSG_NO_ARENA_POINTS);
                    player->PlayerTalkClass->SendCloseGossip();
                }
                else
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    player->SetAtLoginFlag(AT_LOGIN_RENAME);
                    player->ModifyArenaPoints(-CONST_ARENA_RENAME);
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_MSG_RENAME_COMPLETE);
                }
                break;
            case 2001: // Смена внешности
                if (player->GetArenaPoints() < CONST_ARENA_CUSTOMIZE)
                {
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_MSG_NO_ARENA_POINTS);
                    player->PlayerTalkClass->SendCloseGossip();
                }
                else
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
                    player->ModifyArenaPoints(-CONST_ARENA_CUSTOMIZE);
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_MSG_CUSTOMIZE_COMPLETE);
                }
                break;
            case 2002: // Смена фракции
                if (player->GetArenaPoints() < CONST_ARENA_CHANGE_FACTION)
                {
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_MSG_NO_ARENA_POINTS);
                    player->PlayerTalkClass->SendCloseGossip();
                }
                else
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
                    player->ModifyArenaPoints(-CONST_ARENA_CHANGE_FACTION);
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_MSG_CHANGE_FACTION_COMPLETE);
                }
                break;
            case 2003: // Смена расы
                if (player->GetArenaPoints() < CONST_ARENA_CHANGE_RACE)
                {
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_MSG_NO_ARENA_POINTS);
                    player->PlayerTalkClass->SendCloseGossip();
                }
                else
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
                    player->ModifyArenaPoints(-CONST_ARENA_CHANGE_RACE);
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_MSG_CHANGE_RACE_COMPLETE);
                }
                break;
            case 1212: // Сбросить 'КД'
                if (player->HasAura(45523))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    player->GetSession()->SendAreaTriggerMessage(player->GetSession()->GetTrinityString(LANG_ITEM_MSG_RESET_COOLDOWN));
                }
                else
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    player->RemoveArenaSpellCooldowns(true);
                    player->GetSession()->SendAreaTriggerMessage(player->GetSession()->GetTrinityString(LANG_ITEM_MSG_RESET_COOLDOWN));
                    player->CastSpell(player, 45523, true);
                }
                break;
            case 1215: // Сбросить 'КД' заданий
                player->PlayerTalkClass->SendCloseGossip();
                player->ResetDailyQuestStatus();
                player->ResetWeeklyQuestStatus();
                ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_MSG_RESET_RAID_INSTANCES_COOLDOWN_COMPLETE);
                break;
            case 210:
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("|cff006699The next VIP commands are available for you:");
                    if (sWorld->getBoolConfig(CONFIG_VIP_DEBUFF))
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff006699 .vip debuff|r - Drop debuff Deserter and Resurrection Sickness");
                    if (sWorld->getBoolConfig(CONFIG_VIP_BANK))
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff006699 .vip bank|r - Open bank window");
                    if (sWorld->getBoolConfig(CONFIG_VIP_MAIL))
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff006699 .vip mail|r - Open mail box");
                    if (sWorld->getBoolConfig(CONFIG_VIP_REPAIR))
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff006699 .vip repair|r - Repair without costs");
                    if (sWorld->getBoolConfig(CONFIG_VIP_RESET_TALENTS))
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff006699 .vip resettalents|r - Reset talents");
                    if (sWorld->getBoolConfig(CONFIG_VIP_TAXI))
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff006699 .vip taxi|r - Open taxi window");
                    if (sWorld->getBoolConfig(CONFIG_VIP_HOME))
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff006699 .vip home|r - Teleport at Home position (Hearthstone)");
                    if (sWorld->getBoolConfig(CONFIG_VIP_CAPITAL))
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff006699 .vip capital|r - Teleport at your main city");
                    if (sWorld->getBoolConfig(CONFIG_VIP_CHANGE_RACE))
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff006699 .vip changerace|r - Change Race");
                    if (sWorld->getBoolConfig(CONFIG_VIP_CUSTOMIZE))
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff006699 .vip customize|r - Customize character");
                    if (sWorld->getBoolConfig(CONFIG_VIP_APPEAR))
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff006699 .vip app|r - Teleport at your mate in Group");
                    player->PlayerTalkClass->SendCloseGossip();
                }
                break;
            case 777:
                AddGossipItemFor(player, 0, std::string("|cffD80000") + player->GetSession()->GetTrinityString(LANG_ITEM_SERVER_MENU)  + "|r", GOSSIP_SENDER_MAIN, 200110);
                //AddGossipItemFor(player, 0, "|cff660099Web-site:|r RustEmu.org", GOSSIP_SENDER_MAIN, 2001);
                AddGossipItemFor(player, 0, std::string("|cffD80000") + player->GetSession()->GetTrinityString(LANG_ITEM_RATES) + "|r", GOSSIP_SENDER_MAIN, 200110);
                AddGossipItemFor(player, 0, getString(XP, uint32(player->IsPremium() ? sWorld->getRate(RATE_VIP_XP_KILL) : sWorld->getRate(RATE_XP_KILL))).c_str(), GOSSIP_SENDER_MAIN, 200110);
                AddGossipItemFor(player, 0, getString(XP_quest, uint32(player->IsPremium() ? sWorld->getRate(RATE_VIP_XP_QUEST) : sWorld->getRate(RATE_XP_QUEST))).c_str(), GOSSIP_SENDER_MAIN, 200110);
                AddGossipItemFor(player, 0, getString(rep, uint32(player->IsPremium() ? sWorld->getRate(RATE_VIP_REPUTATION) : sWorld->getRate(RATE_REPUTATION_GAIN))).c_str(), GOSSIP_SENDER_MAIN, 200110);
                AddGossipItemFor(player, 0, getString(honor, uint32(player->IsPremium() ? sWorld->getRate(RATE_VIP_HONOR) : sWorld->getRate(RATE_HONOR))).c_str(), GOSSIP_SENDER_MAIN, 200110);
                AddGossipItemFor(player, 0, getString(gold, uint32(sWorld->getRate(RATE_DROP_MONEY))).c_str(), GOSSIP_SENDER_MAIN, 200110);

                //AddGossipItemFor(player, 0, "|cffD80000Администрация|r", GOSSIP_SENDER_MAIN, 2014);
                //AddGossipItemFor(player, 0, "|cff660099Куратор Проекта:|r Re3os ", GOSSIP_SENDER_MAIN, 2015);
                //AddGossipItemFor(player, 0, "|cff660099Администратор:|r Emeris", GOSSIP_SENDER_MAIN, 2017);
                AddGossipItemFor(player, 0, std::string("|TInterface\\icons\\Spell_chargenegative:25:25:-15:0|t") + player->GetSession()->GetTrinityString(LANG_ITEM_CLOSE), GOSSIP_SENDER_MAIN, 200110);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
                break;
            case 212:
                if (player->HasSpell(50281))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_MSG_ALREADY_ITEM);
                }
                else
                {
                    CloseGossipMenuFor(player);
                    player->LearnSpell(50281, false); // Vip маунт
                    break;
                    ChatHandler(player->GetSession()).PSendSysMessage("|cff006699Вы успешно получили вип маунта|r");
                }
                break;
            case 160:
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, player->GetSession()->GetTrinityString(LANG_ITEM_BUY_7), GOSSIP_SENDER_MAIN, 500100, player->GetSession()->GetTrinityString(LANG_ITEM_BUY_7_SURE), 0, false);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, player->GetSession()->GetTrinityString(LANG_ITEM_BUY_14), GOSSIP_SENDER_MAIN, 500101, player->GetSession()->GetTrinityString(LANG_ITEM_BUY_14_SURE), 0, false);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, player->GetSession()->GetTrinityString(LANG_ITEM_BUY_31), GOSSIP_SENDER_MAIN, 500102, player->GetSession()->GetTrinityString(LANG_ITEM_BUY_31_SURE), 0, false);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
                break;
            case 161:
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, player->GetSession()->GetTrinityString(LANG_ITEM_INC_7), GOSSIP_SENDER_MAIN, 500100, player->GetSession()->GetTrinityString(LANG_ITEM_INC_7_SURE), 0, false);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, player->GetSession()->GetTrinityString(LANG_ITEM_INC_14), GOSSIP_SENDER_MAIN, 500101, player->GetSession()->GetTrinityString(LANG_ITEM_INC_14_SURE), 0, false);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, player->GetSession()->GetTrinityString(LANG_ITEM_INC_31), GOSSIP_SENDER_MAIN, 500102, player->GetSession()->GetTrinityString(LANG_ITEM_INC_31_SURE), 0, false);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
                break;
            case 500100:
                {
                    uint32 coins = player->GetCoins();
                    uint32 ostatok = 150 - coins; // 7 дней                        

                    if (coins >= 150)
                    {
                        ostatok = coins - 150;
                        time_t unsetdate;
                        if (player->IsPremium())
                        {
                            unsetdate = player->GetPremiumUnsetdate() + 604800; // 7 дней
                            AccountMgr::UpdateVipStatus(player->GetSession()->GetAccountId(), unsetdate);
                        }
                        else
                        {
                            unsetdate = GameTime::GetGameTime() + 604800; // 7 дней
                            AccountMgr::SetVipStatus(player->GetSession()->GetAccountId(), unsetdate);
                        }
                        player->SetPremiumUnsetdate(unsetdate);
                        player->SetPremiumStatus(true);
                        player->SetCoins(ostatok);
                        AccountMgr::SetCoins(player->GetSession()->GetAccountId(), ostatok);
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff006699Time of your VIP privileges has been increased for %u days!|r", 7);
                        CloseGossipMenuFor(player);
                    }
                    else
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_NOT_ENOUGH_COINS);
                        ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_YOU_HAVE_COINS, coins);
                        ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_YOU_NEED_COINS, ostatok);
                        CloseGossipMenuFor(player);
                    }
                }
                break;
            case 500101:
                {
                    uint32 coins = player->GetCoins();
                    uint32 ostatok = 260 - coins; // 14 дней				

                    if (coins >= 260)
                    {
                        ostatok = coins - 260;
                        time_t unsetdate;
                        if (player->IsPremium())
                        {
                            unsetdate = player->GetPremiumUnsetdate() + 1209600; // 14 дней
                            AccountMgr::UpdateVipStatus(player->GetSession()->GetAccountId(), unsetdate);
                        }
                        else
                        {
                            unsetdate = GameTime::GetGameTime() + 1209600; // 14 дней
                            AccountMgr::SetVipStatus(player->GetSession()->GetAccountId(), unsetdate);
                        }
                        player->SetPremiumUnsetdate(unsetdate);
                        player->SetPremiumStatus(true);
                        player->SetCoins(ostatok);
                        AccountMgr::SetCoins(player->GetSession()->GetAccountId(), ostatok);
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff006699Time of your VIP privileges has been increased for %u days!|r", 14);
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                    else
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_NOT_ENOUGH_COINS);
                        ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_YOU_HAVE_COINS, coins);
                        ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_YOU_NEED_COINS, ostatok);
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                }
                break;
            case 500102:
                {
                    uint32 coins = player->GetCoins();
                    uint32 ostatok = 470 - coins; // 31 день					

                    if (coins >= 470)
                    {
                        ostatok = coins - 470;
                        time_t unsetdate;
                        if (player->IsPremium())
                        {
                            unsetdate = player->GetPremiumUnsetdate() + 2678400; // 31 дней
                            AccountMgr::UpdateVipStatus(player->GetSession()->GetAccountId(), unsetdate);
                        }
                        else
                        {
                            unsetdate = GameTime::GetGameTime() + 2678400; // 31 дней
                            AccountMgr::SetVipStatus(player->GetSession()->GetAccountId(), unsetdate);
                        }
                        player->SetPremiumUnsetdate(unsetdate);
                        player->SetPremiumStatus(true);
                        player->SetCoins(ostatok);
                        AccountMgr::SetCoins(player->GetSession()->GetAccountId(), ostatok);
                        ChatHandler(player->GetSession()).PSendSysMessage("|cff006699Time of your VIP privileges has been increased for %u days!|r", 31);
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                    else
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_NOT_ENOUGH_COINS);
                        ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_YOU_HAVE_COINS, coins);
                        ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_YOU_NEED_COINS, ostatok);
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                }
                break;
            }
        }
    }
};

class LevelupSpellLearn_PlayerScript : PlayerScript
{
public:
    LevelupSpellLearn_PlayerScript() : PlayerScript("levelup_spell_learn") { }

    void LearnSpells(Player* player)
    {
        static std::vector<uint32> npcTrainers =
        {
            0, // None
            985, // Warrior
            927, // Paladin
            987, // Hunter
            917, // Rogue
            376, // Priest
            28472, // Death knight
            986, // Shaman
            328, // Mage
            906, // Warlock
            0, // Monk (5.x)
            3033, // Druid
            0 // Demon hunter
        };

        auto plrClass = player->getClass();
        if (plrClass >= npcTrainers.size())
            return;

        if (auto spells = sObjectMgr->GetNpcTrainerSpells(npcTrainers[plrClass]))
        {
            for (auto itr = spells->spellList.begin(); itr != spells->spellList.end(); itr++)
            {
                auto spell = &itr->second;

                if (spell->SpellID > 0 && player->GetTrainerSpellState(spell) == TRAINER_SPELL_GREEN && !player->HasSpell(spell->SpellID))
                {
                    if (spell->IsCastable())
                        player->CastSpell(player, spell->SpellID, true);
                    else
                        player->LearnSpell(spell->SpellID, false);
                }
            }
        }
    }

    void OnLogin(Player* player, bool) override
    {
        LearnSpells(player);
    }

    void OnLevelChanged(Player* player, uint8 oldLevel) override
    {
        LearnSpells(player);
    }

    void OnFreeTalentPointsChanged(Player* player, uint32 points)
    {
        if (points < 1)
            LearnSpells(player);
    }
};

class rewarded_player : public PlayerScript
{
public:
    rewarded_player() : PlayerScript("rewarded_player") {}

    void OnLevelChanged(Player* player, uint8 newLevel) override
    {
        if (player->GetCFSTeam() == ALLIANCE)
        {
            switch (++newLevel)
            {
            case 10:
                player->AddItem(54218, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 10 уровня.Получите небольшое вознаграждение. Спасибо за то что вы с нами!|r");
                break;
            case 20:
                player->AddItem(54218, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 20 уровня.Получите небольшое вознаграждение. Спасибо за то что вы с нами!|r");
                break;
            case 30:
                player->AddItem(54218, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 30 уровня.Получите небольшое вознаграждение. Спасибо за то что вы с нами!|r");
                break;
            case 40:
                player->AddItem(54218, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 40 уровня.Получите небольшое вознаграждение. Спасибо за то что вы с нами!|r");
                break;
            case 50:
                player->AddItem(54218, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 50 уровня.Получите небольшое вознаграждение. Спасибо за то что вы с нами!|r");
                break;
            case 60:
                player->AddItem(54218, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 60 уровня.Получите небольшое вознаграждение. Спасибо за то что вы с нами!|r");
                break;
            case 70:
                player->AddItem(54218, 1);
                ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 70 уровня.Получите небольшое вознаграждение. Спасибо за то что вы с нами!|r");
                break;
            case 80:
                player->AddItem(54218, 2);
                ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 80 уровня.Получите небольшое вознаграждение. Спасибо за то что вы с нами!|r");
                break;
            }
        }
    }
};

class OnLogin_PlayerScript : public PlayerScript
{
public:
    OnLogin_PlayerScript() : PlayerScript("OnLogin_PlayerScript") { }

    void OnLogin(Player* player, bool /*firstLogin*/) override
    {
        if (!player)
            return;

        if (player->IsPremium())
        {
            if (player->HasSpell(50281))
                return;
        }
        else
            player->RemoveSpell(50281, false);
        return;
    }
};

enum LandrosTexts
{
    SAY_WRONG = 1,
    SAY_CORRECT = 2
};

enum LandroMenus
{
    WELCOME = 8855,
    PROMOTION_MENU_TEXT = 8856,
    PROMOTION = 9197
};

class landro_longshot : public CreatureScript
{
public:

    landro_longshot() : CreatureScript("landro_longshot") { }

    struct landro_longshotAI : public ScriptedAI
    {
        landro_longshotAI(Creature* creature) : ScriptedAI(creature) { }

        int SelectedReward;

        bool GossipHello(Player* player) override
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Ты желаешь что-то особенное?", GOSSIP_SENDER_MAIN, PROMOTION);
            player->PlayerTalkClass->SendGossipMenu(WELCOME, me->GetGUID());
            return true;
        }

        bool GossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            player->PlayerTalkClass->ClearMenus();

            if (action != 0)
            {
                SelectedReward = action;
            }

            QueryResult GetGossipFields = WorldDatabase.PQuery("SELECT OptionText, ActionMenuID FROM gossip_menu_option WHERE MenuID = %u", action);
            do
            {
                Field * fields = GetGossipFields->Fetch();

                std::string OptionText = fields[0].GetString();
                uint32  ActionMenuID = fields[1].GetUInt32();
                if (ActionMenuID != 0)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, OptionText, GOSSIP_SENDER_MAIN, ActionMenuID);
                }
                else
                {
                    AddGossipItemFor(player, 0, OptionText, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1, "", 0, true);
                }

            } while (GetGossipFields->NextRow());

            player->PlayerTalkClass->SendGossipMenu(PROMOTION_MENU_TEXT, me->GetGUID());
            return true;
        }

        bool GossipSelectCode(Player* player, uint32 /*menu_id*/, uint32 gossipListId, char const* code) override
        {
            uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
            player->PlayerTalkClass->ClearMenus();
            uint32 codeUINT = (uint32)atol(code);
            if (!codeUINT)
                return false;
            QueryResult SearchForCode = WorldDatabase.PQuery("SELECT item FROM promotion_codes WHERE code = %u AND collection = %u AND used = 0", codeUINT, SelectedReward);
            if (!SearchForCode)
            {
                me->AI()->Talk(SAY_WRONG);
            }
            else
            {
                me->AI()->Talk(SAY_CORRECT);
                do
                {
                    Field * fields = SearchForCode->Fetch();
                    player->AddItem(fields[0].GetUInt32(), 1);
                    WorldDatabase.PQuery("Update promotion_codes SET USED = 1 WHERE code = %u", codeUINT);
                } while (SearchForCode->NextRow());
            }

            player->PlayerTalkClass->SendCloseGossip();
            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new landro_longshotAI(creature);
    }
};

void AddSC_custom_item()
{
    new custom_item();
    //new LevelupSpellLearn_PlayerScript();
    new rewarded_player();
    new OnLogin_PlayerScript();
    new landro_longshot();
}
