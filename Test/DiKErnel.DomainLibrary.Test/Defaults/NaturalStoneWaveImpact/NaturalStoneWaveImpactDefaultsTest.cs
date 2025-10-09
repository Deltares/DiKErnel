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

using DiKErnel.DomainLibrary.Defaults.NaturalStoneWaveImpact;
using NUnit.Framework;

namespace DiKErnel.DomainLibrary.Test.Defaults.NaturalStoneWaveImpact
{
    [TestFixture]
    internal sealed class NaturalStoneWaveImpactDefaultsTest
    {
        [Test]
        public void SlopeUpperLevelAus_ExpectedValue()
        {
            // Call & Assert
            Assert.That(NaturalStoneWaveImpactDefaults.SlopeUpperLevelAus, Is.EqualTo(0.05));
        }

        [Test]
        public void SlopeLowerLevelAls_ExpectedValue()
        {
            // Call & Assert
            Assert.That(NaturalStoneWaveImpactDefaults.SlopeLowerLevelAls, Is.EqualTo(1.5));
        }

        [Test]
        public void UpperLimitLoadingAul_ExpectedValue()
        {
            // Call & Assert
            Assert.That(NaturalStoneWaveImpactDefaults.UpperLimitLoadingAul, Is.EqualTo(0.1));
        }

        [Test]
        public void UpperLimitLoadingBul_ExpectedValue()
        {
            // Call & Assert
            Assert.That(NaturalStoneWaveImpactDefaults.UpperLimitLoadingBul, Is.EqualTo(0.6));
        }

        [Test]
        public void UpperLimitLoadingCul_ExpectedValue()
        {
            // Call & Assert
            Assert.That(NaturalStoneWaveImpactDefaults.UpperLimitLoadingCul, Is.EqualTo(4));
        }

        [Test]
        public void LowerLimitLoadingAll_ExpectedValue()
        {
            // Call & Assert
            Assert.That(NaturalStoneWaveImpactDefaults.LowerLimitLoadingAll, Is.EqualTo(0.1));
        }

        [Test]
        public void LowerLimitLoadingBll_ExpectedValue()
        {
            // Call & Assert
            Assert.That(NaturalStoneWaveImpactDefaults.LowerLimitLoadingBll, Is.EqualTo(0.2));
        }

        [Test]
        public void LowerLimitLoadingCll_ExpectedValue()
        {
            // Call & Assert
            Assert.That(NaturalStoneWaveImpactDefaults.LowerLimitLoadingCll, Is.EqualTo(4));
        }

        [Test]
        public void DistanceMaximumWaveElevationAsmax_ExpectedValue()
        {
            // Call & Assert
            Assert.That(NaturalStoneWaveImpactDefaults.DistanceMaximumWaveElevationAsmax, Is.EqualTo(0.42));
        }

        [Test]
        public void DistanceMaximumWaveElevationBsmax_ExpectedValue()
        {
            // Call & Assert
            Assert.That(NaturalStoneWaveImpactDefaults.DistanceMaximumWaveElevationBsmax, Is.EqualTo(0.9));
        }

        [Test]
        public void NormativeWidthOfWaveImpactAwi_ExpectedValue()
        {
            // Call & Assert
            Assert.That(NaturalStoneWaveImpactDefaults.NormativeWidthOfWaveImpactAwi, Is.EqualTo(0.96));
        }

        [Test]
        public void NormativeWidthOfWaveImpactBwi_ExpectedValue()
        {
            // Call & Assert
            Assert.That(NaturalStoneWaveImpactDefaults.NormativeWidthOfWaveImpactBwi, Is.EqualTo(0.11));
        }

        [Test]
        public void WaveAngleImpactBetamax_ExpectedValue()
        {
            // Call & Assert
            Assert.That(NaturalStoneWaveImpactDefaults.WaveAngleImpactBetamax, Is.EqualTo(78));
        }
    }
}