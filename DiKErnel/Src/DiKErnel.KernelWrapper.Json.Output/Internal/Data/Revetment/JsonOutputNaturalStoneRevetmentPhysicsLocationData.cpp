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

#include "JsonOutputNaturalStoneRevetmentPhysicsLocationData.h"

#include "CalculationOutputAdapterHelper.h"
#include "JsonOutputDefinitions.h"
#include "JsonOutputNaturalStoneRevetmentDefinitions.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    using namespace Core;
    using namespace Integration;
    using namespace nlohmann;
    using namespace std;

    JsonOutputNaturalStoneRevetmentPhysicsLocationData::JsonOutputNaturalStoneRevetmentPhysicsLocationData(
        const NaturalStoneRevetmentLocationDependentOutput& locationDependentOutput)
        : JsonOutputPhysicsLocationData(locationDependentOutput)
    {
        for (const auto& timeDependentOutput : locationDependentOutput.GetTimeDependentOutputItems())
        {
            _timeDependentOutputItems.push_back(dynamic_cast<NaturalStoneRevetmentTimeDependentOutput*>(&timeDependentOutput.get()));
        }
    }

    ordered_json JsonOutputNaturalStoneRevetmentPhysicsLocationData::CreateJson() const
    {
        auto output = JsonOutputPhysicsLocationData::CreateJson();
        auto& physicsJson = output.at(JsonOutputDefinitions::PHYSICS);

        for (const auto* outputItem : _timeDependentOutputItems)
        {
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::INCREMENT_DAMAGE).push_back(outputItem->GetIncrementDamage());

            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::OUTER_SLOPE).push_back(outputItem->GetOuterSlope());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::SLOPE_UPPER_LEVEL).push_back(outputItem->GetSlopeUpperLevel());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::SLOPE_UPPER_POSITION).push_back(outputItem->GetSlopeUpperPosition());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::SLOPE_LOWER_LEVEL).push_back(outputItem->GetSlopeLowerLevel());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::SLOPE_LOWER_POSITION).push_back(outputItem->GetSlopeLowerPosition());

            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputDefinitions::HYDRAULIC_LOAD).push_back(outputItem->GetLoadingRevetment());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::SURF_SIMILARITY_PARAMETER).push_back(
                outputItem->GetSurfSimilarityParameter());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::WAVE_STEEPNESS_DEEP_WATER).push_back(
                outputItem->GetWaveSteepnessDeepWater());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::UPPER_LIMIT_LOADING).push_back(outputItem->GetUpperLimitLoading());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::LOWER_LIMIT_LOADING).push_back(outputItem->GetLowerLimitLoading());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::DEPTH_MAXIMUM_WAVE_LOAD).push_back(outputItem->GetDepthMaximumWaveLoad());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION).push_back(
                outputItem->GetDistanceMaximumWaveElevation());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::NORMATIVE_WIDTH_WAVE_IMPACT).push_back(
                outputItem->GetNormativeWidthOfWaveImpact());

            CalculationOutputAdapterHelper::PushPropertyWhenApplicable(
                CalculationOutputAdapterHelper::GetJsonElement(physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::HYDRAULIC_LOAD),
                outputItem->GetHydraulicLoad());
            CalculationOutputAdapterHelper::PushPropertyWhenApplicable(
                CalculationOutputAdapterHelper::GetJsonElement(physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::WAVE_ANGLE_IMPACT),
                outputItem->GetWaveAngleImpact());
            CalculationOutputAdapterHelper::PushPropertyWhenApplicable(
                CalculationOutputAdapterHelper::GetJsonElement(physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::RESISTANCE),
                outputItem->GetResistance());
            CalculationOutputAdapterHelper::PushPropertyWhenApplicable(
                CalculationOutputAdapterHelper::GetJsonElement(physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::REFERENCE_TIME_DEGRADATION),
                outputItem->GetReferenceTimeDegradation());
            CalculationOutputAdapterHelper::PushPropertyWhenApplicable(
                CalculationOutputAdapterHelper::GetJsonElement(physicsJson, JsonOutputNaturalStoneRevetmentDefinitions::REFERENCE_DEGRADATION),
                outputItem->GetReferenceDegradation());
        }

        return output;
    }
}
