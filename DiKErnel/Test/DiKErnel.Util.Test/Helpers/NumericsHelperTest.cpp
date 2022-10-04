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

#include "NumericsHelper.h"

namespace DiKErnel::Util::Test
{
    using namespace std;

    TEST(NumericsHelperTest, AreEqual_EqualValue_ReturnsTrue)
    {
        // Call
        const auto areEqual = NumericsHelper::AreEqual(0.1, 0.1);

        // Assert
        ASSERT_TRUE(areEqual);
    }

    TEST(NumericsHelperTest, AreEqual_SecondValueDiffersWithEpsilon_ReturnsTrue)
    {
        // Call
        const auto areEqual = NumericsHelper::AreEqual(0.1, 0.1 + numeric_limits<double>::epsilon());

        // Assert
        ASSERT_TRUE(areEqual);
    }

    TEST(NumericsHelperTest, AreEqual_FirstValueDiffersWithEpsilon_ReturnsTrue)
    {
        // Call
        const auto areEqual = NumericsHelper::AreEqual(0.1 + numeric_limits<double>::epsilon(), 0.1);

        // Assert
        ASSERT_TRUE(areEqual);
    }

    TEST(NumericsHelperTest, AreEqual_SecondValueDiffersWithTwoTimesEpsilon_ReturnsFalse)
    {
        // Call
        const auto areEqual = NumericsHelper::AreEqual(0.1, 0.1 + numeric_limits<double>::epsilon() * 2);

        // Assert
        ASSERT_FALSE(areEqual);
    }

    TEST(NumericsHelperTest, AreEqual_FirstValueDiffersWithTwoTimesEpsilon_ReturnsFalse)
    {
        // Call
        const auto areEqual = NumericsHelper::AreEqual(0.1 + numeric_limits<double>::epsilon() * 2, 0.1);

        // Assert
        ASSERT_FALSE(areEqual);
    }

    TEST(NumericsHelperTest, AreEqual_SecondValueLargerThanFirstValue_ReturnsFalse)
    {
        // Call
        const auto areEqual = NumericsHelper::AreEqual(0.1, 0.11);

        // Assert
        ASSERT_FALSE(areEqual);
    }

    TEST(NumericsHelperTest, AreEqual_SecondValueSmallerThanFirstValue_ReturnsFalse)
    {
        // Call
        const auto areEqual = NumericsHelper::AreEqual(0.11, 0.1);

        // Assert
        ASSERT_FALSE(areEqual);
    }

    TEST(NumericsHelperTest, ToString_Always_ReturnsExpectedValue)
    {
        // Call
        const auto string1 = NumericsHelper::ToString(0.3);
        const auto string2 = NumericsHelper::ToString(1e-6);
        const auto string3 = NumericsHelper::ToString(0.001);
        const auto string4 = NumericsHelper::ToString(1);

        // Assert
        ASSERT_EQ("0.3", string1);
        ASSERT_EQ("1e-06", string2);
        ASSERT_EQ("0.001", string3);
        ASSERT_EQ("1", string4);
    }
}
