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

#include "ScriptMgr.h"
#include "SpecialEventMgr.h"
#include "SpecialEvent.h"
#include "Log.h"
#include "Player.h"

SpecialEventMgr::SpecialEventMgr()
{
    _updateTimer = 0;
}

void SpecialEventMgr::Die()
{
    for (SpecialEventSet::iterator itr = m_SpecialEventSet.begin(); itr != m_SpecialEventSet.end(); ++itr)
        delete* itr;

    m_SpecialEventSet.clear();
    m_SpecialEventDatas.fill(0);
    m_SpecialEventMap.clear();
}

SpecialEventMgr* SpecialEventMgr::instance()
{
    static SpecialEventMgr instance;
    return &instance;
}

void SpecialEventMgr::InitSpecialEvents()
{
    uint32 oldMSTime = getMSTime();

    //                                                 0       1            2               3               4           5
    QueryResult result = WorldDatabase.Query("SELECT TypeId, ScriptName, cooldownTimer, durationTimer, activeStatus, comment FROM special_events");
    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 Special Events definitions. DB table `special_events` is empty.");
        return;
    }

    uint32 count = 0;
    uint32 typeId = 0;
    uint32 cooldownTimer = 0;
    uint32 durationTimer = 0;
    uint32 activeStatus = 0;
    std::string comment = "";
    bool enabledStatus = false;

    do
    {
        Field* fields = result->Fetch();

        typeId = fields[0].GetUInt8();        

        if (typeId >= SPECIALEVENT_EVENTID_MAX)
        {
            TC_LOG_ERROR("sql.sql", "Invalid Special Event TypeId value %u in special_events; skipped.", typeId);
            continue;
        }

        SpecialEventId realTypeId = SpecialEventId(typeId);
        m_SpecialEventDatas[realTypeId] = sObjectMgr->GetScriptId(fields[1].GetString());

        cooldownTimer = fields[2].GetUInt32();
        durationTimer = fields[3].GetUInt32();
        activeStatus = fields[4].GetUInt32();
        comment = fields[5].GetString();
        enabledStatus = activeStatus > 0;

        ++count;
    } while (result->NextRow());

    SpecialEvent* se;
    for (uint8 i = 1; i < SPECIALEVENT_EVENTID_MAX; ++i)
    {
        if (!m_SpecialEventDatas[i])
        {
            TC_LOG_ERROR("sql.sql", "Could not initialize Special Event for type ID %u; no entry in database.", uint32(i));
            continue;
        }

        se = sScriptMgr->CreateSpecialEvent(m_SpecialEventDatas[i]);
        if (!se)
        {
            TC_LOG_ERROR("specialevent", "Could not initialize Special Event for type ID %u; got NULL pointer from script.", uint32(i));
            continue;
        }

        if (!se->SetupSpecialEvent(false, enabledStatus, typeId, cooldownTimer, durationTimer))
        {
            TC_LOG_ERROR("specialevent", "Could not initialize Special Event for type ID %u; SetupSpecialEvent failed.", uint32(i));
            delete se;
            continue;

        }

        TC_LOG_INFO("server.loading", ">> Special Event (id: %u) - %s successfully initialized", uint32(i), comment.c_str());
        m_SpecialEventSet.push_back(se);
    }

    TC_LOG_INFO("server.loading", ">> Loaded %u Special Event definitions in %u ms", count, GetMSTimeDiffToNow(oldMSTime));    
}

SpecialEvent* SpecialEventMgr::GetEnabledSpecialEvent(uint32 eventId)
{
    SpecialEventMap::iterator itr = m_SpecialEventMap.find(eventId);
    if (itr == m_SpecialEventMap.end())
        return nullptr;

    if (!itr->second->IsEnabled())
        return nullptr;

    return itr->second;
}

SpecialEvent* SpecialEventMgr::GetSpecialEvent(SpecialEventId eventId)
{
    SpecialEventMap::iterator itr = m_SpecialEventMap.find(eventId);
    if (itr == m_SpecialEventMap.end())
        return nullptr;

    if (itr->second->GetEventId() == eventId)
        return itr->second;

    return nullptr;
}

void SpecialEventMgr::Update(uint32 diff)
{
    _updateTimer += diff;
    if (_updateTimer > SPECIALEVENT_OBJECTIVE_UPDATE_INTERVAL)
    {
        for (SpecialEventSet::iterator itr = m_SpecialEventSet.begin(); itr != m_SpecialEventSet.end(); ++itr)
            (*itr)->Update(_updateTimer);
        _updateTimer = 0;
    }
}

void SpecialEventMgr::AddEvent(uint32 eventId, SpecialEvent* handle)
{
    m_SpecialEventMap[eventId] = handle;
}
