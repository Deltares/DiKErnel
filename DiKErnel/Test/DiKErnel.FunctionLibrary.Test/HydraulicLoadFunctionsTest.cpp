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

#include "HydraulicLoadFunctions.h"

namespace DiKErnel::FunctionLibrary::Test
{
    TEST(HydraulicLoadFunctionsTest, SlopeAngle_ValidInput_ExpectedValue)
    {
        // Setup
        const auto outerSlope = 0.25;

        // Call
        const auto slopeAngle = HydraulicLoadFunctions::SlopeAngle(outerSlope);

        // Assert
        ASSERT_DOUBLE_EQ(14.036243467926479, slopeAngle);
    }

    TEST(HydraulicLoadFunctionsTest, LoadingRevetment_LowerLimitAndUpperLimitSmallerThanZ_ExpectedFalse)
    {
        // Setup
        const auto lowerLimitLoadingRevetment = 1.3;
        const auto upperLimitLoadingRevetment = 1.4;
        const auto z = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoadFunctions::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, z);

        // Assert
        ASSERT_FALSE(loadingRevetment);
    }

    TEST(HydraulicLoadFunctionsTest, LoadingRevetment_LowerLimitSmallerThanAndUpperLimitEqualToZ_ExpectedTrue)
    {
        // Setup
        const auto lowerLimitLoadingRevetment = 1.4;
        const auto upperLimitLoadingRevetment = 1.5;
        const auto z = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoadFunctions::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, z);

        // Assert
        ASSERT_TRUE(loadingRevetment);
    }

    TEST(HydraulicLoadFunctionsTest, LoadingRevetment_LowerLimitSmallerAndUpperLimitLargerThanZ_ExpectedTrue)
    {
        // Setup
        const auto lowerLimitLoadingRevetment = 1.4;
        const auto upperLimitLoadingRevetment = 1.6;
        const auto z = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoadFunctions::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, z);

        // Assert
        ASSERT_TRUE(loadingRevetment);
    }

    TEST(HydraulicLoadFunctionsTest, LoadingRevetment_LowerLimitEqualToAndUpperLimitLargerThanZ_ExpectedTrue)
    {
        // Setup
        const auto lowerLimitLoadingRevetment = 1.5;
        const auto upperLimitLoadingRevetment = 1.6;
        const auto z = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoadFunctions::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, z);

        // Assert
        ASSERT_TRUE(loadingRevetment);
    }

    TEST(HydraulicLoadFunctionsTest, LoadingRevetment_LowerLimitAndUpperLimitLargerThanZ_ExpectedFalse)
    {
        // Setup
        const auto lowerLimitLoadingRevetment = 1.6;
        const auto upperLimitLoadingRevetment = 1.7;
        const auto z = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoadFunctions::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, z);

        // Assert
        ASSERT_FALSE(loadingRevetment);
    }

    TEST(HydraulicLoadFunctionsTest, WaveSteepnessDeepWater_ValidInput_ExpectedValue)
    {
        // Setup
        const auto waveHeightHm0 = 1.6;
        const auto wavePeriodTm10 = 5.2;
        const auto gravitationalAcceleration = 9.81;

        // Call
        const auto waveSteepnessDeepWater = HydraulicLoadFunctions::WaveSteepnessDeepWater(waveHeightHm0, wavePeriodTm10, gravitationalAcceleration);

        // Assert
        ASSERT_DOUBLE_EQ(0.037898686325266363, waveSteepnessDeepWater);
    }

    TEST(HydraulicLoadFunctionsTest, SurfSimilarityParameter_ValidInput_ExpectedValue)
    {
        // Setup
        const auto outerSlope = 0.25;
        const auto waveHeightHm0 = 1.6;
        const auto wavePeriodTm10 = 5.2;
        const auto gravitationalAcceleration = 9.81;

        // Call
        const auto surfSimilarityParameter = HydraulicLoadFunctions::SurfSimilarityParameter(outerSlope, waveHeightHm0, wavePeriodTm10,
                                                                                    gravitationalAcceleration);

        // Assert
        ASSERT_DOUBLE_EQ(1.2841859985089348, surfSimilarityParameter);
    }

    TEST(HydraulicLoadFunctionsTest, VerticalDistanceWaterLevelElevation_ValidInput_ExpectedValue)
    {
        // Setup
        const auto z = 1.12;
        const auto waterLevel = 0.03;

        // Call
        const auto verticalDistanceWaterLevelElevation = HydraulicLoadFunctions::VerticalDistanceWaterLevelElevation(z, waterLevel);

        // Assert
        ASSERT_DOUBLE_EQ(1.09, verticalDistanceWaterLevelElevation);
    }
}
