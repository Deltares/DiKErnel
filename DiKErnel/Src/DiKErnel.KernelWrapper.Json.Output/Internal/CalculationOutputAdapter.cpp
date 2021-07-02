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

#include "AsphaltRevetmentWaveImpactTimeDependentOutput.h"
#include "GrassRevetmentWaveImpactTimeDependentOutput.h"
#include "GrassRevetmentWaveRunupRayleighTimeDependentOutput.h"
#include "JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData.h"
#include "JsonOutputConversionException.h"
#include "JsonOutputDamageLocationData.h"
#include "JsonOutputGrassRevetmentWaveImpactPhysicsLocationData.h"
#include "JsonOutputGrassRevetmentWaveRunupRayleighPhysicsLocationData.h"
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
        const JsonOutputType outputType)
    {
        return make_unique<JsonOutputData>(
            GetTimes(calculationInput.GetTimeDependentInputItems()),
            GetJsonOutputLocations(calculationOutput.GetLocationDependentOutputItems(), calculationInput.GetLocationDependentInputItems(),
                                   outputType));
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
        const JsonOutputType outputType)
    {
        const auto createLocationDataFuncPtr = GetCreateLocationDataMethod(outputType);

        vector<unique_ptr<JsonOutputFailureLocationData>> jsonOutputLocationDataItems;

        for (auto i = 0; i < static_cast<int>(locationDependentOutputItems.size()); ++i)
        {
            jsonOutputLocationDataItems.emplace_back(
                createLocationDataFuncPtr(locationDependentOutputItems[i].get(), locationDependentInputItems[i].get()));
        }

        return jsonOutputLocationDataItems;
    }

    CalculationOutputAdapter::FuncPtr CalculationOutputAdapter::GetCreateLocationDataMethod(
        const JsonOutputType outputType)
    {
        switch (outputType)
        {
            case JsonOutputType::Failure:
                return &CreateJsonOutputFailureLocationData;
            case JsonOutputType::Damage:
                return &CreateJsonOutputDamageLocationData;
            case JsonOutputType::Physics:
                return &CreateJsonOutputPhysicsLocationData;
            default:
                throw JsonOutputConversionException("Invalid JsonOutputType.");
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
        const auto& locationTimeDependentOutputItem = locationOutput.GetTimeDependentOutputItems().front();

        if (const auto* asphalt1RevetmentWaveImpactLocationTimeDependentOutputItem = dynamic_cast<const
            AsphaltRevetmentWaveImpactTimeDependentOutput*>(
            &locationTimeDependentOutputItem.get()); asphalt1RevetmentWaveImpactLocationTimeDependentOutputItem != nullptr)
        {
            return make_unique<JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData>(locationOutput, locationInput);
        }

        if (const auto* grassRevetmentWaveImpactLocationTimeDependentOutputItem = dynamic_cast<const GrassRevetmentWaveImpactTimeDependentOutput*>(
            &locationTimeDependentOutputItem.get()); grassRevetmentWaveImpactLocationTimeDependentOutputItem != nullptr)
        {
            return make_unique<JsonOutputGrassRevetmentWaveImpactPhysicsLocationData>(locationOutput, locationInput);
        }

        if (const auto* grassRevetmentWaveRunupRayleighLocationTimeDependentOutputItem =
                    dynamic_cast<const GrassRevetmentWaveRunupRayleighTimeDependentOutput*>(&locationTimeDependentOutputItem.get());
            grassRevetmentWaveRunupRayleighLocationTimeDependentOutputItem != nullptr)
        {
            return make_unique<JsonOutputGrassRevetmentWaveRunupRayleighPhysicsLocationData>(locationOutput, locationInput);
        }

        if (const auto* naturalStoneRevetmentLocationTimeDependentOutputItem = dynamic_cast<const NaturalStoneRevetmentTimeDependentOutput*>(
            &locationTimeDependentOutputItem.get()); naturalStoneRevetmentLocationTimeDependentOutputItem != nullptr)
        {
            return make_unique<JsonOutputNaturalStoneRevetmentPhysicsLocationData>(locationOutput, locationInput);
        }

        throw JsonOutputConversionException("Invalid revetment type.");
    }
}
