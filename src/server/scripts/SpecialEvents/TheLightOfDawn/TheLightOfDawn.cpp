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
#include "DBCStores.h"
#include "TheLightOfDawn.h"
#include "Group.h"
#include "Guild.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "SpecialEventMgr.h"
#include "RBAC.h"
#include "MapManager.h"
#include "MiscPackets.h"
#include "Language.h"
#include "Log.h"
#include "WorldSession.h"
#include "World.h"

enum DataEnum
{
    QUEST_THE_LIGHT_OF_DAWN             = 12801,

    // encounters
    ENCOUNTER_START_TIME                = 5,
    ENCOUNTER_TOTAL_DEFENDERS           = 300,
    ENCOUNTER_TOTAL_SCOURGE             = 10000,

    // map_id
    MAPID_THE_SCARLET_ENCLAVE           = 609,
    // zone id
    ZONEID_THE_SCARLET_ENCLAVE          = 4298, // Zone: Plaguelands: The Scarlet Enclave

    // world states
    // basically world states should be shown to all players with phase mask = 128 as stated in DBC
    // because we don't have the possibility to do that we'll just iterate through the players and set the phase mask manually based on the battle status
    WORLD_STATE_FORCES_SHOW             = 3592,             // show the remaining units
    WORLD_STATE_FORCES_SCOURGE          = 3591,
    WORLD_STATE_FORCES_LIGHT            = 3590,
    WORLD_STATE_BATTLE_TIMER_SHOW       = 3603,             // countdown timer
    WORLD_STATE_BATTLE_TIMER            = 3604,
    WORLD_STATE_BATTLE_BEGIN            = 3605,             // battle has begun

    // Intro Events
    EVENT_START_PREPARE                 = 1,
    EVENT_START_COUNTDOWN_1,
    EVENT_START_COUNTDOWN_2,
    EVENT_START_COUNTDOWN_3,
    EVENT_START_COUNTDOWN_4,
    EVENT_START_COUNTDOWN_5,

    EVENT_BEFORE_FIGHT_RISE,
    EVENT_BEFORE_FIGHT_PREVIOUS_LIFE,
    EVENT_BEFORE_FIGHT_RED_SKY,
    EVENT_BEFORE_FIGHT_SPAWN_SCOURGE_1,
    EVENT_BEFORE_FIGHT_SPAWN_SCOURGE_2,
    EVENT_BEFORE_FIGHT_SPAWN_SCOURGE_3,
    EVENT_BEFORE_FIGHT_SPAWN_SCOURGE_4,
    EVENT_BEFORE_FIGHT_START_MOVE_FOR_MONSTERS,
    EVENT_BEFORE_FIGHT_START_MOVE,

    // Fight Events
    EVENT_SPELL_ANTI_MAGIC_ZONE,
    EVENT_SPELL_DEATH_STRIKE,
    EVENT_SPELL_DEATH_EMBRACE,
    EVENT_SPELL_UNHOLY_BLIGHT,
    EVENT_SPELL_TALK,
    // Positioning
    EVENT_FINISH_FIGHT_1,
    EVENT_FINISH_FIGHT_2,
    EVENT_FINISH_FIGHT_3,
    EVENT_FINISH_FIGHT_4,
    EVENT_FINISH_FIGHT_5,
    // Outro
    EVENT_OUTRO_SCENE_1,
    EVENT_OUTRO_SCENE_2,
    EVENT_OUTRO_SCENE_3,
    EVENT_OUTRO_SCENE_4,
    EVENT_OUTRO_SCENE_5,
    EVENT_OUTRO_SCENE_6,
    EVENT_OUTRO_SCENE_7,
    EVENT_OUTRO_SCENE_8,
    EVENT_OUTRO_SCENE_9,
    EVENT_OUTRO_SCENE_10,
    EVENT_OUTRO_SCENE_11,
    EVENT_OUTRO_SCENE_12,
    EVENT_OUTRO_SCENE_13,
    EVENT_OUTRO_SCENE_14,
    EVENT_OUTRO_SCENE_15,
    EVENT_OUTRO_SCENE_16,
    EVENT_OUTRO_SCENE_17,
    EVENT_OUTRO_SCENE_18,
    EVENT_OUTRO_SCENE_19,
    EVENT_OUTRO_SCENE_20,
    EVENT_OUTRO_SCENE_21,
    EVENT_OUTRO_SCENE_22,
    EVENT_OUTRO_SCENE_23,
    EVENT_OUTRO_SCENE_24,
    EVENT_OUTRO_SCENE_25,
    EVENT_OUTRO_SCENE_26,
    EVENT_OUTRO_SCENE_27,
    EVENT_OUTRO_SCENE_28,
    EVENT_OUTRO_SCENE_29,
    EVENT_OUTRO_SCENE_30,
    EVENT_OUTRO_SCENE_31,
    EVENT_OUTRO_SCENE_32,
    EVENT_OUTRO_SCENE_33,
    EVENT_OUTRO_SCENE_34,
    EVENT_OUTRO_SCENE_35,
    EVENT_OUTRO_SCENE_36,
    EVENT_OUTRO_SCENE_37,
    EVENT_OUTRO_SCENE_38,
    EVENT_OUTRO_SCENE_39,
    EVENT_OUTRO_SCENE_40,
    EVENT_OUTRO_SCENE_41,
    EVENT_OUTRO_SCENE_42,
    EVENT_OUTRO_SCENE_43,
    EVENT_OUTRO_SCENE_44,
    EVENT_OUTRO_SCENE_45,
    EVENT_OUTRO_SCENE_46,
    EVENT_OUTRO_SCENE_47,
    EVENT_OUTRO_SCENE_48,
    EVENT_OUTRO_SCENE_49,
    EVENT_OUTRO_SCENE_50,
    EVENT_OUTRO_SCENE_51,
    EVENT_OUTRO_SCENE_52,
    EVENT_OUTRO_SCENE_53,
    EVENT_OUTRO_SCENE_54,
    EVENT_OUTRO_SCENE_55,
    EVENT_OUTRO_SCENE_56,
    EVENT_OUTRO_SCENE_57,
    EVENT_OUTRO_SCENE_58,
    EVENT_OUTRO_SCENE_59,
    EVENT_OUTRO_SCENE_60,
    EVENT_OUTRO_SCENE_61
};

