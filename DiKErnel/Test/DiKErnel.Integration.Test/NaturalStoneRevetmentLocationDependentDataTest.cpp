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

#include "AssertHelper.h"
#include "NaturalStoneRevetmentLocationDependentData.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace TestUtil;

    TEST(NaturalStoneRevetmentLocationDependentDataTest, Constructor_ExpectedValues)
    {
        // Setup
        const auto initialDamage = rand() & 5;

        // Call
        const NaturalStoneRevetmentLocationDependentData locationDependentData(initialDamage, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        // Assert
        AssertHelper::AssertIsInstanceOf<LocationDependentData>(&locationDependentData);
        ASSERT_DOUBLE_EQ(initialDamage, locationDependentData.GetInitialDamage());
    }

    TEST(NaturalStoneRevetmentLocationDependentDataTest, Calculate_Always_PerformsCalculation)
    {
        // Setup
        NaturalStoneRevetmentLocationDependentData locationDependentData(0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3);
        const TimeDependentData timeDependentData(0, 10, 1.4, 1.5, 1.6, 1.7);

        // Call
        const auto damage = locationDependentData.Calculate(0.1, timeDependentData, 1.8);

        // Assert
        ASSERT_DOUBLE_EQ(6.838261669531513, damage);
    }
}
