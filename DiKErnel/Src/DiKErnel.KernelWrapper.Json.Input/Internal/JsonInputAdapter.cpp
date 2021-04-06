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

            const auto* naturalStoneRevetmentLocationData = dynamic_cast<const JsonInputNaturalStoneRevetmentLocationData*>(
                &revetmentLocationData);

            if (naturalStoneRevetmentLocationData != nullptr)
            {
                const auto constructionProperties = CreateNaturalStoneConstructionProperties(location, *naturalStoneRevetmentLocationData);
                builder.AddNaturalStoneLocation(*constructionProperties);
            }

            const auto* grassRevetmentWaveImpactLocationData = dynamic_cast<const JsonInputGrassRevetmentWaveImpactLocationData*>(
                &revetmentLocationData);

            if (grassRevetmentWaveImpactLocationData != nullptr)
            {
                const auto constructionProperties = CreateGrassWaveImpactConstructionProperties(location, *grassRevetmentWaveImpactLocationData);
                builder.AddGrassWaveImpactLocation(*constructionProperties);
            }
        }

        return builder.Build();
    }

    unique_ptr<NaturalStoneRevetmentLocationConstructionProperties> JsonInputAdapter::CreateNaturalStoneConstructionProperties(
        const JsonInputLocationData& location,
        const JsonInputNaturalStoneRevetmentLocationData& naturalStoneRevetmentLocationData)
    {
        const auto& damageData = location.GetDamageData();
        const auto& profileSchematizationData = location.GetProfileSchematizationData();

        auto constructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            location.GetName(), profileSchematizationData.GetTanA(), profileSchematizationData.GetPositionZ(),
            ConvertTypeTopLayer(naturalStoneRevetmentLocationData.GetTopLayerType()),
            naturalStoneRevetmentLocationData.GetThicknessTopLayer(), naturalStoneRevetmentLocationData.GetRelativeDensity());

        constructionProperties->SetInitialDamage(forward<unique_ptr<double>>(CreatePointerOfValue(damageData.GetInitialDamage())));
        constructionProperties->SetFailureNumber(forward<unique_ptr<double>>(CreatePointerOfValue(damageData.GetFailureNumber())));

        constructionProperties->SetHydraulicLoadAp(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetHydraulicLoadAp())));
        constructionProperties->SetHydraulicLoadBp(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetHydraulicLoadBp())));
        constructionProperties->SetHydraulicLoadCp(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetHydraulicLoadCp())));
        constructionProperties->SetHydraulicLoadNp(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetHydraulicLoadNp())));
        constructionProperties->SetHydraulicLoadAs(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetHydraulicLoadAs())));
        constructionProperties->SetHydraulicLoadBs(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetHydraulicLoadBs())));
        constructionProperties->SetHydraulicLoadCs(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetHydraulicLoadCs())));
        constructionProperties->SetHydraulicLoadNs(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetHydraulicLoadNs())));
        constructionProperties->SetHydraulicLoadXib(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetHydraulicLoadXib())));
        constructionProperties->SetUpperLimitLoadingAul(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetUpperLimitLoadingAul())));
        constructionProperties->SetUpperLimitLoadingBul(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetUpperLimitLoadingBul())));
        constructionProperties->SetUpperLimitLoadingCul(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetUpperLimitLoadingCul())));
        constructionProperties->SetLowerLimitLoadingAll(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetLowerLimitLoadingAll())));
        constructionProperties->SetLowerLimitLoadingBll(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetLowerLimitLoadingBll())));
        constructionProperties->SetLowerLimitLoadingCll(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetLowerLimitLoadingCll())));
        constructionProperties->SetDistanceMaximumWaveElevationAsmax(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetDistanceMaximumWaveElevationAsmax())));
        constructionProperties->SetDistanceMaximumWaveElevationBsmax(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetDistanceMaximumWaveElevationBsmax())));
        constructionProperties->SetNormativeWidthOfWaveImpactAwi(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetNormativeWidthOfWaveImpactAwi())));
        constructionProperties->SetNormativeWidthOfWaveImpactBwi(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetNormativeWidthOfWaveImpactBwi())));
        constructionProperties->SetWaveAngleImpactBetamax(
            forward<unique_ptr<double>>(CreatePointerOfValue(naturalStoneRevetmentLocationData.GetWaveAngleImpactBetamax())));

        return constructionProperties;
    }

    NaturalStoneRevetmentTopLayerType JsonInputAdapter::ConvertTypeTopLayer(
        const JsonInputNaturalStoneRevetmentTopLayerType topLayerType)
    {
        if (topLayerType == JsonInputNaturalStoneRevetmentTopLayerType::NordicStone)
        {
            return NaturalStoneRevetmentTopLayerType::NordicStone;
        }

        throw JsonConversionException("Cannot convert top layer type.");
    }

    unique_ptr<GrassRevetmentWaveImpactLocationConstructionProperties> JsonInputAdapter::CreateGrassWaveImpactConstructionProperties(
        const JsonInputLocationData& location,
        const JsonInputGrassRevetmentWaveImpactLocationData& grassRevetmentWaveImpactLocationData)
    {
        const auto& damageData = location.GetDamageData();
        const auto& profileSchematizationData = location.GetProfileSchematizationData();

        auto constructionProperties = make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(
            location.GetName(), profileSchematizationData.GetPositionZ(),
            ConvertTypeTopLayer(grassRevetmentWaveImpactLocationData.GetTopLayerType()));

        constructionProperties->SetInitialDamage(forward<unique_ptr<double>>(CreatePointerOfValue(damageData.GetInitialDamage())));
        constructionProperties->SetFailureNumber(forward<unique_ptr<double>>(CreatePointerOfValue(damageData.GetFailureNumber())));

        constructionProperties->SetTimeLineAgwi(
            forward<unique_ptr<double>>(CreatePointerOfValue(grassRevetmentWaveImpactLocationData.GetTimeLineAgwi())));
        constructionProperties->SetTimeLineBgwi(
            forward<unique_ptr<double>>(CreatePointerOfValue(grassRevetmentWaveImpactLocationData.GetTimeLineBgwi())));
        constructionProperties->SetTimeLineCgwi(
            forward<unique_ptr<double>>(CreatePointerOfValue(grassRevetmentWaveImpactLocationData.GetTimeLineCgwi())));

        constructionProperties->SetMinimumWaveHeightTemax(
            forward<unique_ptr<double>>(CreatePointerOfValue(grassRevetmentWaveImpactLocationData.GetMinimumWaveHeightTemax())));
        constructionProperties->SetMaximumWaveHeightTemin(
            forward<unique_ptr<double>>(CreatePointerOfValue(grassRevetmentWaveImpactLocationData.GetMaximumWaveHeightTemin())));

        constructionProperties->SetWaveAngleImpactNwa(
            forward<unique_ptr<double>>(CreatePointerOfValue(grassRevetmentWaveImpactLocationData.GetWaveAngleImpactNwa())));
        constructionProperties->SetWaveAngleImpactQwa(
            forward<unique_ptr<double>>(CreatePointerOfValue(grassRevetmentWaveImpactLocationData.GetWaveAngleImpactQwa())));
        constructionProperties->SetWaveAngleImpactRwa(
            forward<unique_ptr<double>>(CreatePointerOfValue(grassRevetmentWaveImpactLocationData.GetWaveAngleImpactRwa())));

        constructionProperties->SetUpperLimitLoadingAul(
            forward<unique_ptr<double>>(CreatePointerOfValue(grassRevetmentWaveImpactLocationData.GetUpperLimitLoadingAul())));
        constructionProperties->SetLowerLimitLoadingAll(
            forward<unique_ptr<double>>(CreatePointerOfValue(grassRevetmentWaveImpactLocationData.GetLowerLimitLoadingAll())));

        return constructionProperties;
    }

    GrassRevetmentTopLayerType JsonInputAdapter::ConvertTypeTopLayer(
        const JsonInputGrassRevetmentTopLayerType topLayerType)
    {
        if (topLayerType == JsonInputGrassRevetmentTopLayerType::OpenSod)
        {
            return GrassRevetmentTopLayerType::OpenSod;
        }
        if (topLayerType == JsonInputGrassRevetmentTopLayerType::ClosedSod)
        {
            return GrassRevetmentTopLayerType::ClosedSod;
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
