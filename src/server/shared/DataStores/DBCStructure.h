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









struct TransportRotationEntry
{
    //uint32 ID;                                            // 0
    uint32 GameObjectsID;                                   // 1
    uint32 TimeIndex;                                       // 2
    float X;                                                // 3
    float Y;                                                // 4
    float Z;                                                // 5
    float W;                                                // 6
};

#define MAX_VEHICLE_SEATS 8

struct VehicleEntry
{
    uint32 ID;                                              // 0
    uint32 Flags;                                           // 1
    float TurnSpeed;                                        // 2
    float PitchSpeed;                                       // 3
    float PitchMin;                                         // 4
    float PitchMax;                                         // 5
    uint32 SeatID[MAX_VEHICLE_SEATS];                       // 6-13
    float MouseLookOffsetPitch;                             // 14
    float CameraFadeDistScalarMin;                          // 15
    float CameraFadeDistScalarMax;                          // 16
    float CameraPitchOffset;                                // 17
    float FacingLimitRight;                                 // 18
    float FacingLimitLeft;                                  // 19
    float MsslTrgtTurnLingering;                            // 20
    float MsslTrgtPitchLingering;                           // 21
    float MsslTrgtMouseLingering;                           // 22
    float MsslTrgtEndOpacity;                               // 23
    float MsslTrgtArcSpeed;                                 // 24
    float MsslTrgtArcRepeat;                                // 25
    float MsslTrgtArcWidth;                                 // 26
    float MsslTrgtImpactRadius[2];                          // 27-28
    char const* MsslTrgtArcTexture;                         // 29
    char const* MsslTrgtImpactTexture;                      // 30
    char const* MsslTrgtImpactModel[2];                     // 31-32
    float CameraYawOffset;                                  // 33
    uint32 UiLocomotionType;                                // 34
    float MsslTrgtImpactTexRadius;                          // 35
    uint32 VehicleUIIndicatorID;                            // 36
    uint32 PowerDisplayID;                                  // 37
    //uint32 PowerDisplayIDUnused[2];                       // 38-39
};

struct VehicleSeatEntry
{
    uint32 ID;                                              // 0
    uint32 Flags;                                           // 1
    int32 AttachmentID;                                     // 2
    DBCPosition3D AttachmentOffset;                         // 3-5
    float EnterPreDelay;                                    // 6
    float EnterSpeed;                                       // 7
    float EnterGravity;                                     // 8
    float EnterMinDuration;                                 // 9
    float EnterMaxDuration;                                 // 10
    float EnterMinArcHeight;                                // 11
    float EnterMaxArcHeight;                                // 12
    int32 EnterAnimStart;                                   // 13
    int32 EnterAnimLoop;                                    // 14
    int32 RideAnimStart;                                    // 15
    int32 RideAnimLoop;                                     // 16
    int32 RideUpperAnimStart;                               // 17
    int32 RideUpperAnimLoop;                                // 18
    float ExitPreDelay;                                     // 19
    float ExitSpeed;                                        // 20
    float ExitGravity;                                      // 21
    float ExitMinDuration;                                  // 22
    float ExitMaxDuration;                                  // 23
    float ExitMinArcHeight;                                 // 24
    float ExitMaxArcHeight;                                 // 25
    int32 ExitAnimStart;                                    // 26
    int32 ExitAnimLoop;                                     // 27
    int32 ExitAnimEnd;                                      // 28
    float PassengerYaw;                                     // 29
    float PassengerPitch;                                   // 30
    float PassengerRoll;                                    // 31
    int32 PassengerAttachmentID;                            // 32
    int32 VehicleEnterAnim;                                 // 33
    int32 VehicleExitAnim;                                  // 34
    int32 VehicleRideAnimLoop;                              // 35
    int32 VehicleEnterAnimBone;                             // 36
    int32 VehicleExitAnimBone;                              // 37
    int32 VehicleRideAnimLoopBone;                          // 38
    float VehicleEnterAnimDelay;                            // 39
    float VehicleExitAnimDelay;                             // 40
    uint32 VehicleAbilityDisplay;                           // 41
    uint32 EnterUISoundID;                                  // 42
    uint32 ExitUISoundID;                                   // 43
    int32 UiSkin;                                           // 44
    uint32 FlagsB;                                          // 45
    //float CameraEnteringDelay;                            // 46
    //float CameraEnteringDuration;                         // 47
    //float CameraExitingDelay;                             // 48
    //float CameraExitingDuration;                          // 49
    //DBCPosition3D CameraOffset;                           // 50-52
    //float CameraPosChaseRate;                             // 53
    //float CameraFacingChaseRate;                          // 54
    //float CameraEnteringZoom;                             // 55
    //float CameraSeatZoomMin;                              // 56
    //float CameraSeatZoomMax;                              // 57

