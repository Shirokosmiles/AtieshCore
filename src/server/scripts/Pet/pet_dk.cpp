/*
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

/*
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "npc_pet_dk_".
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "CombatAI.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "MoveSpline.h"
#include "MoveSplineInit.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "ItemTemplate.h"

enum DeathKnightSpells
{
    // Ebon Gargoyle
    SPELL_DK_SUMMON_GARGOYLE_1      = 49206,
    SPELL_DK_SUMMON_GARGOYLE_2      = 50514,
    SPELL_DK_DISMISS_GARGOYLE       = 50515,
    SPELL_DK_SANCTUARY              = 54661,
 
    // Dancing Rune Weapon
    SPELL_DK_DANCING_RUNE_WEAPON        = 49028,
    SPELL_COPY_WEAPON                   = 63416,
    SPELL_DK_RUNE_WEAPON_MARK           = 50474, // doesn't exist in dbc
    SPELL_DK_DANCING_RUNE_WEAPON_VISUAL = 53160, // doesn't exist in dbc
    SPELL_FAKE_AGGRO_RADIUS_8_YARD      = 49812, // doesn't exist in dbc
    SPELL_DK_RUNE_WEAPON_SCALING_01     = 51905, // doesn't exist in dbc
    SPELL_DK_RUNE_WEAPON_SCALING_02     = 51906, // Death Knight Rune Weapon Scaling 02
    SPELL_PET_SCALING__MASTER_SPELL_06__SPELL_HIT_EXPERTISE_SPELL_PENETRATION = 67561, // doesn't exist in dbc
    SPELL_DK_PET_SCALING_03             = 61697, // Death Knight Pet Scaling 03
    SPELL_AGGRO_8_YD_PBAE               = 49813, // doesn't exist in dbc
    // Main Spells
    SPELL_BLOOD_STRIKE                  = 49926,
    SPELL_PLAGUE_STRIKE                 = 49917,
     
    SPELL_DISMISS_RUNEBLADE             = 50707 // Right now despawn is done by its duration
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
            me->GetMotionMaster()->Clear();
            me->SetCanFly(true);

            me->ApplyModFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE, true);

            _events.Reset();
        }

        void IsSummonedBy(WorldObject* summoner) override
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
                                    continue;
                                }
                        }
                        else
                        {
                            _events.ScheduleEvent(EVENT_MOVE_AT_TARGET, 100);
                            break;
                        }

                        Unit* target = nullptr;
                        if (victim)
                            target = ObjectAccessor::GetUnit(*me, victim);

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
                        me->GetMotionMaster()->Clear();
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

class npc_pet_dk_rune_weapon : public CreatureScript
{
    public:
        npc_pet_dk_rune_weapon() : CreatureScript("npc_pet_dk_rune_weapon") { }

        struct npc_pet_dk_rune_weaponAI : ScriptedAI
        {
            npc_pet_dk_rune_weaponAI(Creature* creature) : ScriptedAI(creature)
            {
                // Prevent early victim engage
                creature->SetReactState(REACT_PASSIVE);
                _engageTimer = 0;
            }

            void IsSummonedBy(WorldObject* summoner) override
            {
                if (Unit * ownercaster = summoner->ToUnit())
                {
                    DoCast(ownercaster, SPELL_COPY_WEAPON, true);
                    DoCast(ownercaster, SPELL_DK_RUNE_WEAPON_MARK, true);
                }
                //DoCast(me, SPELL_DK_DANCING_RUNE_WEAPON_VISUAL, true);
                DoCast(me, SPELL_FAKE_AGGRO_RADIUS_8_YARD, true);
                //DoCast(me, SPELL_DK_RUNE_WEAPON_SCALING_01, true);
                DoCast(me, SPELL_DK_RUNE_WEAPON_SCALING_02, true);
                DoCast(me, SPELL_PET_SCALING__MASTER_SPELL_06__SPELL_HIT_EXPERTISE_SPELL_PENETRATION, true);
                DoCast(me, SPELL_DK_PET_SCALING_03, true);

                _events.ScheduleEvent(EVENT_SPELL_CAST_2, 6 * IN_MILLISECONDS);
                _engageTimer = 1 * IN_MILLISECONDS;

                me->GetThreatManager().RegisterRedirectThreat(SPELL_FAKE_AGGRO_RADIUS_8_YARD, summoner->GetGUID(), 100);
            }

            void SetGUID(ObjectGuid const& guid, int32 type) override
            {
                switch (type)
                {
                    case DATA_INITIAL_TARGET_GUID:
                        _targetGUID = guid;
                        me->SetReactState(REACT_AGGRESSIVE);
                        if (Unit* target = ObjectAccessor::GetUnit(*me, _targetGUID))
                            DoWeaponAttack(target);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (!me || !me->IsAlive())
                    return;

                if (me->HasReactState(REACT_PASSIVE))
                {
                    if (_engageTimer <= diff)
                        me->SetReactState(REACT_AGGRESSIVE);
                    else
                    {
                        _engageTimer -= diff;
                        return;
                    }
                }

                if (me->IsInCombat() && (!me->GetVictim() || !me->IsValidAttackTarget(me->GetVictim())))
                    EnterEvadeMode(EVADE_REASON_NO_HOSTILES);

                if (!me->IsInCombat())
                {
                    Unit* ownerTarget = nullptr;
                    if (Player* owner = me->GetCharmerOrOwner()->ToPlayer())
                        ownerTarget = owner->GetSelectedUnit();

                    // recognize which victim will be choosen
                    if (ownerTarget && ownerTarget->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (!ownerTarget->HasBreakableByDamageCrowdControlAura(ownerTarget))
                            DoWeaponAttack(ownerTarget);
                    }
                    else if (ownerTarget && (ownerTarget->GetTypeId() != TYPEID_PLAYER) && IsInThreatList(ownerTarget))
                    {
                        if (!ownerTarget->HasBreakableByDamageCrowdControlAura(ownerTarget))
                            DoWeaponAttack(ownerTarget);
                    }
                    else
                        Init();
                }

                /*
                    Investigate further if these casts are done by
                    any owned aura, eitherway SMSG_SPELL_GO
                    is sent every X seconds.
                */
                _events.Update(diff);

                while (uint32 _eventId = _events.ExecuteEvent())
                {
                    switch (_eventId)
                    {
                        case EVENT_SPELL_CAST_1:
                            // Cast every second
                            if (Unit* victim = me->GetVictim())
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

                if (me->IsInCombat() && me->GetVictim() && me->IsValidAttackTarget(me->GetVictim()))
                    DoMeleeAttackIfReady();
            }

            void DoWeaponAttack(Unit* who)
            {
                if (me->Attack(who, true))
                {
                    me->GetMotionMaster()->MoveChase(who);
                    DoCast(who, SPELL_AGGRO_8_YD_PBAE, true);
                    _events.RescheduleEvent(EVENT_SPELL_CAST_1, 1 * IN_MILLISECONDS);
                }
            }

            void EnterEvadeMode(EvadeReason /*why*/) override
            {
                if (!me->IsAlive())
                    return;

                Unit* owner = me->GetCharmerOrOwner();

                _events.CancelEvent(EVENT_SPELL_CAST_1);
                me->CombatStop(true);
                if (owner && !me->HasUnitState(UNIT_STATE_FOLLOW))
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle(), MOTION_SLOT_ACTIVE);
                }
                Init();
            }

            void Init()
            {
                Unit* owner = me->GetCharmerOrOwner();

                std::list<Unit*> targets;
                Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(me, me, 30.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                Cell::VisitAllObjects(me, searcher, 30.0f);

                Unit* highestThreatUnit = nullptr;
                float highestThreat = 0.0f;
                Unit* nearestPlayer = nullptr;

                if (!targets.empty())
                {
                    for (std::list<Unit*>::const_iterator iter = targets.begin(); iter != targets.end(); ++iter)
                    {
                        // Consider only units without CC
                        if (!(*iter)->HasBreakableByDamageCrowdControlAura((*iter)))
                        {
                            // Take first found unit
                            if (!highestThreatUnit && (*iter)->GetTypeId() != TYPEID_PLAYER)
                            {
                                highestThreatUnit = (*iter);
                                continue;
                            }
                            if (!nearestPlayer && ((*iter)->GetTypeId() == TYPEID_PLAYER))
                            {
                                nearestPlayer = (*iter);
                                continue;
                            }
                            // else compare best fit unit with current unit
                            float threat = (*iter)->GetThreatManager().GetThreat(owner);
                            // Check if best fit hostile unit hs lower threat than this current unit
                            if (highestThreat < threat)
                            {
                                // If so, update best fit unit
                                highestThreat = threat;
                                highestThreatUnit = (*iter);
                            }
                            // In case no unit with threat was found so far, always check for nearest unit (only for players)
                            if ((*iter)->GetTypeId() == TYPEID_PLAYER)
                            {
                                // If this player is closer than the previous one, update it
                                if (me->GetDistance((*iter)->GetPosition()) < me->GetDistance(nearestPlayer->GetPosition()))
                                    nearestPlayer = (*iter);
                            }
                        }
                    }
                }
                // Prioritize units with threat referenced to owner
                if (highestThreat > 0.0f && highestThreatUnit)
                    DoWeaponAttack(highestThreatUnit);
                // If there is no such target, try to attack nearest hostile unit if such exists
                else if (nearestPlayer)
                    DoWeaponAttack(nearestPlayer);
            }

            bool IsInThreatList(Unit* target)
            {
                Unit* owner = me->GetCharmerOrOwner();
                return owner && target->IsThreatenedBy(owner);
            }

        private:
            ObjectGuid _targetGUID;
            EventMap _events;
            uint32 _engageTimer;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_pet_dk_rune_weaponAI(creature);
        }
};

class spell_pet_dk_gargoyle_strike : public SpellScript
{
    PrepareSpellScript(spell_pet_dk_gargoyle_strike);

    void HandleDamageCalc(SpellEffIndex /*effIndex*/)
    {
        int32 damage = 60;
        if (Unit* caster = GetCaster())
        {
            if (caster->getLevel() >= 60)
                damage += (caster->getLevel() - 60) * 4;
        }

        SetEffectValue(damage);
    }

    void Register() override
    {
        OnEffectLaunchTarget += SpellEffectFn(spell_pet_dk_gargoyle_strike::HandleDamageCalc, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

void AddSC_deathknight_pet_scripts()
{
    new npc_pet_dk_ebon_gargoyle();
    new npc_pet_dk_rune_weapon();
    new npc_pet_dk_guardian();
    RegisterSpellScript(spell_pet_dk_gargoyle_strike);
}
