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

#include "JsonInputCalculationData.h"

#include <utility>

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputCalculationData::JsonInputCalculationData(
        vector<int> times,
        unique_ptr<JsonInputHydraulicData> hydraulicData,
        unique_ptr<JsonInputDikeProfileData> dikeProfileData,
        vector<unique_ptr<JsonInputLocationData>> locationData)
        : _times(move(times)),
          _hydraulicData(move(hydraulicData)),
          _dikeProfileData(move(dikeProfileData)),
          _locationData(move(locationData))
    {
        for (const auto& locationDataItem : _locationData)
        {
            _locationDataReferences.emplace_back(*locationDataItem);
        }
    }

    const vector<int>& JsonInputCalculationData::GetTimes() const
    {
        return _times;
    }

    const JsonInputHydraulicData& JsonInputCalculationData::GetHydraulicData() const
    {
        return *_hydraulicData;
    }

    const JsonInputDikeProfileData& JsonInputCalculationData::GetDikeProfileData() const
    {
        return *_dikeProfileData;
    }

    const vector<reference_wrapper<JsonInputLocationData>>& JsonInputCalculationData::GetLocationData() const
    {
        return _locationDataReferences;
    }
}
