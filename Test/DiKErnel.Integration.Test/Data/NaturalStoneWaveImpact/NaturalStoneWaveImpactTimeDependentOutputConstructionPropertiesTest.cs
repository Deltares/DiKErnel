// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using DiKErnel.Core.Data;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.NaturalStoneWaveImpact
{
    [TestFixture]
    internal sealed class NaturalStoneWaveImpactTimeDependentOutputConstructionPropertiesTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Call
            var constructionProperties = new NaturalStoneWaveImpactTimeDependentOutputConstructionProperties();

            // Assert
            Assert.That(constructionProperties, Is.InstanceOf<TimeDependentOutputConstructionProperties>());
            Assert.That(constructionProperties.IncrementDamage, Is.Null);
            Assert.That(constructionProperties.OuterSlope, Is.Null);
            Assert.That(constructionProperties.SlopeUpperLevel, Is.Null);
            Assert.That(constructionProperties.SlopeUpperPosition, Is.Null);
            Assert.That(constructionProperties.SlopeLowerLevel, Is.Null);
            Assert.That(constructionProperties.SlopeLowerPosition, Is.Null);
            Assert.That(constructionProperties.LoadingRevetment, Is.Null);
            Assert.That(constructionProperties.SurfSimilarityParameter, Is.Null);
            Assert.That(constructionProperties.WaveSteepnessDeepWater, Is.Null);
            Assert.That(constructionProperties.UpperLimitLoading, Is.Null);
            Assert.That(constructionProperties.LowerLimitLoading, Is.Null);
            Assert.That(constructionProperties.DepthMaximumWaveLoad, Is.Null);
            Assert.That(constructionProperties.DistanceMaximumWaveElevation, Is.Null);
            Assert.That(constructionProperties.NormativeWidthOfWaveImpact, Is.Null);
            Assert.That(constructionProperties.HydraulicLoad, Is.Null);
            Assert.That(constructionProperties.WaveAngle, Is.Null);
            Assert.That(constructionProperties.WaveAngleImpact, Is.Null);
            Assert.That(constructionProperties.ReferenceTimeDegradation, Is.Null);
            Assert.That(constructionProperties.ReferenceDegradation, Is.Null);
        }

        [Test]
        public void Constructor_WithAllValuesSet_ExpectedValues()
        {
            // Given
            double incrementDamage = Random.NextDouble();
            double outerSlope = Random.NextDouble();
            double slopeUpperLevel = Random.NextDouble();
            double slopeUpperPosition = Random.NextDouble();
            double slopeLowerLevel = Random.NextDouble();
            double slopeLowerPosition = Random.NextDouble();
            bool loadingRevetment = Random.NextBoolean();
            double surfSimilarityParameter = Random.NextDouble();
            double waveSteepnessDeepWater = Random.NextDouble();
            double upperLimitLoading = Random.NextDouble();
            double lowerLimitLoading = Random.NextDouble();
            double depthMaximumWaveLoad = Random.NextDouble();
            double distanceMaximumWaveElevation = Random.NextDouble();
            double normativeWidthOfWaveImpact = Random.NextDouble();
            double hydraulicLoad = Random.NextDouble();
            double waveAngle = Random.NextDouble();
            double waveAngleImpact = Random.NextDouble();
            double referenceTimeDegradation = Random.NextDouble();
            double referenceDegradation = Random.NextDouble();

            // When
            var constructionProperties = new NaturalStoneWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                OuterSlope = outerSlope,
                SlopeUpperLevel = slopeUpperLevel,
                SlopeUpperPosition = slopeUpperPosition,
                SlopeLowerLevel = slopeLowerLevel,
                SlopeLowerPosition = slopeLowerPosition,
                LoadingRevetment = loadingRevetment,
                SurfSimilarityParameter = surfSimilarityParameter,
                WaveSteepnessDeepWater = waveSteepnessDeepWater,
                UpperLimitLoading = upperLimitLoading,
                LowerLimitLoading = lowerLimitLoading,
                DepthMaximumWaveLoad = depthMaximumWaveLoad,
                DistanceMaximumWaveElevation = distanceMaximumWaveElevation,
                NormativeWidthOfWaveImpact = normativeWidthOfWaveImpact,
                HydraulicLoad = hydraulicLoad,
                WaveAngle = waveAngle,
                WaveAngleImpact = waveAngleImpact,
                ReferenceTimeDegradation = referenceTimeDegradation,
                ReferenceDegradation = referenceDegradation
            };

            // Then
            Assert.That(constructionProperties.IncrementDamage, Is.EqualTo(incrementDamage));
            Assert.That(constructionProperties.OuterSlope, Is.EqualTo(outerSlope));
            Assert.That(constructionProperties.SlopeUpperLevel, Is.EqualTo(slopeUpperLevel));
            Assert.That(constructionProperties.SlopeUpperPosition, Is.EqualTo(slopeUpperPosition));
            Assert.That(constructionProperties.SlopeLowerLevel, Is.EqualTo(slopeLowerLevel));
            Assert.That(constructionProperties.SlopeLowerPosition, Is.EqualTo(slopeLowerPosition));
            Assert.That(constructionProperties.LoadingRevetment, Is.EqualTo(loadingRevetment));
            Assert.That(constructionProperties.SurfSimilarityParameter, Is.EqualTo(surfSimilarityParameter));
            Assert.That(constructionProperties.WaveSteepnessDeepWater, Is.EqualTo(waveSteepnessDeepWater));
            Assert.That(constructionProperties.UpperLimitLoading, Is.EqualTo(upperLimitLoading));
            Assert.That(constructionProperties.LowerLimitLoading, Is.EqualTo(lowerLimitLoading));
            Assert.That(constructionProperties.DepthMaximumWaveLoad, Is.EqualTo(depthMaximumWaveLoad));
            Assert.That(constructionProperties.DistanceMaximumWaveElevation, Is.EqualTo(distanceMaximumWaveElevation));
            Assert.That(constructionProperties.NormativeWidthOfWaveImpact, Is.EqualTo(normativeWidthOfWaveImpact));
            Assert.That(constructionProperties.HydraulicLoad, Is.EqualTo(hydraulicLoad));
            Assert.That(constructionProperties.WaveAngle, Is.EqualTo(waveAngle));
            Assert.That(constructionProperties.WaveAngleImpact, Is.EqualTo(waveAngleImpact));
            Assert.That(constructionProperties.ReferenceTimeDegradation, Is.EqualTo(referenceTimeDegradation));
            Assert.That(constructionProperties.ReferenceDegradation, Is.EqualTo(referenceDegradation));
        }
    }
}