/*
 * Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
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
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "npc_pet_dk_".
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "CombatAI.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "MoveSpline.h"
#include "MoveSplineInit.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"

enum DeathKnightSpells
{
    SPELL_DK_SUMMON_GARGOYLE_1      = 49206,
    SPELL_DK_SUMMON_GARGOYLE_2      = 50514,
    SPELL_DK_DISMISS_GARGOYLE       = 50515,
    SPELL_DK_SANCTUARY              = 54661,

    // Dancing Rune Weapon
    SPELL_DK_DANCING_RUNE_WEAPON    = 49028,
    SPELL_COPY_WEAPON               = 63416,
    SPELL_DK_RUNE_WEAPON_MARK       = 50474,
    SPELL_DK_DANCING_RUNE_WEAPON_VISUAL = 53160,
    SPELL_FAKE_AGGRO_RADIUS_8_YARD  = 49812,
    SPELL_DK_RUNE_WEAPON_SCALING_01 = 51905,
    SPELL_DK_RUNE_WEAPON_SCALING    = 51906,
    SPELL_PET_SCALING__MASTER_SPELL_06__SPELL_HIT_EXPERTISE_SPELL_PENETRATION = 67561,
    SPELL_DK_PET_SCALING_03         = 61697,
    SPELL_AGGRO_8_YD_PBAE           = 49813,
    // Main Spells
    SPELL_BLOOD_STRIKE              = 49926,
    SPELL_PLAGUE_STRIKE             = 49917,
    
    SPELL_DISMISS_RUNEBLADE         = 50707 // Right now despawn is done by its duration
};

enum GargoyleState
{    
    EVENT_MOVE_AT_TARGET    = 1,
    EVENT_START_COMBAT      = 2,
    EVENT_COMBAT_OUT        = 3
};

class npc_pet_dk_ebon_gargoyle : public CreatureScript
{
public:
    npc_pet_dk_ebon_gargoyle() : CreatureScript("npc_pet_dk_ebon_gargoyle") { }

    struct npc_pet_dk_ebon_gargoyleAI : CasterAI
    {
        npc_pet_dk_ebon_gargoyleAI(Creature* creature) : CasterAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            ownerGuid = me->GetOwnerGUID();
            if (!ownerGuid)
                return;

            me->SetReactState(REACT_PASSIVE);
            me->CombatStop(true);
            me->StopMoving();
            me->GetMotionMaster()->Clear(false);
            me->SetCanFly(true);

            me->ApplyModFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE, true);

            _events.Reset();
        }

        void IsSummonedBy(Unit* summoner) override
        {
            _events.ScheduleEvent(EVENT_MOVE_AT_TARGET, 100);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!me || !me->IsAlive())
                return;
            
            _events.Update(diff);

            while (uint32 _eventId = _events.ExecuteEvent())
            {
                switch (_eventId)
                {
                    case EVENT_MOVE_AT_TARGET:
                    {
                        // Find victim of Summon Gargoyle spell
                        std::list<Unit*> targets;
                        Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(me, me, 30.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(me, targets, u_check);
						Cell::VisitAllObjects(me, searcher, 30.0f);
                        if (!targets.empty())
                        {
                            for (std::list<Unit*>::const_iterator iter = targets.begin(); iter != targets.end(); ++iter)
                                if ((*iter)->HasAura(SPELL_DK_SUMMON_GARGOYLE_1, ownerGuid))
                                {
                                    victim = (*iter)->GetGUID();
                                    break;
                                }
                        }
                        else
                        {
                            _events.ScheduleEvent(EVENT_MOVE_AT_TARGET, 100);
                            break;
                        }

                        Unit* target = ObjectAccessor::GetUnit(*me, victim);

                        if (!target)
                        {
                            _events.ScheduleEvent(EVENT_MOVE_AT_TARGET, 400);
                            break;
                        }

                        float o = target->GetOrientation();
                        float x = target->GetPositionX() + (7 * cos(o)) + target->GetCombatReach();
                        float y = target->GetPositionY() + (7 * sin(o)) + target->GetCombatReach();
                        float z = target->GetPositionZ() + 4.5f;

                        me->ApplyModFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE, false);

                        me->SetSpeedRate(MOVE_FLIGHT, 1.0f);
                        me->SetSpeedRate(MOVE_RUN, 1.0f);

                        // Fly at target
                        Movement::MoveSplineInit init(me);
                        init.MoveTo(x, y, z);
                        init.SetFly();
                        int32 traveltime = init.Launch();
                        _events.ScheduleEvent(EVENT_START_COMBAT, traveltime);
                        break;
                    }
                    case EVENT_START_COMBAT:
                    {
                        me->SetReactState(REACT_AGGRESSIVE);
                        // Start combat
                        if (Unit* target = ObjectAccessor::GetUnit(*me, victim))
                        {
                            me->Attack(target, false);
                            me->GetMotionMaster()->MoveChase(target);
                        }
                        me->SetCanFly(false);
                        break;
                    }
                    case EVENT_COMBAT_OUT:
                    {
                        me->CombatStop(true);
                        // Stop Fighting
                        me->ApplyModFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE, true);

                        // Sanctuary
                        me->CastSpell(me, SPELL_DK_SANCTUARY, true);
                        me->SetReactState(REACT_PASSIVE);

                        //! HACK: Creature's can't have MOVEMENTFLAG_FLYING
                        // Fly Away
                        me->SetCanFly(true);
                        me->SetSpeedRate(MOVE_FLIGHT, 0.75f);
                        me->SetSpeedRate(MOVE_RUN, 0.75f);
                        float newx = me->GetPositionX() + 20 * std::cos(me->GetOrientation());
                        float newy = me->GetPositionY() + 20 * std::sin(me->GetOrientation());
                        float newz = me->GetPositionZ() + 40.0f;
                        me->GetMotionMaster()->Clear(false);
                        me->GetMotionMaster()->MovePoint(0, newx, newy, newz);

                        // Despawn as soon as possible
                        me->DespawnOrUnsummon(Seconds(4));
                        _events.Reset();
                        break;
                    }
                    default:
                        break;
                }
            }

            CasterAI::UpdateAI(diff);
        }

        void JustDied(Unit* /*killer*/) override
        {
            _events.Reset();
            // Stop Feeding Gargoyle when it dies
            if (Unit* owner = me->GetOwner())
                owner->RemoveAurasDueToSpell(SPELL_DK_SUMMON_GARGOYLE_2);
        }

        // Fly away when dismissed
        void SpellHit(Unit* source, SpellInfo const* spell) override
        {
            if (spell->Id != SPELL_DK_DISMISS_GARGOYLE || !me->IsAlive())
                return;

            Unit* owner = me->GetOwner();
            if (!owner || owner != source)
                return;
            _events.ScheduleEvent(EVENT_COMBAT_OUT, 0);
        }

    private:
        ObjectGuid victim;
        ObjectGuid ownerGuid;
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_pet_dk_ebon_gargoyleAI(creature);
    }
};

