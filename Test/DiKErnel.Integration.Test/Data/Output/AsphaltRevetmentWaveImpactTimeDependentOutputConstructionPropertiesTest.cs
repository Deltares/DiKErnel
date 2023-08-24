// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.Output
{
    [TestFixture]
    public class AsphaltRevetmentWaveImpactTimeDependentOutputConstructionPropertiesTest
    {
        
    }

    TEST(AsphaltRevetmentWaveImpactTimeDependentOutputConstructionPropertiesTest, Constructor_ExpectedValues)
    {
        // Call
        const AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutputConstructionProperties>(&constructionProperties);
        ASSERT_EQ(nullptr, constructionProperties._incrementDamage);
        ASSERT_EQ(nullptr, constructionProperties._damage);
        ASSERT_EQ(nullptr, constructionProperties._timeOfFailure);
        ASSERT_EQ(nullptr, constructionProperties._logFailureTension);
        ASSERT_EQ(nullptr, constructionProperties._maximumPeakStress);
        ASSERT_EQ(nullptr, constructionProperties._stiffnessRelation);
        ASSERT_EQ(nullptr, constructionProperties._computationalThickness);
        ASSERT_EQ(nullptr, constructionProperties._equivalentElasticModulus);
    }

    TEST(AsphaltRevetmentWaveImpactTimeDependentOutputConstructionPropertiesTest, GivenConstructionProperties_WhenAllValuesSet_ThenExpectedValues)
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
        AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
        constructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);
        constructionProperties._logFailureTension = make_unique<double>(logFailureTension);
        constructionProperties._maximumPeakStress = make_unique<double>(maximumPeakStress);
        constructionProperties._stiffnessRelation = make_unique<double>(stiffnessRelation);
        constructionProperties._computationalThickness = make_unique<double>(computationalThickness);
        constructionProperties._equivalentElasticModulus = make_unique<double>(equivalentElasticModulus);

        // Then
        AssertHelper::AssertIsInstanceOf<TimeDependentOutputConstructionProperties>(&constructionProperties);
        ASSERT_DOUBLE_EQ(incrementDamage, *constructionProperties._incrementDamage);
        ASSERT_DOUBLE_EQ(damage, *constructionProperties._damage);
        ASSERT_EQ(timeOfFailure, *constructionProperties._timeOfFailure);
        ASSERT_DOUBLE_EQ(logFailureTension, *constructionProperties._logFailureTension);
        ASSERT_DOUBLE_EQ(maximumPeakStress, *constructionProperties._maximumPeakStress);
        ASSERT_DOUBLE_EQ(stiffnessRelation, *constructionProperties._stiffnessRelation);
        ASSERT_DOUBLE_EQ(computationalThickness, *constructionProperties._computationalThickness);
        ASSERT_DOUBLE_EQ(equivalentElasticModulus, *constructionProperties._equivalentElasticModulus);
    }
}
