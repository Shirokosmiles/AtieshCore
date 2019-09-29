/*
 * Copyright (C) 2018+ AtieshCore <https://at-wow.org/>
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

#include "SpecialEventMgr.h"
#include "SpecialEvent.h"
#include "Log.h"
#include "Player.h"

SpecialEventMgr::SpecialEventMgr()
{
    _updateTimer = 0;
}

SpecialEventMgr::~SpecialEventMgr()
{
    for (auto itr = _specialEventContainer.begin(); itr != _specialEventContainer.end(); ++itr)
        delete itr->second;

    _specialEventContainer.clear();
}

SpecialEventMgr* SpecialEventMgr::instance()
{
    static SpecialEventMgr instance;
    return &instance;
}

void SpecialEventMgr::InitSpecialEvents()
{
    uint32 oldMSTime = getMSTime();

    _specialEventContainer.clear();                                  // for reload case

    //                                                     0                1
    QueryResult result = WorldDatabase.Query("SELECT eventId, cooldownTimer, durationTimer, activeStatus FROM special_events");

    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 Special Events. DB table `special_events` is empty!");
        return;
    }

    uint32 count = 0;

    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        uint32 cooldownTimer = fields[1].GetUInt32();
        uint32 durationTimer = fields[2].GetUInt32();
        uint32 activeStatus = fields[3].GetUInt32();

        bool enabledStatus = activeStatus > 0;
        SpecialEvent* se = new SpecialEvent(false, enabledStatus, id, cooldownTimer, durationTimer);
        _specialEventContainer[id] = se;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u Special Events in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

SpecialEvent* SpecialEventMgr::GetEnabledSpecialEvent(uint32 eventId)
{
    auto itr = _specialEventContainer.find(eventId);
    if (itr == _specialEventContainer.end())
        return nullptr;

    if (!itr->second->IsEnabled())
        return nullptr;

    return itr->second;
}

SpecialEvent* SpecialEventMgr::GetSpecialEvent(SpecialEventId eventId)
{
    for (auto itr = _specialEventContainer.begin(); itr != _specialEventContainer.end(); ++itr)
    {
        if (itr->second->GetEventId() == eventId)
            return itr->second;
    }

    return nullptr;
}

void SpecialEventMgr::Update(uint32 diff)
{
    _updateTimer += diff;
    if (_updateTimer > SPECIALEVENT_OBJECTIVE_UPDATE_INTERVAL)
    {
        for (auto itr = _specialEventContainer.begin(); itr != _specialEventContainer.end(); ++itr)
        {
            if (itr->second->IsEnabled())
                itr->second->Update(_updateTimer);
        }

        _updateTimer = 0;
    }
}
