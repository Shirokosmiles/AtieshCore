/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
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

#include "ScriptMgr.h"
#include "GameObject.h"
#include "Map.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "SpecialEvent.h"
#include "SpecialEventMgr.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "TemporarySummon.h"

class npc_highlord_darion_mograine : public CreatureScript
{
public:
    npc_highlord_darion_mograine() : CreatureScript("npc_highlord_darion_mograine") { }

    struct npc_highlord_darion_mograineAI : public EscortAI
    {
        npc_highlord_darion_mograineAI(Creature* creature) : EscortAI(creature)
        {
            Reset();
        }

        void Reset() override
        {
            if (!HasEscortState(STATE_ESCORT_ESCORTING))
            {
                me->SetStandState(UNIT_STAND_STATE_STAND);
                me->Mount(25279);
                me->SetWalk(false);
                me->SetSpeedRate(MOVE_RUN, 2.0f);
                me->SetVisible(true);
            }
        }

        bool GossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF + 1:
                    CloseGossipMenuFor(player);
                    Start(true, true, player->GetGUID());
                    if (SpecialEvent* DalaranEvent = sSpecialEventMgr->GetEnabledSpecialEventByEventId(SPECIALEVENT_EVENTID_THELIGHTOFDAWN))
                        DalaranEvent->StartSpecialEvent();
                    break;
            }
            return true;
        }

        bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            if (player->GetQuestStatus(12801) == QUEST_STATUS_INCOMPLETE)
                AddGossipItemFor(player, 0, "I am ready.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            SendGossipMenuFor(player, player->GetGossipTextId(me), me->GetGUID());

            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_highlord_darion_mograineAI(creature);
    }
};

/*######
## npc the lich king in dawn of light
######*/
class npc_the_lich_king_tirion_dawn : public CreatureScript
{
public:
    npc_the_lich_king_tirion_dawn() : CreatureScript("npc_the_lich_king_tirion_dawn") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_the_lich_king_tirion_dawnAI(creature);
    }

    struct npc_the_lich_king_tirion_dawnAI : public ScriptedAI
    {
        npc_the_lich_king_tirion_dawnAI(Creature* creature) : ScriptedAI(creature) { Reset(); }
        void Reset() override { }
        void AttackStart(Unit* /*who*/) override { } // very sample, just don't make them aggreesive
        void UpdateAI(uint32 /*diff*/) override { }
        void JustDied(Unit* /*killer*/) override { }
    };

};

// 58418 - Portal to Orgrimmar
// 58420 - Portal to Stormwind
class spell_teleport_leaders_blessing : public SpellScript
{
    PrepareSpellScript(spell_teleport_leaders_blessing);

    void HandleScriptEffect(SpellEffIndex /* effIndex */)
    {
        Player* target = GetHitPlayer();
        if (!target)
            return;

        uint32 spellID = GetSpellInfo()->Effects[EFFECT_0].CalcValue();
        uint32 questID = GetSpellInfo()->Effects[EFFECT_1].CalcValue();

        if (target->GetQuestStatus(questID) == QUEST_STATUS_COMPLETE)
            target->CastSpell(target, spellID, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_teleport_leaders_blessing::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

void AddSC_the_scarlet_enclave_c5()
{
    new npc_highlord_darion_mograine();
    new npc_the_lich_king_tirion_dawn();
    RegisterSpellScript(spell_teleport_leaders_blessing);
}
