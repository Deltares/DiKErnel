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

using DiKErnel.FunctionLibrary.GrassRevetmentWaveRunup;
using DiKErnel.FunctionLibrary.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassRevetmentWaveRunup
{
    [TestFixture]
    public class GrassRevetmentWaveRunupFunctionsTest
    {
        private const double epsilon = 1e-6;

        [Test]
        [TestCase(170, 0)]
        [TestCase(110 + epsilon, 0)]
        [TestCase(110, 0)]
        [TestCase(100, 1.87533524870219)]
        [TestCase(90, 3.7506704974043981)]
        [TestCase(80, 5.626005746106598)]
        [TestCase(80 - epsilon, 5.626005746106598)]
        [TestCase(40, 5.626005746106598)]
        [TestCase(20, 5.626005746106598)]
        [TestCase(-20, 5.626005746106598)]
        [TestCase(-40, 5.626005746106598)]
        [TestCase(-80 + epsilon, 5.626005746106598)]
        [TestCase(-80, 5.626005746106598)]
        [TestCase(-90, 3.7506704974043981)]
        [TestCase(-100, 1.87533524870219)]
        [TestCase(-110, 0)]
        [TestCase(-110 - epsilon, 0)]
        [TestCase(-170, 0)]
        public void RepresentativeWaveRunup2P_ValidInput_ExpectedValue(double waveAngle, double expectedRepresentativeWaveRunup2P)
        {
            // Setup
            const double waveAngleImpact = 0.901;
            const double waveHeightHm0 = 2;
            const double wavePeriodTm10 = 5.2;
            const double representativeWaveRunup2PGammab = 1.1;
            const double representativeWaveRunup2PGammaf = 1.2;
            const double representativeWaveRunup2PAru = 1.65;
            const double representativeWaveRunup2PBru = 4;
            const double representativeWaveRunup2PCru = 1.5;
            const double outerSlope = 0.312;
            const double gravitationalAcceleration = 9.81;

            var input = new GrassRevetmentWaveRunupRepresentative2PInput(waveAngle, waveAngleImpact, waveHeightHm0,
                                                                         wavePeriodTm10, representativeWaveRunup2PGammab,
                                                                         representativeWaveRunup2PGammaf,
                                                                         representativeWaveRunup2PAru,
                                                                         representativeWaveRunup2PBru,
                                                                         representativeWaveRunup2PCru,
                                                                         outerSlope, gravitationalAcceleration);

            // Call
            double representativeWaveRunup2P = GrassRevetmentWaveRunupFunctions.RepresentativeWaveRunup2P(input);

            // Assert
            AssertHelper.AreEqual(expectedRepresentativeWaveRunup2P, representativeWaveRunup2P);
        }

        [Test]
        public void WaveAngleImpact_ValidInput_ExpectedValue()
        {
            // Setup
            const double waveAngle = 45;
            const double waveAngleImpactAbeta = 0.0022;
            const double waveAngleImpactBetamax = 80;

            // Call
            double waveAngleImpact = GrassRevetmentWaveRunupFunctions.WaveAngleImpact(waveAngle, waveAngleImpactAbeta,
                                                                                      waveAngleImpactBetamax);

            // Assert
            AssertHelper.AreEqual(0.901, waveAngleImpact);
        }
    }
}