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

using DiKErnel.DomainLibrary.Defaults.AsphaltRevetmentWaveImpact;
using NUnit.Framework;

namespace DiKErnel.DomainLibrary.Test.Defaults.AsphaltRevetmentWaveImpact
{
    [TestFixture]
    public class AsphaltRevetmentWaveImpactDefaultsTest
    {
        [Test]
        public void DensityOfWater_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(1025, AsphaltRevetmentWaveImpactDefaults.DensityOfWater);
        }

        [Test]
        public void AverageNumberOfWavesCtm_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(1, AsphaltRevetmentWaveImpactDefaults.AverageNumberOfWavesCtm);
        }

        [Test]
        public void ImpactNumberC_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(1, AsphaltRevetmentWaveImpactDefaults.ImpactNumberC);
        }

        [Test]
        public void WidthFactors_ExpectedValue()
        {
            // Call & Assert
            CollectionAssert.AreEqual(new[]
            {
                (0.1, 0.0392),
                (0.2, 0.0738),
                (0.3, 0.1002),
                (0.4, 0.1162),
                (0.5, 0.1213),
                (0.6, 0.1168),
                (0.7, 0.1051),
                (0.8, 0.089),
                (0.9, 0.0712),
                (1, 0.0541),
                (1.1, 0.0391),
                (1.2, 0.0269),
                (1.3, 0.0216),
                (1.4, 0.015),
                (1.5, 0.0105)
            }, AsphaltRevetmentWaveImpactDefaults.WidthFactors);
        }

        [Test]
        public void DepthFactors_ExpectedValue()
        {
            // Call & Assert
            CollectionAssert.AreEqual(new[]
            {
                (-1, 0.0244),
                (-0.875, 0.0544),
                (-0.75, 0.0938),
                (-0.625, 0.1407),
                (-0.5, 0.1801),
                (-0.375, 0.1632),
                (-0.25, 0.1426),
                (-0.125, 0.0994),
                (0, 0.06),
                (0.125, 0.0244),
                (0.25, 0.0169)
            }, AsphaltRevetmentWaveImpactDefaults.DepthFactors);
        }

        [Test]
        public void ImpactFactors_ExpectedValue()
        {
            // Call & Assert
            CollectionAssert.AreEqual(new[]
            {
                (2, 0.039),
                (2.4, 0.1),
                (2.8, 0.18),
                (3.2, 0.235),
                (3.6, 0.2),
                (4, 0.13),
                (4.4, 0.08),
                (4.8, 0.02),
                (5.2, 0.01),
                (5.6, 0.005),
                (6, 0.001)
            }, AsphaltRevetmentWaveImpactDefaults.ImpactFactors);
        }
    }
}