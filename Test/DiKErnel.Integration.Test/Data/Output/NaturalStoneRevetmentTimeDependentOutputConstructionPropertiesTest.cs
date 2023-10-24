// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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
using DiKErnel.Integration.Data.NaturalStoneRevetment;
using DiKErnel.TestUtil;
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
            var constructionProperties = new NaturalStoneRevetmentTimeDependentOutputConstructionProperties();

            // Assert
            Assert.That(constructionProperties, Is.InstanceOf<TimeDependentOutputConstructionProperties>());
            Assert.IsNull(constructionProperties.IncrementDamage);
            Assert.IsNull(constructionProperties.Damage);
            Assert.IsNull(constructionProperties.TimeOfFailure);
            Assert.IsNull(constructionProperties.OuterSlope);
            Assert.IsNull(constructionProperties.SlopeUpperLevel);
            Assert.IsNull(constructionProperties.SlopeUpperPosition);
            Assert.IsNull(constructionProperties.SlopeLowerLevel);
            Assert.IsNull(constructionProperties.SlopeLowerPosition);
            Assert.IsNull(constructionProperties.LoadingRevetment);
            Assert.IsNull(constructionProperties.SurfSimilarityParameter);
            Assert.IsNull(constructionProperties.WaveSteepnessDeepWater);
            Assert.IsNull(constructionProperties.UpperLimitLoading);
            Assert.IsNull(constructionProperties.LowerLimitLoading);
            Assert.IsNull(constructionProperties.DepthMaximumWaveLoad);
            Assert.IsNull(constructionProperties.DistanceMaximumWaveElevation);
            Assert.IsNull(constructionProperties.NormativeWidthOfWaveImpact);
            Assert.IsNull(constructionProperties.HydraulicLoad);
            Assert.IsNull(constructionProperties.WaveAngle);
            Assert.IsNull(constructionProperties.WaveAngleImpact);
            Assert.IsNull(constructionProperties.ReferenceTimeDegradation);
            Assert.IsNull(constructionProperties.ReferenceDegradation);
        }

        [Test]
        public void Constructor_WithAllValuesSet_ExpectedValues()
        {
            // Given
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            int timeOfFailure = Random.Next();
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
            var constructionProperties = new NaturalStoneRevetmentTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = timeOfFailure,
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
            Assert.That(constructionProperties.Damage, Is.EqualTo(damage));
            Assert.That(constructionProperties.TimeOfFailure, Is.EqualTo(timeOfFailure));
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