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

#include "TimeDependentOutput.h"

namespace DiKErnel::Core::Test
{
    using namespace std;

    TEST(TimeDependentOutputTest, Constructor_WithParameters_ExpectedValues)
    {
        // Setup
        const double damage = rand() % 10;
        double timeOfFailure = rand() % 20;

        // Call
        const TimeDependentOutput timeDependentOutput(damage, make_unique<int>(timeOfFailure));

        // Assert
        ASSERT_DOUBLE_EQ(damage, timeDependentOutput.GetDamage());
        ASSERT_EQ(timeOfFailure, *timeDependentOutput.GetTimeOfFailure());
    }

    TEST(TimeDependentOutputTest, Constructor_TimeOfFailureNullPtr_ExpectedValues)
    {
        // Call
        const TimeDependentOutput timeDependentOutput(0, nullptr);

        // Assert
        ASSERT_EQ(nullptr, timeDependentOutput.GetTimeOfFailure());
    }
}
