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

using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.Core.Extensions;
using DiKErnel.TestUtil;
using NSubstitute;
using NUnit.Framework;

namespace DiKErnel.Core.Test.Extensions
{
    [TestFixture]
    internal sealed class LocationDependentOutputExtensionsTest
    {
        [Test]
        public void GivenLocationDependentOutput_WhenGetDamages_ThenExpectedValues()
        {
            // Given
            double initialDamage = Random.NextDouble();
            double incrementDamage1 = Random.NextDouble();
            double incrementDamage2 = Random.NextDouble();

            var timeDependentOutputConstructionProperties1 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties1.IncrementDamage = Random.NextDouble();
            timeDependentOutputConstructionProperties1.Damage = incrementDamage1;

            var timeDependentOutputConstructionProperties2 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties2.IncrementDamage = Random.NextDouble();
            timeDependentOutputConstructionProperties2.Damage = incrementDamage2;

            var timeDependentOutputItems = new List<TimeDependentOutput>
            {
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties1),
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties2)
            };

            var locationDependentOutput = Substitute.For<LocationDependentOutput>(timeDependentOutputItems);

            // When
            IReadOnlyList<double> damages = locationDependentOutput.GetDamages(initialDamage);

            // Then
            Assert.That(damages, Is.EqualTo(new[]
            {
                initialDamage + incrementDamage1,
                initialDamage + incrementDamage1 + incrementDamage2
            }));
        }

        [Test]
        [TestCase(true)]
        [TestCase(false)]
        public void GivenLocationDependentOutputWithDamagesNotEqualToNaN_WhenGetTimeOfFailure_ThenReturnsExpectedValue(
            bool withTimeOfFailure)
        {
            // Given
            double? timeOfFailureInSecondTimeStep = withTimeOfFailure ? Random.NextDouble() : (double?) null;

            var timeDependentOutputConstructionProperties1 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties1.IncrementDamage = Random.NextDouble();
            timeDependentOutputConstructionProperties1.Damage = Random.NextDouble();

            var timeDependentOutputConstructionProperties2 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties2.IncrementDamage = Random.NextDouble();
            timeDependentOutputConstructionProperties2.Damage = Random.NextDouble();
            timeDependentOutputConstructionProperties2.TimeOfFailure = timeOfFailureInSecondTimeStep;

            var timeDependentOutputConstructionProperties3 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties3.IncrementDamage = Random.NextDouble();
            timeDependentOutputConstructionProperties3.Damage = Random.NextDouble();

            var timeDependentOutputItems = new List<TimeDependentOutput>
            {
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties1),
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties2),
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties3)
            };

            var locationDependentOutput = Substitute.For<LocationDependentOutput>(timeDependentOutputItems);

            // When
            double? timeOfFailure = locationDependentOutput.GetTimeOfFailure();

            // Then
            Assert.That(timeOfFailure, Is.EqualTo(timeOfFailureInSecondTimeStep));
        }

        [Test]
        public void GivenLocationDependentOutputWithOneDamageEqualToNaN_WhenGetTimeOfFailure_ThenReturnsNull()
        {
            // Given
            var timeDependentOutputConstructionProperties1 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties1.IncrementDamage = Random.NextDouble();
            timeDependentOutputConstructionProperties1.Damage = Random.NextDouble();

            var timeDependentOutputConstructionProperties2 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties2.IncrementDamage = Random.NextDouble();
            timeDependentOutputConstructionProperties2.Damage = Random.NextDouble();
            timeDependentOutputConstructionProperties2.TimeOfFailure = Random.NextDouble();

            var timeDependentOutputConstructionProperties3 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties3.IncrementDamage = Random.NextDouble();
            timeDependentOutputConstructionProperties3.Damage = double.NaN;

            var timeDependentOutputItems = new List<TimeDependentOutput>
            {
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties1),
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties2),
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties3)
            };

            var locationDependentOutput = Substitute.For<LocationDependentOutput>(timeDependentOutputItems);

            // When
            double? timeOfFailure = locationDependentOutput.GetTimeOfFailure();

            // Then
            Assert.That(timeOfFailure, Is.Null);
        }
    }
}