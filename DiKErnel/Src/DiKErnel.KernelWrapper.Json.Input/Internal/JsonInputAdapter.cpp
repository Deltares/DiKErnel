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

#include "JsonInputAdapter.h"

#include "JsonInputNaturalStoneRevetmentLocationData.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"
#include "RevetmentCalculationInputBuilder.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace Core;
    using namespace Integration;
    using namespace std;

    unique_ptr<ICalculationInput> JsonInputAdapter::AdaptJsonInputData(
        const JsonInputData& jsonInputData)
    {
        const auto& calculationData = jsonInputData.GetCalculationData();
        const auto& hydraulicData = calculationData.GetHydraulicData();

        RevetmentCalculationInputBuilder builder(hydraulicData.GetWaveAngleMaximum());

        const auto& times = calculationData.GetTimes();
        const auto& timeDependentData = hydraulicData.GetTimeDependentHydraulicData();

        for (auto i = 0; i < static_cast<int>(times.size()) - 1; i++)
        {
            const auto& timeDependentDataItem = timeDependentData[i].get();

            builder.AddTimeStep(times[i], times[i + 1], timeDependentDataItem.GetWaterLevel(), timeDependentDataItem.GetWaveHeightHm0(),
                                timeDependentDataItem.GetWavePeriodTm10(), timeDependentDataItem.GetWaveAngle());
        }

        const auto& locations = calculationData.GetLocationData();

        for (const auto& locationReference : locations)
        {
            const auto& location = locationReference.get();
            const auto& revetmentLocationData = location.GetRevetmentLocationData();

            const auto* naturalStoneRevetmentLocationData = dynamic_cast<const JsonInputNaturalStoneRevetmentLocationData*>(&revetmentLocationData);

            if (naturalStoneRevetmentLocationData != nullptr)
            {
                NaturalStoneRevetmentLocationConstructionProperties constructionProperties(
                    location.GetDamageData().GetInitialDamage(), location.GetProfileSchematizationData().GetTanA(),
                    naturalStoneRevetmentLocationData->GetThicknessTopLayer());
                constructionProperties.SetRelativeDensity(make_unique<double>(naturalStoneRevetmentLocationData->GetRelativeDensity()));
                constructionProperties.SetPlungingCoefficientA(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetPlungingCoefficientA()));
                constructionProperties.SetPlungingCoefficientB(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetPlungingCoefficientB()));
                constructionProperties.SetPlungingCoefficientC(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetPlungingCoefficientC()));
                constructionProperties.SetPlungingCoefficientN(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetPlungingCoefficientN()));
                constructionProperties.SetSurgingCoefficientA(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetSurgingCoefficientA()));
                constructionProperties.SetSurgingCoefficientB(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetSurgingCoefficientB()));
                constructionProperties.SetSurgingCoefficientC(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetSurgingCoefficientC()));
                constructionProperties.SetSurgingCoefficientN(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetSurgingCoefficientN()));
                constructionProperties.SetSimilarityParameterThreshold(
                    CreatePointerOfValue(naturalStoneRevetmentLocationData->GetSimilarityParameterThreshold()));

                builder.AddNaturalStoneLocation(constructionProperties);
            }
        }

        return builder.Build();
    }

    unique_ptr<double> JsonInputAdapter::CreatePointerOfValue(
        const double* value)
    {
        return value != nullptr
                   ? make_unique<double>(*value)
                   : nullptr;
    }
}
