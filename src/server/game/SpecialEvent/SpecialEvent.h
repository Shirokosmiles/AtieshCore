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

#ifndef SPECIALEVENT_H_
#define SPECIALEVENT_H_

#include "Timer.h"
#include "SharedDefines.h"

enum SpecialEventId
{
    SPECIALEVENT_EVENTID_WINTERGRASP   = 1, // Wintergrasp (for Future implementation)
    SPECIALEVENT_EVENTID_DALARANCRATER = 2, // Dalaran Crater PVP battle
    SPECIALEVENT_EVENTID_MAX
};

enum SpecialEventTimers
{
    SPECIALEVENT_OBJECTIVE_UPDATE_INTERVAL = 1000,
    SPECIALEVENT_RESURRECT_ITERVAL = 30000
};
class SpecialEvent;
class TC_GAME_API SpecialEvent
{
    friend class SpecialEventMgr;
    public:

        // ctor
        SpecialEvent();
        // dtor
        virtual ~SpecialEvent();

        // enables or disables the special event
        void StartSpecialEvent();
        void EndSpecialEvent(bool endByTimer);        

        bool IsEnabled() const { return _enabled; }
        bool IsActiveTime() const { return _active; }

        /*void SetId(uint32 id) { _eventId = id; }
        void SetNormalTimer(uint32 timer) { _EventTime = timer; }
        void SetDurationTimer(uint32 timer) { _noEventTime = timer; }

        void SetTimer(uint32 timer) { _timer.Reset(timer); }       
        */
        uint32 GetEventId() { return _eventId; }
        uint32 GetCooldownTimer() { return _EventTime; }
        uint32 GetDurationTimer() { return _noEventTime; }
        time_t GetTimeOfNextEvent() { return _gameTimeNextEvent; }
        void RegisterEvent(uint32 eventId);

        // Functions for each Event Scripts
        virtual bool SetupSpecialEvent(bool active, bool enabled, uint32 id, uint32 cooldownTimer, uint32 durationTimer);
        virtual void Update(uint32 diff);
        virtual void OnSpecialEventStart() { }
        virtual void OnSpecialEventEnd(bool /*endByTimer*/) { }
        virtual void AddPlayer(ObjectGuid playerGUID) { }
        virtual void RemovePlayer(ObjectGuid playerGUID) { }
        virtual bool IsPossibleToRegister() { return true; }
        virtual bool IsMemberOfEvent(Player* player) { return false; }
        virtual uint32 GetCountPlayerInEvent() { return 0; }

    protected:
        TimeTrackerSmall _timer;
        bool _active;
        bool _enabled;
        // from database
        uint32 _eventId;
        uint32 _EventTime;      // length of the event
        uint32 _noEventTime;    // time between two events
        time_t _gameTimeNextEvent;
};

#endif
