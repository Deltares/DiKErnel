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

#include "Revetment.h"

namespace DiKErnel::FunctionLibrary::Test
{
    TEST(RevetmentTest, IncrementTime_ValidInput_ExpectedValue)
    {
        // Setup
        const auto startTime = 1200;
        const auto endTime = 1500;

        // Call
        const auto incrementTime = Revetment::IncrementTime(startTime, endTime);

        // Assert
        ASSERT_EQ(300, incrementTime);
    }

    TEST(RevetmentTest, Damage_ValidInput_ExpectedValue)
    {
        // Setup
        const auto incrementDamage = 0.12;
        const auto initialDamage = 0.23;

        // Call
        const auto damage = Revetment::Damage(incrementDamage, initialDamage);

        // Assert
        ASSERT_DOUBLE_EQ(0.35, damage);
    }

    TEST(RevetmentTest, FailureRevetment_DamageAndInitialDamageSmallerThanFailureNumber_ExpectedFalse)
    {
        // Setup
        const auto initialDamage = 0.1;
        const auto damage = 0.2;
        const auto failureNumber = 0.3;

        // Call
        const auto failureRevetment = Revetment::FailureRevetment(damage, initialDamage, failureNumber);

        // Assert
        ASSERT_FALSE(failureRevetment);
    }

    TEST(RevetmentTest, FailureRevetment_InitialDamageEqualToFailureNumber_ExpectedFalse)
    {
        // Setup
        const auto initialDamage = 0.3;
        const auto damage = 0.4;
        const auto failureNumber = 0.3;

        // Call
        const auto failureRevetment = Revetment::FailureRevetment(damage, initialDamage, failureNumber);

        // Assert
        ASSERT_FALSE(failureRevetment);
    }

    TEST(RevetmentTest, FailureRevetment_DamageEqualToFailureNumber_ExpectedTrue)
    {
        // Setup
        const auto initialDamage = 0.2;
        const auto damage = 0.3;
        const auto failureNumber = 0.3;

        // Call
        const auto failureRevetment = Revetment::FailureRevetment(damage, initialDamage, failureNumber);

        // Assert
        ASSERT_TRUE(failureRevetment);
    }

    TEST(RevetmentTest, FailureRevetment_DamageLargerAndInitialDamageSmallerThanFailureNumber_ExpectedTrue)
    {
        // Setup
        const auto initialDamage = 0.2;
        const auto damage = 0.4;
        const auto failureNumber = 0.3;

        // Call
        const auto failureRevetment = Revetment::FailureRevetment(damage, initialDamage, failureNumber);

        // Assert
        ASSERT_TRUE(failureRevetment);
    }

    TEST(RevetmentTest, FailureRevetment_DamageAndInitialDamageLargerThanFailureNumber_ExpectedFalse)
    {
        // Setup
        const auto initialDamage = 0.4;
        const auto damage = 0.5;
        const auto failureNumber = 0.3;

        // Call
        const auto failureRevetment = Revetment::FailureRevetment(damage, initialDamage, failureNumber);

        // Assert
        ASSERT_FALSE(failureRevetment);
    }
}
