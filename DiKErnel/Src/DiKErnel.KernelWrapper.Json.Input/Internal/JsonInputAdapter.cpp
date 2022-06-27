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

#include <cmath>

#include "JsonInputConversionException.h"
#include "MapHelper.h"
#include "RevetmentCalculationInputBuilder.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace Core;
    using namespace Integration;
    using namespace std;
    using namespace Util;

    unique_ptr<ICalculationInput> JsonInputAdapter::AdaptJsonInputData(
        const JsonInputData& jsonInputData)
    {
        const auto& hydraulicData = jsonInputData.GetHydraulicData();

        RevetmentCalculationInputBuilder builder;

        const auto& dikeProfileData = jsonInputData.GetDikeProfileData();

        const auto& xLocations = dikeProfileData.GetXLocations();
        const auto& zLocations = dikeProfileData.GetZLocations();
        const auto& characteristicPoints = dikeProfileData.GetCharacteristicPoints();

        for (auto i = 0; i < static_cast<int>(xLocations.size()); ++i)
        {
            const double xLocation = xLocations.at(i);
            unique_ptr<CharacteristicPointType> characteristicPoint = nullptr;

            for (const auto& [characteristicPointType, characteristicPointLocation] : characteristicPoints)
            {
                if (abs(characteristicPointLocation - xLocation) <= numeric_limits<double>::epsilon())
                {
                    characteristicPoint = ConvertCharacteristicPointType(characteristicPointType);
                }
            }

            builder.AddDikeProfilePoint(xLocation, zLocations.at(i), characteristicPoint.get());
        }

        const auto& times = jsonInputData.GetTimes();

        const auto& waterLevels = hydraulicData.GetWaterLevels();
        const auto& waveHeightsHm0 = hydraulicData.GetWaveHeightsHm0();
        const auto& wavePeriodsTm10 = hydraulicData.GetWavePeriodsTm10();
        const auto& waveAngles = hydraulicData.GetWaveAngles();

        for (auto i = 0; i < static_cast<int>(times.size()) - 1; ++i)
        {
            builder.AddTimeStep(times.at(i), times.at(i + 1), waterLevels.at(i), waveHeightsHm0.at(i), wavePeriodsTm10.at(i), waveAngles.at(i));
        }

        const auto& locationReferences = jsonInputData.GetLocationData();
        const auto& calculationDefinitionReferences = jsonInputData.GetCalculationDefinitionData();

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
                const auto& constructionProperties = CreateGrassWaveImpactConstructionProperties(
                    *grassWaveImpactLocationData,
                    GetCalculationDefinition<JsonInputGrassWaveImpactCalculationDefinitionData>(
                        calculationDefinitionReferences, JsonInputCalculationType::GrassWaveImpact));
                builder.AddGrassWaveImpactLocation(*constructionProperties);
            }

            if (const auto* grassWaveRunupLocationData = dynamic_cast<const JsonInputGrassWaveRunupLocationData*>(&location);
                grassWaveRunupLocationData != nullptr)
            {
                const auto& constructionProperties = CreateGrassWaveRunupConstructionProperties(
                    *grassWaveRunupLocationData,
                    GetCalculationDefinition<JsonInputGrassWaveRunupCalculationDefinitionData>(
                        calculationDefinitionReferences, JsonInputCalculationType::GrassWaveRunup));

                if (const auto* grassWaveRunupRayleighConstructionProperties = dynamic_cast<const
                        GrassRevetmentWaveRunupRayleighLocationConstructionProperties*>(constructionProperties.get());
                    grassWaveRunupRayleighConstructionProperties != nullptr)
                {
                    builder.AddGrassWaveRunupRayleighLocation(*grassWaveRunupRayleighConstructionProperties);
                }
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
        if (MapHelper::ContainsKey(calculationDefinitions, calculationType))
        {
            return dynamic_cast<const T*>(&calculationDefinitions.at(calculationType).get());
        }

        return nullptr;
    }

    unique_ptr<CharacteristicPointType> JsonInputAdapter::ConvertCharacteristicPointType(
        const JsonInputCharacteristicPointType jsonCharacteristicPointType)
    {
        unique_ptr<CharacteristicPointType> characteristicPointType;

        switch (jsonCharacteristicPointType)
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

        return characteristicPointType;
    }

    unique_ptr<AsphaltRevetmentWaveImpactLocationConstructionProperties> JsonInputAdapter::CreateAsphaltWaveImpactConstructionProperties(
        const JsonInputAsphaltWaveImpactLocationData& location,
        const JsonInputAsphaltWaveImpactCalculationDefinitionData* calculationDefinition)
    {
        const auto jsonInputTopLayerType = location.GetTopLayerType();
        auto constructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            location.GetX(), location.GetOuterSlope(), ConvertTopLayerType(jsonInputTopLayerType), location.GetFailureTension(),
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
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetFactorCtm())));

            const auto& topLayerDefinitionData = calculationDefinition->GetTopLayerDefinitionData();
            if (const auto& keyExists = topLayerDefinitionData.find(jsonInputTopLayerType); keyExists != topLayerDefinitionData.end())
            {
                const auto& topLayerDefinition = topLayerDefinitionData.at(jsonInputTopLayerType).get();

                constructionProperties->SetFatigueAlpha(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetFatigueAlpha())));
                constructionProperties->SetFatigueBeta(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetFatigueBeta())));

                constructionProperties->SetStiffnessRelationNu(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetStiffnessRelationNu())));
            }

            constructionProperties->SetImpactNumberC(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetImpactNumberC())));

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
        const JsonInputGrassWaveImpactLocationData& location,
        const JsonInputGrassWaveImpactCalculationDefinitionData* calculationDefinition)
    {
        const auto jsonInputTopLayerType = location.GetTopLayerType();
        auto constructionProperties = make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(
            location.GetX(), ConvertTopLayerType(jsonInputTopLayerType));

        constructionProperties->SetInitialDamage(forward<unique_ptr<double>>(CreatePointerOfValue(location.GetInitialDamage())));

        if (calculationDefinition != nullptr)
        {
            constructionProperties->SetFailureNumber(forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetFailureNumber())));

            const auto& topLayerDefinitionData = calculationDefinition->GetTopLayerDefinitionData();
            if (const auto& keyExists = topLayerDefinitionData.find(jsonInputTopLayerType); keyExists != topLayerDefinitionData.end())
            {
                const auto& topLayerDefinition = topLayerDefinitionData.at(jsonInputTopLayerType).get();

                constructionProperties->SetTimeLineAgwi(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetTimeLineA())));
                constructionProperties->SetTimeLineBgwi(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetTimeLineB())));
                constructionProperties->SetTimeLineCgwi(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetTimeLineC())));
            }

            constructionProperties->SetMinimumWaveHeightTemax(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetTemax())));
            constructionProperties->SetMaximumWaveHeightTemin(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetTemin())));

            constructionProperties->SetWaveAngleImpactNwa(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetWaveAngleImpactN())));
            constructionProperties->SetWaveAngleImpactQwa(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetWaveAngleImpactQ())));
            constructionProperties->SetWaveAngleImpactRwa(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetWaveAngleImpactR())));

            constructionProperties->SetUpperLimitLoadingAul(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetUpperLimitLoading())));
            constructionProperties->SetLowerLimitLoadingAll(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetLowerLimitLoading())));
        }

        return constructionProperties;
    }

    unique_ptr<GrassRevetmentWaveRunupLocationConstructionProperties> JsonInputAdapter::CreateGrassWaveRunupConstructionProperties(
        const JsonInputGrassWaveRunupLocationData& location,
        const JsonInputGrassWaveRunupCalculationDefinitionData* calculationDefinition)
    {
        if (calculationDefinition == nullptr)
        {
            throw JsonInputConversionException("Cannot convert calculation protocol type.");
        }

        unique_ptr<GrassRevetmentWaveRunupLocationConstructionProperties> constructionProperties;

        const auto& jsonInputGrassWaveRunupCalculationProtocolData = calculationDefinition->GetCalculationProtocolData();

        if (const auto* grassWaveRunupRayleighCalculationProtocol = dynamic_cast<const JsonInputGrassWaveRunupRayleighCalculationProtocolData*>(
                jsonInputGrassWaveRunupCalculationProtocolData);
            grassWaveRunupRayleighCalculationProtocol != nullptr)
        {
            constructionProperties = CreateGrassWaveRunupRayleighConstructionProperties(location, *grassWaveRunupRayleighCalculationProtocol);
        }
        else
        {
            throw JsonInputConversionException("Cannot convert calculation protocol type.");
        }

        constructionProperties->SetInitialDamage(forward<unique_ptr<double>>(CreatePointerOfValue(location.GetInitialDamage())));
        constructionProperties->SetFailureNumber(forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetFailureNumber())));

        constructionProperties->SetIncreasedLoadTransitionAlphaM(
            forward<unique_ptr<double>>(CreatePointerOfValue(location.GetIncreasedLoadTransitionAlphaM())));
        constructionProperties->SetReducedStrengthTransitionAlphaS(
            forward<unique_ptr<double>>(CreatePointerOfValue(location.GetReducedStrengthTransitionAlphaS())));
        constructionProperties->SetRepresentativeWaveRunup2PGammab(
            forward<unique_ptr<double>>(CreatePointerOfValue(location.GetRepresentativeWaveRunup2PGammaG())));
        constructionProperties->SetRepresentativeWaveRunup2PGammaf(
            forward<unique_ptr<double>>(CreatePointerOfValue(location.GetRepresentativeWaveRunup2PGammaF())));

        constructionProperties->SetAverageNumberOfWavesCtm(
            forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetFactorCtm())));
        constructionProperties->SetRepresentativeWaveRunup2PAru(
            forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetRepresentativeWaveRunup2PA())));
        constructionProperties->SetRepresentativeWaveRunup2PBru(
            forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetRepresentativeWaveRunup2PB())));
        constructionProperties->SetRepresentativeWaveRunup2PCru(
            forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetRepresentativeWaveRunup2PC())));
        constructionProperties->SetWaveAngleImpactAbeta(
            forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetWaveAngleImpactABeta())));
        constructionProperties->SetWaveAngleImpactBetamax(
            forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetWaveAngleImpactBetaMax())));

        const auto jsonInputTopLayerType = location.GetTopLayerType();
        const auto& topLayerDefinitionData = calculationDefinition->GetTopLayerDefinitionData();
        if (const auto& keyExists = topLayerDefinitionData.find(jsonInputTopLayerType); keyExists != topLayerDefinitionData.end())
        {
            const auto& topLayerDefinition = topLayerDefinitionData.at(jsonInputTopLayerType).get();

            constructionProperties->SetCriticalCumulativeOverload(
                forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetCriticalCumulativeOverload())));
            constructionProperties->SetCriticalFrontVelocity(
                forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetCriticalFrontVelocity())));
        }

        return constructionProperties;
    }

    unique_ptr<GrassRevetmentWaveRunupRayleighLocationConstructionProperties> JsonInputAdapter::CreateGrassWaveRunupRayleighConstructionProperties(
        const JsonInputGrassWaveRunupLocationData& location,
        const JsonInputGrassWaveRunupRayleighCalculationProtocolData& calculationProtocol)
    {
        auto constructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            location.GetX(), location.GetOuterSlope(), ConvertTopLayerType(location.GetTopLayerType()));

        constructionProperties->SetFixedNumberOfWaves(
            forward<unique_ptr<int>>(CreatePointerOfValue(calculationProtocol.GetFixedNumberOfWaves())));
        constructionProperties->SetFrontVelocityCu(
            forward<unique_ptr<double>>(CreatePointerOfValue(calculationProtocol.GetFrontVelocity())));

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

            const auto& topLayerDefinitionData = calculationDefinition->GetTopLayerDefinitionData();
            if (const auto& keyExists = topLayerDefinitionData.find(jsonInputTopLayerType); keyExists != topLayerDefinitionData.end())
            {
                const auto& topLayerDefinition = topLayerDefinitionData.at(jsonInputTopLayerType).get();

                constructionProperties->SetHydraulicLoadAp(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetStabilityPlungingA())));
                constructionProperties->SetHydraulicLoadBp(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetStabilityPlungingB())));
                constructionProperties->SetHydraulicLoadCp(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetStabilityPlungingC())));
                constructionProperties->SetHydraulicLoadNp(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetStabilityPlungingN())));
                constructionProperties->SetHydraulicLoadAs(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetStabilitySurgingA())));
                constructionProperties->SetHydraulicLoadBs(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetStabilitySurgingB())));
                constructionProperties->SetHydraulicLoadCs(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetStabilitySurgingC())));
                constructionProperties->SetHydraulicLoadNs(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetStabilitySurgingN())));
                constructionProperties->SetHydraulicLoadXib(
                    forward<unique_ptr<double>>(CreatePointerOfValue(topLayerDefinition.GetStabilityXib())));
            }

            constructionProperties->SetSlopeUpperLevelAus(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetSlopeUpperLevelA())));
            constructionProperties->SetSlopeLowerLevelAls(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetSlopeLowerLevelA())));

            constructionProperties->SetUpperLimitLoadingAul(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetUpperLimitLoadingA())));
            constructionProperties->SetUpperLimitLoadingBul(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetUpperLimitLoadingB())));
            constructionProperties->SetUpperLimitLoadingCul(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetUpperLimitLoadingC())));

            constructionProperties->SetLowerLimitLoadingAll(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetLowerLimitLoadingA())));
            constructionProperties->SetLowerLimitLoadingBll(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetLowerLimitLoadingB())));
            constructionProperties->SetLowerLimitLoadingCll(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetLowerLimitLoadingC())));

            constructionProperties->SetDistanceMaximumWaveElevationAsmax(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetDistanceMaximumWaveElevationA())));
            constructionProperties->SetDistanceMaximumWaveElevationBsmax(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetDistanceMaximumWaveElevationB())));

            constructionProperties->SetNormativeWidthOfWaveImpactAwi(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetNormativeWidthOfWaveImpactA())));
            constructionProperties->SetNormativeWidthOfWaveImpactBwi(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetNormativeWidthOfWaveImpactB())));

            constructionProperties->SetWaveAngleImpactBetamax(
                forward<unique_ptr<double>>(CreatePointerOfValue(calculationDefinition->GetWaveAngleImpactBetaMax())));
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
