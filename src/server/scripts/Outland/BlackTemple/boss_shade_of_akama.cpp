/*
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
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

/*
Name: Boss_Shade_of_Akama
%Complete: 80
Comment: WIP A few more adds to script, ending script, and bugs.
Category: Black Temple
*/

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "GridNotifiers.h"
#include "black_temple.h"

enum Says
{
    // Akama Ending cinematic text
    SAY_BROKEN_FREE_0                = 0,
    SAY_BROKEN_FREE_1                = 1,
    SAY_BROKEN_FREE_2                = 2
};

enum Spells
{
    // Akama
    SPELL_STEALTH                    = 34189, // On Spawn
    SPELL_AKAMA_SOUL_CHANNEL         = 40447, // Cast on self hits Shade
    SPELL_FIXATE                     = 40607, // Cast on self hits Shade
    SPELL_CHAIN_LIGHTNING            = 39945, // Combat
    SPELL_DESTRUCTIVE_POISON         = 40874, // Combat
    // Shade
    SPELL_THREAT                     = 41602, // self cast hits Akama
    SPELL_SHADE_OF_AKAMA_TRIGGER     = 40955, // Cast on death
    SPELL_AKAMA_SOUL_EXPEL_CHANNEL   = 40927, // must hit shade
    SPELL_AKAMA_SOUL_EXPEL           = 40902, // the one he cast
    // Ashtongue Channeler
    SPELL_SHADE_SOUL_CHANNEL         = 40401,
    SPELL_SHADE_SOUL_CHANNEL_2       = 40520,
    SPELL_SHADOWFORM                 = 40973, // Cast on Shade
    // Creature Spawner
    SPELL_ASHTONGUE_WAVE_B           = 42035,
    SPELL_SUMMON_ASHTONGUE_SORCERER  = 40476,
    SPELL_SUMMON_ASHTONGUE_DEFENDER  = 40474,
    // Ashtongue Defender
    SPELL_DEBILITATING_STRIKE        = 41178,
    SPELL_HEROIC_STRIKE              = 41975,
    SPELL_SHIELD_BASH                = 41180,
    SPELL_WINDFURY                   = 38229,
    // Ashtongue Rogue
    SPELL_DEBILITATING_POISON        = 41978,
    SPELL_EVISCERATE                 = 41177,
    // Ashtongue Elementalist
    SPELL_RAIN_OF_FIRE               = 42023,
    SPELL_LIGHTNING_BOLT             = 42024,
    // Ashtongue Spiritbinder
    SPELL_SPIRIT_MEND                = 42025,
    SPELL_CHAIN_HEAL                 = 42027,
    SPELL_SPIRITBINDER_SPIRIT_HEAL   = 42317
};

enum Creatures
{
    NPC_ASHTONGUE_CHANNELER          = 23421,
    NPC_ASHTONGUE_SORCERER           = 23215,
    NPC_ASHTONGUE_DEFENDER           = 23216,
    NPC_ASHTONGUE_ELEMENTALIST       = 23523,
    NPC_ASHTONGUE_ROGUE              = 23318,
    NPC_ASHTONGUE_SPIRITBINDER       = 23524,
    NPC_ASHTONGUE_BROKEN             = 23319,
    NPC_CREATURE_SPAWNER_AKAMA       = 23210
};

enum Factions
{
    FACTION_FRIENDLY                 = 1820,
    FACTION_COMBAT                   = 1868
};

enum Actions
{
    ACTION_CHANNELER_DIED     = 1,
    ACTION_START_SPAWNING     = 2,
    ACTION_STOP_SPAWNING      = 3,
    ACTION_DESPAWN_ALL_SPAWNS = 4,
};

enum Events
{
    // Akama
    EVENT_SHADE_START                = 1,
    EVENT_SHADE_CHANNEL              = 2,
    EVENT_FIXATE                     = 3,
    EVENT_CHAIN_LIGHTNING            = 4,
    EVENT_DESTRUCTIVE_POISON         = 5,
    // Shade
    EVENT_RESET_ENCOUNTER            = 6,
    EVENT_FIND_CHANNELERS_SPAWNERS   = 7,
    EVENT_SET_CHANNELERS_SPAWNERS    = 8,
    EVENT_START_ATTACK_AKAMA         = 9,
    EVENT_ADD_THREAT                 = 10,
    // Creature spawner
    EVENT_SPAWN_WAVE_B               = 11,
    EVENT_SUMMON_ASHTONGUE_SORCERER  = 12,
    EVENT_SUMMON_ASHTONGUE_DEFENDER  = 13,
    // Channeler
    EVENT_CHANNEL                    = 14,
    // Ashtongue Sorcerer
    EVENT_SORCERER_CHANNEL           = 15,
    // Ashtongue Defender
    EVENT_DEBILITATING_STRIKE        = 16,
    EVENT_HEROIC_STRIKE              = 17,
    EVENT_SHIELD_BASH                = 18,
    EVENT_WINDFURY                   = 29,
    // Ashtongue Rogue
    EVENT_DEBILITATING_POISON        = 20,
    EVENT_EVISCERATE                 = 21,
    // Ashtongue Elementalist
    EVENT_RAIN_OF_FIRE               = 22,
    EVENT_LIGHTNING_BOLT             = 23,
    // Ashtongue Spiritbinder
    EVENT_SPIRIT_HEAL                = 24,
    // spawn of event npc
    EVENT_START_FIGHT                = 25,
    EVENT_END_FIGHT                  = 26,
    EVENT_AFTER_BATTLE               = 27,
    EVENT_FIRST_END_WAVE             = 28,
    EVENT_SECOND_END_WAVE            = 29,
    EVENT_3_END_WAVE                 = 30,
    EVENT_3_END_WAVE_MOVE_1          = 31,
    EVENT_3_END_WAVE_MOVE_2          = 32,
    EVENT_3_END_WAVE_MOVE_3          = 33,
    EVENT_END_EMOTE                  = 34
};

