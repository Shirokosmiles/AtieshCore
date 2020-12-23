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

#define MAX_ITEM_ENCHANTMENT_EFFECTS 3

/*
struct SkillLineCategoryEntry
{
    uint32 ID;                                              // 0
    char const* Name[16];                                   // 1-17
    uint32 Name_lang_mask;                                  // 18
    uint32 SortIndex;                                       // 19
};
*/




struct SpellCategoryEntry
{
    uint32 ID;                                              // 0
    uint32 Flags;                                           // 1
};

struct SpellDifficultyEntry
{
    uint32 ID;                                              // 0
    int32 DifficultySpellID[MAX_DIFFICULTY];                // 1-4 instance modes: 10N, 25N, 10H, 25H or Normal/Heroic if only 1-2 is set, if 3-4 is 0 then Mode-2
};

struct SpellDurationEntry
{
    uint32 ID;                                              // 0
    int32 Duration;                                         // 1
    int32 DurationPerLevel;                                 // 2
    int32 MaxDuration;                                      // 3
};

struct SpellFocusObjectEntry
{
    uint32 ID;                                              // 0
    //char const* Name[16];                                 // 1-15
    //uint32 Name_lang_mask;                                // 16
};

struct SpellItemEnchantmentEntry
{
    uint32 ID;                                              // 0
    //uint32 Charges;                                       // 1
    uint32 Effect[MAX_ITEM_ENCHANTMENT_EFFECTS];            // 2-4
    uint32 EffectPointsMin[MAX_ITEM_ENCHANTMENT_EFFECTS];   // 5-7
    //uint32 EffectPointsMax[MAX_ITEM_ENCHANTMENT_EFFECTS]  // 8-10
    uint32 EffectArg[MAX_ITEM_ENCHANTMENT_EFFECTS];         // 11-13
    char const* Name[16];                                   // 14-29
    //uint32 Name_lang_mask;                                // 30
    uint32 ItemVisual;                                      // 31
    uint32 Flags;                                           // 32
    uint32 SrcItemID;                                       // 33
    uint32 ConditionID;                                     // 34
    uint32 RequiredSkillID;                                 // 35
    uint32 RequiredSkillRank;                               // 36
    uint32 MinLevel;                                        // 37
};

struct SpellItemEnchantmentConditionEntry
{
    uint32 ID;                                              // 0
    uint8 LtOperandType[5];                                 // 1-5
    //uint32 LtOperand[5];                                  // 6-10
    uint8 Operator[5];                                      // 11-15
    uint8 RtOperandType[5];                                 // 15-20
    uint32 RtOperand[5];                                    // 21-25
    //uint8 Logic[5];                                       // 25-30
};

struct SpellRadiusEntry
{
    uint32 ID;                                              // 0
    float Radius;                                           // 1
    float RadiusPerLevel;                                   // 2
    float RadiusMax;                                        // 3
};

struct SpellRangeEntry
{
    uint32 ID;                                              // 0
    float RangeMin[2];                                      // 1-2 [0] Hostile [1] Friendly
    float RangeMax[2];                                      // 3-4 [0] Hostile [1] Friendly
    uint32 Flags;                                           // 5
    //char const* DisplayName[16];                          // 6-21
    //uint32 DisplayName_lang_mask;                         // 22
    //char const* DisplayNameShort[16];                     // 23-38
    //uint32 DisplayNameShort_lang_mask;                    // 39
};

struct SpellRuneCostEntry
{
    uint32 ID;                                              // 0
    uint32 RuneCost[3];                                     // 1-3 [0] Blood [1] Unholy [2] Frost
    uint32 RunicPower;                                      // 4

    bool NoRuneCost() const { return RuneCost[0] == 0 && RuneCost[1] == 0 && RuneCost[2] == 0; }
    bool NoRunicPowerGain() const { return RunicPower == 0; }
};

#define MAX_SHAPESHIFT_SPELLS 8

struct SpellShapeshiftFormEntry
{
    uint32 ID;                                              // 0
    //uint32 BonusActionBar;                                // 1
    //char const* Name[16];                                 // 2-17
    //uint32 Name_lang_mask;                                // 18
    uint32 Flags;                                           // 19
    int32 CreatureType;                                     // 20 <= 0 humanoid, other normal creature types
    //uint32 AttackIconID;                                  // 21
    uint32 CombatRoundTime;                                 // 22
    uint32 CreatureDisplayID[4];                            // 23-26 [0] Alliance [1] Horde [2] Unk [3] Unk
    uint32 PresetSpellID[MAX_SHAPESHIFT_SPELLS];            // 27-34
};

struct SpellVisualEntry
{
    //uint32 ID;                                            // 0
    //uint32 PrecastKit;                                    // 1
    //uint32 CastKit;                                       // 2
    //uint32 ImpactKit;                                     // 3
    //uint32 StateKit;                                      // 4
    //uint32 StateDoneKit;                                  // 5
    //uint32 ChannelKit;                                    // 6
    uint32 HasMissile;                                      // 7
    int32 MissileModel;                                     // 8
    //uint32 MissilePathType;                               // 9
    //uint32 MissileDestinationAttachment;                  // 10
    //uint32 MissileSound;                                  // 11
    //uint32 AnimEventSoundID;                              // 12
    //uint32 Flags;                                         // 13
    //uint32 CasterImpactKit;                               // 14
    //uint32 TargetImpactKit;                               // 15
    //int32 MissileAttachment;                              // 16
    //uint32 MissileFollowGroundHeight;                     // 17
    //uint32 MissileFollowGroundDropSpeed;                  // 18
    //uint32 MissileFollowGroundApproach;                   // 19
    //uint32 MissileFollowGroundFlags;                      // 20
    //uint32 MissileMotion;                                 // 21
    //uint32 MissileTargetingKit;                           // 22
    //uint32 InstantAreaKit;                                // 23
    //uint32 ImpactAreaKit;                                 // 24
    //uint32 PersistentAreaKit;                             // 25
    //DBCPosition3D MissileCastOffset;                      // 26-28
    //DBCPosition3D MissileImpactOffset;                    // 29-31
};

