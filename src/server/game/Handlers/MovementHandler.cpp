/*
 * Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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


#include "Battlefield.h"
#include "BattlefieldMgr.h"
#include "BattlefieldWG.h"
#include "Battleground.h"
#include "Common.h"
#include "Corpse.h"
#include "Creature.h"
#include "GameTime.h"
#include "InstanceSaveMgr.h"
#include "Language.h"
#include "Log.h"
#include "MapManager.h"
#include "MovementPacketSender.h"
#include "MovementPackets.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "Player.h"
#include "Pet.h"
#include "RBAC.h"
#include "Transport.h"
#include "Vehicle.h"
#include "WaypointMovementGenerator.h"
#include "WorldSession.h"

void WorldSession::HandleMoveWorldportAckOpcode(WorldPackets::Movement::WorldPortResponse& /*packet*/)
{
    HandleMoveWorldportAck();
}

void WorldSession::HandleMoveWorldportAck()
{
    // ignore unexpected far teleports
    if (!GetPlayer()->IsBeingTeleportedFar())
        return;

    GetPlayer()->SetSemaphoreTeleportFar(false);

    // get the teleport destination
    WorldLocation const& loc = GetPlayer()->GetTeleportDest();

    // possible errors in the coordinate validity check
    if (!MapManager::IsValidMapCoord(loc))
    {
        LogoutPlayer(false);
        return;
    }

    // get the destination map entry, not the current one, this will fix homebind and reset greeting
    MapEntry const* mEntry = sMapStore.LookupEntry(loc.GetMapId());
    InstanceTemplate const* mInstance = sObjectMgr->GetInstanceTemplate(loc.GetMapId());

    // reset instance validity, except if going to an instance inside an instance
    if (GetPlayer()->m_InstanceValid == false && !mInstance)
        GetPlayer()->m_InstanceValid = true;

    Map* oldMap = GetPlayer()->GetMap();
    Map* newMap = sMapMgr->CreateMap(loc.GetMapId(), GetPlayer());

    if (GetPlayer()->IsInWorld())
    {
        TC_LOG_ERROR("network", "%s %s is still in world when teleported from map %s (%u) to new map %s (%u)", GetPlayer()->GetGUID().ToString().c_str(), GetPlayer()->GetName().c_str(), oldMap->GetMapName(), oldMap->GetId(), newMap ? newMap->GetMapName() : "Unknown", loc.GetMapId());
        oldMap->RemovePlayerFromMap(GetPlayer(), false);
    }

    // relocate the player to the teleport destination
    // the CannotEnter checks are done in TeleporTo but conditions may change
    // while the player is in transit, for example the map may get full
    if (!newMap || newMap->CannotEnter(GetPlayer()))
    {
        TC_LOG_ERROR("network", "Map %d (%s) could not be created for player %d (%s), porting player to homebind", loc.GetMapId(), newMap ? newMap->GetMapName() : "Unknown", GetPlayer()->GetGUID().GetCounter(), GetPlayer()->GetName().c_str());
        GetPlayer()->TeleportTo(GetPlayer()->m_homebindMapId, GetPlayer()->m_homebindX, GetPlayer()->m_homebindY, GetPlayer()->m_homebindZ, GetPlayer()->GetOrientation());
        return;
    }

    GetPlayer()->Relocate(loc.GetPositionX(), loc.GetPositionY(), loc.GetPositionZ(), loc.GetOrientation());
    GetPlayer()->SetFallInformation(0, GetPlayer()->GetPositionZ());
    GetPlayer()->ResetMap();
    GetPlayer()->SetMap(newMap);
    GetPlayer()->SendInitialPacketsBeforeAddToMap();

    if (!GetPlayer()->GetMap()->AddPlayerToMap(GetPlayer()))
    {
        TC_LOG_ERROR("network", "WORLD: failed to teleport player %s (%d) to map %d (%s) because of unknown reason!",
            GetPlayer()->GetName().c_str(), GetPlayer()->GetGUID().GetCounter(), loc.GetMapId(), newMap ? newMap->GetMapName() : "Unknown");
        GetPlayer()->ResetMap();
        GetPlayer()->SetMap(oldMap);
        GetPlayer()->TeleportTo(GetPlayer()->m_homebindMapId, GetPlayer()->m_homebindX, GetPlayer()->m_homebindY, GetPlayer()->m_homebindZ, GetPlayer()->GetOrientation());
        return;
    }

    // battleground state prepare (in case join to BG), at relogin/tele player not invited
    // only add to bg group and object, if the player was invited (else he entered through command)
    if (_player->InBattleground())
    {
        // cleanup setting if outdated
        if (!mEntry->IsBattlegroundOrArena())
        {
            // We're not in BG
            _player->SetBattlegroundId(0, BATTLEGROUND_TYPE_NONE);
            // reset destination bg team
            _player->SetBGTeam(0);
        }
        // join to bg case
        else if (Battleground* bg = _player->GetBattleground())
        {
            if (_player->IsInvitedForBattlegroundInstance(_player->GetBattlegroundId()))
                bg->AddPlayer(_player);
        }
    }

    GetPlayer()->SendInitialPacketsAfterAddToMap();

    // resurrect character at enter into instance where his corpse exist after add to map

    if (mEntry->IsDungeon() && !GetPlayer()->IsAlive())
    {
        if (GetPlayer()->GetCorpseLocation().GetMapId() == mEntry->MapID)
        {
            GetPlayer()->ResurrectPlayer(0.5f, false);
            GetPlayer()->SpawnCorpseBones();
        }
    }

    bool allowMount = !mEntry->IsDungeon() || mEntry->IsBattlegroundOrArena();
    if (mInstance)
    {
        // check if this instance has a reset time and send it to player if so
        Difficulty diff = GetPlayer()->GetDifficulty(mEntry->IsRaid());
        if (MapDifficulty const* mapDiff = GetMapDifficultyData(mEntry->MapID, diff))
        {
            if (mapDiff->resetTime)
            {
                if (time_t timeReset = sInstanceSaveMgr->GetResetTimeFor(mEntry->MapID, diff))
                {
                    uint32 timeleft = uint32(timeReset - time(nullptr));
                    GetPlayer()->SendInstanceResetWarning(mEntry->MapID, diff, timeleft, true);
                }
            }
        }

        // check if instance is valid
        if (!GetPlayer()->CheckInstanceValidity(false))
            GetPlayer()->m_InstanceValid = false;

        // instance mounting is handled in InstanceTemplate
        allowMount = mInstance->AllowMount;
    }

    // mount allow check
    if (!allowMount)
        _player->RemoveAurasByType(SPELL_AURA_MOUNTED);

    // update zone immediately, otherwise leave channel will cause crash in mtmap
    uint32 newzone, newarea;
    GetPlayer()->GetZoneAndAreaId(newzone, newarea);
    GetPlayer()->UpdateZone(newzone, newarea);

    bool InBattlefield = false;
    if (loc.GetMapId() == MAPID_WINTERGRASP && newzone == ZONEID_WINTERGRASP)
    {
        if (Battlefield* battlefield = sBattlefieldMgr->GetEnabledBattlefield(newzone))
        {
            if (battlefield->IsWarTime())
                _player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            InBattlefield = true;
        }
    }
    
    // flight fast teleport case
    if (GetPlayer()->IsInFlight())
    {
        if (!_player->InBattleground() && !InBattlefield)
        {
            // short preparations to continue flight
            if (MovementGenerator* flight = GetPlayer()->GetMotionMaster()->GetMotionSlot(MOTION_SLOT_CONTROLLED))
                flight->Initialize(GetPlayer());
            return;
        }
        
        // stop flight
        GetPlayer()->GetMotionMaster()->Clear(MOTION_SLOT_CONTROLLED);
        GetPlayer()->CleanupAfterTaxiFlight();
    }

    // honorless target
    if (GetPlayer()->pvpInfo.IsHostile)
        GetPlayer()->CastSpell(GetPlayer(), 2479, true);

    // in friendly area
    else if (GetPlayer()->IsPvP() && !GetPlayer()->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_IN_PVP))
        GetPlayer()->UpdatePvP(false, false);

    // resummon pet
    GetPlayer()->ResummonPetTemporaryUnSummonedIfAny();

    //lets process all delayed operations on successful teleport
    GetPlayer()->ProcessDelayedOperations();
}

