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

#include "JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData.h"

#include "CalculationOutputAdapterHelper.h"
#include "JsonOutputAsphaltRevetmentWaveImpactDefinitions.h"
#include "JsonOutputDefinitions.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    using namespace Core;
    using namespace Integration;
    using namespace nlohmann;
    using namespace std;

    JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData::JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData(
        const LocationDependentOutput& locationOutput,
        const ILocationDependentInput& locationInput)
        : JsonOutputDamageLocationData(locationOutput, locationInput)
    {
        for (auto timeDependentOutput : locationOutput.GetTimeDependentOutputItems())
        {
            _timeDependentOutputItems.emplace_back(dynamic_cast<AsphaltRevetmentWaveImpactTimeDependentOutput*>(&timeDependentOutput.get()));
        }
    }

    ordered_json JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData::CreateJson() const
    {
        auto physicsJson = ordered_json(
            {
                {
                    JsonOutputDefinitions::CALCULATION_TYPE,
                    JsonOutputAsphaltRevetmentWaveImpactDefinitions::CALCULATION_TYPE
                }
            });

        for (auto i = 0; i < static_cast<int>(_timeDependentOutputItems.size()); ++i)
        {
            const auto* outputItem = _timeDependentOutputItems[i];

            physicsJson[JsonOutputAsphaltRevetmentWaveImpactDefinitions::INCREMENT_DAMAGE][i] = outputItem->GetIncrementDamage();
            physicsJson[JsonOutputAsphaltRevetmentWaveImpactDefinitions::LOG_FAILURE_TENSION][i] = outputItem->GetLogFailureTension();
            physicsJson[JsonOutputAsphaltRevetmentWaveImpactDefinitions::MAXIMUM_PEAK_STRESS][i] = outputItem->GetMaximumPeakStress();
            physicsJson[JsonOutputAsphaltRevetmentWaveImpactDefinitions::STIFFNESS_RELATION][i] = outputItem->GetStiffnessRelation();
            physicsJson[JsonOutputAsphaltRevetmentWaveImpactDefinitions::COMPUTATIONAL_THICKNESS][i] = outputItem->GetComputationalThickness();
            physicsJson[JsonOutputAsphaltRevetmentWaveImpactDefinitions::EQUIVALENT_ELASTIC_MODULUS][i] =
                    outputItem->GetEquivalentElasticModulus();
        }

        auto output = JsonOutputDamageLocationData::CreateJson();
        output[JsonOutputDefinitions::PHYSICS_REVETMENT] = physicsJson;
        return output;
    }
}
