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

#include "Battlefield.h"
#include "BattlefieldMgr.h"
#include "Battleground.h"
#include "CellImpl.h"
#include "CreatureTextMgr.h"
#include "DBCStores.h"
#include "DBCStoresMgr.h"
#include "GameTime.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Group.h"
#include "GroupMgr.h"
#include "Log.h"
#include "Map.h"
#include "MapManager.h"
#include "MiscPackets.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"
#include "WorldStatePackets.h"
#include <G3D/g3dmath.h>

Battlefield::Battlefield()
{
    m_Timer = 0;
    m_IsEnabled = true;
    m_isActive = false;
    m_DefenderTeam = TEAM_NEUTRAL;

    m_TypeId = 0;
    m_BattleId = 0;
    m_ZoneId = 0;
    m_Map = nullptr;
    m_MapId = 0;
    m_MaxPlayer = 0;
    m_MinPlayer = 0;
    m_MinLevel = 0;
    m_BattleTime = 0;
    m_NoWarBattleTime = 0;
    m_RestartAfterCrash = 0;
    m_TimeForAcceptInvite = 20;
    m_uiAcceptTimer = 1000;

    m_uiKickAfkPlayersTimer = 1000;

    for (uint8 i = 0; i < PVP_TEAMS_COUNT; i++)
        m_freeslots[i] = 0;

    m_LastResurrectTimer = 30 * IN_MILLISECONDS;
    m_StartGroupingTimer = 0;
    m_StartGrouping = false;
}

