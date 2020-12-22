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

#include "InputData.h"

namespace DiKErnel::KernelWrapper::Json
{
    using namespace std;

    InputData::InputData(
        unique_ptr<CalculationData> calculationData,
        unique_ptr<HydraulicLoads> hydraulicLoads,
        vector<unique_ptr<CalculationLocation>> locations)
        : calculationData(move(calculationData)),
          hydraulicLoads(move(hydraulicLoads)),
          locations(move(locations))
    {
        for (const auto& location : this->locations)
        {
            locationReferences.emplace_back(*location);
        }
    }

    const CalculationData& InputData::GetCalculationData() const
    {
        return *calculationData;
    }

    const HydraulicLoads& InputData::GetHydraulicLoads() const
    {
        return *hydraulicLoads;
    }

    const vector<reference_wrapper<CalculationLocation>>& InputData::GetLocations() const
    {
        return locationReferences;
    }
}
