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

#include "JsonOutputGrassRevetmentOvertoppingPhysicsLocationData.h"

#include "CalculationOutputAdapterHelper.h"
#include "JsonOutputDefinitions.h"
#include "JsonOutputGrassRevetmentDefinitions.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    using namespace Integration;
    using namespace nlohmann;

    JsonOutputGrassRevetmentOvertoppingPhysicsLocationData::JsonOutputGrassRevetmentOvertoppingPhysicsLocationData(
        const GrassRevetmentOvertoppingLocationDependentOutput& locationDependentOutput)
        : JsonOutputPhysicsLocationData(locationDependentOutput)
    {
        for (const auto& timeDependentOutput : locationDependentOutput.GetTimeDependentOutputItems())
        {
            _timeDependentOutputItems.push_back(dynamic_cast<GrassRevetmentOvertoppingTimeDependentOutput*>(&timeDependentOutput.get()));
        }
    }

    ordered_json JsonOutputGrassRevetmentOvertoppingPhysicsLocationData::CreateJson() const
    {
        auto output = JsonOutputPhysicsLocationData::CreateJson();
        auto& physicsJson = output.at(JsonOutputDefinitions::PHYSICS);

        for (const auto* outputItem : _timeDependentOutputItems)
        {
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputDefinitions::INCREMENT_DAMAGE).push_back(outputItem->GetIncrementDamage());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputGrassRevetmentDefinitions::VERTICAL_DISTANCE_WATER_LEVEL_ELEVATION).push_back(
                outputItem->GetVerticalDistanceWaterLevelElevation());

            CalculationOutputAdapterHelper::PushPropertyWhenApplicable(
                CalculationOutputAdapterHelper::GetJsonElement(
                    physicsJson, JsonOutputGrassRevetmentDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P), outputItem->GetRepresentativeWaveRunup2P());
            CalculationOutputAdapterHelper::PushPropertyWhenApplicable(
                CalculationOutputAdapterHelper::GetJsonElement(
                    physicsJson, JsonOutputGrassRevetmentDefinitions::CUMULATIVE_OVERLOAD), outputItem->GetCumulativeOverload());
        }

        return output;
    }
}
