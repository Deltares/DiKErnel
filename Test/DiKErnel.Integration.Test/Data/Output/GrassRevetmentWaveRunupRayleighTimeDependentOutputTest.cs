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
using DiKErnel.Integration.Data.GrassRevetmentWaveRunup;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.Output
{
    [TestFixture]
    public class GrassRevetmentWaveRunupRayleighTimeDependentOutputTest
    {
        [Test]
        public void Constructor_WithAllValuesSet_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            int timeOfFailure = Random.Next();
            double verticalDistanceWaterLevelElevation = Random.NextDouble();
            double waveAngle = Random.NextDouble();
            double waveAngleImpact = Random.NextDouble();
            double representativeWaveRunup2P = Random.NextDouble();
            double cumulativeOverload = Random.NextDouble();
            double averageNumberOfWaves = Random.NextDouble();

            var constructionProperties = new GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = timeOfFailure,
                VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation,
                WaveAngle = waveAngle,
                WaveAngleImpact = waveAngleImpact,
                RepresentativeWaveRunup2P = representativeWaveRunup2P,
                CumulativeOverload = cumulativeOverload,
                AverageNumberOfWaves = averageNumberOfWaves
            };

            // Call
            var output = new GrassRevetmentWaveRunupRayleighTimeDependentOutput(constructionProperties);

            // Assert
            Assert.That(output, Is.InstanceOf<TimeDependentOutput>());
            Assert.That(output.IncrementDamage, Is.EqualTo(incrementDamage));
            Assert.That(output.Damage, Is.EqualTo(damage));
            Assert.That(output.TimeOfFailure, Is.EqualTo(timeOfFailure));
            Assert.That(output.VerticalDistanceWaterLevelElevation, Is.EqualTo(verticalDistanceWaterLevelElevation));
            Assert.That(output.WaveAngle, Is.EqualTo(waveAngle));
            Assert.That(output.WaveAngleImpact, Is.EqualTo(waveAngleImpact));
            Assert.That(output.RepresentativeWaveRunup2P, Is.EqualTo(representativeWaveRunup2P));
            Assert.That(output.CumulativeOverload, Is.EqualTo(cumulativeOverload));
            Assert.That(output.AverageNumberOfWaves, Is.EqualTo(averageNumberOfWaves));
        }

        [Test]
        public void Constructor_WithNullValues_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            double verticalDistanceWaterLevelElevation = Random.NextDouble();

            var constructionProperties = new GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation
            };

            // Call
            var output = new GrassRevetmentWaveRunupRayleighTimeDependentOutput(constructionProperties);

            // Assert
            Assert.That(output, Is.InstanceOf<TimeDependentOutput>());
            Assert.That(output.IncrementDamage, Is.EqualTo(incrementDamage));
            Assert.That(output.Damage, Is.EqualTo(damage));
            Assert.That(output.TimeOfFailure, Is.Null);
            Assert.That(output.VerticalDistanceWaterLevelElevation, Is.EqualTo(verticalDistanceWaterLevelElevation));
            Assert.That(output.WaveAngle, Is.Null);
            Assert.That(output.WaveAngleImpact, Is.Null);
            Assert.That(output.RepresentativeWaveRunup2P, Is.Null);
            Assert.That(output.CumulativeOverload, Is.Null);
            Assert.That(output.AverageNumberOfWaves, Is.Null);
        }

        [Test]
        public void Constructor_VerticalDistanceWaterLevelElevationNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            var constructionProperties = new GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties
            {
                IncrementDamage = Random.NextDouble(),
                Damage = Random.NextDouble(),
                TimeOfFailure = Random.Next(),
                VerticalDistanceWaterLevelElevation = null,
                WaveAngle = Random.NextDouble(),
                WaveAngleImpact = Random.NextDouble(),
                RepresentativeWaveRunup2P = Random.NextDouble(),
                CumulativeOverload = Random.NextDouble(),
                AverageNumberOfWaves = Random.NextDouble()
            };

            // Call
            void Call()
            {
                var output = new GrassRevetmentWaveRunupRayleighTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "VerticalDistanceWaterLevelElevation must be set.");
        }
    }
}