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
enum SpecialEventId;

typedef std::unordered_map<uint32, SpecialEvent*> SpecialEventsContainer;

class TC_GAME_API SpecialEventMgr
{
    public:
        static SpecialEventMgr* instance();

        // create SpecialEvents
        void InitSpecialEvents();

        SpecialEvent* GetEnabledSpecialEvent(uint32 eventId);
        SpecialEvent* GetSpecialEvent(SpecialEventId eventId);

        void Update(uint32 diff);

    private:
        SpecialEventMgr();
        ~SpecialEventMgr();

        // contains all initiated battlefields
        SpecialEventsContainer _specialEventContainer;
        // update interval
        uint32 _updateTimer;
};

#define sSpecialEventMgr SpecialEventMgr::instance()

#endif // SPECIALEVENT_MGR_H_
