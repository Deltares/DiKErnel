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

#include "HydraulicLoad.h"

namespace DiKErnel::FunctionLibrary::Test
{
    TEST(HydraulicLoadTest, SlopeAngle_ValidInput_ExpectedValue)
    {
        // Setup
        const auto tanA = 1.1;

        // Call
        const auto slopeAngle = HydraulicLoad::SlopeAngle(tanA);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, slopeAngle);
    }

    TEST(HydraulicLoadTest, LoadingOfRevetment_ValidInput_ExpectedTrue)
    {
        // Setup
        const auto lowerLimitLoadingOfRevetment = 1.1;
        const auto upperLimitLoadingOfRevetment = 1.1;
        const auto positionZ = 1.1;

        // Call
        const auto loadingOfRevetment = HydraulicLoad::LoadingOfRevetment(lowerLimitLoadingOfRevetment, upperLimitLoadingOfRevetment, positionZ);

        // Assert
        ASSERT_TRUE(loadingOfRevetment);
    }

    TEST(HydraulicLoadTest, LoadingOfRevetment_ValidInput_ExpectedFalse)
    {
        // Setup
        const auto lowerLimitLoadingOfRevetment = 1.1;
        const auto upperLimitLoadingOfRevetment = 1.1;
        const auto positionZ = 1.1;

        // Call
        const auto loadingOfRevetment = HydraulicLoad::LoadingOfRevetment(lowerLimitLoadingOfRevetment, upperLimitLoadingOfRevetment, positionZ);

        // Assert
        ASSERT_FALSE(loadingOfRevetment);
    }

    TEST(HydraulicLoadTest, WaveSteepnessDeepWater_ValidInput_ExpectedValue)
    {
        // Setup
        const auto waveHeightHm0 = 1.1;
        const auto wavePeriodTm10 = 1.1;
        const auto gravitationalAcceleration = 1.1;

        // Call
        const auto waveSteepnessDeepWater = HydraulicLoad::WaveSteepnessDeepWater(waveHeightHm0, wavePeriodTm10, gravitationalAcceleration);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, waveSteepnessDeepWater);
    }

    TEST(HydraulicLoadTest, SurfSimilarityParameter_ValidInput_ExpectedValue)
    {
        // Setup
        const auto tanA = 1.1;
        const auto waveHeightHm0 = 1.1;
        const auto wavePeriodTm10 = 1.1;
        const auto gravitationalAcceleration = 1.1;

        // Call
        const auto surfSimilarityParameter = HydraulicLoad::SurfSimilarityParameter(tanA, waveHeightHm0, wavePeriodTm10,
                                                                                    gravitationalAcceleration);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, surfSimilarityParameter);
    }
}
