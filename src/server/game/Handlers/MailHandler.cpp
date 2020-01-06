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

#include "WorldSession.h"
#include "AccountMgr.h"
#include "CharacterCache.h"
#include "Chat.h"
#include "DatabaseEnv.h"
#include "DBCStores.h"
#include "GameTime.h"
#include "Item.h"
#include "Language.h"
#include "Log.h"
#include "Mail.h"
#include "MailMgr.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "Player.h"
#include "World.h"
#include "WorldPacket.h"

bool WorldSession::CanOpenMailBox(ObjectGuid guid)
{
    if (guid == _player->GetGUID())
    {
        if (!HasPermission(rbac::RBAC_PERM_COMMAND_MAILBOX))
        {
            TC_LOG_WARN("cheat", "%s attempted to open mailbox by using a cheat.", _player->GetName().c_str());
            return false;
        }
    }
    else if (guid.IsGameObject())
    {
        if (!_player->GetGameObjectIfCanInteractWith(guid, GAMEOBJECT_TYPE_MAILBOX))
            return false;
    }
    else if (guid.IsAnyTypeCreature())
    {
        if (!_player->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_MAILBOX))
            return false;
    }
    else
        return false;

    return true;
}

void WorldSession::HandleSendMail(WorldPacket& recvData)
{
    ObjectGuid mailbox, unk3;
    std::string receiverName, subject, body;
    uint32 stationery, package, money, COD;
    uint8 unk4;
    uint8 items_count;
    recvData >> mailbox >> receiverName >> subject >> body
             >> stationery                                 // stationery?
             >> package                                    // 0x00000000
             >> items_count;                               // attached items count

    if (!ObjectMgr::IsValidChannelName(receiverName))
        return;

    if (!subject.empty())
        if (!ObjectMgr::IsValidChannelName(subject))
            return;

    if (!body.empty())
        if (!ObjectMgr::IsValidChannelText(body))
            return;

    if (items_count > MAX_MAIL_ITEMS)                      // client limit
    {
        GetPlayer()->SendMailResult(0, MAIL_SEND, MAIL_ERR_TOO_MANY_ATTACHMENTS);
        recvData.rfinish();                   // set to end to avoid warnings spam
        return;
    }

    ObjectGuid itemGUIDs[MAX_MAIL_ITEMS];

    for (uint8 i = 0; i < items_count; ++i)
    {
        recvData.read_skip<uint8>();                       // item slot in mail, not used
        recvData >> itemGUIDs[i];
    }

    recvData >> money >> COD;                              // money and cod
    recvData >> unk3;                                      // const 0
    recvData >> unk4;                                      // const 0

    // packet read complete, now do check

    if (!CanOpenMailBox(mailbox))
        return;

    if (receiverName.empty())
        return;

    Player* player = _player;

    if (player->GetLevel() < sWorld->getIntConfig(CONFIG_MAIL_LEVEL_REQ))
    {
        SendNotification(GetTrinityString(LANG_MAIL_SENDER_REQ), sWorld->getIntConfig(CONFIG_MAIL_LEVEL_REQ));
        return;
    }

    ObjectGuid receiverGuid;
    if (normalizePlayerName(receiverName))
        receiverGuid = sCharacterCache->GetCharacterGuidByName(receiverName);

    if (!receiverGuid)
    {
        TC_LOG_INFO("network", "Player %u is sending mail to %s (GUID: non-existing!) with subject %s "
            "and body %s includes %u items, %u copper and %u COD copper with unk1 = %u, unk2 = %u",
            player->GetGUID().GetCounter(), receiverName.c_str(), subject.c_str(), body.c_str(),
            items_count, money, COD, stationery, package);
        player->SendMailResult(0, MAIL_SEND, MAIL_ERR_RECIPIENT_NOT_FOUND);
        return;
    }

    TC_LOG_INFO("network", "Player %u is sending mail to %s (%s) with subject %s and body %s "
        "including %u items, %u copper and %u COD copper with unk1 = %u, unk2 = %u",
        player->GetGUID().GetCounter(), receiverName.c_str(), receiverGuid.ToString().c_str(), subject.c_str(),
        body.c_str(), items_count, money, COD, stationery, package);

    if (player->GetGUID() == receiverGuid)
    {
        player->SendMailResult(0, MAIL_SEND, MAIL_ERR_CANNOT_SEND_TO_SELF);
        return;
    }

    uint32 cost = items_count ? 30 * items_count : 30;  // price hardcoded in client

    uint32 reqmoney = cost + money;

    // Check for overflow
    if (reqmoney < money)
    {
        player->SendMailResult(0, MAIL_SEND, MAIL_ERR_NOT_ENOUGH_MONEY);
        return;
    }

    if (!player->HasEnoughMoney(reqmoney) && !player->IsGameMaster())
    {
        player->SendMailResult(0, MAIL_SEND, MAIL_ERR_NOT_ENOUGH_MONEY);
        return;
    }

    Player* receiver = ObjectAccessor::FindConnectedPlayer(receiverGuid);

    uint32 receiverTeam = 0;
    uint8 mailsCount = sMailMgr->GetMailBoxSize(receiverGuid.GetCounter());                                  //do not allow to send to one player more than 100 mails
    uint8 receiverLevel = 0;
    uint32 receiverAccountId = 0;

    if (receiver)
    {
        receiverTeam = receiver->GetTeam();
        receiverLevel = receiver->GetLevel();
        receiverAccountId = receiver->GetSession()->GetAccountId();
    }
    else
    {
        if (CharacterCacheEntry const* characterInfo = sCharacterCache->GetCharacterCacheByGuid(receiverGuid))
        {
            receiverTeam = Player::TeamForRace(characterInfo->Race);
            receiverLevel = characterInfo->Level;
            receiverAccountId = characterInfo->AccountId;
        }
    }

    // do not allow to have more than 100 mails in mailbox.. mails count is in opcode uint8!!! - so max can be 255..
    if (mailsCount > 100)
    {
        player->SendMailResult(0, MAIL_SEND, MAIL_ERR_RECIPIENT_CAP_REACHED);
        return;
    }

    // test the receiver's Faction... or all items are account bound
    bool accountBound = items_count ? true : false;
    for (uint8 i = 0; i < items_count; ++i)
    {
        if (Item* item = player->GetItemByGuid(itemGUIDs[i]))
        {
            ItemTemplate const* itemProto = item->GetTemplate();
            if (!itemProto || !(itemProto->Flags & ITEM_FLAG_IS_BOUND_TO_ACCOUNT))
            {
                accountBound = false;
                break;
            }
        }
    }

    if (!accountBound && player->GetTeam() != receiverTeam && !HasPermission(rbac::RBAC_PERM_TWO_SIDE_INTERACTION_MAIL))
    {
        player->SendMailResult(0, MAIL_SEND, MAIL_ERR_NOT_YOUR_TEAM);
        return;
    }

    if (receiverLevel < sWorld->getIntConfig(CONFIG_MAIL_LEVEL_REQ))
    {
        SendNotification(GetTrinityString(LANG_MAIL_RECEIVER_REQ), sWorld->getIntConfig(CONFIG_MAIL_LEVEL_REQ));
        return;
    }

    Item* items[MAX_MAIL_ITEMS];

    for (uint8 i = 0; i < items_count; ++i)
    {
        if (!itemGUIDs[i])
        {
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_MAIL_ATTACHMENT_INVALID);
            return;
        }

        Item* item = player->GetItemByGuid(itemGUIDs[i]);

        // prevent sending bag with items (cheat: can be placed in bag after adding equipped empty bag to mail)
        if (!item)
        {
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_MAIL_ATTACHMENT_INVALID);
            return;
        }

        if (!item->CanBeTraded(true))
        {
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_EQUIP_ERROR, EQUIP_ERR_MAIL_BOUND_ITEM);
            return;
        }

        if (item->IsBoundAccountWide() && item->IsSoulBound() && player->GetSession()->GetAccountId() != receiverAccountId)
        {
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_EQUIP_ERROR, EQUIP_ERR_ARTEFACTS_ONLY_FOR_OWN_CHARACTERS);
            return;
        }

        if ((item->GetTemplate()->Flags & ITEM_FLAG_CONJURED) || item->GetUInt32Value(ITEM_FIELD_DURATION))
        {
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_EQUIP_ERROR, EQUIP_ERR_MAIL_BOUND_ITEM);
            return;
        }

        if (COD && item->HasFlag(ITEM_FIELD_FLAGS, ITEM_FIELD_FLAG_WRAPPED))
        {
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_CANT_SEND_WRAPPED_COD);
            return;
        }

        if (item->IsNotEmptyBag())
        {
            player->SendMailResult(0, MAIL_SEND, MAIL_ERR_EQUIP_ERROR, EQUIP_ERR_CAN_ONLY_DO_WITH_EMPTY_BAGS);
            return;
        }

        items[i] = item;
    }

    // Check for spamming
    if (!UpdateAntispamCount())
    {
        player->SendMailResult(0, MAIL_SEND, MAIL_ERR_INTERNAL_ERROR);
        SendNotification(GetTrinityString(LANG_ANTISPAM_ERROR), sWorld->getIntConfig(CONFIG_ANTISPAM_MAIL_COUNT));
        return;
    }

    player->SendMailResult(0, MAIL_SEND, MAIL_OK);

    player->ModifyMoney(-int32(reqmoney));
    player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_MAIL, cost);

    bool needItemDelay = false;

    std::list<Item*> maillist;
    SQLTransaction trans = CharacterDatabase.BeginTransaction();

    if (items_count > 0 || money > 0)
    {
        bool log = HasPermission(rbac::RBAC_PERM_LOG_GM_TRADE);
        if (items_count > 0)
        {
            for (uint8 i = 0; i < items_count; ++i)
            {
                Item* item = items[i];
                if (log)
                {
                    sLog->outCommand(GetAccountId(), "GM %s (GUID: %u) (Account: %u) mail item: %s (Entry: %u Count: %u) "
                        "to: %s (%s) (Account: %u)", GetPlayerName().c_str(), GetGUIDLow(), GetAccountId(),
                        item->GetTemplate()->Name1.c_str(), item->GetEntry(), item->GetCount(),
                        receiverName.c_str(), receiverGuid.ToString().c_str(), receiverAccountId);
                }

                item->SetNotRefundable(GetPlayer()); // makes the item no longer refundable
                player->MoveItemFromInventory(items[i]->GetBagSlot(), item->GetSlot(), true);

                item->DeleteFromInventoryDB(trans);     // deletes item from character's inventory
                item->SetOwnerGUID(receiverGuid);
                item->SetState(ITEM_CHANGED);
                item->SaveToDB(trans);                  // recursive and not have transaction guard into self, item not in inventory and can be save standalone

                maillist.push_back(item);
            }

            // if item send to character at another account, then apply item delivery delay
            needItemDelay = player->GetSession()->GetAccountId() != receiverAccountId;
        }

        if (log && money > 0)
        {
            sLog->outCommand(GetAccountId(), "GM %s (GUID: %u) (Account: %u) mail money: %u to: %s (%s) (Account: %u)",
                GetPlayerName().c_str(), GetGUIDLow(), GetAccountId(), money, receiverName.c_str(), receiverGuid.ToString().c_str(), receiverAccountId);
        }
    }

    // If theres is an item, there is a one hour delivery delay if sent to another account's character.
    uint32 deliver_delay = needItemDelay ? sWorld->getIntConfig(CONFIG_MAIL_DELIVERY_DELAY) : 0;

    // don't ask for COD if there are no items
    if (items_count == 0)
        COD = 0;

    // will delete item or place to receiver mail list
    player->SaveInventoryAndGoldToDB(trans);
    CharacterDatabase.CommitTransaction(trans);

    if (items_count)
        sMailMgr->SendMailWithItemsBy(player, receiverGuid.GetCounter(), subject, body, money ? money : 0, maillist, body.empty() ? MAIL_CHECK_MASK_COPIED : MAIL_CHECK_MASK_HAS_BODY, deliver_delay, COD);
    else
        sMailMgr->SendMailBy(player, receiverGuid.GetCounter(), subject, body, money ? money : 0, body.empty() ? MAIL_CHECK_MASK_COPIED : MAIL_CHECK_MASK_HAS_BODY, deliver_delay, COD);

    maillist.clear();
}