void WorldSession::HandleMoveTeleportAck(WorldPackets::Movement::MoveTeleportAck& packet)
{
    TC_LOG_DEBUG("network", "CMSG_MOVE_TELEPORT_ACK: Guid: %s, Sequence: %u, Time: %u", packet.MoverGUID.ToString().c_str(), packet.AckIndex, packet.MoveTime);

    Unit* mover = _player->GetUnitBeingMoved();
    ASSERT(mover);

    // now can skip not our packet
    if (mover->GetGUID() != packet.MoverGUID)
        return;

    // verify that indeed the client is replying with the changes that were send to him
    if (!mover->HasPendingMovementChange())
    {
        TC_LOG_INFO("cheat", "WorldSession::HandleMoveTeleportAck: Player %s from account id %u kicked because no movement change ack was expected from this player",
            _player->GetName().c_str(), _player->GetSession()->GetAccountId());
        _player->GetSession()->KickPlayer();
        return;
    }

    PlayerMovementPendingChange pendingChange = mover->PopPendingMovementChange();
    if (pendingChange.movementCounter != packet.AckIndex || pendingChange.movementChangeType != TELEPORT)
    {
        TC_LOG_INFO("cheat", "WorldSession::HandleMoveTeleportAck: Player %s from account id %u kicked for incorrect data returned in an ack",
            _player->GetName().c_str(), _player->GetSession()->GetAccountId());
        _player->GetSession()->KickPlayer();
        return;
    }

    Player* plMover = _player->m_unitMovedByMe->ToPlayer();

    if (!plMover || !plMover->IsBeingTeleportedNear())
        return;

    plMover->SetSemaphoreTeleportNear(false);

    WorldLocation const& dest = plMover->GetTeleportDest();
    // now that it has been acknowledge, we can inform the observers of that teleport
    MovementInfo movementInfo = plMover->GetMovementInfo();
    movementInfo.pos.Relocate(dest);
    if (TransportBase* transportBase = plMover->GetDirectTransport())
    {
        float x, y, z, o;
        dest.GetPosition(x, y, z, o);
        transportBase->CalculatePassengerOffset(x, y, z, &o);
        movementInfo.transport.pos.Relocate(x, y, z, o);
    }
    MovementPacketSender::SendTeleportPacket(plMover, movementInfo);

    uint32 old_zone = plMover->GetZoneId();

    plMover->UpdatePosition(dest, true);
    plMover->SetFallInformation(0, GetPlayer()->GetPositionZ());

    uint32 newzone, newarea;
    plMover->GetZoneAndAreaId(newzone, newarea);
    plMover->UpdateZone(newzone, newarea);

    // new zone
    if (old_zone != newzone)
    {
        // honorless target
        if (plMover->pvpInfo.IsHostile)
            plMover->CastSpell(plMover, 2479, true);

        // in friendly area
        else if (plMover->IsPvP() && !plMover->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_IN_PVP))
            plMover->UpdatePvP(false, false);
    }

    // resummon pet
    GetPlayer()->ResummonPetTemporaryUnSummonedIfAny();

    //lets process all delayed operations on successful teleport
    GetPlayer()->ProcessDelayedOperations();
}

