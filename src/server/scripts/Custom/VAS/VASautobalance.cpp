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

class VAS_AutoBalance_UnitScript : UnitScript
{
public:
    VAS_AutoBalance_UnitScript()
        : UnitScript("VAS_AutoBalance_UnitScript")
    {
    }

    uint32 VAS_Modifer_DealDamage(Unit* attacker, Unit* victim, uint32 damage)
    {
        if (!attacker || !victim)
            return damage;

        if (!attacker->GetMap() || !attacker->GetMap()->IsDungeon())
            return;

        if (attacker->ToPlayer()) // decrease only unit damage (not player)
            return damage;

        if (attacker->GetCharmerOrOwner())
            if (attacker->ToPet() || attacker->ToTotem() || attacker->IsSummon())
                return damage;

        float damageMultiplier = sWorld->getRate(RATE_VAS_DAMAGE_PERCENT);
        float newdamage = CalculatePct(damage, damageMultiplier);
        return uint32(newdamage);
    }

    uint32 VAS_Modifer_DealHeal(Unit* healer, Unit* reciever, uint32 heal)
    {
        if (!reciever || !healer)
            return heal;

        if (!healer->GetMap() || !healer->GetMap()->IsDungeon())
            return;

        if (reciever->ToPlayer()) // Heal casted on player should be 100%
            return heal;

        if (healer->ToPlayer()) // Heal casted by player should be 100%
            return heal;

        float healMultiplier = sWorld->getRate(RATE_VAS_HEAL_PERCENT);
        float newheal = CalculatePct(heal, healMultiplier);
        return uint32(newheal);
    }

    void CreatureUpdateLevelDependantStatsWithMaxHealth(Unit* unit, uint32& maxhealth) override
    {
        if (!sWorld->getBoolConfig(CONFIG_VAS_AUTOBALANCE))
            return;

        if (!unit)
            return;

        if (!unit->GetMap() || !unit->GetMap()->IsDungeon())
            return;

        if (unit->GetCharmerOrOwner())
            if (unit->ToPet() || unit->ToTotem() || unit->IsSummon())
                return;

        float healthMultiplier = sWorld->getRate(RATE_VAS_MAXHP_PERCENT);
        float newhealth = CalculatePct(maxhealth, healthMultiplier);
        maxhealth = newhealth;
    }

    void CreatureUpdateLevelDependantStatsWithMaxMana(Unit* unit, uint32& maxmana) override
    {
        if (!sWorld->getBoolConfig(CONFIG_VAS_AUTOBALANCE))
            return;

        if (!unit)
            return;

        if (!unit->GetMap() || !unit->GetMap()->IsDungeon())
            return;

        if (unit->GetCharmerOrOwner())
            if (unit->ToPet() || unit->ToTotem() || unit->IsSummon())
                return;

        float manaMultiplier = sWorld->getRate(RATE_VAS_MAXMP_PERCENT);
        float newmana = CalculatePct(maxmana, manaMultiplier);
        maxmana = newmana;
    }

    void ModifyPeriodicDamageAurasTick(Unit* victim, Unit* attacker, uint32& damage) override
    {
        if (!sWorld->getBoolConfig(CONFIG_VAS_AUTOBALANCE))
            return;

        damage = VAS_Modifer_DealDamage(attacker, victim, damage);
    }

    void ModifyMeleeDamage(Unit* victim, Unit* attacker, uint32& damage) override
    {
        if (!sWorld->getBoolConfig(CONFIG_VAS_AUTOBALANCE))
            return;

        damage = VAS_Modifer_DealDamage(attacker, victim, damage);
    }

    void ModifySpellDamageTaken(Unit* victim, Unit* attacker, int32& damage) override
    {
        if (!sWorld->getBoolConfig(CONFIG_VAS_AUTOBALANCE))
            return;

        damage = VAS_Modifer_DealDamage(attacker, victim, damage);
    }

    void OnHeal(Unit* healer, Unit* reciever, uint32& gain) override
    {
        if (!sWorld->getBoolConfig(CONFIG_VAS_AUTOBALANCE))
            return;

        gain = VAS_Modifer_DealHeal(healer, reciever, gain);
    }
};

void AddSC_VAS_AutoBalance()
{
    new VAS_AutoBalance_UnitScript;
}
