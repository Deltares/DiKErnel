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
            double waveAngle = Random.NextDouble();
            double waveAngleImpact = Random.NextDouble();
            double waveHeightHm0 = Random.NextDouble();
            double representativeWaveRunup2PGammab = Random.NextDouble();
            double representativeWaveRunup2PGammaf = Random.NextDouble();
            double representativeWaveRunup2PAru = Random.NextDouble();
            double representativeWaveRunup2PBru = Random.NextDouble();
            double representativeWaveRunup2PCru = Random.NextDouble();

            // Call
            var input = new GrassRevetmentWaveRunupRepresentative2PInput(waveAngle, waveAngleImpact,
                                                                         waveHeightHm0, representativeWaveRunup2PGammab,
                                                                         representativeWaveRunup2PGammaf,
                                                                         representativeWaveRunup2PAru,
                                                                         representativeWaveRunup2PBru,
                                                                         representativeWaveRunup2PCru);

            // Assert
            Assert.That(input.WaveAngle, Is.EqualTo(waveAngle));
            Assert.That(input.WaveAngleImpact, Is.EqualTo(waveAngleImpact));
            Assert.That(input.WaveHeightHm0, Is.EqualTo(waveHeightHm0));
            Assert.That(input.RepresentativeWaveRunup2PGammab, Is.EqualTo(representativeWaveRunup2PGammab));
            Assert.That(input.RepresentativeWaveRunup2PGammaf, Is.EqualTo(representativeWaveRunup2PGammaf));
            Assert.That(input.RepresentativeWaveRunup2PAru, Is.EqualTo(representativeWaveRunup2PAru));
            Assert.That(input.RepresentativeWaveRunup2PBru, Is.EqualTo(representativeWaveRunup2PBru));
            Assert.That(input.RepresentativeWaveRunup2PCru, Is.EqualTo(representativeWaveRunup2PCru));
        }
    }
}