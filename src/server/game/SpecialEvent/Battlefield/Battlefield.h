/*
 * Copyright (C) 2008-2019 TrinityCore <https://www.trinitycore.org/>
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

#ifndef TRINITY_BATTLEFIELD_H_
#define TRINITY_BATTLEFIELD_H_

#include "Common.h"
#include "SpecialEvent.h"
#include "SharedDefines.h"
#include "Timer.h"
#include <memory>
#include <unordered_map>

class BattlefieldGraveyard;
class ObjectGuid;
class Player;
class Unit;
struct WorldSafeLocsEntry;

class TC_GAME_API Battlefield : public SpecialEvent
{
public:
    typedef std::unique_ptr<BattlefieldGraveyard> BattlefieldGraveyardPointer;
    typedef std::unordered_map<uint8 /*id*/, BattlefieldGraveyardPointer> BattlefieldGraveyardContainer;

    explicit Battlefield(BattlefieldBattleId battleId, BattlefieldZoneId zoneId);
    virtual ~Battlefield();    

    void EmplaceGraveyard(uint8 id, BattlefieldGraveyardPointer&& pointer);
    BattlefieldGraveyardPointer& GetGraveyard(uint8 graveyardId);

    BattlefieldBattleId GetId() const { return _battleId; }
    uint32 GetZoneId() const { return _zoneId; }
    // enum PvPTeamId
    PvPTeamId GetControllingTeam() const override { return _controllingTeam; }
    // enum PvPTeamId
    PvPTeamId GetAttackingTeam() const override;
    // enum TeamId
    TeamId GetControllingTeamId() const override;
    // enum TeamId
    TeamId GetAttackingTeamId() const override;
    // Battle timer
    uint32 GetTimer() const { return _timer.GetExpiry(); }

private:
    Battlefield(Battlefield const&) = delete;
    Battlefield& operator=(Battlefield const&) = delete;

    // constant information
    BattlefieldBattleId _battleId;
    uint32 _zoneId;

    PvPTeamId _controllingTeam;
    BattlefieldGraveyardContainer _graveyards;
};

#endif
