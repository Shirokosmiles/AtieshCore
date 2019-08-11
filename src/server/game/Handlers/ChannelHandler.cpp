/*
 * Copyright (C) 2016-2019 AtieshCore <https://at-wow.org/>
 * Copyright (C) 2008-2019 TrinityCore <https://www.trinitycore.org/>
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

#include "WorldSession.h"
#include "Channel.h"
#include "ChannelMgr.h"
#include "DBCStores.h"
#include "Log.h"
#include "ObjectMgr.h"                                      // for normalizePlayerName
#include "Player.h"
#include <cctype>
#include <utf8.h>

static size_t const MAX_CHANNEL_PASS_STR = 31;

void WorldSession::HandleJoinChannel(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_JOIN_CHANNEL started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_JOIN_CHANNEL handler not in world return");
        recvPacket.rfinish();
        return;
    }

    uint32 channelId;
    uint8 unknown1, unknown2;
    std::string channelName, password;

    recvPacket >> channelId >> unknown1 >> unknown2 >> channelName >> password;

    if (channelName.empty() && !channelId)
    {
        TC_LOG_DEBUG("chat.system", "CMSG_JOIN_CHANNEL handler No id and empty name");
        recvPacket.rfinish();
        return;
    }

    if (!channelName.empty())
    {
        // Filter for message
        if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
        {
            TC_LOG_DEBUG("chat.system", "CMSG_JOIN_CHANNEL handler bad message from IsValidityChecks");
            recvPacket.rfinish();
            return;
        }

        // Filter for message
        if (!ObjectMgr::IsValidChannelName(channelName))
        {
            TC_LOG_DEBUG("chat.system", "CMSG_JOIN_CHANNEL handler bad message from IsValidChannelName");
            recvPacket.rfinish();
            return;
        }
        
    }

    if (!password.empty())
    {
        // Filter for message
        if (!ObjectMgr::IsValidityChecks(GetPlayer(), password))
        {
            TC_LOG_DEBUG("chat.system", "CMSG_JOIN_CHANNEL handler bad message from password IsValidityChecks");
            recvPacket.rfinish();
            return;
        }

        // Filter for message
        if (!ObjectMgr::IsValidChannelName(password))
        {
            TC_LOG_DEBUG("chat.system", "CMSG_JOIN_CHANNEL handler bad message from password IsValidChannelName");
            recvPacket.rfinish();
            return;
        }        
    }

    if (!ValidateHyperlinksAndMaybeKick(channelName))
        return;

    TC_LOG_DEBUG("chat.system", "CMSG_JOIN_CHANNEL %s Channel: %u, unk1: %u, unk2: %u, channel: %s, password: %s",
        GetPlayerInfo().c_str(), channelId, unknown1, unknown2, channelName.c_str(), password.c_str());

    AreaTableEntry const* zone = sAreaTableStore.LookupEntry(GetPlayer()->GetZoneId());
    if (channelId)
    {
        ChatChannelsEntry const* channel = sChatChannelsStore.LookupEntry(channelId);
        if (!channel)
        {
            recvPacket.rfinish();
            return;
        }

        if (!zone || !GetPlayer()->CanJoinConstantChannelInZone(channel, zone))
        {
            recvPacket.rfinish();
            return;
        }
    }

    if (channelName.empty() || isdigit((unsigned char)channelName[0]))
    {
        WorldPacket data(SMSG_CHANNEL_NOTIFY, 1 + channelName.size());
        data << uint8(CHAT_INVALID_NAME_NOTICE) << channelName;
        SendPacket(&data);
        recvPacket.rfinish();
        return;
    }

    if (ChannelMgr* cMgr = ChannelMgr::forTeam(GetPlayer()->GetCFSTeam()))
    {
        if (channelId)
        { // system channel
            if (Channel* channel = cMgr->GetSystemChannel(channelId, zone))
                channel->JoinChannel(GetPlayer());
        }
        else
        { // custom channel
            if (Channel* channel = cMgr->GetCustomChannel(channelName))
                channel->JoinChannel(GetPlayer(), password);
            else if (Channel* channel = cMgr->CreateCustomChannel(channelName))
            {
                channel->SetPassword(password);
                channel->JoinChannel(GetPlayer(), password);
            }
        }
    TC_LOG_DEBUG("chat.system", "CMSG_JOIN_CHANNEL finished handler all is OK");
    }
}

void WorldSession::HandleLeaveChannel(WorldPacket& recvPacket)
{
    uint32 channelId;
    std::string channelName;
    recvPacket >> channelId >> channelName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_LEAVE_CHANNEL handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_LEAVE_CHANNEL handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    if (channelName.empty() && !channelId)
    {
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "CMSG_LEAVE_CHANNEL %s Channel: %s, channelId: %u",
        GetPlayerInfo().c_str(), channelName.c_str(), channelId);

    AreaTableEntry const* zone = sAreaTableStore.LookupEntry(GetPlayer()->GetZoneId());
    if (channelId)
    {
        TC_LOG_DEBUG("chat.system", "CMSG_LEAVE_CHANNEL handler AreaTableEntry");
        ChatChannelsEntry const* channel = sChatChannelsStore.LookupEntry(channelId);
        if (!channel)
        {
            TC_LOG_DEBUG("chat.system", "CMSG_LEAVE_CHANNEL handler 3 return");
            recvPacket.rfinish();
            return;
        }

        if (!zone || !GetPlayer()->CanJoinConstantChannelInZone(channel, zone))
        {
            TC_LOG_DEBUG("chat.system", "CMSG_LEAVE_CHANNEL handler 4 return");
            recvPacket.rfinish();
            return;
        }
    }

    if (ChannelMgr* cMgr = ChannelMgr::forTeam(GetPlayer()->GetCFSTeam()))
    {
        if (Channel* channel = cMgr->GetChannel(channelId, channelName, GetPlayer(), true, zone))
            channel->LeaveChannel(GetPlayer(), true);

        if (channelId)
            cMgr->LeftChannel(channelId, zone);
    }

    TC_LOG_DEBUG("chat.system", "CMSG_LEAVE_CHANNEL finished handler all is OK");
}

void WorldSession::HandleChannelList(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_LIST started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_LIST handler not in world return");
        recvPacket.rfinish();
        return;
    }

    std::string channelName;
    recvPacket >> channelName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_LIST handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_LIST handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "%s %s Channel: %s",
        recvPacket.GetOpcode() == CMSG_CHANNEL_DISPLAY_LIST ? "CMSG_CHANNEL_DISPLAY_LIST" : "CMSG_CHANNEL_LIST",
        GetPlayerInfo().c_str(), channelName.c_str());

    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
        channel->List(GetPlayer());

    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_LIST finished handler all is OK");
}

void WorldSession::HandleChannelPassword(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_PASSWORD started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_PASSWORD handler not in world return");
        recvPacket.rfinish();
        return;
    }

    std::string channelName, password;
    recvPacket >> channelName >> password;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_PASSWORD handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_PASSWORD handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    if (!password.empty())
    {
        // Filter for message
        if (!ObjectMgr::IsValidityChecks(GetPlayer(), password))
        {
            TC_LOG_DEBUG("chat.system", "CMSG_JOIN_CHANNEL handler bad message from password IsValidityChecks");
            recvPacket.rfinish();
            return;
        }

        // Filter for message
        if (!ObjectMgr::IsValidChannelName(password))
        {
            TC_LOG_DEBUG("chat.system", "CMSG_JOIN_CHANNEL handler bad message from password IsValidChannelName");
            recvPacket.rfinish();
            return;
        }
    }

    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_PASSWORD %s Channel: %s, Password: %s",
        GetPlayerInfo().c_str(), channelName.c_str(), password.c_str());

    if (password.length() > MAX_CHANNEL_PASS_STR)
    {
        recvPacket.rfinish();
        return;
    }

    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
        channel->Password(GetPlayer(), password);
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_PASSWORD finished handler all is OK");
}

void WorldSession::HandleChannelSetOwner(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_SET_OWNER started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_SET_OWNER handler not in world return");
        recvPacket.rfinish();
        return;
    }
    std::string channelName, targetName;
    recvPacket >> channelName >> targetName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_SET_OWNER handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_SET_OWNER handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_SET_OWNER %s Channel: %s, Target: %s",
        GetPlayerInfo().c_str(), channelName.c_str(), targetName.c_str());

    if (!normalizePlayerName(targetName))
    {
        recvPacket.rfinish();
        return;
    }

    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
        channel->SetOwner(GetPlayer(), targetName);
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_SET_OWNER finished handler all is OK");
}

void WorldSession::HandleChannelOwner(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_OWNER started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_OWNER handler not in world return");
        recvPacket.rfinish();
        return;
    }
    std::string channelName;
    recvPacket >> channelName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_OWNER handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_OWNER handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_OWNER %s Channel: %s",
        GetPlayerInfo().c_str(), channelName.c_str());

    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
        channel->SendWhoOwner(GetPlayer()->GetGUID());
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_OWNER finished handler all is OK");
}

void WorldSession::HandleChannelModerator(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_MODERATOR started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_MODERATOR handler not in world return");
        recvPacket.rfinish();
        return;
    }
    std::string channelName, targetName;
    recvPacket >> channelName >> targetName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_MODERATOR handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_MODERATOR handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_MODERATOR %s Channel: %s, Target: %s",
        GetPlayerInfo().c_str(), channelName.c_str(), targetName.c_str());

    if (!normalizePlayerName(targetName))
    {
        recvPacket.rfinish();
        return;
    }

    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
        channel->SetModerator(GetPlayer(), targetName);
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_MODERATOR finished handler all is OK");
}

void WorldSession::HandleChannelUnmoderator(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNMODERATOR started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNMODERATOR handler not in world return");
        recvPacket.rfinish();
        return;
    }
    std::string channelName, targetName;
    recvPacket >> channelName >> targetName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNMODERATOR handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNMODERATOR handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNMODERATOR %s Channel: %s, Target: %s",
        GetPlayerInfo().c_str(), channelName.c_str(), targetName.c_str());

    if (!normalizePlayerName(targetName))
    {
        recvPacket.rfinish();
        return;
    }

    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
        channel->UnsetModerator(GetPlayer(), targetName);
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNMODERATOR finished handler all is OK");
}

void WorldSession::HandleChannelMute(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_MUTE started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_MUTE handler not in world return");
        recvPacket.rfinish();
        return;
    }
    std::string channelName, targetName;
    recvPacket >> channelName >> targetName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_MUTE handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_MUTE handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_MUTE %s Channel: %s, Target: %s",
        GetPlayerInfo().c_str(), channelName.c_str(), targetName.c_str());

    if (!normalizePlayerName(targetName))
    {
        recvPacket.rfinish();
        return;
    }

    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
        channel->SetMute(GetPlayer(), targetName);
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_MUTE finished handler all is OK");
}

void WorldSession::HandleChannelUnmute(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNMUTE started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNMUTE handler not in world return");
        recvPacket.rfinish();
        return;
    }
    std::string channelName, targetName;
    recvPacket >> channelName >> targetName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNMUTE handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNMUTE handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNMUTE %s Channel: %s, Target: %s",
        GetPlayerInfo().c_str(), channelName.c_str(), targetName.c_str());

    if (!normalizePlayerName(targetName))
    {
        recvPacket.rfinish();
        return;
    }

    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
        channel->UnsetMute(GetPlayer(), targetName);
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNMUTE finished handler all is OK");
}

void WorldSession::HandleChannelInvite(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_INVITE started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_INVITE handler not in world return");
        recvPacket.rfinish();
        return;
    }
    std::string channelName, targetName;
    recvPacket >> channelName >> targetName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_INVITE handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_INVITE handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_INVITE %s Channel: %s, Target: %s",
        GetPlayerInfo().c_str(), channelName.c_str(), targetName.c_str());

    if (!normalizePlayerName(targetName))
    {
        recvPacket.rfinish();
        return;
    }

    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
        channel->Invite(GetPlayer(), targetName);
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_INVITE finished handler all is OK");
}

void WorldSession::HandleChannelKick(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_KICK started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_KICK handler not in world return");
        recvPacket.rfinish();
        return;
    }
    std::string channelName, targetName;
    recvPacket >> channelName >> targetName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_KICK handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_KICK handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_KICK %s Channel: %s, Target: %s",
        GetPlayerInfo().c_str(), channelName.c_str(), targetName.c_str());

    if (!normalizePlayerName(targetName))
    {
        recvPacket.rfinish();
        return;
    }

    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
        channel->Kick(GetPlayer(), targetName);
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_KICK finished handler all is OK");
}

void WorldSession::HandleChannelBan(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_BAN started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_BAN handler not in world return");
        recvPacket.rfinish();
        return;
    }
    std::string channelName, targetName;
    recvPacket >> channelName >> targetName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_BAN handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_BAN handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_BAN %s Channel: %s, Target: %s",
        GetPlayerInfo().c_str(), channelName.c_str(), targetName.c_str());

    if (!normalizePlayerName(targetName))
    {
        recvPacket.rfinish();
        return;
    }

    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
        channel->Ban(GetPlayer(), targetName);
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_BAN finished handler all is OK");
}

void WorldSession::HandleChannelUnban(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNBAN started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNBAN handler not in world return");
        recvPacket.rfinish();
        return;
    }
    std::string channelName, targetName;
    recvPacket >> channelName >> targetName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNBAN handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNBAN handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNBAN %s Channel: %s, Target: %s",
        GetPlayerInfo().c_str(), channelName.c_str(), targetName.c_str());

    if (!normalizePlayerName(targetName))
    {
        recvPacket.rfinish();
        return;
    }

    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
        channel->UnBan(GetPlayer(), targetName);
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_UNBAN finished handler all is OK");
}

void WorldSession::HandleChannelAnnouncements(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_ANNOUNCEMENTS started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_ANNOUNCEMENTS handler not in world return");
        recvPacket.rfinish();
        return;
    }
    std::string channelName;
    recvPacket >> channelName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_ANNOUNCEMENTS handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_ANNOUNCEMENTS handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_ANNOUNCEMENTS %s Channel: %s",
        GetPlayerInfo().c_str(), channelName.c_str());

    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
        channel->Announce(GetPlayer());
    TC_LOG_DEBUG("chat.system", "CMSG_CHANNEL_ANNOUNCEMENTS finished handler all is OK");
}

void WorldSession::HandleChannelDisplayListQuery(WorldPacket &recvPacket)
{
    // this should be OK because the 2 function _were_ the same
    HandleChannelList(recvPacket);
}

void WorldSession::HandleGetChannelMemberCount(WorldPacket &recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_GET_CHANNEL_MEMBER_COUNT started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_GET_CHANNEL_MEMBER_COUNT handler not in world return");
        recvPacket.rfinish();
        return;
    }
    std::string channelName;
    recvPacket >> channelName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_GET_CHANNEL_MEMBER_COUNT handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_GET_CHANNEL_MEMBER_COUNT handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "CMSG_GET_CHANNEL_MEMBER_COUNT %s Channel: %s",
        GetPlayerInfo().c_str(), channelName.c_str());

    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
    {
        TC_LOG_DEBUG("chat.system", "SMSG_CHANNEL_MEMBER_COUNT %s Channel: %s Count: %u",
            GetPlayerInfo().c_str(), channelName.c_str(), channel->GetNumPlayers());

        std::string name = channel->GetName(GetSessionDbcLocale());
        WorldPacket data(SMSG_CHANNEL_MEMBER_COUNT, name.size() + 1 + 4);
        data << name;
        data << uint8(channel->GetFlags());
        data << uint32(channel->GetNumPlayers());
        SendPacket(&data);
    }
    TC_LOG_DEBUG("chat.system", "CMSG_GET_CHANNEL_MEMBER_COUNT finished handler all is OK");
}

void WorldSession::HandleSetChannelWatch(WorldPacket &recvPacket)
{
    TC_LOG_DEBUG("chat.system", "CMSG_SET_CHANNEL_WATCH started handler");
    if (!GetPlayer() || !GetPlayer()->IsInWorld() || GetPlayer()->IsLoading() || GetPlayer()->GetSession()->PlayerLogout())
    {
        TC_LOG_DEBUG("chat.system", "CMSG_SET_CHANNEL_WATCH handler not in world return");
        recvPacket.rfinish();
        return;
    }
    std::string channelName;
    recvPacket >> channelName;

    // Filter for message
    if (!ObjectMgr::IsValidityChecks(GetPlayer(), channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_GET_CHANNEL_MEMBER_COUNT handler bad message from IsValidityChecks");
        recvPacket.rfinish();
        return;
    }

    // Filter for message
    if (!ObjectMgr::IsValidChannelName(channelName))
    {
        TC_LOG_DEBUG("chat.system", "CMSG_GET_CHANNEL_MEMBER_COUNT handler bad message from IsValidChannelName");
        recvPacket.rfinish();
        return;
    }

    TC_LOG_DEBUG("chat.system", "CMSG_SET_CHANNEL_WATCH %s Channel: %s",
        GetPlayerInfo().c_str(), channelName.c_str());

    TC_LOG_DEBUG("chat.system", "CMSG_SET_CHANNEL_WATCH finished handler all is OK");
    /*
    if (Channel* channel = ChannelMgr::GetChannelForPlayerByNamePart(channelName, GetPlayer()))
        channel->JoinNotify(GetPlayer());
    */
}
