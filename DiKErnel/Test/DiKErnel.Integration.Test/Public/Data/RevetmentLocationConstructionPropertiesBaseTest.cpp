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

#include "RevetmentLocationConstructionPropertiesBase.h"
#include "RevetmentLocationConstructionPropertiesMock.h"

namespace DiKErnel::Integration::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(RevetmentLocationConstructionPropertiesBaseTest, Constructor_ExpectedValues)
    {
        // Setup
        constexpr auto x = 0.1;

        // Call
        const RevetmentLocationConstructionPropertiesMock constructionProperties(x);

        // Assert
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_EQ(nullptr, constructionProperties.GetInitialDamage());
        ASSERT_EQ(nullptr, constructionProperties.GetFailureNumber());
    }

    TEST(RevetmentLocationConstructionPropertiesBaseTest, GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues)
    {
        // Given
        constexpr auto x = 0.1;
        constexpr auto initialDamage = 0.2;
        constexpr auto failureNumber = 0.3;

        RevetmentLocationConstructionPropertiesMock constructionProperties(x);

        // When
        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));

        // Then
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_DOUBLE_EQ(initialDamage, *constructionProperties.GetInitialDamage());
        ASSERT_DOUBLE_EQ(failureNumber, *constructionProperties.GetFailureNumber());
    }
}
