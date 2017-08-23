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

#include "MovementPackets.h"
#include "UnitDefines.h"

ByteBuffer& operator<<(ByteBuffer& data, MovementInfo const& movementInfo)
{
    data << uint32(movementInfo.flags);
    data << uint16(movementInfo.flags2);
    data << uint32(movementInfo.time);
    data << TaggedPosition<Position::XYZO>(movementInfo.pos);

    if (movementInfo.HasMovementFlag(MOVEMENTFLAG_ONTRANSPORT))
    {
        data << movementInfo.transport.guid.WriteAsPacked();
        data << TaggedPosition<Position::XYZO>(movementInfo.transport.pos);
        data << uint32(movementInfo.transport.time);
        data << int8(movementInfo.transport.seat);

        if (movementInfo.HasExtraMovementFlag(MOVEMENTFLAG2_INTERPOLATED_MOVEMENT))
            data << uint32(movementInfo.transport.time2);
    }

    if (movementInfo.HasMovementFlag(MovementFlags(MOVEMENTFLAG_SWIMMING | MOVEMENTFLAG_FLYING)) || movementInfo.HasExtraMovementFlag(MOVEMENTFLAG2_ALWAYS_ALLOW_PITCHING))
        data << float(movementInfo.pitch);

    data << uint32(movementInfo.fallTime);

    if (movementInfo.HasMovementFlag(MOVEMENTFLAG_FALLING))
    {
        data << float(movementInfo.jump.zspeed);
        data << float(movementInfo.jump.cosAngle);
        data << float(movementInfo.jump.sinAngle);
        data << float(movementInfo.jump.xyspeed);
    }

    if (movementInfo.HasMovementFlag(MOVEMENTFLAG_SPLINE_ELEVATION))
        data << float(movementInfo.splineElevation);

    return data;
}

ByteBuffer& operator >> (ByteBuffer& data, MovementInfo& movementInfo)
{
    data >> movementInfo.flags;
    data >> movementInfo.flags2;
    data >> movementInfo.time;
    data >> movementInfo.pos.PositionXYZOStream();

    if (movementInfo.HasMovementFlag(MOVEMENTFLAG_ONTRANSPORT))
    {
        data >> movementInfo.transport.guid.ReadAsPacked();
        data >> movementInfo.transport.pos.PositionXYZOStream();
        data >> movementInfo.transport.time;
        data >> movementInfo.transport.seat;

        if (movementInfo.HasExtraMovementFlag(MOVEMENTFLAG2_INTERPOLATED_MOVEMENT))
            data >> movementInfo.transport.time2;
    }

    if (movementInfo.HasMovementFlag(MovementFlags(MOVEMENTFLAG_SWIMMING | MOVEMENTFLAG_FLYING)) || movementInfo.HasExtraMovementFlag(MOVEMENTFLAG2_ALWAYS_ALLOW_PITCHING))
        data >> movementInfo.pitch;

    data >> movementInfo.fallTime;

    if (movementInfo.HasMovementFlag(MOVEMENTFLAG_FALLING))
    {
        data >> movementInfo.jump.zspeed;
        data >> movementInfo.jump.cosAngle;
        data >> movementInfo.jump.sinAngle;
        data >> movementInfo.jump.xyspeed;
    }

    if (movementInfo.HasMovementFlag(MOVEMENTFLAG_SPLINE_ELEVATION))
        data >> movementInfo.splineElevation;

    return data;
}

void WorldPackets::Movement::ClientPlayerMovement::Read()
{
    _worldPacket >> Status.guid.ReadAsPacked();
    _worldPacket >> Status;
}

