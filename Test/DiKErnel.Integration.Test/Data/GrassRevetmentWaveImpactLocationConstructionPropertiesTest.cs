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

namespace DiKErnel.Integration.Test.Data
{
    [TestFixture]
    public class GrassRevetmentWaveImpactLocationConstructionPropertiesTest
    {

        [Test]
    public void Constructor_ExpectedValues()
    {
        // Setup
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var x = 0.1;

        // Call
        const GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties(x, topLayerType);

        // Assert
        Assert.IsInstanceOf<RevetmentLocationConstructionPropertiesBase>(&constructionProperties);
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        Assert.AreEqual(x, constructionProperties.GetX());
        ASSERT_EQ(nullptr, constructionProperties.GetInitialDamage());
        ASSERT_EQ(nullptr, constructionProperties.GetFailureNumber());
        ASSERT_EQ(nullptr, constructionProperties.GetTimeLineAgwi());
        ASSERT_EQ(nullptr, constructionProperties.GetTimeLineBgwi());
        ASSERT_EQ(nullptr, constructionProperties.GetTimeLineCgwi());
        ASSERT_EQ(nullptr, constructionProperties.GetMinimumWaveHeightTemax());
        ASSERT_EQ(nullptr, constructionProperties.GetMaximumWaveHeightTemin());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveAngleImpactNwa());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveAngleImpactQwa());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveAngleImpactRwa());
        ASSERT_EQ(nullptr, constructionProperties.GetUpperLimitLoadingAul());
        ASSERT_EQ(nullptr, constructionProperties.GetLowerLimitLoadingAll());
    }

        [Test]
    public void GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues()
    {
        // Given
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var x = 0.1;
        var initialDamage = 0.2;
        var failureNumber = 0.3;
        var timeLineAgwi = 0.4;
        var timeLineBgwi = 0.5;
        var timeLineCgwi = 0.6;
        var minimumWaveHeightTemax = 0.7;
        var maximumWaveHeightTemin = 0.8;
        var waveAngleImpactNwa = 0.9;
        var waveAngleImpactQwa = 1.0;
        var waveAngleImpactRwa = 1.1;
        var upperLimitLoadingAul = 1.2;
        var lowerLimitLoadingAll = 1.3;

        GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties(x, topLayerType);

        // When
        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties.SetTimeLineAgwi(make_unique<double>(timeLineAgwi));
        constructionProperties.SetTimeLineBgwi(make_unique<double>(timeLineBgwi));
        constructionProperties.SetTimeLineCgwi(make_unique<double>(timeLineCgwi));
        constructionProperties.SetMinimumWaveHeightTemax(make_unique<double>(minimumWaveHeightTemax));
        constructionProperties.SetMaximumWaveHeightTemin(make_unique<double>(maximumWaveHeightTemin));
        constructionProperties.SetWaveAngleImpactNwa(make_unique<double>(waveAngleImpactNwa));
        constructionProperties.SetWaveAngleImpactQwa(make_unique<double>(waveAngleImpactQwa));
        constructionProperties.SetWaveAngleImpactRwa(make_unique<double>(waveAngleImpactRwa));
        constructionProperties.SetUpperLimitLoadingAul(make_unique<double>(upperLimitLoadingAul));
        constructionProperties.SetLowerLimitLoadingAll(make_unique<double>(lowerLimitLoadingAll));

        // Then
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        Assert.AreEqual(x, constructionProperties.GetX());
        Assert.AreEqual(initialDamage, *constructionProperties.GetInitialDamage());
        Assert.AreEqual(failureNumber, *constructionProperties.GetFailureNumber());
        Assert.AreEqual(timeLineAgwi, *constructionProperties.GetTimeLineAgwi());
        Assert.AreEqual(timeLineBgwi, *constructionProperties.GetTimeLineBgwi());
        Assert.AreEqual(timeLineCgwi, *constructionProperties.GetTimeLineCgwi());
        Assert.AreEqual(minimumWaveHeightTemax, *constructionProperties.GetMinimumWaveHeightTemax());
        Assert.AreEqual(maximumWaveHeightTemin, *constructionProperties.GetMaximumWaveHeightTemin());
        Assert.AreEqual(waveAngleImpactNwa, *constructionProperties.GetWaveAngleImpactNwa());
        Assert.AreEqual(waveAngleImpactQwa, *constructionProperties.GetWaveAngleImpactQwa());
        Assert.AreEqual(waveAngleImpactRwa, *constructionProperties.GetWaveAngleImpactRwa());
        Assert.AreEqual(upperLimitLoadingAul, *constructionProperties.GetUpperLimitLoadingAul());
        Assert.AreEqual(lowerLimitLoadingAll, *constructionProperties.GetLowerLimitLoadingAll());
    }
}
}
