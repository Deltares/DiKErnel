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
using DiKErnel.Core.Exceptions;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.NaturalStoneWaveImpact
{
    [TestFixture]
    internal sealed class NaturalStoneWaveImpactTimeDependentOutputTest
    {
        [Test]
        public void Constructor_WithAllValuesSet_ExpectedValues()
        {
            // Setup
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

            // Call
            var output = new NaturalStoneWaveImpactTimeDependentOutput(constructionProperties);

            // Assert
            Assert.That(output, Is.InstanceOf<TimeDependentOutput>());
            Assert.That(output.IncrementDamage, Is.EqualTo(incrementDamage));
            Assert.That(output.OuterSlope, Is.EqualTo(outerSlope));
            Assert.That(output.SlopeUpperLevel, Is.EqualTo(slopeUpperLevel));
            Assert.That(output.SlopeUpperPosition, Is.EqualTo(slopeUpperPosition));
            Assert.That(output.SlopeLowerLevel, Is.EqualTo(slopeLowerLevel));
            Assert.That(output.SlopeLowerPosition, Is.EqualTo(slopeLowerPosition));
            Assert.That(output.LoadingRevetment, Is.EqualTo(loadingRevetment));
            Assert.That(output.SurfSimilarityParameter, Is.EqualTo(surfSimilarityParameter));
            Assert.That(output.WaveSteepnessDeepWater, Is.EqualTo(waveSteepnessDeepWater));
            Assert.That(output.UpperLimitLoading, Is.EqualTo(upperLimitLoading));
            Assert.That(output.LowerLimitLoading, Is.EqualTo(lowerLimitLoading));
            Assert.That(output.DepthMaximumWaveLoad, Is.EqualTo(depthMaximumWaveLoad));
            Assert.That(output.DistanceMaximumWaveElevation, Is.EqualTo(distanceMaximumWaveElevation));
            Assert.That(output.NormativeWidthOfWaveImpact, Is.EqualTo(normativeWidthOfWaveImpact));
            Assert.That(output.HydraulicLoad, Is.EqualTo(hydraulicLoad));
            Assert.That(output.WaveAngle, Is.EqualTo(waveAngle));
            Assert.That(output.WaveAngleImpact, Is.EqualTo(waveAngleImpact));
            Assert.That(output.ReferenceTimeDegradation, Is.EqualTo(referenceTimeDegradation));
            Assert.That(output.ReferenceDegradation, Is.EqualTo(referenceDegradation));
        }

        [Test]
        public void Constructor_WithNullValues_ExpectedValues()
        {
            // Setup
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
                HydraulicLoad = null,
                WaveAngle = null,
                WaveAngleImpact = null,
                ReferenceTimeDegradation = null,
                ReferenceDegradation = null
            };

            // Call
            var output = new NaturalStoneWaveImpactTimeDependentOutput(constructionProperties);

            // Assert
            Assert.That(output, Is.InstanceOf<TimeDependentOutput>());
            Assert.That(output.IncrementDamage, Is.EqualTo(incrementDamage));
            Assert.That(output.OuterSlope, Is.EqualTo(outerSlope));
            Assert.That(output.SlopeUpperLevel, Is.EqualTo(slopeUpperLevel));
            Assert.That(output.SlopeUpperPosition, Is.EqualTo(slopeUpperPosition));
            Assert.That(output.SlopeLowerLevel, Is.EqualTo(slopeLowerLevel));
            Assert.That(output.SlopeLowerPosition, Is.EqualTo(slopeLowerPosition));
            Assert.That(output.LoadingRevetment, Is.EqualTo(loadingRevetment));
            Assert.That(output.SurfSimilarityParameter, Is.EqualTo(surfSimilarityParameter));
            Assert.That(output.WaveSteepnessDeepWater, Is.EqualTo(waveSteepnessDeepWater));
            Assert.That(output.UpperLimitLoading, Is.EqualTo(upperLimitLoading));
            Assert.That(output.LowerLimitLoading, Is.EqualTo(lowerLimitLoading));
            Assert.That(output.DepthMaximumWaveLoad, Is.EqualTo(depthMaximumWaveLoad));
            Assert.That(output.DistanceMaximumWaveElevation, Is.EqualTo(distanceMaximumWaveElevation));
            Assert.That(output.NormativeWidthOfWaveImpact, Is.EqualTo(normativeWidthOfWaveImpact));
            Assert.That(output.HydraulicLoad, Is.Null);
            Assert.That(output.WaveAngle, Is.Null);
            Assert.That(output.WaveAngleImpact, Is.Null);
            Assert.That(output.ReferenceTimeDegradation, Is.Null);
            Assert.That(output.ReferenceDegradation, Is.Null);
        }

        [Test]
        public void Constructor_OuterSlopeNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.OuterSlope = null;

            // Call
            void Call()
            {
                var output = new NaturalStoneWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "OuterSlope must be set.");
        }

        [Test]
        public void Constructor_SlopeUpperLevelNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.SlopeUpperLevel = null;

            // Call
            void Call()
            {
                var output = new NaturalStoneWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "SlopeUpperLevel must be set.");
        }

        [Test]
        public void Constructor_SlopeUpperPositionNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.SlopeUpperPosition = null;

            // Call
            void Call()
            {
                var output = new NaturalStoneWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "SlopeUpperPosition must be set.");
        }

        [Test]
        public void Constructor_SlopeLowerLevelNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.SlopeLowerLevel = null;

            // Call
            void Call()
            {
                var output = new NaturalStoneWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "SlopeLowerLevel must be set.");
        }

        [Test]
        public void Constructor_SlopeLowerPositionNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.SlopeLowerPosition = null;

            // Call
            void Call()
            {
                var output = new NaturalStoneWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "SlopeLowerPosition must be set.");
        }

        [Test]
        public void Constructor_LoadingRevetmentNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.LoadingRevetment = null;

            // Call
            void Call()
            {
                var output = new NaturalStoneWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "LoadingRevetment must be set.");
        }

        [Test]
        public void Constructor_SurfSimilarityParameterNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.SurfSimilarityParameter = null;

            // Call
            void Call()
            {
                var output = new NaturalStoneWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "SurfSimilarityParameter must be set.");
        }

        [Test]
        public void Constructor_LowerLimitLoadingNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.LowerLimitLoading = null;

            // Call
            void Call()
            {
                var output = new NaturalStoneWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "LowerLimitLoading must be set.");
        }

        [Test]
        public void Constructor_DepthMaximumWaveLoadNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.DepthMaximumWaveLoad = null;

            // Call
            void Call()
            {
                var output = new NaturalStoneWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "DepthMaximumWaveLoad must be set.");
        }

        [Test]
        public void Constructor_DistanceMaximumWaveElevationNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.DistanceMaximumWaveElevation = null;

            // Call
            void Call()
            {
                var output = new NaturalStoneWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "DistanceMaximumWaveElevation must be set.");
        }

        [Test]
        public void Constructor_NormativeWidthOfWaveImpactNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            NaturalStoneWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.NormativeWidthOfWaveImpact = null;

            // Call
            void Call()
            {
                var output = new NaturalStoneWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "NormativeWidthOfWaveImpact must be set.");
        }

        private static NaturalStoneWaveImpactTimeDependentOutputConstructionProperties CreateFullyConfiguredConstructionProperties()
        {
            return new NaturalStoneWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = Random.NextDouble(),
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
                WaveAngle = Random.NextDouble(),
                WaveAngleImpact = Random.NextDouble(),
                ReferenceTimeDegradation = Random.NextDouble(),
                ReferenceDegradation = Random.NextDouble()
            };
        }
    }
}