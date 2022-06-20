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

#include "JsonInputDikeProfileData.h"

#include <utility>

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputDikeProfileData::JsonInputDikeProfileData(
        vector<double> xLocations,
        vector<double> zLocations,
        vector<std::pair<JsonInputCharacteristicPointType, double>> characteristicPoints)
        : _xLocations(move(xLocations)),
          _zLocations(move(zLocations)),
          _characteristicPoints(move(characteristicPoints)) {}

    JsonInputDikeProfileData::JsonInputDikeProfileData(
        vector<unique_ptr<JsonInputDikeProfilePoint>> dikeProfilePoints)
        : _dikeProfilePoints(move(dikeProfilePoints))
    {
        for (const auto& dikeProfilePoint : _dikeProfilePoints)
        {
            _dikeProfilePointReferences.emplace_back(*dikeProfilePoint);
        }
    }

    const vector<double>& JsonInputDikeProfileData::GetXLocations() const
    {
        return _xLocations;
    }

    const vector<double>& JsonInputDikeProfileData::GetZLocations() const
    {
        return _zLocations;
    }

    const vector<pair<JsonInputCharacteristicPointType, double>>& JsonInputDikeProfileData::GetCharacteristicPoints() const
    {
        return _characteristicPoints;
    }

    const vector<reference_wrapper<JsonInputDikeProfilePoint>>& JsonInputDikeProfileData::GetDikeProfilePoints() const
    {
        return _dikeProfilePointReferences;
    }
}
