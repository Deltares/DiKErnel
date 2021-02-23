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
#include "CalculationInput.h"
#include "InvalidCalculationDataException.h"

namespace DiKErnel::Core::Test
{
    using namespace std;
    using namespace TestUtil;

    struct CalculationInputTest : testing::Test
    {
        static void TimeDependentDataNotSubsequently()
        {
            vector<unique_ptr<TimeDependentData>> timeDependentDataItems;
            timeDependentDataItems.push_back(make_unique<TimeDependentData>(0, 10, 0, 0, 0));
            timeDependentDataItems.push_back(make_unique<TimeDependentData>(15, 20, 0, 0, 0));

            CalculationInput(vector<unique_ptr<ILocationDependentData>>(), move(timeDependentDataItems), 0);
        }

        static void TimeDependentDataUnordered()
        {
            vector<unique_ptr<TimeDependentData>> timeDependentDataItems;
            timeDependentDataItems.push_back(make_unique<TimeDependentData>(10, 20, 0, 0, 0));
            timeDependentDataItems.push_back(make_unique<TimeDependentData>(0, 10, 0, 0, 0));

            CalculationInput(vector<unique_ptr<ILocationDependentData>>(), move(timeDependentDataItems), 0);
        }
    };

    TEST_F(CalculationInputTest, Constructor_WithParameters_ExpectedValues)
    {
        // Setup
        vector<unique_ptr<ILocationDependentData>> locationDependentDataItems;
        locationDependentDataItems.push_back(make_unique<ILocationDependentData>());

        const auto beginTime = rand() % 100;
        const auto endTime = rand() % 100 + 100;
        const auto waveHeightHm0 = 0.1;
        const auto wavePeriodTm10 = 0.2;
        const auto waveAngle = 0.3;

        vector<unique_ptr<TimeDependentData>> timeDependentDataItems;
        timeDependentDataItems.push_back(make_unique<TimeDependentData>(beginTime, endTime, waveHeightHm0, wavePeriodTm10, waveAngle));

        const auto maximumWaveAngle = rand() % 100;

        // Call
        const CalculationInput calculationInput(move(locationDependentDataItems), move(timeDependentDataItems), maximumWaveAngle);

        // Assert
        ASSERT_EQ(1, calculationInput.GetLocationDependentDataItems().size());

        const auto& actualTimeSteps = calculationInput.GetTimeDependentDataItems();
        ASSERT_EQ(1, actualTimeSteps.size());

        const auto& timeDependentData = actualTimeSteps[0].get();
        ASSERT_EQ(beginTime, timeDependentData.GetBeginTime());
        ASSERT_EQ(endTime, timeDependentData.GetEndTime());
        ASSERT_DOUBLE_EQ(waveHeightHm0, timeDependentData.GetWaveHeightHm0());
        ASSERT_DOUBLE_EQ(wavePeriodTm10, timeDependentData.GetWavePeriodTm10());
        ASSERT_DOUBLE_EQ(waveAngle, timeDependentData.GetWaveAngle());

        ASSERT_EQ(maximumWaveAngle, calculationInput.GetMaximumWaveAngle());
    }

    TEST_F(CalculationInputTest, Constructor_TimeDependentDataNotSubsequently_ThrowsInvalidCalculationDataException)
    {
        // Call
        const auto action = &CalculationInputTest::TimeDependentDataNotSubsequently;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidCalculationDataException>(
            action, "The begin time of an element must connect to the end time of the previous element.");
    }

    TEST_F(CalculationInputTest, Constructor_TimeDependentDataUnordered_ThrowsInvalidCalculationDataException)
    {
        // Call
        const auto action = &CalculationInputTest::TimeDependentDataUnordered;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidCalculationDataException>(
            action, "The begin time of an element must connect to the end time of the previous element.");
    }
}
