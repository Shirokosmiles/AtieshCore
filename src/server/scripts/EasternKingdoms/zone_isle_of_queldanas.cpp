/*
 * Copyright (C) 2016-2019 AtieshCore <https://at-wow.org/>
 * Copyright (C) 2008-2019 TrinityCore <https://www.trinitycore.org/>
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

#include "GameObject.h"
#include "GameObjectAI.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "TemporarySummon.h"

enum ThalorienDawnseekerTexts
{
    SAY_THALORIEN_1 = 0,
    SAY_THALORIEN_2 = 1,
    SAY_THALORIEN_3 = 2,
    SAY_THALORIEN_4 = 3,
    SAY_THALORIEN_5 = 4,
    SAY_THALORIEN_6 = 5,
    SAY_THALORIEN_7 = 6,
    SAY_THALORIEN_8 = 7,
    SAY_THALORIEN_9 = 8,
    SAY_THALORIEN_10 = 9,

    SAY_MORLEN_1 = 0,
    SAY_MORLEN_2 = 1,
    SAY_MORLEN_3 = 2,
    SAY_MORLEN_4 = 3,
    SAY_MORLEN_5 = 4
};

enum ThalorienDawnseekerSummons
{
    SUMMON_SUNWELL_DEFENDER = 1,
    SUMMON_SCOURGE_ZOMBIE   = 2,
    SUMMON_GHOUL_INVADER    = 3,
    SUMMON_CRYPT_RAIDER     = 4
};

enum ThalorienDawnseekerActions
{
    ACTION_START_QUEST = 1
};

enum ThalorienDawnseekerEvents
{
    EVENT_INTRO_0           = 1,
    EVENT_INTRO_1           = 2,
    EVENT_INTRO_2           = 3,
    EVENT_INTRO_3           = 4,
    EVENT_SALUTE            = 5,
    EVENT_DEFENDERS_RUN     = 6,
    EVENT_DEFENDERS_RUN_2   = 7,
    EVENT_THALORIEN_GO      = 8,
    EVENT_INTRO_4           = 9,
    EVENT_SUMMON_MORLEN     = 10,
    EVENT_INTRO_5           = 11,
    EVENT_MORLEN_1          = 12,
    EVENT_SPAWN_WAVE_1      = 13,
    EVENT_SPAWN_WAVE_2      = 14,
    EVENT_SPAWN_WAVE_3      = 15,
    EVENT_WAVE_ATTACK       = 16,
    EVENT_MORLEN_2          = 17,
    EVENT_MORLEN_ATTACK     = 18,
    EVENT_OUTRO_1           = 19,
    EVENT_OUTRO_2           = 20,
    EVENT_OUTRO_3           = 21,
    EVENT_OUTRO_4           = 22,
    EVENT_KNEEL             = 23
};

enum ThalorienDawnseeker
{
    MENU_EXAMINE_REMAINS        = 10908,

    NPC_THALORIEN_DAWNSEEKER    = 37205,
    NPC_SUNWELL_DEFENDER        = 37211,
    NPC_MORLEN_GOLDGRIP         = 37542,
    NPC_SCOURGE_ZOMBIE          = 37538,
    NPC_GHOUL_INVADER           = 37539,
    NPC_CRYPT_RAIDER            = 37541,

    SPELL_BLOOD_PRESENCE        = 50689,
    SPELL_KILL_CREDIT           = 70265,
    SPELL_POLYMORPH_VISUAL      = 27123
};

uint8 const defenders = 10;
float const defendersOrientation = 5.67232f;
Position const defendersRun[] =
{
        { 11934.78f, -7064.424f, 33.38046f },
        { 11927.9f,  -7061.303f, 32.00986f },
        { 11927.81f, -7067.289f, 31.81058f },
        { 11927.89f, -7058.299f, 32.13486f },
        { 11927.9f,  -7061.303f, 32.00986f },

        { 11934.78f, -7064.424f, 33.38046f },
        { 11920.69f, -7061.134f, 30.40684f },
        { 11920.56f, -7067.133f, 30.41605f },
        { 11920.76f, -7058.135f, 30.61656f },
        { 11920.5f,  -7070.132f, 30.40836f }
};

Position const thalorienSummon = { 11795.32f, -7070.476f, 26.27511f, 5.67232f  };
Position const thalorienFight = { 11788.46f, -7063.375f, 25.79677f, 3.054326f };
Position const morlenSummon = { 11766.46f, -7050.078f, 26.19846f, 5.637414f  };

struct npc_thalorien_dawnseeker : public ScriptedAI
{
    npc_thalorien_dawnseeker(Creature* creature) : ScriptedAI(creature), _summons(me)
    {
    }

    bool GossipSelect(Player* player, uint32 menuId, uint32 /*gossipListId*/) override
    {
        if (menuId == MENU_EXAMINE_REMAINS)
        {
            CloseGossipMenuFor(player);
            DoAction(ACTION_START_QUEST);
            _playerGUID = player->GetGUID();
        }
        return false;
    }

    void DoAction(int32 action) override
    {
        if (action == ACTION_START_QUEST)
        {
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

            if (Creature* thalorien = me->SummonCreature(NPC_THALORIEN_DAWNSEEKER, thalorienSummon, TEMPSUMMON_CORPSE_DESPAWN, 0))
                _thalorienGUID = thalorien->GetGUID();
            me->SummonCreatureGroup(SUMMON_SUNWELL_DEFENDER);

            _events.ScheduleEvent(EVENT_INTRO_0, 3s);
        }
    }

    void Reset() override
    {
        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        _summons.DespawnAll();
        _playerGUID.Clear();
        _morlenGUID.Clear();
        _thalorienGUID.Clear();
        _events.Reset();
    }

    void ThalorienTalk(uint32 id)
    {
        if (Creature* thalorien = ObjectAccessor::GetCreature(*me, _thalorienGUID))
            thalorien->AI()->Talk(id);
    }

    void MorlenTalk(uint32 id)
    {
        if (Creature* morlen = ObjectAccessor::GetCreature(*me, _morlenGUID))
            morlen->AI()->Talk(id);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_INTRO_0:
                    ThalorienTalk(SAY_THALORIEN_1);

                    _events.ScheduleEvent(EVENT_INTRO_1, 5s);
                    break;
                case EVENT_INTRO_1:
                    ThalorienTalk(SAY_THALORIEN_2);

                    _events.ScheduleEvent(EVENT_INTRO_2, 6s);
                    break;
                case EVENT_INTRO_2:
                    ThalorienTalk(SAY_THALORIEN_3);

                    _events.ScheduleEvent(EVENT_INTRO_3, 7s);
                    break;

                case EVENT_INTRO_3:
                    ThalorienTalk(SAY_THALORIEN_4);

                    _events.ScheduleEvent(EVENT_SALUTE, 4s);
                    break;
                case EVENT_SALUTE:
                    for (auto& summon : _summons)
                        if (Creature* creature = ObjectAccessor::GetCreature(*me, summon))
                            creature->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);

                    _events.ScheduleEvent(EVENT_DEFENDERS_RUN, 3s);
                    break;
                case EVENT_DEFENDERS_RUN:
                {
                    _events.ScheduleEvent(EVENT_DEFENDERS_RUN_2, 3s);
                    _events.ScheduleEvent(EVENT_THALORIEN_GO, 2s);

                    uint8 defendersCount = 0;
                    for (auto& summon : _summons)
                    {
                        Creature* creature = ObjectAccessor::GetCreature(*me, summon);
                        if (!creature)
                            continue;

                        if (creature->GetEntry() != NPC_SUNWELL_DEFENDER)
                            continue;

                        defendersCount++;
                        if (defendersCount <= 5)
                            creature->SetFacingTo(defendersOrientation);
                        else
                            if (defendersCount - 1 < defenders)
                                creature->GetMotionMaster()->MovePoint(0, defendersRun[defendersCount - 1]);
                    }

                    break;
                }
                case EVENT_DEFENDERS_RUN_2:
                {
                    uint8 defendersCount = 0;
                    for (auto& summon : _summons)
                    {
                        Creature* creature = ObjectAccessor::GetCreature(*me, summon);
                        if (!creature)
                            continue;

                        if (creature->GetEntry() != NPC_SUNWELL_DEFENDER)
                            continue;

                        ++defendersCount;
                        if (defendersCount < defenders)
                            creature->GetMotionMaster()->MovePoint(0, defendersRun[defendersCount]);
                    }

                    break;
                }
                case EVENT_THALORIEN_GO:
                    if (Creature* thalorien = ObjectAccessor::GetCreature(*me, _thalorienGUID))
                    {
                        thalorien->SetWalk(true);
                        thalorien->GetMotionMaster()->MovePoint(0, thalorienFight);
                        thalorien->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                        thalorien->SetHomePosition(thalorienFight);
                    }

                    _events.ScheduleEvent(EVENT_INTRO_4, 4s);
                    break;
                case EVENT_INTRO_4:
                    ThalorienTalk(SAY_THALORIEN_5);

                    _events.ScheduleEvent(EVENT_SUMMON_MORLEN, 6s);
                    _events.ScheduleEvent(EVENT_INTRO_5, 9s);
                    break;
                case EVENT_INTRO_5:
                    ThalorienTalk(SAY_THALORIEN_6);

                    _events.ScheduleEvent(EVENT_MORLEN_1, 6s);
                    break;
                case EVENT_SUMMON_MORLEN:
                    if (Creature* morlen = me->SummonCreature(NPC_MORLEN_GOLDGRIP, morlenSummon, TEMPSUMMON_CORPSE_DESPAWN, 0))
                    {
                        _morlenGUID = morlen->GetGUID();
                        morlen->AI()->DoCastSelf(SPELL_BLOOD_PRESENCE);
                    }

                    break;
                case EVENT_MORLEN_1:
                    MorlenTalk(SAY_MORLEN_1);

                    _events.ScheduleEvent(EVENT_SPAWN_WAVE_1, 7s);
                    break;
                case EVENT_SPAWN_WAVE_1:
                    MorlenTalk(SAY_MORLEN_2);

                    me->SummonCreatureGroup(SUMMON_SCOURGE_ZOMBIE);

                    _events.ScheduleEvent(EVENT_WAVE_ATTACK, 3s);
                    break;
                case EVENT_SPAWN_WAVE_2:
                    MorlenTalk(SAY_MORLEN_3);

                    me->SummonCreatureGroup(SUMMON_GHOUL_INVADER);

                    _events.ScheduleEvent(EVENT_WAVE_ATTACK, 3s);
                    break;
                case EVENT_SPAWN_WAVE_3:
                    MorlenTalk(SAY_MORLEN_4);

                    me->SummonCreatureGroup(SUMMON_CRYPT_RAIDER);

                    _events.ScheduleEvent(EVENT_WAVE_ATTACK, 3s);
                    break;
                case EVENT_WAVE_ATTACK:
                    for (auto& summon : _summons)
                    {
                        Creature* creature = ObjectAccessor::GetCreature(*me, summon);
                        if (!creature)
                            continue;

                        if (creature->GetEntry() == NPC_THALORIEN_DAWNSEEKER ||
                            creature->GetEntry() == NPC_MORLEN_GOLDGRIP)
                            continue;

                        creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                        if (Creature* thalorien = ObjectAccessor::GetCreature(*me, _thalorienGUID))
                            creature->AI()->AttackStart(thalorien);
                    }

                    break;
                case EVENT_MORLEN_2:
                    MorlenTalk(SAY_MORLEN_5);

                    _events.ScheduleEvent(EVENT_MORLEN_ATTACK, 1s);
                    break;
                case EVENT_MORLEN_ATTACK:
                    if (Creature* morlen = ObjectAccessor::GetCreature(*me, _morlenGUID))
                    {
                        morlen->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                        if (Creature* thalorien = ObjectAccessor::GetCreature(*me, _thalorienGUID))
                            morlen->AI()->AttackStart(thalorien);
                    }

                    break;
                case EVENT_OUTRO_1:
                    if (Creature* thalorien = ObjectAccessor::GetCreature(*me, _thalorienGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                            thalorien->AI()->DoCast(player, SPELL_KILL_CREDIT);

                    ThalorienTalk(SAY_THALORIEN_7);

                    _events.ScheduleEvent(EVENT_OUTRO_2, 5s);
                    break;
                case EVENT_OUTRO_2:
                    ThalorienTalk(SAY_THALORIEN_8);

                    _events.ScheduleEvent(EVENT_OUTRO_3, 7s);
                    break;
                case EVENT_OUTRO_3:
                    if (Creature* thalorien = ObjectAccessor::GetCreature(*me, _thalorienGUID))
                        thalorien->AI()->DoCastSelf(SPELL_POLYMORPH_VISUAL);

                    ThalorienTalk(SAY_THALORIEN_9);

                    _events.ScheduleEvent(EVENT_OUTRO_4, 5s);
                    break;
                case EVENT_OUTRO_4:
                    ThalorienTalk(SAY_THALORIEN_10);

                    _events.ScheduleEvent(EVENT_KNEEL, 6s);
                    break;
                case EVENT_KNEEL:
                    if (Creature* thalorien = ObjectAccessor::GetCreature(*me, _thalorienGUID))
                    {
                        thalorien->SetStandState(UNIT_STAND_STATE_KNEEL);
                        thalorien->DespawnOrUnsummon(5 * IN_MILLISECONDS);
                    }

                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

                    break;
            }
        }
    }

    void JustSummoned(Creature* summon) override
    {
        _summons.Summon(summon);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        _summons.Despawn(summon);

        if (_summons.size() == 2)
        {
            if (summon->GetEntry() == NPC_SCOURGE_ZOMBIE)
                _events.ScheduleEvent(EVENT_SPAWN_WAVE_2, 1s);
            else if (summon->GetEntry() == NPC_GHOUL_INVADER)
                _events.ScheduleEvent(EVENT_SPAWN_WAVE_3, 1s);
            else if (summon->GetEntry() == NPC_CRYPT_RAIDER)
                _events.ScheduleEvent(EVENT_MORLEN_2, 1s);
        }
        else if (_summons.size() == 1)
        {
            if (summon->GetEntry() == NPC_MORLEN_GOLDGRIP)
                _events.ScheduleEvent(EVENT_OUTRO_1, 2s);
        }
    }