/*
These packets are sent by the client in order to transmit the movement of the character currently controlled by the client.
This character is usually the player but it can be a creature (in case of a possess (eg priest MC)) or a vehicle. Later in this handler explaination,
'player' will be used when 'player controlled unit' should have been used.
The server then retransmits these packets to the other clients, which will extrapolate the unit's motion.
All the server has to do with all these packets is:
1) validate & update the data received: position, orientation, fall data and movement flags (this list should be exhaustive. please update if there is something missing).
2) transmit this packet to the other players nearby
Handles:
MSG_MOVE_START_FORWARD
MSG_MOVE_START_BACKWARD
MSG_MOVE_STOP
MSG_MOVE_START_STRAFE_LEFT
MSG_MOVE_START_STRAFE_RIGHT
MSG_MOVE_STOP_STRAFE
MSG_MOVE_JUMP
MSG_MOVE_START_TURN_LEFT
MSG_MOVE_START_TURN_RIGHT
MSG_MOVE_STOP_TURN
MSG_MOVE_START_PITCH_UP
MSG_MOVE_START_PITCH_DOWN
MSG_MOVE_STOP_PITCH
MSG_MOVE_SET_RUN_MODE
MSG_MOVE_SET_WALK_MODE
MSG_MOVE_FALL_LAND
MSG_MOVE_START_SWIM
MSG_MOVE_STOP_SWIM
MSG_MOVE_SET_FACING
MSG_MOVE_SET_PITCH
MSG_MOVE_HEARTBEAT -- packet sent every 0.5 s when the player is moving.
MSG_MOVE_START_ASCEND
MSG_MOVE_STOP_ASCEND
MSG_MOVE_START_DESCEND
CMSG_MOVE_FALL_RESET -- the player has encounter an object while failing, thus modifing the trajectory of his fall. this packet gives info regarding the new trajectory. !!!! @todo: needs to be processed in a different handler and this opcode shouldn'nt be sent to other clients !!!!
CMSG_MOVE_SET_FLY -- the player has started or stopped to fly (toggle effect). !!!! @todo: needs to be processed in a different handler and this opcode shouldn'nt be sent to other clients !!!!
CMSG_MOVE_CHNG_TRANSPORT !!!! @todo: needs to be processed in a different handler and this opcode shouldn'nt be sent to other clients !!!!
*/
void WorldSession::HandleMovementOpcodes(WorldPackets::Movement::ClientPlayerMovement& packet)
{
    HandleMovementOpcode(packet.GetOpcode(), packet.Status);
}