enum LightOfDawnNPCs
{
    // Defenders
    NPC_DEFENDER_OF_THE_LIGHT           = 29174,
    NPC_KORFAX_CHAMPION_OF_THE_LIGHT    = 29176,
    NPC_COMMANDER_ELIGOR_DAWNBRINGER    = 29177,
    NPC_LORD_MAXWELL_TYROSUS            = 29178,
    NPC_LEONID_BARTHALOMEW_THE_REVERED  = 29179,
    NPC_DUKE_NICHOLAS_ZVERENHOFF        = 29180,
    NPC_RAYNE                           = 29181,
    NPC_RIMBLAT_EARTHSHATTER            = 29182,

    // Scourge
    NPC_RAMPAGING_ABOMINATION           = 29186,
    NPC_ACHERUS_GHOUL                   = 29219,
    NPC_WARRIOR_OF_THE_FROZEN_WASTES    = 29206,
    NPC_FLESH_BEHEMOTH                  = 29190,

    NPC_HIGHLORD_DARION_MOGRAINE        = 29173,
    NPC_KOLTIRA_DEATHWEAVER             = 29199,
    NPC_ORBAZ_BLOODBANE                 = 29204,
    NPC_THASSARIAN                      = 29200,

    // Outro
    NPC_HIGHLORD_TIRION_FORDRING        = 29175,
    NPC_HIGHLORD_ALEXANDROS_MOGRAINE    = 29227, // ghost
    NPC_DARION_MOGRAINE                 = 29228, // ghost
    NPC_THE_LICH_KING                   = 29183,
};

