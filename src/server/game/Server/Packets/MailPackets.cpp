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

#include "MailPackets.h"
#include "Item.h"
#include "Mail.h"
#include "Player.h"
#include "World.h"

WorldPackets::Mail::MailAttachedItem::MailAttachedItem(::Item const* item, uint8 pos)
{
    Position = pos;
    AttachID = item->GetGUID().GetCounter();
    ItemID = item->GetEntry();
    RandomPropertiesID = item->GetItemRandomPropertyId();
    RandomPropertiesSeed = item->GetItemSuffixFactor();
    Count = item->GetCount();
    Charges = item->GetSpellCharges();
    MaxDurability = item->GetUInt32Value(ITEM_FIELD_MAXDURABILITY);
    Durability = item->GetInt32Value(ITEM_FIELD_DURABILITY);
    Unlocked = !item->IsLocked();

    for (uint8 j = 0; j < MAX_INSPECTED_ENCHANTMENT_SLOT; j++)
    {
        EnchantmentSlot slot = EnchantmentSlot(j);
        EnchantmentID[slot] = item->GetEnchantmentId(slot);
        EnchantmentDuration[slot] = item->GetEnchantmentDuration(slot);
        EnchantmentCharges[slot] = item->GetEnchantmentCharges(slot);
    }
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::Mail::MailAttachedItem const& att)
{
    data << uint8(att.Position);
    data << int32(att.AttachID);
    data << int32(att.ItemID);
    for (uint8 i = 0; i < MAX_INSPECTED_ENCHANTMENT_SLOT; i++)
    {
        data << int32(att.EnchantmentID[i]);
        data << int32(att.EnchantmentDuration[i]);
        data << int32(att.EnchantmentCharges[i]);
    }
    data << int32(att.RandomPropertiesID);
    data << int32(att.RandomPropertiesSeed);
    data << int32(att.Count);
    data << int32(att.Charges);
    data << uint32(att.MaxDurability);
    data << int32(att.Durability);
    data << bool(att.Unlocked);

    return data;
}

void WorldPackets::Mail::MailGetList::Read()
{
    _worldPacket >> Mailbox;
}

void WorldPackets::Mail::MailCreateTextItem::Read()
{
    _worldPacket >> Mailbox;
    _worldPacket >> MailID;
}

void WorldPackets::Mail::SendMail::Read()
{
    _worldPacket >> Info.Mailbox;
    _worldPacket >> Info.Target;
    _worldPacket >> Info.Subject;
    _worldPacket >> Info.Body;
    _worldPacket >> Info.StationeryID;
    _worldPacket >> Info.PackageID;
    Info.Attachments.resize(_worldPacket.read<uint8>());

    for (auto& att : Info.Attachments)
    {
        _worldPacket >> att.AttachPosition;
        _worldPacket >> att.ItemGUID;
    }

    _worldPacket >> Info.SendMoney;
    _worldPacket >> Info.Cod;
    _worldPacket.read_skip<uint64>();
    _worldPacket.read_skip<uint8>();
}

void WorldPackets::Mail::MailReturnToSender::Read()
{
    _worldPacket >> Mailbox;
    _worldPacket >> MailID;
    _worldPacket >> SenderGUID;
}

WorldPacket const* WorldPackets::Mail::MailCommandResult::Write()
{
    _worldPacket << uint32(MailID);
    _worldPacket << uint32(Command);
    _worldPacket << uint32(ErrorCode);

    if (ErrorCode == MAIL_ERR_EQUIP_ERROR)
        _worldPacket << uint32(BagResult);

    if (Command == MAIL_ITEM_TAKEN)
    {
        if (ErrorCode == MAIL_OK || ErrorCode == MAIL_ERR_ITEM_HAS_EXPIRED)
        {
            _worldPacket << uint32(AttachID);
            _worldPacket << uint32(QtyInInventory);
        }
    }

    return &_worldPacket;
}

void WorldPackets::Mail::MailMarkAsRead::Read()
{
    _worldPacket >> Mailbox;
    _worldPacket >> MailID;
}

void WorldPackets::Mail::MailDelete::Read()
{
    _worldPacket >> Mailbox;
    _worldPacket >> MailID;
    _worldPacket >> DeleteReason;
}

void WorldPackets::Mail::MailTakeItem::Read()
{
    _worldPacket >> Mailbox;
    _worldPacket >> MailID;
    _worldPacket >> AttachID;
}

void WorldPackets::Mail::MailTakeMoney::Read()
{
    _worldPacket >> Mailbox;
    _worldPacket >> MailID;
}

WorldPacket const* WorldPackets::Mail::NotifyReceivedMail::Write()
{
    _worldPacket << float(Delay);

    return &_worldPacket;
}

WorldPacket const* WorldPackets::Mail::ShowMailbox::Write()
{
    _worldPacket << PostmasterGUID;

    return &_worldPacket;
}
