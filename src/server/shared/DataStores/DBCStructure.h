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

#ifndef TRINITY_DBCSTRUCTURE_H
#define TRINITY_DBCSTRUCTURE_H

#include "Define.h"
#include "DBCEnums.h"
#include "SharedDefines.h"
#include "Util.h"
#include <set>
#include <map>

// Structures used to access raw DBC data require packing for portability
#pragma pack(push, 1)

/*
struct HolidayDescriptionsEntry
{
    uint32 ID;                                              // 0
    char const* Description[16];                            // 1-16
    uint32 Description_lang_mask;                           // 17
};
*/

/*
struct HolidayNamesEntry
{
    uint32 ID;                                              // 0
    char const* Name[16];                                   // 1-16
    uint32 Name_lang_mask;                                  // 17
};
*/

/*
struct ItemCondExtCostsEntry
{
    uint32 ID;                                              // 0
    uint32 CondExtendedCost;                                // 1 ItemTemplate::CondExtendedCost
    uint32 ItemExtendedCostEntry;                           // 2 ItemTemplate::ExtendedCost
    uint32 ArenaSeason;                                     // 3 arena season number (1-4)
};
*/

//#define MAX_ITEM_ENCHANTMENT_EFFECTS 3

/*
struct SkillLineCategoryEntry
{
    uint32 ID;                                              // 0
    char const* Name[16];                                   // 1-17
    uint32 Name_lang_mask;                                  // 18
    uint32 SortIndex;                                       // 19
};
*/










struct WorldSafeLocsEntry
{
    uint32 ID;                                              // 0
    uint32 Continent;                                       // 1
    DBCPosition3D Loc;                                      // 2-4
    //char const* AreaName[16]                              // 5-20
    //uint32 AreaName_lang_mask;                            // 21
};

/*
struct WorldStateUI
{
    uint32 ID;                                              // 0
    uint32 MapID;                                           // 1 Can be -1 to show up everywhere.
    uint32 AreaID;                                          // 2 Can be zero for "everywhere".
    uint32 PhaseShift;                                      // 3 Phase this WorldState is avaliable in
    char const* Icon;                                       // 4 The icon that is used in the interface.
    char const* String;                                     // 5-20
    uint32 String_lang_mask;                                // 21
    char const* Tooltip;                                    // 22-37
    uint32 Tooltip_lang_mask;                               // 38
    uint32 StateVariable;                                   // 39
    uint32 Type;                                            // 40 0 = unknown, 1 = unknown, 2 = not shown in ui, 3 = wintergrasp
    char const* DynamicIcon;                                // 41
    char const* DynamicTooltip[16];                         // 42-57
    uint32 DynamicTooltip_lang_mask;                        // 58
    char const* ExtendedUI;                                 // 59
    uint32 ExtendedUIStateVariable[3];                      // 60-62
};
*/

/*
struct WorldStateZoneSounds
{
    uint32 WorldStateID;                                    // 0
    uint32 WorldStateValue;                                 // 1
    uint32 AreaID;                                          // 2
    uint32 WMOAreaID;                                       // 3
    uint32 ZoneIntroMusicID;                                // 4
    uint32 ZoneMusicID;                                     // 5
    uint32 SoundAmbienceID;                                 // 6
    uint32 SoundProviderPreferencesID;                      // 7
};
*/

#pragma pack(pop)

// Structures not used for casting to loaded DBC data and not required then packing
/*struct MapDifficulty
{
    MapDifficulty() : resetTime(0), maxPlayers(0), hasErrorMessage(false) { }
    MapDifficulty(uint32 _resetTime, uint32 _maxPlayers, bool _hasErrorMessage) : resetTime(_resetTime), maxPlayers(_maxPlayers), hasErrorMessage(_hasErrorMessage) { }

    uint32 resetTime;
    uint32 maxPlayers;
    bool hasErrorMessage;
};*/





#endif
