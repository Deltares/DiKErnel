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

using DiKErnel.FunctionLibrary.GrassRevetment;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassRevetment
{
    [TestFixture]
    public class GrassRevetmentCumulativeOverloadInputTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            double averageNumberOfWaves = Random.NextDouble();
            double representativeWaveRunup2P = Random.NextDouble();
            int fixedNumberOfWaves = Random.Next();
            double verticalDistanceWaterLevelElevation = Random.NextDouble();
            double criticalFrontVelocity = Random.NextDouble();
            double increasedLoadTransitionAlphaM = Random.NextDouble();
            double reducedStrengthTransitionAlphaS = Random.NextDouble();
            double gravitationalAcceleration = Random.NextDouble();

            // Call
            var input = new GrassRevetmentCumulativeOverloadInput(averageNumberOfWaves, representativeWaveRunup2P,
                                                                  fixedNumberOfWaves, verticalDistanceWaterLevelElevation,
                                                                  criticalFrontVelocity, increasedLoadTransitionAlphaM,
                                                                  reducedStrengthTransitionAlphaS, gravitationalAcceleration);

            // Assert
            Assert.AreEqual(averageNumberOfWaves, input.AverageNumberOfWaves);
            Assert.AreEqual(representativeWaveRunup2P, input.RepresentativeWaveRunup2P);
            Assert.AreEqual(fixedNumberOfWaves, input.FixedNumberOfWaves);
            Assert.AreEqual(verticalDistanceWaterLevelElevation, input.VerticalDistanceWaterLevelElevation);
            Assert.AreEqual(criticalFrontVelocity, input.CriticalFrontVelocity);
            Assert.AreEqual(increasedLoadTransitionAlphaM, input.IncreasedLoadTransitionAlphaM);
            Assert.AreEqual(reducedStrengthTransitionAlphaS, input.ReducedStrengthTransitionAlphaS);
            Assert.AreEqual(gravitationalAcceleration, input.GravitationalAcceleration);
        }
    }
}