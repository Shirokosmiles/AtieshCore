/*
 * Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
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

#include "WorldSession.h"
#include "DBCStructure.h"
#include "Log.h"
#include "Map.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "Vehicle.h"
#include "VehiclePackets.h"
#include "WorldPacket.h"

void WorldSession::HandleDismissControlledVehicle(WorldPackets::Vehicle::MoveDismissVehicle& moveDismissVehicle)
{
    TC_LOG_DEBUG("network", "WORLD: Recvd CMSG_DISMISS_CONTROLLED_VEHICLE");

    ObjectGuid vehicleGUID = _player->GetCharmGUID();

    if (!vehicleGUID)                                       // something wrong here...
        return;

    _player->UpdateMovementInfo(moveDismissVehicle.Status);

    _player->ExitVehicle();
}

void WorldSession::HandleRequestVehiclePrevSeat(WorldPackets::Vehicle::RequestVehiclePrevSeat& /*requestVehiclePrevSeat*/)
{
    Unit* vehicle_base = GetPlayer()->GetVehicleBase();
    if (!vehicle_base)
        return;

    VehicleSeatEntry const* seat = GetPlayer()->GetVehicle()->GetSeatForPassenger(GetPlayer());
    if (!seat->CanSwitchFromSeat())
    {
        TC_LOG_ERROR("network", "HandleRequestVehiclePrevSeat: %s tried to switch seats but current seatflags %u don't permit that.",
            GetPlayer()->GetGUID().ToString().c_str(), seat->m_flags);
        return;
    }

    GetPlayer()->ChangeSeat(-1, false);
}

void WorldSession::HandleRequestVehicleNextSeat(WorldPackets::Vehicle::RequestVehicleNextSeat& /*requestVehicleNextSeat*/)
{
    Unit* vehicle_base = GetPlayer()->GetVehicleBase();
    if (!vehicle_base)
        return;

    VehicleSeatEntry const* seat = GetPlayer()->GetVehicle()->GetSeatForPassenger(GetPlayer());
    if (!seat->CanSwitchFromSeat())
    {
        TC_LOG_ERROR("network", "HandleRequestVehicleNextSeat: %s tried to switch seats but current seatflags %u don't permit that.",
            GetPlayer()->GetGUID().ToString().c_str(), seat->m_flags);
        return;
    }

    GetPlayer()->ChangeSeat(-1, true);
}

void WorldSession::HandleMoveChangeVehicleSeats(WorldPackets::Vehicle::MoveChangeVehicleSeats& moveChangeVehicleSeats)
{
    Unit* vehicle_base = GetPlayer()->GetVehicleBase();
    if (!vehicle_base)
        return;

    VehicleSeatEntry const* seat = GetPlayer()->GetVehicle()->GetSeatForPassenger(GetPlayer());
    if (!seat->CanSwitchFromSeat())
    {
        TC_LOG_ERROR("network", "HandleMoveChangeVehicleSeats: %s tried to switch seats but current seatflags %u don't permit that.",
            GetPlayer()->GetGUID().ToString().c_str(), seat->m_flags);
        return;
    }

    if (vehicle_base->GetGUID() != moveChangeVehicleSeats.Status.guid)
        return;

    vehicle_base->UpdateMovementInfo(moveChangeVehicleSeats.Status);

    if (moveChangeVehicleSeats.DstVehicle.IsEmpty())
        GetPlayer()->ChangeSeat(-1, moveChangeVehicleSeats.DstSeatIndex != 255);
    else if (Unit* vehUnit = ObjectAccessor::GetUnit(*GetPlayer(), moveChangeVehicleSeats.DstVehicle))
        if (Vehicle* vehicle = vehUnit->GetVehicleKit())
            if (vehicle->HasEmptySeat(moveChangeVehicleSeats.DstSeatIndex))
                vehUnit->HandleSpellClick(GetPlayer(), int8(moveChangeVehicleSeats.DstSeatIndex));
}

