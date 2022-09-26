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

#include "CalculationInputBuilder.h"
#include "EventAssertHelper.h"
#include "Validator.h"

namespace DiKErnel::System::Test
{
    using namespace Core;
    using namespace Integration;
    using namespace std;
    using namespace testing;
    using namespace Util::TestUtil;
    using namespace Util;

    TEST(ValidationSystemTest, GivenCalculationInputWithInvalidTimeStep_WhenValidating_ThenReturnsExpectedValidationResult)
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddTimeStep(90, 100, 10, -1, 30, 200);
        builder.AddDikeProfileSegment(10, 5, 20, 10);
        builder.AddDikeProfilePointData(10, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(20, CharacteristicPointType::OuterCrest);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(15, GrassRevetmentTopLayerType::ClosedSod));

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput->GetData());

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(3, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "WaveHeightHm0 must be larger than 0.", events.at(0));
        EventAssertHelper::AssertEvent(EventType::Warning, "WavePeriodTm10 should be in range {0.5, 25}.", events.at(1));
        EventAssertHelper::AssertEvent(EventType::Error, "WaveAngle must be in range {-180, 180].", events.at(2));
    }

    TEST(ValidationSystemTest, GivenCalculationInputWithInvalidProfileData_WhenValidating_ThenReturnsExpectedValidationResult)
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(10, 5, 20, 10, 1.5);
        builder.AddDikeProfilePointData(10, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(20, CharacteristicPointType::OuterCrest);
        builder.AddTimeStep(0, 100, 10, 5, 10, 30);

        auto asphaltRevetmentWaveImpactLocationConstructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            12, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1, 0.5, 3, 2);

        builder.AddAsphaltWaveImpactLocation(move(asphaltRevetmentWaveImpactLocationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput->GetData());

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(1, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "Roughness coefficient should be in range [0.5, 1].", events.at(0));
    }

    TEST(ValidationSystemTest,
         GivenCalculationInputWithInvalidAsphaltRevetmentWaveImpactLocation_WhenValidating_ThenReturnsExpectedValidationResult)
    {
        // Given
        auto constructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            15, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 0, 0, -1, -8);
        constructionProperties->SetInitialDamage(make_unique<double>(-0.1));
        constructionProperties->SetFailureNumber(make_unique<double>(-1));
        constructionProperties->SetDensityOfWater(make_unique<double>(800));
        constructionProperties->SetFatigueAlpha(make_unique<double>(0));
        constructionProperties->SetFatigueBeta(make_unique<double>(0));
        constructionProperties->SetImpactNumberC(make_unique<double>(-0.5));
        constructionProperties->SetStiffnessRelationNu(make_unique<double>(-10));
        constructionProperties->SetThicknessSubLayer(make_unique<double>(0));
        constructionProperties->SetElasticModulusSubLayer(make_unique<double>(0));
        constructionProperties->SetAverageNumberOfWavesCtm(make_unique<double>(0));

        CalculationInputBuilder builder;
        builder.AddTimeStep(0, 100, 10, 5, 10, 30);
        builder.AddDikeProfileSegment(10, 5, 20, 10);
        builder.AddDikeProfilePointData(10, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(20, CharacteristicPointType::OuterCrest);
        builder.AddAsphaltWaveImpactLocation(move(constructionProperties));

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput->GetData());

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(14, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "InitialDamage must be equal to 0 or larger.", events.at(0));
        EventAssertHelper::AssertEvent(EventType::Error, "FailureNumber must be equal to InitialDamage or larger.", events.at(1));
        EventAssertHelper::AssertEvent(EventType::Error, "FatigueAlpha must be larger than 0.", events.at(2));
        EventAssertHelper::AssertEvent(EventType::Error, "FatigueBeta must be larger than 0.", events.at(3));
        EventAssertHelper::AssertEvent(EventType::Error, "FailureTension must be larger than 0.", events.at(4));
        EventAssertHelper::AssertEvent(EventType::Error, "ImpactNumberC must be larger than 0.", events.at(5));
        EventAssertHelper::AssertEvent(EventType::Error, "DensityOfWater must be in range [950, 1050].", events.at(6));
        EventAssertHelper::AssertEvent(EventType::Error, "SoilElasticity must be larger than 0.", events.at(7));
        EventAssertHelper::AssertEvent(EventType::Error, "StiffnessRelationNu must be larger than 0.", events.at(8));
        EventAssertHelper::AssertEvent(EventType::Error, "Thickness must be larger than 0.", events.at(9));
        EventAssertHelper::AssertEvent(EventType::Error, "ElasticModulus must be larger than 0.", events.at(10));
        EventAssertHelper::AssertEvent(EventType::Error, "Thickness must be larger than 0.", events.at(11));
        EventAssertHelper::AssertEvent(EventType::Error, "ElasticModulus must be larger than 0.", events.at(12));
        EventAssertHelper::AssertEvent(EventType::Error, "AverageNumberOfWavesCtm must be larger than 0.", events.at(13));
    }

    TEST(ValidationSystemTest, GivenCalculationInputWithInvalidGrassRevetmentWaveImpactLocation_WhenValidating_ThenReturnsExpectedValidationResult)
    {
        // Given
        auto constructionProperties = make_unique<
            GrassRevetmentWaveImpactLocationConstructionProperties>(15, GrassRevetmentTopLayerType::ClosedSod);
        constructionProperties->SetInitialDamage(make_unique<double>(-0.1));
        constructionProperties->SetFailureNumber(make_unique<double>(-1));
        constructionProperties->SetTimeLineAgwi(make_unique<double>(-2));
        constructionProperties->SetTimeLineBgwi(make_unique<double>(0));
        constructionProperties->SetTimeLineCgwi(make_unique<double>(-0.5));
        constructionProperties->SetMinimumWaveHeightTemax(make_unique<double>(8000));
        constructionProperties->SetMaximumWaveHeightTemin(make_unique<double>(11));
        constructionProperties->SetWaveAngleImpactNwa(make_unique<double>(3));
        constructionProperties->SetWaveAngleImpactQwa(make_unique<double>(6));
        constructionProperties->SetWaveAngleImpactRwa(make_unique<double>(0));
        constructionProperties->SetUpperLimitLoadingAul(make_unique<double>(1));
        constructionProperties->SetLowerLimitLoadingAll(make_unique<double>(1));

        CalculationInputBuilder builder;
        builder.AddTimeStep(0, 100, 10, 5, 10, 30);
        builder.AddDikeProfileSegment(10, 5, 20, 10);
        builder.AddDikeProfilePointData(10, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(20, CharacteristicPointType::OuterCrest);
        builder.AddGrassWaveImpactLocation(move(constructionProperties));

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput->GetData());

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(11, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "InitialDamage must be equal to 0 or larger.", events.at(0));
        EventAssertHelper::AssertEvent(EventType::Error, "FailureNumber must be equal to InitialDamage or larger.", events.at(1));
        EventAssertHelper::AssertEvent(EventType::Error, "TimeLineAgwi must be larger than TimeLineCgwi.", events.at(2));
        EventAssertHelper::AssertEvent(EventType::Error, "TimeLineBgwi must be smaller than 0.", events.at(3));
        EventAssertHelper::AssertEvent(EventType::Error, "TimeLineCgwi must be equal to 0 or larger.", events.at(4));
        EventAssertHelper::AssertEvent(EventType::Warning, "MinimumWaveHeightTemax should be in range {1000000, 3600000].", events.at(5));
        EventAssertHelper::AssertEvent(EventType::Warning, "MaximumWaveHeightTemin should be in range [3.6, 10}.", events.at(6));
        EventAssertHelper::AssertEvent(EventType::Error, "WaveAngleImpactNwa must be equal to 1 or smaller.", events.at(7));
        EventAssertHelper::AssertEvent(EventType::Error, "WaveAngleImpactQwa must be in range [0, 1].", events.at(8));
        EventAssertHelper::AssertEvent(EventType::Error, "WaveAngleImpactRwa must be larger than 0.", events.at(9));
        EventAssertHelper::AssertEvent(EventType::Error, "UpperLimitLoadingAul must be smaller than LowerLimitLoadingAll.", events.at(10));
    }

    TEST(ValidationSystemTest,
         GivenCalculationInputWithInvalidGrassRevetmentWaveRunupRayleighLocation_WhenValidating_ThenReturnsExpectedValidationResult)
    {
        // Given
        auto constructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
            15, 20, GrassRevetmentTopLayerType::ClosedSod);
        constructionProperties->SetInitialDamage(make_unique<double>(-0.1));
        constructionProperties->SetFailureNumber(make_unique<double>(-1));
        constructionProperties->SetCriticalCumulativeOverload(make_unique<double>(-2));
        constructionProperties->SetRepresentativeWaveRunup2PGammab(make_unique<double>(0));
        constructionProperties->SetRepresentativeWaveRunup2PGammaf(make_unique<double>(-0.5));
        constructionProperties->SetCriticalFrontVelocity(make_unique<double>(-1));
        constructionProperties->SetIncreasedLoadTransitionAlphaM(make_unique<double>(-11));
        constructionProperties->SetReducedStrengthTransitionAlphaS(make_unique<double>(-3));
        constructionProperties->SetAverageNumberOfWavesCtm(make_unique<double>(0));
        constructionProperties->SetFixedNumberOfWaves(make_unique<int>(0));
        constructionProperties->SetFrontVelocityCu(make_unique<double>(-1));

        CalculationInputBuilder builder;
        builder.AddTimeStep(0, 100, 10, 5, 10, 30);
        builder.AddDikeProfileSegment(10, 5, 20, 10);
        builder.AddDikeProfilePointData(10, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(20, CharacteristicPointType::OuterCrest);
        builder.AddGrassWaveRunupRayleighLocation(move(constructionProperties));

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput->GetData());

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(12, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "InitialDamage must be equal to 0 or larger.", events.at(0));
        EventAssertHelper::AssertEvent(EventType::Error, "FailureNumber must be equal to InitialDamage or larger.", events.at(1));
        EventAssertHelper::AssertEvent(EventType::Error, "CriticalCumulativeOverload must be larger than 0.", events.at(2));
        EventAssertHelper::AssertEvent(EventType::Error, "RepresentativeWaveRunup2PGammab must be in range [0.6, 1].", events.at(3));
        EventAssertHelper::AssertEvent(EventType::Error, "RepresentativeWaveRunup2PGammaf must be in range [0.5, 1].", events.at(4));
        EventAssertHelper::AssertEvent(EventType::Error, "CriticalFrontVelocity must be equal to 0 or larger.", events.at(5));
        EventAssertHelper::AssertEvent(EventType::Error, "IncreasedLoadTransitionAlphaM must be equal to 0 or larger.", events.at(6));
        EventAssertHelper::AssertEvent(EventType::Error, "ReducedStrengthTransitionAlphaS must be equal to 0 or larger.", events.at(7));
        EventAssertHelper::AssertEvent(EventType::Error, "OuterSlope must be in range {0, 1}.", events.at(8));
        EventAssertHelper::AssertEvent(EventType::Error, "AverageNumberOfWavesCtm must be larger than 0.", events.at(9));
        EventAssertHelper::AssertEvent(EventType::Error, "FixedNumberOfWaves must be larger than 0.", events.at(10));
        EventAssertHelper::AssertEvent(EventType::Error, "FrontVelocityCu must be larger than 0.", events.at(11));
    }

    TEST(ValidationSystemTest,
         GivenCalculationInputWithInvalidGrassRevetmentOvertoppingLocation_WhenValidating_ThenReturnsExpectedValidationResult)
    {
        // Given
        auto constructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
            15, GrassRevetmentTopLayerType::ClosedSod);
        constructionProperties->SetInitialDamage(make_unique<double>(-0.1));
        constructionProperties->SetFailureNumber(make_unique<double>(-1));
        constructionProperties->SetCriticalCumulativeOverload(make_unique<double>(-2));
        constructionProperties->SetCriticalFrontVelocity(make_unique<double>(-1));
        constructionProperties->SetAccelerationAlphaAForCrest(make_unique<double>(-0.1));
        constructionProperties->SetAccelerationAlphaAForInnerSlope(make_unique<double>(-0.1));
        constructionProperties->SetFixedNumberOfWaves(make_unique<int>(0));
        constructionProperties->SetFrontVelocityCwo(make_unique<double>(-0.1));
        constructionProperties->SetAverageNumberOfWavesCtm(make_unique<double>(0));
        constructionProperties->SetIncreasedLoadTransitionAlphaM(make_unique<double>(-11));
        constructionProperties->SetReducedStrengthTransitionAlphaS(make_unique<double>(-3));

        CalculationInputBuilder builder;
        builder.AddTimeStep(0, 100, 10, 5, 10, 30);
        builder.AddDikeProfileSegment(10, 5, 20, 10);
        builder.AddDikeProfileSegment(20, 10, 30, 10);
        builder.AddDikeProfileSegment(30, 10, 40, 5);
        builder.AddDikeProfilePointData(10, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(20, CharacteristicPointType::OuterCrest);
        builder.AddDikeProfilePointData(30, CharacteristicPointType::InnerCrest);
        builder.AddDikeProfilePointData(40, CharacteristicPointType::InnerToe);
        builder.AddGrassOvertoppingLocation(move(constructionProperties));

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput->GetData());

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(11, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "InitialDamage must be equal to 0 or larger.", events.at(0));
        EventAssertHelper::AssertEvent(EventType::Error, "FailureNumber must be equal to InitialDamage or larger.", events.at(1));
        EventAssertHelper::AssertEvent(EventType::Error, "CriticalCumulativeOverload must be larger than 0.", events.at(2));
        EventAssertHelper::AssertEvent(EventType::Error, "CriticalFrontVelocity must be equal to 0 or larger.", events.at(3));
        EventAssertHelper::AssertEvent(EventType::Error, "AccelerationAlphaA must be equal to 0 or larger.", events.at(4));
        EventAssertHelper::AssertEvent(EventType::Error, "AccelerationAlphaA must be equal to 0 or larger.", events.at(5));
        EventAssertHelper::AssertEvent(EventType::Error, "FixedNumberOfWaves must be larger than 0.", events.at(6));
        EventAssertHelper::AssertEvent(EventType::Error, "FrontVelocityCwo must be larger than 0.", events.at(7));
        EventAssertHelper::AssertEvent(EventType::Error, "AverageNumberOfWavesCtm must be larger than 0.", events.at(8));
        EventAssertHelper::AssertEvent(EventType::Error, "IncreasedLoadTransitionAlphaM must be equal to 0 or larger.", events.at(9));
        EventAssertHelper::AssertEvent(EventType::Error, "ReducedStrengthTransitionAlphaS must be equal to 0 or larger.", events.at(10));
    }

    TEST(ValidationSystemTest, GivenCalculationInputWithInvalidNaturalStoneRevetmentLocation_WhenValidating_ThenReturnsExpectedValidationResult)
    {
        // Given
        auto constructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            15, NaturalStoneRevetmentTopLayerType::NordicStone, 0, 10);
        constructionProperties->SetInitialDamage(make_unique<double>(-0.1));
        constructionProperties->SetFailureNumber(make_unique<double>(-1));
        constructionProperties->SetSlopeUpperLevelAus(make_unique<double>(0.3));
        constructionProperties->SetSlopeLowerLevelAls(make_unique<double>(0));

        CalculationInputBuilder builder;
        builder.AddTimeStep(0, 100, 10, 5, 10, 30);
        builder.AddDikeProfileSegment(10, 5, 20, 10);
        builder.AddDikeProfilePointData(10, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(20, CharacteristicPointType::OuterCrest);
        builder.AddNaturalStoneLocation(move(constructionProperties));

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput->GetData());

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(6, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "InitialDamage must be equal to 0 or larger.", events.at(0));
        EventAssertHelper::AssertEvent(EventType::Error, "FailureNumber must be equal to InitialDamage or larger.", events.at(1));
        EventAssertHelper::AssertEvent(EventType::Error, "RelativeDensity must be in range {0, 10}.", events.at(2));
        EventAssertHelper::AssertEvent(EventType::Error, "ThicknessTopLayer must be in range {0, 1}.", events.at(3));
        EventAssertHelper::AssertEvent(EventType::Warning, "SlopeUpperLevelAus should be in range [0.01, 0.2].", events.at(4));
        EventAssertHelper::AssertEvent(EventType::Error, "SlopeLowerLevelAls must be larger than 0.", events.at(5));
    }

    TEST(ValidationSystemTest, GivenValidCalculationInput_WhenValidating_ThenReturnsValidationResult)
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddTimeStep(0, 100, 10, 5, 10, 30);
        builder.AddDikeProfileSegment(10.0, 5.0, 20.0, 10.0);
        builder.AddDikeProfilePointData(10.0, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(20.0, CharacteristicPointType::OuterCrest);

        auto asphaltRevetmentWaveImpactLocationConstructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            12, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1, 0.5, 3, 2);

        auto grassRevetmentWaveImpactLocationConstructionProperties = make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(
            14, GrassRevetmentTopLayerType::ClosedSod);

        auto grassRevetmentWaveRunupRayleighLocationConstructionProperties = make_unique<
                    GrassRevetmentWaveRunupRayleighLocationConstructionProperties>
                (19, 0.71, GrassRevetmentTopLayerType::ClosedSod);

        auto naturalStoneRevetmentLocationConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            15, NaturalStoneRevetmentTopLayerType::NordicStone, 0.5, 4.6);

        builder.AddAsphaltWaveImpactLocation(move(asphaltRevetmentWaveImpactLocationConstructionProperties));
        builder.AddGrassWaveImpactLocation(move(grassRevetmentWaveImpactLocationConstructionProperties));
        builder.AddGrassWaveRunupRayleighLocation(move(grassRevetmentWaveRunupRayleighLocationConstructionProperties));
        builder.AddNaturalStoneLocation(move(naturalStoneRevetmentLocationConstructionProperties));

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput->GetData());

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Successful, *validationResult->GetData());
        ASSERT_EQ(0, validationResult->GetEvents().size());
    }
}
