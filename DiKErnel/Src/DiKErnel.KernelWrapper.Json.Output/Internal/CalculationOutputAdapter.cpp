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

#include "JsonConversionException.h"
#include "JsonOutputDamageLocationData.h"
#include "JsonOutputNaturalStoneRevetmentPhysicsLocationData.h"
#include "NaturalStoneRevetmentLocationDependentInput.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    using namespace Core;
    using namespace Integration;
    using namespace std;

    unique_ptr<JsonOutputData> CalculationOutputAdapter::AdaptCalculationOutput(
        const CalculationOutput& calculationOutput,
        const ICalculationInput& calculationInput,
        const JsonProcessType processType)
    {
        return make_unique<JsonOutputData>(
            GetTimes(calculationInput.GetTimeDependentInputItems()),
            GetJsonOutputLocations(calculationOutput.GetLocationDependentOutputItems(), calculationInput.GetLocationDependentInputItems(),
                                   processType));
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

    vector<unique_ptr<JsonOutputFailureLocationData>> CalculationOutputAdapter::GetJsonOutputLocations(
        const vector<reference_wrapper<LocationDependentOutput>>& locationDependentOutputItems,
        const vector<reference_wrapper<ILocationDependentInput>>& locationDependentInputItems,
        const JsonProcessType processType)
    {
        const auto createLocationDataFuncPtr = GetCreateLocationDataMethod(processType);

        vector<unique_ptr<JsonOutputFailureLocationData>> jsonOutputLocationDataItems;

        for (auto i = 0; i < static_cast<int>(locationDependentOutputItems.size()); ++i)
        {
            jsonOutputLocationDataItems.push_back(
                createLocationDataFuncPtr(locationDependentOutputItems[i].get(), locationDependentInputItems[i].get()));
        }

        return jsonOutputLocationDataItems;
    }

    CalculationOutputAdapter::FuncPtr CalculationOutputAdapter::GetCreateLocationDataMethod(
        const JsonProcessType processType)
    {
        switch (processType)
        {
            case JsonProcessType::Failure:
                return &CreateJsonOutputFailureLocationData;
            case JsonProcessType::Damage:
                return &CreateJsonOutputDamageLocationData;
            case JsonProcessType::Physics:
                return &CreateJsonOutputPhysicsLocationData;
            default:
                throw JsonConversionException("Invalid JsonProcessType");
        }
    }

    unique_ptr<JsonOutputFailureLocationData> CalculationOutputAdapter::CreateJsonOutputFailureLocationData(
        const LocationDependentOutput& locationOutput,
        const ILocationDependentInput& locationInput)
    {
        return make_unique<JsonOutputFailureLocationData>(locationOutput, locationInput);
    }

    unique_ptr<JsonOutputFailureLocationData> CalculationOutputAdapter::CreateJsonOutputDamageLocationData(
        const LocationDependentOutput& locationOutput,
        const ILocationDependentInput& locationInput)
    {
        return make_unique<JsonOutputDamageLocationData>(locationOutput, locationInput);
    }

    unique_ptr<JsonOutputFailureLocationData> CalculationOutputAdapter::CreateJsonOutputPhysicsLocationData(
        const LocationDependentOutput& locationOutput,
        const ILocationDependentInput& locationInput)
    {
        if (const auto* naturalStoneRevetmentLocationDependentInput = dynamic_cast<const NaturalStoneRevetmentLocationDependentInput*>(
            &locationInput); naturalStoneRevetmentLocationDependentInput != nullptr)
        {
            return make_unique<JsonOutputNaturalStoneRevetmentPhysicsLocationData>(locationOutput, *naturalStoneRevetmentLocationDependentInput);
        }

        throw JsonConversionException("Invalid revetment type");
    }
}