enum PhaseNpcAkama
{
    PHASE_NPC_AKAMA_NULL = 0,
    PHASE_CHANNEL = 1,
    PHASE_FIGHT_WITH_SHADE = 2,
    PHASE_WALK_AND_MINIOS = 3
};

Position const SummonPositions[9] =
{
    { 487.8522f, 429.9765f, 112.7839f, 4.0f }, // 1
    { 482.5728f, 431.5027f, 112.7839f, 4.3f }, // 2
    { 486.9953f, 431.8665f, 112.7839f, 3.9f }, // 3

    { 509.4674f, 401.0299f, 112.7839f, 3.1f }, // 4
    { 508.5506f, 405.7852f, 112.7839f, 3.1f }, // 5
    { 508.3435f, 396.7022f, 112.7839f, 3.0f }, // 6

    { 493.2539f, 372.1406f, 112.7839f, 2.3f }, // 7
    { 494.4277f, 375.8009f, 112.7839f, 2.24f }, // 8
    { 488.7583f, 369.7834f, 112.7838f, 2.1f }, // 9
};

Position const SummonWP[9] =
{
    { 476.5457f, 417.7671f, 115.5209f }, // 1
    { 472.4048f, 420.4574f, 116.2645f }, // 2
    { 476.5458f, 415.2565f, 115.5131f }, // 3

    { 486.0755f, 401.2258f, 112.7839f }, // 4
    { 485.2746f, 406.8502f, 112.7839f }, // 5
    { 484.6188f, 396.9120f, 112.7839f }, // 6

    { 482.2252f, 382.8841f, 112.7838f }, // 7
    { 482.8166f, 388.1901f, 112.7838f }, // 8
    { 477.4723f, 382.1891f, 114.4382f }, // 9
};

Position const ShadeWP = { 512.4877f, 400.7993f, 112.7837f };

// ########################################################
// Shade of Akama
// ########################################################

class boss_shade_of_akama : public CreatureScript
{
public:
    boss_shade_of_akama() : CreatureScript("boss_shade_of_akama") { }

    struct boss_shade_of_akamaAI : public BossAI
    {
        boss_shade_of_akamaAI(Creature* creature) : BossAI(creature, DATA_SHADE_OF_AKAMA)
        {
            Initialize();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void Initialize()
        {
            combatStarted = false;
            akamaReached = false;
            HasKilledAkama = false;
            HasKilledAkamaAndReseting = false;
            DeadShade = false;
            DeadShadeNoRepeat = false;
        }

        void Reset() override
        {
            _Reset();
            if (!HasKilledAkamaAndReseting)
            {
                for (GuidList::const_iterator itr = Channelers.begin(); itr != Channelers.end(); ++itr)
                    if (Creature* Channeler = ObjectAccessor::GetCreature(*me, *itr))
                        Channeler->DespawnOrUnsummon();

                for (GuidList::const_iterator itr = Spawners.begin(); itr != Spawners.end(); ++itr)
                    if (Creature* Spawner = ObjectAccessor::GetCreature(*me, *itr))
                        Spawner->AI()->DoAction(ACTION_DESPAWN_ALL_SPAWNS);

                events.ScheduleEvent(EVENT_FIND_CHANNELERS_SPAWNERS, 3000);
                events.ScheduleEvent(EVENT_RESET_ENCOUNTER, 5000);
            }

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);

            me->SetWalk(true);
            Initialize();
        }

        void EnterCombat(Unit* /*who*/) override { }

