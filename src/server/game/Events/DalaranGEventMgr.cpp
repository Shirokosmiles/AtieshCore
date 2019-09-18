/*
 * Copyright (C) 2019+ ATieshCore <https://at-wow.org/>
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

#include "Chat.h"
#include "DalaranGEventMgr.h"
#include "Group.h"
#include "Guild.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "RBAC.h"
#include "Language.h"
#include "Log.h"
#include "WorldSession.h"

enum EventTypes
{
    EVENT_START_PREPARING_TO_START  = 1,
    EVENT_START_BEGIN_START         = 2,
    EVENT_START_DONT_ENOUGHT        = 3,

    EVENT_STOP_DURATION_FIGHT       = 4,
    EVENT_STOP_SUCCESS_FIGHT        = 5,
    EVENT_STOP_RETURN_PLAYERS       = 6,
};

DalaranGEventMgr* DalaranGEventMgr::instance()
{
    static DalaranGEventMgr instance;
    return &instance;
}

uint32 DalaranGEventMgr::GetCountPlayerInEvent()
{
    uint32 count = _playersDataStore.size();
    return count;
}

void DalaranGEventMgr::Update(uint32 diff)
{
    if (!sWorld->getBoolConfig(CONFIG_DALARAN_GAME_EVENTS))
        return;

    m_UpdateTimer += diff;

    _events.Update(diff);

    if (!IsActiveEvent())
    {
        if (_registration && !_announce60 && m_UpdateTimer >= (sWorld->getIntConfig(CONFIG_DALARAN_GAME_EVENTS_TIMER) * IN_MILLISECONDS * MINUTE) - (IN_MILLISECONDS * MINUTE))
        {
            sWorld->SendWorldText(LANG_DALARAN_CRATER_ANNOUNCE_BEFORE_START_60);
            _announce60 = true;
        }

        if (_registration && !_announce30 && m_UpdateTimer >= (sWorld->getIntConfig(CONFIG_DALARAN_GAME_EVENTS_TIMER) * IN_MILLISECONDS * MINUTE) - (IN_MILLISECONDS * (MINUTE / 2)))
        {
            sWorld->SendWorldText(LANG_DALARAN_CRATER_ANNOUNCE_BEFORE_START_30);
            _announce30 = true;
        }

        if (_registration && m_UpdateTimer >= sWorld->getIntConfig(CONFIG_DALARAN_GAME_EVENTS_TIMER) * IN_MILLISECONDS * MINUTE)
        {
            m_UpdateTimer = 0;

            if (GetCountPlayerInEvent() < sWorld->getIntConfig(CONFIG_DALARAN_GAME_EVENTS_MIN_PLAYERS))
                _events.ScheduleEvent(EVENT_START_DONT_ENOUGHT, 0);
            else
                _events.ScheduleEvent(EVENT_START_PREPARING_TO_START, 0);
        }
    }
    else if (alivePlayerCount == 1)
        _events.ScheduleEvent(EVENT_STOP_SUCCESS_FIGHT, 0);

    if (m_DurationTimer > 0)
    {
        if (diff >= m_DurationTimer)
        {
            m_DurationTimer = 0;
            sWorld->SendWorldText(LANG_DALARAN_CRATER_PREPARE_TO_STOP_ANNOUNCE, GetCountPlayerInEvent());
            _events.ScheduleEvent(EVENT_STOP_DURATION_FIGHT, 1min);
        }
        else
            m_DurationTimer -= diff;
    }

    while (uint32 eventId = _events.ExecuteEvent())
    {
        switch (eventId)
        {
            case EVENT_START_PREPARING_TO_START:
            {
                TeleportAllPlayersInZone();
                BroadcastToMemberPrepare();
                _events.ScheduleEvent(EVENT_START_BEGIN_START, 30s);
                break;
            }
            case EVENT_START_BEGIN_START:
            {
                sWorld->SendWorldText(LANG_DALARAN_CRATER_START_ANNOUNCE);
                StartEvent();
                break;
            }
            case EVENT_START_DONT_ENOUGHT:
            {
                _events.Reset();
                sWorld->SendWorldText(LANG_DALARAN_CRATER_NOT_ENOGH_MIN_PLAYERS);
                break;
            }
            case EVENT_STOP_DURATION_FIGHT:
            {
                sWorld->SendWorldText(LANG_DALARAN_CRATER_DURATION_STOP_ANNOUNCE);
                StopEvent();
                break;
            }
            case EVENT_STOP_SUCCESS_FIGHT:
            {
                ReceiveWinnerName();
                sWorld->SendWorldText(LANG_DALARAN_CRATER_SUCCESS_STOP_ANNOUNCE, _winnername.c_str());
                StopEvent();
                break;
            }
            case EVENT_STOP_RETURN_PLAYERS:
            {
                _events.Reset();
                TeleportAllPlayersBack();
                break;
            }
            default:
                break;
        }
    }
}

void DalaranGEventMgr::StartEvent()
{
    _activeFight = true;
    _events.Reset();
    m_DurationTimer = sWorld->getIntConfig(CONFIG_DALARAN_GAME_EVENTS_DURATION_TIMER) * IN_MILLISECONDS * MINUTE;
    for (PlayersDataContainer::const_iterator itr = _playersDataStore.begin(); itr != _playersDataStore.end(); ++itr)
    {
        if (Player* player = ObjectAccessor::FindConnectedPlayer(itr->second.guid))
            player->SetByteFlag(UNIT_FIELD_BYTES_2, UNIT_BYTES_2_OFFSET_PVP_FLAG, UNIT_BYTE2_FLAG_FFA_PVP);
    }
}

void DalaranGEventMgr::StopEvent()
{
    _activeFight = false;
    _events.Reset();
    m_DurationTimer = 0;
    alivePlayerCount = 0;

    sWorld->SendWorldText(LANG_DALARAN_CRATER_PREPARE_TO_RETURN_PLAYERS);
    _events.ScheduleEvent(EVENT_STOP_RETURN_PLAYERS, 45s);

    if (!sWorld->IsFFAPvPRealm())
    {
        for (PlayersDataContainer::const_iterator itr = _playersDataStore.begin(); itr != _playersDataStore.end(); ++itr)
        {
            if (Player* player = ObjectAccessor::FindConnectedPlayer(itr->second.guid))
                player->RemoveByteFlag(UNIT_FIELD_BYTES_2, UNIT_BYTES_2_OFFSET_PVP_FLAG, UNIT_BYTE2_FLAG_FFA_PVP);
        }
    }
}

void DalaranGEventMgr::SpawnGOLight()
{
    for (PlayersDataContainer::const_iterator itr = _playersDataStore.begin(); itr != _playersDataStore.end(); ++itr)
    {
        if (Player * player = ObjectAccessor::FindConnectedPlayer(itr->second.guid))
        {
            QuaternionData rotation = QuaternionData::fromEulerAnglesZYX(player->GetOrientation(), 0.f, 0.f);
            player->SummonGameObject(182483, DalaranCraterPoint, rotation, sWorld->getIntConfig(CONFIG_DALARAN_GAME_EVENTS_DURATION_TIMER) * IN_MILLISECONDS * MINUTE);
        }
    }    
}

void DalaranGEventMgr::TeleportAllPlayersInZone()
{
    _registration = false;

    for (PlayersDataContainer::const_iterator itr = _playersDataStore.begin(); itr != _playersDataStore.end(); ++itr)
    {
        if (Player * player = ObjectAccessor::FindConnectedPlayer(itr->second.guid))
        {
            if (!player->IsAlive())
            {
                ChatHandler(player->GetSession()).PSendSysMessage(LANG_DALARAN_CRATER_LEAVE_PLAYER_NOT_ALIVE);
                continue;
            }

            if (player->GetGroup())
            {
                if (player->GetGroup()->isRaidGroup())
                    player->GetGroup()->RemoveMember(itr->second.guid);
                else if (!sWorld->getBoolConfig(CONFIG_DALARAN_GAME_EVENTS_SQUAD_ENABLED))
                    player->GetGroup()->RemoveMember(itr->second.guid);
            }

            player->TeleportTo(DalaranCrater);
            player->CastSpell(player, 59200, true);

            ++alivePlayerCount;
        }        
    }

    SpawnGOLight();
}

void DalaranGEventMgr::TeleportAllPlayersBack()
{
    for (PlayersDataContainer::const_iterator itr = _playersDataStore.begin(); itr != _playersDataStore.end(); ++itr)
    {
        if (Player* player = ObjectAccessor::FindConnectedPlayer(itr->second.guid))
        {
            uint32 mapid = itr->second.mapid;
            float x = itr->second.x;
            float y = itr->second.y;
            float z = itr->second.z;
            player->ResurrectPlayer(player->GetSession()->HasPermission(rbac::RBAC_PERM_RESURRECT_WITH_FULL_HPS) ? 1.0f : 0.5f);
            player->TeleportTo(mapid, x, y, z, player->GetOrientation());
        }
    }

    _playersDataStore.clear();    
    _registration = true;
    _announce60 = false;
    _announce30 = false;
    m_UpdateTimer = 0;
    gameTimeNextEvent = uint32(GameTime::GetGameTime() + sWorld->getIntConfig(CONFIG_DALARAN_GAME_EVENTS_TIMER) * MINUTE);
}

void DalaranGEventMgr::BroadcastToMemberAboutLeavePlayer(std::string const& Name)
{
    for (PlayersDataContainer::const_iterator itr = _playersDataStore.begin(); itr != _playersDataStore.end(); ++itr)
    {
        if (Player* player = ObjectAccessor::FindConnectedPlayer(itr->second.guid))
            ChatHandler(player->GetSession()).PSendSysMessage(LANG_DALARAN_CRATER_LEAVE_PLAYER_AND_COUNT, Name, alivePlayerCount);
    }
}

void DalaranGEventMgr::BroadcastToMemberPrepare()
{
    for (PlayersDataContainer::const_iterator itr = _playersDataStore.begin(); itr != _playersDataStore.end(); ++itr)
    {
        if (Player * player = ObjectAccessor::FindConnectedPlayer(itr->second.guid))
            ChatHandler(player->GetSession()).PSendSysMessage(LANG_DALARAN_CRATER_START_ANNOUNCE_30_SEC, GetCountPlayerInEvent());
    }
}

bool DalaranGEventMgr::IsMemberOfEvent(Player* player)
{
    for (PlayersDataContainer::const_iterator itr = _playersDataStore.begin(); itr != _playersDataStore.end(); ++itr)
    {
        if (itr->second.guid == player->GetGUID())
            return true;
    }

    return false;
}

void DalaranGEventMgr::RemovePlayerFromFight(Player* player, bool withteleport)
{
    if (!IsMemberOfEvent(player))
        return;

    bool found = false;
    for (PlayersDataContainer::const_iterator itr = _playersDataStore.begin(); itr != _playersDataStore.end(); ++itr)
    {
        if (itr->second.guid == player->GetGUID())
        {
            if (Player* player = ObjectAccessor::FindConnectedPlayer(itr->second.guid))
            {
                if (withteleport)
                {
                    uint32 mapid = itr->second.mapid;
                    float x = itr->second.x;
                    float y = itr->second.y;
                    float z = itr->second.z;
                    player->TeleportTo(mapid, x, y, z, player->GetOrientation());
                    if (!sWorld->IsFFAPvPRealm())
                        player->RemoveByteFlag(UNIT_FIELD_BYTES_2, UNIT_BYTES_2_OFFSET_PVP_FLAG, UNIT_BYTE2_FLAG_FFA_PVP);
                }

                found = true;
                break;
            }
        }
    }

    if (found)
    {
        RemovePlayerFromQueue(player);
        --alivePlayerCount;

        BroadcastToMemberAboutLeavePlayer(player->GetName());
    }    
}

void DalaranGEventMgr::ReceiveWinnerName()
{
    for (PlayersDataContainer::const_iterator itr = _playersDataStore.begin(); itr != _playersDataStore.end(); ++itr)
    {
        if (Player* player = ObjectAccessor::FindConnectedPlayer(itr->second.guid))
            if (player->IsAlive())
            {
                _winnername = player->GetName();
                player->RewardPVPCap();
                if (player->GetGuild())
                {
                    player->GetGuild()->AddGuildExp(15, player, true);
                    player->GetGuild()->UpdateGuildRating(2, true, player);
                }
                break;
            }
    }
}

void DalaranGEventMgr::InvitePlayerToQueue(Player* player)
{
    PlayersData pd;
    pd.guid = player->GetGUID();
    pd.mapid = player->GetMapId();
    pd.x = player->GetPositionX();
    pd.y = player->GetPositionY();
    pd.z = player->GetPositionZ();

    // find max id
    uint32 new_id = 0;
    for (PlayersDataContainer::const_iterator itr = _playersDataStore.begin(); itr != _playersDataStore.end(); ++itr)
        if (itr->first > new_id)
            new_id = itr->first;

    // use next
    ++new_id;
    // add in active player list of event
    _playersDataStore[new_id] = pd;
}

void DalaranGEventMgr::RemovePlayerFromQueue(Player* player)
{
    if (!IsMemberOfEvent(player))
        return;

    uint32 id = 0;
    for (PlayersDataContainer::const_iterator itr = _playersDataStore.begin(); itr != _playersDataStore.end(); ++itr)
    {
        if (Player * player = ObjectAccessor::FindConnectedPlayer(itr->second.guid))
        {
            id = itr->first;
            break;
        }
    }

    _playersDataStore.erase(id);
}