class npc_pet_dk_guardian : public CreatureScript
{
    public:
        npc_pet_dk_guardian() : CreatureScript("npc_pet_dk_guardian") { }

        struct npc_pet_dk_guardianAI : public AggressorAI
        {
            npc_pet_dk_guardianAI(Creature* creature) : AggressorAI(creature) { }

            bool CanAIAttack(Unit const* target) const override
            {
                if (!target)
                    return false;
                Unit* owner = me->GetOwner();
                if (owner && !target->IsInCombatWith(owner))
                    return false;
                return AggressorAI::CanAIAttack(target);
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_pet_dk_guardianAI(creature);
        }
};

enum DancingRuneWeapon
{
    DATA_INITIAL_TARGET_GUID = 1,
        
    EVENT_SPELL_CAST_1 = 1,
    EVENT_SPELL_CAST_2 = 2
};

class npc_dancing_rune_weapon : public CreatureScript
{
    public:
        npc_dancing_rune_weapon() : CreatureScript("npc_pet_dk_rune_weapon") { }

        struct npc_dancing_rune_weaponAI : CasterAI
        {
            npc_dancing_rune_weaponAI(Creature* creature) : CasterAI(creature)
            {
                Initialize();
            }

            void Initialize()
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->AddAura(81256, me->GetOwner());

