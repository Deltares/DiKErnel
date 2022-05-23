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

#include "AssertHelper.h"
#include "GrassRevetmentWaveImpactTimeDependentOutput.h"
#include "TimeDependentOutput.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace std;
    using namespace TestUtil;

    TEST(GrassRevetmentWaveImpactTimeDependentOutputTest, Constructor_WithAllValuesSet_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto timeOfFailure = 3;
        constexpr auto loadingRevetment = true;
        constexpr auto upperLimitLoading = 0.4;
        constexpr auto lowerLimitLoading = 0.5;
        constexpr auto minimumWaveHeight = 0.6;
        constexpr auto maximumWaveHeight = 0.7;
        constexpr auto waveAngleImpact = 0.8;
        constexpr auto waveHeightImpact = 0.9;

        // Call
        const auto output = GrassRevetmentWaveImpactTimeDependentOutput(incrementDamage, damage, make_unique<int>(timeOfFailure), loadingRevetment,
                                                                        upperLimitLoading, lowerLimitLoading,
                                                                        make_unique<double>(minimumWaveHeight),
                                                                        make_unique<double>(maximumWaveHeight),
                                                                        make_unique<double>(waveAngleImpact),
                                                                        make_unique<double>(waveHeightImpact));

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(timeOfFailure, *output.GetTimeOfFailure());
        ASSERT_EQ(loadingRevetment, output.GetLoadingRevetment());
        ASSERT_DOUBLE_EQ(upperLimitLoading, output.GetUpperLimitLoading());
        ASSERT_DOUBLE_EQ(lowerLimitLoading, output.GetLowerLimitLoading());
        ASSERT_DOUBLE_EQ(minimumWaveHeight, *output.GetMinimumWaveHeight());
        ASSERT_DOUBLE_EQ(maximumWaveHeight, *output.GetMaximumWaveHeight());
        ASSERT_DOUBLE_EQ(waveAngleImpact, *output.GetWaveAngleImpact());
        ASSERT_DOUBLE_EQ(waveHeightImpact, *output.GetWaveHeightImpact());
    }

    TEST(GrassRevetmentWaveImpactTimeDependentOutputTest, Constructor_WithNullPtrValues_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto loadingRevetment = false;
        constexpr auto upperLimitLoading = 0.3;
        constexpr auto lowerLimitLoading = 0.4;

        // Call
        const auto output = GrassRevetmentWaveImpactTimeDependentOutput(incrementDamage, damage, nullptr, loadingRevetment, upperLimitLoading,
                                                                        lowerLimitLoading, nullptr, nullptr, nullptr, nullptr);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(nullptr, output.GetTimeOfFailure());
        ASSERT_EQ(loadingRevetment, output.GetLoadingRevetment());
        ASSERT_DOUBLE_EQ(upperLimitLoading, output.GetUpperLimitLoading());
        ASSERT_DOUBLE_EQ(lowerLimitLoading, output.GetLowerLimitLoading());
        ASSERT_EQ(nullptr, output.GetMinimumWaveHeight());
        ASSERT_EQ(nullptr, output.GetMaximumWaveHeight());
        ASSERT_EQ(nullptr, output.GetWaveAngleImpact());
        ASSERT_EQ(nullptr, output.GetWaveHeightImpact());
    }
}