void WorldSession::HandleMovementOpcode(Opcodes opcode, MovementInfo& movementInfo, std::size_t reserve)
{
    Unit* mover = _player->GetUnitBeingMoved();
    Player* plrMover = mover->ToPlayer();
    Pet* petMover = nullptr;
    Creature* crMover = nullptr;
    if (plrMover->GetPet())
        petMover = plrMover->GetPet();
    if (petMover && petMover->ToCreature())
        crMover = petMover->ToCreature();

    ASSERT(mover != nullptr);                      // there must always be a mover

                                                   // ignore movement packets if the player is getting far teleported (change of map). keep processing movement packets when the unit is only doing a near teleport.
    if (plrMover && plrMover->IsBeingTeleportedFar())
        return;

    // prevent tampered movement data
    if (movementInfo.guid != mover->GetGUID())
        return;

    if (!movementInfo.pos.IsPositionValid())
        return;

    /* validate new movement packet */
    mover->ValidateMovementInfo(&movementInfo);

    /* handle special cases */
    if (movementInfo.HasMovementFlag(MOVEMENTFLAG_ONTRANSPORT)) // @todo: move this stuff. CMSG_MOVE_CHNG_TRANSPORT should be handled elsewhere than here.
    {
        // We were teleported, skip packets that were broadcast before teleport
        if (movementInfo.pos.GetExactDist2d(mover) > SIZE_OF_GRIDS)
            return;

        // transports size limited
        // (also received at zeppelin leave by some reason with t_* as absolute in continent coordinates, can be safely skipped)
        if (fabs(movementInfo.transport.pos.GetPositionX()) > 75.0f || fabs(movementInfo.transport.pos.GetPositionY()) > 75.0f || fabs(movementInfo.transport.pos.GetPositionZ()) > 75.0f)
            return;

        if (!Trinity::IsValidMapCoord(movementInfo.pos.GetPositionX() + movementInfo.transport.pos.GetPositionX(), movementInfo.pos.GetPositionY() + movementInfo.transport.pos.GetPositionY(),
            movementInfo.pos.GetPositionZ() + movementInfo.transport.pos.GetPositionZ(), movementInfo.pos.GetOrientation() + movementInfo.transport.pos.GetOrientation()))
            return;

        // if we boarded a transport, add us to it
        if (plrMover)
        {
            if (!plrMover->GetTransport())
            {
                if (Transport* transport = plrMover->GetMap()->GetTransport(movementInfo.transport.guid))
                {
                    transport->AddPassenger(plrMover);
                    if (petMover && crMover && !transport->isPassenger(crMover))
                        transport->AddPassenger(crMover);
                }
            }
            else if (plrMover->GetTransport()->GetGUID() != movementInfo.transport.guid)
            {
                plrMover->GetTransport()->RemovePassenger(plrMover);
                if (Transport* transport = plrMover->GetMap()->GetTransport(movementInfo.transport.guid))
                {
                    transport->AddPassenger(plrMover);
                    if (petMover && crMover && !transport->isPassenger(crMover))
                        transport->AddPassenger(crMover);
                }
                else
                    movementInfo.transport.Reset();
            }
        }

        if (!mover->GetTransport() && !mover->GetVehicle())
        {
            GameObject* go = mover->GetMap()->GetGameObject(movementInfo.transport.guid);
            if (!go || go->GetGoType() != GAMEOBJECT_TYPE_TRANSPORT)
                movementInfo.RemoveMovementFlag(MOVEMENTFLAG_ONTRANSPORT);
        }
    }
    else if (plrMover && plrMover->GetTransport())                // if we were on a transport, leave
    {
        plrMover->GetTransport()->RemovePassenger(plrMover);
        if (petMover && crMover && crMover->GetTransport() && crMover->GetTransport()->isPassenger(crMover))
            crMover->GetTransport()->RemovePassenger(crMover);
        movementInfo.transport.Reset();
    }

    // So the PetAI will function properly
    if (petMover)
        petMover->GetCharmInfo()->SetIsOnTransport(plrMover->HasUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT));

    // fall damage generation (ignore in flight case that can be triggered also at lags in moment teleportation to another map).
    if (opcode == MSG_MOVE_FALL_LAND && plrMover && !plrMover->IsInFlight())
        plrMover->HandleFall(movementInfo);

    // interrupt parachutes upon falling or landing in water
    if (opcode == MSG_MOVE_FALL_LAND || opcode == MSG_MOVE_START_SWIM)
        mover->RemoveAurasWithInterruptFlags(AURA_INTERRUPT_FLAG_LANDING); // Parachutes

    if (plrMover && ((movementInfo.flags & MOVEMENTFLAG_SWIMMING) != 0) != plrMover->IsInWater())
    {
        // now client not include swimming flag in case jumping under water
        plrMover->SetInWater(!plrMover->IsInWater() || plrMover->GetBaseMap()->IsUnderWater(movementInfo.pos.GetPositionX(), movementInfo.pos.GetPositionY(), movementInfo.pos.GetPositionZ()));
    }

    /* process position-change */
    mover->UpdateMovementInfo(movementInfo);

    // as strange as it may be, retail servers actually use MSG_MOVE_START_SWIM_CHEAT & MSG_MOVE_STOP_SWIM_CHEAT to respectively set and unset the 'Flying' movement flag.
    // The only thing left to do is to move the handling of CMSG_MOVE_SET_FLY into a different handler
    if (opcode == CMSG_MOVE_SET_FLY)
        opcode = movementInfo.HasMovementFlag(MOVEMENTFLAG_FLYING) ? MSG_MOVE_START_SWIM_CHEAT : MSG_MOVE_STOP_SWIM_CHEAT;

    WorldPackets::Movement::MoveUpdate moveUpdate(opcode, reserve);
    moveUpdate.Status = mover->GetMovementInfo();
    mover->SendMessageToSet(moveUpdate.Write(), _player);

    // Some vehicles allow the passenger to turn by himself
    if (Vehicle* vehicle = mover->GetVehicle())
    {
        if (VehicleSeatEntry const* seat = vehicle->GetSeatForPassenger(mover))
        {
            if (seat->m_flags & VEHICLE_SEAT_FLAG_ALLOW_TURNING)
            {
                if (movementInfo.pos.GetOrientation() != mover->GetOrientation())
                {
                    mover->SetOrientation(movementInfo.pos.GetOrientation());
                    mover->RemoveAurasWithInterruptFlags(AURA_INTERRUPT_FLAG_TURNING);
                }
            }
        }
        return;
    }

    mover->UpdatePosition(movementInfo.pos); // unsure if this can be safely deleted since it is also called in "mover->UpdateMovementInfo(movementInfo)" but the above if blocks may influence the unit's orintation

    if (plrMover)                                            // nothing is charmed, or player charmed
    {
        if (plrMover->IsSitState() && (movementInfo.flags & (MOVEMENTFLAG_MASK_MOVING | MOVEMENTFLAG_MASK_TURNING)))
            plrMover->SetStandState(UNIT_STAND_STATE_STAND);

        plrMover->UpdateFallInformationIfNeed(movementInfo, opcode);

        if (movementInfo.pos.GetPositionZ() < plrMover->GetMap()->GetMinHeight(movementInfo.pos.GetPositionX(), movementInfo.pos.GetPositionY()))
        {
            if (!(plrMover->GetBattleground() && plrMover->GetBattleground()->HandlePlayerUnderMap(_player)))
            {
                // NOTE: this is actually called many times while falling
                // even after the player has been teleported away
                /// @todo discard movement packets after the player is rooted
                if (plrMover->IsAlive())
                {
                    plrMover->SetFlag(PLAYER_FLAGS, PLAYER_FLAGS_IS_OUT_OF_BOUNDS);
                    plrMover->EnvironmentalDamage(DAMAGE_FALL_TO_VOID, GetPlayer()->GetMaxHealth());
                    // player can be alive if GM/etc
                    // change the death state to CORPSE to prevent the death timer from
                    // starting in the next player update
                    if (plrMover->IsAlive())
                        plrMover->KillPlayer();
                }
            }
        }
    }
}