enum LightOfDawnSays
{
    SAY_LIGHT_OF_DAWN01               = 0, // pre text
    SAY_LIGHT_OF_DAWN02               = 1,
    SAY_LIGHT_OF_DAWN03               = 2,
    SAY_LIGHT_OF_DAWN04               = 3, // intro
    SAY_LIGHT_OF_DAWN05               = 4,
    SAY_LIGHT_OF_DAWN06               = 5,
    SAY_LIGHT_OF_DAWN07               = 6, // During the fight - Korfax, Champion of the Light
    SAY_LIGHT_OF_DAWN08               = 7, // Lord Maxwell Tyrosus
    SAY_LIGHT_OF_DAWN09               = 8, // Highlord Darion Mograine
    SAY_LIGHT_OF_DAWN25               = 24, // After the fight
    SAY_LIGHT_OF_DAWN26               = 25, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN27               = 26, // Highlord Darion Mograine
    SAY_LIGHT_OF_DAWN28               = 27, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN29               = 28, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN30               = 29, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN31               = 30, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN32               = 31, // Highlord Alexandros Mograine
    SAY_LIGHT_OF_DAWN33               = 32, // Highlord Darion Mograine
    SAY_LIGHT_OF_DAWN34               = 33, // Highlord Darion Mograine
    SAY_LIGHT_OF_DAWN35               = 34, // Darion Mograine
    SAY_LIGHT_OF_DAWN36               = 35, // Darion Mograine
    SAY_LIGHT_OF_DAWN37               = 36, // Highlord Alexandros Mograine
    SAY_LIGHT_OF_DAWN38               = 37, // Darion Mograine
    SAY_LIGHT_OF_DAWN39               = 38, // Highlord Alexandros Mograine
    SAY_LIGHT_OF_DAWN40               = 39, // Darion Mograine
    SAY_LIGHT_OF_DAWN41               = 40, // Highlord Alexandros Mograine
    SAY_LIGHT_OF_DAWN42               = 41, // Highlord Alexandros Mograine
    SAY_LIGHT_OF_DAWN43               = 42, // The Lich King
    SAY_LIGHT_OF_DAWN44               = 43, // Highlord Darion Mograine
    SAY_LIGHT_OF_DAWN45               = 44, // The Lich King
    SAY_LIGHT_OF_DAWN46               = 45, // The Lich King
    SAY_LIGHT_OF_DAWN47               = 46, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN48               = 47, // The Lich King
    SAY_LIGHT_OF_DAWN49               = 48, // The Lich King
    SAY_LIGHT_OF_DAWN50               = 49, // Lord Maxwell Tyrosus
    SAY_LIGHT_OF_DAWN51               = 50, // The Lich King
    SAY_LIGHT_OF_DAWN52               = 51, // Highlord Darion Mograine
    SAY_LIGHT_OF_DAWN53               = 52, // Highlord Darion Mograine
    SAY_LIGHT_OF_DAWN54               = 53, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN55               = 54, // The Lich King
    SAY_LIGHT_OF_DAWN56               = 55, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN57               = 56, // The Lich King
    SAY_LIGHT_OF_DAWN58               = 57, // The Lich King
    SAY_LIGHT_OF_DAWN59               = 58, // The Lich King
    SAY_LIGHT_OF_DAWN60               = 59, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN61               = 60, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN62               = 61, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN63               = 62, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN64               = 63, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN65               = 64, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN66               = 65, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN67               = 66, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN68               = 67, // Highlord Darion Mograine

    EMOTE_LIGHT_OF_DAWN01             = 68,  // Emotes
    EMOTE_LIGHT_OF_DAWN02             = 69,
    EMOTE_LIGHT_OF_DAWN03             = 70,
    EMOTE_LIGHT_OF_DAWN04             = 71,
    EMOTE_LIGHT_OF_DAWN05             = 72,
    EMOTE_LIGHT_OF_DAWN06             = 73,
    EMOTE_LIGHT_OF_DAWN07             = 74,
    EMOTE_LIGHT_OF_DAWN08             = 75,
    EMOTE_LIGHT_OF_DAWN09             = 76,
    EMOTE_LIGHT_OF_DAWN10             = 77,
    EMOTE_LIGHT_OF_DAWN11             = 78,
    EMOTE_LIGHT_OF_DAWN12             = 79,
    EMOTE_LIGHT_OF_DAWN13             = 80,
    EMOTE_LIGHT_OF_DAWN14             = 81,
    EMOTE_LIGHT_OF_DAWN15             = 82,
    EMOTE_LIGHT_OF_DAWN16             = 83,
    EMOTE_LIGHT_OF_DAWN17             = 84,
    EMOTE_LIGHT_OF_DAWN18             = 85
};

enum LightOfDawnSpells
{
    // Intro Spells
    SPELL_CAMERA_SHAKE_INIT             = 36455,
    SPELL_CAMERA_SHAKE                  = 39983,
    SPELL_THE_MIGHT_OF_MOGRAINE         = 53642,

    // Mograine Fight
    SPELL_ANTI_MAGIC_ZONE1              = 52893,
    SPELL_DEATH_STRIKE                  = 53639,
    SPELL_DEATH_EMBRACE                 = 53635,
    SPELL_ICY_TOUCH1                    = 49723,
    SPELL_UNHOLY_BLIGHT                 = 53640,

    // Outro
    SPELL_THE_LIGHT_OF_DAWN             = 53658,
    SPELL_ALEXANDROS_MOGRAINE_SPAWN     = 53667,
    SPELL_ICEBOUND_VISAGE               = 53274,
    SPELL_SOUL_FEAST_ALEX               = 53677,
    SPELL_MOGRAINE_CHARGE               = 53679,
    SPELL_REBUKE                        = 53680,
    SPELL_SOUL_FEAST_TIRION             = 53685,
    SPELL_APOCALYPSE                    = 53210,
    SPELL_THROW_ASHBRINGER              = 53701,
    SPELL_REBIRTH_OF_THE_ASHBRINGER     = 53702,
    SPELL_TIRION_CHARGE                 = 53705,
    SPELL_EXIT_TELEPORT_VISUAL          = 61456,
    SPELL_LAY_ON_HANDS                  = 53778,
    SPELL_THE_LIGHT_OF_DAWN_Q           = 53606
};