private:
    EventMap _events;
    SummonList _summons;
    ObjectGuid _playerGUID;
    ObjectGuid _thalorienGUID;
    ObjectGuid _morlenGUID;
};

enum SaysQueldelar
{
    SAY_QUELDELAR_1 = 11,  // Damas y Caballeros, les presento a $N, portador de Quel'Delar.
    SAY_QUELDELAR_2 = 0,  // Is it true that this is Quel\'Delar?
    SAY_QUELDELAR_3 = 1,  // We will see.
    SAY_QUELDELAR_4 = 2,  // Look Lor\'themar! It is Quel\'Delar without a doubt.
    SAY_QUELDELAR_5 = 3,  // So be it. You have my thanks, $N, for returning Quel\'Delar to its rightful owners
    SAY_QUELDELAR_6 = 4,  // What means this treason?
    SAY_QUELDELAR_7 = 5,  // Drop the weapon and surrender, traitor.
    SAY_QUELDELAR_8 = 6,  // This is not my fault, Rommath. It is not a treason.
    SAY_QUELDELAR_9 = 7,  // Remove your men. The stupidity of Lor\'themar himself caused his wounds. Quel\'Delar is not chosen, it chooses it\'s master.
    SAY_QUELDELAR_10 = 8,  // Guards, return to your posts
    SAY_QUELDELAR_11 = 9,  // You will have what you seek, $N. Take the sword and leave. And your Auric, be careful what you say in this sacred place.
    SAY_QUELDELAR_12 = 10,  // Take the sword through this portal into Dalaran, $N. You have done what many quel\'dorei have dreamed for years. At last Quel\'Delar is restored.
};