void WorldSession::HandleForceSpeedChangeAck(WorldPackets::Movement::MovementSpeedAck& packet)
{
    Unit* mover = _player->GetUnitBeingMoved();
    ASSERT(mover);

    // now can skip not our packet
    if (mover->GetGUID() != packet.Ack.Status.guid)
        return;

    UnitMoveType move_type;
    switch (packet.GetOpcode())
    {
    case CMSG_FORCE_WALK_SPEED_CHANGE_ACK:          move_type = MOVE_WALK;          break;
    case CMSG_FORCE_RUN_SPEED_CHANGE_ACK:           move_type = MOVE_RUN;           break;
    case CMSG_FORCE_RUN_BACK_SPEED_CHANGE_ACK:      move_type = MOVE_RUN_BACK;      break;
    case CMSG_FORCE_SWIM_SPEED_CHANGE_ACK:          move_type = MOVE_SWIM;          break;
    case CMSG_FORCE_SWIM_BACK_SPEED_CHANGE_ACK:     move_type = MOVE_SWIM_BACK;     break;
    case CMSG_FORCE_TURN_RATE_CHANGE_ACK:           move_type = MOVE_TURN_RATE;     break;
    case CMSG_FORCE_FLIGHT_SPEED_CHANGE_ACK:        move_type = MOVE_FLIGHT;        break;
    case CMSG_FORCE_FLIGHT_BACK_SPEED_CHANGE_ACK:   move_type = MOVE_FLIGHT_BACK;   break;
    case CMSG_FORCE_PITCH_RATE_CHANGE_ACK:          move_type = MOVE_PITCH_RATE;    break;
    default:
        TC_LOG_ERROR("network", "WorldSession::HandleForceSpeedChangeAck: Unknown move type opcode: %s", GetOpcodeNameForLogging(packet.GetOpcode()));
        return;
    }

    // verify that indeed the client is replying with the changes that were send to him
    if (!mover->HasPendingMovementChange())
    {
        TC_LOG_INFO("cheat", "WorldSession::HandleForceSpeedChangeAck: Player %s from account id %u kicked because no movement change ack was expected from this player",
            _player->GetName().c_str(), _player->GetSession()->GetAccountId());
        _player->GetSession()->KickPlayer();
        return;
    }

    PlayerMovementPendingChange pendingChange = mover->PopPendingMovementChange();
    float speedSent = pendingChange.newValue;
    MovementChangeType changeType = pendingChange.movementChangeType;
    UnitMoveType moveTypeSent;
    switch (changeType)
    {
    case SPEED_CHANGE_WALK:                 moveTypeSent = MOVE_WALK; break;
    case SPEED_CHANGE_RUN:                  moveTypeSent = MOVE_RUN; break;
    case SPEED_CHANGE_RUN_BACK:             moveTypeSent = MOVE_RUN_BACK; break;
    case SPEED_CHANGE_SWIM:                 moveTypeSent = MOVE_SWIM; break;
    case SPEED_CHANGE_SWIM_BACK:            moveTypeSent = MOVE_SWIM_BACK; break;
    case RATE_CHANGE_TURN:                  moveTypeSent = MOVE_TURN_RATE; break;
    case SPEED_CHANGE_FLIGHT_SPEED:         moveTypeSent = MOVE_FLIGHT; break;
    case SPEED_CHANGE_FLIGHT_BACK_SPEED:    moveTypeSent = MOVE_FLIGHT_BACK; break;
    case RATE_CHANGE_PITCH:                 moveTypeSent = MOVE_PITCH_RATE; break;
    default:
        TC_LOG_INFO("cheat", "WorldSession::HandleForceSpeedChangeAck: Player %s from account id %u kicked for incorrect data returned in an ack",
            _player->GetName().c_str(), _player->GetSession()->GetAccountId());
        _player->GetSession()->KickPlayer();
        return;
    }

    if (pendingChange.movementCounter != packet.Ack.AckIndex || std::fabs(speedSent - packet.Speed) > 0.01f || moveTypeSent != move_type)
    {
        TC_LOG_INFO("cheat", "WorldSession::HandleForceSpeedChangeAck: Player %s from account id %u kicked for incorrect data returned in an ack",
            _player->GetName().c_str(), _player->GetSession()->GetAccountId());
        _player->GetSession()->KickPlayer();
        return;
    }

    /* the client data has been verified. let's do the actual change now */
    float newSpeedRate = speedSent / (mover->IsControlledByPlayer() ? playerBaseMoveSpeed[move_type] : baseMoveSpeed[move_type]); // is it sure that IsControlledByPlayer() should be used?
    mover->UpdateMovementInfo(packet.Ack.Status);
    mover->SetSpeedRateReal(move_type, newSpeedRate);
    MovementPacketSender::SendSpeedChangeToObservers(mover, move_type, speedSent);
}

