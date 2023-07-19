﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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
        public void GivenLocationDependentOutputWithDamages_WhenGetDamages_ThenExpectedValues()
        {
            // Given
            double damage1 = Random.NextDouble();
            double damage2 = Random.NextDouble();

            var timeDependentOutputItems = new List<TimeDependentOutput>
            {
                Substitute.For<TimeDependentOutput>(Random.NextDouble(), damage1, null),
                Substitute.For<TimeDependentOutput>(Random.NextDouble(), damage2, null)
            };

            var locationDependentOutput = Substitute.For<LocationDependentOutput>(timeDependentOutputItems);

            // When
            IEnumerable<double> damages = locationDependentOutput.GetDamages();

            // Then
            CollectionAssert.AreEqual(new[]
            {
                damage1,
                damage2
            }, damages);
        }

        [Test]
        public void GivenLocationDependentOutputWithTimeOfFailure_WhenGetTimeOfFailure_ThenExpectedValues()
        {
            // Given
            int timeOfFailureForTimeStep = Random.Next();

            var timeDependentOutputItems = new List<TimeDependentOutput>
            {
                Substitute.For<TimeDependentOutput>(Random.NextDouble(), Random.NextDouble(), null),
                Substitute.For<TimeDependentOutput>(Random.NextDouble(), Random.NextDouble(), timeOfFailureForTimeStep)
            };

            var locationDependentOutput = Substitute.For<LocationDependentOutput>(timeDependentOutputItems);

            // When
            int? timeOfFailure = locationDependentOutput.GetTimeOfFailure();

            // Then
            Assert.AreEqual(timeOfFailureForTimeStep, timeOfFailure);
        }

        [Test]
        public void GivenLocationDependentOutputWithoutTimeOfFailure_WhenGetTimeOfFailure_ThenExpectedValues()
        {
            // Given
            var timeDependentOutputItems = new List<TimeDependentOutput>
            {
                Substitute.For<TimeDependentOutput>(Random.NextDouble(), Random.NextDouble(), null),
                Substitute.For<TimeDependentOutput>(Random.NextDouble(), Random.NextDouble(), null)
            };

            var locationDependentOutput = Substitute.For<LocationDependentOutput>(timeDependentOutputItems);

            // When
            int? timeOfFailure = locationDependentOutput.GetTimeOfFailure();

            // Then
            Assert.IsNull(timeOfFailure);
        }
    }
}