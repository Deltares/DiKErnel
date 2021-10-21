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

#include "GenericFunctions.h"

namespace DiKErnel::FunctionLibrary::Test
{
    TEST(GenericFunctionsTest, Pi_ExpectedValue)
    {
        // Call
        const auto pi = GenericFunctions::Pi();

        // Assert
        ASSERT_DOUBLE_EQ(3.1415926535897931, pi);
    }

    TEST(GenericFunctionsTest, Radians_ValidInput_ExpectedValue)
    {
        // Setup
        const auto degrees = 123.45;

        // Call
        const auto radians = GenericFunctions::Radians(degrees);

        // Assert
        ASSERT_DOUBLE_EQ(2.1546089615869999, radians);
    }

    TEST(GenericFunctionsTest, Degrees_ValidInput_ExpectedValue)
    {
        // Setup
        const auto radians = 1.2345;

        // Call
        const auto degrees = GenericFunctions::Degrees(radians);

        // Assert
        ASSERT_DOUBLE_EQ(70.731639808900127, degrees);
    }
}
