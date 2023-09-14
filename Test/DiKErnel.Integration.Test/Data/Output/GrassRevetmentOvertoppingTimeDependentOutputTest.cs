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
using DiKErnel.Integration.Data.GrassRevetmentOvertopping;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.Output
{
    [TestFixture]
    public class GrassRevetmentOvertoppingTimeDependentOutputTest
    {
        [Test]
        public void Constructor_WithAllValuesSet_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            int timeOfFailure = Random.Next();
            double verticalDistanceWaterLevelElevation = Random.NextDouble();
            double representativeWaveRunup2P = Random.NextDouble();
            double cumulativeOverload = Random.NextDouble();

            var constructionProperties = new GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = timeOfFailure,
                VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation,
                RepresentativeWaveRunup2P = representativeWaveRunup2P,
                CumulativeOverload = cumulativeOverload
            };

            // Call
            var output = new GrassRevetmentOvertoppingTimeDependentOutput(constructionProperties);

            // Assert
            Assert.IsInstanceOf<TimeDependentOutput>(output);
            Assert.AreEqual(incrementDamage, output.IncrementDamage);
            Assert.AreEqual(damage, output.Damage);
            Assert.AreEqual(timeOfFailure, output.TimeOfFailure);
            Assert.AreEqual(verticalDistanceWaterLevelElevation, output.VerticalDistanceWaterLevelElevation);
            Assert.AreEqual(representativeWaveRunup2P, output.RepresentativeWaveRunup2P);
            Assert.AreEqual(cumulativeOverload, output.CumulativeOverload);
        }

        [Test]
        public void Constructor_WithNullValues_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            double verticalDistanceWaterLevelElevation = Random.NextDouble();

            var constructionProperties = new GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation
            };

            // Call
            var output = new GrassRevetmentOvertoppingTimeDependentOutput(constructionProperties);

            // Assert
            Assert.IsInstanceOf<TimeDependentOutput>(output);
            Assert.AreEqual(incrementDamage, output.IncrementDamage);
            Assert.AreEqual(damage, output.Damage);
            Assert.IsNull(output.TimeOfFailure);
            Assert.AreEqual(verticalDistanceWaterLevelElevation, output.VerticalDistanceWaterLevelElevation);
            Assert.IsNull(output.RepresentativeWaveRunup2P);
            Assert.IsNull(output.CumulativeOverload);
        }

        [Test]
        public void ConstructorVerticalDistanceWaterLevelElevationNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            var constructionProperties = new GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties
            {
                IncrementDamage = Random.NextDouble(),
                Damage = Random.NextDouble(),
                TimeOfFailure = Random.Next(),
                VerticalDistanceWaterLevelElevation = null,
                RepresentativeWaveRunup2P = Random.NextDouble(),
                CumulativeOverload = Random.NextDouble()
            };

            // Call
            void Call()
            {
                var output = new GrassRevetmentOvertoppingTimeDependentOutput(constructionProperties);
            }

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "verticalDistanceWaterLevelElevation must be set.");
        }
    }
}