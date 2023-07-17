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
using DiKErnel.TestUtil;
using NSubstitute;
using NUnit.Framework;

namespace DiKErnel.Core.Test.Data
{
    [TestFixture]
    public class LocationDependentOutputTest
    {
        [Test]
        public void Constructor_WithTimeOfFailure_ExpectedValues()
        {
            // Setup
            double damage1 = Random.NextDouble();
            double damage2 = Random.NextDouble();
            int timeOfFailure = Random.Next();

            var timeDependentOutputItems = new List<TimeDependentOutput>
            {
                Substitute.For<TimeDependentOutput>(Random.NextDouble(), damage1, null),
                Substitute.For<TimeDependentOutput>(Random.NextDouble(), damage2, timeOfFailure)
            };

            // Call
            var locationDependentOutput = Substitute.For<LocationDependentOutput>(timeDependentOutputItems);

            // Assert
            Assert.AreSame(timeDependentOutputItems, locationDependentOutput.TimeDependentOutputItems);
            CollectionAssert.AreEqual(new[]
            {
                damage1,
                damage2
            }, locationDependentOutput.Damages);
            Assert.AreEqual(timeOfFailure, locationDependentOutput.TimeOfFailure);
        }

        [Test]
        public void Constructor_WithoutTimeOfFailure_ExpectedValues()
        {
            // Setup
            double damage1 = Random.NextDouble();
            double damage2 = Random.NextDouble();

            var timeDependentOutputItems = new List<TimeDependentOutput>
            {
                Substitute.For<TimeDependentOutput>(Random.NextDouble(), damage1, null),
                Substitute.For<TimeDependentOutput>(Random.NextDouble(), damage2, null)
            };

            // Call
            var locationDependentOutput = Substitute.For<LocationDependentOutput>(timeDependentOutputItems);

            // Assert
            Assert.AreSame(timeDependentOutputItems, locationDependentOutput.TimeDependentOutputItems);
            CollectionAssert.AreEqual(new[]
            {
                damage1,
                damage2
            }, locationDependentOutput.Damages);
            Assert.IsNull(locationDependentOutput.TimeOfFailure);
        }
    }
}