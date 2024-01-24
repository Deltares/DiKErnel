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

using DiKErnel.DomainLibrary.Defaults.GrassWaveRunup;
using NUnit.Framework;

namespace DiKErnel.DomainLibrary.Test.Defaults.GrassWaveRunup
{
    [TestFixture]
    public class GrassWaveRunupBattjesGroenendijkAnalyticalDefaultsTest
    {
        [Test]
        public void FrontVelocityCu_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassWaveRunupBattjesGroenendijkAnalyticalDefaults.FrontVelocityCu, Is.EqualTo(1.1));
        }

        [Test]
        public void K1_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassWaveRunupBattjesGroenendijkAnalyticalDefaults.K1, Is.EqualTo(2));
        }

        [Test]
        public void K2_ExpectedValue()
        {
            // Call & Assert
            Assert.That(GrassWaveRunupBattjesGroenendijkAnalyticalDefaults.K2, Is.EqualTo(3.6));
        }
    }
}