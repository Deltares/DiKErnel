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
#include "GrassRevetmentWaveRunupRayleighTimeDependentOutput.h"
#include "TimeDependentOutput.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace std;
    using namespace TestUtil;

    TEST(GrassRevetmentWaveRunupRayleighTimeDependentOutputTest, Constructor_WithAllValuesSet_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto timeOfFailure = 3;
        constexpr auto verticalDistanceWaterLevelElevation = 0.4;
        constexpr auto waveAngleImpact = 0.5;
        constexpr auto representativeWaveRunup2P = 0.6;
        constexpr auto cumulativeOverload = 0.7;

        // Call
        const GrassRevetmentWaveRunupRayleighTimeDependentOutput output(incrementDamage, damage, make_unique<int>(timeOfFailure),
                                                                        verticalDistanceWaterLevelElevation, make_unique<double>(waveAngleImpact),
                                                                        make_unique<double>(representativeWaveRunup2P),
                                                                        make_unique<double>(cumulativeOverload));

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(timeOfFailure, *output.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(verticalDistanceWaterLevelElevation, output.GetVerticalDistanceWaterLevelElevation());
        ASSERT_DOUBLE_EQ(waveAngleImpact, *output.GetWaveAngleImpact());
        ASSERT_DOUBLE_EQ(representativeWaveRunup2P, *output.GetRepresentativeWaveRunup2P());
        ASSERT_DOUBLE_EQ(cumulativeOverload, *output.GetCumulativeOverload());
    }

    TEST(GrassRevetmentWaveRunupRayleighTimeDependentOutputTest, Constructor_WithNullPtrValues_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto verticalDistanceWaterLevelElevation = 0.3;

        // Call
        const GrassRevetmentWaveRunupRayleighTimeDependentOutput output(incrementDamage, damage, nullptr, verticalDistanceWaterLevelElevation,
                                                                        nullptr, nullptr, nullptr);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(nullptr, output.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(verticalDistanceWaterLevelElevation, output.GetVerticalDistanceWaterLevelElevation());
        ASSERT_EQ(nullptr, output.GetWaveAngleImpact());
        ASSERT_EQ(nullptr, output.GetRepresentativeWaveRunup2P());
        ASSERT_EQ(nullptr, output.GetCumulativeOverload());
    }
}
