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

#include "RevetmentFunctions.h"

namespace DiKErnel::FunctionLibrary::Test
{
    using namespace std;
    using namespace testing;

    TEST(RevetmentFunctionsTest, IncrementTime_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto beginTime = 1200;
        constexpr auto endTime = 1500;

        // Call
        const auto incrementTime = RevetmentFunctions::IncrementTime(beginTime, endTime);

        // Assert
        ASSERT_EQ(300, incrementTime);
    }

    TEST(RevetmentFunctionsTest, AverageNumberOfWaves_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto incrementTime = 900.0;
        constexpr auto wavePeriodTm10 = 1.2;
        constexpr auto averageNumberOfWavesCtm = 6.5;

        // Call
        const auto averageNumberOfWaves = RevetmentFunctions::AverageNumberOfWaves(incrementTime, wavePeriodTm10, averageNumberOfWavesCtm);

        // Assert
        ASSERT_DOUBLE_EQ(115.38461538461539, averageNumberOfWaves);
    }

    TEST(RevetmentFunctionsTest, Damage_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto incrementDamage = 0.12;
        constexpr auto initialDamage = 0.23;

        // Call
        const auto damage = RevetmentFunctions::Damage(incrementDamage, initialDamage);

        // Assert
        ASSERT_DOUBLE_EQ(0.35, damage);
    }

    TEST(RevetmentFunctionsTest, FailureRevetment_DamageAndInitialDamageSmallerThanFailureNumber_ExpectedFalse)
    {
        // Setup
        constexpr auto initialDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto failureNumber = 0.3;

        // Call
        const auto failureRevetment = RevetmentFunctions::FailureRevetment(damage, initialDamage, failureNumber);

        // Assert
        ASSERT_FALSE(failureRevetment);
    }

    TEST(RevetmentFunctionsTest, FailureRevetment_InitialDamageEqualToFailureNumber_ExpectedFalse)
    {
        // Setup
        constexpr auto initialDamage = 0.3;
        constexpr auto damage = 0.4;
        constexpr auto failureNumber = 0.3;

        // Call
        const auto failureRevetment = RevetmentFunctions::FailureRevetment(damage, initialDamage, failureNumber);

        // Assert
        ASSERT_FALSE(failureRevetment);
    }

    TEST(RevetmentFunctionsTest, FailureRevetment_DamageEqualToFailureNumber_ExpectedTrue)
    {
        // Setup
        constexpr auto initialDamage = 0.2;
        constexpr auto damage = 0.3;
        constexpr auto failureNumber = 0.3;

        // Call
        const auto failureRevetment = RevetmentFunctions::FailureRevetment(damage, initialDamage, failureNumber);

        // Assert
        ASSERT_TRUE(failureRevetment);
    }

    TEST(RevetmentFunctionsTest, FailureRevetment_DamageLargerAndInitialDamageSmallerThanFailureNumber_ExpectedTrue)
    {
        // Setup
        constexpr auto initialDamage = 0.2;
        constexpr auto damage = 0.4;
        constexpr auto failureNumber = 0.3;

        // Call
        const auto failureRevetment = RevetmentFunctions::FailureRevetment(damage, initialDamage, failureNumber);

        // Assert
        ASSERT_TRUE(failureRevetment);
    }

    TEST(RevetmentFunctionsTest, FailureRevetment_DamageAndInitialDamageLargerThanFailureNumber_ExpectedFalse)
    {
        // Setup
        constexpr auto initialDamage = 0.4;
        constexpr auto damage = 0.5;
        constexpr auto failureNumber = 0.3;

        // Call
        const auto failureRevetment = RevetmentFunctions::FailureRevetment(damage, initialDamage, failureNumber);

        // Assert
        ASSERT_FALSE(failureRevetment);
    }

    TEST(RevetmentFunctionsTest, TimeOfFailure_ValidUnroundedInput_ExpectedValue)
    {
        // Setup
        constexpr auto durationInTimeStepFailure = 254.001;
        constexpr auto beginTime = 1568;

        // Call
        const auto timeOfFailure = RevetmentFunctions::TimeOfFailure(durationInTimeStepFailure, beginTime);

        // Assert
        ASSERT_EQ(1823, timeOfFailure);
    }

    TEST(RevetmentFunctionsTest, DurationInTimeStepFailure_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto incrementTime = 550;
        constexpr auto incrementDamage = 0.234;
        constexpr auto failureNumber = 1.0;
        constexpr auto initialDamage = 0.836;

        // Call
        const auto durationInTimeStepFailure = RevetmentFunctions::DurationInTimeStepFailure(
            incrementTime, incrementDamage, failureNumber, initialDamage);

        // Assert
        ASSERT_DOUBLE_EQ(385.47008547008551, durationInTimeStepFailure);
    }

    TEST(RevetmentFunctionsTest, TimeOfFailure_ValidRoundedInput_ExpectedValue)
    {
        // Setup
        constexpr auto durationInTimeStepFailure = 254;
        constexpr auto beginTime = 1568;

        // Call
        const auto timeOfFailure = RevetmentFunctions::TimeOfFailure(durationInTimeStepFailure, beginTime);

        // Assert
        ASSERT_EQ(1822, timeOfFailure);
    }
}
