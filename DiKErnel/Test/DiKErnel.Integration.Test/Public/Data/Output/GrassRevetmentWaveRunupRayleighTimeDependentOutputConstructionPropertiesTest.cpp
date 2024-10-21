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

#include "AssertHelper.h"
#include "GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace std;
    using namespace TestUtil;

    TEST(GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionPropertiesTest, Constructor_ExpectedValues)
    {
        // Call
        const GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties constructionProperties;

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutputConstructionProperties>(&constructionProperties);
        ASSERT_EQ(nullptr, constructionProperties._incrementDamage);
        ASSERT_EQ(nullptr, constructionProperties._timeOfFailure);
        ASSERT_EQ(nullptr, constructionProperties._verticalDistanceWaterLevelElevation);
        ASSERT_EQ(nullptr, constructionProperties._waveAngleImpact);
        ASSERT_EQ(nullptr, constructionProperties._representativeWaveRunup2P);
        ASSERT_EQ(nullptr, constructionProperties._cumulativeOverload);
    }

    TEST(GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionPropertiesTest,
         GivenConstructionProperties_WhenAllValuesSet_ThenExpectedValues)
    {
        // Given
        constexpr auto incrementDamage = 0.1;
        constexpr auto timeOfFailure = 3;
        constexpr auto verticalDistanceWaterLevelElevation = 0.4;
        constexpr auto waveAngleImpact = 0.5;
        constexpr auto representativeWaveRunup2P = 0.6;
        constexpr auto cumulativeOverload = 0.7;

        // When
        GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);
        constructionProperties._verticalDistanceWaterLevelElevation = make_unique<double>(verticalDistanceWaterLevelElevation);
        constructionProperties._waveAngleImpact = make_unique<double>(waveAngleImpact);
        constructionProperties._representativeWaveRunup2P = make_unique<double>(representativeWaveRunup2P);
        constructionProperties._cumulativeOverload = make_unique<double>(cumulativeOverload);

        // Then
        ASSERT_DOUBLE_EQ(incrementDamage, *constructionProperties._incrementDamage);
        ASSERT_EQ(timeOfFailure, *constructionProperties._timeOfFailure);
        ASSERT_DOUBLE_EQ(verticalDistanceWaterLevelElevation, *constructionProperties._verticalDistanceWaterLevelElevation);
        ASSERT_DOUBLE_EQ(waveAngleImpact, *constructionProperties._waveAngleImpact);
        ASSERT_DOUBLE_EQ(representativeWaveRunup2P, *constructionProperties._representativeWaveRunup2P);
        ASSERT_DOUBLE_EQ(cumulativeOverload, *constructionProperties._cumulativeOverload);
    }
}
