// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.Core.Extensions;
using DiKErnel.TestUtil;
using NSubstitute;
using NUnit.Framework;

namespace DiKErnel.Core.Test.Extensions
{
    [TestFixture]
    public class LocationDependentOutputExtensionsTest
    {
        [Test]
        public void GivenLocationDependentOutput_WhenGetDamages_ThenExpectedValues()
        {
            // Given
            double damage1 = Random.NextDouble();
            double damage2 = Random.NextDouble();

            var timeDependentOutputConstructionProperties1 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties1.IncrementDamage = Random.NextDouble();
            timeDependentOutputConstructionProperties1.Damage = damage1;

            var timeDependentOutputConstructionProperties2 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties2.IncrementDamage = Random.NextDouble();
            timeDependentOutputConstructionProperties2.Damage = damage2;

            var timeDependentOutputItems = new List<TimeDependentOutput>
            {
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties1),
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties2)
            };

            var locationDependentOutput = Substitute.For<LocationDependentOutput>(timeDependentOutputItems);

            // When
            IReadOnlyList<double> damages = locationDependentOutput.GetDamages();

            // Then
            CollectionAssert.AreEqual(new[]
            {
                damage1,
                damage2
            }, damages);
        }

        [Test]
        [TestCase(true)]
        [TestCase(false)]
        public void GivenLocationDependentOutput_WhenGetTimeOfFailure_ThenExpectedValues(bool withTimeOfFailure)
        {
            // Given
            int? timeOfFailureInLastTimeStep = withTimeOfFailure ? Random.Next() : (int?) null;

            var timeDependentOutputConstructionProperties1 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties1.IncrementDamage = Random.NextDouble();
            timeDependentOutputConstructionProperties1.Damage = Random.NextDouble();

            var timeDependentOutputConstructionProperties2 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties2.IncrementDamage = Random.NextDouble();
            timeDependentOutputConstructionProperties2.Damage = Random.NextDouble();
            timeDependentOutputConstructionProperties2.TimeOfFailure = timeOfFailureInLastTimeStep;

            var timeDependentOutputItems = new List<TimeDependentOutput>
            {
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties1),
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties2)
            };

            var locationDependentOutput = Substitute.For<LocationDependentOutput>(timeDependentOutputItems);

            // When
            int? timeOfFailure = locationDependentOutput.GetTimeOfFailure();

            // Then
            Assert.AreEqual(timeOfFailureInLastTimeStep, timeOfFailure);
        }
    }
}