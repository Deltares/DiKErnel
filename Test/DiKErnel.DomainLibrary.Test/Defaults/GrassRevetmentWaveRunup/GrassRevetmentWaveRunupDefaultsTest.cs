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
            Assert.That(GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PAru, Is.EqualTo(1.65));
        }

        [Test]
        public void RepresentativeWaveRunup2PBru_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PBru, Is.EqualTo(4));
        }

        [Test]
        public void RepresentativeWaveRunup2PCru_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PCru, Is.EqualTo(1.5));
        }

        [Test]
        public void RepresentativeWaveRunup2PGammab_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PGammab, Is.EqualTo(1));
        }

        [Test]
        public void RepresentativeWaveRunup2PGammaf_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PGammaf, Is.EqualTo(1));
        }

        [Test]
        public void WaveAngleImpactAbeta_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassRevetmentWaveRunupDefaults.WaveAngleImpactAbeta, Is.EqualTo(0.0022));
        }

        [Test]
        public void WaveAngleImpactBetamax_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassRevetmentWaveRunupDefaults.WaveAngleImpactBetamax, Is.EqualTo(80));
        }
    }
}