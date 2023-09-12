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
using DiKErnel.Core.Exceptions;
using DiKErnel.Integration.Data.NaturalStoneRevetment;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.Output
{
    [TestFixture]
    public class NaturalStoneRevetmentTimeDependentOutputTest
    {
        [Test]
        public void Constructor_WithAllValuesSet_ExpectedValues()
        {
            // Setup
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

            // Call
            var output = new NaturalStoneRevetmentTimeDependentOutput(constructionProperties);

            // Assert
            Assert.IsInstanceOf<TimeDependentOutput>(output);
            Assert.AreEqual(incrementDamage, output.IncrementDamage);
            Assert.AreEqual(damage, output.Damage);
            Assert.AreEqual(timeOfFailure, output.TimeOfFailure);
            Assert.AreEqual(outerSlope, output.OuterSlope);
            Assert.AreEqual(slopeUpperLevel, output.SlopeUpperLevel);
            Assert.AreEqual(slopeUpperPosition, output.SlopeUpperPosition);
            Assert.AreEqual(slopeLowerLevel, output.SlopeLowerLevel);
            Assert.AreEqual(slopeLowerPosition, output.SlopeLowerPosition);
            Assert.AreEqual(loadingRevetment, output.LoadingRevetment);
            Assert.AreEqual(surfSimilarityParameter, output.SurfSimilarityParameter);
            Assert.AreEqual(waveSteepnessDeepWater, output.WaveSteepnessDeepWater);
            Assert.AreEqual(upperLimitLoading, output.UpperLimitLoading);
            Assert.AreEqual(lowerLimitLoading, output.LowerLimitLoading);
            Assert.AreEqual(depthMaximumWaveLoad, output.DepthMaximumWaveLoad);
            Assert.AreEqual(distanceMaximumWaveElevation, output.DistanceMaximumWaveElevation);
            Assert.AreEqual(normativeWidthOfWaveImpact, output.NormativeWidthOfWaveImpact);
            Assert.AreEqual(hydraulicLoad, output.HydraulicLoad);
            Assert.AreEqual(waveAngleImpact, output.WaveAngleImpact);
            Assert.AreEqual(resistance, output.Resistance);
            Assert.AreEqual(referenceTimeDegradation, output.ReferenceTimeDegradation);
            Assert.AreEqual(referenceDegradation, output.ReferenceDegradation);
        }

        [Test]
        public void Constructor_WithNullValues_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
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

            var constructionProperties = new NaturalStoneRevetmentTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = null,
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
                HydraulicLoad = null,
                WaveAngleImpact = null,
                Resistance = null,
                ReferenceTimeDegradation = null,
                ReferenceDegradation = null
            };

            // Call
            var output = new NaturalStoneRevetmentTimeDependentOutput(constructionProperties);

            // Assert
            Assert.IsInstanceOf<TimeDependentOutput>(output);
            Assert.AreEqual(incrementDamage, output.IncrementDamage);
            Assert.AreEqual(damage, output.Damage);
            Assert.IsNull(output.TimeOfFailure);
            Assert.AreEqual(outerSlope, output.OuterSlope);
            Assert.AreEqual(slopeUpperLevel, output.SlopeUpperLevel);
            Assert.AreEqual(slopeUpperPosition, output.SlopeUpperPosition);
            Assert.AreEqual(slopeLowerLevel, output.SlopeLowerLevel);
            Assert.AreEqual(slopeLowerPosition, output.SlopeLowerPosition);
            Assert.AreEqual(loadingRevetment, output.LoadingRevetment);
            Assert.AreEqual(surfSimilarityParameter, output.SurfSimilarityParameter);
            Assert.AreEqual(waveSteepnessDeepWater, output.WaveSteepnessDeepWater);
            Assert.AreEqual(upperLimitLoading, output.UpperLimitLoading);
            Assert.AreEqual(lowerLimitLoading, output.LowerLimitLoading);
            Assert.AreEqual(depthMaximumWaveLoad, output.DepthMaximumWaveLoad);
            Assert.AreEqual(distanceMaximumWaveElevation, output.DistanceMaximumWaveElevation);
            Assert.AreEqual(normativeWidthOfWaveImpact, output.NormativeWidthOfWaveImpact);
            Assert.IsNull(output.HydraulicLoad);
            Assert.IsNull(output.WaveAngleImpact);
            Assert.IsNull(output.Resistance);
            Assert.IsNull(output.ReferenceTimeDegradation);
            Assert.IsNull(output.ReferenceDegradation);
        }

        [Test]
        public void Constructor_OuterSlopeNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.OuterSlope = null;

            // Call
            void Call() => new NaturalStoneRevetmentTimeDependentOutput(constructionProperties);

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "outerSlope must be set.");
        }

        [Test]
        public void Constructor_SlopeUpperLevelNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.SlopeUpperLevel = null;

            // Call
            void Call() => new NaturalStoneRevetmentTimeDependentOutput(constructionProperties);

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "slopeUpperLevel must be set.");
        }

        [Test]
        public void Constructor_SlopeUpperPositionNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.SlopeUpperPosition = null;

            // Call
            void Call() => new NaturalStoneRevetmentTimeDependentOutput(constructionProperties);

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "slopeUpperPosition must be set.");
        }

        [Test]
        public void Constructor_SlopeLowerLevelNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.SlopeLowerLevel = null;

            // Call
            void Call() => new NaturalStoneRevetmentTimeDependentOutput(constructionProperties);

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "slopeLowerLevel must be set.");
        }

        [Test]
        public void Constructor_SlopeLowerPositionNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.SlopeLowerPosition = null;

            // Call
            void Call() => new NaturalStoneRevetmentTimeDependentOutput(constructionProperties);

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "slopeLowerPosition must be set.");
        }

        [Test]
        public void Constructor_LoadingRevetmentNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.LoadingRevetment = null;

            // Call
            void Call() => new NaturalStoneRevetmentTimeDependentOutput(constructionProperties);

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "loadingRevetment must be set.");
        }

        [Test]
        public void Constructor_SurfSimilarityParameterNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.SurfSimilarityParameter = null;

            // Call
            void Call() => new NaturalStoneRevetmentTimeDependentOutput(constructionProperties);

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "surfSimilarityParameter must be set.");
        }

        [Test]
        public void Constructor_LowerLimitLoadingNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.LowerLimitLoading = null;

            // Call
            void Call() => new NaturalStoneRevetmentTimeDependentOutput(constructionProperties);

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "lowerLimitLoading must be set.");
        }

        [Test]
        public void Constructor_DepthMaximumWaveLoadNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.DepthMaximumWaveLoad = null;

            // Call
            void Call() => new NaturalStoneRevetmentTimeDependentOutput(constructionProperties);

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "depthMaximumWaveLoad must be set.");
        }

        [Test]
        public void Constructor_DistanceMaximumWaveElevationNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.DistanceMaximumWaveElevation = null;

            // Call
            void Call() => new NaturalStoneRevetmentTimeDependentOutput(constructionProperties);

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "distanceMaximumWaveElevation must be set.");
        }

        [Test]
        public void Constructor_NormativeWidthOfWaveImpactNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.NormativeWidthOfWaveImpact = null;

            // Call
            void Call() => new NaturalStoneRevetmentTimeDependentOutput(constructionProperties);

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "normativeWidthOfWaveImpact must be set.");
        }

        private static NaturalStoneRevetmentTimeDependentOutputConstructionProperties CreateFullyConfiguredConstructionProperties()
        {
            return new NaturalStoneRevetmentTimeDependentOutputConstructionProperties
            {
                IncrementDamage = Random.NextDouble(),
                Damage = Random.NextDouble(),
                TimeOfFailure = Random.Next(),
                OuterSlope = Random.NextDouble(),
                SlopeUpperLevel = Random.NextDouble(),
                SlopeUpperPosition = Random.NextDouble(),
                SlopeLowerLevel = Random.NextDouble(),
                SlopeLowerPosition = Random.NextDouble(),
                LoadingRevetment = Random.NextBoolean(),
                SurfSimilarityParameter = Random.NextDouble(),
                WaveSteepnessDeepWater = Random.NextDouble(),
                UpperLimitLoading = Random.NextDouble(),
                LowerLimitLoading = Random.NextDouble(),
                DepthMaximumWaveLoad = Random.NextDouble(),
                DistanceMaximumWaveElevation = Random.NextDouble(),
                NormativeWidthOfWaveImpact = Random.NextDouble(),
                HydraulicLoad = Random.NextDouble(),
                WaveAngleImpact = Random.NextDouble(),
                Resistance = Random.NextDouble(),
                ReferenceTimeDegradation = Random.NextDouble(),
                ReferenceDegradation = Random.NextDouble()
            };
        }
    }
}