void TheLightOfDawnEvent::UpdateWorldState(uint32 id, uint32 state)
{
    for (PlayersDataContainer::const_iterator itr = m_playersDataStore.begin(); itr != m_playersDataStore.end(); ++itr)
    {
        if (Player* player = ObjectAccessor::FindPlayer(itr->second.guid))
            player->SendUpdateWorldState(id, state);
    }
}

void TheLightOfDawnEvent::UpdateAllWorldStates()
{
    // update world states to default
    UpdateWorldState(WORLD_STATE_FORCES_SHOW, show_soldiers_count);
    UpdateWorldState(WORLD_STATE_FORCES_LIGHT, defendersRemaining);
    UpdateWorldState(WORLD_STATE_FORCES_SCOURGE, scourgeRemaining);
    UpdateWorldState(WORLD_STATE_BATTLE_TIMER_SHOW, show_timer);
    UpdateWorldState(WORLD_STATE_BATTLE_TIMER, countdownTimerRemaining);
    UpdateWorldState(WORLD_STATE_BATTLE_BEGIN, show_event_begin);
}

void TheLightOfDawnEvent::SetupInitialStates()
{
    events.Reset();
    defendersRemaining      = ENCOUNTER_TOTAL_DEFENDERS;
    scourgeRemaining        = ENCOUNTER_TOTAL_SCOURGE;
    countdownTimerRemaining = 0;
    show_soldiers_count     = true;
    show_timer              = false;
    show_event_begin        = false;

    UpdateAllWorldStates();

    // Light real count
    DefendersCount      = 0;
    EarthshattersCount  = 0;
    // Scourge real count
    AbominationsCount   = 0;
    BehemothsCount      = 0;
    GhoulsCount         = 0;
    WarriorsCount       = 0;
}

void TheLightOfDawnEvent::DoPlaySoundToAll(uint32 soundId)
{
    // We should send data for players in area (only)
    BroadcastPacketToPlayersInArea(WorldPackets::Misc::PlaySound(soundId).Write());
}

void TheLightOfDawnEvent::BroadcastPacketToPlayersInArea(WorldPacket const* data) const
{
    for (PlayersDataContainer::const_iterator itr = m_playersDataStore.begin(); itr != m_playersDataStore.end(); ++itr)
    {
        if (itr->second.isInArea)
            if (Player* player = ObjectAccessor::FindConnectedPlayer(itr->second.guid))
                player->SendDirectMessage(data);
    }
}

void TheLightOfDawnEvent::StartTheLightOfDawnEvent()
{
    SetupInitialStates();
    events.ScheduleEvent(EVENT_START_PREPARE, 0s);
}

void TheLightOfDawnEvent::StopTheLightOfDawnEvent()
{
    SetupInitialStates();
}

void TheLightOfDawnEvent::SummonScorgeArmy()
{
    events.ScheduleEvent(EVENT_BEFORE_FIGHT_SPAWN_SCOURGE_1, 500ms);
    events.ScheduleEvent(EVENT_BEFORE_FIGHT_SPAWN_SCOURGE_2, 1s);
    events.ScheduleEvent(EVENT_BEFORE_FIGHT_SPAWN_SCOURGE_3, 1500ms);
    events.ScheduleEvent(EVENT_BEFORE_FIGHT_SPAWN_SCOURGE_4, 2s);
}

void TheLightOfDawnEvent::SummonDefenseArmy()
{

}

void TheLightOfDawnEvent::ClearAllNPC()
{
    // Light
    for (uint8 i = 0; i < ENCOUNTER_DEFENDER_NUMBER; ++i)
    {
        if (Creature* temp = GetCreature(DefenderGUID[i]))
            temp->setDeathState(JUST_DIED);
        DefenderGUID[i].Clear();
    }
    for (uint8 i = 0; i < ENCOUNTER_EARTHSHATTER_NUMBER; ++i)
    {
        if (Creature* temp = GetCreature(EarthshatterGUID[i]))
            temp->setDeathState(JUST_DIED);
        EarthshatterGUID[i].Clear();
    }

    // Scourge
    for (uint8 i = 0; i < ENCOUNTER_ABOMINATION_NUMBER; ++i)
    {
        if (Creature* temp = GetCreature(AbominationGUID[i]))
            temp->setDeathState(JUST_DIED);
        AbominationGUID[i].Clear();
    }
    for (uint8 i = 0; i < ENCOUNTER_BEHEMOTH_NUMBER; ++i)
    {
        if (Creature* temp = GetCreature(BehemothGUID[i]))
            temp->setDeathState(JUST_DIED);
        BehemothGUID[i].Clear();
    }
    for (uint8 i = 0; i < ENCOUNTER_GHOUL_NUMBER; ++i)
    {
        if (Creature* temp = GetCreature(GhoulGUID[i]))
            temp->setDeathState(JUST_DIED);
        GhoulGUID[i].Clear();
    }
    for (uint8 i = 0; i < ENCOUNTER_WARRIOR_NUMBER; ++i)
    {
        if (Creature* temp = GetCreature(WarriorGUID[i]))
            temp->setDeathState(JUST_DIED);
        WarriorGUID[i].Clear();
    }
}

