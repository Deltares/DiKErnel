// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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
using System.Linq;
using NUnit.Framework;

namespace DiKErnel.External.Overtopping.Test
{
    [TestFixture]
    public class OvertoppingAdapterTest
    {
        [Test]
        public void Validate_WithInvalidData_ReturnsMessages()
        {
            // Setup
            const double dikeHeight = 9.1;
            var xCoordinates = new double[]
            {
                0,
                10,
                20,
                30,
                40
            };

            var zCoordinates = new double[]
            {
                -5,
                0,
                5,
                4,
                0
            };

            var roughnessCoefficients = new[]
            {
                0.5,
                0.5,
                0.5,
                0.5
            };

            // Call
            IEnumerable<string> messages = OvertoppingAdapter.Validate(xCoordinates, zCoordinates, roughnessCoefficients, dikeHeight);

            // Assert
            Assert.IsTrue(messages.Any());
        }

        [Test]
        public void Validate_WithValidData_ReturnsEmptyMessages()
        {
            // Setup
            const double dikeHeight = 9.1;
            var xCoordinates = new double[]
            {
                0,
                10,
                20,
                30,
                40
            };

            var zCoordinates = new double[]
            {
                -5,
                0,
                5,
                10,
                20
            };

            var roughnessCoefficients = new[]
            {
                0.5,
                0.5,
                0.5,
                0.5
            };

            // Call
            IEnumerable<string> messages = OvertoppingAdapter.Validate(xCoordinates, zCoordinates, roughnessCoefficients, dikeHeight);

            // Assert
            Assert.IsFalse(messages.Any());
        }
    }
}