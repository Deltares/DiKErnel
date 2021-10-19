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
    using namespace std;
    using namespace testing;

    struct RevetmentTest : Test
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

    TEST_F(RevetmentTest, IncrementTime_ValidInput_ExpectedValue)
    {
        // Setup
        const auto beginTime = 1200;
        const auto endTime = 1500;

        // Call
        const auto incrementTime = Revetment::IncrementTime(beginTime, endTime);

        // Assert
        ASSERT_EQ(300, incrementTime);
    }

    TEST_F(RevetmentTest, AverageNumberOfWaves_ValidInput_ExpectedValue)
    {
        // Setup
        const auto incrementTime = 900.0;
        const auto wavePeriodTm10 = 1.2;
        const auto averageNumberOfWavesCtm = 6.5;

        // Call
        const auto averageNumberOfWaves = Revetment::AverageNumberOfWaves(incrementTime, wavePeriodTm10, averageNumberOfWavesCtm);

        // Assert
        ASSERT_DOUBLE_EQ(115.38461538461539, averageNumberOfWaves);
    }

    TEST_F(RevetmentTest, Damage_ValidInput_ExpectedValue)
    {
        // Setup
        const auto incrementDamage = 0.12;
        const auto initialDamage = 0.23;

        // Call
        const auto damage = Revetment::Damage(incrementDamage, initialDamage);

        // Assert
        ASSERT_DOUBLE_EQ(0.35, damage);
    }

    TEST_F(RevetmentTest, InterpolationVerticalHeight_HorizontalPositionLeftOfDikeProfile_ExpectedValue)
    {
        // Call
        const auto verticalHeight = Revetment::InterpolationVerticalHeight(0.0, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), verticalHeight);
    }

    TEST_F(RevetmentTest, InterpolationVerticalHeight_HorizontalPositionOnFirstDikeProfilePoint_ExpectedValue)
    {
        // Call
        const auto verticalHeight = Revetment::InterpolationVerticalHeight(1.0, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, verticalHeight);
    }

    TEST_F(RevetmentTest, InterpolationVerticalHeight_HorizontalPositionOnRandomDikeProfilePoint_ExpectedValue)
    {
        // Call
        const auto verticalHeight = Revetment::InterpolationVerticalHeight(2.0, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(2.2, verticalHeight);
    }

    TEST_F(RevetmentTest, InterpolationVerticalHeight_HorizontalPositionOnLastDikeProfilePoint_ExpectedValue)
    {
        // Call
        const auto verticalHeight = Revetment::InterpolationVerticalHeight(3.0, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(3.3, verticalHeight);
    }

    TEST_F(RevetmentTest, InterpolationVerticalHeight_HorizontalPositionBetweenAscendingDikeProfilePoints_ExpectedValue)
    {
        // Call
        const auto verticalHeight = Revetment::InterpolationVerticalHeight(1.5, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(1.65, verticalHeight);
    }

    TEST_F(RevetmentTest, InterpolationVerticalHeight_HorizontalPositionBetweenDescendingDikeProfilePoints_ExpectedValue)
    {
        // Call
        const auto verticalHeight = Revetment::InterpolationVerticalHeight(2.5, _testDikeProfileWithDescendingHeight);

        // Assert
        ASSERT_DOUBLE_EQ(1.65, verticalHeight);
    }

    TEST_F(RevetmentTest, InterpolationVerticalHeight_HorizontalPositionRightOfDikeProfile_ExpectedValue)
    {
        // Call
        const auto verticalHeight = Revetment::InterpolationVerticalHeight(4.0, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), verticalHeight);
    }

    TEST_F(RevetmentTest, InterpolationHorizontalPosition_VerticalHeightBelowDikeProfile_ExpectedValue)
    {
        // Call
        const auto horizontalPosition = Revetment::InterpolationHorizontalPosition(0.0, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), horizontalPosition);
    }

    TEST_F(RevetmentTest, InterpolationHorizontalPosition_VerticalHeightOnFirstDikeProfilePoint_ExpectedValue)
    {
        // Call
        const auto horizontalPosition = Revetment::InterpolationHorizontalPosition(1.1, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(1.0, horizontalPosition);
    }

    TEST_F(RevetmentTest, InterpolationHorizontalPosition_VerticalHeightOnRandomDikeProfilePoint_ExpectedValue)
    {
        // Call
        const auto horizontalPosition = Revetment::InterpolationHorizontalPosition(2.2, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(2.0, horizontalPosition);
    }

    TEST_F(RevetmentTest, InterpolationHorizontalPosition_VerticalHeightOnLastDikeProfilePoint_ExpectedValue)
    {
        // Call
        const auto horizontalPosition = Revetment::InterpolationHorizontalPosition(3.3, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(3.0, horizontalPosition);
    }

    TEST_F(RevetmentTest, InterpolationHorizontalPosition_VerticalHeightBetweenProfilePoints_ExpectedValue)
    {
        // Call
        const auto horizontalPosition = Revetment::InterpolationHorizontalPosition(1.65, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(1.5, horizontalPosition);
    }

    TEST_F(RevetmentTest, InterpolationHorizontalPosition_VerticalHeightAboveDikeProfile_ExpectedValue)
    {
        // Call
        const auto horizontalPosition = Revetment::InterpolationHorizontalPosition(4.0, _testDikeProfile);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), horizontalPosition);
    }

    TEST_F(RevetmentTest, FailureRevetment_DamageAndInitialDamageSmallerThanFailureNumber_ExpectedFalse)
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

    TEST_F(RevetmentTest, FailureRevetment_InitialDamageEqualToFailureNumber_ExpectedFalse)
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

    TEST_F(RevetmentTest, FailureRevetment_DamageEqualToFailureNumber_ExpectedTrue)
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

    TEST_F(RevetmentTest, FailureRevetment_DamageLargerAndInitialDamageSmallerThanFailureNumber_ExpectedTrue)
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

    TEST_F(RevetmentTest, FailureRevetment_DamageAndInitialDamageLargerThanFailureNumber_ExpectedFalse)
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

    TEST_F(RevetmentTest, TimeOfFailure_ValidUnroundedInput_ExpectedValue)
    {
        // Setup
        const auto durationInTimeStepFailure = 254.001;
        const auto beginTime = 1568;

        // Call
        const auto timeOfFailure = Revetment::TimeOfFailure(durationInTimeStepFailure, beginTime);

        // Assert
        ASSERT_EQ(1823, timeOfFailure);
    }

    TEST_F(RevetmentTest, DurationInTimeStepFailure_ValidInput_ExpectedValue)
    {
        // Setup
        const auto incrementTime = 550;
        const auto incrementDamage = 0.234;
        const auto failureNumber = 1.0;
        const auto initialDamage = 0.836;

        // Call
        const auto durationInTimeStepFailure = Revetment::DurationInTimeStepFailure(incrementTime, incrementDamage, failureNumber, initialDamage);

        // Assert
        ASSERT_DOUBLE_EQ(385.47008547008551, durationInTimeStepFailure);
    }

    TEST_F(RevetmentTest, TimeOfFailure_ValidRoundedInput_ExpectedValue)
    {
        // Setup
        const auto durationInTimeStepFailure = 254;
        const auto beginTime = 1568;

        // Call
        const auto timeOfFailure = Revetment::TimeOfFailure(durationInTimeStepFailure, beginTime);

        // Assert
        ASSERT_EQ(1822, timeOfFailure);
    }
}
