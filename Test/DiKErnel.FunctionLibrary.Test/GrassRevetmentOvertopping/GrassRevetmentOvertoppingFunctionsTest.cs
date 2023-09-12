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

using DiKErnel.FunctionLibrary.GrassRevetmentOvertopping;
using DiKErnel.FunctionLibrary.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassRevetmentOvertopping
{
    [TestFixture]
    public class GrassRevetmentOvertoppingFunctionsTest
    {
        [Test]
        public void RepresentativeWaveRunup2P_ValidInput_ExpectedValue()
        {
            // Setup
            const double waterLevel = 5.5;
            const double waveHeightHm0 = 1.9;
            const double wavePeriodTm10 = 4.7;
            const double waveDirection = 350;

            double[] xValuesProfile =
            {
                5,
                15,
                22,
                30
            };

            double[] zValuesProfile =
            {
                0,
                3,
                3.2,
                7.5
            };

            double[] roughnessCoefficients =
            {
                1,
                0.75,
                0.5
            };

            const double dikeHeight = 7.7;

            var input = new GrassRevetmentOvertoppingRepresentative2PInput(waterLevel, waveHeightHm0, wavePeriodTm10,
                                                                           waveDirection, xValuesProfile, zValuesProfile,
                                                                           roughnessCoefficients, dikeHeight);

            // Call
            double representativeWaveRunup2P = GrassRevetmentOvertoppingFunctions.RepresentativeWaveRunup2P(input);

            // Assert
            AssertHelper.AreEqual(2.79696767501212, representativeWaveRunup2P);
        }

        [Test]
        public void CumulativeOverload_ValidInput_ExpectedValue()
        {
            // Setup
            const double averageNumberOfWaves = 832.56;
            const double representativeWaveRunup2P = 2.602;
            const int fixedNumberOfWaves = 10000;
            const double verticalDistanceWaterLevelElevation = 2.2;
            const double criticalFrontVelocity = 6.6;
            const double increasedLoadTransitionAlphaM = 1;
            const double reducedStrengthTransitionAlphaS = 1;
            const double gravitationalAcceleration = 9.81;
            const double accelerationAlphaA = 1.4;
            const double frontVelocityCwo = 1.45;

            var input = new GrassRevetmentOvertoppingCumulativeOverloadInput(averageNumberOfWaves, representativeWaveRunup2P,
                                                                             fixedNumberOfWaves,
                                                                             verticalDistanceWaterLevelElevation,
                                                                             criticalFrontVelocity, increasedLoadTransitionAlphaM,
                                                                             reducedStrengthTransitionAlphaS,
                                                                             gravitationalAcceleration, accelerationAlphaA,
                                                                             frontVelocityCwo);

            // Call
            double cumulativeOverload = GrassRevetmentOvertoppingFunctions.CumulativeOverload(input);

            // Assert
            AssertHelper.AreEqual(14.88390482811014, cumulativeOverload);
        }
    }
}