    inline bool HasFlag(VehicleSeatFlags flag) const { return (Flags & flag) != 0; }
    inline bool HasFlag(VehicleSeatFlagsB flag) const { return (FlagsB & flag) != 0; }

    inline bool CanEnterOrExit() const { return HasFlag(VehicleSeatFlags(VEHICLE_SEAT_FLAG_CAN_ENTER_OR_EXIT | VEHICLE_SEAT_FLAG_CAN_CONTROL | VEHICLE_SEAT_FLAG_SHOULD_USE_VEH_SEAT_EXIT_ANIM_ON_VOLUNTARY_EXIT)); }
    inline bool CanSwitchFromSeat() const { return HasFlag(VEHICLE_SEAT_FLAG_CAN_SWITCH); }
    inline bool IsUsableByOverride() const { return HasFlag(VehicleSeatFlags(VEHICLE_SEAT_FLAG_UNCONTROLLED | VEHICLE_SEAT_FLAG_UNK18))
                                    || HasFlag(VehicleSeatFlagsB(VEHICLE_SEAT_FLAG_B_USABLE_FORCED | VEHICLE_SEAT_FLAG_B_USABLE_FORCED_2 |
                                        VEHICLE_SEAT_FLAG_B_USABLE_FORCED_3 | VEHICLE_SEAT_FLAG_B_USABLE_FORCED_4)); }
    inline bool IsEjectable() const { return HasFlag(VEHICLE_SEAT_FLAG_B_EJECTABLE); }
};

struct WMOAreaTableEntry
{
    uint32 ID;                                              // 0 index
    int32 WMOID;                                            // 1 used in root WMO
    int32 NameSetID;                                        // 2 used in adt file
    int32 WMOGroupID;                                       // 3 used in group WMO
    //uint32 SoundProviderPref;                             // 4
    //uint32 SoundProviderPrefUnderwater;                   // 5
    //uint32 AmbienceID;                                    // 6
    //uint32 ZoneMusic;                                     // 7
    //uint32 IntroSound;                                    // 8
    uint32 Flags;                                           // 9 used for indoor/outdoor determination
    uint32 AreaTableID;                                     // 10 link to AreaTableEntry.ID
    //char const* AreaName[16];                             // 11
    //uint32 AreaName_lang_mask;                            // 12
};

struct WorldMapAreaEntry
{
    //uint32 ID;                                            // 0
    uint32 MapID;                                           // 1
    uint32 AreaID;                                          // 2
    //char const* AreaName                                  // 3
    float LocLeft;                                          // 4
    float LocRight;                                         // 5
    float LocTop;                                           // 6
    float LocBottom;                                        // 7
    int32 DisplayMapID;                                     // 8 -1 (map_id have correct map) other: virtual map where zone show (map_id - where zone in fact internally)
    //int32 DefaultDungeonFloor;                            // 9 pointer to DungeonMap.dbc (override x1, x2, y1, y2 coordinates)
    //uint32 ParentWorldMapID;                              // 10
};

#define MAX_WORLD_MAP_OVERLAY_AREA_IDX 4

struct WorldMapOverlayEntry
{
    uint32 ID;                                              // 0
    //uint32 MapAreaID;                                     // 1 ID in WorldMapArea.dbc
    uint32 AreaID[MAX_WORLD_MAP_OVERLAY_AREA_IDX];          // 2-5
    //uint32 MapPointX;                                     // 6
    //uint32 MapPointY;                                     // 7
    //char const* TextureName                               // 8
    //uint32 TextureWidth;                                  // 9
    //uint32 TextureHeight;                                 // 10
    //uint32 OffsetX;                                       // 11
    //uint32 OffsetY;                                       // 12
    //uint32 HitRectTop;                                    // 13
    //uint32 HitRectLeft;                                   // 14
    //uint32 HitRectBottom;                                 // 15
    //uint32 HitRectRight;                                  // 16
};

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
