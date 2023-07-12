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

using System;
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
            Assert.AreEqual(1025.0, AsphaltRevetmentWaveImpactDefaults.DensityOfWater);
        }

        [Test]
        public void AverageNumberOfWavesCtm_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(1.0, AsphaltRevetmentWaveImpactDefaults.AverageNumberOfWavesCtm);
        }

        [Test]
        public void ImpactNumberC_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(1.0, AsphaltRevetmentWaveImpactDefaults.ImpactNumberC);
        }

        [Test]
        public void WidthFactors_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(new[]
            {
                new Tuple<double, double>(0.1, 0.0392),
                new Tuple<double, double>(0.2, 0.0738),
                new Tuple<double, double>(0.3, 0.1002),
                new Tuple<double, double>(0.4, 0.1162),
                new Tuple<double, double>(0.5, 0.1213),
                new Tuple<double, double>(0.6, 0.1168),
                new Tuple<double, double>(0.7, 0.1051),
                new Tuple<double, double>(0.8, 0.0890),
                new Tuple<double, double>(0.9, 0.0712),
                new Tuple<double, double>(1.0, 0.0541),
                new Tuple<double, double>(1.1, 0.0391),
                new Tuple<double, double>(1.2, 0.0269),
                new Tuple<double, double>(1.3, 0.0216),
                new Tuple<double, double>(1.4, 0.0150),
                new Tuple<double, double>(1.5, 0.0105)
            }, AsphaltRevetmentWaveImpactDefaults.WidthFactors);
        }

        [Test]
        public void DepthFactors_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(new[]
            {
                new Tuple<double, double>(-1.0, 0.0244),
                new Tuple<double, double>(-0.875, 0.0544),
                new Tuple<double, double>(-0.750, 0.0938),
                new Tuple<double, double>(-0.625, 0.1407),
                new Tuple<double, double>(-0.500, 0.1801),
                new Tuple<double, double>(-0.375, 0.1632),
                new Tuple<double, double>(-0.250, 0.1426),
                new Tuple<double, double>(-0.125, 0.0994),
                new Tuple<double, double>(0.0, 0.06),
                new Tuple<double, double>(0.125, 0.0244),
                new Tuple<double, double>(0.250, 0.0169)
            }, AsphaltRevetmentWaveImpactDefaults.DepthFactors);
        }

        [Test]
        public void ImpactFactors_ExpectedValue()
        {
            // Call & Assert
            Assert.AreEqual(new[]
            {
                new Tuple<double, double>(2.0, 0.039),
                new Tuple<double, double>(2.4, 0.1),
                new Tuple<double, double>(2.8, 0.18),
                new Tuple<double, double>(3.2, 0.235),
                new Tuple<double, double>(3.6, 0.2),
                new Tuple<double, double>(4.0, 0.13),
                new Tuple<double, double>(4.4, 0.08),
                new Tuple<double, double>(4.8, 0.02),
                new Tuple<double, double>(5.2, 0.01),
                new Tuple<double, double>(5.6, 0.005),
                new Tuple<double, double>(6.0, 0.001)
            }, AsphaltRevetmentWaveImpactDefaults.ImpactFactors);
        }
    }
}