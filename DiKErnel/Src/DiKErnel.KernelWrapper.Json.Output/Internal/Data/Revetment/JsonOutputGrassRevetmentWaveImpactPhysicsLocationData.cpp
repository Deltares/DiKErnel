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

#include "JsonOutputGrassRevetmentWaveImpactPhysicsLocationData.h"

#include "CalculationOutputAdapterHelper.h"
#include "JsonOutputDefinitions.h"
#include "JsonOutputGrassRevetmentWaveImpactDefinitions.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    using namespace Core;
    using namespace Integration;
    using namespace nlohmann;
    using namespace std;

    JsonOutputGrassRevetmentWaveImpactPhysicsLocationData::JsonOutputGrassRevetmentWaveImpactPhysicsLocationData(
        const GrassRevetmentWaveImpactLocationDependentOutput& locationOutput)
        : JsonOutputPhysicsLocationData(locationOutput)
    {
        for (const auto& timeDependentOutput : locationOutput.GetTimeDependentOutputItems())
        {
            _timeDependentOutputItems.push_back(dynamic_cast<GrassRevetmentWaveImpactTimeDependentOutput*>(&timeDependentOutput.get()));
        }
    }

    ordered_json JsonOutputGrassRevetmentWaveImpactPhysicsLocationData::CreateJson() const
    {
        auto output = JsonOutputPhysicsLocationData::CreateJson();
        auto& physicsJson = output.at(JsonOutputDefinitions::PHYSICS_REVETMENT);

        for (const auto* outputItem : _timeDependentOutputItems)
        {
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputGrassRevetmentWaveImpactDefinitions::INCREMENT_DAMAGE).push_back(outputItem->GetIncrementDamage());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputDefinitions::HYDRAULIC_LOAD).push_back(outputItem->GetLoadingRevetment());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputGrassRevetmentWaveImpactDefinitions::UPPER_LIMIT_LOADING).push_back(outputItem->GetUpperLimitLoading());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputGrassRevetmentWaveImpactDefinitions::LOWER_LIMIT_LOADING).push_back(outputItem->GetLowerLimitLoading());

            CalculationOutputAdapterHelper::PushPropertyWhenApplicable(
                CalculationOutputAdapterHelper::GetJsonElement(physicsJson, JsonOutputGrassRevetmentWaveImpactDefinitions::MAXIMUM_WAVE_HEIGHT),
                outputItem->GetMaximumWaveHeight());
            CalculationOutputAdapterHelper::PushPropertyWhenApplicable(
                CalculationOutputAdapterHelper::GetJsonElement(physicsJson, JsonOutputGrassRevetmentWaveImpactDefinitions::MINIMUM_WAVE_HEIGHT),
                outputItem->GetMinimumWaveHeight());
            CalculationOutputAdapterHelper::PushPropertyWhenApplicable(
                CalculationOutputAdapterHelper::GetJsonElement(physicsJson, JsonOutputGrassRevetmentWaveImpactDefinitions::WAVE_ANGLE_IMPACT),
                outputItem->GetWaveAngleImpact());
            CalculationOutputAdapterHelper::PushPropertyWhenApplicable(
                CalculationOutputAdapterHelper::GetJsonElement(physicsJson, JsonOutputGrassRevetmentWaveImpactDefinitions::WAVE_HEIGHT_IMPACT),
                outputItem->GetWaveHeightImpact());
        }

        return output;
    }
}
