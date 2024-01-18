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

using DiKErnel.FunctionLibrary.GrassRevetmentWaveRunup;
using DiKErnel.FunctionLibrary.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassRevetmentWaveRunup
{
    [TestFixture]
    public class GrassRevetmentWaveRunupBattjesGroenendijkAnalyticalFunctionsTest
    {
        [Test]
        [TestCase(0.80, 0.00, 300, 1.38280392857274, 95.12417141759073)]
        [TestCase(0.80, 0.01, 225, 1.84373857143032, 394.50421519375334)]
        [TestCase(0.80, 0.02, 300, 1.24590633964404, 39.72057327531430)]
        [TestCase(1.20, 0.03, 225, 2.25810935954614, 1005.7065223489108)]
        [TestCase(1.20, 0.04, 180, 2.82263669943267, 1454.5193898881962)]
        [TestCase(1.20, 0.05, 225, 2.03455653295107, 710.86334037955851)]
        [TestCase(1.60, 0.06, 180, 3.25930011648394, 2273.5849827117563)]
        [TestCase(1.60, 0.07, 150, 3.91116013978073, 2567.9438158569155)]
        [TestCase(1.60, 0.08, 180, 2.93662940495203, 1861.5154934919606)]
        [TestCase(2.00, 0.09, 150, 4.37280997171864, 3375.6712412054667)]
        [TestCase(2.00, 0.10, 100, 5.87209471713409, 3287.3327350497325)]
        [TestCase(2.00, 0.11, 150, 3.93990178451850, 2909.1489797082131)]
        [TestCase(2.40, 0.12, 100, 6.92743146918533, 4265.4626420200575)]
        [TestCase(2.40, 0.13, 90, 7.06457887192072, 3922.7901327987101)]
        [TestCase(2.40, 0.14, 100, 6.24161575373599, 3773.8629858234135)]
        [TestCase(2.80, 0.15, 90, 8.12578956708121, 4797.4226527254459)]
        public void CumulativeOverload_VariousScenarios_ExpectedValue(double waveHeightHm0, double waterLevel, double averageNumberOfWaves,
                                                                      double representativeWaveRunup2P, double expectedCumulativeOverload)
        {
            // Setup
            const double increasedLoadTransitionAlphaM = 1;
            const double reducedStrengthTransitionAlphaS = 1;

            const double frontVelocityCu = 1.1;
            const double criticalFrontVelocity = 4.0;
            const double gravitationalAcceleration = 9.81;

            const double slopeForeshore = 0.004;
            const double bottomForeshoreZ = -4;
            const double k1 = 2.0;
            const double k2 = 3.6;

            double verticalDistanceWaterLevelElevation = 1 - waterLevel;

            var input = new GrassRevetmentWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput(
                averageNumberOfWaves, representativeWaveRunup2P, waterLevel, waveHeightHm0, verticalDistanceWaterLevelElevation,
                bottomForeshoreZ, slopeForeshore, criticalFrontVelocity, frontVelocityCu, increasedLoadTransitionAlphaM,
                reducedStrengthTransitionAlphaS, gravitationalAcceleration, k1, k2);

            // Call
            double cumulativeOverload = GrassRevetmentWaveRunupBattjesGroenendijkAnalyticalFunctions.CumulativeOverload(input);

            // Assert
            AssertHelper.AreEqual(expectedCumulativeOverload, cumulativeOverload);
        }
    }
}