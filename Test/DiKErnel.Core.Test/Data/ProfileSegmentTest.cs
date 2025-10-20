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

using DiKErnel.Core.Data;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Core.Test.Data
{
    [TestFixture]
    internal sealed class ProfileSegmentTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            var startPoint = new ProfilePoint(Random.NextDouble(), Random.NextDouble());
            var endPoint = new ProfilePoint(Random.NextDouble(), Random.NextDouble());
            double roughnessCoefficient = Random.NextDouble();

            // Call
            var profileSegment = new ProfileSegment(startPoint, endPoint, roughnessCoefficient);

            // Assert
            Assert.That(profileSegment.StartPoint, Is.SameAs(startPoint));
            Assert.That(profileSegment.EndPoint, Is.SameAs(endPoint));
            Assert.That(profileSegment.RoughnessCoefficient, Is.EqualTo(roughnessCoefficient));
        }
    }
}