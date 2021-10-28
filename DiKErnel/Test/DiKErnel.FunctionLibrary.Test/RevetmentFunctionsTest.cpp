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

#include "RevetmentFunctions.h"

namespace DiKErnel::FunctionLibrary::Test
{
    using namespace std;
    using namespace testing;

    struct RevetmentFunctionsTest : Test
    {
        const vector<pair<double, double>> _testDikeProfile
        {
            {
                1.0,
                1.1
            },
            {
                2.0,
                2.2
            },
            {
                3.0,
                3.3
            }
        };

        const vector<pair<double, double>> _testDikeProfileWithDescendingHeight
        {
            {
                1.0,
                3.3
            },
            {
                2.0,
                2.2
            },
            {
                3.0,
                1.1
            }
        };
    };

    TEST_F(RevetmentFunctionsTest, IncrementTime_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto beginTime = 1200;
        constexpr auto endTime = 1500;

        // Call
        const auto incrementTime = RevetmentFunctions::IncrementTime(beginTime, endTime);

        // Assert
        ASSERT_EQ(300, incrementTime);
    }

    TEST_F(RevetmentFunctionsTest, AverageNumberOfWaves_ValidInput_ExpectedValue)
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

    TEST_F(RevetmentFunctionsTest, Damage_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto incrementDamage = 0.12;
        constexpr auto initialDamage = 0.23;

        // Call
        const auto damage = RevetmentFunctions::Damage(incrementDamage, initialDamage);

        // Assert
        ASSERT_DOUBLE_EQ(0.35, damage);
    }

    TEST_F(RevetmentFunctionsTest, InterpolationVerticalHeight_HorizontalPositionLeftOfDikeProfile_ExpectedValue)
    {
        // Call
        const auto verticalHeight = RevetmentFunctions::InterpolationVerticalHeight(0.0, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), verticalHeight);
    }

    TEST_F(RevetmentFunctionsTest, InterpolationVerticalHeight_HorizontalPositionOnFirstDikeProfilePoint_ExpectedValue)
    {
        // Call
        const auto verticalHeight = RevetmentFunctions::InterpolationVerticalHeight(1.0, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, verticalHeight);
    }

    TEST_F(RevetmentFunctionsTest, InterpolationVerticalHeight_HorizontalPositionOnRandomDikeProfilePoint_ExpectedValue)
    {
        // Call
        const auto verticalHeight = RevetmentFunctions::InterpolationVerticalHeight(2.0, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(2.2, verticalHeight);
    }

    TEST_F(RevetmentFunctionsTest, InterpolationVerticalHeight_HorizontalPositionOnLastDikeProfilePoint_ExpectedValue)
    {
        // Call
        const auto verticalHeight = RevetmentFunctions::InterpolationVerticalHeight(3.0, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(3.3, verticalHeight);
    }

    TEST_F(RevetmentFunctionsTest, InterpolationVerticalHeight_HorizontalPositionBetweenAscendingDikeProfilePoints_ExpectedValue)
    {
        // Call
        const auto verticalHeight = RevetmentFunctions::InterpolationVerticalHeight(1.5, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(1.65, verticalHeight);
    }

    TEST_F(RevetmentFunctionsTest, InterpolationVerticalHeight_HorizontalPositionBetweenDescendingDikeProfilePoints_ExpectedValue)
    {
        // Call
        const auto verticalHeight = RevetmentFunctions::InterpolationVerticalHeight(2.5, _testDikeProfileWithDescendingHeight);

        // Assert
        ASSERT_DOUBLE_EQ(1.65, verticalHeight);
    }

    TEST_F(RevetmentFunctionsTest, InterpolationVerticalHeight_HorizontalPositionRightOfDikeProfile_ExpectedValue)
    {
        // Call
        const auto verticalHeight = RevetmentFunctions::InterpolationVerticalHeight(4.0, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), verticalHeight);
    }

    TEST_F(RevetmentFunctionsTest, InterpolationHorizontalPosition_VerticalHeightBelowDikeProfile_ExpectedValue)
    {
        // Call
        const auto horizontalPosition = RevetmentFunctions::InterpolationHorizontalPosition(0.0, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), horizontalPosition);
    }

    TEST_F(RevetmentFunctionsTest, InterpolationHorizontalPosition_VerticalHeightOnFirstDikeProfilePoint_ExpectedValue)
    {
        // Call
        const auto horizontalPosition = RevetmentFunctions::InterpolationHorizontalPosition(1.1, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(1.0, horizontalPosition);
    }

    TEST_F(RevetmentFunctionsTest, InterpolationHorizontalPosition_VerticalHeightOnRandomDikeProfilePoint_ExpectedValue)
    {
        // Call
        const auto horizontalPosition = RevetmentFunctions::InterpolationHorizontalPosition(2.2, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(2.0, horizontalPosition);
    }

    TEST_F(RevetmentFunctionsTest, InterpolationHorizontalPosition_VerticalHeightOnLastDikeProfilePoint_ExpectedValue)
    {
        // Call
        const auto horizontalPosition = RevetmentFunctions::InterpolationHorizontalPosition(3.3, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(3.0, horizontalPosition);
    }

    TEST_F(RevetmentFunctionsTest, InterpolationHorizontalPosition_VerticalHeightBetweenProfilePoints_ExpectedValue)
    {
        // Call
        const auto horizontalPosition = RevetmentFunctions::InterpolationHorizontalPosition(1.65, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(1.5, horizontalPosition);
    }

    TEST_F(RevetmentFunctionsTest, InterpolationHorizontalPosition_VerticalHeightAboveDikeProfile_ExpectedValue)
    {
        // Call
        const auto horizontalPosition = RevetmentFunctions::InterpolationHorizontalPosition(4.0, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), horizontalPosition);
    }

    TEST_F(RevetmentFunctionsTest, FailureRevetment_DamageAndInitialDamageSmallerThanFailureNumber_ExpectedFalse)
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

    TEST_F(RevetmentFunctionsTest, FailureRevetment_InitialDamageEqualToFailureNumber_ExpectedFalse)
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

    TEST_F(RevetmentFunctionsTest, FailureRevetment_DamageEqualToFailureNumber_ExpectedTrue)
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

    TEST_F(RevetmentFunctionsTest, FailureRevetment_DamageLargerAndInitialDamageSmallerThanFailureNumber_ExpectedTrue)
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

    TEST_F(RevetmentFunctionsTest, FailureRevetment_DamageAndInitialDamageLargerThanFailureNumber_ExpectedFalse)
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

    TEST_F(RevetmentFunctionsTest, TimeOfFailure_ValidUnroundedInput_ExpectedValue)
    {
        // Setup
        constexpr auto durationInTimeStepFailure = 254.001;
        constexpr auto beginTime = 1568;

        // Call
        const auto timeOfFailure = RevetmentFunctions::TimeOfFailure(durationInTimeStepFailure, beginTime);

        // Assert
        ASSERT_EQ(1823, timeOfFailure);
    }

    TEST_F(RevetmentFunctionsTest, DurationInTimeStepFailure_ValidInput_ExpectedValue)
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

    TEST_F(RevetmentFunctionsTest, TimeOfFailure_ValidRoundedInput_ExpectedValue)
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
