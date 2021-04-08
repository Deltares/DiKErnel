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

#include "CalculationOutputAdapter.h"

#include "LocationDependentOutput.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    using namespace Core;
    using namespace std;

    unique_ptr<JsonOutputData> CalculationOutputAdapter::AdaptCalculationOutput(
        const CalculationOutput& calculationOutput,
        const ICalculationInput& calculationInput)
    {
        return make_unique<JsonOutputData>(
            GetTimes(calculationInput.GetTimeDependentInputItems()),
            GetJsonOutputLocations(calculationOutput.GetLocationDependentOutputItems(), calculationInput.GetLocationDependentInputItems()));
    }

    vector<int> CalculationOutputAdapter::GetTimes(
        const vector<reference_wrapper<ITimeDependentInput>>& timeDependentInputItems)
    {
        vector<int> times;

        for (auto i = 0; i < static_cast<int>(timeDependentInputItems.size()); ++i)
        {
            const auto& timeDependentInput = timeDependentInputItems[i].get();

            if (i == 0)
            {
                times.push_back(timeDependentInput.GetBeginTime());
            }

            times.push_back(timeDependentInput.GetEndTime());
        }

        return times;
    }

    vector<unique_ptr<JsonOutputLocationData>> CalculationOutputAdapter::GetJsonOutputLocations(
        const vector<reference_wrapper<LocationDependentOutput>>& locationDependentOutputItems,
        const vector<reference_wrapper<ILocationDependentInput>>& locationDependentInputItems)
    {
        vector<unique_ptr<JsonOutputLocationData>> jsonOutputLocationDataItems;

        for (auto i = 0; i < static_cast<int>(locationDependentOutputItems.size()); ++i)
        {
            const auto& locationOutput = locationDependentOutputItems[i].get();

            jsonOutputLocationDataItems.push_back(make_unique<JsonOutputLocationData>(
                locationDependentInputItems[i].get().GetName(),
                locationOutput.GetDamages(),
                locationOutput.GetTimeOfFailure()));
        }

        return jsonOutputLocationDataItems;
    }
}
