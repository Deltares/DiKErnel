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

#include <stdexcept>

#include "JsonConversionException.h"
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

        RevetmentCalculationInputBuilder builder;

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
                    ConvertTypeTopLayer(naturalStoneRevetmentLocationData->GetTopLayerType()), location.GetName(),
                    location.GetDamageData().GetInitialDamage(), location.GetProfileSchematizationData().GetTanA(),
                    naturalStoneRevetmentLocationData->GetThicknessTopLayer(), naturalStoneRevetmentLocationData->GetRelativeDensity());

                constructionProperties.SetPlungingCoefficientA(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetPlungingCoefficientA())));
                constructionProperties.SetPlungingCoefficientB(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetPlungingCoefficientB())));
                constructionProperties.SetPlungingCoefficientC(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetPlungingCoefficientC())));
                constructionProperties.SetPlungingCoefficientN(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetPlungingCoefficientN())));
                constructionProperties.SetSurgingCoefficientA(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetSurgingCoefficientA())));
                constructionProperties.SetSurgingCoefficientB(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetSurgingCoefficientB())));
                constructionProperties.SetSurgingCoefficientC(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetSurgingCoefficientC())));
                constructionProperties.SetSurgingCoefficientN(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetSurgingCoefficientN())));
                constructionProperties.SetSimilarityParameterThreshold(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetSimilarityParameterThreshold())));
                constructionProperties.SetUpperLimitLoadingAul(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetUpperLimitLoadingAul())));
                constructionProperties.SetUpperLimitLoadingBul(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetUpperLimitLoadingBul())));
                constructionProperties.SetUpperLimitLoadingCul(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetUpperLimitLoadingCul())));
                constructionProperties.SetLowerLimitLoadingAll(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetLowerLimitLoadingAll())));
                constructionProperties.SetLowerLimitLoadingBll(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetLowerLimitLoadingBll())));
                constructionProperties.SetLowerLimitLoadingCll(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetLowerLimitLoadingCll())));
                constructionProperties.SetDistanceMaximumWaveElevationAsmax(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetDistanceMaximumWaveElevationAsmax())));
                constructionProperties.SetDistanceMaximumWaveElevationBsmax(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetDistanceMaximumWaveElevationBsmax())));
                constructionProperties.SetNormativeWidthOfWaveImpactAwi(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetNormativeWidthOfWaveImpactAwi())));
                constructionProperties.SetNormativeWidthOfWaveImpactBwi(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetNormativeWidthOfWaveImpactBwi())));
                constructionProperties.SetWaveAngleImpactBetamax(
                    forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData->GetWaveAngleImpactBetamax())));

                builder.AddNaturalStoneLocation(constructionProperties);
            }
        }

        return builder.Build();
    }

    NaturalStoneRevetmentLocationConstructionProperties::TopLayerType JsonInputAdapter::ConvertTypeTopLayer(
        const JsonInputNaturalStoneRevetmentLocationData::TopLayerType topLayerType)
    {
        if (topLayerType == JsonInputNaturalStoneRevetmentLocationData::TopLayerType::NordicStone)
        {
            return NaturalStoneRevetmentLocationConstructionProperties::TopLayerType::NordicStone;
        }

        throw JsonConversionException("Cannot convert top layer type.");
    }

    unique_ptr<double> JsonInputAdapter::CreatePointerOfValue(
        const double* value)
    {
        return value != nullptr
                   ? make_unique<double>(*value)
                   : nullptr;
    }
}
