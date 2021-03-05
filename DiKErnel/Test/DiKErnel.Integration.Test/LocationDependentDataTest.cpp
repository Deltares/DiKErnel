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
#include "LocationDependentDataMock.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace DiKErnel::TestUtil;
    using namespace TestUtil;

    TEST(LocationDependentDataTest, Constructor_WithParameters_ExpectedValues)
    {
        // Setup
        const auto initialDamage = rand() % 10;

        // Call
        const LocationDependentDataMock locationDependentData(initialDamage);

        // Assert
        AssertHelper::AssertIsInstanceOf<ILocationDependentData>(&locationDependentData);
        ASSERT_DOUBLE_EQ(initialDamage, locationDependentData.GetInitialDamage());
    }
}
