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

using DiKErnel.DomainLibrary.Defaults.GrassRevetmentWaveRunup;
using NUnit.Framework;

namespace DiKErnel.DomainLibrary.Test.Defaults.GrassRevetmentWaveRunup
{
    [TestFixture]
    public class GrassRevetmentWaveRunupDefaultsTest
    {
        [Test]
        public void RepresentativeWaveRunup2PAru_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(1.65, GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PAru);
        }

        [Test]
        public void RepresentativeWaveRunup2PBru_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(4, GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PBru);
        }

        [Test]
        public void RepresentativeWaveRunup2PCru_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(1.5, GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PCru);
        }

        [Test]
        public void RepresentativeWaveRunup2PGammab_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(1, GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PGammab);
        }

        [Test]
        public void RepresentativeWaveRunup2PGammaf_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(1, GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PGammaf);
        }

        [Test]
        public void WaveAngleImpactAbeta_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(0.0022, GrassRevetmentWaveRunupDefaults.WaveAngleImpactAbeta);
        }

        [Test]
        public void WaveAngleImpactBetamax_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(80, GrassRevetmentWaveRunupDefaults.WaveAngleImpactBetamax);
        }
    }
}