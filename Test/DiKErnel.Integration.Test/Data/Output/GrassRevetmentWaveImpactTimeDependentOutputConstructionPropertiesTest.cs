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
    public class GrassRevetmentWaveImpactTimeDependentOutputConstructionPropertiesTest
    {
        

        [Test]
    public void Constructor_ExpectedValues()
    {
        // Call
        const GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;

        // Assert
        Assert.IsInstanceOf<TimeDependentOutputConstructionProperties>(&constructionProperties);
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

        [Test]
    public void GivenConstructionProperties_WhenAllValuesSet_ThenExpectedValues()
    {
        // Given
        var incrementDamage = 0.1;
        var damage = 0.2;
        var timeOfFailure = 3;
        var loadingRevetment = true;
        var upperLimitLoading = 0.4;
        var lowerLimitLoading = 0.5;
        var minimumWaveHeight = 0.6;
        var maximumWaveHeight = 0.7;
        var waveAngleImpact = 0.8;
        var waveHeightImpact = 0.9;

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
        Assert.AreEqual(incrementDamage, *constructionProperties._incrementDamage);
        Assert.AreEqual(damage, *constructionProperties._damage);
        ASSERT_EQ(timeOfFailure, *constructionProperties._timeOfFailure);
        ASSERT_EQ(loadingRevetment, *constructionProperties._loadingRevetment);
        Assert.AreEqual(upperLimitLoading, *constructionProperties._upperLimitLoading);
        Assert.AreEqual(lowerLimitLoading, *constructionProperties._lowerLimitLoading);
        Assert.AreEqual(minimumWaveHeight, *constructionProperties._minimumWaveHeight);
        Assert.AreEqual(maximumWaveHeight, *constructionProperties._maximumWaveHeight);
        Assert.AreEqual(waveAngleImpact, *constructionProperties._waveAngleImpact);
        Assert.AreEqual(waveHeightImpact, *constructionProperties._waveHeightImpact);
    }
}
}
