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

#include "AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties.h"
#include "AssertHelper.h"

namespace DiKErnel::Integration::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(AsphaltRevetmentWaveImpactTimeDependentOutputConstructionPropertiesTest, Constructor_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto timeOfFailure = 3;

        // Call
        AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties(
            incrementDamage, damage, make_unique<int>(timeOfFailure));

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutputConstructionProperties>(&constructionProperties);
        ASSERT_DOUBLE_EQ(incrementDamage, constructionProperties.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, constructionProperties.GetDamage());
        ASSERT_EQ(timeOfFailure, *constructionProperties.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), constructionProperties.GetLogFailureTension());
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), constructionProperties.GetMaximumPeakStress());
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), constructionProperties.GetStiffnessRelation());
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), constructionProperties.GetComputationalThickness());
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), constructionProperties.GetEquivalentElasticModulus());
    }

    TEST(AsphaltRevetmentWaveImpactTimeDependentOutputConstructionPropertiesTest, GivenConstructionProperties_WhenAllOutputSet_ThenExpectedValues)
    {
        // Given
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto timeOfFailure = 3;
        constexpr auto logFailureTension = 0.4;
        constexpr auto maximumPeakStress = 0.5;
        constexpr auto stiffnessRelation = 0.6;
        constexpr auto computationalThickness = 0.7;
        constexpr auto equivalentElasticModulus = 0.8;

        // When
        AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties(
            incrementDamage, damage, make_unique<int>(timeOfFailure));
        constructionProperties.SetLogFailureTension(logFailureTension);
        constructionProperties.SetMaximumPeakStress(maximumPeakStress);
        constructionProperties.SetStiffnessRelation(stiffnessRelation);
        constructionProperties.SetComputationalThickness(computationalThickness);
        constructionProperties.SetEquivalentElasticModulus(equivalentElasticModulus);

        // Then
        AssertHelper::AssertIsInstanceOf<TimeDependentOutputConstructionProperties>(&constructionProperties);
        ASSERT_DOUBLE_EQ(incrementDamage, constructionProperties.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, constructionProperties.GetDamage());
        ASSERT_EQ(timeOfFailure, *constructionProperties.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(logFailureTension, constructionProperties.GetLogFailureTension());
        ASSERT_DOUBLE_EQ(maximumPeakStress, constructionProperties.GetMaximumPeakStress());
        ASSERT_DOUBLE_EQ(stiffnessRelation, constructionProperties.GetStiffnessRelation());
        ASSERT_DOUBLE_EQ(computationalThickness, constructionProperties.GetComputationalThickness());
        ASSERT_DOUBLE_EQ(equivalentElasticModulus, constructionProperties.GetEquivalentElasticModulus());
    }
}
