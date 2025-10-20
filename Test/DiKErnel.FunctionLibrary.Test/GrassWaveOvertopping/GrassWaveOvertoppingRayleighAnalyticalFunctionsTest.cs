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

using DiKErnel.FunctionLibrary.GrassWaveOvertopping;
using DiKErnel.FunctionLibrary.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassWaveOvertopping
{
    [TestFixture]
    internal sealed class GrassWaveOvertoppingRayleighAnalyticalFunctionsTest
    {
        [Test]
        public void CumulativeOverload_ValidInput_ExpectedValue()
        {
            // Setup
            const double averageNumberOfWaves = 832.5624421831636;
            const double representativeWaveRunup2P = 4.161931614163568;
            const double verticalDistanceWaterLevelElevation = 2.2;
            const double criticalFrontVelocity = 6.6;
            const double increasedLoadTransitionAlphaM = 1;
            const double reducedStrengthTransitionAlphaS = 1;
            const double gravitationalAcceleration = 9.81;
            const double frontVelocityCwo = 1.45;
            const double accelerationAlphaA = 1.4;

            double cumulativeOverloadPartial1 = increasedLoadTransitionAlphaM * accelerationAlphaA * accelerationAlphaA *
                                                frontVelocityCwo * frontVelocityCwo * gravitationalAcceleration;

            double cumulativeOverloadPartial2 = reducedStrengthTransitionAlphaS * criticalFrontVelocity * criticalFrontVelocity;

            var input = new GrassWaveOvertoppingRayleighCumulativeOverloadInput(averageNumberOfWaves,
                                                                                representativeWaveRunup2P,
                                                                                verticalDistanceWaterLevelElevation,
                                                                                criticalFrontVelocity,
                                                                                increasedLoadTransitionAlphaM,
                                                                                reducedStrengthTransitionAlphaS,
                                                                                gravitationalAcceleration,
                                                                                frontVelocityCwo, accelerationAlphaA);

            // Call
            double cumulativeOverload = GrassWaveOvertoppingRayleighAnalyticalFunctions.CumulativeOverload(
                input, cumulativeOverloadPartial1, cumulativeOverloadPartial2);

            // Assert
            AssertHelper.AreEqual(1733.057985595415, cumulativeOverload);
        }
    }
}