void WorldSession::HandleCollisionHeightChangeAck(WorldPackets::Movement::MoveSetCollisionHeightAck& setCollisionHeightAck)
{
    Unit* mover = _player->GetUnitBeingMoved();
    ASSERT(mover);

    // now can skip not our packet
    if (mover->GetGUID() != setCollisionHeightAck.Data.Status.guid) // @todo: potential hack attempt. use disciplinary measure?
        return;

    // verify that indeed the client is replying with the changes that were send to him
    if (!mover->HasPendingMovementChange())
    {
        TC_LOG_INFO("cheat", "WorldSession::HandleCollisionHeightChangeAck: Player %s from account id %u kicked because no movement change ack was expected from this player",
            _player->GetName().c_str(), _player->GetSession()->GetAccountId());
        _player->GetSession()->KickPlayer();
        return;
    }

    PlayerMovementPendingChange pendingChange = mover->PopPendingMovementChange();
    float heightSent = pendingChange.newValue;
    MovementChangeType changeType = pendingChange.movementChangeType;

    if (pendingChange.movementCounter != setCollisionHeightAck.Data.AckIndex || changeType != SET_COLLISION_HGT || std::fabs(heightSent - setCollisionHeightAck.Height) > 0.01f)
    {
        TC_LOG_INFO("cheat", "WorldSession::HandleCollisionHeightChangeAck: Player %s from account id %u kicked for incorrect data returned in an ack",
            _player->GetName().c_str(), _player->GetSession()->GetAccountId());
        _player->GetSession()->KickPlayer();
        return;
    }

    mover->ValidateMovementInfo(&setCollisionHeightAck.Data.Status);
    /* the client data has been verified. let's do the actual change now */
    mover->UpdateMovementInfo(setCollisionHeightAck.Data.Status);
    mover->SetCollisionHeightReal(heightSent);
    MovementPacketSender::SendHeightChangeToObservers(mover, heightSent);
}

void WorldSession::HandleSetActiveMoverOpcode(WorldPackets::Movement::SetActiveMover& packet)
{
    if (GetPlayer()->IsInWorld())
        if (_player->m_unitMovedByMe->GetGUID() != packet.ActiveMover)
            TC_LOG_DEBUG("network", "HandleSetActiveMoverOpcode: incorrect mover guid: mover is %s and should be %s", packet.ActiveMover.ToString().c_str(), _player->m_unitMovedByMe->GetGUID().ToString().c_str());

    // !!! @todo: call transfer of 'mover' code !!!
}

void WorldSession::HandleMoveNotActiveMover(WorldPackets::Movement::MoveNotActiveMover& moveNotActiveMover)
{
    Unit* mover = _player->GetUnitBeingMoved();
    ASSERT(mover);

    // check whether or not the player had control of the unit mentioned in the MovementInfo
    if (mover->GetGUID() != moveNotActiveMover.Status.guid) // @todo: potential hack attempt. use disciplinary measure?
        return;

    mover->ValidateMovementInfo(&moveNotActiveMover.Status);
    mover->UpdateMovementInfo(moveNotActiveMover.Status);

    // !!! @todo: call transfer of 'mover' code (which is the main purpose of this packet) !!!
}

void WorldSession::HandleMountSpecialAnimOpcode(WorldPacket& /*recvData*/)
{
    WorldPacket data(SMSG_MOUNTSPECIAL_ANIM, 8);
    data << uint64(GetPlayer()->GetGUID());

    GetPlayer()->SendMessageToSet(&data, false);
}

void WorldSession::HandleMoveKnockBackAck(WorldPackets::Movement::MoveKnockBackAck& movementAck)
{
    Unit* mover = _player->GetUnitBeingMoved();
    ASSERT(mover);

    // now can skip not our packet
    if (mover->GetGUID() != movementAck.Ack.Status.guid) // @todo: potential hack attempt. use disciplinary measure?
        return;

    // verify that indeed the client is replying with the changes that were send to him
    if (!mover->HasPendingMovementChange())
    {
        TC_LOG_INFO("cheat", "WorldSession::HandleMoveKnockBackAck: Player %s from account id %u kicked because no movement change ack was expected from this player",
            _player->GetName().c_str(), _player->GetSession()->GetAccountId());
        _player->GetSession()->KickPlayer();
        return;
    }

    PlayerMovementPendingChange pendingChange = mover->PopPendingMovementChange();
    if (pendingChange.movementCounter != movementAck.Ack.AckIndex || pendingChange.movementChangeType != KNOCK_BACK
        || std::fabs(pendingChange.knockbackInfo.speedXY - movementAck.Ack.Status.jump.xyspeed) > 0.01f
        || std::fabs(pendingChange.knockbackInfo.speedZ - movementAck.Ack.Status.jump.zspeed) > 0.01f
        || std::fabs(pendingChange.knockbackInfo.vcos - movementAck.Ack.Status.jump.cosAngle) > 0.01f
        || std::fabs(pendingChange.knockbackInfo.vsin - movementAck.Ack.Status.jump.sinAngle) > 0.01f)
    {
        TC_LOG_INFO("cheat", "WorldSession::HandleMoveKnockBackAck: Player %s from account id %u kicked for incorrect data returned in an ack",
            _player->GetName().c_str(), _player->GetSession()->GetAccountId());
        _player->GetSession()->KickPlayer();
        return;
    }

    mover->ValidateMovementInfo(&movementAck.Ack.Status);
    /* the client data has been verified. let's do the actual change now */
    mover->UpdateMovementInfo(movementAck.Ack.Status);
    MovementPacketSender::SendKnockBackToObservers(mover, pendingChange.knockbackInfo.vcos, pendingChange.knockbackInfo.vsin,
        pendingChange.knockbackInfo.speedXY, pendingChange.knockbackInfo.speedZ);
}

