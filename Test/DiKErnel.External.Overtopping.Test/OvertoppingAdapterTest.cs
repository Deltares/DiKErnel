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
using NUnit.Framework;

namespace DiKErnel.External.Overtopping.Test
{
    [TestFixture]
    internal sealed class OvertoppingAdapterTest
    {
        [Test]
        public void Validate_WithInvalidData_ReturnsNonEmptyMessages()
        {
            // Setup
            const double dikeHeight = 9.1;
            const double dikeOrientation = 0;

            double[] xCoordinates =
            {
                0,
                10,
                20,
                30,
                40
            };

            double[] zCoordinates =
            {
                -5,
                0,
                5,
                4,
                0
            };

            double[] roughnessCoefficients =
            {
                0.5,
                0.5,
                0.5,
                0.5
            };

            // Call
            IReadOnlyList<string> messages = OvertoppingAdapter.Validate(xCoordinates, zCoordinates, roughnessCoefficients,
                                                                         dikeHeight, dikeOrientation);

            // Assert
            Assert.That(messages, Is.Not.Empty);
        }

        [Test]
        public void Validate_WithValidData_ReturnsEmptyMessages()
        {
            // Setup
            const double dikeHeight = 9.1;
            const double dikeOrientation = 0;

            double[] xCoordinates =
            {
                0,
                10,
                20,
                30,
                40
            };

            double[] zCoordinates =
            {
                -5,
                0,
                5,
                10,
                20
            };

            double[] roughnessCoefficients =
            {
                0.5,
                0.5,
                0.5,
                0.5
            };

            // Call
            IReadOnlyList<string> messages = OvertoppingAdapter.Validate(xCoordinates, zCoordinates, roughnessCoefficients,
                                                                         dikeHeight, dikeOrientation);

            // Assert
            Assert.That(messages, Is.Empty);
        }

        [Test]
        public void CalculateZ2_WithInvalidData_ReturnsZeroValue()
        {
            // Setup
            const double waterLevel = 1e-6;
            const double waveHeightHm0 = -0.361314622129615;
            const double wavePeriodTm10 = 45;
            const double waveDirection = 1.912229230397281e-12;

            const double dikeHeight = 3.7;
            const double dikeOrientation = 0;

            double[] xCoordinates =
            {
                0,
                24
            };

            double[] zCoordinates =
            {
                -3,
                3
            };

            double[] roughnessCoefficients =
            {
                1
            };

            // Call
            double z2 = OvertoppingAdapter.CalculateZ2(waterLevel, waveHeightHm0, wavePeriodTm10, waveDirection, xCoordinates,
                                                       zCoordinates, roughnessCoefficients, dikeHeight, dikeOrientation);

            // Assert
            Assert.That(z2, Is.Zero);
        }

        [Test]
        public void CalculateZ2_WithValidData_ReturnsNonZeroValue()
        {
            // Setup
            const double waterLevel = 5.5;
            const double waveHeightHm0 = 1;
            const double wavePeriodTm10 = 4;
            const double waveDirection = 50;

            const double dikeHeight = 9.1;
            const double dikeOrientation = 0;

            double[] xCoordinates =
            {
                5,
                10,
                15
            };

            double[] zCoordinates =
            {
                5,
                7,
                9
            };

            double[] roughnessCoefficients =
            {
                1,
                1,
                1
            };

            // Call
            double z2 = OvertoppingAdapter.CalculateZ2(waterLevel, waveHeightHm0, wavePeriodTm10, waveDirection, xCoordinates,
                                                       zCoordinates, roughnessCoefficients, dikeHeight, dikeOrientation);

            // Assert
            Assert.That(z2, Is.Not.Zero);
        }
    }
}