        void AttackStart(Unit* who) override
        {
            if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
            {
                if (Creature* Akama = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_AKAMA_SHADE)))
                    if (Akama->IsAlive())
                        ScriptedAI::AttackStart(Akama);
            }
            else
                ScriptedAI::AttackStart(who);
        }

        void JustDied(Unit* /*killer*/) override
        {
            DeadShade = true;
            instance->SetBossState(DATA_SHADE_OF_AKAMA, DONE);
        }

        void DoAction(int32 actionId) override
        {
            if (actionId == ACTION_CHANNELER_DIED)
                me->RemoveAuraFromStack(SPELL_SHADE_SOUL_CHANNEL_2);

            UpdateSpeed();
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_AKAMA_SOUL_CHANNEL)
            {
                combatStarted = true;
                events.ScheduleEvent(EVENT_START_ATTACK_AKAMA, 500);
                events.ScheduleEvent(EVENT_SET_CHANNELERS_SPAWNERS, 1000);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                if (Creature* Akama = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_AKAMA_SHADE)))
                    me->AddThreat(Akama, 10000000.0f);
            }
            else if (spell->Id == SPELL_SHADE_SOUL_CHANNEL_2)
                UpdateSpeed();
        }

        void UpdateSpeed()
        {
            float moveSpeed = 0.2f;

            if (me->GetAuraCount(SPELL_SHADE_SOUL_CHANNEL_2) <= 3)
            {
                moveSpeed = (2.0f - (0.6f * me->GetAuraCount(SPELL_SHADE_SOUL_CHANNEL_2)));
                me->SetSpeedRate(MOVE_WALK, moveSpeed / 2.5f);
                me->SetSpeedRate(MOVE_RUN, (moveSpeed * 2) / 7);
                me->ClearUnitState(UNIT_STATE_ROOT);
            }
            else
                me->AddUnitState(UNIT_STATE_ROOT);
        }

        void UpdateAI(uint32 diff) override
        {
            if (HasKilledAkamaAndReseting)
                return;

            events.Update(diff);

            if (!combatStarted)
            {
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_RESET_ENCOUNTER:
                            if (Creature* Akama = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_AKAMA_SHADE)))
                                if (!Akama->IsAlive())
                                    Akama->Respawn();
                            break;
                        case EVENT_FIND_CHANNELERS_SPAWNERS:
                        {
                            std::list<Creature*> ChannelerList;
                            me->GetCreatureListWithEntryInGrid(ChannelerList, NPC_ASHTONGUE_CHANNELER, 15.0f);

                            if (!ChannelerList.empty())
                                for (std::list<Creature*>::const_iterator itr = ChannelerList.begin(); itr != ChannelerList.end(); ++itr)
                                {
                                    Channelers.push_back((*itr)->GetGUID());
                                    if ((*itr)->isDead())
                                        (*itr)->Respawn();
                                }

                            std::list<Creature*> SpawnerList;
                            me->GetCreatureListWithEntryInGrid(SpawnerList, NPC_CREATURE_SPAWNER_AKAMA, 90.0f);

                            if (!SpawnerList.empty())
                                for (std::list<Creature*>::const_iterator itr = SpawnerList.begin(); itr != SpawnerList.end(); ++itr)
                                    Spawners.push_back((*itr)->GetGUID());

                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STUN);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            else
            {
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SET_CHANNELERS_SPAWNERS:
                        {
                            for (GuidList::const_iterator itr = Channelers.begin(); itr != Channelers.end(); ++itr)
                                if (Creature* Channeler = ObjectAccessor::GetCreature(*me, *itr))
                                    Channeler->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                            for (GuidList::const_iterator itr = Spawners.begin(); itr != Spawners.end(); ++itr)
                                if (Creature* Spawner = ObjectAccessor::GetCreature(*me, *itr))
                                    Spawner->AI()->DoAction(ACTION_START_SPAWNING);
                            break;
                        }
                        case EVENT_START_ATTACK_AKAMA:
                            if (!akamaReached)
                            {
                                me->GetMotionMaster()->MovePoint(0, ShadeWP, false);
                                events.ScheduleEvent(EVENT_START_ATTACK_AKAMA, 1000);
                            }
                            else
                            {
                                me->StopMoving();
                                me->GetMotionMaster()->Clear(true);
                            }

                            break;
                        case EVENT_ADD_THREAT:
                            DoCast(SPELL_THREAT);
                            events.ScheduleEvent(EVENT_ADD_THREAT, 3500);
                            break;
                        default:
                            break;
                    }
                }

                if (HasKilledAkama)
                {
                    if (!HasKilledAkamaAndReseting)
                    {
                        HasKilledAkamaAndReseting = true;
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        instance->SetBossState(DATA_SHADE_OF_AKAMA, NOT_STARTED);
                        me->RemoveAllAurasExceptType(SPELL_AURA_DUMMY);
                        me->DeleteThreatList();
                        me->CombatStop();
                        me->GetMotionMaster()->MoveTargetedHome();
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                        combatStarted = false;

                        if (Creature* Akama = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_AKAMA_SHADE)))
                            Akama->DespawnOrUnsummon();

                        for (GuidList::const_iterator itr = Channelers.begin(); itr != Channelers.end(); ++itr)
                            if (Creature* Channeler = ObjectAccessor::GetCreature(*me, *itr))
                                Channeler->DespawnOrUnsummon();

                        for (GuidList::const_iterator itr = Spawners.begin(); itr != Spawners.end(); ++itr)
                            if (Creature* Spawner = ObjectAccessor::GetCreature(*me, *itr))
                                Spawner->AI()->DoAction(ACTION_DESPAWN_ALL_SPAWNS);

                        events.ScheduleEvent(EVENT_FIND_CHANNELERS_SPAWNERS, 10000);
                        events.ScheduleEvent(EVENT_RESET_ENCOUNTER, 20000);
                    }
                }

                if (!akamaReached)
                {
                    if (Creature* Akama = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_AKAMA_SHADE)))
                    {
                        if (me->IsWithinDist(Akama, 2.0f, false))
                        {
                            akamaReached = true;                            

                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                            events.CancelEvent(EVENT_START_ATTACK_AKAMA);
                            events.ScheduleEvent(EVENT_ADD_THREAT, 100);

                            me->StopMoving();
                            me->GetMotionMaster()->Clear(true);

                            for (GuidList::const_iterator itr = Spawners.begin(); itr != Spawners.end(); ++itr)
                                if (Creature* Spawner = ObjectAccessor::GetCreature(*me, *itr))
                                    Spawner->AI()->DoAction(ACTION_STOP_SPAWNING);
                        }
                    }
                }
                else
                    DoMeleeAttackIfReady();
            }
        }

        public:
            bool HasKilledAkama;    
            bool akamaReached;
            bool DeadShade;
            bool DeadShadeNoRepeat;
        private:
            GuidList Channelers;
            GuidList Spawners;
            bool combatStarted;                      
            bool HasKilledAkamaAndReseting;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<boss_shade_of_akamaAI>(creature);
    }
};

