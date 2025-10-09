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

using DiKErnel.FunctionLibrary.GrassWaveRunup;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassWaveRunup
{
    [TestFixture]
    internal sealed class GrassWaveRunupRayleighDiscreteCumulativeOverloadInputTest
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
            int fixedNumberOfWaves = Random.Next();

            // Call
            var input = new GrassWaveRunupRayleighDiscreteCumulativeOverloadInput(averageNumberOfWaves,
                                                                                  representativeWaveRunup2P,
                                                                                  verticalDistanceWaterLevelElevation,
                                                                                  criticalFrontVelocity,
                                                                                  increasedLoadTransitionAlphaM,
                                                                                  reducedStrengthTransitionAlphaS,
                                                                                  gravitationalAcceleration,
                                                                                  frontVelocityCu,
                                                                                  fixedNumberOfWaves);

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
            Assert.That(input.FixedNumberOfWaves, Is.EqualTo(fixedNumberOfWaves));
        }
    }
}