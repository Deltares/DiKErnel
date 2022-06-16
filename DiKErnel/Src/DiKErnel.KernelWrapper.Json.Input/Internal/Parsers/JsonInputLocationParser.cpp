// Copyright (C) Stichting Deltares 2022. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#include "JsonInputLocationParser.h"

#include "JsonInputDefinitions.h"
#include "JsonInputParserHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace nlohmann;
    using namespace std;

    JsonInputLocationParser::JsonInputLocationParser(
        const json& readLocation)
        : _readLocation(readLocation) { }

    unique_ptr<JsonInputLocationData> JsonInputLocationParser::Parse()
    {
        const auto x = _readLocation.at(JsonInputDefinitions::X).get<double>();
        auto initialDamage = JsonInputParserHelper::ParseOptionalDouble(_readLocation, JsonInputDefinitions::INITIAL_DAMAGE);

        return ParseLocationData(x, move(initialDamage));
    }

    const json& JsonInputLocationParser::GetReadLocation() const
    {
        return _readLocation;
    }
}