/*
handles those packets:
APPLY:
CMSG_FORCE_MOVE_ROOT_ACK
CMSG_MOVE_GRAVITY_DISABLE_ACK
UNAPPLY:
CMSG_FORCE_MOVE_UNROOT_ACK
CMSG_MOVE_GRAVITY_ENABLE_ACK
*/
void WorldSession::HandleMovementFlagChangeAck(WorldPackets::Movement::MovementAckMessage& movementAck)
{
    Unit* mover = _player->GetUnitBeingMoved();
    ASSERT(mover);

    // now can skip not our packet
    if (mover->GetGUID() != movementAck.Ack.Status.guid) // @todo: potential hack attempt. use disciplinary measure?
        return;

    // verify that indeed the client is replying with the changes that were send to him
    if (!mover->HasPendingMovementChange())
    {
        TC_LOG_INFO("cheat", "WorldSession::HandleForceSpeedChangeAck: Player %s from account id %u kicked because no movement change ack was expected from this player",
            _player->GetName().c_str(), _player->GetSession()->GetAccountId());
        _player->GetSession()->KickPlayer();
        return;
    }

    PlayerMovementPendingChange pendingChange = mover->PopPendingMovementChange();
    bool applySent = pendingChange.apply;
    MovementChangeType changeTypeSent = pendingChange.movementChangeType;

    MovementFlags mFlag;
    MovementChangeType changeTypeReceived;
    bool applyReceived;
    switch (movementAck.GetOpcode())
    {
    case CMSG_FORCE_MOVE_ROOT_ACK:      changeTypeReceived = ROOT; applyReceived = true; mFlag = MOVEMENTFLAG_ROOT; break;
    case CMSG_FORCE_MOVE_UNROOT_ACK:    changeTypeReceived = ROOT; applyReceived = false; mFlag = MOVEMENTFLAG_ROOT; break;

    case CMSG_MOVE_GRAVITY_DISABLE_ACK: changeTypeReceived = GRAVITY_DISABLE; applyReceived = true; mFlag = MOVEMENTFLAG_DISABLE_GRAVITY; break;
    case CMSG_MOVE_GRAVITY_ENABLE_ACK:  changeTypeReceived = GRAVITY_DISABLE; applyReceived = false; mFlag = MOVEMENTFLAG_DISABLE_GRAVITY; break;
    default:
        TC_LOG_ERROR("network", "WorldSession::HandleMovementFlagChangeAck: Unknown move type opcode: %s", GetOpcodeNameForLogging(movementAck.GetOpcode()));
        return;
    }

    if (pendingChange.movementCounter != movementAck.Ack.AckIndex
        || applySent != applyReceived
        || changeTypeSent != changeTypeReceived)
    {
        TC_LOG_INFO("cheat", "WorldSession::HandleMovementFlagChangeAck: Player %s from account id %u kicked for incorrect data returned in an ack",
            _player->GetName().c_str(), _player->GetSession()->GetAccountId());
        _player->GetSession()->KickPlayer();
        return;
    }

    switch (changeTypeReceived)
    {
    case ROOT: mover->SetRootedReal(applyReceived); break;
    case GRAVITY_DISABLE: mover->SetDisableGravityReal(applyReceived); break;
    default:
        TC_LOG_ERROR("network", "WorldSession::HandleMovementFlagChangeToggleAck: Unknown move type opcode: %s", GetOpcodeNameForLogging(movementAck.GetOpcode()));
        return;
    }

    mover->ValidateMovementInfo(&movementAck.Ack.Status);
    mover->UpdateMovementInfo(movementAck.Ack.Status);
    MovementPacketSender::SendMovementFlagChangeToObservers(mover, mFlag, applySent);
}

