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
#include "TimeDependentData.h"

namespace DiKErnel::Core::Test
{
    using namespace std;
    using namespace TestUtil;

    struct TimeDependentDataTest : testing::TestWithParam<int>
    {
        static void DoCall()
        {
            TimeDependentData(50, GetParam(), 0, 0, 0);
        }
    };

    TEST(TimeDependentDataTest, Constructor_WithParameters_ExpectedValues)
    {
        // Setup
        const auto beginTime = rand() % 100;
        const auto endTime = rand() % 100 + 100;
        const auto waveHeightHm0 = 0.1;
        const auto wavePeriodTm10 = 0.2;
        const auto waveAngle = 0.3;

        // Call
        const TimeDependentData timeDependentData(beginTime, endTime, waveHeightHm0, wavePeriodTm10, waveAngle);

        // Assert
        ASSERT_EQ(beginTime, timeDependentData.GetBeginTime());
        ASSERT_EQ(endTime, timeDependentData.GetEndTime());
        ASSERT_DOUBLE_EQ(waveHeightHm0, timeDependentData.GetWaveHeightHm0());
        ASSERT_DOUBLE_EQ(wavePeriodTm10, timeDependentData.GetWavePeriodTm10());
        ASSERT_DOUBLE_EQ(waveAngle, timeDependentData.GetWaveAngle());
    }

    TEST_P(TimeDependentDataTest, Constructor_EndTimeSmallerThanOrEqualToBeginTime_ThrowsInvalidCalculationDataException)
    {
        // Call
        const auto action = &TimeDependentDataTest::DoCall;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidCalculationDataException>(action, "'beginTime' should be smaller than 'endTime'.");
    }

    INSTANTIATE_TEST_SUITE_P(
        Constructor_EndTimeSmallerThanOrEqualToBeginTime_ThrowsInvalidCalculationDataException,
        TimeDependentDataTest,
        ::testing::Values(
            40, 50
        ));
}
