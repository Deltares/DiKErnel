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
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.GrassWaveRunup
{
    [TestFixture]
    public class GrassWaveRunupBattjesGroenendijkAnalyticalTimeDependentOutputConstructionPropertiesTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Call
            var constructionProperties =
                new GrassWaveRunupBattjesGroenendijkAnalyticalTimeDependentOutputConstructionProperties();

            // Assert
            Assert.That(constructionProperties, Is.InstanceOf<TimeDependentOutputConstructionProperties>());
            Assert.That(constructionProperties.AverageNumberOfWaves, Is.Null);
            Assert.That(constructionProperties.IncrementDamage, Is.Null);
            Assert.That(constructionProperties.Damage, Is.Null);
            Assert.That(constructionProperties.TimeOfFailure, Is.Null);
            Assert.That(constructionProperties.VerticalDistanceWaterLevelElevation, Is.Null);
            Assert.That(constructionProperties.RepresentativeWaveRunup2P, Is.Null);
            Assert.That(constructionProperties.CumulativeOverload, Is.Null);
        }

        [Test]
        public void GivenConstructionProperties_WhenAllValuesSet_ThenExpectedValues()
        {
            // Given
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            double timeOfFailure = Random.NextDouble();
            double verticalDistanceWaterLevelElevation = Random.NextDouble();
            double representativeWaveRunup2P = Random.NextDouble();
            double cumulativeOverload = Random.NextDouble();
            double averageNumberOfWaves = Random.NextDouble();

            // When
            var constructionProperties =
                new GrassWaveRunupBattjesGroenendijkAnalyticalTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = incrementDamage,
                    Damage = damage,
                    TimeOfFailure = timeOfFailure,
                    VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation,
                    RepresentativeWaveRunup2P = representativeWaveRunup2P,
                    CumulativeOverload = cumulativeOverload,
                    AverageNumberOfWaves = averageNumberOfWaves
                };

            // Then
            Assert.That(constructionProperties.IncrementDamage, Is.EqualTo(incrementDamage));
            Assert.That(constructionProperties.Damage, Is.EqualTo(damage));
            Assert.That(constructionProperties.TimeOfFailure, Is.EqualTo(timeOfFailure));
            Assert.That(constructionProperties.VerticalDistanceWaterLevelElevation, Is.EqualTo(verticalDistanceWaterLevelElevation));
            Assert.That(constructionProperties.RepresentativeWaveRunup2P, Is.EqualTo(representativeWaveRunup2P));
            Assert.That(constructionProperties.CumulativeOverload, Is.EqualTo(cumulativeOverload));
            Assert.That(constructionProperties.AverageNumberOfWaves, Is.EqualTo(averageNumberOfWaves));
        }
    }
}