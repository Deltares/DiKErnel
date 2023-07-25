// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using DiKErnel.DomainLibrary.Defaults.NaturalStoneRevetment;
using NUnit.Framework;

namespace DiKErnel.DomainLibrary.Test.Defaults.NaturalStoneRevetment
{
    [TestFixture]
    public class NaturalStoneRevetmentNordicStoneTopLayerDefaultsTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            var defaults = NaturalStoneRevetmentNordicStoneTopLayerDefaults.Instance;

            // Call & Assert
            Assert.IsInstanceOf<INaturalStoneRevetmentTopLayerDefaults>(defaults);
            Assert.AreEqual(2.9, defaults.HydraulicLoadXib);
            Assert.AreEqual(4, defaults.HydraulicLoadAp);
            Assert.AreEqual(0, defaults.HydraulicLoadBp);
            Assert.AreEqual(0, defaults.HydraulicLoadCp);
            Assert.AreEqual(-0.9, defaults.HydraulicLoadNp);
            Assert.AreEqual(0.8, defaults.HydraulicLoadAs);
            Assert.AreEqual(0, defaults.HydraulicLoadBs);
            Assert.AreEqual(0, defaults.HydraulicLoadCs);
            Assert.AreEqual(0.6, defaults.HydraulicLoadNs);
        }
    }
}