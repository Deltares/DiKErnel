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
#include "JsonInputGrassOvertoppingCalculationDefinitionData.h"
#include "JsonInputGrassOvertoppingLocationData.h"
#include "UniquePtrHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace Core;
    using namespace Integration;
    using namespace std;
    using namespace Util;

    unique_ptr<ICalculationInput> JsonInputAdapter::AdaptJsonInputData(
        const JsonInputData& jsonInputData)
    {
        CalculationInputBuilder builder;

        AdaptDikeProfile(jsonInputData, builder);
        AdaptHydraulicData(jsonInputData, builder);
        AdaptLocations(jsonInputData, builder);

        return builder.Build();
    }

    void JsonInputAdapter::AdaptDikeProfile(
        const JsonInputData& jsonInputData,
        CalculationInputBuilder& builder)
    {
        const auto& dikeProfileData = jsonInputData.GetDikeProfileData();

        const auto& xLocations = dikeProfileData.GetXLocations();
        const auto& zLocations = dikeProfileData.GetZLocations();
        const auto* roughnessCoefficients = dikeProfileData.GetRoughnessCoefficients();

        for (auto i = 0; i < static_cast<int>(xLocations.size()) - 1; ++i)
        {
            const double startPointX = xLocations.at(i);
            const double startPointZ = zLocations.at(i);
            const double endPointX = xLocations.at(i + 1);
            const double endPointZ = zLocations.at(i + 1);

            const double* roughnessCoefficient = roughnessCoefficients != nullptr
                                                     ? &roughnessCoefficients->at(i)
                                                     : nullptr;

            builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, roughnessCoefficient);
        }

        for (const auto& characteristicPoints = dikeProfileData.GetCharacteristicPoints();
             const auto& [characteristicPointType, characteristicPointLocation] : characteristicPoints)
        {
            builder.AddDikeProfilePointData(characteristicPointLocation, ConvertCharacteristicPointType(characteristicPointType));
        }
    }

    CharacteristicPointType JsonInputAdapter::ConvertCharacteristicPointType(
        const JsonInputCharacteristicPointType jsonCharacteristicPointType)
    {
        switch (jsonCharacteristicPointType)
        {
            case JsonInputCharacteristicPointType::OuterToe:
                return CharacteristicPointType::OuterToe;
            case JsonInputCharacteristicPointType::OuterCrest:
                return CharacteristicPointType::OuterCrest;
            case JsonInputCharacteristicPointType::CrestOuterBerm:
                return CharacteristicPointType::CrestOuterBerm;
            case JsonInputCharacteristicPointType::NotchOuterBerm:
                return CharacteristicPointType::NotchOuterBerm;
            case JsonInputCharacteristicPointType::InnerCrest:
                return CharacteristicPointType::InnerCrest;
            case JsonInputCharacteristicPointType::InnerToe:
                return CharacteristicPointType::InnerToe;
            default:
                throw JsonInputConversionException("Cannot convert characteristic point type.");
        }
    }

    void JsonInputAdapter::AdaptHydraulicData(
        const JsonInputData& jsonInputData,
        CalculationInputBuilder& builder)
    {
        const auto& hydraulicData = jsonInputData.GetHydraulicData();

        const auto& waterLevels = hydraulicData.GetWaterLevels();
        const auto& waveHeightsHm0 = hydraulicData.GetWaveHeightsHm0();
        const auto& wavePeriodsTm10 = hydraulicData.GetWavePeriodsTm10();
        const auto& waveAngles = hydraulicData.GetWaveAngles();

        const auto& times = jsonInputData.GetTimes();
        for (auto i = 0; i < static_cast<int>(times.size()) - 1; ++i)
        {
            builder.AddTimeStep(times.at(i), times.at(i + 1), waterLevels.at(i), waveHeightsHm0.at(i), wavePeriodsTm10.at(i), waveAngles.at(i));
        }
    }

    void JsonInputAdapter::AdaptLocations(
        const JsonInputData& jsonInputData,
        CalculationInputBuilder& builder)
    {
        const auto& locationReferences = jsonInputData.GetLocationData();
        const auto& calculationDefinitionReferences = jsonInputData.GetCalculationDefinitionData();

        for (const auto& locationReference : locationReferences)
        {
            const auto& location = locationReference.get();

            if (const auto* asphaltWaveImpactLocationData = dynamic_cast<const JsonInputAsphaltWaveImpactLocationData*>(&location);
                asphaltWaveImpactLocationData != nullptr)
            {
                auto constructionProperties = CreateAsphaltWaveImpactConstructionProperties(
                    *asphaltWaveImpactLocationData,
                    GetCalculationDefinition<JsonInputAsphaltWaveImpactCalculationDefinitionData>(
                        calculationDefinitionReferences, JsonInputCalculationType::AsphaltWaveImpact));
                builder.AddAsphaltWaveImpactLocation(move(constructionProperties));
            }

            if (const auto* grassOvertoppingLocationData = dynamic_cast<const JsonInputGrassOvertoppingLocationData*>(&location);
                grassOvertoppingLocationData != nullptr)
            {
                auto constructionProperties = CreateGrassOvertoppingConstructionProperties(
                    *grassOvertoppingLocationData,
                    GetCalculationDefinition<JsonInputGrassOvertoppingCalculationDefinitionData>(
                        calculationDefinitionReferences, JsonInputCalculationType::GrassOvertopping));
                builder.AddGrassOvertoppingLocation(move(constructionProperties));
            }

            if (const auto* grassWaveImpactLocationData = dynamic_cast<const JsonInputGrassWaveImpactLocationData*>(&location);
                grassWaveImpactLocationData != nullptr)
            {
                auto constructionProperties = CreateGrassWaveImpactConstructionProperties(
                    *grassWaveImpactLocationData,
                    GetCalculationDefinition<JsonInputGrassWaveImpactCalculationDefinitionData>(
                        calculationDefinitionReferences, JsonInputCalculationType::GrassWaveImpact));
                builder.AddGrassWaveImpactLocation(move(constructionProperties));
            }

            if (const auto* grassWaveRunupLocationData = dynamic_cast<const JsonInputGrassWaveRunupLocationData*>(&location);
                grassWaveRunupLocationData != nullptr)
            {
                auto constructionProperties = CreateGrassWaveRunupConstructionProperties(
                    *grassWaveRunupLocationData,
                    GetCalculationDefinition<JsonInputGrassWaveRunupCalculationDefinitionData>(
                        calculationDefinitionReferences, JsonInputCalculationType::GrassWaveRunup));

                if (auto rayleighConstructionProperties = UniquePtrHelper::DynamicCast<
                        GrassRevetmentWaveRunupRayleighLocationConstructionProperties, GrassRevetmentWaveRunupLocationConstructionProperties>(
                        constructionProperties);
                    rayleighConstructionProperties != nullptr)
                {
                    builder.AddGrassWaveRunupRayleighLocation(move(rayleighConstructionProperties));
                }
            }

            if (const auto* naturalStoneLocationData = dynamic_cast<const JsonInputNaturalStoneLocationData*>(&location);
                naturalStoneLocationData != nullptr)
            {
                auto constructionProperties = CreateNaturalStoneConstructionProperties(
                    *naturalStoneLocationData,
                    GetCalculationDefinition<JsonInputNaturalStoneCalculationDefinitionData>(
                        calculationDefinitionReferences, JsonInputCalculationType::NaturalStone));
                builder.AddNaturalStoneLocation(move(constructionProperties));
            }
        }
    }

    template <typename T>
    const T* JsonInputAdapter::GetCalculationDefinition(
        const map<JsonInputCalculationType, reference_wrapper<JsonInputCalculationDefinitionData>>& calculationDefinitions,
        const JsonInputCalculationType calculationType)
    {
        if (calculationDefinitions.contains(calculationType))
        {
            return dynamic_cast<const T*>(&calculationDefinitions.at(calculationType).get());
        }

        return nullptr;
    }

    unique_ptr<AsphaltRevetmentWaveImpactLocationConstructionProperties> JsonInputAdapter::CreateAsphaltWaveImpactConstructionProperties(
        const JsonInputAsphaltWaveImpactLocationData& location,
        const JsonInputAsphaltWaveImpactCalculationDefinitionData* calculationDefinition)
    {
        const auto jsonInputTopLayerType = location.GetTopLayerType();
        auto constructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            location.GetX(), ConvertTopLayerType(jsonInputTopLayerType), location.GetFailureTension(), location.GetSoilElasticity(),
            location.GetThicknessUpperLayer(), location.GetElasticModulusUpperLayer());

        constructionProperties->SetInitialDamage(CreatePointerOfValue(location.GetInitialDamage()));

        constructionProperties->SetThicknessSubLayer(CreatePointerOfValue(location.GetThicknessSubLayer()));
        constructionProperties->SetElasticModulusSubLayer(CreatePointerOfValue(location.GetElasticModulusSubLayer()));

        if (calculationDefinition != nullptr)
        {
            constructionProperties->SetFailureNumber(CreatePointerOfValue(calculationDefinition->GetFailureNumber()));
            constructionProperties->SetDensityOfWater(CreatePointerOfValue(calculationDefinition->GetDensityOfWater()));

            constructionProperties->SetAverageNumberOfWavesCtm(CreatePointerOfValue(calculationDefinition->GetFactorCtm()));

            if (const auto& topLayerDefinitionData = calculationDefinition->GetTopLayerDefinitionData();
                topLayerDefinitionData.contains(jsonInputTopLayerType))
            {
                const auto& topLayerDefinition = topLayerDefinitionData.at(jsonInputTopLayerType).get();

                constructionProperties->SetFatigueAlpha(CreatePointerOfValue(topLayerDefinition.GetFatigueAlpha()));
                constructionProperties->SetFatigueBeta(CreatePointerOfValue(topLayerDefinition.GetFatigueBeta()));

                constructionProperties->SetStiffnessRelationNu(CreatePointerOfValue(topLayerDefinition.GetStiffnessRelationNu()));
            }

            constructionProperties->SetImpactNumberC(CreatePointerOfValue(calculationDefinition->GetImpactNumberC()));

            constructionProperties->SetWidthFactors(CreatePointerOfValue(calculationDefinition->GetWidthFactors()));
            constructionProperties->SetDepthFactors(CreatePointerOfValue(calculationDefinition->GetDepthFactors()));
            constructionProperties->SetImpactFactors(CreatePointerOfValue(calculationDefinition->GetImpactFactors()));
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

    unique_ptr<GrassRevetmentOvertoppingLocationConstructionProperties> JsonInputAdapter::CreateGrassOvertoppingConstructionProperties(
        const JsonInputGrassOvertoppingLocationData& location,
        const JsonInputGrassOvertoppingCalculationDefinitionData* calculationDefinition)
    {
        const auto jsonInputTopLayerType = location.GetTopLayerType();
        auto constructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
            location.GetX(), ConvertTopLayerType(jsonInputTopLayerType));

        constructionProperties->SetInitialDamage(CreatePointerOfValue(location.GetInitialDamage()));
        constructionProperties->SetIncreasedLoadTransitionAlphaM(CreatePointerOfValue(location.GetIncreasedLoadTransitionAlphaM()));
        constructionProperties->SetReducedStrengthTransitionAlphaS(CreatePointerOfValue(location.GetReducedStrengthTransitionAlphaS()));

        if (calculationDefinition != nullptr)
        {
            constructionProperties->SetFailureNumber(CreatePointerOfValue(calculationDefinition->GetFailureNumber()));

            if (const auto& topLayerDefinitionData = calculationDefinition->GetTopLayerDefinitionData();
                topLayerDefinitionData.contains(jsonInputTopLayerType))
            {
                const auto& topLayerDefinition = topLayerDefinitionData.at(jsonInputTopLayerType).get();

                constructionProperties->SetCriticalCumulativeOverload(CreatePointerOfValue(topLayerDefinition.GetCriticalCumulativeOverload()));
                constructionProperties->SetCriticalFrontVelocity(CreatePointerOfValue(topLayerDefinition.GetCriticalFrontVelocity()));
            }

            constructionProperties->SetDikeHeight(CreatePointerOfValue(calculationDefinition->GetDikeHeight()));
            constructionProperties->SetAccelerationAlphaAForCrest(CreatePointerOfValue(calculationDefinition->GetAccelerationAlphaAForCrest()));
            constructionProperties->SetAccelerationAlphaAForInnerSlope(
                CreatePointerOfValue(calculationDefinition->GetAccelerationAlphaAForInnerSlope()));
            constructionProperties->SetFixedNumberOfWaves(CreatePointerOfValue(calculationDefinition->GetFixedNumberOfWaves()));
            constructionProperties->SetFrontVelocityCwo(CreatePointerOfValue(calculationDefinition->GetFrontVelocity()));
            constructionProperties->SetAverageNumberOfWavesCtm(CreatePointerOfValue(calculationDefinition->GetFactorCtm()));
        }

        return constructionProperties;
    }

    unique_ptr<GrassRevetmentWaveImpactLocationConstructionProperties> JsonInputAdapter::CreateGrassWaveImpactConstructionProperties(
        const JsonInputGrassWaveImpactLocationData& location,
        const JsonInputGrassWaveImpactCalculationDefinitionData* calculationDefinition)
    {
        const auto jsonInputTopLayerType = location.GetTopLayerType();
        auto constructionProperties = make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(
            location.GetX(), ConvertTopLayerType(jsonInputTopLayerType));

        constructionProperties->SetInitialDamage(CreatePointerOfValue(location.GetInitialDamage()));

        if (calculationDefinition != nullptr)
        {
            constructionProperties->SetFailureNumber(CreatePointerOfValue(calculationDefinition->GetFailureNumber()));

            if (const auto& topLayerDefinitionData = calculationDefinition->GetTopLayerDefinitionData();
                topLayerDefinitionData.contains(jsonInputTopLayerType))
            {
                const auto& topLayerDefinition = topLayerDefinitionData.at(jsonInputTopLayerType).get();

                constructionProperties->SetTimeLineAgwi(CreatePointerOfValue(topLayerDefinition.GetTimeLineA()));
                constructionProperties->SetTimeLineBgwi(CreatePointerOfValue(topLayerDefinition.GetTimeLineB()));
                constructionProperties->SetTimeLineCgwi(CreatePointerOfValue(topLayerDefinition.GetTimeLineC()));
            }

            constructionProperties->SetMinimumWaveHeightTemax(CreatePointerOfValue(calculationDefinition->GetTemax()));
            constructionProperties->SetMaximumWaveHeightTemin(CreatePointerOfValue(calculationDefinition->GetTemin()));

            constructionProperties->SetWaveAngleImpactNwa(CreatePointerOfValue(calculationDefinition->GetWaveAngleImpactN()));
            constructionProperties->SetWaveAngleImpactQwa(CreatePointerOfValue(calculationDefinition->GetWaveAngleImpactQ()));
            constructionProperties->SetWaveAngleImpactRwa(CreatePointerOfValue(calculationDefinition->GetWaveAngleImpactR()));

            constructionProperties->SetUpperLimitLoadingAul(CreatePointerOfValue(calculationDefinition->GetUpperLimitLoading()));
            constructionProperties->SetLowerLimitLoadingAll(CreatePointerOfValue(calculationDefinition->GetLowerLimitLoading()));
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
            jsonInputGrassWaveRunupCalculationProtocolData); grassWaveRunupRayleighCalculationProtocol != nullptr)
        {
            constructionProperties = CreateGrassWaveRunupRayleighConstructionProperties(location, *grassWaveRunupRayleighCalculationProtocol);
        }
        else
        {
            throw JsonInputConversionException("Cannot convert calculation protocol type.");
        }

        constructionProperties->SetInitialDamage(CreatePointerOfValue(location.GetInitialDamage()));
        constructionProperties->SetFailureNumber(CreatePointerOfValue(calculationDefinition->GetFailureNumber()));

        constructionProperties->SetIncreasedLoadTransitionAlphaM(CreatePointerOfValue(location.GetIncreasedLoadTransitionAlphaM()));
        constructionProperties->SetReducedStrengthTransitionAlphaS(CreatePointerOfValue(location.GetReducedStrengthTransitionAlphaS()));
        constructionProperties->SetRepresentativeWaveRunup2PGammab(CreatePointerOfValue(location.GetRepresentativeWaveRunup2PGammaG()));
        constructionProperties->SetRepresentativeWaveRunup2PGammaf(CreatePointerOfValue(location.GetRepresentativeWaveRunup2PGammaF()));

        constructionProperties->SetAverageNumberOfWavesCtm(CreatePointerOfValue(calculationDefinition->GetFactorCtm()));
        constructionProperties->SetRepresentativeWaveRunup2PAru(CreatePointerOfValue(calculationDefinition->GetRepresentativeWaveRunup2PA()));
        constructionProperties->SetRepresentativeWaveRunup2PBru(CreatePointerOfValue(calculationDefinition->GetRepresentativeWaveRunup2PB()));
        constructionProperties->SetRepresentativeWaveRunup2PCru(CreatePointerOfValue(calculationDefinition->GetRepresentativeWaveRunup2PC()));
        constructionProperties->SetWaveAngleImpactAbeta(CreatePointerOfValue(calculationDefinition->GetWaveAngleImpactABeta()));
        constructionProperties->SetWaveAngleImpactBetamax(CreatePointerOfValue(calculationDefinition->GetWaveAngleImpactBetaMax()));

        const auto jsonInputTopLayerType = location.GetTopLayerType();
        if (const auto& topLayerDefinitionData = calculationDefinition->GetTopLayerDefinitionData();
            topLayerDefinitionData.contains(jsonInputTopLayerType))
        {
            const auto& topLayerDefinition = topLayerDefinitionData.at(jsonInputTopLayerType).get();

            constructionProperties->SetCriticalCumulativeOverload(CreatePointerOfValue(topLayerDefinition.GetCriticalCumulativeOverload()));
            constructionProperties->SetCriticalFrontVelocity(CreatePointerOfValue(topLayerDefinition.GetCriticalFrontVelocity()));
        }

        return constructionProperties;
    }

    unique_ptr<GrassRevetmentWaveRunupRayleighLocationConstructionProperties> JsonInputAdapter::CreateGrassWaveRunupRayleighConstructionProperties(
        const JsonInputGrassWaveRunupLocationData& location,
        const JsonInputGrassWaveRunupRayleighCalculationProtocolData& calculationProtocol)
    {
        auto constructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            location.GetX(), location.GetOuterSlope(), ConvertTopLayerType(location.GetTopLayerType()));

        constructionProperties->SetFixedNumberOfWaves(CreatePointerOfValue(calculationProtocol.GetFixedNumberOfWaves()));
        constructionProperties->SetFrontVelocityCu(CreatePointerOfValue(calculationProtocol.GetFrontVelocity()));

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

        constructionProperties->SetInitialDamage(CreatePointerOfValue(location.GetInitialDamage()));

        if (calculationDefinition != nullptr)
        {
            constructionProperties->SetFailureNumber(CreatePointerOfValue(calculationDefinition->GetFailureNumber()));

            if (const auto& topLayerDefinitionData = calculationDefinition->GetTopLayerDefinitionData();
                topLayerDefinitionData.contains(jsonInputTopLayerType))
            {
                const auto& topLayerDefinition = topLayerDefinitionData.at(jsonInputTopLayerType).get();

                constructionProperties->SetHydraulicLoadAp(CreatePointerOfValue(topLayerDefinition.GetStabilityPlungingA()));
                constructionProperties->SetHydraulicLoadBp(CreatePointerOfValue(topLayerDefinition.GetStabilityPlungingB()));
                constructionProperties->SetHydraulicLoadCp(CreatePointerOfValue(topLayerDefinition.GetStabilityPlungingC()));
                constructionProperties->SetHydraulicLoadNp(CreatePointerOfValue(topLayerDefinition.GetStabilityPlungingN()));
                constructionProperties->SetHydraulicLoadAs(CreatePointerOfValue(topLayerDefinition.GetStabilitySurgingA()));
                constructionProperties->SetHydraulicLoadBs(CreatePointerOfValue(topLayerDefinition.GetStabilitySurgingB()));
                constructionProperties->SetHydraulicLoadCs(CreatePointerOfValue(topLayerDefinition.GetStabilitySurgingC()));
                constructionProperties->SetHydraulicLoadNs(CreatePointerOfValue(topLayerDefinition.GetStabilitySurgingN()));
                constructionProperties->SetHydraulicLoadXib(CreatePointerOfValue(topLayerDefinition.GetStabilityXib()));
            }

            constructionProperties->SetSlopeUpperLevelAus(CreatePointerOfValue(calculationDefinition->GetSlopeUpperLevelA()));
            constructionProperties->SetSlopeLowerLevelAls(CreatePointerOfValue(calculationDefinition->GetSlopeLowerLevelA()));

            constructionProperties->SetUpperLimitLoadingAul(CreatePointerOfValue(calculationDefinition->GetUpperLimitLoadingA()));
            constructionProperties->SetUpperLimitLoadingBul(CreatePointerOfValue(calculationDefinition->GetUpperLimitLoadingB()));
            constructionProperties->SetUpperLimitLoadingCul(CreatePointerOfValue(calculationDefinition->GetUpperLimitLoadingC()));

            constructionProperties->SetLowerLimitLoadingAll(CreatePointerOfValue(calculationDefinition->GetLowerLimitLoadingA()));
            constructionProperties->SetLowerLimitLoadingBll(CreatePointerOfValue(calculationDefinition->GetLowerLimitLoadingB()));
            constructionProperties->SetLowerLimitLoadingCll(CreatePointerOfValue(calculationDefinition->GetLowerLimitLoadingC()));

            constructionProperties->SetDistanceMaximumWaveElevationAsmax(
                CreatePointerOfValue(calculationDefinition->GetDistanceMaximumWaveElevationA()));
            constructionProperties->SetDistanceMaximumWaveElevationBsmax(
                CreatePointerOfValue(calculationDefinition->GetDistanceMaximumWaveElevationB()));

            constructionProperties->SetNormativeWidthOfWaveImpactAwi(CreatePointerOfValue(calculationDefinition->GetNormativeWidthOfWaveImpactA()));
            constructionProperties->SetNormativeWidthOfWaveImpactBwi(CreatePointerOfValue(calculationDefinition->GetNormativeWidthOfWaveImpactB()));

            constructionProperties->SetWaveAngleImpactBetamax(CreatePointerOfValue(calculationDefinition->GetWaveAngleImpactBetaMax()));
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
        if (value != nullptr)
        {
            return make_unique<TValue>(*value);
        }

        return nullptr;
    }
}
