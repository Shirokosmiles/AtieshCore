/*
 * Copyright (C) 2016-2019 AtieshCore <https://at-wow.org/>
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

#include "Util.h"
#include "Unit.h"
#include "MapManager.h"
#include "World.h"

class VAS_AutoBalance_UnitScript : public UnitScript
{
public:
    VAS_AutoBalance_UnitScript()
        : UnitScript("VAS_AutoBalance_UnitScript")
    {
    }

    uint32 VAS_Modifer_DealDamage(Unit* target, Unit* victim, uint32 damage)
    {
        if (!victim || !victim->IsInWorld())
            return damage;

        if (victim->ToPlayer() || victim->IsHunterPet() || victim->IsPet() || victim->IsSummon())
        {
            float damageMultiplier = sWorld->getRate(RATE_VAS_DAMAGE_PERCENT);
            float newdamage = CalculatePct(damage, damageMultiplier);
            damage = uint32(newdamage);
        }

        return damage;
    }

    void AddToWorldWithHealth(Unit* unit, uint32 maxhealth) override
    {
        if (!unit->ToPlayer() && !unit->IsPet() && !unit->IsTotem() && unit->GetMap()->IsDungeon())
        {
            float damageMultiplier = sWorld->getRate(RATE_VAS_DAMAGE_PERCENT);
            float newhealth = CalculatePct(maxhealth, damageMultiplier);
            unit->SetMaxHealth(uint32(newhealth));
        }
    }

    void ModifyPeriodicDamageAurasTick(Unit* target, Unit* attacker, uint32& damage) override
    {
        if (attacker->GetMap()->IsDungeon() && target->GetMap()->IsDungeon())
            damage = VAS_Modifer_DealDamage(attacker, target, damage);
    }

    void ModifyMeleeDamage(Unit* target, Unit* attacker, uint32& damage) override
    {
        if (attacker->GetMap()->IsDungeon() && target->GetMap()->IsDungeon())
            damage = VAS_Modifer_DealDamage(attacker, target, damage);
    }

    void ModifySpellDamageTaken(Unit* target, Unit* attacker, int32& damage) override
    {
        if (attacker->GetMap()->IsDungeon() && target->GetMap()->IsDungeon())
            damage = VAS_Modifer_DealDamage(attacker, target, damage);
    }
};

void AddSC_VAS_AutoBalance()
{
    new VAS_AutoBalance_UnitScript;
}