TheLightOfDawnEvent::TheLightOfDawnEvent()
{
    _eventId = SPECIALEVENT_EVENTID_THELIGHTOFDAWN;
    SetPhase(PHASE_IDLE);

    //prepareTimer.Reset(IN_MILLISECONDS);
}

bool TheLightOfDawnEvent::SetupSpecialEvent(bool enabled, bool active, bool repeatable, uint32 id, uint32 cooldownTimer, uint32 durationTimer, std::string comment)
{
    // override Setup for Set time of first run in cooldownTimer
    if (!SpecialEvent::SetupSpecialEvent(enabled, active, repeatable, id, cooldownTimer, durationTimer, comment))
        return false;
    
    _mapId = MAPID_THE_SCARLET_ENCLAVE;
    _map = sMapMgr->FindMap(_mapId, 0);
    if (!_map)
        _map = sMapMgr->CreateBaseMap(_mapId);

    RegisterZoneIdForEvent(ZONEID_THE_SCARLET_ENCLAVE);
    SetupInitialStates();
    return true;
}

void TheLightOfDawnEvent::DoActionForMember(ObjectGuid playerGUID, uint32 param)
{
    for (PlayersDataContainer::iterator itr = m_playersDataStore.begin(); itr != m_playersDataStore.end(); ++itr)
    {
        if (itr->second.guid == playerGUID)
        {
            if (!param) // if param == 0, we should set true isDoingQuest
                itr->second.isDoingQuest = true;
            else        // if param == 1, we should set false isDoingQuest
                itr->second.isDoingQuest = false;
        }
    }
}

TheLightOfDawnEvent::~TheLightOfDawnEvent()
{
    m_playersDataStore.clear();

    // Dawn
    TirionGUID.Clear();
    AlexandrosGUID.Clear();
    DarionGUID.Clear();
    KorfaxGUID.Clear();
    MaxwellGUID.Clear();
    EligorGUID.Clear();
    RayneGUID.Clear();

    // Scourge
    Darion_Mograine.Clear();
    KoltiraGUID.Clear();
    OrbazGUID.Clear();
    ThassarianGUID.Clear();
    LichKingGUID.Clear();

    ClearAllNPC();
}

