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

using DiKErnel.FunctionLibrary.GrassWaveRunup;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassWaveRunup
{
    [TestFixture]
    internal sealed class GrassWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInputTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            double averageNumberOfWaves = Random.NextDouble();
            double representativeWaveRunup2P = Random.NextDouble();
            double verticalDistanceWaterLevelElevation = Random.NextDouble();
            double criticalFrontVelocity = Random.NextDouble();
            double increasedLoadTransitionAlphaM = Random.NextDouble();
            double reducedStrengthTransitionAlphaS = Random.NextDouble();
            double gravitationalAcceleration = Random.NextDouble();
            double frontVelocityCu = Random.NextDouble();
            double waterLevel = Random.NextDouble();
            double waveHeightHm0 = Random.NextDouble();
            double bottomForeshoreZ = Random.NextDouble();
            double slopeForeshore = Random.NextDouble();
            double k1 = Random.NextDouble();
            double k2 = Random.NextDouble();

            // Call
            var input = new GrassWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput(
                averageNumberOfWaves, representativeWaveRunup2P, verticalDistanceWaterLevelElevation,
                criticalFrontVelocity, increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS,
                gravitationalAcceleration, frontVelocityCu, waterLevel, waveHeightHm0, bottomForeshoreZ, slopeForeshore,
                k1, k2);

            // Assert
            Assert.That(input, Is.InstanceOf<GrassWaveRunupCumulativeOverloadInput>());
            Assert.That(input.AverageNumberOfWaves, Is.EqualTo(averageNumberOfWaves));
            Assert.That(input.RepresentativeWaveRunup2P, Is.EqualTo(representativeWaveRunup2P));
            Assert.That(input.VerticalDistanceWaterLevelElevation, Is.EqualTo(verticalDistanceWaterLevelElevation));
            Assert.That(input.CriticalFrontVelocity, Is.EqualTo(criticalFrontVelocity));
            Assert.That(input.IncreasedLoadTransitionAlphaM, Is.EqualTo(increasedLoadTransitionAlphaM));
            Assert.That(input.ReducedStrengthTransitionAlphaS, Is.EqualTo(reducedStrengthTransitionAlphaS));
            Assert.That(input.GravitationalAcceleration, Is.EqualTo(gravitationalAcceleration));
            Assert.That(input.FrontVelocityCu, Is.EqualTo(frontVelocityCu));
            Assert.That(input.WaterLevel, Is.EqualTo(waterLevel));
            Assert.That(input.WaveHeightHm0, Is.EqualTo(waveHeightHm0));
            Assert.That(input.BottomForeshoreZ, Is.EqualTo(bottomForeshoreZ));
            Assert.That(input.SlopeForeshore, Is.EqualTo(slopeForeshore));
            Assert.That(input.K1, Is.EqualTo(k1));
            Assert.That(input.K2, Is.EqualTo(k2));
        }
    }
}