enum QuelDelarEvents
{
    EVENT_QUEST_STEP_1 = 1,
    EVENT_QUEST_STEP_2 = 2,
    EVENT_QUEST_STEP_3 = 3,
    EVENT_QUEST_STEP_4 = 4,
    EVENT_QUEST_STEP_5 = 5,
    EVENT_QUEST_STEP_6 = 6,
    EVENT_QUEST_STEP_7 = 7,
    EVENT_QUEST_STEP_8 = 8,
    EVENT_QUEST_STEP_9 = 9,
    EVENT_QUEST_STEP_10 = 10,
    EVENT_QUEST_STEP_11 = 11,
    EVENT_QUEST_STEP_12 = 12,
    EVENT_QUEST_STEP_13 = 13,
    EVENT_QUEST_STEP_14 = 14,
    EVENT_QUEST_STEP_15 = 15,
    EVENT_QUEST_STEP_16 = 16
};

enum QuelDelarActions
{
    ACTION_START_EVENT = 1
};

enum QuelDelarCreatures
{
    NPC_ROMMATH = 37763,
    NPC_THERON = 37764,
    NPC_AURIC = 37765,
    NPC_QUEL_GUARD = 37781,
    NPC_CASTER_BUNNY = 37746
};

enum QuelDelarGameobjects
{
    GO_QUEL_DANAR = 201794
};

