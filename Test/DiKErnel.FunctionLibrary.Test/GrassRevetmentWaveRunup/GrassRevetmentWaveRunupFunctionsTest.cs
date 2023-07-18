// // Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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

using DiKErnel.FunctionLibrary.GrassRevetmentWaveRunup;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassRevetmentWaveRunup
{
    [TestFixture]
    public class GrassRevetmentWaveRunupFunctionsTest
    {
        [Test]
        public void RepresentativeWaveRunup2P_ValidInput_ExpectedValue()
        {
            // Setup
            const double surfSimilarityParameter = 1.436;
            const double waveAngleImpact = 0.901;
            const double waveHeightHm0 = 2.0;
            const double representativeWaveRunup2PGammab = 1.1;
            const double representativeWaveRunup2PGammaf = 1.2;
            const double representativeWaveRunup2PAru = 1.65;
            const double representativeWaveRunup2PBru = 4.0;
            const double representativeWaveRunup2PCru = 1.5;

            var input = new GrassRevetmentWaveRunupRepresentative2PInput(surfSimilarityParameter, waveAngleImpact, waveHeightHm0,
                                                                         representativeWaveRunup2PGammab,
                                                                         representativeWaveRunup2PGammaf,
                                                                         representativeWaveRunup2PAru,
                                                                         representativeWaveRunup2PBru,
                                                                         representativeWaveRunup2PCru);

            // Call
            double representativeWaveRunup2P = GrassRevetmentWaveRunupFunctions.RepresentativeWaveRunup2P(input);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(5.635949616, representativeWaveRunup2P);
        }

        [Test]
        public void WaveAngleImpact_ValidInput_ExpectedValue()
        {
            // Setup
            const double waveAngle = 45.0;
            const double waveAngleImpactAbeta = 0.0022;
            const double waveAngleImpactBetamax = 80.0;

            // Call
            double waveAngleImpact = GrassRevetmentWaveRunupFunctions.WaveAngleImpact(waveAngle, waveAngleImpactAbeta,
                                                                                      waveAngleImpactBetamax);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(0.901, waveAngleImpact);
        }
    }
}