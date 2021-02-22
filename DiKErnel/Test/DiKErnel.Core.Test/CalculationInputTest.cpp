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

#include "CalculationInput.h"

namespace DiKErnel::Core::Test
{
    using namespace std;

    TEST(CalculationInputTest, Constructor_WithParameters_ExpectedValues)
    {
        // Setup
        vector<unique_ptr<ILocationDependentData>> locationDependentData;
        locationDependentData.push_back(make_unique<ILocationDependentData>());

        const auto beginTime = rand() % 100;
        const auto endTime = rand() % 100;
        const auto waveHeightHm0 = 0.1;
        const auto wavePeriodTm10 = 0.2;
        const auto waveAngle = 0.3;

        vector<unique_ptr<TimeDependentData>> timeSteps;
        timeSteps.push_back(make_unique<TimeDependentData>(beginTime, endTime, waveHeightHm0, wavePeriodTm10, waveAngle));

        const auto maximumWaveAngle = rand() % 100;

        // Call
        const CalculationInput calculationInput(move(locationDependentData), move(timeSteps), maximumWaveAngle);

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
}
