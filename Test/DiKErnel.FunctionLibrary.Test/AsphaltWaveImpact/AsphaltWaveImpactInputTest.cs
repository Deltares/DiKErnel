// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
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

using System;
using System.Collections.Generic;
using DiKErnel.FunctionLibrary.AsphaltWaveImpact;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.FunctionLibrary.Test.AsphaltWaveImpact
{
    [TestFixture]
    internal sealed class AsphaltWaveImpactInputTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            double logFlexuralStrength = Random.NextDouble();
            double averageNumberOfWaves = Random.NextDouble();
            double maximumPeakStress = Random.NextDouble();
            double stiffnessRelation = Random.NextDouble();
            double computationalThickness = Random.NextDouble();
            double outerSlope = Random.NextDouble();

            IReadOnlyList<(double, double)> widthFactors = Array.Empty<(double, double)>();
            IReadOnlyList<(double, double)> depthFactors = Array.Empty<(double, double)>();
            IReadOnlyList<(double, double)> impactFactors = Array.Empty<(double, double)>();

            double z = Random.NextDouble();
            double waterLevel = Random.NextDouble();
            double waveHeightHm0 = Random.NextDouble();
            double fatigueAlpha = Random.NextDouble();
            double fatigueBeta = Random.NextDouble();
            double impactNumberC = Random.NextDouble();

            // Call
            var input = new AsphaltWaveImpactInput(logFlexuralStrength, averageNumberOfWaves, maximumPeakStress,
                                                   stiffnessRelation, computationalThickness, outerSlope, widthFactors,
                                                   depthFactors, impactFactors, z, waterLevel, waveHeightHm0,
                                                   fatigueAlpha, fatigueBeta, impactNumberC);

            // Assert
            Assert.That(input.LogFlexuralStrength, Is.EqualTo(logFlexuralStrength));
            Assert.That(input.AverageNumberOfWaves, Is.EqualTo(averageNumberOfWaves));
            Assert.That(input.MaximumPeakStress, Is.EqualTo(maximumPeakStress));
            Assert.That(input.StiffnessRelation, Is.EqualTo(stiffnessRelation));
            Assert.That(input.ComputationalThickness, Is.EqualTo(computationalThickness));
            Assert.That(input.OuterSlope, Is.EqualTo(outerSlope));

            Assert.That(input.WidthFactors, Is.SameAs(widthFactors));
            Assert.That(input.DepthFactors, Is.SameAs(depthFactors));
            Assert.That(input.ImpactFactors, Is.SameAs(impactFactors));

            Assert.That(input.Z, Is.EqualTo(z));
            Assert.That(input.WaterLevel, Is.EqualTo(waterLevel));
            Assert.That(input.WaveHeightHm0, Is.EqualTo(waveHeightHm0));
            Assert.That(input.FatigueAlpha, Is.EqualTo(fatigueAlpha));
            Assert.That(input.FatigueBeta, Is.EqualTo(fatigueBeta));
            Assert.That(input.ImpactNumberC, Is.EqualTo(impactNumberC));
        }
    }
}