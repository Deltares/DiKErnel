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
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassRevetmentWaveRunup
{
    [TestFixture]
    public class GrassRevetmentWaveRunupRayleighFunctionsTest
    {
        [Test]
        public void CumulativeOverload_ValidInput_ExpectedValue()
        {
            // Setup
            const double averageNumberOfWaves = 225;
            const double representativeWaveRunup2P = 2.258;
            const int fixedNumberOfWaves = 10000;
            const double verticalDistanceWaterLevelElevation = 0.97;
            const double criticalFrontVelocity = 4.0;
            const double increasedLoadTransitionAlphaM = 1.1;
            const double reducedStrengthTransitionAlphaS = 1.2;
            const double gravitationalAcceleration = 9.81;
            const double frontVelocityCu = 1.3;

            var input = new GrassRevetmentWaveRunupRayleighCumulativeOverloadInput(averageNumberOfWaves, representativeWaveRunup2P,
                                                                                   fixedNumberOfWaves,
                                                                                   verticalDistanceWaterLevelElevation,
                                                                                   criticalFrontVelocity,
                                                                                   increasedLoadTransitionAlphaM,
                                                                                   reducedStrengthTransitionAlphaS,
                                                                                   gravitationalAcceleration, frontVelocityCu);

            // Call
            double cumulativeOverload = GrassRevetmentWaveRunupRayleighFunctions.CumulativeOverload(input);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(735.67446176679459, cumulativeOverload);
        }
    }
}