// ########################################################
// Akama
// ########################################################

class npc_akama_shade : public CreatureScript
{
public:
    npc_akama_shade() : CreatureScript("npc_akama_shade") { }

    struct npc_akamaAI : public ScriptedAI
    {
        npc_akamaAI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
            instance = creature->GetInstanceScript();
        }

        void Initialize()
        {
            StartChannel = false;
            StartCombat = false;
            HasYelledOnce = false;

            Phase = PHASE_NPC_AKAMA_NULL;

            for (ObjectGuid summon : summons)
                summon = ObjectGuid::Empty;
        }

        void Reset() override
        {
            me->setFaction(FACTION_FRIENDLY);
            DoCast(me, SPELL_STEALTH);
            Initialize();

            if (instance->GetBossState(DATA_SHADE_OF_AKAMA) != DONE)
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }

        void JustDied(Unit* /*killer*/) override
        {
            if (Creature* Shade = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_SHADE_OF_AKAMA)))
                if (Shade->IsAlive())
                    ENSURE_AI(boss_shade_of_akama::boss_shade_of_akamaAI, Shade->AI())->HasKilledAkama = true;
            me->GetMotionMaster()->Clear(true);
            me->GetMotionMaster()->MoveIdle();
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_THREAT && !StartCombat)
            {
                me->ClearUnitState(UNIT_STATE_ROOT);
                me->RemoveAura(SPELL_AKAMA_SOUL_CHANNEL);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
                if (Creature* Shade = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_SHADE_OF_AKAMA)))
                    Shade->RemoveAura(SPELL_AKAMA_SOUL_CHANNEL);
                StartCombat = true;
            }
        }

        void EnterPhase(PhaseNpcAkama NextPhase)
        {
            switch (NextPhase)
            {
                case PHASE_CHANNEL:
                    events.ScheduleEvent(EVENT_SHADE_START, 500);                  
                    break;
                case PHASE_FIGHT_WITH_SHADE:
                    me->InterruptNonMeleeSpells(0);                    
                    me->ClearUnitState(UNIT_STATE_ROOT);
                    me->ClearUnitState(UNIT_STATE_STUNNED);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);

                    if (Creature* Shade = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_AKAMA_SHADE)))
                        if (Shade->IsAlive())
                            ScriptedAI::AttackStart(Shade);    

                    events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 2000);
                    events.ScheduleEvent(EVENT_DESTRUCTIVE_POISON, 5000);
                    break;
                case PHASE_WALK_AND_MINIOS:                                        
                    me->setFaction(FACTION_FRIENDLY); 
                    me->StopMoving();
                    me->GetMotionMaster()->Clear(true);                    
                    events.ScheduleEvent(EVENT_FIRST_END_WAVE, 500);
                    break;
                default:
                    break;
            }
            Phase = NextPhase;
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);                          

            if (Phase == PHASE_CHANNEL)
            {
                if (Creature* Shade = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_SHADE_OF_AKAMA)))
                    if (Shade->IsAlive())
                        if (ENSURE_AI(boss_shade_of_akama::boss_shade_of_akamaAI, Shade->AI())->akamaReached == true)
                        {
                            events.ScheduleEvent(EVENT_START_FIGHT, 500);
                        }

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_SHADE_START:
                        instance->SetBossState(DATA_SHADE_OF_AKAMA, IN_PROGRESS);
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        me->RemoveAura(SPELL_STEALTH);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->SetWalk(true);
                        me->GetMotionMaster()->MovePoint(0, 517.4877f, 400.7993f, 112.7837f, false);
                        me->SetPosition(517.4877f, 400.7993f, 112.7837f, me->GetOrientation());
                        events.ScheduleEvent(EVENT_SHADE_CHANNEL, 10000);
                        break;
                    case EVENT_SHADE_CHANNEL:
                        me->AddUnitState(UNIT_STATE_ROOT);
                        me->SetFacingTo(3.118662f);
                        DoCast(me, SPELL_AKAMA_SOUL_CHANNEL);
                        me->setFaction(FACTION_COMBAT);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        events.ScheduleEvent(EVENT_FIXATE, 5000);
                        break;
                    case EVENT_FIXATE:
                        DoCast(SPELL_FIXATE);
                        StartChannel = false;                        
                        break;
                    case EVENT_START_FIGHT:
                        EnterPhase(PHASE_FIGHT_WITH_SHADE);
                        break;
                    default:
                        break;
                    }
                }
            }
            else if (Phase == PHASE_FIGHT_WITH_SHADE)
            {
                if (Creature* Shade = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_SHADE_OF_AKAMA)))
                    if (!Shade->IsAlive())
                        if (ENSURE_AI(boss_shade_of_akama::boss_shade_of_akamaAI, Shade->AI())->DeadShade == true && ENSURE_AI(boss_shade_of_akama::boss_shade_of_akamaAI, Shade->AI())->DeadShadeNoRepeat == false)
                        {
                            events.ScheduleEvent(EVENT_END_FIGHT, 500);
                            ENSURE_AI(boss_shade_of_akama::boss_shade_of_akamaAI, Shade->AI())->DeadShadeNoRepeat = true; // only for 1 time for execute event
                        }

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_CHAIN_LIGHTNING:
                        DoCast(SPELL_CHAIN_LIGHTNING);
                        events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, urand(10000, 15000));
                        break;
                    case EVENT_DESTRUCTIVE_POISON:
                        DoCast(me, SPELL_DESTRUCTIVE_POISON);
                        events.ScheduleEvent(EVENT_DESTRUCTIVE_POISON, urand(4000, 5000));
                        break;
                    case EVENT_END_FIGHT:
                        events.CancelEvent(EVENT_CHAIN_LIGHTNING);
                        events.CancelEvent(EVENT_DESTRUCTIVE_POISON);
                        me->InterruptNonMeleeSpells(0);
                        me->RemoveMovementImpairingAuras();
                        me->AttackStop();
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovePoint(0, 468.4435f, 401.1062f, 118.5379f, true);
                        events.ScheduleEvent(EVENT_AFTER_BATTLE, 7000);
                        break;
                    case EVENT_AFTER_BATTLE:
                        me->SetFacingTo(0.1f);
                        EnterPhase(PHASE_WALK_AND_MINIOS);                        
                        break;
                    default:
                        break;
                    }
                }

                DoMeleeAttackIfReady();
            }
            else if (Phase == PHASE_WALK_AND_MINIOS)
            {
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {                    
                    case EVENT_FIRST_END_WAVE:                        
                        SummonEndWave(0);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                        Talk(SAY_BROKEN_FREE_0);
                        events.ScheduleEvent(EVENT_3_END_WAVE_MOVE_1, 500);
                        break;
                    case EVENT_SECOND_END_WAVE:
                        SummonEndWave(1);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                        Talk(SAY_BROKEN_FREE_1);
                        events.ScheduleEvent(EVENT_3_END_WAVE_MOVE_2, 500);
                        break;
                    case EVENT_3_END_WAVE:
                        SummonEndWave(2);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                        Talk(SAY_BROKEN_FREE_2);
                        events.ScheduleEvent(EVENT_3_END_WAVE_MOVE_3, 500);
                        break;
                    case EVENT_3_END_WAVE_MOVE_1:
                        for (uint8 i = 0; i < 3; ++i)
                        {
                            Creature* summon = ObjectAccessor::GetCreature(*me, summons[i]);
                            if (!summon)
                                continue;

                            summon->AttackStop();
                            summon->SetWalk(true);
                            summon->GetMotionMaster()->MovePoint(0, SummonWP[i]);
                        }

                        events.ScheduleEvent(EVENT_SECOND_END_WAVE, urand(5000, 9000));
                        break;
                    case EVENT_3_END_WAVE_MOVE_2:
                        for (uint8 i = 0; i < 3; ++i)
                        {
                            Creature* summon = ObjectAccessor::GetCreature(*me, summons[i + 3]);
                            if (!summon)
                                continue;

                            summon->AttackStop();
                            summon->SetWalk(true);
                            summon->GetMotionMaster()->MovePoint(0, SummonWP[i + 3]);
                        }

                        events.ScheduleEvent(EVENT_3_END_WAVE, urand(5000, 9000));
                        break;
                    case EVENT_3_END_WAVE_MOVE_3:
                        for (uint8 i = 0; i < 3; ++i)
                        {
                            Creature* summon = ObjectAccessor::GetCreature(*me, summons[i + 6]);
                            if (!summon)
                                continue;

                            summon->AttackStop();
                            summon->SetWalk(true);
                            summon->GetMotionMaster()->MovePoint(0, SummonWP[i + 6]);
                        }

                        events.ScheduleEvent(EVENT_END_EMOTE, 8000);
                        break;
                    case EVENT_END_EMOTE:
                        for (ObjectGuid summonGuid : summons)
                        {
                            Creature* summon = ObjectAccessor::GetCreature(*me, summonGuid);
                            if (!summon)
                                continue;

                            summon->SetStandState(UNIT_STAND_STATE_KNEEL);
                        }
                        me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        
        void SummonEndWave(uint8 num)
        {
            if (num > 2)
                return;

            uint32 summonEntries[3] = { NPC_ASHTONGUE_SORCERER, NPC_ASHTONGUE_DEFENDER, NPC_ASHTONGUE_ELEMENTALIST };
            if (num == 1)
            {
                summonEntries[0] = NPC_ASHTONGUE_ROGUE;
                summonEntries[1] = NPC_ASHTONGUE_SPIRITBINDER;
            }
            else if (num == 2)
            {
                summonEntries[0] = NPC_ASHTONGUE_BROKEN;
                summonEntries[1] = NPC_ASHTONGUE_SPIRITBINDER;
                summonEntries[2] = NPC_ASHTONGUE_DEFENDER;
            }

            for (uint8 i = 0; i < 3; ++i)
            {
                TempSummon* summ = me->SummonCreature(summonEntries[i], SummonPositions[i + num * 3], TEMPSUMMON_DEAD_DESPAWN);
                if (!summ)
                    continue;

                summons[i + num * 3] = summ->GetGUID();
                summ->setFaction(FACTION_FRIENDLY);
                summ->StopMoving();
                summ->GetMotionMaster()->Clear(true);
            }
        }

        void sGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            if (gossipListId == 0)
            {
                player->CLOSE_GOSSIP_MENU();
                StartChannel = true;
                EnterPhase(PHASE_CHANNEL);         
            }
        }

        private:
            ObjectGuid summons[9];
            InstanceScript* instance;
            EventMap events;
            PhaseNpcAkama Phase;
            bool StartChannel;            
            bool StartCombat;
            bool HasYelledOnce;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_akamaAI>(creature);
    }
};

