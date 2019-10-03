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

#ifndef SPECIALEVENT_MGR_H_
#define SPECIALEVENT_MGR_H_

#include "SpecialEvent.h"
#include <unordered_map>

class Player;
class SpecialEvent;
class ZoneScript;
enum SpecialEventId : uint32;
enum LocaleConstant : uint8;

class TC_GAME_API SpecialEventMgr
{
    private:
        SpecialEventMgr();
        ~SpecialEventMgr() { };

    public:
        static SpecialEventMgr* instance();

        // cleanup
        void Die();

        // create SpecialEvents
        void InitSpecialEvents();

        void Update(uint32 diff);

        // event sector
        void AddEvent(SpecialEventId eventId, SpecialEvent* handle);
        
        SpecialEvent* GetSpecialEventByEventId(SpecialEventId eventId) const;
        SpecialEvent* GetSpecialEventByZoneId(uint32 zoneId) const;

        SpecialEvent* GetEnabledSpecialEventByEventId(SpecialEventId eventId) const;
        SpecialEvent* GetEnabledSpecialEventByZoneId(uint32 zoneId) const;

        // ZoneScript
        void AddZone(uint32 zoneId, SpecialEvent* handle);
        ZoneScript* GetZoneScriptbyZoneId(uint32 zoneId) const;
        ZoneScript* GetZoneScriptbyEventId(SpecialEventId eventId) const;

        // handlers
        // called when a player enters a battlefield area
        void HandlePlayerEnterZone(Player* player, uint32 zoneId);
        // called when player leaves a battlefield area
        void HandlePlayerLeaveZone(Player* player, uint32 zoneId);

    private:
        typedef std::vector<SpecialEvent*> SpecialEventSet;
        typedef std::unordered_map<uint32 /*eventid*/, SpecialEvent*> SpecialEventMap;
        typedef std::unordered_map<uint32 /*zoneid*/, SpecialEvent*> SpecialEventZoneMap;
        typedef std::array<uint32, SPECIALEVENT_EVENTID_MAX> SpecialEventScriptIds;

        // contains all initiated outdoor pvp events
        // used when initing / cleaning up
        SpecialEventSet m_SpecialEventSet;

        // maps the event ids to an outdoor pvp event
        // used in player event handling
        SpecialEventMap m_SpecialEventMap;

        // maps the zone ids to an outdoor pvp event
        // used in player event handling
        SpecialEventZoneMap m_SpecialEventZoneMap;

        // Holds the outdoor PvP templates
        SpecialEventScriptIds m_SpecialEventDatas;
        // update interval
        uint32 _updateTimer;
};

#define sSpecialEventMgr SpecialEventMgr::instance()

#endif // SPECIALEVENT_MGR_H_
