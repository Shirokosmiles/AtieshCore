/*
 * Copyright (C) 2016-2019 AtieshCore <https://at-wow.org/>
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

#include "AccountMgr.h"
#include "AuctionHouseMgr.h"
#include "Battleground.h"
#include "Chat.h"
#include "Item.h"
#include "Player.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"

 // Vanish System
void Player::SetVanishTimer()
{
    m_vanishTimer = sWorld->getIntConfig(CONFIG_VANISH_VISION_TIMER);
    m_breakblevanishTimer = sWorld->getIntConfig(CONFIG_VANISH_CC_BREAK_TIMER);
    m_visiblevanish = true;
    m_breakablevanish = true;
}

void Player::StopVanish()
{
    m_vanishTimer = m_breakblevanishTimer;
}

bool Player::CanSeeVFD(WorldObject const* obj) const
{
    if (Player const* seerPlayer = obj->ToPlayer())
        if (seerPlayer->UnderVisibleVanish())
            return true;

    return false;
}

 // Auction info
void Player::CalculateAuctionLotsCounter()
{
    uint32 count = 0;
    if (AuctionHouseObject * AllianceauctionHouse = sAuctionMgr->GetAuctionsMapByHouseId(AUCTIONHOUSE_ALLIANCE))
        AllianceauctionHouse->BuildListAllLots(this, count);

    if (AuctionHouseObject * AllianceauctionHouse = sAuctionMgr->GetAuctionsMapByHouseId(AUCTIONHOUSE_HORDE))
        AllianceauctionHouse->BuildListAllLots(this, count);

    if (AuctionHouseObject * AllianceauctionHouse = sAuctionMgr->GetAuctionsMapByHouseId(AUCTIONHOUSE_NEUTRAL))
        AllianceauctionHouse->BuildListAllLots(this, count);

    TC_LOG_DEBUG("chatmessage", "Player: CalculateAuctionLotsCounter - Player (%s) has %u lots in all auctions", GetName().c_str(), count);
    m_auctionlots = count;
}

// ItemPresent settings
void Player::InstallItemPresentBySlot(uint32 entry)
{
    ItemPresentList const* accessories = sObjectMgr->GetItemPresentList(entry);
    if (!accessories)
        return;

    for (ItemPresentList::const_iterator itr = accessories->begin(); itr != accessories->end(); ++itr)
        if (itr->ItemPresentSlot == entry)
            InstallItemPresent(itr->ItemPresentSlot, itr->ItemId, itr->Count);
}

void Player::InstallItemPresent(uint32 entry, uint32 itemId, uint32 count)
{
    TC_LOG_DEBUG("entities.player", "Player (Guid: %u) %s: installing itempresent (Entry: %u) for item %u",
        GetGUID().GetCounter(), GetName().c_str(), entry, itemId);

    ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(itemId);
    if (!itemTemplate)
        return;

    if (!AddItem(itemId, count))
        TC_LOG_DEBUG("entities.player", "Player (Guid: %u) %s: did not received itempresent (Entry: %u) for item %u",
            GetGUID().GetCounter(), GetName().c_str(), entry, itemId);
}

// VIP system
void Player::SetPremiumStatus(bool vipstatus)
{
    m_vip = vipstatus;
    if (m_vip)
        m_premiumTimer = 1000 * MINUTE;
    else
        m_premiumTimer = 0;
}

uint32 Player::GetVerifiedCoins()
{
    uint32 coinsCount = GetCoins();
    if (GetSession())
    {
        uint32 coinsFromDB;
        // it's nessesary, if we will change coins count through web-site or some another way, and player will in-game in this time
        coinsFromDB = AccountMgr::GetCoins(GetSession()->GetAccountId());
        if (coinsCount != coinsFromDB)
        {
            coinsCount = coinsFromDB;
            SetCoins(coinsCount);
        }
    }

    return coinsCount;
}

// GeatScore formula
uint32 Player::GetGearScore() const
{
    uint8 R = 0;    // rare (uint)
    float Q = 0.0f; // quility
    float W = 0.0f; // slot cost - worth
    float A = 0.0f; // coefficent A
    float B = 0.0f; // coefficent B
    float itemlevel = 0.0f;
    uint32 itemGS = 0;
    uint32 fullGS = 0;
    for (int i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
    {
        if (i == EQUIPMENT_SLOT_HEAD || i == EQUIPMENT_SLOT_CHEST || i == EQUIPMENT_SLOT_LEGS || i == EQUIPMENT_SLOT_MAINHAND || i == EQUIPMENT_SLOT_OFFHAND)
            W = 1.0f;
        else if (i == EQUIPMENT_SLOT_SHOULDERS || i == EQUIPMENT_SLOT_WAIST || i == EQUIPMENT_SLOT_FEET || i == EQUIPMENT_SLOT_HANDS)
            W = 0.75f;
        else if (i == EQUIPMENT_SLOT_NECK || i == EQUIPMENT_SLOT_WRISTS || i == EQUIPMENT_SLOT_LEGS ||
            i == EQUIPMENT_SLOT_FINGER1 || i == EQUIPMENT_SLOT_FINGER2 || i == EQUIPMENT_SLOT_TRINKET1 || i == EQUIPMENT_SLOT_TRINKET2 ||
            i == EQUIPMENT_SLOT_BACK)
            W = 0.5625f;
        else if (i == EQUIPMENT_SLOT_RANGED)
            W = 0.3164f;
        else if (i == EQUIPMENT_SLOT_TABARD || i == EQUIPMENT_SLOT_BODY)
            W = 0.0f;

        if (m_items[i] && m_items[i]->GetTemplate())
        {
            switch (m_items[i]->GetTemplate()->Quality)
            {
            case ITEM_QUALITY_POOR:
            case ITEM_QUALITY_NORMAL:
                R = 2;
                Q = 0.005f;
                break;
            case ITEM_QUALITY_UNCOMMON:
            case ITEM_QUALITY_RARE:
                R = 2;
                Q = 1.0f;
                break;
            case ITEM_QUALITY_EPIC:
                R = 4;
                Q = 1.0f;
                break;
            case ITEM_QUALITY_LEGENDARY:
                R = 4;
                Q = 1.3f;
                break;
            case ITEM_QUALITY_ARTIFACT: // idk about this
            case ITEM_QUALITY_HEIRLOOM:
                R = 3;
                Q = 1.0f;
                break;
            }

            if (m_items[i]->GetTemplate()->InventoryType == INVTYPE_2HWEAPON)
                W = 2.0f;

            itemlevel = m_items[i]->GetTemplate()->ItemLevel;
            if (itemlevel > 120.0f)
            {
                switch (R)
                {
                case 4: A = 91.45f; B = 0.6500f; break;
                case 3: A = 81.37f; B = 0.8125f; break;
                case 2: A = 73.00f; B = 1.0f; break;
                default:
                    break;
                }
            }
            else
            {
                switch (R)
                {
                case 4: A = 26.0f; B = 1.2f; break;
                case 3: A = 0.75f; B = 1.8f; break;
                case 2: A = 8.0f; B = 2.0f; break;
                case 1: A = 0.0f; B = 1.2f; break;
                default:
                    break;
                }
            }

            itemGS = 1.8618 * W * Q * (itemlevel - A) / B;
            fullGS += itemGS;
            //TC_LOG_ERROR("server", "GetGearScore :  slot = %i, itemGS = %u", i, itemGS);
        }
    }
    //TC_LOG_ERROR("server", "GetGearScore = %u", fullGS);
    return fullGS;
}

// AT talent spec info
uint8 Player::GetMostPointsTalentTree() const
{
    uint32 specPoints[3] = { 0, 0, 0 };
    for (uint32 talentId = 0; talentId < sTalentStore.GetNumRows(); ++talentId)
    {
        TalentEntry const* talentInfo = sTalentStore.LookupEntry(talentId);

        if (!talentInfo)
            continue;

        TalentTabEntry const* talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);

        if (!talentTabInfo)
            continue;

        if (talentTabInfo->tabpage < 3)
        {
            for (uint8 rank = 0; rank < MAX_TALENT_RANK; ++rank)
            {
                PlayerTalentMap::iterator plrTalent = m_talents[m_activeSpec]->find(talentInfo->RankID[rank]);
                if (plrTalent != m_talents[m_activeSpec]->end())
                    if (plrTalent->second->state != PLAYERSPELL_REMOVED)
                        specPoints[talentTabInfo->tabpage] += rank;
            }
        }
    }
    //TC_LOG_ERROR("server", "talents :  1tab = %u, 2tab = %u, 3tab = %u", specPoints[0], specPoints[1], specPoints[2]);
    uint8 maxIndex = 0;
    uint8 maxCount = specPoints[0];
    for (uint8 i = 1; i < 3; ++i)
        if (specPoints[i] > maxCount)
        {
            maxIndex = i;
            maxCount = specPoints[i];
        }
    return maxIndex;
}

bool Player::IsHealerTalentSpec() const
{
    uint8 tree = GetMostPointsTalentTree();
    return ((GetClass() == CLASS_DRUID && tree == 2) || (GetClass() == CLASS_PALADIN && tree == 0) || (GetClass() == CLASS_PRIEST && tree <= 1) || (GetClass() == CLASS_SHAMAN && tree == 2));
}

bool Player::IsTankTalentSpec() const
{
    uint8 tree = GetMostPointsTalentTree();
    return ((GetClass() == CLASS_WARRIOR && tree == 2) || (GetClass() == CLASS_DRUID && tree == 1 && HasAura(33856)) || (GetClass() == CLASS_PALADIN && tree == 1) || (GetClass() == CLASS_DEATH_KNIGHT && tree == 1));
}

// PVP Weekly Bonus Cap reward
void Player::SetPVPCapPoints(uint32 cap, bool weeklyupdate)
{
    if (!sWorld->getBoolConfig(CONFIG_PVP_REWARD))
        return;

    uint32 maxcap = sWorld->getIntConfig(CONFIG_PVP_REWARD_MAXCAP);
    if (cap > maxcap)
        cap = maxcap;

    m_pvpcap = cap;

    if (weeklyupdate)
    {
        m_pvpcapReceived = false;
        if (GetSession())
            ChatHandler(GetSession()).PSendSysMessage("Your Weekly Arena Cap was reseted");
    }
    else
    {
        if (cap < 1500)
            m_pvpcapReceived = false;
        else
            m_pvpcapReceived = true;

        if (GetSession())
            ChatHandler(GetSession()).PSendSysMessage("Your Weekly Arena Cap was updated : ( %u / %u )", m_pvpcap, maxcap);
    }
}

void Player::RewardPVPCapPoints(uint32 reward)
{
    if (!sWorld->getBoolConfig(CONFIG_PVP_REWARD))
        return;

    if (m_pvpcapReceived)
        return;

    uint32 maxcap = sWorld->getIntConfig(CONFIG_PVP_REWARD_MAXCAP);
    m_pvpcap += reward;

    if (m_pvpcap >= maxcap)
    {
        m_pvpcap = maxcap;
        RewardPVPCap();
    }

    if (GetSession())
        ChatHandler(GetSession()).PSendSysMessage("Your Weekly Arena Cap was updated : ( %u / %u )", m_pvpcap, maxcap);
}

void Player::RewardPVPCap()
{
    m_pvpcapReceived = true;
    uint32 quility = 0;
    if (GetAverageItemLevel() >= 270.0f)
        quility = 1;
    else if (GetAverageItemLevel() >= 251.0f)
        quility = 2;
    else
        quility = 3;

    uint32 count = 1;
    uint32 entryreward = 0;
    uint8 randomlevel = urand(0, 1);

    switch (randomlevel) // if 0 - mounts/and others, if 1 - items
    {
        case 0:
        {
            entryreward = 49426;
            count = 15;
            break;
        }
        case 1:
        {
            switch (GetClass())
            {
                case CLASS_WARRIOR:
                {
                    uint32 item_list_1[15] = { 51543, 51545, 51541, 51542, 51554, 51364, 51362, 51363, 51354, 51356, 51358, uint32((GetCFSTeam() == ALLIANCE ? 51377 : 51378)), 51353, 51355, 51357 };
                    uint32 item_list_2[14] = { 40829, 40870, 40790, 40810, 40850, 40890, 40883, 40884, 42081, 42082, 42119, 46374, 42041, 42042 };
                    uint32 item_list_3[5] = { 40826, 40866, 40789, 40807, 40847 };

                    switch (quility)
                    {
                        case 1: entryreward = item_list_1[urand(0, 14)]; break;
                        case 2: entryreward = item_list_2[urand(0, 13)]; break;
                        case 3: entryreward = item_list_3[urand(0, 4)]; break;
                    }
                    break;
                }
                case CLASS_PALADIN:
                {
                    if (IsHealerTalentSpec())
                    {
                        uint32 item_list_1[21] = { 51470, 51473, 51468, 51469, 51471, 51361, 51359, 51360, 51472, 51334, 51348, 51330, 51346, 51332, 51336, 51335, 51349, 51331, 51347, 51333, uint32((GetCFSTeam() == ALLIANCE ? 51377 : 51378)) };
                        uint32 item_list_2[20] = { 40934, 40964, 40910, 40928, 40940, 40984, 40978, 40949, 42616, 42078, 42080, 42076, 42079, 42077, 42118, 42044, 42046, 42043, 42047, 42045 };
                        uint32 item_list_3[6] = { 40933, 40963, 40907, 40927, 40939, 42615 };

                        switch (quility)
                        {
                        case 1: entryreward = item_list_1[urand(0, 20)]; break;
                        case 2: entryreward = item_list_2[urand(0, 19)]; break;
                        case 3: entryreward = item_list_3[urand(0, 5)]; break;
                        }
                    }
                    else // Retribution or Prot =)
                    {
                        uint32 item_list_1[16] = { 51476, 51479, 51474, 51475, 51477, 51364, 51362, 51363, 51478, 51354, 51356, 51358, 51353, 51355, 51357, uint32((GetCFSTeam() == ALLIANCE ? 51377 : 51378)) };
                        uint32 item_list_2[15] = { 40831, 40872, 40792, 40812, 40852, 40890, 40883, 40884, 42854, 42081, 42082, 42119, 46374, 42041, 42042 };
                        uint32 item_list_3[6] = { 40828, 40869, 40788, 40808, 40849, 42853 };

                        switch (quility)
                        {
                            case 1: entryreward = item_list_1[urand(0, 15)]; break;
                            case 2: entryreward = item_list_2[urand(0, 14)]; break;
                            case 3: entryreward = item_list_3[urand(0, 5)]; break;
                        }
                    }
                    break;
                }
                case CLASS_HUNTER:
                {
                    uint32 item_list_1[15] = { 51460, 51462, 51458, 51459, 51461, 51352, 51350, 51351, 51354, 51356, 51358, 51353, 51355, 51357, uint32((GetCFSTeam() == ALLIANCE ? 51377 : 51378)) };
                    uint32 item_list_2[13] = { 41158, 41218, 41088, 41144, 41206, 41226, 41236, 41231, 42081, 42082, 46374, 42041, 42042 };
                    uint32 item_list_3[5] = { 41157, 41217, 41087, 41143, 41205 };

                    switch (quility)
                    {
                        case 1: entryreward = item_list_1[urand(0, 14)]; break;
                        case 2: entryreward = item_list_2[urand(0, 12)]; break;
                        case 3: entryreward = item_list_3[urand(0, 4)]; break;
                    }
                    break;
                }
                case CLASS_ROGUE:
                {
                    uint32 item_list_1[15] = { 51494, 51496, 51492, 51493, 51495, 51370, 51368, 51369, 51354, 51356, 51358, 51353, 51355, 51357, uint32((GetCFSTeam() == ALLIANCE ? 51377 : 51378)) };
                    uint32 item_list_2[14] = { 41673, 41684, 41651, 41768, 41656, 41841, 41833, 41837, 42081, 42082, 46374, 42041, 42042, 42119 };
                    uint32 item_list_3[5] = { 41672, 41683, 41650, 41767, 41655 };

                    switch (quility)
                    {
                        case 1: entryreward = item_list_1[urand(0, 14)]; break;
                        case 2: entryreward = item_list_2[urand(0, 13)]; break;
                        case 3: entryreward = item_list_3[urand(0, 4)]; break;
                    }
                    break;
                }
                case CLASS_PRIEST:
                {
                    // back2 42078, 42080, 42076, 42079, 42077, - ring 42118 - neck 42044, 42046, 42043, 42047, 42045
                    uint32 item_list_1[31] = { 51484, 51486, 51482, 51483, 51485, 51489, 51491, 51487, 51488, 51490, 51329, 51327, 51328, 51367, 51365, 51366, 51339, 51337, 51338, 51334, 51348, 51330, 51346, 51332, 51336, 51335, 51349, 51331, 51347, 51333, uint32((GetCFSTeam() == ALLIANCE ? 51377 : 51378)) };
                    uint32 item_list_2[30] = { 41855, 41870, 41860, 41875, 41865, 41916, 41935, 41922, 41941, 41928, 41910, 41899, 41904, 41894, 41882, 41886, 49181, 49179, 49183, 42078, 42080, 42076, 42079, 42077, 42118, 42044, 42046, 42043, 42047, 42045 };
                    uint32 item_list_3[10] = { 41854, 41869, 41859, 41874, 41864, 41915, 41934, 41921, 41940, 41927 };

                    switch (quility)
                    {
                        case 1: entryreward = item_list_1[urand(0, 30)]; break;
                        case 2: entryreward = item_list_2[urand(0, 29)]; break;
                        case 3: entryreward = item_list_3[urand(0, 9)]; break;
                    }
                    break;
                }
                case CLASS_DEATH_KNIGHT:
                {
                    // stat A8: 51354, 51356, 51358, 51353, 51355, 51357
                    // stat A7: 42081, 42082, 42119, 46374, 42041, 42042
                    uint32 item_list_1[16] = { 51415, 51418, 51413, 51414, 51416, 51364, 51362, 51363, 51417, 51354, 51356, 51358, 51353, 51355, 51357, uint32((GetCFSTeam() == ALLIANCE ? 51377 : 51378)) };
                    uint32 item_list_2[15] = { 40830, 40871, 40791, 40811, 40851, 40890, 40883, 40884, 42622, 42081, 42082, 42119, 46374, 42041, 42042 };
                    uint32 item_list_3[6] = { 40827, 40868, 40787, 40809, 40848, 42621 };

                    switch (quility)
                    {
                        case 1: entryreward = item_list_1[urand(0, 15)]; break;
                        case 2: entryreward = item_list_2[urand(0, 14)]; break;
                        case 3: entryreward = item_list_3[urand(0, 5)]; break;
                    }
                    break;
                }
                case CLASS_SHAMAN:
                {
                    uint32 item_list_1[42] = { 51511, 51514, 51509, 51510, 51512, // elem
                        51505, 51508, 51530, 51504, 51506, //enh
                        51499, 51502, 51497, 51498, 51500, // restor
                        51376, 51374, 51375, 51373, 51371, 51372, 51352, 51350, 51351, //off-set
                        51334, 51348, 51330, 51346, 51332, 51336, 51335, 51349, 51331, 51347, 51333, 51354, 51356, 51358, 51353, 51355, 51357, uint32((GetCFSTeam() == ALLIANCE ? 51377 : 51378)) };
                    uint32 item_list_2[50] = { 41020, 41045, 40995, 41008, 41034, // elem
                        41152, 41212, 41082, 41138, 41200, // enh
                        41014, 41039, 40994, 41002, 41028, //restor
                        41066, 41071, 41076, 41061, 41052, 41056, 41226, 41236, 41231, //off-set
                        41910, 41899, 41904, 41894, 41882, 41886, 49181, 49179, 49183, 42078, 42080, 42076, 42079, 42077, 42118, 42044, 42046, 42043, 42047, 42045, 42081, 42082, 42119, 46374, 42041, 42042 };
                    uint32 item_list_3[15] = { 41019, 41044, 40993, 41007, 41033, 41151, 41211, 41081, 41137, 41199, 41013, 41038, 40992, 41001, 41027 };

                    switch (quility)
                    {
                        case 1: entryreward = item_list_1[urand(0, 41)]; break;
                        case 2: entryreward = item_list_2[urand(0, 49)]; break;
                        case 3: entryreward = item_list_3[urand(0, 14)]; break;
                    }
                    break;
                }
                case CLASS_MAGE:
                {
                    // spell A8: 51329, 51327, 51328, 51367, 51365, 51366, 51339, 51337, 51338, back 51334, 51348, 51330, 51346, 51332, ring 51336, neck 51335, 51349, 51331, 51347, 51333, 
                    // spell A7: 41910, 41899, 41904, 41894, 41882, 41886, 49181, 49179, 49183, back 42078, 42080, 42076, 42079, 42077, ring 42118, neck 42044, 42046, 42043, 42047, 42045, 
                    uint32 item_list_1[26] = { 51465, 51467, 51463, 51464, 51466, 51329, 51327, 51328, 51367, 51365, 51366, 51339, 51337, 51338, 51334, 51348, 51330, 51346, 51332, 51336, 51335, 51349, 51331, 51347, 51333, uint32((GetCFSTeam() == ALLIANCE ? 51377 : 51378)) };
                    uint32 item_list_2[25] = { 41947, 41966, 41954, 41972, 41960, 41910, 41899, 41904, 41894, 41882, 41886, 49181, 49179, 49183, 42078, 42080, 42076, 42079, 42077, 42118, 42044, 42046, 42043, 42047, 42045 };
                    uint32 item_list_3[5] = { 41946, 41965, 41953, 41971, 41959 };

                    switch (quility)
                    {
                        case 1: entryreward = item_list_1[urand(0, 25)]; break;
                        case 2: entryreward = item_list_2[urand(0, 24)]; break;
                        case 3: entryreward = item_list_3[urand(0, 4)]; break;
                    }
                    break;
                }
                case CLASS_WARLOCK:
                {
                    uint32 item_list_1[26] = { 51538, 51540, 51536, 51537, 51539, 51329, 51327, 51328, 51367, 51365, 51366, 51339, 51337, 51338, 51334, 51348, 51330, 51346, 51332, 51336, 51335, 51349, 51331, 51347, 51333, uint32((GetCFSTeam() == ALLIANCE ? 51377 : 51378)) };
                    uint32 item_list_2[25] = { 41994, 42012, 41999, 42018, 42006, 41910, 41899, 41904, 41894, 41882, 41886, 49181, 49179, 49183, 42078, 42080, 42076, 42079, 42077, 42118, 42044, 42046, 42043, 42047, 42045 };
                    uint32 item_list_3[5] = { 41993, 42011, 41998, 42017, 42005 };

                    switch (quility)
                    {
                        case 1: entryreward = item_list_1[urand(0, 25)]; break;
                        case 2: entryreward = item_list_2[urand(0, 24)]; break;
                        case 3: entryreward = item_list_3[urand(0, 4)]; break;
                    }
                    break;
                }
                case CLASS_DRUID:
                {
                    uint32 item_list_1[54] = { 51435, 51438, 51433, 51434, 51436, 51421, 51424, 51419, 51420, 51422, 51427, 51430, 51425, 51426, 51428, 51345, 51343, 51344, 51342, 51340, 51341, 51370, 51368, 51369, 51429, 51437, 51423, 51329, 51327, 51328, 51367, 51365, 51366, 51339, 51337, 51338, 51334, 51348, 51330, 51346, 51332, 51336, 51335, 51349, 51331, 51347, 51333,51354, 51356, 51358, 51353, 51355, 51357, uint32((GetCFSTeam() == ALLIANCE ? 51377 : 51378)) };
                    uint32 item_list_2[44] = { 41328, 41282, 41317, 41294, 41305, 41679, 41716, 41662, 41774, 41668, 41322, 41276, 41311, 41288, 41299, 41641, 41631, 41636, 41626, 41618, 41622, 41841, 41833, 41837, 42591, 42585, 42580, 42078, 42080, 42076, 42079, 42077, 42118, 42044, 42046, 42043, 42047, 42045, 42081, 42082, 42119, 46374, 42041, 42042 };
                    uint32 item_list_3[18] = { 41327, 41281, 41316, 41293, 41304, 41678, 41715, 41661, 41773, 41667, 41321, 41275, 41310, 41287, 41298, 42589, 42584, 42579 };

                    switch (quility)
                    {
                        case 1: entryreward = item_list_1[urand(0, 53)]; break;
                        case 2: entryreward = item_list_2[urand(0, 43)]; break;
                        case 3: entryreward = item_list_3[urand(0, 17)]; break;
                    }
                    break;
                }
            }

            break;
        }
    }

    if (entryreward)
    {
        if (!AddItem(entryreward, count))
            SendItemRetrievalMail(entryreward, count);
    }
}

void Player::RewardTitleForRating(uint16 rating)
{
    uint32 title = 0;
    if (rating >= 2400)
        title = 9;
    else if (rating >= 2200)
        title = 8;
    else if (rating >= 2000)
        title = 7;
    else if (rating >= 1900)
        title = 6;
    else if (rating >= 1800)
        title = 5;
    else if (rating >= 1700)
        title = 4;
    else if (rating >= 1600)
        title = 3;
    else if (rating >= 1500)
        title = 2;
    else if (rating >= 1400)
        title = 1;

    switch (title)
    {
        case 9: title = GetCFSTeam() == ALLIANCE ? GRAND_MARSHAL : HIGH_WARLORD; break;
        case 8: title = GetCFSTeam() == ALLIANCE ? FIELD_MARSHAL : WARLORD; break;
        case 7: title = GetCFSTeam() == ALLIANCE ? MARSHAL : GENERAL; break;
        case 6: title = GetCFSTeam() == ALLIANCE ? COMMANDER : LIEUTENANT_GENERAL; break;
        case 5: title = GetCFSTeam() == ALLIANCE ? LIEUTENANT_COMMANDER : CHAMPION; break;
        case 4: title = GetCFSTeam() == ALLIANCE ? KNIGHT_CHAMPION : CENTURION; break;
        case 3: title = GetCFSTeam() == ALLIANCE ? KNIGHT_CAPTAIN : LEGIONNAIRE; break;
        case 2: title = GetCFSTeam() == ALLIANCE ? KNIGHT_LIEUTENANT : BLOOD_GUARD; break;
        case 1: title = GetCFSTeam() == ALLIANCE ? KNIGHT : STONE_GUARD; break;
        default:
            break;
    }

    if (!title)
        return;

    if (CharTitlesEntry const* titleEntry = sCharTitlesStore.LookupEntry(title))
    {
        if (!HasTitle(titleEntry))
            SetTitle(titleEntry);
    }
}

void Player::RewardTitleForKills(uint32 kills)
{
    uint32 title = 0;
    switch (kills)
    {
        //case 50000: title = 6; break; - this rank working with achievment in 100k HK
        case 4000: title = 5; break;
        case 2000: title = 4; break;
        case 1000: title = 3; break;
        case 500: title = 2; break;
        case 100: title = 1; break;
        default:
            break;
    }

    switch (title)
    {
        //case 6: title = GetCFSTeam() == ALLIANCE ? OF_THE_ALLIANCE : OF_THE_HORDE; break;
        case 5: title = GetCFSTeam() == ALLIANCE ? SERGEANT_MAJOR : FIRST_SERGEANT; break;
        case 4: title = GetCFSTeam() == ALLIANCE ? MASTER_SERGEANT : SENIOR_SERGEANT; break;
        case 3: title = GetCFSTeam() == ALLIANCE ? SERGEANT : SERGEANT_H; break;
        case 2: title = GetCFSTeam() == ALLIANCE ? CORPORAL : GRUNT; break;
        case 1: title = GetCFSTeam() == ALLIANCE ? PRIVATE : SCOUT; break;
        default:
            break;
    }

    if (!title)
        return;

    if (CharTitlesEntry const* titleEntry = sCharTitlesStore.LookupEntry(title))
    {
        if (!HasTitle(titleEntry))
            SetTitle(titleEntry);
    }
}

// ArenaSpectator
void Player::SetSelection(ObjectGuid guid)
{
    m_curSelection = guid;
    SetGuidValue(UNIT_FIELD_TARGET, guid);
    if (Player * target = ObjectAccessor::FindPlayer(guid))
    {
        if (HaveSpectators())
        {
            SpectatorAddonMsg msg;
            msg.SetPlayer(GetName());
            msg.SetTarget(target->GetName());
            SendSpectatorAddonMsgToBG(msg);
        }
    }
}

void Player::SetSpectate(bool on)
{
    if (on)
    {
        SetSpeedRate(MOVE_RUN, 3.0f);
        spectatorFlag = true;

        m_ExtraFlags |= PLAYER_EXTRA_GM_ON;
        SetFaction(35);

        if (Pet* pet = GetPet())
            RemovePet(pet, PET_SAVE_NOT_IN_SLOT, true);

        UnsummonPetTemporaryIfAny();

        RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
        ResetContestedPvP();

        //getHostileRefManager().setOnlineOfflineState(false);
        CombatStopWithPets();

        SetDisplayId(22984);
        m_serverSideVisibility.SetValue(SERVERSIDE_VISIBILITY_GM, SEC_ADMINISTRATOR);
    }
    else
    {
        uint32 newPhase = 0;
        AuraEffectList const& phases = GetAuraEffectsByType(SPELL_AURA_PHASE);
        if (!phases.empty())
            for (AuraEffectList::const_iterator itr = phases.begin(); itr != phases.end(); ++itr)
                newPhase |= (*itr)->GetMiscValue();

        if (!newPhase)
            newPhase = PHASEMASK_NORMAL;

        SetPhaseMask(newPhase, false);

        m_ExtraFlags &= ~PLAYER_EXTRA_GM_ON;
        SetFactionForRace(GetRace());
        RemoveFlag(PLAYER_FLAGS, PLAYER_FLAGS_GM);
        RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_ALLOW_CHEAT_SPELLS);

        if (spectateFrom)
            SetViewpoint(spectateFrom, false);

        // restore FFA PvP Server state
        if (sWorld->IsFFAPvPRealm())
            SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);

        // restore FFA PvP area state, remove not allowed for GM mounts
        UpdateArea(m_areaUpdateId);

        //getHostileRefManager().setOnlineOfflineState(true);
        m_serverSideVisibility.SetValue(SERVERSIDE_VISIBILITY_GM, SEC_PLAYER);
        spectateCanceled = false;
        spectatorFlag = false;
        RestoreDisplayId();
        UpdateSpeed(MOVE_RUN);
    }
    UpdateObjectVisibility();
}

bool Player::HaveSpectators()
{
    if (IsSpectator())
        return false;

    if (Battleground* bg = GetBattleground())
        if (bg->isArena())
        {
            if (bg->GetStatus() != STATUS_IN_PROGRESS)
                return false;

            return bg->HaveSpectators();
        }

    return false;
}

void Player::SendSpectatorAddonMsgToBG(SpectatorAddonMsg msg)
{
    if (!HaveSpectators())
        return;

    GetBattleground()->SendSpectateAddonsMsg(msg);
}
