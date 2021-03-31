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
        const auto tanA = 0.25;

        // Call
        const auto slopeAngle = HydraulicLoad::SlopeAngle(tanA);

        // Assert
        ASSERT_DOUBLE_EQ(14.036243467926479, slopeAngle);
    }

    TEST(HydraulicLoadTest, LoadingRevetment_LowerLimitAndUpperLimitSmallerThanPositionZ_ExpectedFalse)
    {
        // Setup
        const auto lowerLimitLoadingRevetment = 1.3;
        const auto upperLimitLoadingRevetment = 1.4;
        const auto positionZ = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoad::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, positionZ);

        // Assert
        ASSERT_FALSE(loadingRevetment);
    }

    TEST(HydraulicLoadTest, LoadingRevetment_LowerLimitSmallerThanAndUpperLimitEqualToPositionZ_ExpectedTrue)
    {
        // Setup
        const auto lowerLimitLoadingRevetment = 1.4;
        const auto upperLimitLoadingRevetment = 1.5;
        const auto positionZ = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoad::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, positionZ);

        // Assert
        ASSERT_TRUE(loadingRevetment);
    }

    TEST(HydraulicLoadTest, LoadingRevetment_LowerLimitSmallerAndUpperLimitLargerThanPositionZ_ExpectedTrue)
    {
        // Setup
        const auto lowerLimitLoadingRevetment = 1.4;
        const auto upperLimitLoadingRevetment = 1.6;
        const auto positionZ = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoad::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, positionZ);

        // Assert
        ASSERT_TRUE(loadingRevetment);
    }

    TEST(HydraulicLoadTest, LoadingRevetment_LowerLimitEqualToAndUpperLimitLargerThanPositionZ_ExpectedTrue)
    {
        // Setup
        const auto lowerLimitLoadingRevetment = 1.5;
        const auto upperLimitLoadingRevetment = 1.6;
        const auto positionZ = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoad::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, positionZ);

        // Assert
        ASSERT_TRUE(loadingRevetment);
    }

    TEST(HydraulicLoadTest, LoadingRevetment_LowerLimitAndUpperLimitLargerThanPositionZ_ExpectedFalse)
    {
        // Setup
        const auto lowerLimitLoadingRevetment = 1.6;
        const auto upperLimitLoadingRevetment = 1.7;
        const auto positionZ = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoad::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, positionZ);

        // Assert
        ASSERT_FALSE(loadingRevetment);
    }

    TEST(HydraulicLoadTest, WaveSteepnessDeepWater_ValidInput_ExpectedValue)
    {
        // Setup
        const auto waveHeightHm0 = 1.6;
        const auto wavePeriodTm10 = 5.2;
        const auto gravitationalAcceleration = 9.81;

        // Call
        const auto waveSteepnessDeepWater = HydraulicLoad::WaveSteepnessDeepWater(waveHeightHm0, wavePeriodTm10, gravitationalAcceleration);

        // Assert
        ASSERT_DOUBLE_EQ(0.037898686325266363, waveSteepnessDeepWater);
    }

    TEST(HydraulicLoadTest, SurfSimilarityParameter_ValidInput_ExpectedValue)
    {
        // Setup
        const auto tanA = 0.25;
        const auto waveHeightHm0 = 1.6;
        const auto wavePeriodTm10 = 5.2;
        const auto gravitationalAcceleration = 9.81;

        // Call
        const auto surfSimilarityParameter = HydraulicLoad::SurfSimilarityParameter(tanA, waveHeightHm0, wavePeriodTm10,
                                                                                    gravitationalAcceleration);

        // Assert
        ASSERT_DOUBLE_EQ(1.2841859985089348, surfSimilarityParameter);
    }
}
