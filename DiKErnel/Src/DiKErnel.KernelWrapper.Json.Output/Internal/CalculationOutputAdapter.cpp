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

#include "AsphaltRevetmentWaveImpactLocationDependentOutput.h"
#include "GrassRevetmentWaveImpactLocationDependentOutput.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentOutput.h"
#include "JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData.h"
#include "JsonOutputConversionException.h"
#include "JsonOutputGrassRevetmentWaveImpactPhysicsLocationData.h"
#include "JsonOutputGrassRevetmentWaveRunupRayleighPhysicsLocationData.h"
#include "JsonOutputNaturalStoneRevetmentPhysicsLocationData.h"
#include "NaturalStoneRevetmentLocationDependentOutput.h"

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
        if (const auto* asphaltRevetmentWaveImpactLocationDependentOutput =
                    dynamic_cast<const AsphaltRevetmentWaveImpactLocationDependentOutput*>(&locationOutput);
            asphaltRevetmentWaveImpactLocationDependentOutput != nullptr)
        {
            return make_unique<JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData>(*asphaltRevetmentWaveImpactLocationDependentOutput);
        }

        if (const auto* grassRevetmentWaveImpactLocationDependentOutput =
                    dynamic_cast<const GrassRevetmentWaveImpactLocationDependentOutput*>(&locationOutput);
            grassRevetmentWaveImpactLocationDependentOutput != nullptr)
        {
            return make_unique<JsonOutputGrassRevetmentWaveImpactPhysicsLocationData>(*grassRevetmentWaveImpactLocationDependentOutput);
        }

        if (const auto* grassRevetmentWaveRunupRayleighLocationDependentOutput =
                    dynamic_cast<const GrassRevetmentWaveRunupRayleighLocationDependentOutput*>(&locationOutput);
            grassRevetmentWaveRunupRayleighLocationDependentOutput != nullptr)
        {
            return make_unique<JsonOutputGrassRevetmentWaveRunupRayleighPhysicsLocationData>(
                *grassRevetmentWaveRunupRayleighLocationDependentOutput);
        }

        if (const auto* naturalStoneRevetmentLocationDependentOutput =
                    dynamic_cast<const NaturalStoneRevetmentLocationDependentOutput*>(&locationOutput);
            naturalStoneRevetmentLocationDependentOutput != nullptr)
        {
            return make_unique<JsonOutputNaturalStoneRevetmentPhysicsLocationData>(*naturalStoneRevetmentLocationDependentOutput);
        }

        throw JsonOutputConversionException("Invalid revetment type.");
    }
}
