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

#include "LocationOutput.h"

namespace DiKErnel::Core::Test
{
    TEST(LocationOutputTest, Constructor_ExpectedValues)
    {
        // Call
        const LocationOutput locationOutput;

        // Assert
        ASSERT_EQ(0, locationOutput.GetDamages().size());
        ASSERT_EQ(nullptr, locationOutput.GetTimeOfFailure());
    }

    TEST(LocationOutputTest, AddDamage_Always_AddsDamageToTotal)
    {
        // Setup
        LocationOutput locationOutput;

        // Call
        const auto damageToAdd = rand() % 100;
        locationOutput.AddDamage(damageToAdd);

        // Assert
        ASSERT_EQ(1, locationOutput.GetDamages().size());
        ASSERT_DOUBLE_EQ(damageToAdd, locationOutput.GetDamages()[0]);
    }

    TEST(LocationOutputTest, GivenLocationOutputWithTimeOfFailureSet_WhenGetTimeOfFailure_ThenReturnsValue)
    {
        // Given
        const auto timeOfFailure = rand() % 100;

        LocationOutput locationOutput;
        locationOutput.SetTimeOfFailure(timeOfFailure);

        // When
        auto* actualTimeOfFailure = locationOutput.GetTimeOfFailure();

        // Assert
        ASSERT_DOUBLE_EQ(timeOfFailure, *actualTimeOfFailure);
    }
}
