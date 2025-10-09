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

using DiKErnel.FunctionLibrary.GrassWaveRunup;
using DiKErnel.FunctionLibrary.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassWaveRunup
{
    [TestFixture]
    internal sealed class GrassWaveRunupRayleighDiscreteFunctionsTest
    {
        [Test]
        public void CumulativeOverload_ValidInput_ExpectedValue()
        {
            // Setup
            const double averageNumberOfWaves = 225;
            const double representativeWaveRunup2P = 2.258;
            const double verticalDistanceWaterLevelElevation = 0.97;
            const double criticalFrontVelocity = 4;
            const double increasedLoadTransitionAlphaM = 1.1;
            const double reducedStrengthTransitionAlphaS = 1.2;
            const double gravitationalAcceleration = 9.81;
            const double frontVelocityCu = 1.3;
            const int fixedNumberOfWaves = 10000;

            var input = new GrassWaveRunupRayleighDiscreteCumulativeOverloadInput(averageNumberOfWaves,
                                                                                  representativeWaveRunup2P,
                                                                                  verticalDistanceWaterLevelElevation,
                                                                                  criticalFrontVelocity,
                                                                                  increasedLoadTransitionAlphaM,
                                                                                  reducedStrengthTransitionAlphaS,
                                                                                  gravitationalAcceleration,
                                                                                  frontVelocityCu,
                                                                                  fixedNumberOfWaves);

            // Call
            double cumulativeOverload = GrassWaveRunupRayleighDiscreteFunctions.CumulativeOverload(input);

            // Assert
            AssertHelper.AreEqual(735.67446176679459, cumulativeOverload);
        }
    }
}