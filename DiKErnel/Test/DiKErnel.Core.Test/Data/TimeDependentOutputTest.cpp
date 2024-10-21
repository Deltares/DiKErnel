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
#include "InvalidTimeDependentOutputException.h"
#include "TimeDependentOutputMock.h"

namespace DiKErnel::Core::Test
{
    using namespace DiKErnel::TestUtil;
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct TimeDependentOutputTest : Test
    {
        static void CreateOutputWithConstructionPropertiesWithIncrementDamageNullPtr()
        {
            // Setup
            TimeDependentOutputConstructionProperties constructionProperties;
            constructionProperties._incrementDamage = nullptr;

            // Call
            const TimeDependentOutputMock timeDependentOutput(constructionProperties);
        }
    };

    TEST_F(TimeDependentOutputTest, Constructor_ConstructionPropertiesWithValuesSet_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;

        TimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);

        // Call
        const TimeDependentOutputMock timeDependentOutput(constructionProperties);

        // Assert
        ASSERT_DOUBLE_EQ(incrementDamage, timeDependentOutput.GetIncrementDamage());
    }

    TEST_F(TimeDependentOutputTest, Constructor_IncrementDamageNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &TimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithIncrementDamageNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "incrementDamage must be set.");
    }
}
