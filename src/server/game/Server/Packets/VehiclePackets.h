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

#ifndef VehiclePackets_h__
#define VehiclePackets_h__

#include "Packet.h"
#include "MovementPackets.h"

namespace WorldPackets
{
    namespace Vehicle
    {
        class MoveDismissVehicle final : public ClientPacket
        {
        public:
            MoveDismissVehicle(WorldPacket&& packet) : ClientPacket(CMSG_DISMISS_CONTROLLED_VEHICLE, std::move(packet)) { }

            void Read() override;

            MovementInfo Status;
        };

        class RequestVehiclePrevSeat final : public ClientPacket
        {
        public:
            RequestVehiclePrevSeat(WorldPacket&& packet) : ClientPacket(CMSG_REQUEST_VEHICLE_PREV_SEAT, std::move(packet)) { }

            void Read() override { }
        };

        class RequestVehicleNextSeat final : public ClientPacket
        {
        public:
            RequestVehicleNextSeat(WorldPacket&& packet) : ClientPacket(CMSG_REQUEST_VEHICLE_NEXT_SEAT, std::move(packet)) { }

            void Read() override { }
        };

        class MoveChangeVehicleSeats final : public ClientPacket
        {
        public:
            MoveChangeVehicleSeats(WorldPacket&& packet) : ClientPacket(CMSG_CHANGE_SEATS_ON_CONTROLLED_VEHICLE, std::move(packet)) { }

            void Read() override;

            ObjectGuid DstVehicle;
            MovementInfo Status;
            uint8 DstSeatIndex = 255;
        };

        class RequestVehicleSwitchSeat final : public ClientPacket
        {
        public:
            RequestVehicleSwitchSeat(WorldPacket&& packet) : ClientPacket(CMSG_REQUEST_VEHICLE_SWITCH_SEAT, std::move(packet)) { }

            void Read() override;

            ObjectGuid Vehicle;
            uint8 SeatIndex = 255;
        };
    }
}

#endif // VehiclePackets_h__
