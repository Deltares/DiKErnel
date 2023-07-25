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
    public class NaturalStoneRevetmentDefaultsTest
    {
        [Test]
        public void SlopeUpperLevelAus_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(0.05, NaturalStoneRevetmentDefaults.SlopeUpperLevelAus);
        }

        [Test]
        public void SlopeLowerLevelAls_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(1.5, NaturalStoneRevetmentDefaults.SlopeLowerLevelAls);
        }

        [Test]
        public void UpperLimitLoadingAul_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(0.1, NaturalStoneRevetmentDefaults.UpperLimitLoadingAul);
        }

        [Test]
        public void UpperLimitLoadingBul_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(0.6, NaturalStoneRevetmentDefaults.UpperLimitLoadingBul);
        }

        [Test]
        public void UpperLimitLoadingCul_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(4, NaturalStoneRevetmentDefaults.UpperLimitLoadingCul);
        }

        [Test]
        public void LowerLimitLoadingAll_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(0, NaturalStoneRevetmentDefaults.LowerLimitLoadingAll);
        }

        [Test]
        public void LowerLimitLoadingBll_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(0.2, NaturalStoneRevetmentDefaults.LowerLimitLoadingBll);
        }

        [Test]
        public void LowerLimitLoadingCll_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(4, NaturalStoneRevetmentDefaults.LowerLimitLoadingCll);
        }

        [Test]
        public void DistanceMaximumWaveElevationAsmax_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(0.42, NaturalStoneRevetmentDefaults.DistanceMaximumWaveElevationAsmax);
        }

        [Test]
        public void DistanceMaximumWaveElevationBsmax_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(0.9, NaturalStoneRevetmentDefaults.DistanceMaximumWaveElevationBsmax);
        }

        [Test]
        public void NormativeWidthOfWaveImpactAwi_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(0.96, NaturalStoneRevetmentDefaults.NormativeWidthOfWaveImpactAwi);
        }

        [Test]
        public void NormativeWidthOfWaveImpactBwi_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(0.11, NaturalStoneRevetmentDefaults.NormativeWidthOfWaveImpactBwi);
        }

        [Test]
        public void WaveAngleImpactBetamax_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(78, NaturalStoneRevetmentDefaults.WaveAngleImpactBetamax);
        }
    }
}