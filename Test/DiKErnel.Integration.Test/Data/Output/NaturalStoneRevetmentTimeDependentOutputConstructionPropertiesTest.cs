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
        Assert.IsInstanceOf<TimeDependentOutputConstructionProperties>(constructionProperties);
        Assert.IsNull(constructionProperties.IncrementDamage);
        Assert.IsNull(constructionProperties.Damage);
        Assert.IsNull(constructionProperties.TimeOfFailure);
        Assert.IsNull(constructionProperties._outerSlope);
        Assert.IsNull(constructionProperties._slopeUpperLevel);
        Assert.IsNull(constructionProperties._slopeUpperPosition);
        Assert.IsNull(constructionProperties._slopeLowerLevel);
        Assert.IsNull(constructionProperties._slopeLowerPosition);
        Assert.IsNull(constructionProperties.LoadingRevetment);
        Assert.IsNull(constructionProperties._surfSimilarityParameter);
        Assert.IsNull(constructionProperties._waveSteepnessDeepWater);
        Assert.IsNull(constructionProperties.UpperLimitLoading);
        Assert.IsNull(constructionProperties.LowerLimitLoading);
        Assert.IsNull(constructionProperties._depthMaximumWaveLoad);
        Assert.IsNull(constructionProperties._distanceMaximumWaveElevation);
        Assert.IsNull(constructionProperties._normativeWidthOfWaveImpact);
        Assert.IsNull(constructionProperties._hydraulicLoad);
        Assert.IsNull(constructionProperties.WaveAngleImpact);
        Assert.IsNull(constructionProperties._resistance);
        Assert.IsNull(constructionProperties._referenceTimeDegradation);
        Assert.IsNull(constructionProperties._referenceDegradation);
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
        constructionProperties.IncrementDamage = incrementDamage);
        constructionProperties.Damage = damage);
        constructionProperties.TimeOfFailure = timeOfFailure);
        constructionProperties._outerSlope = outerSlope);
        constructionProperties._slopeUpperLevel = slopeUpperLevel);
        constructionProperties._slopeUpperPosition = slopeUpperPosition);
        constructionProperties._slopeLowerLevel = slopeLowerLevel);
        constructionProperties._slopeLowerPosition = slopeLowerPosition);
        constructionProperties.LoadingRevetment = loadingRevetment);
        constructionProperties._surfSimilarityParameter = surfSimilarityParameter);
        constructionProperties._waveSteepnessDeepWater = waveSteepnessDeepWater);
        constructionProperties.UpperLimitLoading = upperLimitLoading);
        constructionProperties.LowerLimitLoading = lowerLimitLoading);
        constructionProperties._depthMaximumWaveLoad = depthMaximumWaveLoad);
        constructionProperties._distanceMaximumWaveElevation = distanceMaximumWaveElevation);
        constructionProperties._normativeWidthOfWaveImpact = normativeWidthOfWaveImpact);
        constructionProperties._hydraulicLoad = hydraulicLoad);
        constructionProperties.WaveAngleImpact = waveAngleImpact);
        constructionProperties._resistance = resistance);
        constructionProperties._referenceTimeDegradation = referenceTimeDegradation);
        constructionProperties._referenceDegradation = referenceDegradation);

        // Then
        Assert.AreEqual(incrementDamage, constructionProperties.IncrementDamage);
        Assert.AreEqual(damage, constructionProperties.Damage);
        Assert.AreEqual(timeOfFailure, constructionProperties.TimeOfFailure);
        Assert.AreEqual(outerSlope, constructionProperties._outerSlope);
        Assert.AreEqual(slopeUpperLevel, constructionProperties._slopeUpperLevel);
        Assert.AreEqual(slopeUpperPosition, constructionProperties._slopeUpperPosition);
        Assert.AreEqual(slopeLowerLevel, constructionProperties._slopeLowerLevel);
        Assert.AreEqual(slopeLowerPosition, constructionProperties._slopeLowerPosition);
        Assert.AreEqual(loadingRevetment, constructionProperties.LoadingRevetment);
        Assert.AreEqual(surfSimilarityParameter, constructionProperties._surfSimilarityParameter);
        Assert.AreEqual(waveSteepnessDeepWater, constructionProperties._waveSteepnessDeepWater);
        Assert.AreEqual(upperLimitLoading, constructionProperties.UpperLimitLoading);
        Assert.AreEqual(lowerLimitLoading, constructionProperties.LowerLimitLoading);
        Assert.AreEqual(depthMaximumWaveLoad, constructionProperties._depthMaximumWaveLoad);
        Assert.AreEqual(distanceMaximumWaveElevation, constructionProperties._distanceMaximumWaveElevation);
        Assert.AreEqual(normativeWidthOfWaveImpact, constructionProperties._normativeWidthOfWaveImpact);
        Assert.AreEqual(hydraulicLoad, constructionProperties._hydraulicLoad);
        Assert.AreEqual(waveAngleImpact, constructionProperties.WaveAngleImpact);
        Assert.AreEqual(resistance, constructionProperties._resistance);
        Assert.AreEqual(referenceTimeDegradation, constructionProperties._referenceTimeDegradation);
        Assert.AreEqual(referenceDegradation, constructionProperties._referenceDegradation);
    }
}
}
