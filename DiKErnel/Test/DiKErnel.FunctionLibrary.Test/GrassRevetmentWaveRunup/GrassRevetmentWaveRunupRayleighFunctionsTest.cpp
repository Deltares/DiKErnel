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

#include "GrassRevetmentWaveRunupRayleighFunctions.h"

namespace DiKErnel::FunctionLibrary::Test
{
    TEST(GrassRevetmentWaveRunupRayleighFunctionsTest, CumulativeOverload_ValidInput_ExpectedValue)
    {
        // Setup
        const GrassRevetmentWaveRunupRayleighCumulativeOverloadInput input
        {
            ._averageNumberOfWaves = 225,
            ._representativeWaveRunup2P = 2.258,
            ._fixedNumberOfWaves = 10000,
            ._verticalDistanceWaterLevelElevation = 0.97,
            ._criticalFrontVelocity = 4.0,
            ._increasedLoadTransitionAlphaM = 1.1,
            ._reducedStrengthTransitionAlphaS = 1.2,
            ._frontVelocityCu = 1.3,
            ._gravitationalAcceleration = 9.81
        };

        // Call
        const auto cumulativeOverload = GrassRevetmentWaveRunupRayleighFunctions::CumulativeOverload(input);

        // Assert
        ASSERT_DOUBLE_EQ(735.67446176679459, cumulativeOverload);
    }
}