enum QuelDelarMisc
{
    ITEM_TAINTED_QUELDANAR_1 = 49879,
    ITEM_TAINTED_QUELDANAR_2 = 49889,
    SPELL_WRATH_QUEL_DANAR = 70493,
    SPELL_ICY_PRISON = 70540
};

/*######
## npc_queldelar_sunwell_plateau
######*/
class item_tainted_queldelar : public ItemScript
{
public:
    item_tainted_queldelar() : ItemScript("item_tainted_queldelar") { }
    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/)
    {
        InstanceScript *instance = player->GetInstanceScript();
        if (instance && player->FindNearestCreature(NPC_CASTER_BUNNY, 20.0f, true))
        {

            if (Creature *introducer = player->FindNearestCreature(NPC_CASTER_BUNNY, 20.0f, true))
            {
                Unit::Kill(introducer, introducer, false);
            }
            return true;
        }

        else
            return false;
    }
};

class npc_queldelar_sunwell_plateau : public CreatureScript
{
public:
    npc_queldelar_sunwell_plateau() : CreatureScript("npc_queldelar_sunwell_plateau") { }

    struct npc_queldelar_sunwell_plateauAI : public ScriptedAI
    {
        npc_queldelar_sunwell_plateauAI(Creature* creature) : ScriptedAI(creature) { }
        int i = 0;
        void MoveInLineOfSight(Unit * who) override
        {
            if (!who)
                return;

            if (who && me->IsWithinDistInMap(who, 150.0f) && me->FindNearestCreature(NPC_CASTER_BUNNY, 200.0f, false) && i == 0)
            {
                DoAction(ACTION_START_EVENT);
                i = 1;
                return;
            }
        }

