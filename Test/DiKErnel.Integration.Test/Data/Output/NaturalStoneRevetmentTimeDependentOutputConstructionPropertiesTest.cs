// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

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
            Assert.IsInstanceOf<TimeDependentOutputConstructionProperties>(constructionProperties);
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
            Assert.IsNull(constructionProperties.WaveAngleImpact);
            Assert.IsNull(constructionProperties.Resistance);
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
            double waveAngleImpact = Random.NextDouble();
            double resistance = Random.NextDouble();
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
                WaveAngleImpact = waveAngleImpact,
                Resistance = resistance,
                ReferenceTimeDegradation = referenceTimeDegradation,
                ReferenceDegradation = referenceDegradation
            };

            // Then
            Assert.AreEqual(incrementDamage, constructionProperties.IncrementDamage);
            Assert.AreEqual(damage, constructionProperties.Damage);
            Assert.AreEqual(timeOfFailure, constructionProperties.TimeOfFailure);
            Assert.AreEqual(outerSlope, constructionProperties.OuterSlope);
            Assert.AreEqual(slopeUpperLevel, constructionProperties.SlopeUpperLevel);
            Assert.AreEqual(slopeUpperPosition, constructionProperties.SlopeUpperPosition);
            Assert.AreEqual(slopeLowerLevel, constructionProperties.SlopeLowerLevel);
            Assert.AreEqual(slopeLowerPosition, constructionProperties.SlopeLowerPosition);
            Assert.AreEqual(loadingRevetment, constructionProperties.LoadingRevetment);
            Assert.AreEqual(surfSimilarityParameter, constructionProperties.SurfSimilarityParameter);
            Assert.AreEqual(waveSteepnessDeepWater, constructionProperties.WaveSteepnessDeepWater);
            Assert.AreEqual(upperLimitLoading, constructionProperties.UpperLimitLoading);
            Assert.AreEqual(lowerLimitLoading, constructionProperties.LowerLimitLoading);
            Assert.AreEqual(depthMaximumWaveLoad, constructionProperties.DepthMaximumWaveLoad);
            Assert.AreEqual(distanceMaximumWaveElevation, constructionProperties.DistanceMaximumWaveElevation);
            Assert.AreEqual(normativeWidthOfWaveImpact, constructionProperties.NormativeWidthOfWaveImpact);
            Assert.AreEqual(hydraulicLoad, constructionProperties.HydraulicLoad);
            Assert.AreEqual(waveAngleImpact, constructionProperties.WaveAngleImpact);
            Assert.AreEqual(resistance, constructionProperties.Resistance);
            Assert.AreEqual(referenceTimeDegradation, constructionProperties.ReferenceTimeDegradation);
            Assert.AreEqual(referenceDegradation, constructionProperties.ReferenceDegradation);
        }
    }
}