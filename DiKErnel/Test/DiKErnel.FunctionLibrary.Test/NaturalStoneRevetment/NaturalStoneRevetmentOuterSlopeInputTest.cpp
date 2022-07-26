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

#include "NaturalStoneRevetmentOuterSlopeInput.h"

namespace DiKErnel::FunctionLibrary::Test
{
    using namespace std;

    TEST(NaturalStoneRevetmentOuterSlopeInputTest, GivenInput_WhenCreated_ThenExpectedValues)
    {
        // Given & When
        constexpr NaturalStoneRevetmentOuterSlopeInput input{};

        // Then
        ASSERT_DOUBLE_EQ(0.0, input._slopeLowerPosition);
        ASSERT_DOUBLE_EQ(0.0, input._slopeLowerLevel);
        ASSERT_DOUBLE_EQ(0.0, input._slopeUpperPosition);
        ASSERT_DOUBLE_EQ(0.0, input._slopeUpperLevel);
        ASSERT_DOUBLE_EQ(0.0, input._outerToeHeight);
        ASSERT_DOUBLE_EQ(0.0, input._outerCrestHeight);
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), input._notchOuterBermPosition);
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), input._notchOuterBermHeight);
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), input._crestOuterBermPosition);
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), input._crestOuterBermHeight);
        ASSERT_FALSE(input.HasBerm());
    }

    TEST(NaturalStoneRevetmentOuterSlopeInputTest, HasBerm_NotchOuterBermPositionInfinite_ReturnsFalse)
    {
        // Setup
        constexpr NaturalStoneRevetmentOuterSlopeInput input
        {
            ._notchOuterBermHeight = 0.1,
            ._crestOuterBermPosition = 0.2,
            ._crestOuterBermHeight = 0.3
        };

        // Call
        const auto hasBerm = input.HasBerm();

        // Assert
        ASSERT_FALSE(hasBerm);
    }

    TEST(NaturalStoneRevetmentOuterSlopeInputTest, HasBerm_NotchOuterBermHeightInfinite_ReturnsFalse)
    {
        // Setup
        constexpr NaturalStoneRevetmentOuterSlopeInput input
        {
            ._notchOuterBermPosition = 0.1,
            ._crestOuterBermPosition = 0.2,
            ._crestOuterBermHeight = 0.3
        };

        // Call
        const auto hasBerm = input.HasBerm();

        // Assert
        ASSERT_FALSE(hasBerm);
    }

    TEST(NaturalStoneRevetmentOuterSlopeInputTest, HasBerm_CrestOuterBermPositionInfinite_ReturnsFalse)
    {
        // Setup
        constexpr NaturalStoneRevetmentOuterSlopeInput input
        {
            ._notchOuterBermPosition = 0.1,
            ._notchOuterBermHeight = 0.2,
            ._crestOuterBermHeight = 0.3
        };

        // Call
        const auto hasBerm = input.HasBerm();

        // Assert
        ASSERT_FALSE(hasBerm);
    }

    TEST(NaturalStoneRevetmentOuterSlopeInputTest, HasBerm_CrestOuterBermHeightInfinite_ReturnsFalse)
    {
        // Setup
        constexpr NaturalStoneRevetmentOuterSlopeInput input
        {
            ._notchOuterBermPosition = 0.1,
            ._notchOuterBermHeight = 0.2,
            ._crestOuterBermPosition = 0.3
        };

        // Call
        const auto hasBerm = input.HasBerm();

        // Assert
        ASSERT_FALSE(hasBerm);
    }

    TEST(NaturalStoneRevetmentOuterSlopeInputTest, HasBerm_AllBermPropertiesNotInfinite_ReturnsTrue)
    {
        // Setup
        constexpr NaturalStoneRevetmentOuterSlopeInput input
        {
            ._notchOuterBermPosition = 0.1,
            ._notchOuterBermHeight = 0.2,
            ._crestOuterBermPosition = 0.3,
            ._crestOuterBermHeight = 0.4
        };

        // Call
        const auto hasBerm = input.HasBerm();

        // Assert
        ASSERT_TRUE(hasBerm);
    }
}
