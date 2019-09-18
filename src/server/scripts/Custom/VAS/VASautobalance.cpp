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
        if (!attacker->FindMap() || !attacker->FindMap()->IsDungeon())
            return damage;

        if (attacker->ToPlayer() && !victim->ToPlayer()) // decrease only unit damage (not player)
            return damage;

        if (attacker->GetCharmerOrOwner())
            if (attacker->ToPet() || attacker->ToTotem() || attacker->IsSummon())
                return damage;

        if (!attacker->ToPlayer() && attacker->IsControlledByPlayer())
            return damage;

        float damageMultiplier = sWorld->getRate(RATE_VAS_DAMAGE_PERCENT);
        float tmpnewdamage = CalculatePct(damage, damageMultiplier);
        uint32 newdamage = uint32(tmpnewdamage);
        return newdamage;
    }

    uint32 VAS_Modifer_DealHeal(Unit* healer, Unit* reciever, uint32 heal)
    {
        if (!healer->FindMap() || !healer->FindMap()->IsDungeon())
            return heal;

        if (reciever->ToPlayer()) // Heal casted on player should be 100%
            return heal;

        if (healer->ToPlayer()) // Heal casted by player should be 100%
            return heal;

        float healMultiplier = sWorld->getRate(RATE_VAS_HEAL_PERCENT);
        float tmpnewheal = CalculatePct(heal, healMultiplier);
        uint32 newheal = uint32(tmpnewheal);
        return newheal;
    }

    void InstanceCreatureAddToWorld(Unit* unit) override
    {
        if (!sWorld->getBoolConfig(CONFIG_VAS_AUTOBALANCE))
            return;

        if (!unit)
            return;

        if (unit->GetCharmerOrOwner())
            if (unit->ToPet() || unit->ToTotem() || unit->IsSummon())
                return;
                
        uint32 maxhealth = unit->GetMaxHealth();
        float healthMultiplier = sWorld->getRate(RATE_VAS_MAXHP_PERCENT);
        uint32 newmaxhealth = CalculatePct(maxhealth, healthMultiplier);

        float healthPct = unit->GetHealthPct();
        uint32 newhealth = CalculatePct(newmaxhealth, healthPct);

        unit->SetCreateHealth(newmaxhealth);
        unit->SetMaxHealth(newmaxhealth);
        unit->SetHealth(newhealth);

        if (unit->ToCreature())
            unit->ToCreature()->ResetPlayerDamageReq();

        // mana section
        uint32 maxmana = unit->GetCreateMana();
        float mpMultiplier = sWorld->getRate(RATE_VAS_MAXMP_PERCENT);
        uint32 newhmaxmana = CalculatePct(maxmana, mpMultiplier);

        unit->SetCreateMana(newhmaxmana);
        if (unit->GetClass() == UNIT_CLASS_MAGE || unit->GetClass() == UNIT_CLASS_PALADIN)
        {
            unit->SetMaxPower(POWER_MANA, newhmaxmana);
            unit->SetFullPower(POWER_MANA);
        }

        unit->SetStatFlatModifier(UNIT_MOD_HEALTH, BASE_VALUE, (float)newmaxhealth);
    }

    void ModifyPeriodicDamageAurasTick(Unit* victim, Unit* attacker, uint32& damage) override
    {
        if (!sWorld->getBoolConfig(CONFIG_VAS_AUTOBALANCE))
            return;

        damage = VAS_Modifer_DealDamage(attacker, victim, damage);
    }

    void ModifyPeriodicHealthLeechAuraTick(Unit* victim, Unit* attacker, uint32& damage) override
    {
        if (!sWorld->getBoolConfig(CONFIG_VAS_AUTOBALANCE))
            return;

        damage = VAS_Modifer_DealHeal(attacker, victim, damage);
    }

    void ModifyPeriodicHealAurasTick(Unit* victim, Unit* attacker, uint32& damage) override
    {
        if (!sWorld->getBoolConfig(CONFIG_VAS_AUTOBALANCE))
            return;

        damage = VAS_Modifer_DealHeal(attacker, victim, damage);
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
