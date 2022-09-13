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
#include <random>

#include "HydraulicLoadFunctions.h"
#include "RandomValueHelper.h"

namespace DiKErnel::FunctionLibrary::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(HydraulicLoadFunctionsTest, WaveDirection_InputEqualTo0Degrees_ExpectedValue)
    {
        // Setup
        constexpr auto waveAngle = 0.0;

        // Call
        const auto waveDirection = HydraulicLoadFunctions::WaveDirection(waveAngle);

        // Assert
        ASSERT_DOUBLE_EQ(0.0, waveDirection);
    }

    TEST(HydraulicLoadFunctionsTest, WaveDirection_InputLargerThan0Degrees_ExpectedValue)
    {
        // Setup
        const double waveAngle = RandomValueHelper::GetRandomValue(0.0 + numeric_limits<double>::epsilon(), 540);

        // Call
        const auto waveDirection = HydraulicLoadFunctions::WaveDirection(waveAngle);

        // Assert
        ASSERT_DOUBLE_EQ(waveAngle, waveDirection);
    }

    TEST(HydraulicLoadFunctionsTest, WaveDirection_InputBetweenMinus180And0Degrees_ExpectedValue)
    {
        // Setup
        const double waveAngle = RandomValueHelper::GetRandomValue(-180 + numeric_limits<double>::epsilon(), -numeric_limits<double>::epsilon());

        // Call
        const auto waveDirection = HydraulicLoadFunctions::WaveDirection(waveAngle);

        // Assert
        ASSERT_DOUBLE_EQ(360.0 + waveAngle, waveDirection);
    }

    TEST(HydraulicLoadFunctionsTest, WaveDirection_InputEqualToMinus180Degrees_ExpectedValue)
    {
        // Setup
        constexpr auto waveAngle = -180;

        // Call
        const auto waveDirection = HydraulicLoadFunctions::WaveDirection(waveAngle);

        // Assert
        ASSERT_DOUBLE_EQ(180.0, waveDirection);
    }

    TEST(HydraulicLoadFunctionsTest, SlopeAngle_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto outerSlope = 0.25;

        // Call
        const auto slopeAngle = HydraulicLoadFunctions::SlopeAngle(outerSlope);

        // Assert
        ASSERT_DOUBLE_EQ(14.036243467926479, slopeAngle);
    }

    TEST(HydraulicLoadFunctionsTest, LoadingRevetment_LowerLimitAndUpperLimitSmallerThanZ_ExpectedFalse)
    {
        // Setup
        constexpr auto lowerLimitLoadingRevetment = 1.3;
        constexpr auto upperLimitLoadingRevetment = 1.4;
        constexpr auto z = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoadFunctions::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, z);

        // Assert
        ASSERT_FALSE(loadingRevetment);
    }

    TEST(HydraulicLoadFunctionsTest, LoadingRevetment_LowerLimitSmallerThanAndUpperLimitEqualToZ_ExpectedTrue)
    {
        // Setup
        constexpr auto lowerLimitLoadingRevetment = 1.4;
        constexpr auto upperLimitLoadingRevetment = 1.5;
        constexpr auto z = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoadFunctions::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, z);

        // Assert
        ASSERT_TRUE(loadingRevetment);
    }

    TEST(HydraulicLoadFunctionsTest, LoadingRevetment_LowerLimitSmallerAndUpperLimitLargerThanZ_ExpectedTrue)
    {
        // Setup
        constexpr auto lowerLimitLoadingRevetment = 1.4;
        constexpr auto upperLimitLoadingRevetment = 1.6;
        constexpr auto z = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoadFunctions::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, z);

        // Assert
        ASSERT_TRUE(loadingRevetment);
    }

    TEST(HydraulicLoadFunctionsTest, LoadingRevetment_LowerLimitEqualToAndUpperLimitLargerThanZ_ExpectedTrue)
    {
        // Setup
        constexpr auto lowerLimitLoadingRevetment = 1.5;
        constexpr auto upperLimitLoadingRevetment = 1.6;
        constexpr auto z = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoadFunctions::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, z);

        // Assert
        ASSERT_TRUE(loadingRevetment);
    }

    TEST(HydraulicLoadFunctionsTest, LoadingRevetment_LowerLimitAndUpperLimitLargerThanZ_ExpectedFalse)
    {
        // Setup
        constexpr auto lowerLimitLoadingRevetment = 1.6;
        constexpr auto upperLimitLoadingRevetment = 1.7;
        constexpr auto z = 1.5;

        // Call
        const auto loadingRevetment = HydraulicLoadFunctions::LoadingRevetment(lowerLimitLoadingRevetment, upperLimitLoadingRevetment, z);

        // Assert
        ASSERT_FALSE(loadingRevetment);
    }

    TEST(HydraulicLoadFunctionsTest, WaveSteepnessDeepWater_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto waveHeightHm0 = 1.6;
        constexpr auto wavePeriodTm10 = 5.2;
        constexpr auto gravitationalAcceleration = 9.81;

        // Call
        const auto waveSteepnessDeepWater = HydraulicLoadFunctions::WaveSteepnessDeepWater(waveHeightHm0, wavePeriodTm10,
                                                                                           gravitationalAcceleration);

        // Assert
        ASSERT_DOUBLE_EQ(0.037898686325266363, waveSteepnessDeepWater);
    }

    TEST(HydraulicLoadFunctionsTest, SurfSimilarityParameter_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto outerSlope = 0.25;
        constexpr auto waveHeightHm0 = 1.6;
        constexpr auto wavePeriodTm10 = 5.2;
        constexpr auto gravitationalAcceleration = 9.81;

        // Call
        const auto surfSimilarityParameter = HydraulicLoadFunctions::SurfSimilarityParameter(outerSlope, waveHeightHm0, wavePeriodTm10,
                                                                                             gravitationalAcceleration);

        // Assert
        ASSERT_DOUBLE_EQ(1.2841859985089348, surfSimilarityParameter);
    }

    TEST(HydraulicLoadFunctionsTest, VerticalDistanceWaterLevelElevation_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto z = 1.12;
        constexpr auto waterLevel = 0.03;

        // Call
        const auto verticalDistanceWaterLevelElevation = HydraulicLoadFunctions::VerticalDistanceWaterLevelElevation(z, waterLevel);

        // Assert
        ASSERT_DOUBLE_EQ(1.09, verticalDistanceWaterLevelElevation);
    }
}
