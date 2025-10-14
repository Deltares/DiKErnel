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

using System;
using System.Collections.Generic;
using DiKErnel.Core.Data;
using NSubstitute;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.Core.Test.Data
{
    [TestFixture]
    internal sealed class LocationDependentOutputTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            var timeDependentOutputItems = new List<TimeDependentOutput>();

            // Call
            var locationDependentOutput = Substitute.For<LocationDependentOutput>(Random.NextDouble(), Random.NextDouble(),
                                                                                  Array.Empty<ITimeDependentInput>(),
                                                                                  timeDependentOutputItems);

            // Assert
            Assert.That(locationDependentOutput.TimeDependentOutputItems, Is.SameAs(timeDependentOutputItems));
        }

        [Test]
        public void GivenLocationDependentOutput_ThenCumulativeDamagesHasExpectedValues()
        {
            // Given
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double incrementDamage1 = Random.NextDouble();
            double incrementDamage2 = Random.NextDouble();

            LocationDependentOutput locationDependentOutput =
                CreateLocationDependentOutput(initialDamage, failureNumber, Array.Empty<ITimeDependentInput>(), incrementDamage1,
                                              incrementDamage2);

            // Then
            Assert.That(locationDependentOutput.CumulativeDamages, Is.EqualTo(new[]
            {
                initialDamage + incrementDamage1,
                initialDamage + incrementDamage1 + incrementDamage2
            }));
        }

        [Test]
        [TestCase(0.2, 0.3, 0.5, 280)]
        [TestCase(0.2, 0.3, 0.2, 400)]
        [TestCase(0.2, 0.4, 0.1, 200)]
        [TestCase(0.2, 0.1, 0.2, null)]
        [TestCase(0.6, 0.1, 0.1, null)]
        public void GivenLocationDependentOutput_WhenGetTimeOfFailure_ThenExpectedValue(
            double initialDamage, double incrementDamage1, double incrementDamage2, double? expectedTimeOfFailure)
        {
            // Given
            const double failureNumber = 0.6;

            List<ITimeDependentInput> timeDependentInputItems = CreateTimeDependentInputItems();

            LocationDependentOutput locationDependentOutput =
                CreateLocationDependentOutput(initialDamage, failureNumber, timeDependentInputItems, incrementDamage1, incrementDamage2);

            // When
            double? timeOfFailure = locationDependentOutput.GetTimeOfFailure(initialDamage, failureNumber, timeDependentInputItems);

            // Then
            Assert.That(timeOfFailure, Is.EqualTo(expectedTimeOfFailure).Within(1.0e-13));
        }

        private static TestLocationDependentOutput CreateLocationDependentOutput(double initialDamage, double failureNumber,
                                                                                 IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                                                                 double incrementDamage1, double incrementDamage2)
        {
            var timeDependentOutputConstructionProperties1 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties1.IncrementDamage = incrementDamage1;

            var timeDependentOutputConstructionProperties2 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties2.IncrementDamage = incrementDamage2;

            var timeDependentOutputItems = new List<TimeDependentOutput>
            {
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties1),
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties2)
            };

            return new TestLocationDependentOutput(initialDamage, failureNumber, timeDependentInputItems, timeDependentOutputItems);
        }

        private static List<ITimeDependentInput> CreateTimeDependentInputItems()
        {
            var timeDependentInput1 = Substitute.For<ITimeDependentInput>();
            timeDependentInput1.BeginTime.Returns(0);
            timeDependentInput1.EndTime.Returns(200);

            var timeDependentInput2 = Substitute.For<ITimeDependentInput>();
            timeDependentInput2.BeginTime.Returns(200);
            timeDependentInput2.EndTime.Returns(600);

            return new List<ITimeDependentInput>
            {
                timeDependentInput1,
                timeDependentInput2
            };
        }

        private sealed class TestLocationDependentOutput : LocationDependentOutput
        {
            public TestLocationDependentOutput(double initialDamage, double failureNumber,
                                               IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                               IReadOnlyList<TimeDependentOutput> timeDependentOutputItems) :
                base(initialDamage, failureNumber, timeDependentInputItems, timeDependentOutputItems) {}
        }
    }
}