void TheLightOfDawnEvent::Update(uint32 diff)
{
    SpecialEvent::Update(diff);

    events.Update(diff);

    while (uint32 eventId = events.ExecuteEvent())
    {
        switch (eventId)
        {
            case EVENT_START_PREPARE:
            {
                countdownTimerRemaining = ENCOUNTER_START_TIME;
                show_timer              = true;

                UpdateAllWorldStates();

                events.Reset();
                events.ScheduleEvent(EVENT_START_COUNTDOWN_1, 60s);
                events.ScheduleEvent(EVENT_START_COUNTDOWN_2, 120s);
                events.ScheduleEvent(EVENT_START_COUNTDOWN_3, 180s);
                events.ScheduleEvent(EVENT_START_COUNTDOWN_4, 240s);
                events.ScheduleEvent(EVENT_START_COUNTDOWN_5, 300s);
                break;
            }
            case EVENT_START_COUNTDOWN_1:
            {
                --countdownTimerRemaining;  // 4 minutes
                UpdateWorldState(WORLD_STATE_BATTLE_TIMER, countdownTimerRemaining);
                break;
            }
            case EVENT_START_COUNTDOWN_2:
            {
                --countdownTimerRemaining;  // 3 minutes
                UpdateWorldState(WORLD_STATE_BATTLE_TIMER, countdownTimerRemaining);
                break;
            }
            case EVENT_START_COUNTDOWN_3:
            {
                --countdownTimerRemaining;  // 2 minutes
                UpdateWorldState(WORLD_STATE_BATTLE_TIMER, countdownTimerRemaining);
                break;
            }
            case EVENT_START_COUNTDOWN_4:
            {
                --countdownTimerRemaining;  // 1 minutes
                UpdateWorldState(WORLD_STATE_BATTLE_TIMER, countdownTimerRemaining);
                if (Creature* Darion = GetCreature(Darion_Mograine))
                    Darion->AI()->Talk(SAY_LIGHT_OF_DAWN02);    //The sky weeps at the glorious devastation of these lands! Soon, Azeroth's futile tears will rain down upon us!
                break;
            }
            case EVENT_START_COUNTDOWN_5:
            {
                --countdownTimerRemaining;  // 0 minutes
                UpdateWorldState(WORLD_STATE_BATTLE_TIMER, countdownTimerRemaining);

                show_timer       = false;
                show_event_begin = true;
                UpdateWorldState(WORLD_STATE_BATTLE_TIMER_SHOW, show_timer);                
                UpdateWorldState(WORLD_STATE_BATTLE_BEGIN, show_event_begin);

                if (Creature* Darion = GetCreature(Darion_Mograine))
                    Darion->AI()->Talk(SAY_LIGHT_OF_DAWN04);    // Death knights of Acherus, the death march begins!

                events.ScheduleEvent(EVENT_BEFORE_FIGHT_RISE, 10s);
                break;
            }
            case EVENT_BEFORE_FIGHT_RISE:
            {
                if (Creature* Darion = GetCreature(Darion_Mograine))
                {
                    Darion->AI()->Talk(SAY_LIGHT_OF_DAWN05);    // RISE!
                    Darion->AI()->DoCast(SPELL_CAMERA_SHAKE_INIT);
                }

                SummonScorgeArmy();
                events.ScheduleEvent(EVENT_BEFORE_FIGHT_PREVIOUS_LIFE, 25s);
                break;
            }
            case EVENT_BEFORE_FIGHT_PREVIOUS_LIFE:
            {
                // only for Ru locale?
                // Need audio play (Nasha prejnyaa jisn bila bessmislenna)

                events.ScheduleEvent(EVENT_BEFORE_FIGHT_RED_SKY, 7s);
                break;
            }
            case EVENT_BEFORE_FIGHT_RED_SKY:
            {
                if (Creature* Darion = GetCreature(Darion_Mograine))
                    Darion->AI()->Talk(SAY_LIGHT_OF_DAWN06);    // The skies turn red with the blood of the fallen! The Lich King watches over us, minions! Leave only ashes and misery in your destructive wake!

                events.ScheduleEvent(EVENT_BEFORE_FIGHT_START_MOVE_FOR_MONSTERS, 3s);
                events.ScheduleEvent(EVENT_BEFORE_FIGHT_START_MOVE, 5s);
                break;
            }
            case EVENT_BEFORE_FIGHT_SPAWN_SCOURGE_1:
            {
                if (Creature* Darion = GetCreature(Darion_Mograine))
                {
                    Position spawnpos;
                    while (AbominationsCount < ENCOUNTER_ABOMINATION_NUMBER)
                    {
                        spawnpos = Darion->GetNearPosition(frand(10.f, 200.f), frand(0, 6.14f));
                        if (Unit* temp = Darion->SummonCreature(NPC_RAMPAGING_ABOMINATION, spawnpos.GetPositionX(), spawnpos.GetPositionY(), spawnpos.GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300s))
                        {
                            temp->SetWalk(false);
                            temp->SetFaction(FACTION_UNDEAD_SCOURGE_3);
                            AbominationGUID[AbominationsCount] = temp->GetGUID();
                            ++AbominationsCount;
                        }
                    }
                }
                break;
            }
            case EVENT_BEFORE_FIGHT_SPAWN_SCOURGE_2:
            {
                if (Creature* Darion = GetCreature(Darion_Mograine))
                {
                    Position spawnpos;
                    while (BehemothsCount < ENCOUNTER_BEHEMOTH_NUMBER)
                    {
                        spawnpos = Darion->GetNearPosition(frand(10.f, 200.f), frand(0, 6.14f));
                        if (Unit* temp = Darion->SummonCreature(NPC_FLESH_BEHEMOTH, spawnpos.GetPositionX(), spawnpos.GetPositionY(), spawnpos.GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300s))
                        {
                            temp->SetWalk(false);
                            temp->SetFaction(FACTION_UNDEAD_SCOURGE_3);
                            BehemothGUID[AbominationsCount] = temp->GetGUID();
                            ++BehemothsCount;
                        }
                    }
                }
                break;
            }
            case EVENT_BEFORE_FIGHT_SPAWN_SCOURGE_3:
            {
                if (Creature* Darion = GetCreature(Darion_Mograine))
                {
                    Position spawnpos;
                    while (GhoulsCount < ENCOUNTER_GHOUL_NUMBER)
                    {
                        spawnpos = Darion->GetNearPosition(frand(10.f, 200.f), frand(0, 6.14f));
                        if (Unit* temp = Darion->SummonCreature(NPC_ACHERUS_GHOUL, spawnpos.GetPositionX(), spawnpos.GetPositionY(), spawnpos.GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300s))
                        {
                            temp->SetWalk(false);
                            temp->SetFaction(FACTION_UNDEAD_SCOURGE_3);
                            GhoulGUID[AbominationsCount] = temp->GetGUID();
                            ++GhoulsCount;
                        }
                    }
                }
                break;
            }
            case EVENT_BEFORE_FIGHT_SPAWN_SCOURGE_4:
            {
                if (Creature* Darion = GetCreature(Darion_Mograine))
                {
                    Position spawnpos;                    
                    while (WarriorsCount < ENCOUNTER_WARRIOR_NUMBER)
                    {
                        spawnpos = Darion->GetNearPosition(frand(10.f, 200.f), frand(0, 6.14f));
                        if (Unit* temp = Darion->SummonCreature(NPC_WARRIOR_OF_THE_FROZEN_WASTES, spawnpos.GetPositionX(), spawnpos.GetPositionY(), spawnpos.GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300s))
                        {
                            temp->SetWalk(false);
                            temp->SetFaction(FACTION_UNDEAD_SCOURGE_3);
                            WarriorGUID[AbominationsCount] = temp->GetGUID();
                            ++WarriorsCount;
                        }
                    }
                }
                break;
            }
            case EVENT_BEFORE_FIGHT_START_MOVE_FOR_MONSTERS:
            {
                // monsters start move early then Morgraine
                break;
            }
            case EVENT_BEFORE_FIGHT_START_MOVE:
            {
                // Morgraine start moveing
                break;
            }
            default:
                break;
        }
    }
}