// ########################################################
// Ashtongue Channeler
// ########################################################

class npc_ashtongue_channeler : public CreatureScript
{
public:
    npc_ashtongue_channeler() : CreatureScript("npc_ashtongue_channeler") { }

    struct npc_ashtongue_channelerAI : public ScriptedAI
    {
        npc_ashtongue_channelerAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        void Reset() override
        {
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);

            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            events.ScheduleEvent(EVENT_CHANNEL, 2000);
        }

        void JustDied(Unit* /*killer*/) override
        {
            if (Creature* Shade = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_SHADE_OF_AKAMA)))
                Shade->AI()->DoAction(ACTION_CHANNELER_DIED);
        }

        void EnterCombat(Unit* /*who*/) override { }
        void AttackStart(Unit* /*who*/) override { }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHANNEL:
                        if (Creature* Shade = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_SHADE_OF_AKAMA)))
                        {
                            if (Shade->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                                DoCast(me, SPELL_SHADE_SOUL_CHANNEL);
                            else
                            {
                                me->InterruptSpell(CURRENT_CHANNELED_SPELL);
                                Shade->AI()->DoAction(ACTION_CHANNELER_DIED);
                            }
                        }
                        events.ScheduleEvent(EVENT_CHANNEL, 2000);
                        break;
                    default:
                        break;
                }
            }
        }

        private:
            InstanceScript* instance;
            EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_ashtongue_channelerAI>(creature);
    }
};

