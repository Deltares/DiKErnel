// Copyright (C) Stichting Deltares 2020. All rights reserved.
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

#include "JsonInputLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputLocationData::JsonInputLocationData(
        string name,
        const double x,
        unique_ptr<JsonInputDamageData> damageData,
        unique_ptr<IJsonInputRevetmentLocationData> revetmentLocationData,
        unique_ptr<JsonInputProfileSchematizationData> profileSchematizationData)
        : _name(move(name)),
          _x(x),
          _damageData(move(damageData)),
          _revetmentLocationData(move(revetmentLocationData)),
          _profileSchematizationData(move(profileSchematizationData)) { }

    const string& JsonInputLocationData::GetName() const
    {
        return _name;
    }

    double JsonInputLocationData::GetX() const
    {
        return _x;
    }

    const JsonInputDamageData& JsonInputLocationData::GetDamageData() const
    {
        return *_damageData;
    }

    const IJsonInputRevetmentLocationData& JsonInputLocationData::GetRevetmentLocationData() const
    {
        return *_revetmentLocationData;
    }

    const JsonInputProfileSchematizationData& JsonInputLocationData::GetProfileSchematizationData() const
    {
        return *_profileSchematizationData;
    }
}
