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

#ifndef MovementPackets_h__
#define MovementPackets_h__

#include "Packet.h"
#include "MovementInfo.h"

namespace WorldPackets
{
    namespace Movement
    {
        class ClientPlayerMovement final : public ClientPacket
        {
        public:
            ClientPlayerMovement(WorldPacket&& packet) : ClientPacket(std::move(packet)) { }

            void Read() override;

            MovementInfo Status;
        };

        class TC_GAME_API MoveUpdate final : public ServerPacket
        {
        public:
            MoveUpdate(OpcodeServer opcode, std::size_t reserve) : ServerPacket(opcode, reserve) { }

            WorldPacket const* Write() override;

            MovementInfo Status;
        };

        class MoveSplineSetSpeed : public ServerPacket
        {
        public:
            MoveSplineSetSpeed(OpcodeServer opcode, PackedGuid const& moverGUID, float speed)
                : ServerPacket(opcode, moverGUID.size() + 4), MoverGUID(moverGUID), Speed(speed) { }

            WorldPacket const* Write() override;

            PackedGuid const& MoverGUID;
            float Speed;
        };

        class MoveSetSpeed : public ServerPacket
        {
        public:
            MoveSetSpeed(OpcodeServer opcode, PackedGuid const& moverGUID, uint32 sequenceIndex, float speed)
                : ServerPacket(opcode, moverGUID.size() + 4 + 4 + 1), MoverGUID(moverGUID), SequenceIndex(sequenceIndex), Speed(speed), WriteLastClickToMoveSpeed(1) { }

            WorldPacket const* Write() override;

            PackedGuid const& MoverGUID;
            uint32 SequenceIndex; ///< Unit movement packet index, incremented each time
            float Speed;
            uint8 WriteLastClickToMoveSpeed;
        };

        class MoveUpdateSpeed : public ServerPacket
        {
        public:
            MoveUpdateSpeed(OpcodeServer opcode) : ServerPacket(opcode) { }

            WorldPacket const* Write() override;

            MovementInfo Status;
            float Speed = 1.0f;
        };

        class MoveSplineSetFlag final : public ServerPacket
        {
        public:
            MoveSplineSetFlag(OpcodeServer opcode, PackedGuid const& moverGUID)
                : ServerPacket(opcode, moverGUID.size()), MoverGUID(moverGUID) { }

            WorldPacket const* Write() override;

            PackedGuid const& MoverGUID;
        };

        class MoveSetFlag final : public ServerPacket
        {
        public:
            MoveSetFlag(OpcodeServer opcode, PackedGuid const& moverGUID, uint32 sequenceIndex)
                : ServerPacket(opcode, moverGUID.size() + 4), MoverGUID(moverGUID), SequenceIndex(sequenceIndex) { }

            WorldPacket const* Write() override;

            PackedGuid const& MoverGUID;
            uint32 SequenceIndex; ///< Unit movement packet index, incremented each time
        };

        class WorldPortResponse final : public ClientPacket
        {
        public:
            WorldPortResponse(WorldPacket&& packet) : ClientPacket(MSG_MOVE_WORLDPORT_ACK, std::move(packet)) { }

            void Read() override { }
        };

        class MoveTeleport final : public ServerPacket
        {
        public:
            MoveTeleport(MovementInfo const& movementInfo) : ServerPacket(MSG_MOVE_TELEPORT_ACK, 41), Status(movementInfo) { }

            WorldPacket const* Write() override;

            MovementInfo const& Status;
            uint32 SequenceIndex = 0;
        };

        class MoveUpdateTeleport final : public ServerPacket
        {
        public:
            MoveUpdateTeleport(MovementInfo const& movementInfo) : ServerPacket(MSG_MOVE_TELEPORT, 38), Status(movementInfo) { }

            WorldPacket const* Write() override;

            MovementInfo const& Status;
        };

        class MoveTeleportAck final : public ClientPacket
        {
        public:
            MoveTeleportAck(WorldPacket&& packet) : ClientPacket(MSG_MOVE_TELEPORT_ACK, std::move(packet)) { }

            void Read() override;

            ObjectGuid MoverGUID;
            int32 AckIndex = 0;
            int32 MoveTime = 0;
        };

        struct MovementAck
        {
            MovementInfo Status;
            int32 AckIndex = 0;
        };

        class MovementAckMessage final : public ClientPacket
        {
        public:
            MovementAckMessage(WorldPacket&& packet) : ClientPacket(std::move(packet)) { }

            void Read() override;

            MovementAck Ack;
        };

        class MovementToggleAckMessage final : public ClientPacket
        {
        public:
            MovementToggleAckMessage(WorldPacket&& packet) : ClientPacket(std::move(packet)) { }

            void Read() override;

            MovementAck Ack;
            uint32 Apply;
        };

        class MovementSpeedAck final : public ClientPacket
        {
        public:
            MovementSpeedAck(WorldPacket&& packet) : ClientPacket(std::move(packet)) { }

            void Read() override;

            MovementAck Ack;
            float Speed = 0.0f;
        };