// ########################################################
// Creature Generator Akama
// ########################################################

class npc_creature_generator_akama : public CreatureScript
{
public:
    npc_creature_generator_akama() : CreatureScript("npc_creature_generator_akama") { }

    struct npc_creature_generator_akamaAI : public ScriptedAI
    {
        npc_creature_generator_akamaAI(Creature* creature) : ScriptedAI(creature), Summons(me)
        {
            Initialize();
            instance = creature->GetInstanceScript();
        }

        void Initialize()
        {
            doSpawning = false;
            leftSide = false;
        }

        void Reset() override
        {
            Summons.DespawnAll();

            Initialize();

            if (me->GetPositionY() < 400.0f)
                leftSide   = true;
        }

        void JustSummoned(Creature* summon) override
        {
            Summons.Summon(summon);
        }

        void DoAction(int32 actionId) override
        {
            doSpawning = true;

            switch (actionId)
            {
                case ACTION_START_SPAWNING:
                    if (leftSide)
                    {
                        events.ScheduleEvent(EVENT_SPAWN_WAVE_B, 100);
                        events.ScheduleEvent(EVENT_SUMMON_ASHTONGUE_SORCERER, urand(2000, 5000));
                    }
                    else
                    {
                        events.ScheduleEvent(EVENT_SPAWN_WAVE_B, 10000);
                        events.ScheduleEvent(EVENT_SUMMON_ASHTONGUE_DEFENDER, urand(2000, 5000));
                    }
                    break;
                case ACTION_STOP_SPAWNING:
                    doSpawning = false;
                    break;
                case ACTION_DESPAWN_ALL_SPAWNS:
                    doSpawning = false;
                    Summons.DespawnAll();
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (doSpawning)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SPAWN_WAVE_B:
                            DoCast(me, SPELL_ASHTONGUE_WAVE_B);
                            events.ScheduleEvent(EVENT_SPAWN_WAVE_B, urand(45000, 50000));
                            break;
                        case EVENT_SUMMON_ASHTONGUE_SORCERER: // left
                            DoCast(me, SPELL_SUMMON_ASHTONGUE_SORCERER);
                            events.ScheduleEvent(EVENT_SUMMON_ASHTONGUE_SORCERER, urand(30000, 35000));
                            break;
                        case EVENT_SUMMON_ASHTONGUE_DEFENDER: // right
                            DoCast(me, SPELL_SUMMON_ASHTONGUE_DEFENDER);
                            events.ScheduleEvent(EVENT_SUMMON_ASHTONGUE_DEFENDER, urand(30000, 35000));
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        private:
            InstanceScript* instance;
            EventMap events;
            SummonList Summons;
            bool leftSide;
            bool doSpawning;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_creature_generator_akamaAI>(creature);
    }
};

// ########################################################
// Ashtongue Sorcerer
// ########################################################

class npc_ashtongue_sorcerer : public CreatureScript
{
public:
    npc_ashtongue_sorcerer() : CreatureScript("npc_ashtongue_sorcerer") { }

    struct npc_ashtongue_sorcererAI : public ScriptedAI
    {
        npc_ashtongue_sorcererAI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
            instance = creature->GetInstanceScript();
        }

        void Initialize()
        {
            startedBanishing = false;
            switchToCombat = false;
            resetevents = false;
        }

