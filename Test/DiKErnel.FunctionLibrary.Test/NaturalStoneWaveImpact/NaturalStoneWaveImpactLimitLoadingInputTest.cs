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

using DiKErnel.FunctionLibrary.NaturalStoneWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.NaturalStoneWaveImpact
{
    [TestFixture]
    internal sealed class NaturalStoneWaveImpactLimitLoadingInputTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            double depthMaximumWaveLoad = Random.NextDouble();
            double surfSimilarityParameter = Random.NextDouble();
            double waterLevel = Random.NextDouble();
            double waveHeightHm0 = Random.NextDouble();
            double a = Random.NextDouble();
            double b = Random.NextDouble();
            double c = Random.NextDouble();

            // Call
            var input = new NaturalStoneWaveImpactLimitLoadingInput(depthMaximumWaveLoad, surfSimilarityParameter,
                                                                    waterLevel, waveHeightHm0, a, b, c);

            // Assert
            Assert.That(input.DepthMaximumWaveLoad, Is.EqualTo(depthMaximumWaveLoad));
            Assert.That(input.SurfSimilarityParameter, Is.EqualTo(surfSimilarityParameter));
            Assert.That(input.WaterLevel, Is.EqualTo(waterLevel));
            Assert.That(input.WaveHeightHm0, Is.EqualTo(waveHeightHm0));
            Assert.That(input.A, Is.EqualTo(a));
            Assert.That(input.B, Is.EqualTo(b));
            Assert.That(input.C, Is.EqualTo(c));
        }
    }
}