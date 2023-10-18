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
using DiKErnel.Integration.Data.GrassRevetmentWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.Output
{
    [TestFixture]
    public class GrassRevetmentWaveImpactTimeDependentOutputConstructionPropertiesTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Call
            var constructionProperties = new GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties();

            // Assert
            Assert.IsInstanceOf<TimeDependentOutputConstructionProperties>(constructionProperties);
            Assert.IsNull(constructionProperties.IncrementDamage);
            Assert.IsNull(constructionProperties.Damage);
            Assert.IsNull(constructionProperties.TimeOfFailure);
            Assert.IsNull(constructionProperties.LoadingRevetment);
            Assert.IsNull(constructionProperties.UpperLimitLoading);
            Assert.IsNull(constructionProperties.LowerLimitLoading);
            Assert.IsNull(constructionProperties.MinimumWaveHeight);
            Assert.IsNull(constructionProperties.MaximumWaveHeight);
            Assert.IsNull(constructionProperties.WaveAngle);
            Assert.IsNull(constructionProperties.WaveAngleImpact);
            Assert.IsNull(constructionProperties.WaveHeightImpact);
        }

        [Test]
        public void GivenConstructionProperties_WhenAllValuesSet_ThenExpectedValues()
        {
            // Given
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            int timeOfFailure = Random.Next();
            bool loadingRevetment = Random.NextBoolean();
            double upperLimitLoading = Random.NextDouble();
            double lowerLimitLoading = Random.NextDouble();
            double minimumWaveHeight = Random.NextDouble();
            double maximumWaveHeight = Random.NextDouble();
            double waveAngle = Random.NextDouble();
            double waveAngleImpact = Random.NextDouble();
            double waveHeightImpact = Random.NextDouble();

            // When
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
                WaveAngle = waveAngle,
                WaveAngleImpact = waveAngleImpact,
                WaveHeightImpact = waveHeightImpact
            };

            // Then
            Assert.AreEqual(incrementDamage, constructionProperties.IncrementDamage);
            Assert.AreEqual(damage, constructionProperties.Damage);
            Assert.AreEqual(timeOfFailure, constructionProperties.TimeOfFailure);
            Assert.AreEqual(loadingRevetment, constructionProperties.LoadingRevetment);
            Assert.AreEqual(upperLimitLoading, constructionProperties.UpperLimitLoading);
            Assert.AreEqual(lowerLimitLoading, constructionProperties.LowerLimitLoading);
            Assert.AreEqual(minimumWaveHeight, constructionProperties.MinimumWaveHeight);
            Assert.AreEqual(maximumWaveHeight, constructionProperties.MaximumWaveHeight);
            Assert.AreEqual(waveAngle, constructionProperties.WaveAngle);
            Assert.AreEqual(waveAngleImpact, constructionProperties.WaveAngleImpact);
            Assert.AreEqual(waveHeightImpact, constructionProperties.WaveHeightImpact);
        }
    }
}