/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
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

#ifndef _WARDENCHECKMGR_H
#define _WARDENCHECKMGR_H

#include <map>
#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>
#include "Cryptography/BigNumber.h"

enum WardenActions : uint8
{
    WARDEN_ACTION_LOG,
    WARDEN_ACTION_KICK,
    WARDEN_ACTION_BAN
};

struct WardenCheck
{
    uint8 Type;
    BigNumber Data;
    uint32 Address;                                         // PROC_CHECK, MEM_CHECK, PAGE_CHECK
    uint8 Length;                                           // PROC_CHECK, MEM_CHECK, PAGE_CHECK
    std::string Str;                                        // LUA, MPQ, DRIVER
    std::string Comment;
    uint16 CheckId;
    uint8 Action;
};

struct WardenCheckResult
{
    uint16 Id;
    BigNumber Result;                                       // MEM_CHECK
};

class TC_GAME_API WardenCheckMgr
{
    private:
        WardenCheckMgr();
        ~WardenCheckMgr();

    public:
        static WardenCheckMgr* instance()
        {
            static WardenCheckMgr instance;
            return &instance;
        }

        WardenCheck* GetWardenDataById(uint16 /*build*/, uint16 /*id*/);
        WardenCheckResult* GetWardenResultById(uint16 /*build*/, uint16 /*id*/);
        void GetWardenCheckIds(bool isMemCheck /* true = MEM */, uint16 build, std::list<uint16>& list);

        void LoadWardenChecks();
        void LoadWardenOverrides();

        boost::shared_mutex _checkStoreLock;

    private:
        
        typedef std::multimap< uint16, WardenCheck* > CheckMap;
        typedef std::multimap< uint16, WardenCheckResult* > CheckResultMap;

        CheckMap       CheckStore;
        CheckResultMap CheckResultStore;

};

#define sWardenCheckMgr WardenCheckMgr::instance()

#endif
