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
#include "GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties.h"

namespace DiKErnel::Integration::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(GrassRevetmentWaveImpactTimeDependentOutputConstructionPropertiesTest, Constructor_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto timeOfFailure = 3;

        // Call
        const GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties(
            incrementDamage, damage, make_unique<int>(timeOfFailure));

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutputConstructionProperties>(&constructionProperties);
        ASSERT_DOUBLE_EQ(incrementDamage, constructionProperties.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, constructionProperties.GetDamage());
        ASSERT_EQ(timeOfFailure, *constructionProperties.GetTimeOfFailure());
        ASSERT_FALSE(constructionProperties.GetLoadingRevetment());
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), constructionProperties.GetUpperLimitLoading());
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), constructionProperties.GetLowerLimitLoading());
        ASSERT_EQ(nullptr, constructionProperties.GetMinimumWaveHeight());
        ASSERT_EQ(nullptr, constructionProperties.GetMaximumWaveHeight());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveAngleImpact());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveHeightImpact());
    }

    TEST(GrassRevetmentWaveImpactTimeDependentOutputConstructionPropertiesTest, GivenConstructionProperties_WhenAllValuesSet_ThenExpectedValues)
    {
        // Given
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto timeOfFailure = 3;
        constexpr auto loadingRevetment = true;
        constexpr auto upperLimitLoading = 0.4;
        constexpr auto lowerLimitLoading = 0.5;
        constexpr auto minimumWaveHeight = 0.6;
        constexpr auto maximumWaveHeight = 0.7;
        constexpr auto waveAngleImpact = 0.8;
        constexpr auto waveHeightImpact = 0.9;

        // When
        GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties(
            incrementDamage, damage, make_unique<int>(timeOfFailure));
        constructionProperties.SetLoadingRevetment(loadingRevetment);
        constructionProperties.SetUpperLimitLoading(upperLimitLoading);
        constructionProperties.SetLowerLimitLoading(lowerLimitLoading);
        constructionProperties.SetMinimumWaveHeight(make_unique<double>(minimumWaveHeight));
        constructionProperties.SetMaximumWaveHeight(make_unique<double>(maximumWaveHeight));
        constructionProperties.SetWaveAngleImpact(make_unique<double>(waveAngleImpact));
        constructionProperties.SetWaveHeightImpact(make_unique<double>(waveHeightImpact));

        // Then
        ASSERT_DOUBLE_EQ(incrementDamage, constructionProperties.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, constructionProperties.GetDamage());
        ASSERT_EQ(timeOfFailure, *constructionProperties.GetTimeOfFailure());
        ASSERT_EQ(loadingRevetment, constructionProperties.GetLoadingRevetment());
        ASSERT_DOUBLE_EQ(upperLimitLoading, constructionProperties.GetUpperLimitLoading());
        ASSERT_DOUBLE_EQ(lowerLimitLoading, constructionProperties.GetLowerLimitLoading());
        ASSERT_DOUBLE_EQ(minimumWaveHeight, *constructionProperties.GetMinimumWaveHeight());
        ASSERT_DOUBLE_EQ(maximumWaveHeight, *constructionProperties.GetMaximumWaveHeight());
        ASSERT_DOUBLE_EQ(waveAngleImpact, *constructionProperties.GetWaveAngleImpact());
        ASSERT_DOUBLE_EQ(waveHeightImpact, *constructionProperties.GetWaveHeightImpact());
    }

    TEST(GrassRevetmentWaveImpactTimeDependentOutputTest, GivenConstructionProperties_WhenValuesSetWithNullPtrValues_ThenExpectedValues)
    {
        // Given
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto loadingRevetment = false;
        constexpr auto upperLimitLoading = 0.3;
        constexpr auto lowerLimitLoading = 0.4;

        // When
        GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties(incrementDamage, damage, nullptr);
        constructionProperties.SetLoadingRevetment(loadingRevetment);
        constructionProperties.SetUpperLimitLoading(upperLimitLoading);
        constructionProperties.SetLowerLimitLoading(lowerLimitLoading);
        constructionProperties.SetMinimumWaveHeight(nullptr);
        constructionProperties.SetMaximumWaveHeight(nullptr);
        constructionProperties.SetWaveAngleImpact(nullptr);
        constructionProperties.SetWaveHeightImpact(nullptr);

        // Then
        ASSERT_DOUBLE_EQ(incrementDamage, constructionProperties.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, constructionProperties.GetDamage());
        ASSERT_EQ(nullptr, constructionProperties.GetTimeOfFailure());
        ASSERT_EQ(loadingRevetment, constructionProperties.GetLoadingRevetment());
        ASSERT_DOUBLE_EQ(upperLimitLoading, constructionProperties.GetUpperLimitLoading());
        ASSERT_DOUBLE_EQ(lowerLimitLoading, constructionProperties.GetLowerLimitLoading());
        ASSERT_EQ(nullptr, constructionProperties.GetMinimumWaveHeight());
        ASSERT_EQ(nullptr, constructionProperties.GetMaximumWaveHeight());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveAngleImpact());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveHeightImpact());
    }
}
