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
        : JsonOutputDamageLocationData(locationOutput)
    {
        for (const auto& timeDependentOutput : locationOutput.GetTimeDependentOutputItems())
        {
            _timeDependentOutputItems.push_back(dynamic_cast<NaturalStoneRevetmentTimeDependentOutput*>(&timeDependentOutput.get()));
        }
    }

    ordered_json JsonOutputNaturalStoneRevetmentPhysicsLocationData::CreateJson() const
    {
        auto physicsJson = ordered_json(
            {
                {
                    JsonOutputDefinitions::Z,
                    GetLocationOutput().GetZ()
                }
            });

        for (auto i = 0; i < static_cast<int>(_timeDependentOutputItems.size()); ++i)
        {
            const auto* outputItem = _timeDependentOutputItems[i];

            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::INCREMENT_DAMAGE][i] = outputItem->GetIncrementDamage();

            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::OUTER_SLOPE][i] = outputItem->GetOuterSlope();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::SLOPE_UPPER_LEVEL][i] = outputItem->GetSlopeUpperLevel();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::SLOPE_UPPER_POSITION][i] = outputItem->GetSlopeUpperPosition();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::SLOPE_LOWER_LEVEL][i] = outputItem->GetSlopeLowerLevel();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::SLOPE_LOWER_POSITION][i] = outputItem->GetSlopeLowerPosition();

            physicsJson[JsonOutputDefinitions::HYDRAULIC_LOAD][i] = outputItem->GetLoadingRevetment();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::SURF_SIMILARITY_PARAMETER][i] = outputItem->GetSurfSimilarityParameter();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::WAVE_STEEPNESS_DEEP_WATER][i] = outputItem->GetWaveSteepnessDeepWater();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::UPPER_LIMIT_LOADING][i] = outputItem->GetUpperLimitLoading();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::LOWER_LIMIT_LOADING][i] = outputItem->GetLowerLimitLoading();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::DEPTH_MAXIMUM_WAVE_LOAD][i] = outputItem->GetDepthMaximumWaveLoad();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION][i] =
                    outputItem->GetDistanceMaximumWaveElevation();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::NORMATIVE_WIDTH_WAVE_IMPACT][i] = outputItem->GetNormativeWidthOfWaveImpact();

            CalculationOutputAdapterHelper::SetPropertyWhenApplicable(physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::HYDRAULIC_LOAD][i],
                                                                      outputItem->GetHydraulicLoad());
            CalculationOutputAdapterHelper::SetPropertyWhenApplicable(physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::WAVE_ANGLE_IMPACT][i],
                                                                      outputItem->GetWaveAngleImpact());
            CalculationOutputAdapterHelper::SetPropertyWhenApplicable(physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::RESISTANCE][i],
                                                                      outputItem->GetResistance());
            CalculationOutputAdapterHelper::SetPropertyWhenApplicable(
                physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::REFERENCE_TIME_DEGRADATION][i], outputItem->GetReferenceTimeDegradation());
            CalculationOutputAdapterHelper::SetPropertyWhenApplicable(
                physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::REFERENCE_DEGRADATION][i], outputItem->GetReferenceDegradation());
        }

        auto output = JsonOutputDamageLocationData::CreateJson();
        output[JsonOutputDefinitions::PHYSICS_REVETMENT] = physicsJson;
        return output;
    }
}
