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

namespace DiKErnel.Integration.Test.Data.Output
{
    TEST(GrassRevetmentWaveImpactTimeDependentOutputConstructionPropertiesTest, Constructor_ExpectedValues)
    {
        // Call
        const GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutputConstructionProperties>(&constructionProperties);
        ASSERT_EQ(nullptr, constructionProperties._incrementDamage);
        ASSERT_EQ(nullptr, constructionProperties._damage);
        ASSERT_EQ(nullptr, constructionProperties._timeOfFailure);
        ASSERT_EQ(nullptr, constructionProperties._loadingRevetment);
        ASSERT_EQ(nullptr, constructionProperties._upperLimitLoading);
        ASSERT_EQ(nullptr, constructionProperties._lowerLimitLoading);
        ASSERT_EQ(nullptr, constructionProperties._minimumWaveHeight);
        ASSERT_EQ(nullptr, constructionProperties._maximumWaveHeight);
        ASSERT_EQ(nullptr, constructionProperties._waveAngleImpact);
        ASSERT_EQ(nullptr, constructionProperties._waveHeightImpact);
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
        GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
        constructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);
        constructionProperties._loadingRevetment = make_unique<bool>(loadingRevetment);
        constructionProperties._upperLimitLoading = make_unique<double>(upperLimitLoading);
        constructionProperties._lowerLimitLoading = make_unique<double>(lowerLimitLoading);
        constructionProperties._minimumWaveHeight = make_unique<double>(minimumWaveHeight);
        constructionProperties._maximumWaveHeight = make_unique<double>(maximumWaveHeight);
        constructionProperties._waveAngleImpact = make_unique<double>(waveAngleImpact);
        constructionProperties._waveHeightImpact = make_unique<double>(waveHeightImpact);

        // Then
        ASSERT_DOUBLE_EQ(incrementDamage, *constructionProperties._incrementDamage);
        ASSERT_DOUBLE_EQ(damage, *constructionProperties._damage);
        ASSERT_EQ(timeOfFailure, *constructionProperties._timeOfFailure);
        ASSERT_EQ(loadingRevetment, *constructionProperties._loadingRevetment);
        ASSERT_DOUBLE_EQ(upperLimitLoading, *constructionProperties._upperLimitLoading);
        ASSERT_DOUBLE_EQ(lowerLimitLoading, *constructionProperties._lowerLimitLoading);
        ASSERT_DOUBLE_EQ(minimumWaveHeight, *constructionProperties._minimumWaveHeight);
        ASSERT_DOUBLE_EQ(maximumWaveHeight, *constructionProperties._maximumWaveHeight);
        ASSERT_DOUBLE_EQ(waveAngleImpact, *constructionProperties._waveAngleImpact);
        ASSERT_DOUBLE_EQ(waveHeightImpact, *constructionProperties._waveHeightImpact);
    }
}
