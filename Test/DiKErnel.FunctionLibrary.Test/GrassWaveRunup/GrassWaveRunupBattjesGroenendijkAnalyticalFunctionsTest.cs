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

using DiKErnel.FunctionLibrary.GrassWaveRunup;
using DiKErnel.FunctionLibrary.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassWaveRunup
{
    [TestFixture]
    internal sealed class GrassWaveRunupBattjesGroenendijkAnalyticalFunctionsTest
    {
        [Test]
        [TestCase(0.8, 0, 300, 1.38280392857274, 95.12417141759073)]
        [TestCase(0.01, 0.15, 90, 8.12578956708121, 3413.6086113813335)]
        public void CumulativeOverload_VariousScenarios_ExpectedValue(double waveHeightHm0, double waterLevel, double averageNumberOfWaves,
                                                                      double representativeWaveRunup2P, double expectedCumulativeOverload)
        {
            // Setup
            const double criticalFrontVelocity = 4;
            const double increasedLoadTransitionAlphaM = 1;
            const double reducedStrengthTransitionAlphaS = 1;
            const double gravitationalAcceleration = 9.81;
            const double frontVelocityCu = 1.1;
            const double bottomForeshoreZ = -4;
            const double slopeForeshore = 0.004;
            const double k1 = 2;
            const double k2 = 3.6;

            double verticalDistanceWaterLevelElevation = 1 - waterLevel;

            double upperLimitWaveRunup = GrassWaveRunupBattjesGroenendijkAnalyticalFunctions.UpperLimitWaveRunup(
                increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS,
                frontVelocityCu, criticalFrontVelocity, gravitationalAcceleration);

            var input = new GrassWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput(
                averageNumberOfWaves, representativeWaveRunup2P, verticalDistanceWaterLevelElevation,
                criticalFrontVelocity, increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS,
                gravitationalAcceleration, frontVelocityCu, waterLevel, waveHeightHm0, bottomForeshoreZ, slopeForeshore,
                k1, k2);

            // Call
            double cumulativeOverload = GrassWaveRunupBattjesGroenendijkAnalyticalFunctions.CumulativeOverload(input, upperLimitWaveRunup);

            // Assert
            AssertHelper.AreEqual(expectedCumulativeOverload, cumulativeOverload);
        }
    }
}