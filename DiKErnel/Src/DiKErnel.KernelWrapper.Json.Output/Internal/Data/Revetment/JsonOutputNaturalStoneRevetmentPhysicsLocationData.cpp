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

#include "JsonOutputDefinitions.h"
#include "JsonOutputNaturalStoneRevetmentDefinitions.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    using namespace Core;
    using namespace Integration;
    using namespace nlohmann;
    using namespace std;

    JsonOutputNaturalStoneRevetmentPhysicsLocationData::JsonOutputNaturalStoneRevetmentPhysicsLocationData(
        const LocationDependentOutput& locationOutput,
        const ILocationDependentInput& locationInput)
        : JsonOutputDamageLocationData(locationOutput, locationInput)
    {
        for (auto timeDependentOutput : locationOutput.GetTimeDependentOutputItems())
        {
            _timeDependentOutputItems.emplace_back(dynamic_cast<NaturalStoneRevetmentTimeDependentOutput*>(&timeDependentOutput.get()));
        }
    }

    ordered_json JsonOutputNaturalStoneRevetmentPhysicsLocationData::CreateJson() const
    {
        auto physicsJson = ordered_json(
            {
                {
                    JsonOutputDefinitions::CALCULATION_TYPE,
                    JsonOutputNaturalStoneRevetmentDefinitions::CALCULATION_TYPE_NATURAL_STONE
                }
            });

        for (int i = 0; i < static_cast<int>(_timeDependentOutputItems.size()); ++i)
        {
            const auto* outputItem = _timeDependentOutputItems[i];

            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::INCREMENT_DAMAGE][i] = outputItem->GetIncrementDamage();
            physicsJson[JsonOutputDefinitions::HYDRAULIC_LOAD][i] = outputItem->GetLoadingRevetment();
            physicsJson[JsonOutputDefinitions::SURF_SIMILARITY_PARAMETER][i] = outputItem->GetSurfSimilarityParameter();
            physicsJson[JsonOutputDefinitions::WAVE_STEEPNESS_DEEP_WATER][i] = outputItem->GetWaveSteepnessDeepWater();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::UPPER_LIMIT_LOADING][i] = outputItem->GetUpperLimitLoading();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::LOWER_LIMIT_LOADING][i] = outputItem->GetLowerLimitLoading();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::DEPTH_MAXIMUM_WAVE_LOAD][i] = outputItem->GetDepthMaximumWaveLoad();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION][i] = outputItem->GetDistanceMaximumWaveElevation();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::NORMATIVE_WIDTH_WAVE_IMPACT][i] = outputItem->GetNormativeWidthOfWaveImpact();
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::HYDRAULIC_LOAD][i] = nullptr;
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::WAVE_ANGLE_IMPACT][i] = nullptr;
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::RESISTANCE][i] = nullptr;
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::REFERENCE_TIME_DEGRADATION][i] = nullptr;
            physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::REFERENCE_DEGRADATION][i] = nullptr;

            SetPropertyWhenApplicable(physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::HYDRAULIC_LOAD][i], outputItem->GetHydraulicLoad());
            SetPropertyWhenApplicable(physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::WAVE_ANGLE_IMPACT][i], outputItem->GetWaveAngleImpact());
            SetPropertyWhenApplicable(physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::RESISTANCE][i], outputItem->GetResistance());
            SetPropertyWhenApplicable(physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::REFERENCE_TIME_DEGRADATION][i], outputItem->GetReferenceTimeDegradation());
            SetPropertyWhenApplicable(physicsJson[JsonOutputNaturalStoneRevetmentDefinitions::REFERENCE_DEGRADATION][i], outputItem->GetReferenceDegradation());
        }

        auto output = JsonOutputDamageLocationData::CreateJson();
        output[JsonOutputDefinitions::PHYSICS_REVETMENT] = physicsJson;
        return output;
    }

    void JsonOutputNaturalStoneRevetmentPhysicsLocationData::SetPropertyWhenApplicable(
        ordered_json& jsonObject,
        const double* value)
    {
        if (value != nullptr)
        {
            jsonObject = *value;
        }
    }
}
