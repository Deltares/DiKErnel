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

#include "GrassRevetmentWaveImpactFunctions.h"

namespace DiKErnel::FunctionLibrary::Test
{
    TEST(GrassRevetmentWaveImpactFunctionsTest, IncrementDamage_ValidInput_ExpectedValue)
    {
        // Setup
        const auto incrementTime = 900;
        const auto timeLine = 3319.12;

        // Call
        const auto incrementDamage = GrassRevetmentWaveImpactFunctions::IncrementDamage(incrementTime, timeLine);

        // Assert
        ASSERT_DOUBLE_EQ(0.27115621007978019, incrementDamage);
    }

    TEST(GrassRevetmentWaveImpactFunctionsTest, TimeLine_ValidInput_ExpectedValue)
    {
        // Setup
        const auto waveHeightImpact = 1.0;
        const auto timeLineAgwi = 0.8;
        const auto timeLineBgwi = -0.00001944;
        const auto timeLineCgwi = 0.25;

        // Call
        const auto timeLine = GrassRevetmentWaveImpactFunctions::TimeLine(waveHeightImpact, timeLineAgwi, timeLineBgwi, timeLineCgwi);

        // Assert
        ASSERT_DOUBLE_EQ(3319.8827745664184, timeLine);
    }

    TEST(GrassRevetmentWaveImpactFunctionsTest, WaveHeightImpact_ValidInput_ExpectedValue)
    {
        // Setup
        const auto minimumWaveHeight = 0.25;
        const auto maximumWaveHeight = 1.05;
        const auto waveAngleImpact = 0.79;
        const auto waveHeightHm0 = 1.0;

        // Call
        const auto waveHeightImpact = GrassRevetmentWaveImpactFunctions::WaveHeightImpact(minimumWaveHeight, maximumWaveHeight, waveAngleImpact,
                                                                                 waveHeightHm0);

        // Assert
        ASSERT_DOUBLE_EQ(0.79, waveHeightImpact);
    }

    TEST(GrassRevetmentWaveImpactFunctionsTest, MinimumWaveHeight_ValidInput_ExpectedValue)
    {
        // Setup
        const auto timeLineAgwi = 0.8;
        const auto timeLineBgwi = -0.00001944;
        const auto timeLineCgwi = 0.25;
        const auto minimumWaveHeightTemax = 3600000.0;

        // Call
        const auto minimumWaveHeight =
                GrassRevetmentWaveImpactFunctions::MinimumWaveHeight(timeLineAgwi, timeLineBgwi, timeLineCgwi, minimumWaveHeightTemax);

        // Assert
        ASSERT_DOUBLE_EQ(0.25, minimumWaveHeight);
    }

    TEST(GrassRevetmentWaveImpactFunctionsTest, MaximumWaveHeight_ValidInput_ExpectedValue)
    {
        // Setup
        const auto timeLineAgwi = 0.8;
        const auto timeLineBgwi = -0.00001944;
        const auto timeLineCgwi = 0.25;
        const auto maximumWaveHeightTemin = 3.6;

        // Call
        const auto maximumWaveHeight =
                GrassRevetmentWaveImpactFunctions::MaximumWaveHeight(timeLineAgwi, timeLineBgwi, timeLineCgwi, maximumWaveHeightTemin);

        // Assert
        ASSERT_DOUBLE_EQ(1.0499440147590584, maximumWaveHeight);
    }

    TEST(GrassRevetmentWaveImpactFunctionsTest, WaveAngleImpact_ValidInputAndWaveAngleSmallerThan90Degrees_ExpectedValue)
    {
        // Setup
        const auto waveAngle = 45.0;
        const auto waveAngleImpactNwa = 0.67;
        const auto waveAngleImpactQwa = 0.35;
        const auto waveAngleImpactRwa = 10.0;

        // Call
        const auto waveAngleImpact = GrassRevetmentWaveImpactFunctions::WaveAngleImpact(waveAngle, waveAngleImpactNwa, waveAngleImpactQwa,
                                                                               waveAngleImpactRwa);

        // Assert
        ASSERT_DOUBLE_EQ(0.79278413661028446, waveAngleImpact);
    }

    TEST(GrassRevetmentWaveImpactFunctionsTest, WaveAngleImpact_ValidInputAndWaveAngleEqualTo90Degrees_ExpectedValue)
    {
        // Setup
        const auto waveAngle = 90.0;
        const auto waveAngleImpactNwa = 0.67;
        const auto waveAngleImpactQwa = 0.35;
        const auto waveAngleImpactRwa = 10.0;

        // Call
        const auto waveAngleImpact = GrassRevetmentWaveImpactFunctions::WaveAngleImpact(waveAngle, waveAngleImpactNwa, waveAngleImpactQwa,
                                                                               waveAngleImpactRwa);

        // Assert
        ASSERT_DOUBLE_EQ(0.35, waveAngleImpact);
    }

    TEST(GrassRevetmentWaveImpactFunctionsTest, WaveAngleImpact_ValidInputAndWaveAngleLargerThan90Degrees_ExpectedValue)
    {
        // Setup
        const auto waveAngle = 91.0;
        const auto waveAngleImpactNwa = 0.67;
        const auto waveAngleImpactQwa = 0.35;
        const auto waveAngleImpactRwa = 10.0;

        // Call
        const auto waveAngleImpact = GrassRevetmentWaveImpactFunctions::WaveAngleImpact(waveAngle, waveAngleImpactNwa, waveAngleImpactQwa,
                                                                               waveAngleImpactRwa);

        // Assert
        ASSERT_DOUBLE_EQ(0.315, waveAngleImpact);
    }

    TEST(GrassRevetmentWaveImpactFunctionsTest, UpperLimitLoading_ValidInput_ExpectedValue)
    {
        // Setup
        const auto waterLevel = 0.03;
        const auto waveHeightHm0 = 1.0;
        const auto upperLimitLoadingAul = 0.001;

        // Call
        const auto upperLimitLoading = GrassRevetmentWaveImpactFunctions::UpperLimitLoading(waterLevel, waveHeightHm0, upperLimitLoadingAul);

        // Assert
        ASSERT_DOUBLE_EQ(0.029, upperLimitLoading);
    }

    TEST(GrassRevetmentWaveImpactFunctionsTest, LowerLimitLoading_ValidInput_ExpectedValue)
    {
        // Setup
        const auto waterLevel = 0.03;
        const auto waveHeightHm0 = 1.0;
        const auto lowerLimitLoadingAll = 0.5;

        // Call
        const auto lowerLimitLoading = GrassRevetmentWaveImpactFunctions::LowerLimitLoading(waterLevel, waveHeightHm0, lowerLimitLoadingAll);

        // Assert
        ASSERT_DOUBLE_EQ(-0.47, lowerLimitLoading);
    }
}