void TheLightOfDawnEvent::OnSpecialEventStart()
{
    StartTheLightOfDawnEvent();
}

void TheLightOfDawnEvent::OnSpecialEventEnd(bool /*endByTimer*/)
{
    StopTheLightOfDawnEvent();
}

void TheLightOfDawnEvent::AddPlayer(ObjectGuid playerGUID)
{
    PlayersData pd;
    pd.guid         = playerGUID;
    pd.isDoingQuest = false;
    pd.isInArea     = false;
    if (Player* player = ObjectAccessor::FindConnectedPlayer(playerGUID))
    {
        if (player->GetQuestStatus(12801) == QUEST_STATUS_INCOMPLETE)
            pd.isDoingQuest = true;

        uint32 plrAreaid = player->GetAreaId();
        bool areaIdFounded = plrAreaid == 4298 || plrAreaid == 4361 || plrAreaid == 4364;
        if (areaIdFounded)
            pd.isInArea = true;
    }

    // find max id
    uint32 new_id = 0;
    for (PlayersDataContainer::const_iterator itr = m_playersDataStore.begin(); itr != m_playersDataStore.end(); ++itr)
        if (itr->first > new_id)
            new_id = itr->first;

    // use next
    ++new_id;
    // add in active player list of event
    m_playersDataStore[new_id] = pd;
}

void TheLightOfDawnEvent::RemovePlayer(ObjectGuid playerGUID)
{
    uint32 id = 0;
    for (PlayersDataContainer::const_iterator itr = m_playersDataStore.begin(); itr != m_playersDataStore.end(); ++itr)
    {
        if (itr->second.guid == playerGUID)
            id = itr->first;
    }

    if (id)
        m_playersDataStore.erase(id);
}

bool TheLightOfDawnEvent::IsMemberOfEvent(Player* player)
{
    for (PlayersDataContainer::const_iterator itr = m_playersDataStore.begin(); itr != m_playersDataStore.end(); ++itr)
    {
        if (itr->second.guid == player->GetGUID())
            return true;
    }

    return false;
}

void TheLightOfDawnEvent::HandlePlayerEnterZone(Player* player, uint32 zoneId)
{
    if (zoneId != ZONEID_THE_SCARLET_ENCLAVE)
        return;

    if (!IsMemberOfEvent(player))
        AddPlayer(player->GetGUID());

    player->SendUpdateWorldState(WORLD_STATE_FORCES_SHOW, show_soldiers_count);
    player->SendUpdateWorldState(WORLD_STATE_FORCES_LIGHT, defendersRemaining);
    player->SendUpdateWorldState(WORLD_STATE_FORCES_SCOURGE, scourgeRemaining);
    player->SendUpdateWorldState(WORLD_STATE_BATTLE_TIMER_SHOW, show_timer);
    player->SendUpdateWorldState(WORLD_STATE_BATTLE_TIMER, countdownTimerRemaining);
    player->SendUpdateWorldState(WORLD_STATE_BATTLE_BEGIN, show_event_begin);
}

