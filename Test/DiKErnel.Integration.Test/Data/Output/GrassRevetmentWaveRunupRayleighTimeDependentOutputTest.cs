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
using NSubstitute.ExceptionExtensions;
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
                WaveAngleImpact = waveAngleImpact,
                RepresentativeWaveRunup2P = representativeWaveRunup2P,
                CumulativeOverload = cumulativeOverload,
                AverageNumberOfWaves = averageNumberOfWaves
            };

            // Call
            var output = new GrassRevetmentWaveRunupRayleighTimeDependentOutput(constructionProperties);

            // Assert
            Assert.IsInstanceOf<TimeDependentOutput>(output);
            Assert.AreEqual(incrementDamage, output.IncrementDamage);
            Assert.AreEqual(damage, output.Damage);
            Assert.AreEqual(timeOfFailure, output.TimeOfFailure);
            Assert.AreEqual(verticalDistanceWaterLevelElevation, output.VerticalDistanceWaterLevelElevation);
            Assert.AreEqual(waveAngleImpact, output.WaveAngleImpact);
            Assert.AreEqual(representativeWaveRunup2P, output.RepresentativeWaveRunup2P);
            Assert.AreEqual(cumulativeOverload, output.CumulativeOverload);
            Assert.AreEqual(averageNumberOfWaves, output.AverageNumberOfWaves);
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
            Assert.IsInstanceOf<TimeDependentOutput>(output);
            Assert.AreEqual(incrementDamage, output.IncrementDamage);
            Assert.AreEqual(damage, output.Damage);
            Assert.IsNull(output.TimeOfFailure);
            Assert.AreEqual(verticalDistanceWaterLevelElevation, output.VerticalDistanceWaterLevelElevation);
            Assert.IsNull(output.WaveAngleImpact);
            Assert.IsNull(output.RepresentativeWaveRunup2P);
            Assert.IsNull(output.CumulativeOverload);
            Assert.IsNull(output.AverageNumberOfWaves);
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
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "verticalDistanceWaterLevelElevation must be set.");
        }
    }
}