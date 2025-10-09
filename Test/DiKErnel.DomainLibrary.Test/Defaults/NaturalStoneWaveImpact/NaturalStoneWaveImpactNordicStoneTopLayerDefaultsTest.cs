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
    internal sealed class NaturalStoneWaveImpactNordicStoneTopLayerDefaultsTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            var defaults = NaturalStoneWaveImpactNordicStoneTopLayerDefaults.Instance;

            // Call & Assert
            Assert.That(defaults, Is.InstanceOf<INaturalStoneWaveImpactTopLayerDefaults>());
            Assert.That(defaults.HydraulicLoadXib, Is.EqualTo(2.9));
            Assert.That(defaults.HydraulicLoadAp, Is.EqualTo(4));
            Assert.That(defaults.HydraulicLoadBp, Is.EqualTo(0));
            Assert.That(defaults.HydraulicLoadCp, Is.EqualTo(0));
            Assert.That(defaults.HydraulicLoadNp, Is.EqualTo(-0.9));
            Assert.That(defaults.HydraulicLoadAs, Is.EqualTo(0.8));
            Assert.That(defaults.HydraulicLoadBs, Is.EqualTo(0));
            Assert.That(defaults.HydraulicLoadCs, Is.EqualTo(0));
            Assert.That(defaults.HydraulicLoadNs, Is.EqualTo(0.6));
        }
    }
}