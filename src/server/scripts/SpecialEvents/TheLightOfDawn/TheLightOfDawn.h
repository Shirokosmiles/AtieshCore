/*
 * Copyright (C) 2019+ ATieshCore <https://at-wow.org/>
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

#ifndef _TLODEVENT_H
#define _TLODEVENT_H

#include "GameTime.h"
#include "ObjectGuid.h"
#include "SpecialEvent.h"
#include "Position.h"
#include "World.h"
#include "ZoneScript.h"

WorldLocation const DalaranCrater(0, 276.82178f, 368.0858f, 121.2f, 4.135169f);
WorldLocation const DalaranCraterPoint(0, 287.2068f, 381.9773f, -67.5977f, 4.135169f);

struct PlayersData
{
    ObjectGuid guid;
    bool isDoingQuest;
    bool isInArea;
};
typedef std::unordered_map<uint32, PlayersData> PlayersDataContainer;

enum TheLightOfDawnPhase
{
    PHASE_IDLE  = 1,
    PHASE_INTRO = 2,
    PHASE_FIGHT = 3,
    PHASE_OUTRO = 4,
};

enum TheLightOfDawnEncounters
{
    // Light
    ENCOUNTER_DEFENDER_NUMBER         = 30, // how many of defender
    // Scourge
    ENCOUNTER_ABOMINATION_NUMBER      = 10, // how many of abomination
    ENCOUNTER_BEHEMOTH_NUMBER         = 3,  // how many of behemoth
    ENCOUNTER_GHOUL_NUMBER            = 60, // how many of ghoul
    ENCOUNTER_WARRIOR_NUMBER          = 25, // how many of warrior
};

class TC_GAME_API TheLightOfDawnEvent : public SpecialEvent
{
public:
    TheLightOfDawnEvent();
    ~TheLightOfDawnEvent();

    // phase
    TheLightOfDawnPhase GetPhase() { return phaseStage; }
    void SetPhase(TheLightOfDawnPhase phase) { phaseStage = phase; }

    void UpdateWorldState(uint32 id, uint32 state);
    void UpdateAllWorldStates();
    void SetupInitialStates();

    void DoPlaySoundToAll(uint32 soundId);
    void BroadcastPacketToPlayersInArea(WorldPacket const* data) const;

    void StartTheLightOfDawnEvent();
    void StopTheLightOfDawnEvent();

    void SummonScorgeArmy();
    void SummonDefenseArmy();
    void ClearAllNPC();

    // Override Sector
    // SpecialEvent sector
    void Update(uint32 diff) override;
    void OnSpecialEventStart() override;
    void OnSpecialEventEnd(bool /*endByTimer*/) override;
    void AddPlayer(ObjectGuid playerGUID) override;
    void RemovePlayer(ObjectGuid playerGUID) override;
    bool IsMemberOfEvent(Player* player) override;
    uint32 GetCountPlayerInEvent() override { return m_playersDataStore.size(); }
    bool SetupSpecialEvent(bool enabled, bool active, bool repeatable, uint32 id, uint32 cooldownTimer, uint32 durationTimer, std::string comment) override;
    bool IsSpellAreaAllowed(uint32 /*spellId*/, Player const* /*player*/, uint32 /*newArea*/) const  override { return true; }
    void DoActionForMember(ObjectGuid playerGUID, uint32 param) override;
    // ZoneScript sector
    void HandlePlayerEnterZone(Player* player, uint32 zoneId) override;
    // Called when a player leaves the battlefield zone
    void HandlePlayerLeaveZone(Player* player, uint32 zoneId) override;

    void HandlePlayerEnterArea(Player* player, uint32 zoneId, uint32 areaId) override;
    void HandlePlayerLeaveArea(Player* player, uint32 zoneId, uint32 areaId) override;

    Creature* GetCreature(ObjectGuid guid);
    GameObject* GetGameObject(ObjectGuid guid);

    void OnCreatureCreate(Creature* creature) override;
    void OnUnitDeath(Unit* unit) override;

    void SummonAbomination();
    void SummonBehemoth();
    void SummonGhoul();
    void SummonWarriorOfFrozenWastes();

    void SummonDawnDefender();

private:
    TheLightOfDawnPhase phaseStage;
    PlayersDataContainer m_playersDataStore;

    Map* _map;
    uint32 _mapId;

    uint32 defendersRemaining;
    uint32 scourgeRemaining;
    uint32 countdownTimerRemaining;
    bool show_soldiers_count;
    bool show_timer;
    bool show_event_begin;
    EventMap events;

    // Dawn
    ObjectGuid TirionGUID;
    ObjectGuid AlexandrosGUID;
    ObjectGuid DarionGUID;
    ObjectGuid KorfaxGUID;
    ObjectGuid MaxwellGUID;
    ObjectGuid EligorGUID;
    ObjectGuid LeonidGUID;
    ObjectGuid RayneGUID;
    ObjectGuid ZverenhoffGUID;
    ObjectGuid RimblatGUID;
    GuidUnorderedSet DefenderGUID;    //ENCOUNTER_DEFENDER_NUMBER

    // Scourge
    ObjectGuid Darion_Mograine;
    ObjectGuid KoltiraGUID;
    ObjectGuid OrbazGUID;
    ObjectGuid ThassarianGUID;
    ObjectGuid LichKingGUID;

    GuidUnorderedSet AbominationGUID; //ENCOUNTER_ABOMINATION_NUMBER
    GuidUnorderedSet BehemothGUID;    //ENCOUNTER_BEHEMOTH_NUMBER
    GuidUnorderedSet GhoulGUID;       //ENCOUNTER_GHOUL_NUMBER
    GuidUnorderedSet WarriorGUID;     //ENCOUNTER_WARRIOR_NUMBER
};

#endif // _TLODEVENT_H
