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

#include "CalculationOutputAdapter.h"

#include "JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData.h"
#include "JsonOutputConversionException.h"
#include "JsonOutputGrassRevetmentWaveImpactPhysicsLocationData.h"
#include "JsonOutputGrassRevetmentWaveRunupRayleighPhysicsLocationData.h"
#include "JsonOutputNaturalStoneRevetmentPhysicsLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    using namespace Core;
    using namespace Integration;
    using namespace std;

    unique_ptr<JsonOutputData> CalculationOutputAdapter::AdaptCalculationOutput(
        const CalculationOutput& calculationOutput,
        const JsonOutputType outputType,
        const vector<pair<string, variant<double, string>>>& metaDataItems)
    {
        return make_unique<JsonOutputData>(GetJsonOutputLocations(calculationOutput.GetLocationDependentOutputItems(), outputType), metaDataItems);
    }

    vector<unique_ptr<JsonOutputFailureLocationData>> CalculationOutputAdapter::GetJsonOutputLocations(
        const vector<reference_wrapper<LocationDependentOutput>>& locationDependentOutputItems,
        const JsonOutputType outputType)
    {
        const auto& createLocationDataFuncPtr = GetCreateLocationDataMethod(outputType);

        vector<unique_ptr<JsonOutputFailureLocationData>> jsonOutputLocationDataItems;

        jsonOutputLocationDataItems.reserve(static_cast<int>(locationDependentOutputItems.size()));

        for (const auto& locationDependentOutputItem : locationDependentOutputItems)
        {
            jsonOutputLocationDataItems.push_back(createLocationDataFuncPtr(locationDependentOutputItem.get()));
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
        const LocationDependentOutput& locationOutput)
    {
        return make_unique<JsonOutputFailureLocationData>(locationOutput);
    }

    unique_ptr<JsonOutputFailureLocationData> CalculationOutputAdapter::CreateJsonOutputDamageLocationData(
        const LocationDependentOutput& locationOutput)
    {
        return make_unique<JsonOutputDamageLocationData>(locationOutput);
    }

    unique_ptr<JsonOutputFailureLocationData> CalculationOutputAdapter::CreateJsonOutputPhysicsLocationData(
        const LocationDependentOutput& locationOutput)
    {
        const auto& locationTimeDependentOutputItem = locationOutput.GetTimeDependentOutputItems().front();

        if (const auto* asphaltRevetmentWaveImpactLocationTimeDependentOutputItem = dynamic_cast<const
            AsphaltRevetmentWaveImpactTimeDependentOutput*>(
            &locationTimeDependentOutputItem.get()); asphaltRevetmentWaveImpactLocationTimeDependentOutputItem != nullptr)
        {
            return make_unique<JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData>(locationOutput);
        }

        if (const auto* grassRevetmentWaveImpactLocationTimeDependentOutputItem = dynamic_cast<const GrassRevetmentWaveImpactTimeDependentOutput*>(
            &locationTimeDependentOutputItem.get()); grassRevetmentWaveImpactLocationTimeDependentOutputItem != nullptr)
        {
            return make_unique<JsonOutputGrassRevetmentWaveImpactPhysicsLocationData>(locationOutput);
        }

        if (const auto* grassRevetmentWaveRunupRayleighLocationTimeDependentOutputItem =
                    dynamic_cast<const GrassRevetmentWaveRunupRayleighTimeDependentOutput*>(&locationTimeDependentOutputItem.get());
            grassRevetmentWaveRunupRayleighLocationTimeDependentOutputItem != nullptr)
        {
            return make_unique<JsonOutputGrassRevetmentWaveRunupRayleighPhysicsLocationData>(locationOutput);
        }

        if (const auto* naturalStoneRevetmentLocationTimeDependentOutputItem = dynamic_cast<const NaturalStoneRevetmentTimeDependentOutput*>(
            &locationTimeDependentOutputItem.get()); naturalStoneRevetmentLocationTimeDependentOutputItem != nullptr)
        {
            return make_unique<JsonOutputNaturalStoneRevetmentPhysicsLocationData>(locationOutput);
        }

        throw JsonOutputConversionException("Invalid revetment type.");
    }
}
