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
#include "RevetmentCalculationInputBuilder.h"
#include "RevetmentCalculationInputBuilderException.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace std;
    using namespace TestUtil;

    struct RevetmentCalculationInputBuilderTest : testing::Test
    {
        static void CreateBuilderAndAddInvalidTimeStep()
        {
            RevetmentCalculationInputBuilder builder(0);
            builder.AddTimeStep(10, 5, 0, 0, 0, 0);
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

    TEST_F(RevetmentCalculationInputBuilderTest, GivenBuilderWithData_WhenBuild_ThenReturnsCalculationInput)
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
        AssertTimeDependentDataItems(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle,
                                     calculationInput->GetTimeDependentDataItems());
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
}
