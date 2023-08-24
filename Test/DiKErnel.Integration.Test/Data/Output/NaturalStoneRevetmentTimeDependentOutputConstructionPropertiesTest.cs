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
    public class NaturalStoneRevetmentTimeDependentOutputConstructionPropertiesTest
    {

        [Test]
    public void Constructor_ExpectedValues()
    {
        // Call
        const NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties;

        // Assert
        Assert.IsInstanceOf<TimeDependentOutputConstructionProperties>(&constructionProperties);
        ASSERT_EQ(nullptr, constructionProperties._incrementDamage);
        ASSERT_EQ(nullptr, constructionProperties._damage);
        ASSERT_EQ(nullptr, constructionProperties._timeOfFailure);
        ASSERT_EQ(nullptr, constructionProperties._outerSlope);
        ASSERT_EQ(nullptr, constructionProperties._slopeUpperLevel);
        ASSERT_EQ(nullptr, constructionProperties._slopeUpperPosition);
        ASSERT_EQ(nullptr, constructionProperties._slopeLowerLevel);
        ASSERT_EQ(nullptr, constructionProperties._slopeLowerPosition);
        ASSERT_EQ(nullptr, constructionProperties._loadingRevetment);
        ASSERT_EQ(nullptr, constructionProperties._surfSimilarityParameter);
        ASSERT_EQ(nullptr, constructionProperties._waveSteepnessDeepWater);
        ASSERT_EQ(nullptr, constructionProperties._upperLimitLoading);
        ASSERT_EQ(nullptr, constructionProperties._lowerLimitLoading);
        ASSERT_EQ(nullptr, constructionProperties._depthMaximumWaveLoad);
        ASSERT_EQ(nullptr, constructionProperties._distanceMaximumWaveElevation);
        ASSERT_EQ(nullptr, constructionProperties._normativeWidthOfWaveImpact);
        ASSERT_EQ(nullptr, constructionProperties._hydraulicLoad);
        ASSERT_EQ(nullptr, constructionProperties._waveAngleImpact);
        ASSERT_EQ(nullptr, constructionProperties._resistance);
        ASSERT_EQ(nullptr, constructionProperties._referenceTimeDegradation);
        ASSERT_EQ(nullptr, constructionProperties._referenceDegradation);
    }

        [Test]
    public void Constructor_WithAllValuesSet_ExpectedValues)
    {
        // Given
        var incrementDamage = 0.1;
        var damage = 0.2;
        var timeOfFailure = 3;
        var outerSlope = 0.4;
        var slopeUpperLevel = 0.5;
        var slopeUpperPosition = 0.6;
        var slopeLowerLevel = 0.7;
        var slopeLowerPosition = 0.8;
        var loadingRevetment = true;
        var surfSimilarityParameter = 0.9;
        var waveSteepnessDeepWater = 1.0;
        var upperLimitLoading = 1.1;
        var lowerLimitLoading = 1.2;
        var depthMaximumWaveLoad = 1.3;
        var distanceMaximumWaveElevation = 1.4;
        var normativeWidthOfWaveImpact = 1.5;
        var hydraulicLoad = 1.6;
        var waveAngleImpact = 1.7;
        var resistance = 1.8;
        var referenceTimeDegradation = 1.9;
        var referenceDegradation = 2.0;

        // When
        NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
        constructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);
        constructionProperties._outerSlope = make_unique<double>(outerSlope);
        constructionProperties._slopeUpperLevel = make_unique<double>(slopeUpperLevel);
        constructionProperties._slopeUpperPosition = make_unique<double>(slopeUpperPosition);
        constructionProperties._slopeLowerLevel = make_unique<double>(slopeLowerLevel);
        constructionProperties._slopeLowerPosition = make_unique<double>(slopeLowerPosition);
        constructionProperties._loadingRevetment = make_unique<bool>(loadingRevetment);
        constructionProperties._surfSimilarityParameter = make_unique<double>(surfSimilarityParameter);
        constructionProperties._waveSteepnessDeepWater = make_unique<double>(waveSteepnessDeepWater);
        constructionProperties._upperLimitLoading = make_unique<double>(upperLimitLoading);
        constructionProperties._lowerLimitLoading = make_unique<double>(lowerLimitLoading);
        constructionProperties._depthMaximumWaveLoad = make_unique<double>(depthMaximumWaveLoad);
        constructionProperties._distanceMaximumWaveElevation = make_unique<double>(distanceMaximumWaveElevation);
        constructionProperties._normativeWidthOfWaveImpact = make_unique<double>(normativeWidthOfWaveImpact);
        constructionProperties._hydraulicLoad = make_unique<double>(hydraulicLoad);
        constructionProperties._waveAngleImpact = make_unique<double>(waveAngleImpact);
        constructionProperties._resistance = make_unique<double>(resistance);
        constructionProperties._referenceTimeDegradation = make_unique<double>(referenceTimeDegradation);
        constructionProperties._referenceDegradation = make_unique<double>(referenceDegradation);

        // Then
        Assert.AreEqual(incrementDamage, *constructionProperties._incrementDamage);
        Assert.AreEqual(damage, *constructionProperties._damage);
        ASSERT_EQ(timeOfFailure, *constructionProperties._timeOfFailure);
        Assert.AreEqual(outerSlope, *constructionProperties._outerSlope);
        Assert.AreEqual(slopeUpperLevel, *constructionProperties._slopeUpperLevel);
        Assert.AreEqual(slopeUpperPosition, *constructionProperties._slopeUpperPosition);
        Assert.AreEqual(slopeLowerLevel, *constructionProperties._slopeLowerLevel);
        Assert.AreEqual(slopeLowerPosition, *constructionProperties._slopeLowerPosition);
        ASSERT_EQ(loadingRevetment, *constructionProperties._loadingRevetment);
        Assert.AreEqual(surfSimilarityParameter, *constructionProperties._surfSimilarityParameter);
        Assert.AreEqual(waveSteepnessDeepWater, *constructionProperties._waveSteepnessDeepWater);
        Assert.AreEqual(upperLimitLoading, *constructionProperties._upperLimitLoading);
        Assert.AreEqual(lowerLimitLoading, *constructionProperties._lowerLimitLoading);
        Assert.AreEqual(depthMaximumWaveLoad, *constructionProperties._depthMaximumWaveLoad);
        Assert.AreEqual(distanceMaximumWaveElevation, *constructionProperties._distanceMaximumWaveElevation);
        Assert.AreEqual(normativeWidthOfWaveImpact, *constructionProperties._normativeWidthOfWaveImpact);
        Assert.AreEqual(hydraulicLoad, *constructionProperties._hydraulicLoad);
        Assert.AreEqual(waveAngleImpact, *constructionProperties._waveAngleImpact);
        Assert.AreEqual(resistance, *constructionProperties._resistance);
        Assert.AreEqual(referenceTimeDegradation, *constructionProperties._referenceTimeDegradation);
        Assert.AreEqual(referenceDegradation, *constructionProperties._referenceDegradation);
    }
}
}
