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

#include "AssertHelper.h"
#include "InvalidCalculationDataException.h"
#include "NaturalStoneRevetmentDefaults.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"
#include "NaturalStoneRevetmentLocationDependentData.h"
#include "RevetmentCalculationInputBuilder.h"
#include "RevetmentCalculationInputBuilderException.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;
    using namespace TestUtil;

    struct RevetmentCalculationInputBuilderTest : testing::Test
    {
        static void CreateBuilderAndAddInvalidTimeStep()
        {
            RevetmentCalculationInputBuilder builder(0);
            builder.AddTimeStep(10, 5, 0, 0, 0, 0);
        }

        static void CreateBuilderAndAddNotConnectingTimeStep()
        {
            RevetmentCalculationInputBuilder builder(0);
            builder.AddTimeStep(0, 5, 0, 0, 0, 0);
            builder.AddTimeStep(10, 20, 0, 0, 0, 0);
            builder.Build();
        }

        static void AssertTimeDependentDataItems(
            const int expectedBeginTime,
            const int expectedEndTime,
            const double expectedWaterLevel,
            const double expectedWaveHeightHm0,
            const double expectedWavePeriodTm10,
            const double expectedWaveAngle,
            const vector<reference_wrapper<TimeDependentData>>& actualTimeDependentDataItems)
        {
            ASSERT_EQ(1, actualTimeDependentDataItems.size());
            const auto& timeDependentDataItem = actualTimeDependentDataItems[0].get();
            ASSERT_DOUBLE_EQ(expectedBeginTime, timeDependentDataItem.GetBeginTime());
            ASSERT_DOUBLE_EQ(expectedEndTime, timeDependentDataItem.GetEndTime());
            ASSERT_DOUBLE_EQ(expectedWaterLevel, timeDependentDataItem.GetWaterLevel());
            ASSERT_DOUBLE_EQ(expectedWaveHeightHm0, timeDependentDataItem.GetWaveHeightHm0());
            ASSERT_DOUBLE_EQ(expectedWavePeriodTm10, timeDependentDataItem.GetWavePeriodTm10());
            ASSERT_DOUBLE_EQ(expectedWaveAngle, timeDependentDataItem.GetWaveAngle());
        }
    };

    TEST_F(RevetmentCalculationInputBuilderTest, GiveBuilder_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto maximumWaveAngle = rand() % 100;

        // When
        RevetmentCalculationInputBuilder builder(maximumWaveAngle);
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_DOUBLE_EQ(maximumWaveAngle, calculationInput->GetMaximumWaveAngle());
        ASSERT_EQ(0, calculationInput->GetTimeDependentDataItems().size());
        ASSERT_EQ(0, calculationInput->GetLocationDependentDataItems().size());
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithTimeStepAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto maximumWaveAngle = rand() % 100;
        const auto beginTime = rand() % 100;
        const auto endTime = rand() % 100 + 100;
        const auto waterLevel = 0.1;
        const auto waveHeightHm0 = 0.2;
        const auto wavePeriodTm10 = 0.3;
        const auto waveAngle = 0.4;

        // When
        RevetmentCalculationInputBuilder builder(maximumWaveAngle);
        builder.AddTimeStep(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle);
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_DOUBLE_EQ(maximumWaveAngle, calculationInput->GetMaximumWaveAngle());

        const auto& actualTimeDependentDataItems = calculationInput->GetTimeDependentDataItems();
        ASSERT_EQ(1, actualTimeDependentDataItems.size());
        const auto& timeDependentDataItem = actualTimeDependentDataItems[0].get();
        ASSERT_DOUBLE_EQ(beginTime, timeDependentDataItem.GetBeginTime());
        ASSERT_DOUBLE_EQ(endTime, timeDependentDataItem.GetEndTime());
        ASSERT_DOUBLE_EQ(waterLevel, timeDependentDataItem.GetWaterLevel());
        ASSERT_DOUBLE_EQ(waveHeightHm0, timeDependentDataItem.GetWaveHeightHm0());
        ASSERT_DOUBLE_EQ(wavePeriodTm10, timeDependentDataItem.GetWavePeriodTm10());
        ASSERT_DOUBLE_EQ(waveAngle, timeDependentDataItem.GetWaveAngle());

        ASSERT_EQ(0, calculationInput->GetLocationDependentDataItems().size());
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilder_WhenAddTimeStepWithInvalidEndTime_ThenThrowsRevetmentCalculationInputBuilderException)
    {
        // Call
        const auto action = &RevetmentCalculationInputBuilderTest::CreateBuilderAndAddInvalidTimeStep;

        // Assert
        AssertHelper::AssertThrowsWithMessageAndInnerException<RevetmentCalculationInputBuilderException, InvalidCalculationDataException>(
            action, "Could not create TimeDependentData.", "'beginTime' should be smaller than 'endTime'.");
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithFullyConfiguredNaturalStoneLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto maximumWaveAngle = rand() % 100;
        const auto initialDamage = 0.1;
        const auto slopeAngle = 0.2;
        const auto thicknessTopLayer = 0.3;
        const auto relativeDensity = 0.4;
        const auto similarityParameterThreshold = 0.5;
        const auto plungingCoefficientA = 0.6;
        const auto plungingCoefficientB = 0.7;
        const auto plungingCoefficientC = 0.8;
        const auto plungingCoefficientN = 0.9;
        const auto surgingCoefficientA = 1.0;
        const auto surgingCoefficientB = 1.1;
        const auto surgingCoefficientC = 1.2;
        const auto surgingCoefficientN = 1.3;

        NaturalStoneRevetmentLocationConstructionProperties naturalStoneConstructionProperties(initialDamage, slopeAngle, thicknessTopLayer);
        naturalStoneConstructionProperties._relativeDensityPtr = make_unique<double>(relativeDensity);
        naturalStoneConstructionProperties._similarityParameterThresholdPtr = make_unique<double>(similarityParameterThreshold);
        naturalStoneConstructionProperties._plungingCoefficientAPtr = make_unique<double>(plungingCoefficientA);
        naturalStoneConstructionProperties._plungingCoefficientBPtr = make_unique<double>(plungingCoefficientB);
        naturalStoneConstructionProperties._plungingCoefficientCPtr = make_unique<double>(plungingCoefficientC);
        naturalStoneConstructionProperties._plungingCoefficientNPtr = make_unique<double>(plungingCoefficientN);
        naturalStoneConstructionProperties._surgingCoefficientAPtr = make_unique<double>(surgingCoefficientA);
        naturalStoneConstructionProperties._surgingCoefficientBPtr = make_unique<double>(surgingCoefficientB);
        naturalStoneConstructionProperties._surgingCoefficientCPtr = make_unique<double>(surgingCoefficientC);
        naturalStoneConstructionProperties._surgingCoefficientNPtr = make_unique<double>(surgingCoefficientN);

        // When
        RevetmentCalculationInputBuilder builder(maximumWaveAngle);
        builder.AddNaturalStoneLocation(naturalStoneConstructionProperties);
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_DOUBLE_EQ(maximumWaveAngle, calculationInput->GetMaximumWaveAngle());
        ASSERT_EQ(0, calculationInput->GetTimeDependentDataItems().size());

        const auto& actualLocationDependentDataItems = calculationInput->GetLocationDependentDataItems();
        ASSERT_EQ(1, actualLocationDependentDataItems.size());

        const auto& locationDependentDataItem = static_cast<NaturalStoneRevetmentLocationDependentData&>(actualLocationDependentDataItems[0].get());

        ASSERT_DOUBLE_EQ(initialDamage, locationDependentDataItem.GetInitialDamage());
        ASSERT_DOUBLE_EQ(slopeAngle, locationDependentDataItem.GetSlopeAngle());
        ASSERT_DOUBLE_EQ(relativeDensity, locationDependentDataItem.GetRelativeDensity());
        ASSERT_DOUBLE_EQ(thicknessTopLayer, locationDependentDataItem.GetThicknessTopLayer());
        ASSERT_DOUBLE_EQ(plungingCoefficientA, locationDependentDataItem.GetPlungingCoefficientA());
        ASSERT_DOUBLE_EQ(plungingCoefficientB, locationDependentDataItem.GetPlungingCoefficientB());
        ASSERT_DOUBLE_EQ(plungingCoefficientC, locationDependentDataItem.GetPlungingCoefficientC());
        ASSERT_DOUBLE_EQ(plungingCoefficientN, locationDependentDataItem.GetPlungingCoefficientN());
        ASSERT_DOUBLE_EQ(surgingCoefficientA, locationDependentDataItem.GetSurgingCoefficientA());
        ASSERT_DOUBLE_EQ(surgingCoefficientB, locationDependentDataItem.GetSurgingCoefficientB());
        ASSERT_DOUBLE_EQ(surgingCoefficientC, locationDependentDataItem.GetSurgingCoefficientC());
        ASSERT_DOUBLE_EQ(surgingCoefficientN, locationDependentDataItem.GetSurgingCoefficientN());
        ASSERT_DOUBLE_EQ(similarityParameterThreshold, locationDependentDataItem.GetSimilarityParameterThreshold());
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithNotFullyConfiguredNaturalStoneLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto maximumWaveAngle = rand() % 100;
        const auto initialDamage = 0.1;
        const auto slopeAngle = 0.2;
        const auto thicknessTopLayer = 0.3;

        NaturalStoneRevetmentLocationConstructionProperties naturalStoneConstructionProperties(initialDamage, slopeAngle, thicknessTopLayer);

        // When
        RevetmentCalculationInputBuilder builder(maximumWaveAngle);
        builder.AddNaturalStoneLocation(naturalStoneConstructionProperties);
        const auto calculationInput = builder.Build();

        // Then
        ASSERT_DOUBLE_EQ(maximumWaveAngle, calculationInput->GetMaximumWaveAngle());
        ASSERT_EQ(0, calculationInput->GetTimeDependentDataItems().size());

        const auto& actualLocationDependentDataItems = calculationInput->GetLocationDependentDataItems();
        ASSERT_EQ(1, actualLocationDependentDataItems.size());

        const auto& locationDependentDataItem = static_cast<NaturalStoneRevetmentLocationDependentData&>(actualLocationDependentDataItems[0].get());

        ASSERT_DOUBLE_EQ(initialDamage, locationDependentDataItem.GetInitialDamage());
        ASSERT_DOUBLE_EQ(slopeAngle, locationDependentDataItem.GetSlopeAngle());
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::RELATIVE_DENSITY, locationDependentDataItem.GetRelativeDensity());
        ASSERT_DOUBLE_EQ(thicknessTopLayer, locationDependentDataItem.GetThicknessTopLayer());
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_A, locationDependentDataItem.GetPlungingCoefficientA());
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_B, locationDependentDataItem.GetPlungingCoefficientB());
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_C, locationDependentDataItem.GetPlungingCoefficientC());
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_N, locationDependentDataItem.GetPlungingCoefficientN());
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_A, locationDependentDataItem.GetSurgingCoefficientA());
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_B, locationDependentDataItem.GetSurgingCoefficientB());
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_C, locationDependentDataItem.GetSurgingCoefficientC());
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_N, locationDependentDataItem.GetSurgingCoefficientN());
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::SIMILARITY_PARAMETER_THRESHOLD,
                         locationDependentDataItem.GetSimilarityParameterThreshold());
    }

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithInvalidTimeSteps_WhenBuild_ThenThrowsRevetmentCalculationInputBuilderException)
    {
        // Call
        const auto action = &RevetmentCalculationInputBuilderTest::CreateBuilderAndAddNotConnectingTimeStep;

        // Assert
        AssertHelper::AssertThrowsWithMessageAndInnerException<RevetmentCalculationInputBuilderException, InvalidCalculationDataException>(
            action, "Could not create TimeDependentData.", "The begin time of an element must connect to the end time of the previous element.");
    }
}