Battlefield::~Battlefield()
{
    for (CapturePointContainer::const_iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
        delete itr->second.pointer;
    for (GraveyardVect::const_iterator itr = m_GraveyardList.begin(); itr != m_GraveyardList.end(); ++itr)
        delete *itr;

    m_PlayerMap.clear();
}

// Called when a player enters the zone
void Battlefield::HandlePlayerEnterZone(Player* player, uint32 /*zone*/)
{
    if (PlayerInBFPlayerMap(player))
        UpdateZoneStatusInPlayerMap(player, true);
    else
    {
        if (IsWarTime())
        {
            if (GetFreeslot(player->GetCFSTeamId()))
            {
                // low level
                if (player->GetLevel() < m_MinLevel)
                {
                    BFLeaveReason reason = BF_LEAVE_REASON_LOW_LEVEL;
                    player->GetSession()->SendBattlefieldLeaveMessage(m_BattleId, reason);
                    AddPlayer(player, true, false, false, true, GameTime::GetGameTime() + m_TimeForAcceptInvite);
                    return;
                }

                InviteNewPlayerToWar(player, true);
            }
            else  // no free slots for player
            {
                player->GetSession()->SendBattlefieldEjectPending(m_BattleId, true);
                AddPlayer(player, true, false, false, true, GameTime::GetGameTime() + m_TimeForAcceptInvite);
            }
        }
        else
        {
            if (player->GetLevel() < m_MinLevel)
                AddPlayer(player, true, false, false, false);   // we should add him in playermap, when war will start, if level will lower - will be kicked
            else
            {
                if (GetFreeslot(player->GetCFSTeamId()))
                    InviteNewPlayerToQueue(player, true);
                else
                    AddPlayer(player, true, false, false, false);   // we should add him in playermap, when war will start, we will try to add him in war and queue (if will exist free slot)
            }
        }
    }

    OnPlayerEnterZone(player);
}

// Called when a player leave the zone
void Battlefield::HandlePlayerLeaveZone(Player* player, uint32 /*zone*/)
{
    if (PlayerInBFPlayerMap(player))
    {
        UpdateZoneStatusInPlayerMap(player, false);

        if (IsWarTime())
        {
            // If the player is participating to the battle
            player->GetSession()->SendBattlefieldLeaveMessage(m_BattleId);
            RemovePlayer(player);

            if (Group* group = player->GetGroup()) // Remove the player from the raid group
                group->RemoveMember(player->GetGUID());

            OnPlayerLeaveWar(player);
        }
        else
        {
            bool needtoremove = false;
            // remove player in piece time if he not in queue
            for (PlayerHolderContainer::const_iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
                if (itr->second.GUID == player->GetGUID())
                {
                    if (!itr->second.inQueue)
                        needtoremove = true;
                    break;
                }

            if (needtoremove)
                RemovePlayer(player);
        }

        for (CapturePointContainer::iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
            itr->second.pointer->HandlePlayerLeave(player);
    }

    SendRemoveWorldStates(player);
    RemovePlayerFromResurrectQueue(player->GetGUID());

    OnPlayerLeaveZone(player);
}

bool Battlefield::Update(uint32 diff)
{
    if (m_Timer <= diff)
    {
        // Battlefield ends on time
        if (IsWarTime())
            EndBattle(true);
        else // Time to start a new battle!
            StartBattle();
    }
    else
        m_Timer -= diff;

    // Invite players a few minutes before the battle's beginning
    if (!IsWarTime() && !m_StartGrouping && m_Timer <= m_StartGroupingTimer)
    {
        m_StartGrouping = true;
        InvitePlayersInZoneToQueue();
        OnStartGrouping();
    }

    bool objective_changed = false;

    // Expired time for Awaiting Responce List
    if (m_uiAcceptTimer <= diff)
    {
        time_t now = GameTime::GetGameTime();
        std::set<ObjectGuid>_playerkick;
        for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        {
            // check estimation time for awaiting war and waiting to kick
            if (itr->second.isWaitingWar || itr->second.isWaitingKick)
            {
                if (itr->second.time <= now)
                    _playerkick.insert(itr->second.GUID);
            }
        }

        for (auto itr = _playerkick.begin(); itr != _playerkick.end(); ++itr)
            KickPlayerFromBattlefield(*itr);

        _playerkick.clear();

        m_uiAcceptTimer = 1000;
    }
    else
        m_uiAcceptTimer -= diff;

    for (CapturePointContainer::iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
        if (itr->second.pointer->Update(diff))
            objective_changed = true;

    if (m_LastResurrectTimer <= diff)
    {
        for (uint8 i = 0; i < m_GraveyardList.size(); i++)
            if (GetGraveyardById(i))
                m_GraveyardList[i]->Resurrect();
        m_LastResurrectTimer = RESURRECTION_INTERVAL;
    }
    else
        m_LastResurrectTimer -= diff;

    return objective_changed;
}

void Battlefield::InvitePlayersInZoneToQueue()
{
    time_t futuretime = GameTime::GetGameTime() + m_TimeForAcceptInvite;
    for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (!itr->second.inQueue && !itr->second.isWaitingQueue)
            if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
            {
                itr->second.isWaitingQueue = true;
                itr->second.time = futuretime;
                player->GetSession()->SendBattlefieldInvitePlayerToQueue(m_BattleId);
            }
}

void Battlefield::InvitePlayersInQueueToWar()
{
    time_t futuretime = GameTime::GetGameTime() + m_TimeForAcceptInvite;
    for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (itr->second.inQueue)
            if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
            {
                itr->second.isWaitingWar = true;
                itr->second.time = futuretime;
                player->GetSession()->SendBattlefieldInvitePlayerToWar(m_BattleId, m_ZoneId, m_TimeForAcceptInvite);
            }
}

void Battlefield::TryInvitePlayersNotInQueueToWarOrKickThem()
{
    std::set<ObjectGuid>_playerkick;
    time_t futuretime = GameTime::GetGameTime() + m_TimeForAcceptInvite;
    for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (!itr->second.inQueue)
        {
            if (GetFreeslot(itr->second.team))
            {
                if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
                {
                    if (player->GetLevel() >= m_MinLevel)
                    {
                        itr->second.isWaitingQueue = true;
                        itr->second.isWaitingWar = true;
                        itr->second.time = futuretime;
                        player->GetSession()->SendBattlefieldInvitePlayerToWar(m_BattleId, m_ZoneId, m_TimeForAcceptInvite);
                    }
                    else
                        _playerkick.insert(itr->second.GUID);
                }
            }
            else
                _playerkick.insert(itr->second.GUID);
        }

    for (auto itr = _playerkick.begin(); itr != _playerkick.end(); ++itr)
        KickPlayerFromBattlefield(*itr);

    _playerkick.clear();
}

void Battlefield::InitStalker(uint32 entry, Position const& pos)
{
    if (Creature* creature = SpawnCreature(entry, pos))
        StalkerGuid = creature->GetGUID();
    else
        TC_LOG_ERROR("bg.battlefield", "Battlefield::InitStalker: Could not spawn Stalker (Creature entry %u), zone messages will be unavailable!", entry);
}

bool Battlefield::PlayerInBFPlayerMap(Player* plr)
{
    bool result = false;
    for (PlayerHolderContainer::const_iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (itr->second.GUID == plr->GetGUID())
        {
            result = true;
            break;
        }

    return result;
}

void Battlefield::UpdateZoneStatusInPlayerMap(Player* plr, bool inZone)
{
    for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (itr->second.GUID == plr->GetGUID())
        {
            itr->second.inZone = inZone;
            break;
        }
}

void Battlefield::InviteNewPlayerToWar(Player* player, bool inZone)
{
    if (!player)
        return;

    // we should to add each player in queue, doesn't matter war status
    AddPlayer(player, inZone, true, true, false, GameTime::GetGameTime() + m_TimeForAcceptInvite);
    player->GetSession()->SendBattlefieldInvitePlayerToWar(m_BattleId, m_ZoneId, m_TimeForAcceptInvite);
}

void Battlefield::InviteNewPlayerToQueue(Player* player, bool isInZone)
{
    if (!player)
        return;

    // we should to add each player in queue
    AddPlayer(player, isInZone, true, false, false);
    player->GetSession()->SendBattlefieldInvitePlayerToQueue(m_BattleId);
}

void Battlefield::AddPlayer(Player* plr, bool InZone, bool IsWaitingQueue, bool IsWaitingWar, bool IsWaitingKick, time_t time)
{
    if (PlayerInBFPlayerMap(plr))
        return;

    uint32 new_id = 0;
    for (PlayerHolderContainer::const_iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (itr->first > new_id)
            new_id = itr->first;

    // use next
    ++new_id;

    PlayerHolder pl;
    pl.GUID = plr->GetGUID();
    pl.inZone = InZone;
    pl.isWaitingQueue = IsWaitingQueue;
    pl.isWaitingWar = IsWaitingWar;
    pl.isWaitingKick = IsWaitingKick;
    pl.inQueue = false;
    pl.inWar = false;
    pl.team = plr->GetCFSTeamId();
    pl.time = time;
    m_PlayerMap[new_id] = pl;
}

void Battlefield::RemovePlayer(Player* plr)
{
    uint32 id = 0;
    for (PlayerHolderContainer::const_iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (itr->second.GUID == plr->GetGUID())
        {
            id = itr->first;
            if (itr->second.inQueue)
                m_freeslots[itr->second.team]++;
            if (itr->second.inWar)
                plr->SetBattlefieldWarMember(false);
            break;
        }

    if (id)
        m_PlayerMap.erase(id);
}

void Battlefield::KickPlayerFromBattlefield(ObjectGuid guid)
{
    if (Player* player = ObjectAccessor::FindPlayer(guid))
        if (player->GetZoneId() == GetZoneId())
        {
            player->TeleportTo(KickPosition);
            RemovePlayer(player);
            player->GetSession()->SendBattlefieldLeaveMessage(m_BattleId);
        }
}

void Battlefield::StartBattle()
{
    if (m_isActive)
        return;

    for (uint8 team = 0; team < PVP_TEAMS_COUNT; ++team)
        m_Groups[team].clear();

    m_Timer = m_BattleTime;
    m_isActive = true;

    InvitePlayersInQueueToWar();
    TryInvitePlayersNotInQueueToWarOrKickThem();
    OnBattleStart();
}

void Battlefield::EndBattle(bool endByTimer)
{
    if (!m_isActive)
        return;

    m_isActive = false;

    m_StartGrouping = false;

    if (!endByTimer)
        SetDefenderTeam(GetAttackerTeam());

    OnBattleEnd(endByTimer);

    for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
    {
        itr->second.inWar = false;
        itr->second.inQueue = false;

        if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
            player->SetBattlefieldWarMember(false);
    }

    for (uint8 i = 0; i < PVP_TEAMS_COUNT; i++)
        m_freeslots[i] = m_MaxPlayer;

    // Reset bat0tlefield timer
    m_Timer = m_NoWarBattleTime;
    SendInitWorldStatesToAll();
}

void Battlefield::DoPlaySoundToAll(uint32 soundID)
{
    BroadcastPacketToWar(WorldPackets::Misc::PlaySound(soundID).Write());
}

// Called in WorldSession::HandleBfQueueExitRequest
void Battlefield::AskToLeaveQueue(Player* player)
{
    if (IsWarTime())
    {
        RemovePlayer(player);
        PlayerAskToLeave(player);
    }
    else
    {
        bool removeIfNotInZone = false;
        for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
            if (itr->second.GUID == player->GetGUID())
            {
                if (itr->second.inQueue)
                {
                    itr->second.inQueue = false;
                    m_freeslots[itr->second.team]++;

                    removeIfNotInZone = !itr->second.inZone;
                }
                break;
            }

        if (removeIfNotInZone)
            RemovePlayer(player);
    }
}

// Called in WorldSession::HandleHearthAndResurrect
void Battlefield::PlayerAskToLeave(Player* player)
{
    // Player leaving Wintergrasp, teleport to Dalaran.
    // ToDo: confirm teleport destination.
    player->TeleportTo(571, 5804.1499f, 624.7710f, 647.7670f, 1.6400f);
}

// Called in WorldSession::HandleBfQueueInviteResponse
void Battlefield::PlayerAcceptInviteToQueue(Player* player)
{
    for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (itr->second.GUID == player->GetGUID())
        {
            if (!itr->second.inQueue && itr->second.isWaitingQueue)
            {
                if (GetFreeslot(player->GetCFSTeamId()))
                {
                    m_freeslots[player->GetCFSTeamId()]--;
                    itr->second.isWaitingQueue = false;
                    itr->second.inQueue = true;
                    // Send notification
                    player->GetSession()->SendBattlefieldQueueInviteResponse(m_BattleId, m_ZoneId);
                }
                else
                {
                    itr->second.isWaitingQueue = false;
                    itr->second.inQueue = false;
                    // Send notification
                    player->GetSession()->SendBattlefieldQueueInviteResponse(m_BattleId, m_ZoneId, false, false);
                }
            }

            break;
        }
}

// Called in WorldSession::HandleBfEntryInviteResponse
void Battlefield::PlayerAcceptInviteToWar(Player* player)
{
    if (!IsWarTime())
        return;

    for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (itr->second.GUID == player->GetGUID())
        {
            // if newplayer trying to enter in war we should add him in queue
            if (itr->second.isWaitingQueue)
            {
                if (GetFreeslot(player->GetCFSTeamId()))
                {
                    m_freeslots[player->GetCFSTeamId()]--;
                    itr->second.isWaitingQueue = false;
                    itr->second.isWaitingWar = false;
                    itr->second.inQueue = true;
                    player->SetBattlefieldWarMember(true);
                }
                else // if player has declined invite in queue in zone, and bf has started, but no more free slots
                {
                    itr->second.isWaitingQueue = false;
                    itr->second.isWaitingWar = false;
                    // just kick him by next update tick
                    itr->second.isWaitingKick = true;
                    itr->second.time = GameTime::GetGameTime();
                    player->GetSession()->SendBattlefieldEjectPending(m_BattleId, true);
                    player->SetBattlefieldWarMember(false);
                }
            }

            // Check that this player already in queue
            if (itr->second.inQueue)
            {
                itr->second.isWaitingWar = false;
                itr->second.inWar = true;
                player->SetBattlefieldWarMember(true);
                if (AddOrSetPlayerToCorrectBfGroup(player))
                {
                    player->GetSession()->SendBattlefieldEntered(m_BattleId);
                    if (player->isAFK())
                        player->ToggleAFK();

                    OnPlayerJoinWar(player);                               //for scripting
                }
            }

            break;
        }
}

void Battlefield::PlayerDeclineInviteToQueue(Player* player)
{
    for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (itr->second.GUID == player->GetGUID())
        {
            itr->second.isWaitingQueue = false;
            itr->second.inQueue = false;
            break;
        }
}

void Battlefield::PlayerDeclineInviteToWar(Player* player)
{
    m_freeslots[player->GetCFSTeamId()]++;

    AskToLeaveQueue(player);
}

void Battlefield::TeamCastSpell(TeamId team, int32 spellId)
{
    if (spellId > 0)
    {
        for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
            if (itr->second.inWar && itr->second.team == team)
                if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
                    player->CastSpell(player, uint32(spellId), true);
    }
    else
    {
        for (PlayerHolderContainer::iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
            if (itr->second.inWar && itr->second.team == team)
                if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
                    player->RemoveAuraFromStack(uint32(-spellId));
    }
}

void Battlefield::BroadcastPacketToZone(WorldPacket const* data) const
{
    for (PlayerHolderContainer::const_iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (itr->second.inZone)
            if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
                player->SendDirectMessage(data);
}

void Battlefield::BroadcastPacketToQueue(WorldPacket const* data) const
{
    for (PlayerHolderContainer::const_iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (itr->second.inQueue)
            if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
                player->SendDirectMessage(data);
}

void Battlefield::BroadcastPacketToWar(WorldPacket const* data) const
{
    for (PlayerHolderContainer::const_iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (itr->second.inWar)
            if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
                player->SendDirectMessage(data);
}

void Battlefield::SendWarning(uint8 id, WorldObject const* target /*= nullptr*/)
{
    if (Creature* stalker = GetCreature(StalkerGuid))
        sCreatureTextMgr->SendChat(stalker, id, target);
}

void Battlefield::SendInitWorldStatesTo(Player* player)
{
    WorldPackets::WorldState::InitWorldStates packet;
    packet.MapID = m_MapId;
    packet.ZoneID = m_ZoneId;
    packet.AreaID = player->GetAreaId();
    FillInitialWorldStates(packet);

    player->SendDirectMessage(packet.Write());
}

void Battlefield::SendUpdateWorldState(uint32 field, uint32 value)
{
    for (PlayerHolderContainer::const_iterator itr = m_PlayerMap.begin(); itr != m_PlayerMap.end(); ++itr)
        if (Player* player = ObjectAccessor::FindPlayer(itr->second.GUID))
            player->SendUpdateWorldState(field, value);
}

void Battlefield::RegisterZone(uint32 zoneId)
{
    sBattlefieldMgr->AddZone(zoneId, this);
}

void Battlefield::HideNpc(Creature* creature)
{
    creature->CombatStop();
    creature->SetReactState(REACT_PASSIVE);
    creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
    creature->SetPhaseMask(2, true);
    //creature->DisappearAndDie();
    creature->SetVisible(false);
}

void Battlefield::ShowNpc(Creature* creature, bool aggressive)
{
    creature->SetPhaseMask(1, true);
    creature->SetVisible(true);
    creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
    if (!creature->IsAlive())
        creature->Respawn(true);
    if (aggressive)
        creature->SetReactState(REACT_AGGRESSIVE);
    else
    {
        creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        creature->SetReactState(REACT_PASSIVE);
    }
}

// ****************************************************
// ******************* Group System *******************
// ****************************************************
Group* Battlefield::GetFreeBfRaid(TeamId TeamId)
{
    for (auto itr = m_Groups[TeamId].begin(); itr != m_Groups[TeamId].end(); ++itr)
        if (Group* group = sGroupMgr->GetGroupByGUID(itr->GetCounter()))
            if (!group->IsFull())
                return group;

    return nullptr;
}

Group* Battlefield::GetGroupPlayer(ObjectGuid guid, TeamId TeamId)
{
    for (auto itr = m_Groups[TeamId].begin(); itr != m_Groups[TeamId].end(); ++itr)
        if (Group* group = sGroupMgr->GetGroupByGUID(itr->GetCounter()))
            if (group->IsMember(guid))
                return group;

    return nullptr;
}

bool Battlefield::AddOrSetPlayerToCorrectBfGroup(Player* player)
{
    if (!player->IsInWorld())
        return false;

    if (Group* group = player->GetGroup())
        group->RemoveMember(player->GetGUID());

    Group* group = GetFreeBfRaid(player->GetTeamId());
    if (!group)
    {
        group = new Group;
        group->SetBattlefieldGroup(this);
        group->Create(player);
        sGroupMgr->AddGroup(group);
        m_Groups[player->GetTeamId()].insert(group->GetGUID());
    }
    else if (group->IsMember(player->GetGUID()))
    {
        uint8 subgroup = group->GetMemberGroup(player->GetGUID());
        player->SetBattlegroundOrBattlefieldRaid(group, subgroup);
    }
    else
        group->AddMember(player);

    return true;
}

//***************End of Group System*******************

//*****************************************************
//***************Spirit Guide System*******************
//*****************************************************

//--------------------
//-Battlefield Method-
//--------------------
BfGraveyard* Battlefield::GetGraveyardById(uint32 id) const
{
    if (id < m_GraveyardList.size())
    {
        if (BfGraveyard* graveyard = m_GraveyardList.at(id))
            return graveyard;
        else
            TC_LOG_ERROR("bg.battlefield", "Battlefield::GetGraveyardById Id:%u does not exist.", id);
    }
    else
        TC_LOG_ERROR("bg.battlefield", "Battlefield::GetGraveyardById Id:%u could not be found.", id);

    return nullptr;
}

WorldSafeLocsDBC const* Battlefield::GetClosestGraveyard(Player* player)
{
    BfGraveyard* closestGY = nullptr;
    float maxdist = -1;
    for (uint8 i = 0; i < m_GraveyardList.size(); i++)
    {
        if (m_GraveyardList[i])
        {
            if (m_GraveyardList[i]->GetControlTeamId() != player->GetTeamId())
                continue;

            float dist = m_GraveyardList[i]->GetDistance(player);
            if (dist < maxdist || maxdist < 0)
            {
                closestGY = m_GraveyardList[i];
                maxdist = dist;
            }
        }
    }

    if (closestGY)
        return sDBCStoresMgr->GetWorldSafeLocsDBC(closestGY->GetGraveyardId());

    return nullptr;
}

void Battlefield::AddPlayerToResurrectQueue(ObjectGuid npcGuid, ObjectGuid playerGuid)
{
    for (uint8 i = 0; i < m_GraveyardList.size(); i++)
    {
        if (!m_GraveyardList[i])
            continue;

        if (m_GraveyardList[i]->HasNpc(npcGuid))
        {
            m_GraveyardList[i]->AddPlayer(playerGuid);
            break;
        }
    }
}

void Battlefield::RemovePlayerFromResurrectQueue(ObjectGuid playerGuid)
{
    for (uint8 i = 0; i < m_GraveyardList.size(); i++)
    {
        if (!m_GraveyardList[i])
            continue;

        if (m_GraveyardList[i]->HasPlayer(playerGuid))
        {
            m_GraveyardList[i]->RemovePlayer(playerGuid);
            break;
        }
    }
}

void Battlefield::SendAreaSpiritHealerQueryOpcode(Player* player, ObjectGuid guid)
{
    WorldPacket data(SMSG_AREA_SPIRIT_HEALER_TIME, 12);
    uint32 time = m_LastResurrectTimer;  // resurrect every 30 seconds

    data << guid << time;
    player->SendDirectMessage(&data);
}

// ----------------------
// - BfGraveyard Method -
// ----------------------
BfGraveyard::BfGraveyard(Battlefield* battlefield)
{
    m_Bf = battlefield;
    m_GraveyardId = 0;
    m_ControlTeam = TEAM_NEUTRAL;
}

void BfGraveyard::Initialize(TeamId startControl, uint32 graveyardId)
{
    m_ControlTeam = startControl;
    m_GraveyardId = graveyardId;
}

void BfGraveyard::SetSpirit(Creature* spirit, TeamId team)
{
    if (!spirit)
    {
        TC_LOG_ERROR("bg.battlefield", "BfGraveyard::SetSpirit: Invalid Spirit.");
        return;
    }

    m_SpiritGuide[team] = spirit->GetGUID();
    spirit->SetReactState(REACT_PASSIVE);
}

float BfGraveyard::GetDistance(Player* player)
{
    WorldSafeLocsDBC const* safeLoc = sDBCStoresMgr->GetWorldSafeLocsDBC(m_GraveyardId);
    return player->GetDistance2d(safeLoc->Loc.X, safeLoc->Loc.Y);
}

void BfGraveyard::AddPlayer(ObjectGuid playerGuid)
{
    if (!m_ResurrectQueue.count(playerGuid))
    {
        m_ResurrectQueue.insert(playerGuid);

        if (Player* player = ObjectAccessor::FindPlayer(playerGuid))
            player->CastSpell(player, SPELL_WAITING_FOR_RESURRECT, true);
    }
}

void BfGraveyard::RemovePlayer(ObjectGuid playerGuid)
{
    m_ResurrectQueue.erase(m_ResurrectQueue.find(playerGuid));

    if (Player* player = ObjectAccessor::FindPlayer(playerGuid))
        player->RemoveAurasDueToSpell(SPELL_WAITING_FOR_RESURRECT);
}

void BfGraveyard::Resurrect()
{
    if (m_ResurrectQueue.empty())
        return;

    for (GuidSet::const_iterator itr = m_ResurrectQueue.begin(); itr != m_ResurrectQueue.end(); ++itr)
    {
        // Get player object from his guid
        Player* player = ObjectAccessor::FindPlayer(*itr);
        if (!player)
            continue;

        // Check if the player is in world and on the good graveyard
        if (player->IsInWorld())
            if (Creature* spirit = m_Bf->GetCreature(m_SpiritGuide[m_ControlTeam]))
                spirit->CastSpell(spirit, SPELL_SPIRIT_HEAL, true);

        // Resurrect player
        player->CastSpell(player, SPELL_RESURRECTION_VISUAL, true);
        player->ResurrectPlayer(1.0f);
        player->CastSpell(player, 6962, true);
        player->CastSpell(player, SPELL_SPIRIT_HEAL_MANA, true);

        player->SpawnCorpseBones(false);
    }

    m_ResurrectQueue.clear();
}

// For changing graveyard control
void BfGraveyard::GiveControlTo(TeamId team)
{
    // Guide switching
    // Note: Visiblity changes are made by phasing
    /*if (m_SpiritGuide[1 - team])
        m_SpiritGuide[1 - team]->SetVisible(false);
    if (m_SpiritGuide[team])
        m_SpiritGuide[team]->SetVisible(true);*/

    m_ControlTeam = team;
    // Teleport to other graveyard, player witch were on this graveyard
    RelocateDeadPlayers();
}

void BfGraveyard::RelocateDeadPlayers()
{
    WorldSafeLocsDBC const* closestGrave = nullptr;
    for (GuidSet::const_iterator itr = m_ResurrectQueue.begin(); itr != m_ResurrectQueue.end(); ++itr)
    {
        Player* player = ObjectAccessor::FindPlayer(*itr);
        if (!player)
            continue;

        if (closestGrave)
            player->TeleportTo(player->GetMapId(), closestGrave->Loc.X, closestGrave->Loc.Y, closestGrave->Loc.Z, player->GetOrientation());
        else
        {
            closestGrave = m_Bf->GetClosestGraveyard(player);
            if (closestGrave)
                player->TeleportTo(player->GetMapId(), closestGrave->Loc.X, closestGrave->Loc.Y, closestGrave->Loc.Z, player->GetOrientation());
        }
    }
}

bool BfGraveyard::HasNpc(ObjectGuid guid)
{
    if (!m_SpiritGuide[TEAM_ALLIANCE] || !m_SpiritGuide[TEAM_HORDE])
        return false;

    if (!m_Bf->GetCreature(m_SpiritGuide[TEAM_ALLIANCE]) ||
        !m_Bf->GetCreature(m_SpiritGuide[TEAM_HORDE]))
        return false;

    return (m_SpiritGuide[TEAM_ALLIANCE] == guid || m_SpiritGuide[TEAM_HORDE] == guid);
}

// *******************************************************
// *************** End Spirit Guide system ***************
// *******************************************************
// ********************** Misc ***************************
// *******************************************************

Creature* Battlefield::SpawnCreature(uint32 entry, Position const& pos)
{
    //Get map object
    Map* map = sMapMgr->CreateBaseMap(m_MapId);
    if (!map)
    {
        TC_LOG_ERROR("bg.battlefield", "Battlefield::SpawnCreature: Can't create creature entry: %u, map not found.", entry);
        return nullptr;
    }

    Creature* creature = new Creature();
    if (!creature->Create(map->GenerateLowGuid<HighGuid::Unit>(), map, PHASEMASK_NORMAL, entry, pos))
    {
        TC_LOG_ERROR("bg.battlefield", "Battlefield::SpawnCreature: Can't create creature entry: %u", entry);
        delete creature;
        return nullptr;
    }

    creature->SetHomePosition(pos);

    // Set creature in world
    map->AddToMap(creature);
    creature->setActive(true);
    creature->SetFarVisible(true);

    return creature;
}

// Method for spawning gameobject on map
GameObject* Battlefield::SpawnGameObject(uint32 entry, Position const& pos, QuaternionData const& rot)
{
    // Get map object
    Map* map = sMapMgr->CreateBaseMap(m_MapId);
    if (!map)
        return nullptr;

    // Create gameobject
    GameObject* go = new GameObject;
    if (!go->Create(map->GenerateLowGuid<HighGuid::GameObject>(), entry, map, PHASEMASK_NORMAL, pos, rot, 255, GO_STATE_READY))
    {
        TC_LOG_ERROR("bg.battlefield", "Battlefield::SpawnGameObject: Gameobject template %u could not be found in the database! Battlefield has not been created!", entry);
        TC_LOG_ERROR("bg.battlefield", "Battlefield::SpawnGameObject: Could not create gameobject template %u! Battlefield has not been created!", entry);
        delete go;
        return nullptr;
    }

    // Add to world
    map->AddToMap(go);
    go->setActive(true);
    go->SetFarVisible(true);

    return go;
}

Creature* Battlefield::GetCreature(ObjectGuid guid)
{
    if (!m_Map)
        return nullptr;
    return m_Map->GetCreature(guid);
}

GameObject* Battlefield::GetGameObject(ObjectGuid guid)
{
    if (!m_Map)
        return nullptr;
    return m_Map->GetGameObject(guid);
}

// *******************************************************
// ******************* CapturePoint **********************
// *******************************************************

BfCapturePoint::BfCapturePoint(Battlefield* battlefield) : m_Bf(battlefield), m_capturePointGUID()
{
    m_team = TEAM_NEUTRAL;
    m_value = 0;
    m_minValue = 0.0f;
    m_maxValue = 0.0f;
    m_State = BF_CAPTUREPOINT_OBJECTIVESTATE_NEUTRAL;
    m_OldState = BF_CAPTUREPOINT_OBJECTIVESTATE_NEUTRAL;
    m_capturePointEntry = 0;
    m_neutralValuePct = 0;
    m_maxSpeed = 0;
}

void Battlefield::AddCapturePoint(BfCapturePoint* cp, uint8 workshopId)
{
    uint32 new_id = 0;
    for (CapturePointContainer::const_iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
        if (itr->first > new_id)
            new_id = itr->first;

    // use next
    ++new_id;

    CapturePointHolder cph;
    cph.pointer = cp;
    cph.workshopId = workshopId;
    m_capturePoints[new_id] = cph;
}

bool BfCapturePoint::HandlePlayerEnter(Player* player)
{
    if (m_capturePointGUID)
    {
        if (GameObject* capturePoint = m_Bf->GetGameObject(m_capturePointGUID))
        {
            player->SendUpdateWorldState(capturePoint->GetGOInfo()->capturePoint.worldState1, 1);
            player->SendUpdateWorldState(capturePoint->GetGOInfo()->capturePoint.worldstate2, uint32(ceil((m_value + m_maxValue) / (2 * m_maxValue) * 100.0f)));
            player->SendUpdateWorldState(capturePoint->GetGOInfo()->capturePoint.worldstate3, m_neutralValuePct);
        }
    }

    return m_activePlayers[player->GetTeamId()].insert(player->GetGUID()).second;
}

GuidSet::iterator BfCapturePoint::HandlePlayerLeave(Player* player)
{
    if (m_capturePointGUID)
        if (GameObject* capturePoint = m_Bf->GetGameObject(m_capturePointGUID))
            player->SendUpdateWorldState(capturePoint->GetGOInfo()->capturePoint.worldState1, 0);

    GuidSet::iterator current = m_activePlayers[player->GetTeamId()].find(player->GetGUID());

    if (current == m_activePlayers[player->GetTeamId()].end())
        return current; // return end()

    m_activePlayers[player->GetTeamId()].erase(current++);
    return current;
}

void BfCapturePoint::SendChangePhase()
{
    if (!m_capturePointGUID)
        return;

    if (GameObject* capturePoint = m_Bf->GetGameObject(m_capturePointGUID))
    {
        // send this too, sometimes the slider disappears, dunno why :(
        SendUpdateWorldState(capturePoint->GetGOInfo()->capturePoint.worldState1, 1);
        // send these updates to only the ones in this objective
        SendUpdateWorldState(capturePoint->GetGOInfo()->capturePoint.worldstate2, (uint32) std::ceil((m_value + m_maxValue) / (2 * m_maxValue) * 100.0f));
        // send this too, sometimes it resets :S
        SendUpdateWorldState(capturePoint->GetGOInfo()->capturePoint.worldstate3, m_neutralValuePct);
    }
}

bool BfCapturePoint::ChangeState()
{
    bool result = false;
    if (!m_capturePointGUID)
        return result;

    if (GameObject* capturePoint = m_Bf->GetGameObject(m_capturePointGUID))
    {
        uint32 artkit = 0;
        switch (m_State)
        {
            case BF_CAPTUREPOINT_OBJECTIVESTATE_HORDE: artkit = 1; break;
            case BF_CAPTUREPOINT_OBJECTIVESTATE_ALLIANCE: artkit = 2; break;
            default:
                break;
        }

        if (capturePoint->GetGoArtKit() != artkit)
        {
            switch (artkit)
            {
                case 0: m_team = TEAM_NEUTRAL; break;
                case 1: m_team = TEAM_HORDE; break;
                case 2: m_team = TEAM_ALLIANCE; break;
            }
            result = true;
        }
        capturePoint->SetGoArtKit(artkit);
    }

    return result;
}

void BfCapturePoint::SetInitialData(TeamId team)
{
    switch (team)
    {
        case TEAM_ALLIANCE:
        {
            m_value = m_maxValue;
            m_State = BF_CAPTUREPOINT_OBJECTIVESTATE_ALLIANCE;
            m_team = TEAM_ALLIANCE;
            break;
        }
        case TEAM_HORDE:
        {
            m_value = -m_maxValue;
            m_State = BF_CAPTUREPOINT_OBJECTIVESTATE_HORDE;
            m_team = TEAM_HORDE;
            break;
        }
        case TEAM_NEUTRAL:
        {
            m_value = 0;
            m_State = BF_CAPTUREPOINT_OBJECTIVESTATE_NEUTRAL;
            m_team = TEAM_NEUTRAL;
        }
    }

    ChangeState();
}

bool BfCapturePoint::SetCapturePointData(GameObject* capturePoint)
{
    ASSERT(capturePoint);

    TC_LOG_DEBUG("bg.battlefield", "Creating capture point %u", capturePoint->GetEntry());

    m_capturePointGUID = ObjectGuid(HighGuid::GameObject, capturePoint->GetEntry(), capturePoint->GetGUID().GetCounter());

    // check info existence
    GameObjectTemplate const* goinfo = capturePoint->GetGOInfo();
    if (goinfo->type != GAMEOBJECT_TYPE_CAPTURE_POINT)
    {
        TC_LOG_ERROR("bg.battlefield", "SetCapturePointData: GO %u is not a capture point!", capturePoint->GetEntry());
        return false;
    }

    // get the needed values from goinfo
    m_maxValue = (float)goinfo->capturePoint.maxTime;
    m_maxSpeed = m_maxValue / (goinfo->capturePoint.minTime ? goinfo->capturePoint.minTime : 60);
    m_neutralValuePct = goinfo->capturePoint.neutralPercent;
    m_minValue = CalculatePct(m_maxValue, m_neutralValuePct);

    return true;
}

GameObject* BfCapturePoint::GetCapturePointGo()
{
    return m_Bf->GetGameObject(m_capturePointGUID);
}

bool BfCapturePoint::DelCapturePoint()
{
    if (m_capturePointGUID)
    {
        if (GameObject* capturePoint = m_Bf->GetGameObject(m_capturePointGUID))
        {
            capturePoint->SetRespawnTime(0);                  // not save respawn time
            capturePoint->Delete();
            capturePoint = nullptr;
        }
        m_capturePointGUID.Clear();
    }

    return true;
}

bool BfCapturePoint::Update(uint32 diff)
{
    GameObject* capturePoint = m_Bf->GetGameObject(m_capturePointGUID);
    if (!capturePoint)
        return false;

    float radius = (float)capturePoint->GetGOInfo()->capturePoint.radius/2;

    for (uint32 team = 0; team < 2; ++team)
    {
        for (GuidSet::iterator itr = m_activePlayers[team].begin(); itr != m_activePlayers[team].end();)
        {
            ObjectGuid playerGuid = *itr;
            ++itr;

            if (Player* player = ObjectAccessor::FindPlayer(playerGuid))
                if (!capturePoint->IsWithinDistInMap(player, radius) || !player->IsOutdoorPvPActive())
                    HandlePlayerLeave(player);
        }
    }

    std::list<Player*> players;
    Trinity::AnyPlayerInObjectRangeCheck checker(capturePoint, radius);
    Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(capturePoint, players, checker);
    Cell::VisitWorldObjects(capturePoint, searcher, radius);

    for (std::list<Player*>::iterator itr = players.begin(); itr != players.end(); ++itr)
    {
        Player* const player = *itr;
        if (player->IsOutdoorPvPActive())
        {
            if (m_activePlayers[player->GetTeamId()].insert(player->GetGUID()).second)
                HandlePlayerEnter(*itr);
        }
    }

    // get the difference of numbers
    float fact_diff = ((float)m_activePlayers[0].size() - (float)m_activePlayers[1].size()) * diff / BATTLEFIELD_OBJECTIVE_UPDATE_INTERVAL;
    if (!fact_diff)
        return false;

    uint32 Challenger = 0;
    float maxDiff = m_maxSpeed * diff;

    if (fact_diff < 0)
    {
        // horde is in majority, but it's already horde-controlled -> no change
        if (m_State == BF_CAPTUREPOINT_OBJECTIVESTATE_HORDE && m_value <= -m_maxValue)
            return false;

        if (fact_diff < -maxDiff)
            fact_diff = -maxDiff;

        Challenger = HORDE;
    }
    else
    {
        // ally is in majority, but it's already ally-controlled -> no change
        if (m_State == BF_CAPTUREPOINT_OBJECTIVESTATE_ALLIANCE && m_value >= m_maxValue)
            return false;

        if (fact_diff > maxDiff)
            fact_diff = maxDiff;

        Challenger = ALLIANCE;
    }

    float oldValue = m_value;
    //TeamId oldTeam = m_team;

    m_OldState = m_State;

    m_value += fact_diff;

    if (m_value < -m_minValue) // red
    {
        if (m_value < -m_maxValue)
            m_value = -m_maxValue;
        m_State = BF_CAPTUREPOINT_OBJECTIVESTATE_HORDE;
        m_team = TEAM_HORDE;
    }
    else if (m_value > m_minValue) // blue
    {
        if (m_value > m_maxValue)
            m_value = m_maxValue;
        m_State = BF_CAPTUREPOINT_OBJECTIVESTATE_ALLIANCE;
        m_team = TEAM_ALLIANCE;
    }
    else if (oldValue * m_value <= 0) // grey, go through mid point
    {
        // if challenger is ally, then n->a challenge
        if (Challenger == ALLIANCE)
            m_State = BF_CAPTUREPOINT_OBJECTIVESTATE_NEUTRAL_ALLIANCE_CHALLENGE;
        // if challenger is horde, then n->h challenge
        else if (Challenger == HORDE)
            m_State = BF_CAPTUREPOINT_OBJECTIVESTATE_NEUTRAL_HORDE_CHALLENGE;
        m_team = TEAM_NEUTRAL;
    }
    else // grey, did not go through mid point
    {
        // old phase and current are on the same side, so one team challenges the other
        if (Challenger == ALLIANCE && (m_OldState == BF_CAPTUREPOINT_OBJECTIVESTATE_HORDE || m_OldState == BF_CAPTUREPOINT_OBJECTIVESTATE_NEUTRAL_HORDE_CHALLENGE))
            m_State = BF_CAPTUREPOINT_OBJECTIVESTATE_HORDE_ALLIANCE_CHALLENGE;
        else if (Challenger == HORDE && (m_OldState == BF_CAPTUREPOINT_OBJECTIVESTATE_ALLIANCE || m_OldState == BF_CAPTUREPOINT_OBJECTIVESTATE_NEUTRAL_ALLIANCE_CHALLENGE))
            m_State = BF_CAPTUREPOINT_OBJECTIVESTATE_ALLIANCE_HORDE_CHALLENGE;
        m_team = TEAM_NEUTRAL;
    }

    if (m_value != oldValue)
        SendChangePhase();

    if (m_OldState != m_State)
    {
        //TC_LOG_ERROR("bg.battlefield", "%u->%u", m_OldState, m_State);
        ChangeState();
        ChangeTeam(m_team);
        return true;
    }

    return false;
}

void BfCapturePoint::SendUpdateWorldState(uint32 field, uint32 value)
{
    for (uint8 team = 0; team < PVP_TEAMS_COUNT; ++team)
        for (GuidSet::iterator itr = m_activePlayers[team].begin(); itr != m_activePlayers[team].end(); ++itr)  // send to all players present in the area
            if (Player* player = ObjectAccessor::FindPlayer(*itr))
                player->SendUpdateWorldState(field, value);
}

void BfCapturePoint::SendObjectiveComplete(uint32 id, ObjectGuid guid)
{
    uint8 team;
    switch (m_State)
    {
        case BF_CAPTUREPOINT_OBJECTIVESTATE_ALLIANCE:
            team = TEAM_ALLIANCE;
            break;
        case BF_CAPTUREPOINT_OBJECTIVESTATE_HORDE:
            team = TEAM_HORDE;
            break;
        default:
            return;
    }

    // send to all players present in the area
    for (GuidSet::iterator itr = m_activePlayers[team].begin(); itr != m_activePlayers[team].end(); ++itr)
        if (Player* player = ObjectAccessor::FindPlayer(*itr))
            player->KilledMonsterCredit(id, guid);
}

bool BfCapturePoint::IsInsideObjective(Player* player) const
{
    return m_activePlayers[player->GetTeamId()].find(player->GetGUID()) != m_activePlayers[player->GetTeamId()].end();
}
