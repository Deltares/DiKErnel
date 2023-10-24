﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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

using DiKErnel.DomainLibrary.Defaults.GrassRevetmentWaveImpact;
using NUnit.Framework;

namespace DiKErnel.DomainLibrary.Test.Defaults.GrassRevetmentWaveImpact
{
    [TestFixture]
    public class GrassRevetmentWaveImpactDefaultsTest
    {
        [Test]
        public void MinimumWaveHeightTemax_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassRevetmentWaveImpactDefaults.MinimumWaveHeightTemax, Is.EqualTo(3600000));
        }

        [Test]
        public void MaximumWaveHeightTemin_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassRevetmentWaveImpactDefaults.MaximumWaveHeightTemin, Is.EqualTo(3.6));
        }

        [Test]
        public void WaveAngleImpactNwa_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassRevetmentWaveImpactDefaults.WaveAngleImpactNwa, Is.EqualTo(2d / 3));
        }

        [Test]
        public void WaveAngleImpactQwa_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassRevetmentWaveImpactDefaults.WaveAngleImpactQwa, Is.EqualTo(0.35));
        }

        [Test]
        public void WaveAngleImpactRwa_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassRevetmentWaveImpactDefaults.WaveAngleImpactRwa, Is.EqualTo(10));
        }

        [Test]
        public void UpperLimitLoadingAul_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassRevetmentWaveImpactDefaults.UpperLimitLoadingAul, Is.EqualTo(0));
        }

        [Test]
        public void LowerLimitLoadingAll_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassRevetmentWaveImpactDefaults.LowerLimitLoadingAll, Is.EqualTo(0.5));
        }
    }
}