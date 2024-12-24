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

using System;
using System.Collections.Generic;
using DiKErnel.FunctionLibrary.AsphaltWaveImpact;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.FunctionLibrary.Test.AsphaltWaveImpact
{
    [TestFixture]
    public class AsphaltWaveImpactInputTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            float logFlexuralStrength = Random.NextSingle();
            float averageNumberOfWaves = Random.NextSingle();
            float maximumPeakStress = Random.NextSingle();
            float stiffnessRelation = Random.NextSingle();
            float computationalThickness = Random.NextSingle();
            float outerSlope = Random.NextSingle();

            IReadOnlyList<(float, float)> widthFactors = Array.Empty<(float, float)>();
            IReadOnlyList<(float, float)> depthFactors = Array.Empty<(float, float)>();
            IReadOnlyList<(float, float)> impactFactors = Array.Empty<(float, float)>();

            float z = Random.NextSingle();
            float waterLevel = Random.NextSingle();
            float waveHeightHm0 = Random.NextSingle();
            float fatigueAlpha = Random.NextSingle();
            float fatigueBeta = Random.NextSingle();
            float impactNumberC = Random.NextSingle();

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