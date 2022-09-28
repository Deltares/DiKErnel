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

    unique_ptr<DataResult<ICalculationInput>> JsonInputAdapter::AdaptJsonInputData(
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
            const auto startPointX = xLocations.at(i);
            const auto startPointZ = zLocations.at(i);
            const auto endPointX = xLocations.at(i + 1);
            const auto endPointZ = zLocations.at(i + 1);

            if(roughnessCoefficients != nullptr)
            {
                builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, roughnessCoefficients->at(i));
            }
            else
            {
                builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ);
            }
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

        constructionProperties->SetInitialDamage(UniquePtrHelper::CreatePtrOfValue(location.GetInitialDamage()));

        constructionProperties->SetThicknessSubLayer(UniquePtrHelper::CreatePtrOfValue(location.GetThicknessSubLayer()));
        constructionProperties->SetElasticModulusSubLayer(UniquePtrHelper::CreatePtrOfValue(location.GetElasticModulusSubLayer()));

        if (calculationDefinition != nullptr)
        {
            constructionProperties->SetFailureNumber(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetFailureNumber()));
            constructionProperties->SetDensityOfWater(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetDensityOfWater()));

            constructionProperties->SetAverageNumberOfWavesCtm(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetFactorCtm()));

            if (const auto& topLayerDefinitionData = calculationDefinition->GetTopLayerDefinitionData();
                topLayerDefinitionData.contains(jsonInputTopLayerType))
            {
                const auto& topLayerDefinition = topLayerDefinitionData.at(jsonInputTopLayerType).get();

                constructionProperties->SetFatigueAlpha(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetFatigueAlpha()));
                constructionProperties->SetFatigueBeta(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetFatigueBeta()));

                constructionProperties->SetStiffnessRelationNu(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetStiffnessRelationNu()));
            }

            constructionProperties->SetImpactNumberC(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetImpactNumberC()));

            constructionProperties->SetWidthFactors(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetWidthFactors()));
            constructionProperties->SetDepthFactors(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetDepthFactors()));
            constructionProperties->SetImpactFactors(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetImpactFactors()));
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

        constructionProperties->SetInitialDamage(UniquePtrHelper::CreatePtrOfValue(location.GetInitialDamage()));
        constructionProperties->SetIncreasedLoadTransitionAlphaM(UniquePtrHelper::CreatePtrOfValue(location.GetIncreasedLoadTransitionAlphaM()));
        constructionProperties->SetReducedStrengthTransitionAlphaS(
            UniquePtrHelper::CreatePtrOfValue(location.GetReducedStrengthTransitionAlphaS()));

        if (calculationDefinition != nullptr)
        {
            constructionProperties->SetFailureNumber(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetFailureNumber()));

            if (const auto& topLayerDefinitionData = calculationDefinition->GetTopLayerDefinitionData();
                topLayerDefinitionData.contains(jsonInputTopLayerType))
            {
                const auto& topLayerDefinition = topLayerDefinitionData.at(jsonInputTopLayerType).get();

                constructionProperties->SetCriticalCumulativeOverload(
                    UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetCriticalCumulativeOverload()));
                constructionProperties->SetCriticalFrontVelocity(
                    UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetCriticalFrontVelocity()));
            }

            constructionProperties->SetDikeHeight(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetDikeHeight()));
            constructionProperties->SetAccelerationAlphaAForCrest(
                UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetAccelerationAlphaAForCrest()));
            constructionProperties->SetAccelerationAlphaAForInnerSlope(
                UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetAccelerationAlphaAForInnerSlope()));
            constructionProperties->SetFixedNumberOfWaves(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetFixedNumberOfWaves()));
            constructionProperties->SetFrontVelocityCwo(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetFrontVelocity()));
            constructionProperties->SetAverageNumberOfWavesCtm(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetFactorCtm()));
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

        constructionProperties->SetInitialDamage(UniquePtrHelper::CreatePtrOfValue(location.GetInitialDamage()));

        if (calculationDefinition != nullptr)
        {
            constructionProperties->SetFailureNumber(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetFailureNumber()));

            if (const auto& topLayerDefinitionData = calculationDefinition->GetTopLayerDefinitionData();
                topLayerDefinitionData.contains(jsonInputTopLayerType))
            {
                const auto& topLayerDefinition = topLayerDefinitionData.at(jsonInputTopLayerType).get();

                constructionProperties->SetTimeLineAgwi(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetTimeLineA()));
                constructionProperties->SetTimeLineBgwi(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetTimeLineB()));
                constructionProperties->SetTimeLineCgwi(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetTimeLineC()));
            }

            constructionProperties->SetMinimumWaveHeightTemax(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetTemax()));
            constructionProperties->SetMaximumWaveHeightTemin(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetTemin()));

            constructionProperties->SetWaveAngleImpactNwa(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetWaveAngleImpactN()));
            constructionProperties->SetWaveAngleImpactQwa(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetWaveAngleImpactQ()));
            constructionProperties->SetWaveAngleImpactRwa(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetWaveAngleImpactR()));

            constructionProperties->SetUpperLimitLoadingAul(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetUpperLimitLoading()));
            constructionProperties->SetLowerLimitLoadingAll(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetLowerLimitLoading()));
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

        constructionProperties->SetInitialDamage(UniquePtrHelper::CreatePtrOfValue(location.GetInitialDamage()));
        constructionProperties->SetFailureNumber(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetFailureNumber()));

        constructionProperties->SetIncreasedLoadTransitionAlphaM(UniquePtrHelper::CreatePtrOfValue(location.GetIncreasedLoadTransitionAlphaM()));
        constructionProperties->SetReducedStrengthTransitionAlphaS(
            UniquePtrHelper::CreatePtrOfValue(location.GetReducedStrengthTransitionAlphaS()));
        constructionProperties->SetRepresentativeWaveRunup2PGammab(
            UniquePtrHelper::CreatePtrOfValue(location.GetRepresentativeWaveRunup2PGammaG()));
        constructionProperties->SetRepresentativeWaveRunup2PGammaf(
            UniquePtrHelper::CreatePtrOfValue(location.GetRepresentativeWaveRunup2PGammaF()));

        constructionProperties->SetAverageNumberOfWavesCtm(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetFactorCtm()));
        constructionProperties->SetRepresentativeWaveRunup2PAru(
            UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetRepresentativeWaveRunup2PA()));
        constructionProperties->SetRepresentativeWaveRunup2PBru(
            UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetRepresentativeWaveRunup2PB()));
        constructionProperties->SetRepresentativeWaveRunup2PCru(
            UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetRepresentativeWaveRunup2PC()));
        constructionProperties->SetWaveAngleImpactAbeta(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetWaveAngleImpactABeta()));
        constructionProperties->SetWaveAngleImpactBetamax(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetWaveAngleImpactBetaMax()));

        const auto jsonInputTopLayerType = location.GetTopLayerType();
        if (const auto& topLayerDefinitionData = calculationDefinition->GetTopLayerDefinitionData();
            topLayerDefinitionData.contains(jsonInputTopLayerType))
        {
            const auto& topLayerDefinition = topLayerDefinitionData.at(jsonInputTopLayerType).get();

            constructionProperties->SetCriticalCumulativeOverload(
                UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetCriticalCumulativeOverload()));
            constructionProperties->SetCriticalFrontVelocity(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetCriticalFrontVelocity()));
        }

        return constructionProperties;
    }

    unique_ptr<GrassRevetmentWaveRunupRayleighLocationConstructionProperties> JsonInputAdapter::CreateGrassWaveRunupRayleighConstructionProperties(
        const JsonInputGrassWaveRunupLocationData& location,
        const JsonInputGrassWaveRunupRayleighCalculationProtocolData& calculationProtocol)
    {
        auto constructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            location.GetX(), location.GetOuterSlope(), ConvertTopLayerType(location.GetTopLayerType()));

        constructionProperties->SetFixedNumberOfWaves(UniquePtrHelper::CreatePtrOfValue(calculationProtocol.GetFixedNumberOfWaves()));
        constructionProperties->SetFrontVelocityCu(UniquePtrHelper::CreatePtrOfValue(calculationProtocol.GetFrontVelocity()));

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

        constructionProperties->SetInitialDamage(UniquePtrHelper::CreatePtrOfValue(location.GetInitialDamage()));

        if (calculationDefinition != nullptr)
        {
            constructionProperties->SetFailureNumber(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetFailureNumber()));

            if (const auto& topLayerDefinitionData = calculationDefinition->GetTopLayerDefinitionData();
                topLayerDefinitionData.contains(jsonInputTopLayerType))
            {
                const auto& topLayerDefinition = topLayerDefinitionData.at(jsonInputTopLayerType).get();

                constructionProperties->SetHydraulicLoadAp(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetStabilityPlungingA()));
                constructionProperties->SetHydraulicLoadBp(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetStabilityPlungingB()));
                constructionProperties->SetHydraulicLoadCp(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetStabilityPlungingC()));
                constructionProperties->SetHydraulicLoadNp(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetStabilityPlungingN()));
                constructionProperties->SetHydraulicLoadAs(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetStabilitySurgingA()));
                constructionProperties->SetHydraulicLoadBs(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetStabilitySurgingB()));
                constructionProperties->SetHydraulicLoadCs(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetStabilitySurgingC()));
                constructionProperties->SetHydraulicLoadNs(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetStabilitySurgingN()));
                constructionProperties->SetHydraulicLoadXib(UniquePtrHelper::CreatePtrOfValue(topLayerDefinition.GetStabilityXib()));
            }

            constructionProperties->SetSlopeUpperLevelAus(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetSlopeUpperLevelA()));
            constructionProperties->SetSlopeLowerLevelAls(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetSlopeLowerLevelA()));

            constructionProperties->SetUpperLimitLoadingAul(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetUpperLimitLoadingA()));
            constructionProperties->SetUpperLimitLoadingBul(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetUpperLimitLoadingB()));
            constructionProperties->SetUpperLimitLoadingCul(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetUpperLimitLoadingC()));

            constructionProperties->SetLowerLimitLoadingAll(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetLowerLimitLoadingA()));
            constructionProperties->SetLowerLimitLoadingBll(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetLowerLimitLoadingB()));
            constructionProperties->SetLowerLimitLoadingCll(UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetLowerLimitLoadingC()));

            constructionProperties->SetDistanceMaximumWaveElevationAsmax(
                UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetDistanceMaximumWaveElevationA()));
            constructionProperties->SetDistanceMaximumWaveElevationBsmax(
                UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetDistanceMaximumWaveElevationB()));

            constructionProperties->SetNormativeWidthOfWaveImpactAwi(
                UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetNormativeWidthOfWaveImpactA()));
            constructionProperties->SetNormativeWidthOfWaveImpactBwi(
                UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetNormativeWidthOfWaveImpactB()));

            constructionProperties->SetWaveAngleImpactBetamax(
                UniquePtrHelper::CreatePtrOfValue(calculationDefinition->GetWaveAngleImpactBetaMax()));
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
}