//called when mail is read
void WorldSession::HandleMailMarkAsRead(WorldPacket& recvData)
{
    ObjectGuid mailbox;
    uint32 mailId;
    recvData >> mailbox;
    recvData >> mailId;

    if (!CanOpenMailBox(mailbox))
        return;

    Player* player = _player;

    if (!sMailMgr->HandleMailMarkAsRead(mailId))
        return;

    if (player->unReadMails)
        --player->unReadMails;

    //player->m_mailsUpdated = true;
}

//called when client deletes mail
void WorldSession::HandleMailDelete(WorldPacket& recvData)
{
    ObjectGuid mailbox;
    uint32 mailId;
    recvData >> mailbox;
    recvData >> mailId;
    recvData.read_skip<uint32>();                          // mailTemplateId

    if (!CanOpenMailBox(mailbox))
        return;

    Player* player = _player;

    if (sMailMgr->HandleMailDelete(mailId))
        player->SendMailResult(mailId, MAIL_DELETED, MAIL_OK);
    else
        player->SendMailResult(mailId, MAIL_DELETED, MAIL_ERR_INTERNAL_ERROR);
}

void WorldSession::HandleMailReturnToSender(WorldPacket& recvData)
{
    ObjectGuid mailbox;
    uint32 mailId;
    recvData >> mailbox;
    recvData >> mailId;
    recvData.read_skip<uint64>();                          // original sender GUID for return to, not used

    if (!CanOpenMailBox(mailbox))
        return;

    Player* player = _player;

    switch (sMailMgr->HandleMailReturnToSender(mailId))
    {
        case 0:
            player->SendMailResult(mailId, MAIL_RETURNED_TO_SENDER, MAIL_ERR_INTERNAL_ERROR);
            break;
        case 1: break;
            GetPlayer()->SendMailResult(0, MAIL_SEND, MAIL_ERR_RECIPIENT_CAP_REACHED);
            break;
        case 2:
            player->SendMailResult(mailId, MAIL_RETURNED_TO_SENDER, MAIL_OK);
            break;
        default:
            break;
    }
}