WorldPacket const* WorldPackets::Movement::MoveUpdate::Write()
{
    _worldPacket << Status.guid.WriteAsPacked();
    _worldPacket << Status;

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Movement::MoveSplineSetSpeed::Write()
{
    _worldPacket << MoverGUID;
    _worldPacket << float(Speed);

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Movement::MoveSetSpeed::Write()
{
    _worldPacket << MoverGUID;
    _worldPacket << uint32(SequenceIndex);
    if (GetOpcode() == SMSG_FORCE_RUN_SPEED_CHANGE)
        _worldPacket << uint8(WriteLastClickToMoveSpeed);

    _worldPacket << float(Speed);

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Movement::MoveUpdateSpeed::Write()
{
    _worldPacket << Status.guid.WriteAsPacked();
    _worldPacket << Status;
    _worldPacket << float(Speed);

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Movement::MoveSplineSetFlag::Write()
{
    _worldPacket << MoverGUID;

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Movement::MoveSetFlag::Write()
{
    _worldPacket << MoverGUID;
    _worldPacket << uint32(SequenceIndex);

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Movement::MoveTeleport::Write()
{
    _worldPacket << Status.guid.WriteAsPacked();
    _worldPacket << uint32(SequenceIndex);
    _worldPacket << Status;

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Movement::MoveUpdateTeleport::Write()
{
    _worldPacket << Status.guid.WriteAsPacked();
    _worldPacket << Status;

    return &_worldPacket;
}

void WorldPackets::Movement::MoveTeleportAck::Read()
{
    _worldPacket >> MoverGUID.ReadAsPacked();
    _worldPacket >> AckIndex;
    _worldPacket >> MoveTime;
}

ByteBuffer& operator >> (ByteBuffer& data, WorldPackets::Movement::MovementAck& ack)
{
    data >> ack.Status.guid.ReadAsPacked();
    data >> ack.AckIndex;
    data >> ack.Status;
    return data;
}

void WorldPackets::Movement::MovementAckMessage::Read()
{
    _worldPacket >> Ack;
}

void WorldPackets::Movement::MovementToggleAckMessage::Read()
{
    _worldPacket >> Ack;
    _worldPacket >> Apply;
}

void WorldPackets::Movement::MovementSpeedAck::Read()
{
    _worldPacket >> Ack;
    _worldPacket >> Speed;
}

void WorldPackets::Movement::SetActiveMover::Read()
{
    _worldPacket >> ActiveMover;
}

void WorldPackets::Movement::MoveNotActiveMover::Read()
{
    _worldPacket >> Status.guid.ReadAsPacked();
    _worldPacket >> Status;
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::Movement::MoveKnockBackSpeeds const& speeds)
{
    data << float(speeds.HorzSpeed);
    data << float(speeds.VertSpeed);

    return data;
}

WorldPacket const* WorldPackets::Movement::MoveKnockBack::Write()
{
    _worldPacket << MoverGUID;
    _worldPacket << uint32(SequenceIndex);
    _worldPacket << Direction;
    _worldPacket << Speeds;

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Movement::MoveUpdateKnockBack::Write()
{
    _worldPacket << Status.guid.WriteAsPacked();
    _worldPacket << Status;
    _worldPacket << Direction;
    _worldPacket << Speeds;

    return &_worldPacket;
}

void WorldPackets::Movement::MoveKnockBackAck::Read()
{
    _worldPacket >> Ack;
}

WorldPacket const* WorldPackets::Movement::MoveSetCollisionHeight::Write()
{
    _worldPacket << MoverGUID;
    _worldPacket << uint32(SequenceIndex);
    _worldPacket << float(Height);

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Movement::MoveUpdateCollisionHeight::Write()
{
    _worldPacket << Status.guid.WriteAsPacked();
    _worldPacket << Status;
    _worldPacket << float(Height);

    return &_worldPacket;
}

void WorldPackets::Movement::MoveSetCollisionHeightAck::Read()
{
    _worldPacket >> Data;
    _worldPacket >> Height;
}

void WorldPackets::Movement::MoveTimeSkipped::Read()
{
    _worldPacket >> MoverGUID.ReadAsPacked();
    _worldPacket >> TimeSkipped;
}

void WorldPackets::Movement::SummonResponse::Read()
{
    _worldPacket >> SummonerGUID;
    _worldPacket >> Accept;
}

void WorldPackets::Movement::MoveSplineDone::Read()
{
    _worldPacket >> Status.guid.ReadAsPacked();
    _worldPacket >> Status;
    _worldPacket >> SplineID;
}

WorldPacket const* WorldPackets::Movement::SummonRequest::Write()
{
    _worldPacket << SummonerGUID;
    _worldPacket << int32(AreaID);
    _worldPacket << uint32(TimeLimit);

    return &_worldPacket;
}
