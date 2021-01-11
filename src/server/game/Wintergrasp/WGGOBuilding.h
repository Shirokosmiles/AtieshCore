/*
 * Copyright (C) 2021+ ATieshCore <https://at-wow.org/>
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

#include "WintergraspMgr.h"
#include "SharedDefines.h"
#include "WorldStatePackets.h"

struct StaticWintergraspTowerInfo;

class WGGameObjectBuilding
{
public:
    WGGameObjectBuilding(WintergraspMgr* wg, WintergraspGameObjectBuildingType type, uint32 worldState);
    ~WGGameObjectBuilding();

    void Init(GameObject* go);
    ObjectGuid const& GetGUID() const { return _buildGUID; }

    void Rebuild();
    void RebuildGate();

    // Called when associated gameobject is damaged
    void Damaged();
    // Called when associated gameobject is destroyed
    void Destroyed();

    void UpdateGo();
    void FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet);

    void Save();

    uint32 GetID() { return _buildID; }
    bool IsAttackTower() { return _buildID >= BATTLEFIELD_WG_TOWER_SHADOWSIGHT && _buildID <= BATTLEFIELD_WG_TOWER_FLAMEWATCH; }
    bool IsAttackSide() { return IsAttackTower(); }
    bool IsAlive() { return _state != BATTLEFIELD_WG_OBJECTSTATE_NEUTRAL_DESTROY && _state != BATTLEFIELD_WG_OBJECTSTATE_HORDE_DESTROY && _state != BATTLEFIELD_WG_OBJECTSTATE_ALLIANCE_DESTROY; }

    TeamId GetTeamController() { return _teamControl; }
    WintergraspGameObjectBuildingType GetType() { return _type; }

private:
    // WG object
    WintergraspMgr* _wg;
    // Linked gameobject
    ObjectGuid _buildGUID;
    // ID building
    uint32 _buildID;
    // the team that controls this point
    TeamId _teamControl;
    WintergraspGameObjectBuildingType _type;
    uint32 _worldState;
    WintergraspGameObjectState _state;
    StaticWintergraspTowerInfo const* _staticTowerInfo;
    // GameObject associations
    GuidVector m_GameObjectList[3];
};
