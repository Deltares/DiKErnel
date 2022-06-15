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

#include "JsonInputAdapter.h"

#include "JsonInputConversionException.h"
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

        const auto& dikeProfileData = calculationData.GetDikeProfileData();

        for (const auto& dikeProfilePointReference : dikeProfileData.GetDikeProfilePoints())
        {
            const auto& dikeProfilePoint = dikeProfilePointReference.get();
            const auto characteristicPointType = ConvertCharacteristicPointType(dikeProfilePoint.GetCharacteristicPointType());

            builder.AddDikeProfilePoint(dikeProfilePoint.GetX(), dikeProfilePoint.GetZ(), characteristicPointType.get());
        }

        const auto& times = calculationData.GetTimes();
        const auto& timeDependentData = hydraulicData.GetTimeDependentHydraulicData();

        for (auto i = 0; i < static_cast<int>(times.size()) - 1; ++i)
        {
            const auto& timeDependentDataItem = timeDependentData.at(i).get();

            builder.AddTimeStep(times.at(i), times.at(i + 1), timeDependentDataItem.GetWaterLevel(), timeDependentDataItem.GetWaveHeightHm0(),
                                timeDependentDataItem.GetWavePeriodTm10(), timeDependentDataItem.GetWaveAngle());
        }

        const auto& locationReferences = calculationData.GetLocationData();
        const auto& calculationDefinitionReferences = calculationData.GetCalculationDefinitionData();

        for (const auto& locationReference : locationReferences)
        {
            const auto& location = locationReference.get();

            if (const auto* asphaltWaveImpactLocationData = dynamic_cast<const JsonInputAsphaltWaveImpactLocationData*>(&location);
                asphaltWaveImpactLocationData != nullptr)
            {
                const auto& constructionProperties = CreateAsphaltWaveImpactConstructionProperties(
                    *asphaltWaveImpactLocationData,
                    GetCalculationDefinition<JsonInputAsphaltWaveImpactCalculationDefinitionData>(
                        calculationDefinitionReferences, JsonInputCalculationType::AsphaltWaveImpact));
                builder.AddAsphaltWaveImpactLocation(*constructionProperties);
            }

            if (const auto* grassWaveImpactLocationData = dynamic_cast<const JsonInputGrassWaveImpactLocationData*>(&location);
                grassWaveImpactLocationData != nullptr)
            {
                const auto& constructionProperties = CreateGrassWaveImpactConstructionProperties(*grassWaveImpactLocationData);
                builder.AddGrassWaveImpactLocation(*constructionProperties);
            }

            if (const auto* grassWaveRunupRayleighLocationData = dynamic_cast<const JsonInputGrassWaveRunupRayleighLocationData*>(&location);
                grassWaveRunupRayleighLocationData != nullptr)
            {
                const auto& constructionProperties = CreateGrassWaveRunupRayleighConstructionProperties(*grassWaveRunupRayleighLocationData);
                builder.AddGrassWaveRunupRayleighLocation(*constructionProperties);
            }

            if (const auto* naturalStoneLocationData = dynamic_cast<const JsonInputNaturalStoneLocationData*>(&location);
                naturalStoneLocationData != nullptr)
            {
                const auto& constructionProperties = CreateNaturalStoneConstructionProperties(
                    *naturalStoneLocationData,
                    GetCalculationDefinition<JsonInputNaturalStoneCalculationDefinitionData>(
                        calculationDefinitionReferences, JsonInputCalculationType::NaturalStone));
                builder.AddNaturalStoneLocation(*constructionProperties);
            }
        }

        return builder.Build();
    }

    template <typename T>
    const T* JsonInputAdapter::GetCalculationDefinition(
        const map<JsonInputCalculationType, reference_wrapper<JsonInputCalculationDefinitionData>>& calculationDefinitions,
        const JsonInputCalculationType calculationType)
    {
        if (const auto& keyExists = calculationDefinitions.find(calculationType); keyExists != calculationDefinitions.end())
        {
            return dynamic_cast<const T*>(&calculationDefinitions.at(calculationType).get());
        }

        return nullptr;
    }

    unique_ptr<CharacteristicPointType> JsonInputAdapter::ConvertCharacteristicPointType(
        const JsonInputCharacteristicPointType* jsonCharacteristicPointType)
    {
        unique_ptr<CharacteristicPointType> characteristicPointType = nullptr;

        if (jsonCharacteristicPointType != nullptr)
        {
            switch (*jsonCharacteristicPointType)
            {
                case JsonInputCharacteristicPointType::OuterToe:
                    characteristicPointType = make_unique<CharacteristicPointType>(CharacteristicPointType::OuterToe);
                    break;
                case JsonInputCharacteristicPointType::OuterCrest:
                    characteristicPointType = make_unique<CharacteristicPointType>(CharacteristicPointType::OuterCrest);
                    break;
                case JsonInputCharacteristicPointType::CrestOuterBerm:
                    characteristicPointType = make_unique<CharacteristicPointType>(CharacteristicPointType::CrestOuterBerm);
                    break;
                case JsonInputCharacteristicPointType::NotchOuterBerm:
                    characteristicPointType = make_unique<CharacteristicPointType>(CharacteristicPointType::NotchOuterBerm);
                    break;
                default:
                    throw JsonInputConversionException("Cannot convert characteristic point type.");
            }
        }

        return characteristicPointType;
    }

    unique_ptr<AsphaltRevetmentWaveImpactLocationConstructionProperties> JsonInputAdapter::CreateAsphaltWaveImpactConstructionProperties(
        const JsonInputAsphaltWaveImpactLocationData& location,
        const JsonInputAsphaltWaveImpactCalculationDefinitionData* calculationDefinition)
    {
        auto constructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            location.GetX(), location.GetOuterSlope(), ConvertTopLayerType(location.GetTopLayerType()), location.GetFailureTension(),
            location.GetSoilElasticity(), location.GetThicknessUpperLayer(), location.GetElasticModulusUpperLayer());

        constructionProperties->SetInitialDamage(forward<unique_ptr<double>>(CreatePointerOfValue(location.GetInitialDamage())));

        constructionProperties->SetThicknessSubLayer(
            forward<unique_ptr<double>>(CreatePointerOfValue(location.GetThicknessSubLayer())));
        constructionProperties->SetElasticModulusSubLayer(
            forward<unique_ptr<double>>(CreatePointerOfValue(location.GetElasticModulusSubLayer())));

        if (calculationDefinition != nullptr)
        {
            constructionProperties->SetFailureNumber(forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetFailureNumber())));
            constructionProperties->SetDensityOfWater(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetDensityOfWater())));

            constructionProperties->SetAverageNumberOfWavesCtm(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetAverageNumberOfWavesCtm())));

            constructionProperties->SetFatigueAlpha(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetFatigueAlpha())));
            constructionProperties->SetFatigueBeta(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetFatigueBeta())));

            constructionProperties->SetImpactNumberC(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetImpactNumberC())));
            constructionProperties->SetStiffnessRelationNu(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetStiffnessRelationNu())));

            constructionProperties->SetWidthFactors(
                forward<unique_ptr<vector<pair<double, double>>>>(CreatePointerOfValue(calculationDefinition->GetWidthFactors())));
            constructionProperties->SetDepthFactors(
                forward<unique_ptr<vector<pair<double, double>>>>(CreatePointerOfValue(calculationDefinition->GetDepthFactors())));
            constructionProperties->SetImpactFactors(
                forward<unique_ptr<vector<pair<double, double>>>>(CreatePointerOfValue(calculationDefinition->GetImpactFactors())));
        }

        return constructionProperties;
    }

    AsphaltRevetmentTopLayerType JsonInputAdapter::ConvertTopLayerType(
        const JsonInputAsphaltRevetmentTopLayerType topLayerType)
    {
        if (topLayerType == JsonInputAsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete)
        {
            return AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete;
        }

        throw JsonInputConversionException("Cannot convert top layer type.");
    }

    unique_ptr<GrassRevetmentWaveImpactLocationConstructionProperties> JsonInputAdapter::CreateGrassWaveImpactConstructionProperties(
        const JsonInputGrassWaveImpactLocationData& location)
    {
        const auto& damageData = location.GetDamageData();
        const auto& revetmentData = location.GetRevetmentLocationData();

        auto constructionProperties = make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(
            location.GetX(), ConvertTopLayerType(location.GetTopLayerType()));

        constructionProperties->SetInitialDamage(forward<unique_ptr<double>>(CreatePointerOfValue(location.GetInitialDamage())));
        constructionProperties->SetFailureNumber(forward<unique_ptr<double>>(CreatePointerOfValue(damageData.GetFailureNumber())));

        constructionProperties->SetTimeLineAgwi(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetTimeLineAgwi())));
        constructionProperties->SetTimeLineBgwi(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetTimeLineBgwi())));
        constructionProperties->SetTimeLineCgwi(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetTimeLineCgwi())));

        constructionProperties->SetMinimumWaveHeightTemax(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetMinimumWaveHeightTemax())));
        constructionProperties->SetMaximumWaveHeightTemin(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetMaximumWaveHeightTemin())));

        constructionProperties->SetWaveAngleImpactNwa(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetWaveAngleImpactNwa())));
        constructionProperties->SetWaveAngleImpactQwa(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetWaveAngleImpactQwa())));
        constructionProperties->SetWaveAngleImpactRwa(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetWaveAngleImpactRwa())));

        constructionProperties->SetUpperLimitLoadingAul(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetUpperLimitLoadingAul())));
        constructionProperties->SetLowerLimitLoadingAll(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetLowerLimitLoadingAll())));

        return constructionProperties;
    }

    unique_ptr<GrassRevetmentWaveRunupRayleighLocationConstructionProperties> JsonInputAdapter::CreateGrassWaveRunupRayleighConstructionProperties(
        const JsonInputGrassWaveRunupRayleighLocationData& location)
    {
        const auto& damageData = location.GetDamageData();
        const auto& revetmentData = location.GetRevetmentLocationData();

        auto constructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            location.GetX(), location.GetOuterSlope(), ConvertTopLayerType(location.GetTopLayerType()));

        constructionProperties->SetInitialDamage(forward<unique_ptr<double>>(CreatePointerOfValue(location.GetInitialDamage())));
        constructionProperties->SetFailureNumber(forward<unique_ptr<double>>(CreatePointerOfValue(damageData.GetFailureNumber())));

        constructionProperties->SetCriticalCumulativeOverload(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetCriticalCumulativeOverload())));
        constructionProperties->SetCriticalFrontVelocity(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetCriticalFrontVelocity())));
        constructionProperties->SetIncreasedLoadTransitionAlphaM(
            forward<unique_ptr<double>>(CreatePointerOfValue(location.GetIncreasedLoadTransitionAlphaM())));
        constructionProperties->SetReducedStrengthTransitionAlphaS(
            forward<unique_ptr<double>>(CreatePointerOfValue(location.GetReducedStrengthTransitionAlphaS())));
        constructionProperties->SetAverageNumberOfWavesCtm(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetAverageNumberOfWavesCtm())));

        constructionProperties->SetRepresentativeWaveRunup2PAru(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetRepresentativeWaveRunup2PAru())));
        constructionProperties->SetRepresentativeWaveRunup2PBru(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetRepresentativeWaveRunup2PBru())));
        constructionProperties->SetRepresentativeWaveRunup2PCru(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetRepresentativeWaveRunup2PCru())));
        constructionProperties->SetRepresentativeWaveRunup2PGammab(
            forward<unique_ptr<double>>(CreatePointerOfValue(location.GetRepresentativeWaveRunup2PGammab())));
        constructionProperties->SetRepresentativeWaveRunup2PGammaf(
            forward<unique_ptr<double>>(CreatePointerOfValue(location.GetRepresentativeWaveRunup2PGammaf())));

        constructionProperties->SetWaveAngleImpactAbeta(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetWaveAngleImpactAbeta())));
        constructionProperties->SetWaveAngleImpactBetamax(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetWaveAngleImpactBetamax())));

        constructionProperties->SetFixedNumberOfWaves(
            forward<unique_ptr<int>>(CreatePointerOfValue(revetmentData.GetFixedNumberOfWaves())));
        constructionProperties->SetFrontVelocityCu(
            forward<unique_ptr<double>>(CreatePointerOfValue(revetmentData.GetFrontVelocityCu())));

        return constructionProperties;
    }

    GrassRevetmentTopLayerType JsonInputAdapter::ConvertTopLayerType(
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

        throw JsonInputConversionException("Cannot convert top layer type.");
    }

    unique_ptr<NaturalStoneRevetmentLocationConstructionProperties> JsonInputAdapter::CreateNaturalStoneConstructionProperties(
        const JsonInputNaturalStoneLocationData& location,
        const JsonInputNaturalStoneCalculationDefinitionData* calculationDefinition)
    {
        const auto jsonInputTopLayerType = location.GetTopLayerType();
        auto constructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            location.GetX(), ConvertTopLayerType(jsonInputTopLayerType), location.GetThicknessTopLayer(),
            location.GetRelativeDensity());

        constructionProperties->SetInitialDamage(forward<unique_ptr<double>>(CreatePointerOfValue(location.GetInitialDamage())));

        if (calculationDefinition != nullptr)
        {
            constructionProperties->SetFailureNumber(forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetFailureNumber())));

            const auto& topLayerDefinitions = calculationDefinition->GetTopLayerDefinitions();
            if (const auto& keyExists = topLayerDefinitions.find(jsonInputTopLayerType); keyExists != topLayerDefinitions.end())
            {
                const auto& topLayerDefinition = topLayerDefinitions.at(jsonInputTopLayerType).get();

                constructionProperties->SetHydraulicLoadAp(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetHydraulicLoadAp())));
                constructionProperties->SetHydraulicLoadBp(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetHydraulicLoadBp())));
                constructionProperties->SetHydraulicLoadCp(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetHydraulicLoadCp())));
                constructionProperties->SetHydraulicLoadNp(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetHydraulicLoadNp())));
                constructionProperties->SetHydraulicLoadAs(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetHydraulicLoadAs())));
                constructionProperties->SetHydraulicLoadBs(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetHydraulicLoadBs())));
                constructionProperties->SetHydraulicLoadCs(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetHydraulicLoadCs())));
                constructionProperties->SetHydraulicLoadNs(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetHydraulicLoadNs())));
                constructionProperties->SetHydraulicLoadXib(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetHydraulicLoadXib())));
            }

            constructionProperties->SetSlopeUpperLevelAus(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetSlopeUpperLevelAus())));
            constructionProperties->SetSlopeLowerLevelAls(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetSlopeLowerLevelAls())));

            constructionProperties->SetUpperLimitLoadingAul(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetUpperLimitLoadingAul())));
            constructionProperties->SetUpperLimitLoadingBul(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetUpperLimitLoadingBul())));
            constructionProperties->SetUpperLimitLoadingCul(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetUpperLimitLoadingCul())));

            constructionProperties->SetLowerLimitLoadingAll(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetLowerLimitLoadingAll())));
            constructionProperties->SetLowerLimitLoadingBll(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetLowerLimitLoadingBll())));
            constructionProperties->SetLowerLimitLoadingCll(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetLowerLimitLoadingCll())));

            constructionProperties->SetDistanceMaximumWaveElevationAsmax(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetDistanceMaximumWaveElevationAsmax())));
            constructionProperties->SetDistanceMaximumWaveElevationBsmax(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetDistanceMaximumWaveElevationBsmax())));

            constructionProperties->SetNormativeWidthOfWaveImpactAwi(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetNormativeWidthOfWaveImpactAwi())));
            constructionProperties->SetNormativeWidthOfWaveImpactBwi(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetNormativeWidthOfWaveImpactBwi())));

            constructionProperties->SetWaveAngleImpactBetamax(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetWaveAngleImpactBetamax())));
        }

        return constructionProperties;
    }

    NaturalStoneRevetmentTopLayerType JsonInputAdapter::ConvertTopLayerType(
        const JsonInputNaturalStoneRevetmentTopLayerType topLayerType)
    {
        if (topLayerType == JsonInputNaturalStoneRevetmentTopLayerType::NordicStone)
        {
            return NaturalStoneRevetmentTopLayerType::NordicStone;
        }

        throw JsonInputConversionException("Cannot convert top layer type.");
    }

    template <typename TValue>
    unique_ptr<TValue> JsonInputAdapter::CreatePointerOfValue(
        const TValue* value)
    {
        return value != nullptr
                   ? make_unique<TValue>(*value)
                   : nullptr;
    }
}
