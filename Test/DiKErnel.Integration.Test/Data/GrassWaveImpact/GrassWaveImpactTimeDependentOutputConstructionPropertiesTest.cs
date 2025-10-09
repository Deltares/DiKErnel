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
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.GrassWaveImpact
{
    [TestFixture]
    internal sealed class GrassWaveImpactTimeDependentOutputConstructionPropertiesTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Call
            var constructionProperties = new GrassWaveImpactTimeDependentOutputConstructionProperties();

            // Assert
            Assert.That(constructionProperties, Is.InstanceOf<TimeDependentOutputConstructionProperties>());
            Assert.That(constructionProperties.IncrementDamage, Is.Null);
            Assert.That(constructionProperties.Damage, Is.Null);
            Assert.That(constructionProperties.TimeOfFailure, Is.Null);
            Assert.That(constructionProperties.LoadingRevetment, Is.Null);
            Assert.That(constructionProperties.UpperLimitLoading, Is.Null);
            Assert.That(constructionProperties.LowerLimitLoading, Is.Null);
            Assert.That(constructionProperties.WaveAngle, Is.Null);
            Assert.That(constructionProperties.WaveAngleImpact, Is.Null);
            Assert.That(constructionProperties.WaveHeightImpact, Is.Null);
        }

        [Test]
        public void GivenConstructionProperties_WhenAllValuesSet_ThenExpectedValues()
        {
            // Given
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            double timeOfFailure = Random.NextDouble();
            bool loadingRevetment = Random.NextBoolean();
            double upperLimitLoading = Random.NextDouble();
            double lowerLimitLoading = Random.NextDouble();
            double waveAngle = Random.NextDouble();
            double waveAngleImpact = Random.NextDouble();
            double waveHeightImpact = Random.NextDouble();

            // When
            var constructionProperties = new GrassWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = timeOfFailure,
                LoadingRevetment = loadingRevetment,
                UpperLimitLoading = upperLimitLoading,
                LowerLimitLoading = lowerLimitLoading,
                WaveAngle = waveAngle,
                WaveAngleImpact = waveAngleImpact,
                WaveHeightImpact = waveHeightImpact
            };

            // Then
            Assert.That(constructionProperties.IncrementDamage, Is.EqualTo(incrementDamage));
            Assert.That(constructionProperties.Damage, Is.EqualTo(damage));
            Assert.That(constructionProperties.TimeOfFailure, Is.EqualTo(timeOfFailure));
            Assert.That(constructionProperties.LoadingRevetment, Is.EqualTo(loadingRevetment));
            Assert.That(constructionProperties.UpperLimitLoading, Is.EqualTo(upperLimitLoading));
            Assert.That(constructionProperties.LowerLimitLoading, Is.EqualTo(lowerLimitLoading));
            Assert.That(constructionProperties.WaveAngle, Is.EqualTo(waveAngle));
            Assert.That(constructionProperties.WaveAngleImpact, Is.EqualTo(waveAngleImpact));
            Assert.That(constructionProperties.WaveHeightImpact, Is.EqualTo(waveHeightImpact));
        }
    }
}