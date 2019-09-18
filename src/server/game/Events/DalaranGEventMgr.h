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

#ifndef _DALARANGEVENTMGR_H
#define _DALARANGEVENTMGR_H

#include "Common.h"
#include "GameTime.h"
#include "ObjectGuid.h"
#include "EventMap.h"
#include "World.h"

WorldLocation const DalaranCrater(0, 276.82178f, 368.0858f, 121.2f, 4.135169f);
WorldLocation const DalaranCraterPoint(0, 287.2068f, 381.9773f, -67.5977f, 4.135169f);

struct PlayersData
{
    ObjectGuid guid;
    uint32 mapid;
    float x;
    float y;
    float z;
};
typedef std::unordered_map<uint32, PlayersData> PlayersDataContainer;

class TC_GAME_API DalaranGEventMgr
{
private:
    DalaranGEventMgr()
    {
        _activeFight = false;
        _registration = true;
        _announce60 = false;
        _announce30 = false;
        m_UpdateTimer = 0;
        m_DurationTimer = 0;
        alivePlayerCount = 0;
        gameTimeNextEvent = uint32(GameTime::GetGameTime() + (sWorld->getIntConfig(CONFIG_DALARAN_GAME_EVENTS_TIMER) * MINUTE));
        _winnername = "";
        _events.Reset();
    };
    ~DalaranGEventMgr() { };
    
    bool _activeFight;
    bool _registration;
    bool _announce60;
    bool _announce30;

    // update interval
    uint32 m_UpdateTimer;
    uint32 m_DurationTimer;
    uint32 alivePlayerCount;
    time_t gameTimeNextEvent;

    std::string _winnername;
    EventMap _events;

    PlayersDataContainer _playersDataStore; 
public:
    static DalaranGEventMgr* instance();

    bool IsActiveEvent() const { return _activeFight; }
    bool IsPossibleToRegister() const { return _registration; }
    uint32 GetCountPlayerInEvent();
    time_t GetTimeOfNextEvent() { return gameTimeNextEvent; }

    void Update(uint32 diff);

    void StartEvent();
    void StopEvent();

    void SpawnGOLight();

    void TeleportAllPlayersInZone();
    void TeleportAllPlayersBack();

    void BroadcastToMemberAboutLeavePlayer(std::string const& Name);
    void BroadcastToMemberPrepare();

    bool IsMemberOfEvent(Player* player);
    // Fight stage    
    void RemovePlayerFromFight(Player* player, bool withteleport = false);
    void ReceiveWinnerName();
    void DecreaseAliveCounter() { --alivePlayerCount; }
    // Queue stage
    void InvitePlayerToQueue(Player* player);
    void RemovePlayerFromQueue(Player* player);
};

#define sDalaranGEventMgr DalaranGEventMgr::instance()

#endif // _DALARANGEVENTMGR_H