/*
handles those packets:
CMSG_MOVE_WATER_WALK_ACK
CMSG_MOVE_HOVER_ACK
CMSG_MOVE_SET_CAN_FLY_ACK
CMSG_MOVE_SET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY_ACK
CMSG_MOVE_FEATHER_FALL_ACK
*/
void WorldSession::HandleMovementFlagChangeToggleAck(WorldPackets::Movement::MovementToggleAckMessage& movementAck)
{
    Unit* mover = _player->GetUnitBeingMoved();
    ASSERT(mover);

    bool applyReceived = movementAck.Apply != 0;

    // now can skip not our packet
    if (mover->GetGUID() != movementAck.Ack.Status.guid) // @todo: potential hack attempt. use disciplinary measure?
        return;

    // verify that indeed the client is replying with the changes that were send to him
    if (!mover->HasPendingMovementChange())
    {
        TC_LOG_INFO("cheat", "WorldSession::HandleForceSpeedChangeAck: Player %s from account id %u kicked because no movement change ack was expected from this player",
            _player->GetName().c_str(), _player->GetSession()->GetAccountId());
        _player->GetSession()->KickPlayer();
        return;
    }

    PlayerMovementPendingChange pendingChange = mover->PopPendingMovementChange();
    bool applySent = pendingChange.apply;
    MovementChangeType changeTypeSent = pendingChange.movementChangeType;

    MovementFlags mFlag = MOVEMENTFLAG_NONE;
    MovementFlags2 mFlag2 = MOVEMENTFLAG2_NONE;
    MovementChangeType changeTypeReceived;
    switch (movementAck.GetOpcode())
    {
    case CMSG_MOVE_WATER_WALK_ACK:      changeTypeReceived = WATER_WALK; mFlag = MOVEMENTFLAG_WATERWALKING; break;
    case CMSG_MOVE_HOVER_ACK:           changeTypeReceived = SET_HOVER; mFlag = MOVEMENTFLAG_HOVER; break;
    case CMSG_MOVE_SET_CAN_FLY_ACK:     changeTypeReceived = SET_CAN_FLY; mFlag = MOVEMENTFLAG_CAN_FLY; break;
    case CMSG_MOVE_SET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY_ACK:
        changeTypeReceived = SET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY; mFlag2 = MOVEMENTFLAG2_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY; break;
    case CMSG_MOVE_FEATHER_FALL_ACK:    changeTypeReceived = FEATHER_FALL; mFlag = MOVEMENTFLAG_FALLING_SLOW; break;
    default:
        TC_LOG_ERROR("network", "WorldSession::HandleMovementFlagChangeToggleAck: Unknown move type opcode: %s", GetOpcodeNameForLogging(movementAck.GetOpcode()));
        return;
    }

    if (pendingChange.movementCounter != movementAck.Ack.AckIndex
        || applySent != applyReceived
        || changeTypeSent != changeTypeReceived)
    {
        TC_LOG_INFO("cheat", "WorldSession::HandleMovementFlagChangeAck: Player %s from account id %u kicked for incorrect data returned in an ack",
            _player->GetName().c_str(), _player->GetSession()->GetAccountId());
        _player->GetSession()->KickPlayer();
        return;
    }

    switch (changeTypeReceived)
    {
    case WATER_WALK:            mover->SetWaterWalkingReal(applyReceived); break;
    case SET_HOVER:             mover->SetHoverReal(applyReceived); break;
    case SET_CAN_FLY:           mover->SetCanFlyReal(applyReceived); break;
    case SET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY:
        mover->SetCanTransitionBetweenSwimAndFlyReal(applyReceived); break;
    case FEATHER_FALL:          mover->SetFeatherFallReal(applyReceived); break;
    default:
        TC_LOG_ERROR("network", "WorldSession::HandleMovementFlagChangeToggleAck: Unknown move type opcode: %s", GetOpcodeNameForLogging(movementAck.GetOpcode()));
        return;
    }

    mover->ValidateMovementInfo(&movementAck.Ack.Status);
    mover->UpdateMovementInfo(movementAck.Ack.Status);
    if (mFlag != MOVEMENTFLAG_NONE)
        MovementPacketSender::SendMovementFlagChangeToObservers(mover, mFlag, applySent);
    else
        MovementPacketSender::SendMovementFlagChangeToObservers(mover, mFlag2);
}

void WorldSession::HandleMoveTimeSkippedOpcode(WorldPackets::Movement::MoveTimeSkipped& /*moveTimeSkipped*/)
{
    /*
    //// @todo
    must be need use in Trinity
    We substract server Lags to move time (AntiLags)
    for exmaple
    GetPlayer()->ModifyLastMoveTime(-int32(moveTimeSkipped.TimeSkipped));
    */
}

/*
Handles CMSG_WORLD_TELEPORT. That packet is sent by the client when the user types a special build-in command restricted to GMs.
cf http://wow.gamepedia.com/Console_variables#GM_Commands
The usage of this packet is therefore restricted to GMs and will never be used by normal players.
*/
void WorldSession::HandleWorldTeleportOpcode(WorldPacket& recvData)
{
    uint32 time;
    uint32 mapid;
    float PositionX;
    float PositionY;
    float PositionZ;
    float Orientation;

    recvData >> time;                                      // time in m.sec.
    recvData >> mapid;
    recvData >> PositionX;
    recvData >> PositionY;
    recvData >> PositionZ;
    recvData >> Orientation;                               // o (3.141593 = 180 degrees)

    TC_LOG_DEBUG("network", "WORLD: Received CMSG_WORLD_TELEPORT");

    if (GetPlayer()->IsInFlight())
    {
        TC_LOG_DEBUG("network", "Player '%s' (GUID: %u) in flight, ignore worldport command.",
            GetPlayer()->GetName().c_str(), GetPlayer()->GetGUID().GetCounter());
        return;
    }

    TC_LOG_DEBUG("network", "CMSG_WORLD_TELEPORT: Player = %s, Time = %u, map = %u, x = %f, y = %f, z = %f, o = %f",
        GetPlayer()->GetName().c_str(), time, mapid, PositionX, PositionY, PositionZ, Orientation);

    if (HasPermission(rbac::RBAC_PERM_OPCODE_WORLD_TELEPORT))
        GetPlayer()->TeleportTo(mapid, PositionX, PositionY, PositionZ, Orientation);
    else
        SendNotification(LANG_YOU_NOT_HAVE_PERMISSION);
}

void WorldSession::HandleSummonResponseOpcode(WorldPackets::Movement::SummonResponse& packet)
{
    if (!_player->IsAlive() || _player->IsInCombat())
        return;

    _player->SummonIfPossible(packet.Accept);
}