void TheLightOfDawnEvent::HandlePlayerLeaveZone(Player* player, uint32 zoneId)
{
    if (zoneId != ZONEID_THE_SCARLET_ENCLAVE)
        return;

    if (IsMemberOfEvent(player))
        RemovePlayer(player->GetGUID());
}

void TheLightOfDawnEvent::HandlePlayerEnterArea(Player* player, uint32 zoneId, uint32 areaId)
{
    if (zoneId != ZONEID_THE_SCARLET_ENCLAVE)
        return;

    bool areaIdFounded = areaId == 4298 || areaId == 4361 || areaId == 4364;
    if (!areaIdFounded)
        return;

    for (PlayersDataContainer::iterator itr = m_playersDataStore.begin(); itr != m_playersDataStore.end(); ++itr)
    {
        if (itr->second.guid == player->GetGUID())
        {
            if (!itr->second.isInArea)
                itr->second.isInArea = true;
        }
    }
}

void TheLightOfDawnEvent::HandlePlayerLeaveArea(Player* player, uint32 zoneId, uint32 areaId)
{
    if (zoneId != ZONEID_THE_SCARLET_ENCLAVE)
        return;

    bool areaIdFounded = areaId == 4298 || areaId == 4361 || areaId == 4364;
    if (!areaIdFounded)
        return;

    for (PlayersDataContainer::iterator itr = m_playersDataStore.begin(); itr != m_playersDataStore.end(); ++itr)
    {
        if (itr->second.guid == player->GetGUID())
        {
            if (itr->second.isInArea)
                itr->second.isInArea = false;
        }
    }
}

Creature* TheLightOfDawnEvent::GetCreature(ObjectGuid guid)
{
    if (!_map)
        return nullptr;

    return _map->GetCreature(guid);
}

GameObject* TheLightOfDawnEvent::GetGameObject(ObjectGuid guid)
{
    if (!_map)
        return nullptr;

    return _map->GetGameObject(guid);
}

void TheLightOfDawnEvent::OnCreatureCreate(Creature* creature)
{
    switch (creature->GetEntry())
    {
        case NPC_HIGHLORD_DARION_MOGRAINE: Darion_Mograine = creature->GetGUID(); break;
        case NPC_KOLTIRA_DEATHWEAVER: KoltiraGUID = creature->GetGUID(); break;
        case NPC_ORBAZ_BLOODBANE: OrbazGUID = creature->GetGUID(); break;
        case NPC_THASSARIAN: ThassarianGUID = creature->GetGUID(); break;
        default:
            break;
    }
}

class SpecialEvent_TheLightOfDawn : public SpecialEventScript
{
public:
    SpecialEvent_TheLightOfDawn() : SpecialEventScript("the_light_of_dawn") { }

    SpecialEvent* GetSpecialEvent() const override
    {
        return new TheLightOfDawnEvent();
    }
};

class EndQuestTheLichKingCommand : public PlayerScript
{
public:
    EndQuestTheLichKingCommand() : PlayerScript("EndQuestTheLichKingCommand") { }

    void OnQuestStatusChange(Player* player, uint32 questId) override
    {
        if (questId != QUEST_THE_LIGHT_OF_DAWN)
            return;

        if (player->GetQuestStatus(QUEST_THE_LIGHT_OF_DAWN) == QUEST_STATUS_INCOMPLETE)
        {
            if (SpecialEvent* LoD = sSpecialEventMgr->GetEnabledSpecialEventByEventId(SPECIALEVENT_EVENTID_THELIGHTOFDAWN))
                LoD->DoActionForMember(player->GetGUID(), 0);  // Add player isDoingQuest (because player already in LoD area)
        }
        else if (player->GetQuestStatus(QUEST_THE_LIGHT_OF_DAWN) == QUEST_STATUS_NONE)
        {
            if (SpecialEvent* LoD = sSpecialEventMgr->GetEnabledSpecialEventByEventId(SPECIALEVENT_EVENTID_THELIGHTOFDAWN))
                LoD->DoActionForMember(player->GetGUID(), 1);  // Remove player isDoingQuest
        }
    }
};

void AddSC_TheLightOfDawnScripts()
{
    new SpecialEvent_TheLightOfDawn();
    new EndQuestTheLichKingCommand();
}
