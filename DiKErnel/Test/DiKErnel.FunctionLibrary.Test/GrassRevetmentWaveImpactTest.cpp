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

#include "GrassRevetmentWaveImpact.h"

namespace DiKErnel::FunctionLibrary::Test
{
    TEST(GrassRevetmentWaveImpactTest, IncrementDamage_ValidInput_ExpectedValue)
    {
        // Setup
        const auto incrementTime = 1.1;
        const auto failureTime = 1.1;

        // Call
        const auto incrementDamage = GrassRevetmentWaveImpact::IncrementDamage(
            incrementTime,
            failureTime);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, incrementDamage);
    }

    TEST(GrassRevetmentWaveImpactTest, TimeLine_ValidInput_ExpectedValue)
    {
        // Setup
        const auto waveHeight = 1.1;
        const auto failureTimeAgwi = 1.1;
        const auto failureTimeBgwi = 1.1;
        const auto failureTimeCgwi = 1.1;

        // Call
        const auto timeLine = GrassRevetmentWaveImpact::TimeLine(
            waveHeight,
            failureTimeAgwi,
            failureTimeBgwi,
            failureTimeCgwi);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, timeLine);
    }

    TEST(GrassRevetmentWaveImpactTest, WaveHeight_ValidInput_ExpectedValue)
    {
        // Setup
        const auto minimumWaveHeight = 1.1;
        const auto maximumWaveHeight = 1.1;
        const auto waveAngleImpact = 1.1;
        const auto waveHeightHm0 = 1.1;

        // Call
        const auto waveHeight = GrassRevetmentWaveImpact::WaveHeight(
            minimumWaveHeight,
            maximumWaveHeight,
            waveAngleImpact,
            waveHeightHm0);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, waveHeight);
    }

    TEST(GrassRevetmentWaveImpactTest, MinimumWaveHeight_ValidInput_ExpectedValue)
    {
        // Setup
        const auto failureTimeAgwi = 1.1;
        const auto failureTimeBgwi = 1.1;
        const auto failureTimeCgwi = 1.1;
        const auto minimumWaveHeightTemax = 1.1;

        // Call
        const auto minimumWaveHeight = GrassRevetmentWaveImpact::MinimumWaveHeight(
            failureTimeAgwi,
            failureTimeBgwi,
            failureTimeCgwi,
            minimumWaveHeightTemax);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, minimumWaveHeight);
    }

    TEST(GrassRevetmentWaveImpactTest, MaximumWaveHeight_ValidInput_ExpectedValue)
    {
        // Setup
        const auto failureTimeAgwi = 1.1;
        const auto failureTimeBgwi = 1.1;
        const auto failureTimeCgwi = 1.1;
        const auto maximumWaveHeightTemin = 1.1;

        // Call
        const auto maximumWaveHeight = GrassRevetmentWaveImpact::MaximumWaveHeight(
            failureTimeAgwi,
            failureTimeBgwi,
            failureTimeCgwi,
            maximumWaveHeightTemin);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, maximumWaveHeight);
    }

    TEST(GrassRevetmentWaveImpactTest, WaveAngleImpact_ValidInput_ExpectedValue)
    {
        // Setup
        const auto waveAngle = 1.1;
        const auto waveAngleImpactNwa = 1.1;
        const auto waveAngleImpactQwa = 1.1;
        const auto waveAngleImpactRwa = 1.1;

        // Call
        const auto waveAngleImpact = GrassRevetmentWaveImpact::WaveAngleImpact(
            waveAngle,
            waveAngleImpactNwa,
            waveAngleImpactQwa,
            waveAngleImpactRwa);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, waveAngleImpact);
    }

    TEST(GrassRevetmentWaveImpactTest, UpperLimitLoading_ValidInput_ExpectedValue)
    {
        // Setup
        const auto waterLevel = 1.1;
        const auto waveHeightHm0 = 1.1;
        const auto upperLimitLoadingAul = 1.1;

        // Call
        const auto upperLimitLoading = GrassRevetmentWaveImpact::UpperLimitLoading(
            waterLevel,
            waveHeightHm0,
            upperLimitLoadingAul);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, upperLimitLoading);
    }

    TEST(GrassRevetmentWaveImpactTest, LowerLimitLoading_ValidInput_ExpectedValue)
    {
        // Setup
        const auto waterLevel = 1.1;
        const auto waveHeightHm0 = 1.1;
        const auto lowerLimitLoadingAll = 1.1;

        // Call
        const auto lowerLimitLoading = GrassRevetmentWaveImpact::LowerLimitLoading(
            waterLevel,
            waveHeightHm0,
            lowerLimitLoadingAll);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, lowerLimitLoading);
    }

    TEST(GrassRevetmentWaveImpactTest, FailureTime_ValidInput_ExpectedValue)
    {
        // Setup
        const auto timeLine = 1.1;
        const auto failureNumber = 1.1;
        const auto initialDamage = 1.1;

        // Call
        const auto failureTime = GrassRevetmentWaveImpact::FailureTime(
            timeLine,
            failureNumber,
            initialDamage);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, failureTime);
    }
}