//called when player takes item attached in mail
void WorldSession::HandleMailTakeItem(WorldPacket& recvData)
{
    ObjectGuid mailbox;
    uint32 mailId;
    uint32 itemId;
    recvData >> mailbox;
    recvData >> mailId;
    recvData >> itemId;                                    // item guid low

    if (!CanOpenMailBox(mailbox))
        return;

    Player* player = _player;
    uint8 msg_result = 0;
    uint32 count = 0;
    switch (sMailMgr->HandleMailTakeItem(player, mailId, itemId, count, msg_result))
    {
        case 0:
            player->SendMailResult(mailId, MAIL_ITEM_TAKEN, MAIL_ERR_INTERNAL_ERROR);
            break;
        case 1:
            player->SendMailResult(mailId, MAIL_ITEM_TAKEN, MAIL_ERR_NOT_ENOUGH_MONEY);
            break;
        case 2:
            player->SendMailResult(mailId, MAIL_ITEM_TAKEN, MAIL_OK, 0, itemId, count);
            break;
        case 3:
            player->SendMailResult(mailId, MAIL_ITEM_TAKEN, MAIL_ERR_EQUIP_ERROR, msg_result);
            break;
        default:
            break;
    }    
}

void WorldSession::HandleMailTakeMoney(WorldPacket& recvData)
{
    ObjectGuid mailbox;
    uint32 mailId;
    recvData >> mailbox;
    recvData >> mailId;

    if (!CanOpenMailBox(mailbox))
        return;

    Player* player = _player;
    sMailMgr->HandleMailTakeMoney(player, mailId);
}

