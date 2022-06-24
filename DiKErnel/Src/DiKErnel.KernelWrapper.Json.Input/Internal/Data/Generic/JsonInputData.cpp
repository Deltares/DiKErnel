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

#include "JsonInputData.h"

#include <utility>

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputData::JsonInputData(
        vector<int> times,
        unique_ptr<JsonInputHydraulicData> hydraulicData,
        unique_ptr<JsonInputDikeProfileData> dikeProfileData,
        vector<unique_ptr<JsonInputLocationData>> locationData,
        map<JsonInputCalculationType, unique_ptr<JsonInputCalculationDefinitionData>> calculationDefinitionData)
        : _times(move(times)),
          _hydraulicData(move(hydraulicData)),
          _dikeProfileData(move(dikeProfileData)),
          _locationData(move(locationData)),
          _calculationDefinitionData(move(calculationDefinitionData))
    {
        for (const auto& locationDataItem : _locationData)
        {
            _locationDataReferences.emplace_back(*locationDataItem);
        }

        for (const auto& [calculationType, calculationDefinition] : _calculationDefinitionData)
        {
            _calculationDefinitionDataReferences.insert(
                pair<JsonInputCalculationType, reference_wrapper<JsonInputCalculationDefinitionData>>(calculationType, *calculationDefinition));
        }
    }

    const vector<int>& JsonInputData::GetTimes() const
    {
        return _times;
    }

    const JsonInputHydraulicData& JsonInputData::GetHydraulicData() const
    {
        return *_hydraulicData;
    }

    const JsonInputDikeProfileData& JsonInputData::GetDikeProfileData() const
    {
        return *_dikeProfileData;
    }

    const vector<reference_wrapper<JsonInputLocationData>>& JsonInputData::GetLocationData() const
    {
        return _locationDataReferences;
    }

    const map<JsonInputCalculationType, reference_wrapper<JsonInputCalculationDefinitionData>>&
        JsonInputData::GetCalculationDefinitionData() const
    {
        return _calculationDefinitionDataReferences;
    }
}