                if (Unit* owner = me->GetOwner())
                {
                    float minDamage = CalculatePct(owner->GetFloatValue(UNIT_FIELD_MINDAMAGE), 50);
                    float maxDamage = CalculatePct(owner->GetFloatValue(UNIT_FIELD_MAXDAMAGE), 50);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                }

                _events.Reset();
            }

            void IsSummonedBy(Unit* summoner) override
            {
                /*DoCast(summoner, SPELL_COPY_WEAPON, true);
                DoCast(summoner, SPELL_DK_RUNE_WEAPON_MARK, true);
                DoCast(me, SPELL_DK_DANCING_RUNE_WEAPON_VISUAL, true);
                DoCast(me, SPELL_FAKE_AGGRO_RADIUS_8_YARD, true);
                DoCast(me, SPELL_DK_RUNE_WEAPON_SCALING_01, true);
                DoCast(me, SPELL_DK_RUNE_WEAPON_SCALING, true);
                DoCast(me, SPELL_PET_SCALING__MASTER_SPELL_06__SPELL_HIT_EXPERTISE_SPELL_PENETRATION, true);
                DoCast(me, SPELL_DK_PET_SCALING_03, true);*/
                
                _events.ScheduleEvent(EVENT_SPELL_CAST_2, 6 * IN_MILLISECONDS);
                
                me->SetRedirectThreat(summoner->GetGUID(), 100);
            }

            void SetGUID(ObjectGuid const& guid, int32 type) override
            {
                switch (type)
                {
                    case DATA_INITIAL_TARGET_GUID:
                        _targetGUID = guid;
                        if (Unit* target = ObjectAccessor::GetUnit(*me, _targetGUID))
                        {
                            if (me->Attack(target, true))
                                me->GetMotionMaster()->MoveChase(target);
                            DoCast(target, SPELL_AGGRO_8_YD_PBAE, true);
                            _events.ScheduleEvent(EVENT_SPELL_CAST_1, 1 * IN_MILLISECONDS);
                        }
                        break;
                    default:
                        break;
                }
            }

            void OwnerMeleeDamageDealt(Unit* /*owner*/, CalcDamageInfo* damageInfo) override
            {
                if (Unit* target = ObjectAccessor::GetUnit(*me, _targetGUID))
                {
                    damageInfo->attacker = me;
                    damageInfo->damage /= 2;
                    me->DealDamage(target, damageInfo->damage, nullptr, DIRECT_DAMAGE, SpellSchoolMask(damageInfo->damageSchoolMask));
                    me->SendAttackStateUpdate(damageInfo);
                    //me->ProcDamageAndSpell(damageInfo->target, damageInfo->procAttacker, damageInfo->procVictim, damageInfo->procEx, damageInfo->damage, damageInfo->attackType);
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (!me || !me->IsAlive())
                    return;

                _events.Update(diff);
                
                while (uint32 _eventId = _events.ExecuteEvent())
                {
                    switch (_eventId)
                    {
                        case EVENT_SPELL_CAST_1:
                            // Cast every second
                            if (Unit* victim = ObjectAccessor::GetUnit(*me, _targetGUID))
                                DoCast(victim, SPELL_AGGRO_8_YD_PBAE, true);
                            _events.ScheduleEvent(EVENT_SPELL_CAST_1, 1 * IN_MILLISECONDS);
                            break;
                        case EVENT_SPELL_CAST_2:
                            // Cast every 6 seconds
                            DoCast(me, SPELL_DK_DANCING_RUNE_WEAPON_VISUAL, true);
                            _events.ScheduleEvent(EVENT_SPELL_CAST_2, 6 * IN_MILLISECONDS);
                            break;
                        default:
                    break;
                    }
                }

                CasterAI::UpdateAI(diff);
                DoMeleeAttackIfReady();
            }

        private:
            ObjectGuid _targetGUID;
            EventMap _events;
         };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_dancing_rune_weaponAI(creature);
    }
};

void AddSC_deathknight_pet_scripts()
{
    new npc_pet_dk_ebon_gargoyle();
    new npc_dancing_rune_weapon();
    new npc_pet_dk_guardian();
}
