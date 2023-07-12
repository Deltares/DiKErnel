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

        [Test]
        public void CalculateZ2_WithInvalidData_ReturnsExpectedValue()
        {
            // Setup
            const double waterLevel = 1e-6;
            const double waveHeightHm0 = -0.361314622129615;
            const double wavePeriodTm10 = 45;
            const double waveDirection = 1.912229230397281e-12;

            const double dikeHeight = 3.7;
            var xCoordinates = new double[]
            {
                0,
                24
            };

            var zCoordinates = new double[]
            {
                -3,
                3
            };

            var roughnessCoefficients = new[]
            {
                1.0
            };

            // Call
            double z2 = OvertoppingAdapter.CalculateZ2(waterLevel, waveHeightHm0, wavePeriodTm10, waveDirection,
                                                       xCoordinates, zCoordinates, roughnessCoefficients, dikeHeight);

            // Assert
            Assert.Zero(z2);
        }

        [Test]
        public void CalculateZ2_WithValidData_ReturnsExpectedValue()
        {
            // Setup
            const double waterLevel = 5.5;
            const double waveHeightHm0 = 1;
            const double wavePeriodTm10 = 4;
            const double waveDirection = 50;

            const double dikeHeight = 9.1;
            var xCoordinates = new double[]
            {
                5,
                10,
                15
            };

            var zCoordinates = new double[]
            {
                5,
                7,
                9
            };

            var roughnessCoefficients = new double[]
            {
                1,
                1,
                1
            };

            // Call
            double z2 = OvertoppingAdapter.CalculateZ2(waterLevel, waveHeightHm0, wavePeriodTm10, waveDirection,
                                                       xCoordinates, zCoordinates, roughnessCoefficients, dikeHeight);

            // Assert
            Assert.NotZero(z2);
        }
    }
}