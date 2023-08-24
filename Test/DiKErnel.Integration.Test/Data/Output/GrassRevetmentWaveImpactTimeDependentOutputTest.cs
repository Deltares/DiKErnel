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

using DiKErnel.Core.Data;
using DiKErnel.Core.Exceptions;
using DiKErnel.Integration.Data.GrassRevetmentWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.Output
{
    [TestFixture]
    public class GrassRevetmentWaveImpactTimeDependentOutputTest
    {
        [Test]
        public void Constructor_WithAllValuesSet_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            int timeOfFailure = Random.Next();
            bool loadingRevetment = Random.NextBoolean();
            double upperLimitLoading = Random.NextDouble();
            double lowerLimitLoading = Random.NextDouble();
            double minimumWaveHeight = Random.NextDouble();
            double maximumWaveHeight = Random.NextDouble();
            double waveAngleImpact = Random.NextDouble();
            double waveHeightImpact = Random.NextDouble();

            var constructionProperties = new GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = timeOfFailure,
                LoadingRevetment = loadingRevetment,
                UpperLimitLoading = upperLimitLoading,
                LowerLimitLoading = lowerLimitLoading,
                MinimumWaveHeight = minimumWaveHeight,
                MaximumWaveHeight = maximumWaveHeight,
                WaveAngleImpact = waveAngleImpact,
                WaveHeightImpact = waveHeightImpact
            };

            // Call
            var output = new GrassRevetmentWaveImpactTimeDependentOutput(constructionProperties);

            // Assert
            Assert.IsInstanceOf<TimeDependentOutput>(output);
            Assert.AreEqual(incrementDamage, output.IncrementDamage);
            Assert.AreEqual(damage, output.Damage);
            Assert.AreEqual(timeOfFailure, output.TimeOfFailure);
            Assert.AreEqual(loadingRevetment, output.LoadingRevetment);
            Assert.AreEqual(upperLimitLoading, output.UpperLimitLoading);
            Assert.AreEqual(lowerLimitLoading, output.LowerLimitLoading);
            Assert.AreEqual(minimumWaveHeight, output.MinimumWaveHeight);
            Assert.AreEqual(maximumWaveHeight, output.MaximumWaveHeight);
            Assert.AreEqual(waveAngleImpact, output.WaveAngleImpact);
            Assert.AreEqual(waveHeightImpact, output.WaveHeightImpact);
        }

        [Test]
        public void Constructor_WithNullValues_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            bool loadingRevetment = Random.NextBoolean();
            double upperLimitLoading = Random.NextDouble();
            double lowerLimitLoading = Random.NextDouble();

            var constructionProperties = new GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = null,
                LoadingRevetment = loadingRevetment,
                UpperLimitLoading = upperLimitLoading,
                LowerLimitLoading = lowerLimitLoading,
                MinimumWaveHeight = null,
                MaximumWaveHeight = null,
                WaveAngleImpact = null,
                WaveHeightImpact = null
            };

            // Call
            var output = new GrassRevetmentWaveImpactTimeDependentOutput(constructionProperties);

            // Assert
            Assert.IsInstanceOf<TimeDependentOutput>(output);
            Assert.AreEqual(incrementDamage, output.IncrementDamage);
            Assert.AreEqual(damage, output.Damage);
            Assert.IsNull(output.TimeOfFailure);
            Assert.AreEqual(loadingRevetment, output.LoadingRevetment);
            Assert.AreEqual(upperLimitLoading, output.UpperLimitLoading);
            Assert.AreEqual(lowerLimitLoading, output.LowerLimitLoading);
            Assert.IsNull(output.MinimumWaveHeight);
            Assert.IsNull(output.MaximumWaveHeight);
            Assert.IsNull(output.WaveAngleImpact);
            Assert.IsNull(output.WaveHeightImpact);
        }

        [Test]
        public void Constructor_LoadingRevetmentNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.LoadingRevetment = null;

            // Call
            void Call() => new GrassRevetmentWaveImpactTimeDependentOutput(constructionProperties);

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "loadingRevetment must be set.");
        }

        [Test]
        public void Constructor_UpperLimitLoadingNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.UpperLimitLoading = null;

            // Call
            void Call() => new GrassRevetmentWaveImpactTimeDependentOutput(constructionProperties);

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "upperLimitLoading must be set.");
        }

        [Test]
        public void Constructor_LowerLimitLoadingNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.LowerLimitLoading = null;

            // Call
            void Call() => new GrassRevetmentWaveImpactTimeDependentOutput(constructionProperties);

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "lowerLimitLoading must be set.");
        }

        private static GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties CreateFullyConfiguredConstructionProperties()
        {
            return new GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = Random.NextDouble(),
                Damage = Random.NextDouble(),
                TimeOfFailure = Random.Next(),
                LoadingRevetment = Random.NextBoolean(),
                UpperLimitLoading = Random.NextDouble(),
                LowerLimitLoading = Random.NextDouble(),
                MinimumWaveHeight = Random.NextDouble(),
                MaximumWaveHeight = Random.NextDouble(),
                WaveAngleImpact = Random.NextDouble(),
                WaveHeightImpact = Random.NextDouble()
            };
        }
    }
}