struct StableSlotPricesEntry
{
    uint32 ID;                                              // 0
    uint32 Cost;                                            // 1
};

struct SummonPropertiesEntry
{
    uint32 ID;                                              // 0
    uint32 Control;                                         // 1
    uint32 Faction;                                         // 2
    uint32 Title;                                           // 3
    uint32 Slot;                                            // 4
    uint32 Flags;                                           // 5
};

struct TalentEntry
{
    uint32 ID;                                              // 0
    uint32 TabID;                                           // 1 index in TalentTab.dbc (TalentTabEntry)
    uint32 TierID;                                          // 2
    uint32 ColumnIndex;                                     // 3
    std::array<uint32, MAX_TALENT_RANK> SpellRank;          // 4-8
    //std::array<uint32, 4> SpellRankUnused;                // 9-12
    uint32 PrereqTalent;                                    // 13 index in Talent.dbc (TalentEntry)
    //std::array<uint32, 2> PrereqTalentUnused;             // 14-15
    uint32 PrereqRank;                                      // 16
    //std::array<uint32, 2> PrereqRankUnused;               // 17-18
    //uint32 Flags;                                         // 19
    //uint32 RequiredSpellID;                               // 20 all 0
    //std::array<uint32, 2> CategoryMask;                   // 21 its a 64 bit mask for pet 1<<CategoryEnumID in CreatureFamily.dbc
};

struct TalentTabEntry
{
    uint32 ID;                                              // 0
    //char const* Name[16];                                 // 1-16
    //uint32 Name_lang_mask;                                // 17
    //unit32 SpellIconID;                                   // 18
    //uint32 RaceMask;                                      // 19
    uint32 ClassMask;                                       // 20
    uint32 PetTalentMask;                                   // 21
    uint32 OrderIndex;                                      // 22
    //char const* BackgroundFile;                           // 23
};

struct TaxiNodesEntry
{
    uint32 ID;                                              // 0
    uint32 ContinentID;                                     // 1
    DBCPosition3D Pos;                                      // 2-4
    char const* Name[16];                                   // 5-21
    //uint32 Name_lang_mask;                                // 22
    uint32 MountCreatureID[2];                              // 23-24
};

struct TaxiPathEntry
{
    uint32 ID;                                              // 0
    uint32 FromTaxiNode;                                    // 1
    uint32 ToTaxiNode;                                      // 2
    uint32 Cost;                                            // 3
};

struct TaxiPathNodeEntry
{
    //uint32 ID;                                            // 0
    uint32 PathID;                                          // 1
    uint32 NodeIndex;                                       // 2
    uint32 ContinentID;                                     // 3
    DBCPosition3D Loc;                                      // 4-6
    uint32 Flags;                                           // 7
    uint32 Delay;                                           // 8
    uint32 ArrivalEventID;                                  // 9
    uint32 DepartureEventID;                                // 10
};

struct TeamContributionPointsEntry
{
    //uint32 ID;                                            // 0
    float Data;                                             // 1
};

struct TotemCategoryEntry
{
    uint32 ID;                                              // 0
    //char const* Name[16];                                 // 1-16
    //uint32 Name_lang_mask;                                // 17
    uint32 TotemCategoryType;                               // 18 (one for specialization)
    uint32 TotemCategoryMask;                               // 19 (compatibility mask for same type: different for totems, compatible from high to low for rods)
};

struct TransportAnimationEntry
{
    //uint32 ID;                                            // 0
    uint32 TransportID;                                     // 1
    uint32 TimeIndex;                                       // 2
    DBCPosition3D Pos;                                      // 3
    //uint32 SequenceID;                                    // 4
};

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

struct TalentSpellPos
{
    TalentSpellPos() : talent_id(0), rank(0) { }
    TalentSpellPos(uint16 _talent_id, uint8 _rank) : talent_id(_talent_id), rank(_rank) { }

    uint16 talent_id;
    uint8  rank;
};

typedef std::map<uint32, TalentSpellPos> TalentSpellPosMap;

struct TaxiPathBySourceAndDestination
{
    TaxiPathBySourceAndDestination() : ID(0), price(0) { }
    TaxiPathBySourceAndDestination(uint32 _id, uint32 _price) : ID(_id), price(_price) { }

    uint32    ID;
    uint32    price;
};
typedef std::map<uint32, TaxiPathBySourceAndDestination> TaxiPathSetForSource;
typedef std::map<uint32, TaxiPathSetForSource> TaxiPathSetBySource;

typedef std::vector<TaxiPathNodeEntry const*> TaxiPathNodeList;
typedef std::vector<TaxiPathNodeList> TaxiPathNodesByPath;

#endif
