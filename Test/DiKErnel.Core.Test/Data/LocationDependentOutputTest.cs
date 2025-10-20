// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
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
            double incrementDamage4 = Random.NextDouble();

            LocationDependentOutput locationDependentOutput =
                CreateLocationDependentOutput(initialDamage, failureNumber, Array.Empty<ITimeDependentInput>(), incrementDamage1,
                                              incrementDamage2, double.NaN, incrementDamage4);

            // Then
            Assert.That(locationDependentOutput.CumulativeDamages, Is.EqualTo(new[]
            {
                initialDamage + incrementDamage1,
                initialDamage + incrementDamage1 + incrementDamage2,
                initialDamage + incrementDamage1 + incrementDamage2,
                initialDamage + incrementDamage1 + incrementDamage2 + incrementDamage4
            }));
        }

        [Test]
        [TestCase(0.2, 0.3, 0.5, double.NaN, 0.4, 280)]
        [TestCase(0.2, 0.1, 0.2, double.NaN, 0.4, 750)]
        [TestCase(0.2, 0.4, 0.2, double.NaN, 0.4, 200)]
        [TestCase(0.2, 0.1, 0.1, double.NaN, 0.1, null)]
        [TestCase(0.6, 0.3, 0.2, double.NaN, 0.1, null)]
        public void GivenLocationDependentOutput_ThenTimeOfFailureHasExpectedValue(
            double initialDamage, double incrementDamage1, double incrementDamage2, double incrementDamage3, double incrementDamage4,
            double? expectedTimeOfFailure)
        {
            // Given
            const double failureNumber = 0.6;

            List<ITimeDependentInput> timeDependentInputItems = CreateTimeDependentInputItems();

            LocationDependentOutput locationDependentOutput =
                CreateLocationDependentOutput(initialDamage, failureNumber, timeDependentInputItems, incrementDamage1, incrementDamage2,
                                              incrementDamage3, incrementDamage4);

            // Then
            Assert.That(locationDependentOutput.TimeOfFailure, Is.EqualTo(expectedTimeOfFailure).Within(1.0e-13));
        }

        private static TestLocationDependentOutput CreateLocationDependentOutput(double initialDamage, double failureNumber,
                                                                                 IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                                                                 double incrementDamage1, double incrementDamage2,
                                                                                 double incrementDamage3, double incrementDamage4)
        {
            var timeDependentOutputConstructionProperties1 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties1.IncrementDamage = incrementDamage1;

            var timeDependentOutputConstructionProperties2 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties2.IncrementDamage = incrementDamage2;

            var timeDependentOutputConstructionProperties3 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties3.IncrementDamage = incrementDamage3;

            var timeDependentOutputConstructionProperties4 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties4.IncrementDamage = incrementDamage4;

            var timeDependentOutputItems = new List<TimeDependentOutput>
            {
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties1),
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties2),
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties3),
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties4)
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

            var timeDependentInput3 = Substitute.For<ITimeDependentInput>();
            timeDependentInput3.BeginTime.Returns(600);
            timeDependentInput3.EndTime.Returns(700);

            var timeDependentInput4 = Substitute.For<ITimeDependentInput>();
            timeDependentInput4.BeginTime.Returns(700);
            timeDependentInput4.EndTime.Returns(900);

            return new List<ITimeDependentInput>
            {
                timeDependentInput1,
                timeDependentInput2,
                timeDependentInput3,
                timeDependentInput4
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