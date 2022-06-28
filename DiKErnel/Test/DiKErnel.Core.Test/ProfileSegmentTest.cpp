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

#include "ProfileSegment.h"

namespace DiKErnel::Core::Test
{
    TEST(ProfileSegmentTest, Constructor_ExpectedValues)
    {
        // Setup
        constexpr auto x1 = 0.0;
        constexpr auto z1 = 1.1;
        constexpr auto x2 = 2.2;
        constexpr auto z2 = 3.3;
        const ProfilePoint upperPoint(x1, z1);
        const ProfilePoint lowerPoint(x2, z2);

        // Call
        const ProfileSegment profileSegment(upperPoint, lowerPoint);

        // Assert
        ASSERT_EQ(&upperPoint, &profileSegment.GetUpperPoint());
        ASSERT_EQ(&lowerPoint, &profileSegment.GetLowerPoint());
    }
}
