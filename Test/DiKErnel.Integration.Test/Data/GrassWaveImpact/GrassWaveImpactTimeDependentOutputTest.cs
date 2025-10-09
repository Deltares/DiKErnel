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
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.GrassWaveImpact
{
    [TestFixture]
    internal sealed class GrassWaveImpactTimeDependentOutputTest
    {
        [Test]
        public void Constructor_WithAllValuesSet_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            bool loadingRevetment = Random.NextBoolean();
            double upperLimitLoading = Random.NextDouble();
            double lowerLimitLoading = Random.NextDouble();
            double waveAngle = Random.NextDouble();
            double waveAngleImpact = Random.NextDouble();
            double waveHeightImpact = Random.NextDouble();

            var constructionProperties = new GrassWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                LoadingRevetment = loadingRevetment,
                UpperLimitLoading = upperLimitLoading,
                LowerLimitLoading = lowerLimitLoading,
                WaveAngle = waveAngle,
                WaveAngleImpact = waveAngleImpact,
                WaveHeightImpact = waveHeightImpact
            };

            // Call
            var output = new GrassWaveImpactTimeDependentOutput(constructionProperties);

            // Assert
            Assert.That(output, Is.InstanceOf<TimeDependentOutput>());
            Assert.That(output.IncrementDamage, Is.EqualTo(incrementDamage));
            Assert.That(output.LoadingRevetment, Is.EqualTo(loadingRevetment));
            Assert.That(output.UpperLimitLoading, Is.EqualTo(upperLimitLoading));
            Assert.That(output.LowerLimitLoading, Is.EqualTo(lowerLimitLoading));
            Assert.That(output.WaveAngle, Is.EqualTo(waveAngle));
            Assert.That(output.WaveAngleImpact, Is.EqualTo(waveAngleImpact));
            Assert.That(output.WaveHeightImpact, Is.EqualTo(waveHeightImpact));
        }

        [Test]
        public void Constructor_WithNullValues_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            bool loadingRevetment = Random.NextBoolean();
            double upperLimitLoading = Random.NextDouble();
            double lowerLimitLoading = Random.NextDouble();

            var constructionProperties = new GrassWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                LoadingRevetment = loadingRevetment,
                UpperLimitLoading = upperLimitLoading,
                LowerLimitLoading = lowerLimitLoading,
                WaveAngle = null,
                WaveAngleImpact = null,
                WaveHeightImpact = null
            };

            // Call
            var output = new GrassWaveImpactTimeDependentOutput(constructionProperties);

            // Assert
            Assert.That(output, Is.InstanceOf<TimeDependentOutput>());
            Assert.That(output.IncrementDamage, Is.EqualTo(incrementDamage));
            Assert.That(output.LoadingRevetment, Is.EqualTo(loadingRevetment));
            Assert.That(output.UpperLimitLoading, Is.EqualTo(upperLimitLoading));
            Assert.That(output.LowerLimitLoading, Is.EqualTo(lowerLimitLoading));
            Assert.That(output.WaveAngle, Is.Null);
            Assert.That(output.WaveAngleImpact, Is.Null);
            Assert.That(output.WaveHeightImpact, Is.Null);
        }

        [Test]
        public void Constructor_LoadingRevetmentNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            GrassWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.LoadingRevetment = null;

            // Call
            void Call()
            {
                var output = new GrassWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "LoadingRevetment must be set.");
        }

        [Test]
        public void Constructor_UpperLimitLoadingNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            GrassWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.UpperLimitLoading = null;

            // Call
            void Call()
            {
                var output = new GrassWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "UpperLimitLoading must be set.");
        }

        [Test]
        public void Constructor_LowerLimitLoadingNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            GrassWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.LowerLimitLoading = null;

            // Call
            void Call()
            {
                var output = new GrassWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "LowerLimitLoading must be set.");
        }

        private static GrassWaveImpactTimeDependentOutputConstructionProperties CreateFullyConfiguredConstructionProperties()
        {
            return new GrassWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = Random.NextDouble(),
                LoadingRevetment = Random.NextBoolean(),
                UpperLimitLoading = Random.NextDouble(),
                LowerLimitLoading = Random.NextDouble(),
                WaveAngle = Random.NextDouble(),
                WaveAngleImpact = Random.NextDouble(),
                WaveHeightImpact = Random.NextDouble()
            };
        }
    }
}