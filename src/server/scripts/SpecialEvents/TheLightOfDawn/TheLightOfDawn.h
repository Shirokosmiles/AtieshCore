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
};
typedef std::unordered_map<uint32, PlayersData> PlayersDataContainer;

enum TheLightOfDawnPhase
{
    PHASE_IDLE  = 1,
    PHASE_START = 2
};

class TC_GAME_API TheLightOfDawnEvent : public SpecialEvent
{
public:
    TheLightOfDawnEvent();
    ~TheLightOfDawnEvent();

    bool IsActiveTheLightOfDawnEvent() const { return activeFight; }

    // phase
    TheLightOfDawnPhase GetPhase() { return phaseStage; }
    void SetPhase(TheLightOfDawnPhase phase) { phaseStage = phase; }

    void UpdateWorldState(uint32 id, uint32 state);

    void Update(uint32 diff) override;
    void OnSpecialEventStart() override;
    void OnSpecialEventEnd(bool /*endByTimer*/) override;
    void AddPlayer(ObjectGuid playerGUID) override;
    void RemovePlayer(ObjectGuid playerGUID) override;
    bool IsMemberOfEvent(Player* player) override;
    uint32 GetCountPlayerInEvent() override { return m_playersDataStore.size(); }
    bool SetupSpecialEvent(bool enabled, bool active, bool repeatable, uint32 id, uint32 cooldownTimer, uint32 durationTimer) override;    

    void StartTheLightOfDawnEvent();
    void StopTheLightOfDawnEvent();    

    void HandlePlayerEnterZone(Player* player) override;
    // Called when a player leaves the battlefield zone
    void HandlePlayerLeaveZone(Player* player) override;

private:   
    bool activeFight;
    TheLightOfDawnPhase phaseStage;
    PlayersDataContainer m_playersDataStore;
};

#endif // _TLODEVENT_H
