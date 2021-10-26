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

#include <gtest/gtest.h>

#include "EventAssertHelper.h"
#include "RevetmentCalculationInputBuilder.h"
#include "Validator.h"

namespace DiKErnel::System::Test
{
    using namespace Core;
    using namespace Integration;
    using namespace std;
    using namespace testing;
    using namespace Util::TestUtil;
    using namespace Util;

    TEST(ValidationSystemTest, GivenCalculationInputWithoutTimeStepsAndLocations_WhenValidating_ThenReturnsValidationResult)
    {
        // Given
        RevetmentCalculationInputBuilder builder;
        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput);

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(2, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "At least 1 time step must be defined.", events[0]);
        EventAssertHelper::AssertEvent(EventType::Error, "At least 1 location must be defined.", events[1]);
    }

    TEST(ValidationSystemTest, GivenCalculationInputWithInvalidTimeStep_WhenValidating_ThenReturnsValidationResult)
    {
        // Given
        RevetmentCalculationInputBuilder builder;
        builder.AddTimeStep(100, 90, 10, -1, 30, 200);

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput);

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(5, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "BeginTime must be smaller than EndTime.", events[1]);
        EventAssertHelper::AssertEvent(EventType::Error, "WaveHeightHm0 must be larger than 0.", events[2]);
        EventAssertHelper::AssertEvent(EventType::Warning, "WavePeriodTm10 should be in range {0.5, 25}.", events[3]);
        EventAssertHelper::AssertEvent(EventType::Error, "WaveAngle must be in range {-180, 180].", events[4]);
    }

    TEST(ValidationSystemTest, GivenCalculationInputWithInvalidAsphaltRevetmentWaveImpactLocation_WhenValidating_ThenReturnsValidationResult)
    {
        // Given
        AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties(10, 2, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 0, 800, 0, -1, -8);
        constructionProperties.SetInitialDamage(make_unique<double>(-0.1));
        constructionProperties.SetFailureNumber(make_unique<double>(-1));
        constructionProperties.SetFatigueAlpha(make_unique<double>(0));
        constructionProperties.SetFatigueBeta(make_unique<double>(0));
        constructionProperties.SetImpactNumberC(make_unique<double>(-0.5));
        constructionProperties.SetStiffnessRelationNu(make_unique<double>(-10));
        constructionProperties.SetThicknessSubLayer(make_unique<double>(0));
        constructionProperties.SetElasticModulusSubLayer(make_unique<double>(0));
        constructionProperties.SetAverageNumberOfWavesCtm(make_unique<double>(0));

        RevetmentCalculationInputBuilder builder;
        constexpr auto outerToe = CharacteristicPointType::OuterToe;
        constexpr auto outerCrest = CharacteristicPointType::OuterCrest;
        builder.AddDikeProfilePoint(10, 5, &outerToe);
        builder.AddDikeProfilePoint(20, 10, &outerCrest);
        builder.AddAsphaltWaveImpactLocation(constructionProperties);

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput);

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(17, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "X must be in range {OuterToeX, OuterCrestX}.", events[1]);
        EventAssertHelper::AssertEvent(EventType::Error, "InitialDamage must be equal to 0 or larger.", events[2]);
        EventAssertHelper::AssertEvent(EventType::Error, "FailureNumber must be larger than InitialDamage.", events[3]);
        EventAssertHelper::AssertEvent(EventType::Error, "FatigueAlpha must be larger than 0.", events[4]);
        EventAssertHelper::AssertEvent(EventType::Error, "FatigueBeta must be larger than 0.", events[5]);
        EventAssertHelper::AssertEvent(EventType::Error, "FailureTension must be larger than 0.", events[6]);
        EventAssertHelper::AssertEvent(EventType::Error, "ImpactNumberC must be larger than 0.", events[7]);
        EventAssertHelper::AssertEvent(EventType::Error, "DensityOfWater must be in range [950, 1050].", events[8]);
        EventAssertHelper::AssertEvent(EventType::Error, "SoilElasticity must be larger than 0.", events[9]);
        EventAssertHelper::AssertEvent(EventType::Error, "StiffnessRelationNu must be larger than 0.", events[10]);
        EventAssertHelper::AssertEvent(EventType::Error, "Thickness must be larger than 0.", events[11]);
        EventAssertHelper::AssertEvent(EventType::Error, "ElasticModulus must be larger than 0.", events[12]);
        EventAssertHelper::AssertEvent(EventType::Error, "Thickness must be larger than 0.", events[13]);
        EventAssertHelper::AssertEvent(EventType::Error, "ElasticModulus must be larger than 0.", events[14]);
        EventAssertHelper::AssertEvent(EventType::Error, "AverageNumberOfWavesCtm must be larger than 0.", events[15]);
        EventAssertHelper::AssertEvent(EventType::Error, "OuterSlope must be in range {0, 1}.", events[16]);
    }

    TEST(ValidationSystemTest, GivenCalculationInputWithInvalidNaturalStoneRevetmentLocation_WhenValidating_ThenReturnsValidationResult)
    {
        // Given
        NaturalStoneRevetmentLocationConstructionProperties constructionProperties(10, NaturalStoneRevetmentTopLayerType::NordicStone, 0, 10);
        constructionProperties.SetInitialDamage(make_unique<double>(-0.1));
        constructionProperties.SetFailureNumber(make_unique<double>(-1));
        constructionProperties.SetSlopeUpperLevelAus(make_unique<double>(0.3));
        constructionProperties.SetSlopeLowerLevelAls(make_unique<double>(0));

        RevetmentCalculationInputBuilder builder;
        constexpr auto outerToe = CharacteristicPointType::OuterToe;
        constexpr auto outerCrest = CharacteristicPointType::OuterCrest;
        builder.AddDikeProfilePoint(10, 5, &outerToe);
        builder.AddDikeProfilePoint(20, 10, &outerCrest);
        builder.AddNaturalStoneLocation(constructionProperties);

        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput);

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(8, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "X must be in range {OuterToeX, OuterCrestX}.", events[1]);
        EventAssertHelper::AssertEvent(EventType::Error, "InitialDamage must be equal to 0 or larger.", events[2]);
        EventAssertHelper::AssertEvent(EventType::Error, "FailureNumber must be larger than InitialDamage.", events[3]);
        EventAssertHelper::AssertEvent(EventType::Error, "RelativeDensity must be in range {0, 10}.", events[4]);
        EventAssertHelper::AssertEvent(EventType::Error, "ThicknessTopLayer must be in range {0, 1}.", events[5]);
        EventAssertHelper::AssertEvent(EventType::Warning, "SlopeUpperLevelAus should be in range [0.01, 0.2].", events[6]);
        EventAssertHelper::AssertEvent(EventType::Error, "SlopeLowerLevelAls must be larger than 0.", events[7]);
    }
}
