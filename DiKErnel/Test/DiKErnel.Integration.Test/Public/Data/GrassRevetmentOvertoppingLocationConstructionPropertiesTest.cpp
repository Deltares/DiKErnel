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
#include "GrassRevetmentOvertoppingLocationConstructionProperties.h"

namespace DiKErnel::Integration::Test
{
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    TEST(GrassRevetmentOvertoppingLocationConstructionPropertiesTest, Constructor_ExpectedValues)
    {
        // Setup
        const auto topLayerType = static_cast<GrassRevetmentTopLayerType>(rand() % 2);
        constexpr auto x = 0.1;

        // Call
        const GrassRevetmentOvertoppingLocationConstructionProperties constructionProperties(x, topLayerType);

        // Assert
        AssertHelper::AssertIsInstanceOf<RevetmentLocationConstructionPropertiesBase>(&constructionProperties);
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_EQ(nullptr, constructionProperties.GetInitialDamage());
        ASSERT_EQ(nullptr, constructionProperties.GetFailureNumber());
        ASSERT_EQ(nullptr, constructionProperties.GetCriticalCumulativeOverload());
        ASSERT_EQ(nullptr, constructionProperties.GetCriticalFrontVelocity());
        ASSERT_EQ(nullptr, constructionProperties.GetIncreasedLoadTransitionAlphaM());
        ASSERT_EQ(nullptr, constructionProperties.GetReducedStrengthTransitionAlphaS());
        ASSERT_EQ(nullptr, constructionProperties.GetAverageNumberOfWavesCtm());
        ASSERT_EQ(nullptr, constructionProperties.GetFixedNumberOfWaves());
        ASSERT_EQ(nullptr, constructionProperties.GetFrontVelocityCwo());
        ASSERT_EQ(nullptr, constructionProperties.GetAccelerationAlphaAForCrest());
        ASSERT_EQ(nullptr, constructionProperties.GetAccelerationAlphaAForInnerSlope());
        ASSERT_EQ(nullptr, constructionProperties.GetDikeHeight());
    }

    TEST(GrassRevetmentOvertoppingLocationConstructionPropertiesTest, GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues)
    {
        // Given
        const auto topLayerType = static_cast<GrassRevetmentTopLayerType>(rand() % 2);
        constexpr auto x = 0.1;
        constexpr auto initialDamage = 0.2;
        constexpr auto failureNumber = 0.3;
        constexpr auto criticalCumulativeOverload = 0.4;
        constexpr auto criticalFrontVelocity = 0.5;
        constexpr auto increasedLoadTransitionAlphaM = 0.6;
        constexpr auto reducedStrengthTransitionAlphaS = 0.7;
        constexpr auto averageNumberOfWavesCtm = 0.8;
        constexpr auto fixedNumberOfWaves = 9;
        constexpr auto frontVelocityCwo = 1.0;
        constexpr auto accelerationAlphaAForCrest = 1.1;
        constexpr auto accelerationAlphaAForInnerSlope = 1.2;
        constexpr auto dikeHeight = 1.3;

        GrassRevetmentOvertoppingLocationConstructionProperties constructionProperties(x, topLayerType);

        // When
        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties.SetCriticalCumulativeOverload(make_unique<double>(criticalCumulativeOverload));
        constructionProperties.SetCriticalFrontVelocity(make_unique<double>(criticalFrontVelocity));
        constructionProperties.SetIncreasedLoadTransitionAlphaM(make_unique<double>(increasedLoadTransitionAlphaM));
        constructionProperties.SetReducedStrengthTransitionAlphaS(make_unique<double>(reducedStrengthTransitionAlphaS));
        constructionProperties.SetAverageNumberOfWavesCtm(make_unique<double>(averageNumberOfWavesCtm));
        constructionProperties.SetFixedNumberOfWaves(make_unique<int>(fixedNumberOfWaves));
        constructionProperties.SetFrontVelocityCwo(make_unique<double>(frontVelocityCwo));
        constructionProperties.SetAccelerationAlphaAForCrest(make_unique<double>(accelerationAlphaAForCrest));
        constructionProperties.SetAccelerationAlphaAForInnerSlope(make_unique<double>(accelerationAlphaAForInnerSlope));
        constructionProperties.SetDikeHeight(make_unique<double>(dikeHeight));

        // Then
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_DOUBLE_EQ(initialDamage, *constructionProperties.GetInitialDamage());
        ASSERT_DOUBLE_EQ(failureNumber, *constructionProperties.GetFailureNumber());
        ASSERT_DOUBLE_EQ(criticalCumulativeOverload, *constructionProperties.GetCriticalCumulativeOverload());
        ASSERT_DOUBLE_EQ(criticalFrontVelocity, *constructionProperties.GetCriticalFrontVelocity());
        ASSERT_DOUBLE_EQ(increasedLoadTransitionAlphaM, *constructionProperties.GetIncreasedLoadTransitionAlphaM());
        ASSERT_DOUBLE_EQ(reducedStrengthTransitionAlphaS, *constructionProperties.GetReducedStrengthTransitionAlphaS());
        ASSERT_DOUBLE_EQ(averageNumberOfWavesCtm, *constructionProperties.GetAverageNumberOfWavesCtm());
        ASSERT_DOUBLE_EQ(fixedNumberOfWaves, *constructionProperties.GetFixedNumberOfWaves());
        ASSERT_DOUBLE_EQ(frontVelocityCwo, *constructionProperties.GetFrontVelocityCwo());
        ASSERT_DOUBLE_EQ(accelerationAlphaAForCrest, *constructionProperties.GetAccelerationAlphaAForCrest());
        ASSERT_DOUBLE_EQ(accelerationAlphaAForInnerSlope, *constructionProperties.GetAccelerationAlphaAForInnerSlope());
        ASSERT_DOUBLE_EQ(dikeHeight, *constructionProperties.GetDikeHeight());
    }
}