        void Reset() override
        {
            if (!startedBanishing)
            {
                if (Creature* Shade = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_SHADE_OF_AKAMA)))
                {
                    if (Shade->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                        me->GetMotionMaster()->MovePoint(0, Shade->GetPositionX(), Shade->GetPositionY(), Shade->GetPositionZ(), true);
                    else
                    {
                        if (Unit* target = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_AKAMA_SHADE)))
                            AttackStart(target);
                    }
                }
            }

            Initialize();
        }

        void JustDied(Unit* /*killer*/) override
        {
            if (Creature* Shade = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_SHADE_OF_AKAMA)))
                Shade->AI()->DoAction(ACTION_CHANNELER_DIED);
            me->DespawnOrUnsummon(5000);
        }

        void EnterCombat(Unit* /*who*/) override { }

        void AttackStart(Unit* who) override
        {
            if (!switchToCombat)
                return;
            ScriptedAI::AttackStart(who);
        }

        void UpdateAI(uint32 diff) override
        {
            if (me->getFaction() == FACTION_FRIENDLY && resetevents)
                return;
            else if (me->getFaction() == FACTION_FRIENDLY)
            {
                events.Reset();
                resetevents = true;
                return;
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SORCERER_CHANNEL:
                        if (Creature* Shade = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_SHADE_OF_AKAMA)))
                        {
                            if (Shade->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                            {
                                me->SetFacingToObject(Shade);
                                DoCast(me, SPELL_SHADE_SOUL_CHANNEL);
                                events.ScheduleEvent(EVENT_SORCERER_CHANNEL, 2000);
                            }
                            else
                            {
                                me->InterruptSpell(CURRENT_CHANNELED_SPELL);
                                Shade->AI()->DoAction(ACTION_CHANNELER_DIED);
                                switchToCombat = true;
                                if (Unit* target = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_AKAMA_SHADE)))
                                    AttackStart(target);
                            }
                        }
                        break;
                    default:
                        break;
                }
            }

            if (!startedBanishing)
            {
                Creature* Shade = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_SHADE_OF_AKAMA));
                if (me->IsWithinDist(Shade, 20.0f, false))
                {
                    me->StopMoving();
                    me->GetMotionMaster()->Clear(false);
                    me->GetMotionMaster()->MovePoint(1, me->GetPositionX() + frand (-8.0f, 8.0f), me->GetPositionY() + frand (-8.0f, 8.0f), me->GetPositionZ(), true);
                    events.ScheduleEvent(EVENT_SORCERER_CHANNEL, 1500);
                    startedBanishing = true;
                }
            }

            DoMeleeAttackIfReady();
        }

        private:
            InstanceScript* instance;
            EventMap events;
            bool startedBanishing;
            bool switchToCombat;
            bool resetevents;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_ashtongue_sorcererAI>(creature);
    }
};

// ########################################################
// Ashtongue Defender
// ########################################################

class npc_ashtongue_defender : public CreatureScript
{
public:
    npc_ashtongue_defender() : CreatureScript("npc_ashtongue_defender") { }

    struct npc_ashtongue_defenderAI : public ScriptedAI
    {
        npc_ashtongue_defenderAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            Initialize();
        }

        void Initialize()
        {
            resetevents = false;
        }

        void Reset() override
        {
            Initialize();
            if (Unit* target = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_AKAMA_SHADE)))
                AttackStart(target);
        }

        void JustDied(Unit* /*killer*/) override
        {
            me->DespawnOrUnsummon(5000);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_HEROIC_STRIKE, 5000);
            events.ScheduleEvent(EVENT_SHIELD_BASH, urand(10000, 16000));
            events.ScheduleEvent(EVENT_DEBILITATING_STRIKE, urand(10000, 16000));
            events.ScheduleEvent(EVENT_WINDFURY, urand(8000, 12000));
        }

        void UpdateAI(uint32 diff) override
        {
            if (me->getFaction() == FACTION_FRIENDLY && resetevents)
                return;
            else if (me->getFaction() == FACTION_FRIENDLY)
            {
                events.Reset();
                resetevents = true;
                return;
            }

            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DEBILITATING_STRIKE:
                        DoCastVictim(SPELL_DEBILITATING_STRIKE);
                        events.ScheduleEvent(EVENT_DEBILITATING_STRIKE, urand(8000, 16000));
                        break;
                    case EVENT_HEROIC_STRIKE:
                        DoCast(me, SPELL_HEROIC_STRIKE);
                        events.ScheduleEvent(EVENT_HEROIC_STRIKE, urand(50000, 60000));
                        break;
                    case EVENT_SHIELD_BASH:
                        DoCastVictim(SPELL_SHIELD_BASH);
                        events.ScheduleEvent(EVENT_SHIELD_BASH, urand(8000, 16000));
                        break;
                    case EVENT_WINDFURY:
                        DoCastVictim(SPELL_WINDFURY);
                        events.ScheduleEvent(EVENT_WINDFURY, urand(6000 , 8000));
                        break;
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        private:
            InstanceScript* instance;
            EventMap events;
            bool resetevents;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_ashtongue_defenderAI>(creature);
    }
};

// ########################################################
// Ashtongue Rogue
// ########################################################

class npc_ashtongue_rogue : public CreatureScript
{
public:
    npc_ashtongue_rogue() : CreatureScript("npc_ashtongue_rogue") { }

    struct npc_ashtongue_rogueAI : public ScriptedAI
    {
        npc_ashtongue_rogueAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        void Initialize()
        {
            resetevents = false;
        }

