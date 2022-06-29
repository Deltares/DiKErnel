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

#include "AsphaltRevetmentWaveImpactLocationDependentOutput.h"
#include "AssertHelper.h"
#include "LocationDependentOutput.h"
#include "TimeDependentOutputMock.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace Core::TestUtil;
    using namespace DiKErnel::TestUtil;
    using namespace std;

    TEST(AsphaltRevetmentWaveImpactLocationDependentOutputTest, Constructor_ExpectedValues)
    {
        // Setup
        constexpr auto z = 0.1;
        constexpr auto incrementDamage = 0.2;
        constexpr auto damage = 0.3;
        constexpr auto timeOfFailure = 4;
        constexpr auto outerSlope = 0.5;

        auto timeDependentOutputItems = vector<unique_ptr<TimeDependentOutput>>();
        timeDependentOutputItems.push_back(make_unique<TimeDependentOutputMock>(incrementDamage, damage, make_unique<int>(timeOfFailure)));

        // Call
        const AsphaltRevetmentWaveImpactLocationDependentOutput output(z, move(timeDependentOutputItems), outerSlope);

        // Assert
        AssertHelper::AssertIsInstanceOf<LocationDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(z, output.GetZ());
        ASSERT_EQ(vector{ damage }, output.GetDamages());
        ASSERT_EQ(timeOfFailure, *output.GetTimeOfFailure());
        ASSERT_EQ(1, output.GetTimeDependentOutputItems().size());
        ASSERT_DOUBLE_EQ(outerSlope, output.GetOuterSlope());
    }
}