void WorldSession::HandleRequestVehicleSwitchSeat(WorldPackets::Vehicle::RequestVehicleSwitchSeat& requestVehicleSwitchSeat)
{
    Unit* vehicle_base = GetPlayer()->GetVehicleBase();
    if (!vehicle_base)
        return;

    VehicleSeatEntry const* seat = GetPlayer()->GetVehicle()->GetSeatForPassenger(GetPlayer());
    if (!seat->CanSwitchFromSeat())
    {
        TC_LOG_ERROR("network", "HandleRequestVehicleSwitchSeat: %s tried to switch seats but current seatflags %u don't permit that.",
            GetPlayer()->GetGUID().ToString().c_str(), seat->m_flags);
        return;
    }

    if (vehicle_base->GetGUID() == requestVehicleSwitchSeat.Vehicle)
        GetPlayer()->ChangeSeat(int8(requestVehicleSwitchSeat.SeatIndex));
    else if (Unit* vehUnit = ObjectAccessor::GetUnit(*GetPlayer(), requestVehicleSwitchSeat.Vehicle))
        if (Vehicle* vehicle = vehUnit->GetVehicleKit())
            if (vehicle->HasEmptySeat(int8(requestVehicleSwitchSeat.SeatIndex)))
                vehUnit->HandleSpellClick(GetPlayer(), int8(requestVehicleSwitchSeat.SeatIndex));
}

void WorldSession::HandleEnterPlayerVehicle(WorldPacket &data)
{
    // Read guid
    ObjectGuid guid;
    data >> guid;

    if (Player* player = ObjectAccessor::GetPlayer(*_player, guid))
    {
        if (!player->GetVehicleKit())
            return;
        if (!player->IsInRaidWith(_player))
            return;
        if (!player->IsWithinDistInMap(_player, INTERACTION_DISTANCE))
            return;
        // Dont' allow players to enter player vehicle on arena
        if (!_player->FindMap() || _player->FindMap()->IsBattleArena())
            return;

        _player->EnterVehicle(player);
    }
}

void WorldSession::HandleEjectPassenger(WorldPacket &data)
{
    Vehicle* vehicle = _player->GetVehicleKit();
    if (!vehicle)
    {
        data.rfinish();                                     // prevent warnings spam
        TC_LOG_ERROR("network", "HandleEjectPassenger: %s is not in a vehicle!", GetPlayer()->GetGUID().ToString().c_str());
        return;
    }

    ObjectGuid guid;
    data >> guid;

    if (guid.IsUnit())
    {
        Unit* unit = ObjectAccessor::GetUnit(*_player, guid);
        if (!unit) // creatures can be ejected too from player mounts
        {
            TC_LOG_ERROR("network", "%s tried to eject %s from vehicle, but the latter was not found in world!", GetPlayer()->GetGUID().ToString().c_str(), guid.ToString().c_str());
            return;
        }

        if (!unit->IsOnVehicle(vehicle->GetBase()))
        {
            TC_LOG_ERROR("network", "%s tried to eject %s, but they are not in the same vehicle", GetPlayer()->GetGUID().ToString().c_str(), guid.ToString().c_str());
            return;
        }

        VehicleSeatEntry const* seat = vehicle->GetSeatForPassenger(unit);
        ASSERT(seat);
        if (seat->IsEjectable())
            unit->ExitVehicle();
        else
            TC_LOG_ERROR("network", "Player %u attempted to eject %s from non-ejectable seat.", GetPlayer()->GetGUID().GetCounter(), guid.ToString().c_str());
    }
    else
        TC_LOG_ERROR("network", "HandleEjectPassenger: %s tried to eject invalid %s ", GetPlayer()->GetGUID().ToString().c_str(), guid.ToString().c_str());
}

void WorldSession::HandleRequestVehicleExit(WorldPacket& /*recvData*/)
{
    TC_LOG_DEBUG("network", "WORLD: Recvd CMSG_REQUEST_VEHICLE_EXIT");

    if (Vehicle* vehicle = GetPlayer()->GetVehicle())
    {
        if (VehicleSeatEntry const* seat = vehicle->GetSeatForPassenger(GetPlayer()))
        {
            if (seat->CanEnterOrExit())
                GetPlayer()->ExitVehicle();
            else
                TC_LOG_ERROR("network", "Player %u tried to exit vehicle, but seatflags %u (ID: %u) don't permit that.",
                    GetPlayer()->GetGUID().GetCounter(), seat->m_ID, seat->m_flags);
        }
    }
}
