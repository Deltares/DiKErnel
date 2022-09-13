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

#include "LocationDependentOutput.h"
#include "LocationDependentOutputMock.h"
#include "TimeDependentOutputMock.h"

namespace DiKErnel::Core::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(LocationDependentOutputTest, Constructor_WithTimeDependentOutputItems_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto timeOfFailure = 3;

        auto timeDependentOutputItems = vector<unique_ptr<TimeDependentOutput>>();

        TimeDependentOutputConstructionProperties timeDependentOutputConstructionProperties;
        timeDependentOutputConstructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        timeDependentOutputConstructionProperties._damage = make_unique<double>(damage);
        timeDependentOutputConstructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);

        timeDependentOutputItems.push_back(make_unique<TimeDependentOutputMock>(timeDependentOutputConstructionProperties));

        // Call
        const LocationDependentOutputMock locationDependentOutput(move(timeDependentOutputItems));

        // Assert
        ASSERT_EQ(vector{ damage }, locationDependentOutput.GetDamages());
        ASSERT_EQ(timeOfFailure, *locationDependentOutput.GetTimeOfFailure());
        ASSERT_EQ(1, locationDependentOutput.GetTimeDependentOutputItems().size());
    }

    TEST(LocationDependentOutputTest, Constructor_WithTimeDependentOutputItemsWithOnlyTimeOfFailureNullPtr_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;

        auto timeDependentOutputItems = vector<unique_ptr<TimeDependentOutput>>();

        TimeDependentOutputConstructionProperties timeDependentOutputConstructionProperties;
        timeDependentOutputConstructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        timeDependentOutputConstructionProperties._damage = make_unique<double>(damage);
        timeDependentOutputConstructionProperties._timeOfFailure = nullptr;

        timeDependentOutputItems.push_back(make_unique<TimeDependentOutputMock>(timeDependentOutputConstructionProperties));

        // Call
        const LocationDependentOutputMock locationDependentOutput(move(timeDependentOutputItems));

        // Assert
        ASSERT_EQ(vector{ damage }, locationDependentOutput.GetDamages());
        ASSERT_EQ(nullptr, locationDependentOutput.GetTimeOfFailure());
        ASSERT_EQ(1, locationDependentOutput.GetTimeDependentOutputItems().size());
    }
}
