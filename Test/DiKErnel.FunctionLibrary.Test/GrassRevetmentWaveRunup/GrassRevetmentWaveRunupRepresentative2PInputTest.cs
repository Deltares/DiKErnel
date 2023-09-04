// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

using DiKErnel.FunctionLibrary.GrassRevetmentWaveRunup;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassRevetmentWaveRunup
{
    [TestFixture]
    public class GrassRevetmentWaveRunupRepresentative2PInputTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            double surfSimilarityParameter = Random.NextDouble();
            double waveAngleImpact = Random.NextDouble();
            double waveHeightHm0 = Random.NextDouble();
            double representativeWaveRunup2PGammab = Random.NextDouble();
            double representativeWaveRunup2PGammaf = Random.NextDouble();
            double representativeWaveRunup2PAru = Random.NextDouble();
            double representativeWaveRunup2PBru = Random.NextDouble();
            double representativeWaveRunup2PCru = Random.NextDouble();

            // Call
            var input = new GrassRevetmentWaveRunupRepresentative2PInput(surfSimilarityParameter, waveAngleImpact,
                                                                         waveHeightHm0, representativeWaveRunup2PGammab,
                                                                         representativeWaveRunup2PGammaf,
                                                                         representativeWaveRunup2PAru,
                                                                         representativeWaveRunup2PBru,
                                                                         representativeWaveRunup2PCru);

            // Assert
            Assert.AreEqual(surfSimilarityParameter, input.SurfSimilarityParameter);
            Assert.AreEqual(waveAngleImpact, input.WaveAngleImpact);
            Assert.AreEqual(waveHeightHm0, input.WaveHeightHm0);
            Assert.AreEqual(representativeWaveRunup2PGammab, input.RepresentativeWaveRunup2PGammab);
            Assert.AreEqual(representativeWaveRunup2PGammaf, input.RepresentativeWaveRunup2PGammaf);
            Assert.AreEqual(representativeWaveRunup2PAru, input.RepresentativeWaveRunup2PAru);
            Assert.AreEqual(representativeWaveRunup2PBru, input.RepresentativeWaveRunup2PBru);
            Assert.AreEqual(representativeWaveRunup2PCru, input.RepresentativeWaveRunup2PCru);
        }
    }
}