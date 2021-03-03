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

    template <typename TJsonInputRevetmentLocationData>
    JsonInputLocationData<TJsonInputRevetmentLocationData>::JsonInputLocationData(
        string name,
        unique_ptr<JsonInputDamageData> damageData,
        unique_ptr<TJsonInputRevetmentLocationData> revetmentLocationData,
        unique_ptr<JsonInputProfileSchematizationData> profileSchematizationData)
        : _name(move(name)),
          _damageData(move(damageData)),
          _revetmentLocationData(move(revetmentLocationData)),
          _profileSchematizationData(move(profileSchematizationData)) { }

    template <typename TJsonInputRevetmentLocationData>
    const string& JsonInputLocationData<TJsonInputRevetmentLocationData>::GetName() const
    {
        return _name;
    }

    template <typename TJsonInputRevetmentLocationData>
    const JsonInputDamageData& JsonInputLocationData<TJsonInputRevetmentLocationData>::GetDamageData() const
    {
        return *_damageData;
    }

    template <typename TJsonInputRevetmentLocationData>
    const TJsonInputRevetmentLocationData& JsonInputLocationData<TJsonInputRevetmentLocationData>::GetRevetmentLocationData() const
    {
        return *_revetmentLocationData;
    }

    template <typename TJsonInputRevetmentLocationData>
    const JsonInputProfileSchematizationData& JsonInputLocationData<TJsonInputRevetmentLocationData>::GetProfileSchematizationData() const
    {
        return *_profileSchematizationData;
    }
}
