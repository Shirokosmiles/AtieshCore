/*
* Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
* Copyright (C) 2016-2017 AtieshCore <https://gitlab.com/healthstone/>
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

#include "DatabaseEnv.h"
#include "GossipDef.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "WorldSession.h"
#include "ObjectMgr.h"
#include "Language.h"

#include <sstream>
#include <string>
#include <vector>

enum LandrosTexts
{
    SAY_WRONG = 1,
    SAY_CORRECT = 2
};

enum LandroMenus
{
    WELCOME             = 8855,
    PROMOTION_MENU_TEXT = 8856,
    PROMOTION           = 9197
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
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Do you desire something special?", GOSSIP_SENDER_MAIN, PROMOTION);
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
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, OptionText, GOSSIP_SENDER_MAIN, ActionMenuID);
                else
                    AddGossipItemFor(player, 0, OptionText, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1, "", 0, true);

            } while (GetGossipFields->NextRow());

            player->PlayerTalkClass->SendGossipMenu(PROMOTION_MENU_TEXT, me->GetGUID());
            return true;
        }

        bool GossipSelectCode(Player* player, uint32 /*menu_id*/, uint32 gossipListId, char const* code) override
        {
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

void AddSC_landro_longshot()
{
    new landro_longshot();
}
