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

#include "GrassRevetmentOvertoppingFunctions.h"

namespace DiKErnel::FunctionLibrary::Test
{
    TEST(GrassRevetmentOvertoppingFunctionsTest, RepresentativeWaveRunup2P_ValidInput_ExpectedValue)
    {
        // Setup
        const GrassRevetmentOvertoppingRepresentative2PInput input
        {
            ._waterLevel = 5.5,
            ._waveHeightHm0 = 1.6,
            ._wavePeriodTm10 = 4.7,
            ._waveDirection = 350,
            ._xValuesProfile = {
                5,
                15,
                22,
                30
            },
            ._zValuesProfile = {
                0,
                3,
                3.2,
                7.5
            },
            ._roughnessCoefficients = {
                1,
                0.75,
                0.5
            },
            ._dikeHeight = 7.7
        };

        // Call
        const auto representativeWaveRunup2P = GrassRevetmentOvertoppingFunctions::RepresentativeWaveRunup2P(input);

        // Assert
        ASSERT_DOUBLE_EQ(2.60170961496113, representativeWaveRunup2P);
    }

    TEST(GrassRevetmentOvertoppingFunctionsTest, CumulativeOverload_ValidInput_ExpectedValue)
    {
        // Setup
        GrassRevetmentOvertoppingCumulativeOverloadInput input
        {
            ._accelerationAlphaA = 1.4,
            ._frontVelocityCwo = 1.45
        };

        input._averageNumberOfWaves = 832.56;
        input._representativeWaveRunup2P = 2.602;
        input._fixedNumberOfWaves = 10000;
        input._verticalDistanceWaterLevelElevation = 2.2;
        input._criticalFrontVelocity = 6.6;
        input._increasedLoadTransitionAlphaM = 1.0;
        input._reducedStrengthTransitionAlphaS = 1.0;
        input._gravitationalAcceleration = 9.81;

        // Call
        const auto cumulativeOverload = GrassRevetmentOvertoppingFunctions::CumulativeOverload(input);

        // Assert
        ASSERT_DOUBLE_EQ(14.883904828110145, cumulativeOverload);
    }
}
