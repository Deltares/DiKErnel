﻿// // Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
// //
// // This file is part of DiKErnel.
// //
// // DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// // GNU Lesser General Public License as published by the Free Software Foundation, either
// // version 3 of the License, or (at your option) any later version.
// //
// // This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// // without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// // See the GNU Lesser General Public License for more details.
// //
// // You should have received a copy of the GNU Lesser General Public License along with this
// // program. If not, see <http://www.gnu.org/licenses/>.
// //
// // All names, logos, and references to "Deltares" are registered trademarks of Stichting
// // Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using DiKErnel.FunctionLibrary.AsphaltRevetmentWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.AsphaltRevetmentWaveImpact
{
    [TestFixture]
    public class AsphaltRevetmentWaveImpactFunctionsTest
    {
        [Test]
        public void IncrementDamage_ValidInput_ExpectedValue()
        {
            // Setup
            var widthFactors = new[]
            {
                (0.1, 0.0392),
                (0.2, 0.0738),
                (0.3, 0.1002),
                (0.4, 0.1162),
                (0.5, 0.1213),
                (0.6, 0.1168),
                (0.7, 0.1051),
                (0.8, 0.089),
                (0.9, 0.0712),
                (1.0, 0.0541),
                (1.1, 0.0391),
                (1.2, 0.0269),
                (1.3, 0.0216),
                (1.4, 0.015),
                (1.5, 0.0105)
            };

            var depthFactors = new[]
            {
                (-1.0, 0.0244),
                (-0.875, 0.0544),
                (-0.75, 0.0938),
                (-0.625, 0.1407),
                (-0.5, 0.1801),
                (-0.375, 0.1632),
                (-0.25, 0.1426),
                (-0.125, 0.0994),
                (0.0, 0.06),
                (0.125, 0.0244),
                (0.25, 0.0169)
            };

            var impactFactors = new[]
            {
                (2.0, 0.039),
                (2.4, 0.1),
                (2.8, 0.18),
                (3.2, 0.235),
                (3.6, 0.2),
                (4.0, 0.13),
                (4.4, 0.08),
                (4.8, 0.02),
                (5.2, 0.01),
                (5.6, 0.005),
                (6.0, 0.001)
            };

            const double logFailureTension = 0.193124598;
            const double averageNumberOfWaves = 6492.937853;
            const double maximumPeakStress = 0.0160884;
            const double stiffnessRelation = 1.185626183;
            const double computationalThickness = 0.16;
            const double outerSlope = 0.232914161;

            const double z = 2.988;
            const double waterLevel = 3.8;
            const double waveHeightHm0 = 1.6;
            const double fatigueAlpha = 0.42;
            const double fatigueBeta = 4.76;
            const double impactNumberC = 1.0;

            var input = new AsphaltRevetmentWaveImpactFunctionsInput(logFailureTension, averageNumberOfWaves, maximumPeakStress,
                                                                     stiffnessRelation, computationalThickness, outerSlope,
                                                                     widthFactors, depthFactors, impactFactors, z, waterLevel,
                                                                     waveHeightHm0, fatigueAlpha, fatigueBeta, impactNumberC);

            // Call
            double incrementDamage = AsphaltRevetmentWaveImpactFunctions.IncrementDamage(input);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(7.94813500019044, incrementDamage);
        }
    }
}