        void Reset() override
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            events.Reset();
        }

        void DoAction(int32 action) override
        {
            switch (action)
            {
            case ACTION_START_EVENT:
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                events.ScheduleEvent(EVENT_QUEST_STEP_1, 0);
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            switch (events.ExecuteEvent())
            {
            case EVENT_QUEST_STEP_1:
                me->Yell(SAY_QUELDELAR_1);
                if (Creature* rommath = me->FindNearestCreature(NPC_ROMMATH, 100.0f, true))  // Rommath
                    uiRommath = rommath->GetGUID();

                if (Creature* theron = me->FindNearestCreature(NPC_THERON, 100.0f, true))    // Lor'Themar Theron
                    uiTheron = theron->GetGUID();

                if (Creature* auric = me->FindNearestCreature(NPC_AURIC, 100.0f, true))      // Auric
                    uiAuric = auric->GetGUID();

                if (GameObject* quelDelar = me->SummonGameObject(GO_QUEL_DANAR, 1683.99f, 620.231f, 29.3599f, 0.410932f, QuaternionData(), 0))
                {
                    uiQuelDelar = quelDelar->GetGUID();
                    quelDelar->SetFlag(GAMEOBJECT_FLAGS, 5);
                }

                if (Player* player = me->SelectNearestPlayer(200.0f))
                {
                    player->DestroyItemCount(ITEM_TAINTED_QUELDANAR_1, 1, true);
                    player->DestroyItemCount(ITEM_TAINTED_QUELDANAR_2, 1, true);
                }
                events.ScheduleEvent(EVENT_QUEST_STEP_2, 2 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_2:
                if (Creature* guard = me->FindNearestCreature(NPC_QUEL_GUARD, 100.0f, true))
                    guard->AI()->Talk(SAY_QUELDELAR_2);
                events.ScheduleEvent(EVENT_QUEST_STEP_3, 1 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_3:
                if (Creature* theron = ObjectAccessor::GetCreature(*me, uiTheron))
                    theron->AI()->Talk(SAY_QUELDELAR_3);
                events.ScheduleEvent(EVENT_QUEST_STEP_4, 4 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_4:
                if (Creature* rommath = ObjectAccessor::GetCreature(*me, uiRommath))
                    rommath->GetMotionMaster()->MovePoint(1, 1675.8f, 617.19f, 28.0504f);
                if (Creature*auric = ObjectAccessor::GetCreature(*me, uiAuric))
                    auric->GetMotionMaster()->MovePoint(1, 1681.77f, 612.084f, 28.4409f);
                events.ScheduleEvent(EVENT_QUEST_STEP_5, 6 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_5:
                if (Creature* rommath = ObjectAccessor::GetCreature(*me, uiRommath))
                {
                    rommath->SetOrientation(0.3308f);
                    rommath->AI()->Talk(SAY_QUELDELAR_4);
                }
                if (Creature* auric = ObjectAccessor::GetCreature(*me, uiAuric))
                    auric->SetOrientation(1.29057f);
                if (Creature* theron = ObjectAccessor::GetCreature(*me, uiTheron))
                    theron->GetMotionMaster()->MovePoint(1, 1677.07f, 613.122f, 28.0504f);
                events.ScheduleEvent(EVENT_QUEST_STEP_6, 10 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_6:
                if (Creature* theron = ObjectAccessor::GetCreature(*me, uiTheron))
                {
                    theron->AI()->Talk(SAY_QUELDELAR_5);
                    theron->GetMotionMaster()->MovePoint(1, 1682.3f, 618.459f, 27.9581f);
                }
                events.ScheduleEvent(EVENT_QUEST_STEP_7, 4 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_7:
                if (Creature* theron = ObjectAccessor::GetCreature(*me, uiTheron))
                    theron->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                events.ScheduleEvent(EVENT_QUEST_STEP_8, 0.8 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_8:
                if (Creature* theron = ObjectAccessor::GetCreature(*me, uiTheron))
                    theron->CastSpell(theron, SPELL_WRATH_QUEL_DANAR, true);
                events.ScheduleEvent(EVENT_QUEST_STEP_9, 1 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_9:
                if (Creature* rommath = ObjectAccessor::GetCreature(*me, uiRommath))
                {
                    if (Player* player = me->SelectNearestPlayer(200.0f))
                        rommath->AddAura(SPELL_ICY_PRISON, player);
                    rommath->AI()->Talk(SAY_QUELDELAR_6);
                }
                if (Creature* guard = me->FindNearestCreature(NPC_QUEL_GUARD, 200.0f))
                {
                    guard->GetMotionMaster()->MovePoint(0, 1681.1f, 614.955f, 28.4983f);
                    guard->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY1H);
                }
                events.ScheduleEvent(EVENT_QUEST_STEP_10, 3 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_10:
                if (Creature* guard = me->FindNearestCreature(NPC_QUEL_GUARD, 200.0f))
                    guard->AI()->Talk(SAY_QUELDELAR_7);
                events.ScheduleEvent(EVENT_QUEST_STEP_11, 2 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_11:
                if (Creature* auric = ObjectAccessor::GetCreature(*me, uiAuric))
                    auric->AI()->Talk(SAY_QUELDELAR_8);
                events.ScheduleEvent(EVENT_QUEST_STEP_12, 6 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_12:
                if (Creature* auric = ObjectAccessor::GetCreature(*me, uiAuric))
                    auric->AI()->Talk(SAY_QUELDELAR_9);
                events.ScheduleEvent(EVENT_QUEST_STEP_13, 5 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_13:
                if (Creature* rommath = ObjectAccessor::GetCreature(*me, uiRommath))
                    rommath->AI()->Talk(SAY_QUELDELAR_10);
                events.ScheduleEvent(EVENT_QUEST_STEP_14, 2 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_14:
                if (Creature* guard = me->FindNearestCreature(NPC_QUEL_GUARD, 200.0f))
                {
                    guard->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                    guard->GetMotionMaster()->MovePoint(0, guard->GetHomePosition());
                }
                if (Creature* rommath = ObjectAccessor::GetCreature(*me, uiRommath))
                {
                    rommath->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                    rommath->AI()->Talk(SAY_QUELDELAR_11);
                }
                events.ScheduleEvent(EVENT_QUEST_STEP_15, 7 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_15:
                if (Creature* auric = ObjectAccessor::GetCreature(*me, uiAuric))
                {
                    auric->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                    auric->AI()->Talk(SAY_QUELDELAR_12);
                    if (GameObject* quelDelar = me->FindNearestGameObject(GO_QUEL_DANAR, 100.0f))
                        quelDelar->RemoveFlag(GAMEOBJECT_FLAGS, 5);
                }
                events.ScheduleEvent(EVENT_QUEST_STEP_16, 2 * IN_MILLISECONDS);
                break;
            case EVENT_QUEST_STEP_16:
                if (Creature* auric = ObjectAccessor::GetCreature(*me, uiAuric))
                    auric->GetMotionMaster()->MovePoint(0, auric->GetHomePosition());
                if (Creature* rommath = ObjectAccessor::GetCreature(*me, uiRommath))
                    rommath->GetMotionMaster()->MovePoint(0, rommath->GetHomePosition());
                if (Creature* theron = ObjectAccessor::GetCreature(*me, uiTheron))
                    theron->DespawnOrUnsummon(5 * IN_MILLISECONDS);
                break;
            default:
                break;
            }
        }
    private:
        EventMap events;
        ObjectGuid uiRommath;
        ObjectGuid uiTheron;
        ObjectGuid uiAuric;
        ObjectGuid uiQuelDelar;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_queldelar_sunwell_plateauAI(creature);
    }
};

class npc_sunwell_warder : public CreatureScript
{
public:
    npc_sunwell_warder() : CreatureScript("npc_sunwell_warder") { }

    struct npc_sunwell_warderAI : public ScriptedAI
    {
        npc_sunwell_warderAI(Creature* creature) : ScriptedAI(creature) { }

        bool GossipHello(Player* player) override
        {
            player->PrepareGossipMenu(me, 0);
            if (player->HasItemCount(49879, 1) || player->HasItemCount(49889, 1))
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Take me to the Sunwell", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SendPreparedGossip(me);
            return true;
        }

        bool GossipSelect(Player* player, uint32 /*uiSender*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            player->PlayerTalkClass->ClearMenus();
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                CloseGossipMenuFor(player);
                player->SetCanEnterInInstanceOrRaidCustom(true);
                player->TeleportTo(580, 1728.5f, 709.219f, 71.1905f, 2.78676f);
                player->SetPhaseMask(2, true);
                break;
            default:
                return false; // nothing defined -> trinity core handling
            }
            return true; // no default handling -> prevent trinity core handling
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sunwell_warderAI(creature);
    }
};

class go_dalaran_portal_sunwell : public GameObjectScript
{
public:
    go_dalaran_portal_sunwell() : GameObjectScript("go_dalaran_portal_sunwell") {}

    struct go_dalaran_portal_sunwellAI : public GameObjectAI
    {
        go_dalaran_portal_sunwellAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            player->PrepareGossipMenu(me, 0);
            player->SetCanEnterInInstanceOrRaidCustom(false);
            player->TeleportTo(571, 5804.149902f, 624.770996f, 647.767029f, 1.640000f);
            player->SetPhaseMask(1, true);
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_dalaran_portal_sunwellAI(go);
    }
};

void AddSC_isle_of_queldanas()
{
    RegisterCreatureAI(npc_thalorien_dawnseeker);
    new go_dalaran_portal_sunwell();
    new npc_sunwell_warder();
    new npc_queldelar_sunwell_plateau();
    new item_tainted_queldelar();
}
