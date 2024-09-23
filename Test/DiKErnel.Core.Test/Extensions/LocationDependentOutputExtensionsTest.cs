﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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
    public class LocationDependentOutputExtensionsTest
    {
        [Test]
        public void GivenLocationDependentOutput_WhenGetDamages_ThenExpectedValues()
        {
            // Given
            double initialDamage = Random.NextDouble();
            double incrementDamage1 = Random.NextDouble();
            double incrementDamage2 = Random.NextDouble();

            var timeDependentOutputConstructionProperties1 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties1.IncrementDamage = incrementDamage1;

            var timeDependentOutputConstructionProperties2 = Substitute.For<TimeDependentOutputConstructionProperties>();
            timeDependentOutputConstructionProperties2.IncrementDamage = incrementDamage2;

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
    }
}