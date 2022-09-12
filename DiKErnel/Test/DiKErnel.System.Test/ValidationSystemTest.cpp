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

#include <gtest/gtest.h>

#include "EventAssertHelper.h"
#include "CalculationInputBuilder.h"
#include "Validator.h"

namespace DiKErnel::System::Test
{
    using namespace Core;
    using namespace Integration;
    using namespace std;
    using namespace testing;
    using namespace Util::TestUtil;
    using namespace Util;

    TEST(ValidationSystemTest, GivenCalculationInputWithoutTimeStepsAndLocations_WhenValidating_ThenReturnsExpectedValidationResult)
    {
        // Given
        CalculationInputBuilder builder;
        constexpr auto outerToe = CharacteristicPointType::OuterToe;
        constexpr auto outerCrest = CharacteristicPointType::OuterCrest;
        builder.AddDikeProfilePointData(10, 5, &outerToe);
        builder.AddDikeProfilePointData(20, 10, &outerCrest);
        builder.AddDikeProfileSegment(10, 5, 20, 10, nullptr);

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput);

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(2, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "At least 1 time step must be defined.", events.at(0));
        EventAssertHelper::AssertEvent(EventType::Error, "At least 1 location must be defined.", events.at(1));
    }

    TEST(ValidationSystemTest, GivenCalculationInputWithInvalidTimeStep_WhenValidating_ThenReturnsExpectedValidationResult)
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddTimeStep(100, 90, 10, -1, 30, 200);
        constexpr auto outerToe = CharacteristicPointType::OuterToe;
        constexpr auto outerCrest = CharacteristicPointType::OuterCrest;
        builder.AddDikeProfilePointData(10, 5, &outerToe);
        builder.AddDikeProfilePointData(20, 10, &outerCrest);
        builder.AddDikeProfileSegment(10, 5, 20, 10, nullptr);

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput);

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(5, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "BeginTime must be smaller than EndTime.", events.at(1));
        EventAssertHelper::AssertEvent(EventType::Error, "WaveHeightHm0 must be larger than 0.", events.at(2));
        EventAssertHelper::AssertEvent(EventType::Warning, "WavePeriodTm10 should be in range {0.5, 25}.", events.at(3));
        EventAssertHelper::AssertEvent(EventType::Error, "WaveAngle must be in range {-180, 180].", events.at(4));
    }

    TEST(ValidationSystemTest, GivenCalculationInputWithInvalidProfileData_WhenValidating_ThenReturnsExpectedValidationResult)
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddTimeStep(0, 100, 10, 5, 10, 30);

        const AsphaltRevetmentWaveImpactLocationConstructionProperties asphaltRevetmentWaveImpactLocationConstructionProperties(
            12, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1, 0.5, 3, 2);

        builder.AddAsphaltWaveImpactLocation(asphaltRevetmentWaveImpactLocationConstructionProperties);

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput);

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(2, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "The OuterToe must be defined.", events.at(0));
        EventAssertHelper::AssertEvent(EventType::Error, "The OuterCrest must be defined.", events.at(1));
    }

    TEST(ValidationSystemTest,
         GivenCalculationInputWithInvalidAsphaltRevetmentWaveImpactLocation_WhenValidating_ThenReturnsExpectedValidationResult)
    {
        // Given
        AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties(
            10, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 0, 0, -1, -8);
        constructionProperties.SetInitialDamage(make_unique<double>(-0.1));
        constructionProperties.SetFailureNumber(make_unique<double>(-1));
        constructionProperties.SetDensityOfWater(make_unique<double>(800));
        constructionProperties.SetFatigueAlpha(make_unique<double>(0));
        constructionProperties.SetFatigueBeta(make_unique<double>(0));
        constructionProperties.SetImpactNumberC(make_unique<double>(-0.5));
        constructionProperties.SetStiffnessRelationNu(make_unique<double>(-10));
        constructionProperties.SetThicknessSubLayer(make_unique<double>(0));
        constructionProperties.SetElasticModulusSubLayer(make_unique<double>(0));
        constructionProperties.SetAverageNumberOfWavesCtm(make_unique<double>(0));

        CalculationInputBuilder builder;
        builder.AddTimeStep(0, 100, 10, 5, 10, 30);
        constexpr auto outerToe = CharacteristicPointType::OuterToe;
        constexpr auto outerCrest = CharacteristicPointType::OuterCrest;
        builder.AddDikeProfilePointData(10, 5, &outerToe);
        builder.AddDikeProfilePointData(20, 10, &outerCrest);
        builder.AddDikeProfileSegment(10, 5, 20, 10, nullptr);
        builder.AddAsphaltWaveImpactLocation(constructionProperties);

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput);

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(15, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "X must be in range {OuterToeX, OuterCrestX}.", events.at(0));
        EventAssertHelper::AssertEvent(EventType::Error, "InitialDamage must be equal to 0 or larger.", events.at(1));
        EventAssertHelper::AssertEvent(EventType::Error, "FailureNumber must be equal to InitialDamage or larger.", events.at(2));
        EventAssertHelper::AssertEvent(EventType::Error, "FatigueAlpha must be larger than 0.", events.at(3));
        EventAssertHelper::AssertEvent(EventType::Error, "FatigueBeta must be larger than 0.", events.at(4));
        EventAssertHelper::AssertEvent(EventType::Error, "FailureTension must be larger than 0.", events.at(5));
        EventAssertHelper::AssertEvent(EventType::Error, "ImpactNumberC must be larger than 0.", events.at(6));
        EventAssertHelper::AssertEvent(EventType::Error, "DensityOfWater must be in range [950, 1050].", events.at(7));
        EventAssertHelper::AssertEvent(EventType::Error, "SoilElasticity must be larger than 0.", events.at(8));
        EventAssertHelper::AssertEvent(EventType::Error, "StiffnessRelationNu must be larger than 0.", events.at(9));
        EventAssertHelper::AssertEvent(EventType::Error, "Thickness must be larger than 0.", events.at(10));
        EventAssertHelper::AssertEvent(EventType::Error, "ElasticModulus must be larger than 0.", events.at(11));
        EventAssertHelper::AssertEvent(EventType::Error, "Thickness must be larger than 0.", events.at(12));
        EventAssertHelper::AssertEvent(EventType::Error, "ElasticModulus must be larger than 0.", events.at(13));
        EventAssertHelper::AssertEvent(EventType::Error, "AverageNumberOfWavesCtm must be larger than 0.", events.at(14));
    }

    TEST(ValidationSystemTest, GivenCalculationInputWithInvalidGrassRevetmentWaveImpactLocation_WhenValidating_ThenReturnsExpectedValidationResult)
    {
        // Given
        GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties(10, GrassRevetmentTopLayerType::ClosedSod);
        constructionProperties.SetInitialDamage(make_unique<double>(-0.1));
        constructionProperties.SetFailureNumber(make_unique<double>(-1));
        constructionProperties.SetTimeLineAgwi(make_unique<double>(-2));
        constructionProperties.SetTimeLineBgwi(make_unique<double>(0));
        constructionProperties.SetTimeLineCgwi(make_unique<double>(-0.5));
        constructionProperties.SetMinimumWaveHeightTemax(make_unique<double>(8000));
        constructionProperties.SetMaximumWaveHeightTemin(make_unique<double>(11));
        constructionProperties.SetWaveAngleImpactNwa(make_unique<double>(3));
        constructionProperties.SetWaveAngleImpactQwa(make_unique<double>(6));
        constructionProperties.SetWaveAngleImpactRwa(make_unique<double>(0));
        constructionProperties.SetUpperLimitLoadingAul(make_unique<double>(1));
        constructionProperties.SetLowerLimitLoadingAll(make_unique<double>(1));

        CalculationInputBuilder builder;
        builder.AddTimeStep(0, 100, 10, 5, 10, 30);
        constexpr auto outerToe = CharacteristicPointType::OuterToe;
        constexpr auto outerCrest = CharacteristicPointType::OuterCrest;
        builder.AddDikeProfilePointData(10, 5, &outerToe);
        builder.AddDikeProfilePointData(20, 10, &outerCrest);
        builder.AddDikeProfileSegment(10, 5, 20, 10, nullptr);
        builder.AddGrassWaveImpactLocation(constructionProperties);

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput);

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(12, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "X must be in range {OuterToeX, OuterCrestX}.", events.at(0));
        EventAssertHelper::AssertEvent(EventType::Error, "InitialDamage must be equal to 0 or larger.", events.at(1));
        EventAssertHelper::AssertEvent(EventType::Error, "FailureNumber must be equal to InitialDamage or larger.", events.at(2));
        EventAssertHelper::AssertEvent(EventType::Error, "TimeLineAgwi must be larger than TimeLineCgwi.", events.at(3));
        EventAssertHelper::AssertEvent(EventType::Error, "TimeLineBgwi must be smaller than 0.", events.at(4));
        EventAssertHelper::AssertEvent(EventType::Error, "TimeLineCgwi must be equal to 0 or larger.", events.at(5));
        EventAssertHelper::AssertEvent(EventType::Warning, "MinimumWaveHeightTemax should be in range {1000000, 3600000].", events.at(6));
        EventAssertHelper::AssertEvent(EventType::Warning, "MaximumWaveHeightTemin should be in range [3.6, 10}.", events.at(7));
        EventAssertHelper::AssertEvent(EventType::Error, "WaveAngleImpactNwa must be equal to 1 or smaller.", events.at(8));
        EventAssertHelper::AssertEvent(EventType::Error, "WaveAngleImpactQwa must be in range [0, 1].", events.at(9));
        EventAssertHelper::AssertEvent(EventType::Error, "WaveAngleImpactRwa must be larger than 0.", events.at(10));
        EventAssertHelper::AssertEvent(EventType::Error, "UpperLimitLoadingAul must be smaller than LowerLimitLoadingAll.", events.at(11));
    }

    TEST(ValidationSystemTest,
         GivenCalculationInputWithInvalidGrassRevetmentWaveRunupRayleighLocation_WhenValidating_ThenReturnsExpectedValidationResult)
    {
        // Given
        GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties(10, 20, GrassRevetmentTopLayerType::ClosedSod);
        constructionProperties.SetInitialDamage(make_unique<double>(-0.1));
        constructionProperties.SetFailureNumber(make_unique<double>(-1));
        constructionProperties.SetCriticalCumulativeOverload(make_unique<double>(-2));
        constructionProperties.SetRepresentativeWaveRunup2PGammab(make_unique<double>(0));
        constructionProperties.SetRepresentativeWaveRunup2PGammaf(make_unique<double>(-0.5));
        constructionProperties.SetCriticalFrontVelocity(make_unique<double>(-1));
        constructionProperties.SetIncreasedLoadTransitionAlphaM(make_unique<double>(-11));
        constructionProperties.SetReducedStrengthTransitionAlphaS(make_unique<double>(-3));
        constructionProperties.SetAverageNumberOfWavesCtm(make_unique<double>(0));
        constructionProperties.SetFixedNumberOfWaves(make_unique<int>(0));
        constructionProperties.SetFrontVelocityCu(make_unique<double>(-1));

        CalculationInputBuilder builder;
        builder.AddTimeStep(0, 100, 10, 5, 10, 30);
        constexpr auto outerToe = CharacteristicPointType::OuterToe;
        constexpr auto outerCrest = CharacteristicPointType::OuterCrest;
        builder.AddDikeProfilePointData(10, 5, &outerToe);
        builder.AddDikeProfilePointData(20, 10, &outerCrest);
        builder.AddDikeProfileSegment(10, 5, 20, 10, nullptr);
        builder.AddGrassWaveRunupRayleighLocation(constructionProperties);

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput);

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(13, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "X must be in range {OuterToeX, OuterCrestX}.", events.at(0));
        EventAssertHelper::AssertEvent(EventType::Error, "InitialDamage must be equal to 0 or larger.", events.at(1));
        EventAssertHelper::AssertEvent(EventType::Error, "FailureNumber must be equal to InitialDamage or larger.", events.at(2));
        EventAssertHelper::AssertEvent(EventType::Error, "CriticalCumulativeOverload must be larger than 0.", events.at(3));
        EventAssertHelper::AssertEvent(EventType::Error, "RepresentativeWaveRunup2PGammab must be in range [0.6, 1].", events.at(4));
        EventAssertHelper::AssertEvent(EventType::Error, "RepresentativeWaveRunup2PGammaf must be in range [0.5, 1].", events.at(5));
        EventAssertHelper::AssertEvent(EventType::Error, "CriticalFrontVelocity must be equal to 0 or larger.", events.at(6));
        EventAssertHelper::AssertEvent(EventType::Error, "IncreasedLoadTransitionAlphaM must be equal to 0 or larger.", events.at(7));
        EventAssertHelper::AssertEvent(EventType::Error, "ReducedStrengthTransitionAlphaS must be equal to 0 or larger.", events.at(8));
        EventAssertHelper::AssertEvent(EventType::Error, "OuterSlope must be in range {0, 1}.", events.at(9));
        EventAssertHelper::AssertEvent(EventType::Error, "AverageNumberOfWavesCtm must be larger than 0.", events.at(10));
        EventAssertHelper::AssertEvent(EventType::Error, "FixedNumberOfWaves must be larger than 0.", events.at(11));
        EventAssertHelper::AssertEvent(EventType::Error, "FrontVelocityCu must be larger than 0.", events.at(12));
    }

    TEST(ValidationSystemTest, GivenCalculationInputWithInvalidNaturalStoneRevetmentLocation_WhenValidating_ThenReturnsExpectedValidationResult)
    {
        // Given
        NaturalStoneRevetmentLocationConstructionProperties constructionProperties(10, NaturalStoneRevetmentTopLayerType::NordicStone, 0, 10);
        constructionProperties.SetInitialDamage(make_unique<double>(-0.1));
        constructionProperties.SetFailureNumber(make_unique<double>(-1));
        constructionProperties.SetSlopeUpperLevelAus(make_unique<double>(0.3));
        constructionProperties.SetSlopeLowerLevelAls(make_unique<double>(0));

        CalculationInputBuilder builder;
        builder.AddTimeStep(0, 100, 10, 5, 10, 30);
        constexpr auto outerToe = CharacteristicPointType::OuterToe;
        constexpr auto outerCrest = CharacteristicPointType::OuterCrest;
        builder.AddDikeProfilePointData(10, 5, &outerToe);
        builder.AddDikeProfilePointData(20, 10, &outerCrest);
        builder.AddDikeProfileSegment(10, 5, 20, 10, nullptr);
        builder.AddNaturalStoneLocation(constructionProperties);

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput);

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(7, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "X must be in range {OuterToeX, OuterCrestX}.", events.at(0));
        EventAssertHelper::AssertEvent(EventType::Error, "InitialDamage must be equal to 0 or larger.", events.at(1));
        EventAssertHelper::AssertEvent(EventType::Error, "FailureNumber must be equal to InitialDamage or larger.", events.at(2));
        EventAssertHelper::AssertEvent(EventType::Error, "RelativeDensity must be in range {0, 10}.", events.at(3));
        EventAssertHelper::AssertEvent(EventType::Error, "ThicknessTopLayer must be in range {0, 1}.", events.at(4));
        EventAssertHelper::AssertEvent(EventType::Warning, "SlopeUpperLevelAus should be in range [0.01, 0.2].", events.at(5));
        EventAssertHelper::AssertEvent(EventType::Error, "SlopeLowerLevelAls must be larger than 0.", events.at(6));
    }

    TEST(ValidationSystemTest, GivenValidCalculationInput_WhenValidating_ThenReturnsValidationResult)
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddTimeStep(0, 100, 10, 5, 10, 30);
        constexpr auto outerToe = CharacteristicPointType::OuterToe;
        constexpr auto outerCrest = CharacteristicPointType::OuterCrest;
        builder.AddDikeProfilePointData(10.0, 5.0, &outerToe);
        builder.AddDikeProfilePointData(20.0, 10.0, &outerCrest);
        builder.AddDikeProfileSegment(10.0, 5.0, 20.0, 10.0, nullptr);

        const AsphaltRevetmentWaveImpactLocationConstructionProperties asphaltRevetmentWaveImpactLocationConstructionProperties(
            12, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1, 0.5, 3, 2);

        const GrassRevetmentWaveImpactLocationConstructionProperties grassRevetmentWaveImpactLocationConstructionProperties(
            14, GrassRevetmentTopLayerType::ClosedSod);

        const GrassRevetmentWaveRunupRayleighLocationConstructionProperties grassRevetmentWaveRunupRayleighLocationConstructionProperties
                (19, 0.71, GrassRevetmentTopLayerType::ClosedSod);

        const NaturalStoneRevetmentLocationConstructionProperties naturalStoneRevetmentLocationConstructionProperties(
            15, NaturalStoneRevetmentTopLayerType::NordicStone, 0.5, 4.6);

        builder.AddAsphaltWaveImpactLocation(asphaltRevetmentWaveImpactLocationConstructionProperties);
        builder.AddGrassWaveImpactLocation(grassRevetmentWaveImpactLocationConstructionProperties);
        builder.AddGrassWaveRunupRayleighLocation(grassRevetmentWaveRunupRayleighLocationConstructionProperties);
        builder.AddNaturalStoneLocation(naturalStoneRevetmentLocationConstructionProperties);

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput);

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Successful, *validationResult->GetData());
        ASSERT_EQ(0, validationResult->GetEvents().size());
    }
}
