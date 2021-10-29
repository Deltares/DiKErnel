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

#include "JsonOutputGrassRevetmentWaveRunupRayleighPhysicsLocationData.h"

#include "CalculationOutputAdapterHelper.h"
#include "JsonOutputDefinitions.h"
#include "JsonOutputGrassRevetmentWaveRunupRayleighDefinitions.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    using namespace Core;
    using namespace Integration;
    using namespace nlohmann;
    using namespace std;

    JsonOutputGrassRevetmentWaveRunupRayleighPhysicsLocationData::JsonOutputGrassRevetmentWaveRunupRayleighPhysicsLocationData(
        const LocationDependentOutput& locationOutput)
        : JsonOutputPhysicsLocationData(locationOutput)
    {
        for (const auto& timeDependentOutput : locationOutput.GetTimeDependentOutputItems())
        {
            _timeDependentOutputItems.push_back(dynamic_cast<GrassRevetmentWaveRunupRayleighTimeDependentOutput*>(&timeDependentOutput.get()));
        }
    }

    ordered_json JsonOutputGrassRevetmentWaveRunupRayleighPhysicsLocationData::CreateJson() const
    {
        auto output = JsonOutputPhysicsLocationData::CreateJson();
        auto& physicsJson = output.at(JsonOutputDefinitions::PHYSICS_REVETMENT);

        for (const auto* outputItem : _timeDependentOutputItems)
        {
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputGrassRevetmentWaveRunupRayleighDefinitions::INCREMENT_DAMAGE).push_back(outputItem->GetIncrementDamage());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputGrassRevetmentWaveRunupRayleighDefinitions::VERTICAL_DISTANCE_WATER_LEVEL_ELEVATION).push_back(
                outputItem->GetVerticalDistanceWaterLevelElevation());

            CalculationOutputAdapterHelper::PushPropertyWhenApplicable(
                CalculationOutputAdapterHelper::GetJsonElement(
                    physicsJson, JsonOutputGrassRevetmentWaveRunupRayleighDefinitions::WAVE_ANGLE_IMPACT),
                outputItem->GetWaveAngleImpact());
            CalculationOutputAdapterHelper::PushPropertyWhenApplicable(
                CalculationOutputAdapterHelper::GetJsonElement(
                    physicsJson, JsonOutputGrassRevetmentWaveRunupRayleighDefinitions::REPRESENTATIVE_WAVE_RUNUP_2P),
                outputItem->GetRepresentativeWaveRunup2P());
            CalculationOutputAdapterHelper::PushPropertyWhenApplicable(
                CalculationOutputAdapterHelper::GetJsonElement(
                    physicsJson, JsonOutputGrassRevetmentWaveRunupRayleighDefinitions::CUMULATIVE_OVERLOAD),
                outputItem->GetCumulativeOverload());
        }

        return output;
    }
}
