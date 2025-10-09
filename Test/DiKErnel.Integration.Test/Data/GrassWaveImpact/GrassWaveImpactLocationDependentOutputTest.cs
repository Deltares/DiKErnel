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
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.GrassWaveImpact
{
    [TestFixture]
    internal sealed class GrassWaveImpactLocationDependentOutputTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            double z = Random.NextDouble();
            double minimumWaveHeight = Random.NextDouble();
            double maximumWaveHeight = Random.NextDouble();
            var timeDependentOutputItems = new List<TimeDependentOutput>();

            // Call
            var output = new GrassWaveImpactLocationDependentOutput(timeDependentOutputItems, z, minimumWaveHeight,
                                                                    maximumWaveHeight);

            // Assert
            Assert.That(output, Is.InstanceOf<LocationDependentOutput>());
            Assert.That(output.TimeDependentOutputItems, Is.SameAs(timeDependentOutputItems));
            Assert.That(output.Z, Is.EqualTo(z));
            Assert.That(output.MinimumWaveHeight, Is.EqualTo(minimumWaveHeight));
            Assert.That(output.MaximumWaveHeight, Is.EqualTo(maximumWaveHeight));
        }
    }
}