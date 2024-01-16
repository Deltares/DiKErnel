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

using System;
using DiKErnel.FunctionLibrary.GrassRevetmentWaveRunup;
using DiKErnel.FunctionLibrary.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassRevetmentWaveRunup
{
    [TestFixture]
    public class GrassRevetmentWaveRunupBattjesGroenendijkAnalyticalFunctionsTest
    {
        [Test]
        public void CumulativeOverload_VariousScenarios_ExpectedValue()
        {
            // Setup
            double increasedLoadTransitionAlphaM = 1;
            double reducedStrengthTransitionAlphaS = 1;

            double frontVelocityCu = 1.1;
            double criticalFrontVelocity = 4.0;
            double gravitationalAcceleration = 9.81;

            double slopeForeshore = 0.004;
            double representativeWaveRunup2P = 1.382803929; // Variable in time
            double waveHeightHm0 = 0.8; // variable in time
            double waterLevel = 0; // variable in time
            double bottomForeshoreZ = 4;
            double verticalDistanceWaterLevelElevation = 1 - waterLevel;
            double k1 = 2.0;
            double k2 = 3.6;

            var input = new GrassRevetmentWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput(increasedLoadTransitionAlphaM,
                reducedStrengthTransitionAlphaS, frontVelocityCu, criticalFrontVelocity, gravitationalAcceleration, slopeForeshore,
                representativeWaveRunup2P, waveHeightHm0, waterLevel, bottomForeshoreZ, verticalDistanceWaterLevelElevation, k1, k2);

            // Call
            double cumulativeOverload = GrassRevetmentWaveRunupBattjesGroenendijkAnalyticalFunctions.CumulativeOverload(input);

            // Assert
            AssertHelper.AreEqual(double.NaN, cumulativeOverload);
        }
    }
}