        void Reset() override
        {
            Initialize();
            if (Unit* target = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_AKAMA_SHADE)))
                AttackStart(target);
        }

        void JustDied(Unit* /*killer*/) override
        {
            me->DespawnOrUnsummon(5000);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_DEBILITATING_POISON, urand(500, 2000));
            events.ScheduleEvent(EVENT_EVISCERATE, urand(2000, 5000));
        }

        void UpdateAI(uint32 diff) override
        {
            if (me->getFaction() == FACTION_FRIENDLY && resetevents)
                return;
            else if (me->getFaction() == FACTION_FRIENDLY)
            {
                events.Reset();
                resetevents = true;
                return;
            }

            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DEBILITATING_POISON:
                        DoCastVictim(SPELL_DEBILITATING_POISON);
                        events.ScheduleEvent(EVENT_DEBILITATING_POISON, urand(14000, 18000));
                        break;
                    case EVENT_EVISCERATE:
                        DoCastVictim(SPELL_EVISCERATE);
                        events.ScheduleEvent(EVENT_EVISCERATE, urand(12000, 16000));
                        break;
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        private:
            InstanceScript* instance;
            EventMap events;
            bool resetevents;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_ashtongue_rogueAI>(creature);
    }
};

// ########################################################
// Ashtongue Elementalist
// ########################################################

class npc_ashtongue_elementalist : public CreatureScript
{
public:
    npc_ashtongue_elementalist() : CreatureScript("npc_ashtongue_elementalist") { }

    struct npc_ashtongue_elementalistAI : public ScriptedAI
    {
        npc_ashtongue_elementalistAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        void Initialize()
        {
            resetevents = false;
        }

        void Reset() override
        {
            Initialize();
            if (Unit* target = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_AKAMA_SHADE)))
                AttackStart(target);
        }

        void JustDied(Unit* /*killer*/) override
        {
            me->DespawnOrUnsummon(5000);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_RAIN_OF_FIRE, 18000);
            events.ScheduleEvent(EVENT_LIGHTNING_BOLT, 6000);
        }

        void UpdateAI(uint32 diff) override
        {
            if (me->getFaction() == FACTION_FRIENDLY && resetevents)
                return;
            else if (me->getFaction() == FACTION_FRIENDLY)
            {
                events.Reset();
                resetevents = true;
                return;
            }

            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RAIN_OF_FIRE:
                        DoCastVictim(SPELL_RAIN_OF_FIRE);
                        events.ScheduleEvent(EVENT_RAIN_OF_FIRE, 20000);
                        break;
                    case EVENT_LIGHTNING_BOLT:
                        DoCastVictim(SPELL_LIGHTNING_BOLT);
                        events.ScheduleEvent(EVENT_LIGHTNING_BOLT, 15000);
                        break;
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        private:
            InstanceScript* instance;
            EventMap events;
            bool resetevents;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_ashtongue_elementalistAI>(creature);
    }
};

// ########################################################
// Ashtongue Spiritbinder
// ########################################################

class npc_ashtongue_spiritbinder : public CreatureScript
{
public:
    npc_ashtongue_spiritbinder() : CreatureScript("npc_ashtongue_spiritbinder") { }

    struct npc_ashtongue_spiritbinderAI : public ScriptedAI
    {
        npc_ashtongue_spiritbinderAI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
            instance = creature->GetInstanceScript();
        }

        void Initialize()
        {
            spiritMend = false;
            chainHeal = false;
            resetevents = false;
        }

        void Reset() override
        {
            Initialize();

            if (Unit* target = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_AKAMA_SHADE)))
                AttackStart(target);
        }

        void JustDied(Unit* /*killer*/) override
        {
            me->DespawnOrUnsummon(5000);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            events.ScheduleEvent(EVENT_SPIRIT_HEAL, urand (5000, 6000));
        }

        void UpdateAI(uint32 diff) override
        {
            if (me->getFaction() == FACTION_FRIENDLY && resetevents)
                return;
            else if (me->getFaction() == FACTION_FRIENDLY)
            {
                events.Reset();
                resetevents = true;
                return;
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SPIRIT_HEAL:
                        DoCast(me, SPELL_SPIRITBINDER_SPIRIT_HEAL);
                        events.ScheduleEvent(EVENT_SPIRIT_HEAL, urand (13000, 16000));
                        break;
                    default:
                        break;
                }
            }

            if (!UpdateVictim())
                return;

            if (!spiritMend)
            {
                if (HealthBelowPct(25))
                {
                    DoCast(me, SPELL_SPIRIT_MEND);
                    spiritMend = true;
                }
            }

            if (!chainHeal)
            {
                if (HealthBelowPct(40))
                {
                    DoCast(me, SPELL_CHAIN_HEAL);
                    chainHeal = true;
                }
            }

            DoMeleeAttackIfReady();
        }

        private:
            InstanceScript* instance;
            EventMap events;
            bool spiritMend;
            bool chainHeal;
            bool resetevents;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_ashtongue_spiritbinderAI>(creature);
    }
};

void AddSC_boss_shade_of_akama()
{
    new boss_shade_of_akama();
    new npc_akama_shade();
    new npc_ashtongue_channeler();
    new npc_creature_generator_akama();
    new npc_ashtongue_sorcerer();
    new npc_ashtongue_defender();
    new npc_ashtongue_rogue();
    new npc_ashtongue_elementalist();
    new npc_ashtongue_spiritbinder();
}