        class SetActiveMover final : public ClientPacket
        {
        public:
            SetActiveMover(WorldPacket&& packet) : ClientPacket(CMSG_SET_ACTIVE_MOVER, std::move(packet)) { }

            void Read() override;

            ObjectGuid ActiveMover;
        };

        class MoveNotActiveMover final : public ClientPacket
        {
        public:
            MoveNotActiveMover(WorldPacket&& packet) : ClientPacket(CMSG_MOVE_NOT_ACTIVE_MOVER, std::move(packet)) { }

            void Read() override;

            MovementInfo Status;
        };

        struct MoveKnockBackSpeeds
        {
            float HorzSpeed = 0.0f;
            float VertSpeed = 0.0f;
        };

        class MoveKnockBack final : public ServerPacket
        {
        public:
            MoveKnockBack(PackedGuid const& moverGUID, uint32 sequenceIndex)
                : ServerPacket(SMSG_MOVE_KNOCK_BACK, 8 + 4 + 8 + 8), MoverGUID(moverGUID), SequenceIndex(sequenceIndex) { }

            WorldPacket const* Write() override;

            PackedGuid const& MoverGUID;
            uint32 SequenceIndex = 0;
            TaggedPosition<Position::XY> Direction;
            MoveKnockBackSpeeds Speeds;
        };

        class MoveUpdateKnockBack final : public ServerPacket
        {
        public:
            MoveUpdateKnockBack() : ServerPacket(MSG_MOVE_KNOCK_BACK, 66) { }

            WorldPacket const* Write() override;

            MovementInfo Status;
            TaggedPosition<Position::XY> Direction;
            MoveKnockBackSpeeds Speeds;
        };

        class MoveKnockBackAck final : public ClientPacket
        {
        public:
            MoveKnockBackAck(WorldPacket&& packet) : ClientPacket(CMSG_MOVE_KNOCK_BACK_ACK, std::move(packet)) { }

            void Read() override;

            MovementAck Ack;
        };

        enum UpdateCollisionHeightReason : uint8
        {
            UPDATE_COLLISION_HEIGHT_SCALE = 0,
            UPDATE_COLLISION_HEIGHT_MOUNT = 1,
            UPDATE_COLLISION_HEIGHT_FORCE = 2
        };

        class MoveSetCollisionHeight final : public ServerPacket
        {
        public:
            MoveSetCollisionHeight(PackedGuid const& moverGUID, uint32 sequenceIndex, float height)
                : ServerPacket(SMSG_MOVE_SET_COLLISION_HGT, 4 + 16 + 4 + 1 + 4 + 4), MoverGUID(moverGUID), SequenceIndex(sequenceIndex), Height(height) { }

            WorldPacket const* Write() override;

            PackedGuid const& MoverGUID;
            uint32 SequenceIndex;
            float Height;
        };

        class MoveUpdateCollisionHeight final : public ServerPacket
        {
        public:
            MoveUpdateCollisionHeight() : ServerPacket(MSG_MOVE_SET_COLLISION_HGT) { }

            WorldPacket const* Write() override;

            MovementInfo Status;
            float Height = 1.0f;
        };

        class MoveSetCollisionHeightAck final : public ClientPacket
        {
        public:
            MoveSetCollisionHeightAck(WorldPacket&& packet) : ClientPacket(CMSG_MOVE_SET_COLLISION_HGT_ACK, std::move(packet)) { }

            void Read() override;

            MovementAck Data;
            float Height = 1.0f;
        };

        class MoveTimeSkipped final : public ClientPacket
        {
        public:
            MoveTimeSkipped(WorldPacket&& packet) : ClientPacket(CMSG_MOVE_TIME_SKIPPED, std::move(packet)) { }

            void Read() override;

            ObjectGuid MoverGUID;
            uint32 TimeSkipped = 0;
        };

        class SummonResponse final : public ClientPacket
        {
        public:
            SummonResponse(WorldPacket&& packet) : ClientPacket(CMSG_SUMMON_RESPONSE, std::move(packet)) { }

            void Read() override;

            ObjectGuid SummonerGUID;
            bool Accept = false;
        };

        class MoveSplineDone final : public ClientPacket
        {
        public:
            MoveSplineDone(WorldPacket&& packet) : ClientPacket(CMSG_MOVE_SPLINE_DONE, std::move(packet)) { }

            void Read() override;

            MovementInfo Status;
            int32 SplineID = 0;
        };

        class SummonRequest final : public ServerPacket
        {
        public:
            SummonRequest() : ServerPacket(SMSG_SUMMON_REQUEST, 8 + 4 + 4) { }

            WorldPacket const* Write() override;

            ObjectGuid SummonerGUID;
            int32 AreaID = 0;
            uint32 TimeLimit = 0;
        };
    }
}

// these do not read/write guid as it can be out of sequence in various packets
ByteBuffer& operator >> (ByteBuffer& data, MovementInfo& movementInfo);
ByteBuffer& operator<<(ByteBuffer& data, MovementInfo const& movementInfo);

#endif // MovementPackets_h__