//called when player lists his received mails
void WorldSession::HandleGetMailList(WorldPacket& recvData)
{
    ObjectGuid mailbox;
    recvData >> mailbox;

    if (!CanOpenMailBox(mailbox))
        return;

    Player* player = _player;

    WorldPacket data(SMSG_MAIL_LIST_RESULT, (200));         // guess size
    sMailMgr->HandleGetMailList(player, data);
    SendPacket(&data);

    // recalculate m_nextMailDelivereTime and unReadMails
    _player->UpdateNextMailTimeAndUnreads();
}

//used when player copies mail body to his inventory
void WorldSession::HandleMailCreateTextItem(WorldPacket& recvData)
{
    ObjectGuid mailbox;
    uint32 mailId;

    recvData >> mailbox;
    recvData >> mailId;

    if (!CanOpenMailBox(mailbox))
        return;

    Player* player = _player;

    sMailMgr->HandleMailCreateTextItem(player, mailId);    
}

/// @todo Fix me! ... this void has probably bad condition, but good data are sent
void WorldSession::HandleQueryNextMailTime(WorldPacket & /*recvData*/)
{
    WorldPacket data(MSG_QUERY_NEXT_MAIL_TIME, 8);

    if (_player->unReadMails > 0)
    {
        if (!sMailMgr->HandleQueryNextMailTime(_player, data))
        {
            data << float(-DAY);
            data << uint32(0);
        }
    }
    else
    {
        data << float(-DAY);
        data << uint32(0);
    }

    SendPacket(&data);
}
