/*
 * Copyright (C) since 2016 AtieshCore <https://at-wow.org/>
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

#include "CustomWorldConfigMgr.h"
#include "DatabaseEnv.h"
#include "GridDefines.h"
#include "ObjectDefines.h"
#include "ObjectMgr.h"
#include "Log.h"
#include "Player.h"
#include "World.h"
#include "StringConvert.h"

CustomWorldConfig* CustomWorldConfig::instance()
{
    static CustomWorldConfig instance;
    return &instance;
}

void CustomWorldConfig::AddOption(CustomWorldConfigType type, uint32 IDinTypeGroup, std::string const& defaultValue, std::string const& value)
{
    switch (type)
    {
        case CustomWorldConfigType::GAME_CONFIG_TYPE_BOOL:
        {
            Optional<bool> boolValDefault = Trinity::StringTo<bool>(defaultValue);
            Optional<bool> boolVal = Trinity::StringTo<bool>(value);
            AddBoolOption(IDinTypeGroup, value.empty() ? *boolValDefault : *boolVal);
            break;
        }
        case CustomWorldConfigType::GAME_CONFIG_TYPE_INT:
            AddIntOption(IDinTypeGroup, value.empty() ? (uint32)std::stoi(defaultValue) : (uint32)std::stoi(value));
            break;
        case CustomWorldConfigType::GAME_CONFIG_TYPE_FLOAT:
            AddFloatOption(IDinTypeGroup, value.empty() ? std::stof(defaultValue) : std::stof(value));
            break;
        case CustomWorldConfigType::GAME_CONFIG_TYPE_RATES:
            AddRateOption(IDinTypeGroup, value.empty() ? std::stof(defaultValue) : std::stof(value));
            break;
        default:
            ABORT();
            break;
    }
}

void CustomWorldConfig::Load()
{
    uint32 oldMSTime = getMSTime();

    QueryResult result = WorldDatabase.PQuery("SELECT `OptionName`, `Type`, `IDInTypeGroup`, `DefaultValue`, `CustomValue` FROM world_custom_config");
    if (!result)
    {
        FMT_LOG_INFO("server.loading", ">> Loaded 0 game config options. DB table `game_config` is empty.");
        return;
    }

    uint32 count = 0;

    auto GetTypeString = [](std::string optionType) -> CustomWorldConfigType
    {
        if (optionType == "bool")
            return CustomWorldConfigType::GAME_CONFIG_TYPE_BOOL;
        else if (optionType == "int")
            return CustomWorldConfigType::GAME_CONFIG_TYPE_INT;
        else if (optionType == "float")
            return CustomWorldConfigType::GAME_CONFIG_TYPE_FLOAT;
        else if (optionType == "rate")
            return CustomWorldConfigType::GAME_CONFIG_TYPE_RATES;
        else
            return CustomWorldConfigType::GAME_CONFIG_TYPE_UNKNOWN;
    };

    do
    {
        Field* fields = result->Fetch();

        std::string const& optionName   = fields[0].GetString();
        std::string const& optionType   = fields[1].GetString();
        uint32 const& IDinTypeGroup     = fields[2].GetUInt32();
        std::string const& defaultValue = fields[3].GetString();
        std::string const& customValue  = fields[4].GetString();

        auto _type = GetTypeString(optionType);

        if (_type == CustomWorldConfigType::GAME_CONFIG_TYPE_UNKNOWN)
        {
            FMT_LOG_ERROR("config", "> Don't support type ({}) for option ({})", optionType, optionName);
            continue;
        }

        AddOption(_type, IDinTypeGroup, defaultValue, customValue);

        count++;

    } while (result->NextRow());

    FMT_LOG_INFO("server.loading", ">> Loaded {} game config option in {} ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void CustomWorldConfig::AddBoolOption(uint32 IDinTypeGroup, bool const& value)
{
    if (!sWorld->customSetBoolConfig(CustomWorldBoolConfigs(IDinTypeGroup), value))
    {
        FMT_LOG_ERROR("config", "> Bool option ({}) did not registered in core!", IDinTypeGroup);
        return;
    }
}

void CustomWorldConfig::AddIntOption(uint32 IDinTypeGroup, uint32 const& value)
{
    if (!sWorld->customSetIntConfig(CustomWorldIntConfigs(IDinTypeGroup), value))
    {
        FMT_LOG_ERROR("config", "> Int option ({}) did not registered in core!", IDinTypeGroup);
        return;
    }
}

void CustomWorldConfig::AddFloatOption(uint32 IDinTypeGroup, float const& value)
{
    if (!sWorld->customSetFloatConfig(CustomWorldFloatConfigs(IDinTypeGroup), value))
    {
        FMT_LOG_ERROR("config", "> Float option ({}) did not registered in core!", IDinTypeGroup);
        return;
    }
}

void CustomWorldConfig::AddRateOption(uint32 IDinTypeGroup, float const& value)
{
    if (!sWorld->customSetRate(CustomRates(IDinTypeGroup), value))
    {
        FMT_LOG_ERROR("config", "> Rate option ({}) did not registered in core!", IDinTypeGroup);
        return;
    }
}
