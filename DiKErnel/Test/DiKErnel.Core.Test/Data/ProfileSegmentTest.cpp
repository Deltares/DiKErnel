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
        const ProfilePoint lowerPoint(0.0, 1.1);
        const ProfilePoint upperPoint(2.2, 3.3);

        // Call
        const ProfileSegment profileSegment(lowerPoint, upperPoint);

        // Assert
        ASSERT_EQ(&lowerPoint, &profileSegment.GetLowerPoint());
        ASSERT_EQ(&upperPoint, &profileSegment.GetUpperPoint());
    }

    TEST(ProfileSegmentTest, Constructor_With_Roughness_ExpectedValues)
    {
        // Setup
        const ProfilePoint lowerPoint(0.0, 1.1);
        const ProfilePoint upperPoint(2.2, 3.3);
        constexpr double roughness(13.37);

        // Call
        const ProfileSegment profileSegment(lowerPoint, upperPoint, roughness);

        // Assert
        ASSERT_EQ(&lowerPoint, &profileSegment.GetLowerPoint());
        ASSERT_EQ(&upperPoint, &profileSegment.GetUpperPoint());
        ASSERT_DOUBLE_EQ(roughness, profileSegment.GetRoughness());
    }
}
