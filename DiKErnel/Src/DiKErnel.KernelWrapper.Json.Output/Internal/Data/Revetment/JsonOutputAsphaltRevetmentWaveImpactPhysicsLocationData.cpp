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
        const AsphaltRevetmentWaveImpactLocationDependentOutput& locationOutput)
        : JsonOutputPhysicsLocationData(locationOutput)
    {
        for (const auto& timeDependentOutput : locationOutput.GetTimeDependentOutputItems())
        {
            _timeDependentOutputItems.push_back(dynamic_cast<AsphaltRevetmentWaveImpactTimeDependentOutput*>(&timeDependentOutput.get()));
        }
    }

    ordered_json JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData::CreateJson() const
    {
        auto output = JsonOutputPhysicsLocationData::CreateJson();
        auto& physicsJson = output.at(JsonOutputDefinitions::PHYSICS_REVETMENT);

        const auto asphaltRevetmentWaveImpactLocationDependentOutput = dynamic_cast<const AsphaltRevetmentWaveImpactLocationDependentOutput*>(
            &GetLocationDependentOutput());

        CalculationOutputAdapterHelper::GetJsonElement(physicsJson, JsonOutputAsphaltRevetmentWaveImpactDefinitions::OUTER_SLOPE) =
                asphaltRevetmentWaveImpactLocationDependentOutput->GetOuterSlope();

        for (const auto* outputItem : _timeDependentOutputItems)
        {
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputAsphaltRevetmentWaveImpactDefinitions::INCREMENT_DAMAGE).push_back(outputItem->GetIncrementDamage());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputAsphaltRevetmentWaveImpactDefinitions::LOG_FAILURE_TENSION).push_back(outputItem->GetLogFailureTension());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputAsphaltRevetmentWaveImpactDefinitions::MAXIMUM_PEAK_STRESS).push_back(outputItem->GetMaximumPeakStress());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputAsphaltRevetmentWaveImpactDefinitions::STIFFNESS_RELATION).push_back(outputItem->GetStiffnessRelation());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputAsphaltRevetmentWaveImpactDefinitions::COMPUTATIONAL_THICKNESS).push_back(
                outputItem->GetComputationalThickness());
            CalculationOutputAdapterHelper::GetJsonElement(
                physicsJson, JsonOutputAsphaltRevetmentWaveImpactDefinitions::EQUIVALENT_ELASTIC_MODULUS).push_back(
                outputItem->GetEquivalentElasticModulus());
        }

        return output;
    }
}
