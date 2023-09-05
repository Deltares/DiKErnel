// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

using System;
using System.Collections.Generic;
using DiKErnel.FunctionLibrary.AsphaltRevetmentWaveImpact;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.FunctionLibrary.Test.AsphaltRevetmentWaveImpact
{
    [TestFixture]
    public class AsphaltRevetmentWaveImpactFunctionsInputTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            double logFailureTension = Random.NextDouble();
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
            var input = new AsphaltRevetmentWaveImpactFunctionsInput(logFailureTension, averageNumberOfWaves, maximumPeakStress,
                                                                     stiffnessRelation, computationalThickness, outerSlope,
                                                                     widthFactors, depthFactors, impactFactors, z, waterLevel,
                                                                     waveHeightHm0, fatigueAlpha, fatigueBeta, impactNumberC);

            // Assert
            Assert.AreEqual(logFailureTension, input.LogFailureTension);
            Assert.AreEqual(averageNumberOfWaves, input.AverageNumberOfWaves);
            Assert.AreEqual(maximumPeakStress, input.MaximumPeakStress);
            Assert.AreEqual(stiffnessRelation, input.StiffnessRelation);
            Assert.AreEqual(computationalThickness, input.ComputationalThickness);
            Assert.AreEqual(outerSlope, input.OuterSlope);

            Assert.AreSame(widthFactors, input.WidthFactors);
            Assert.AreSame(depthFactors, input.DepthFactors);
            Assert.AreSame(impactFactors, input.ImpactFactors);

            Assert.AreEqual(z, input.Z);
            Assert.AreEqual(waterLevel, input.WaterLevel);
            Assert.AreEqual(waveHeightHm0, input.WaveHeightHm0);
            Assert.AreEqual(fatigueAlpha, input.FatigueAlpha);
            Assert.AreEqual(fatigueBeta, input.FatigueBeta);
            Assert.AreEqual(impactNumberC, input.ImpactNumberC);
        }
    }
}