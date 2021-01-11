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

struct StaticWintergraspWorkshopInfo;

class WGWorkshop
{
public:
    WGWorkshop(WintergraspMgr* wg, uint8 type);
    ~WGWorkshop();

    uint8 GetId() const;
    TeamId GetTeamControl() const { return _teamControl; }

    void InitialWorkshopAndCapturePoint(TeamId teamId, uint8 workshopId);
    // Called on change faction in CapturePoint class
    void GiveControlTo(TeamId teamId, bool init = false);

    void UpdateGraveyardAndWorkshop();

    void FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet);

    void Save();

    void UpdateCreatureAndGo();

private:
    WintergraspMgr* _wg;                            // Pointer to wintergrasp
    ObjectGuid _buildGUID;
    WintergraspGameObjectState _state;                       // For worldstate
    TeamId _teamControl;                            // Team witch control the workshop

    StaticWintergraspWorkshopInfo const* _staticInfo;

    // GameObject associations
    GuidVector m_GOList[3];
    // Flag banner GO with CapturePoint for spawn and despawn
    GuidVector m_workshopGO;
};
