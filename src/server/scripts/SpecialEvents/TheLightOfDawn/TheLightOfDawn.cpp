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

#include "Chat.h"
#include "TheLightOfDawn.h"
#include "Group.h"
#include "Guild.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "RBAC.h"
#include "Language.h"
#include "Log.h"
#include "WorldSession.h"
#include "World.h"

enum DataEnum
{
    ZONEID_THE_SCARLET_ENCLAVE = 4298, // Zone: Plaguelands: The Scarlet Enclave

    WORLD_STATE_REMAINS        = 3592,
    WORLD_STATE_COUNTDOWN      = 3603,
    WORLD_STATE_EVENT_BEGIN    = 3605
};

TheLightOfDawnEvent::TheLightOfDawnEvent()
{
    _eventId = SPECIALEVENT_EVENTID_THELIGHTOFDAWN;
    activeFight = false;

    SetPhase(PHASE_IDLE);

    //prepareTimer.Reset(IN_MILLISECONDS);
}

bool TheLightOfDawnEvent::SetupSpecialEvent(bool enabled, bool active, bool repeatable, uint32 id, uint32 cooldownTimer, uint32 durationTimer)
{
    // override Setup for Set time of first run in cooldownTimer
    if (SpecialEvent::SetupSpecialEvent(enabled, active, repeatable, id, cooldownTimer, durationTimer))
    {
        RegisterZoneIdForEvent(ZONEID_THE_SCARLET_ENCLAVE);
        return true;
    }

    return false;
}

TheLightOfDawnEvent::~TheLightOfDawnEvent()
{
    m_playersDataStore.clear();
}

void TheLightOfDawnEvent::UpdateWorldState(uint32 id, uint32 state)
{
    for (PlayersDataContainer::const_iterator itr = m_playersDataStore.begin(); itr != m_playersDataStore.end(); ++itr)
    {
        if (Player* player = ObjectAccessor::FindPlayer(itr->second.guid))
            player->SendUpdateWorldState(id, state);
    }
}

void TheLightOfDawnEvent::Update(uint32 diff)
{
    SpecialEvent::Update(diff);

    if (IsActiveTheLightOfDawnEvent())
    {

    }
    else
    {

    }
}

void TheLightOfDawnEvent::OnSpecialEventStart()
{
    StartTheLightOfDawnEvent();
}

void TheLightOfDawnEvent::OnSpecialEventEnd(bool /*endByTimer*/)
{
    StopTheLightOfDawnEvent();
}

void TheLightOfDawnEvent::AddPlayer(ObjectGuid playerGUID)
{
    PlayersData pd;
    pd.guid = playerGUID;

    // find max id
    uint32 new_id = 0;
    for (PlayersDataContainer::const_iterator itr = m_playersDataStore.begin(); itr != m_playersDataStore.end(); ++itr)
        if (itr->first > new_id)
            new_id = itr->first;

    // use next
    ++new_id;
    // add in active player list of event
    m_playersDataStore[new_id] = pd;
}

void TheLightOfDawnEvent::RemovePlayer(ObjectGuid playerGUID)
{
    uint32 id = 0;
    for (PlayersDataContainer::const_iterator itr = m_playersDataStore.begin(); itr != m_playersDataStore.end(); ++itr)
    {
        if (itr->second.guid == playerGUID)
            id = itr->first;
    }

    if (id)
        m_playersDataStore.erase(id);
}

bool TheLightOfDawnEvent::IsMemberOfEvent(Player* player)
{
    for (PlayersDataContainer::const_iterator itr = m_playersDataStore.begin(); itr != m_playersDataStore.end(); ++itr)
    {
        if (itr->second.guid == player->GetGUID())
            return true;
    }

    return false;
}

void TheLightOfDawnEvent::StartTheLightOfDawnEvent()
{
    // Update timers
    SetPhase(PHASE_START);
    activeFight = true;
}

void TheLightOfDawnEvent::StopTheLightOfDawnEvent()
{
    SetPhase(PHASE_IDLE);
    activeFight = false;
}

void TheLightOfDawnEvent::HandlePlayerEnterZone(Player* player)
{
    if (!IsMemberOfEvent(player))
        AddPlayer(player->GetGUID());
}

void TheLightOfDawnEvent::HandlePlayerLeaveZone(Player* player)
{
    if (IsMemberOfEvent(player))
        RemovePlayer(player->GetGUID());
}

class SpecialEvent_TheLightOfDawn : public SpecialEventScript
{
public:
    SpecialEvent_TheLightOfDawn() : SpecialEventScript("the_light_of_dawn") { }

    SpecialEvent* GetSpecialEvent() const override
    {
        return new TheLightOfDawnEvent();
    }
};

void AddSC_TheLightOfDawnScripts()
{
    new SpecialEvent_TheLightOfDawn();
}
