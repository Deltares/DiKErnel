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
        const LocationDependentOutput& locationOutput)
        : JsonOutputPhysicsLocationData(locationOutput)
    {
        for (const auto& timeDependentOutput : locationOutput.GetTimeDependentOutputItems())
        {
            _timeDependentOutputItems.push_back(dynamic_cast<NaturalStoneRevetmentTimeDependentOutput*>(&timeDependentOutput.get()));
        }
    }

    ordered_json JsonOutputNaturalStoneRevetmentPhysicsLocationData::CreateJson() const
    {
        auto output = JsonOutputPhysicsLocationData::CreateJson();
        auto& physicsJson = output[JsonOutputDefinitions::PHYSICS_REVETMENT];

        for (auto i = 0; i < static_cast<int>(_timeDependentOutputItems.size()); ++i)
        {
            const auto* outputItem = _timeDependentOutputItems.at(i);

            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::INCREMENT_DAMAGE].at(i) = outputItem->GetIncrementDamage();

            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::OUTER_SLOPE].at(i) = outputItem->GetOuterSlope();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::SLOPE_UPPER_LEVEL].at(i) = outputItem->GetSlopeUpperLevel();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::SLOPE_UPPER_POSITION].at(i) = outputItem->GetSlopeUpperPosition();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::SLOPE_LOWER_LEVEL].at(i) = outputItem->GetSlopeLowerLevel();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::SLOPE_LOWER_POSITION].at(i) = outputItem->GetSlopeLowerPosition();

            physicsJson[JsonOutputDefinitions::HYDRAULIC_LOAD].at(i) = outputItem->GetLoadingRevetment();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::SURF_SIMILARITY_PARAMETER].at(i) = outputItem->GetSurfSimilarityParameter();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::WAVE_STEEPNESS_DEEP_WATER].at(i) = outputItem->GetWaveSteepnessDeepWater();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::UPPER_LIMIT_LOADING].at(i) = outputItem->GetUpperLimitLoading();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::LOWER_LIMIT_LOADING].at(i) = outputItem->GetLowerLimitLoading();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::DEPTH_MAXIMUM_WAVE_LOAD].at(i) = outputItem->GetDepthMaximumWaveLoad();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION].at(i) =
                    outputItem->GetDistanceMaximumWaveElevation();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::NORMATIVE_WIDTH_WAVE_IMPACT].at(i) = outputItem->
                    GetNormativeWidthOfWaveImpact();

            CalculationOutputAdapterHelper::SetPropertyWhenApplicable(physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::HYDRAULIC_LOAD].at(i),
                                                                      outputItem->GetHydraulicLoad());
            CalculationOutputAdapterHelper::SetPropertyWhenApplicable(
                physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::WAVE_ANGLE_IMPACT].at(i),
                outputItem->GetWaveAngleImpact());
            CalculationOutputAdapterHelper::SetPropertyWhenApplicable(physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::RESISTANCE].at(i),
                                                                      outputItem->GetResistance());
            CalculationOutputAdapterHelper::SetPropertyWhenApplicable(
                physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::REFERENCE_TIME_DEGRADATION].at(i),
                outputItem->GetReferenceTimeDegradation());
            CalculationOutputAdapterHelper::SetPropertyWhenApplicable(
                physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::REFERENCE_DEGRADATION].at(i), outputItem->GetReferenceDegradation());
        }

        return output;
    }
}
