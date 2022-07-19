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

#include "TimeDependentOutputMock.h"

namespace DiKErnel::Core::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(TimeDependentOutputTest, Constructor_ConstructionPropertiesWithValuesSet_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        auto timeOfFailure = 3;

        TimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
        constructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);

        // Call
        const TimeDependentOutputMock timeDependentOutput(constructionProperties);

        // Assert
        ASSERT_DOUBLE_EQ(incrementDamage, timeDependentOutput.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, timeDependentOutput.GetDamage());
        ASSERT_EQ(timeOfFailure, *timeDependentOutput.GetTimeOfFailure());
    }

    TEST(TimeDependentOutputTest, Constructor_TimeOfFailureNullPtr_ExpectedValues)
    {
        // Setup
        TimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(0.1);
        constructionProperties._damage = make_unique<double>(0.2);
        constructionProperties._timeOfFailure = nullptr;

        // Call
        const TimeDependentOutputMock timeDependentOutput(constructionProperties);

        // Assert
        ASSERT_EQ(nullptr, timeDependentOutput.GetTimeOfFailure());
    }
}
