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

#include "LocationDependentOutput.h"

namespace DiKErnel::Core::Test
{
    using namespace std;

    TEST(LocationDependentOutputTest, Constructor_WithParameters_ExpectedValues)
    {
        // Setup
        auto damages = vector<double>();
        damages.push_back(rand() % 10);

        double timeOfFailure = rand() % 20;

        // Call
        const LocationDependentOutput locationDependentOutput(move(damages), make_unique<int>(timeOfFailure));

        // Assert
        ASSERT_EQ(1, locationDependentOutput.GetDamages().size());
        ASSERT_EQ(timeOfFailure, *locationDependentOutput.GetTimeOfFailure());
    }

    TEST(LocationDependentOutputTest, Constructor_TimeOfFailureNullPtr_ExpectedValues)
    {
        // Call
        const LocationDependentOutput locationDependentOutput((vector<double>()), nullptr);

        // Assert
        ASSERT_EQ(nullptr, locationDependentOutput.GetTimeOfFailure());
    }
}
