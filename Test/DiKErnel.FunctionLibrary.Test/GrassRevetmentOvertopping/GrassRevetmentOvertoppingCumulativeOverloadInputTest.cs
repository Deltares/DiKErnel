// // Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
// //
// // This file is part of DiKErnel.
// //
// // DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// // GNU Lesser General Public License as published by the Free Software Foundation, either
// // version 3 of the License, or (at your option) any later version.
// //
// // This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// // without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// // See the GNU Lesser General Public License for more details.
// //
// // You should have received a copy of the GNU Lesser General Public License along with this
// // program. If not, see <http://www.gnu.org/licenses/>.
// //
// // All names, logos, and references to "Deltares" are registered trademarks of Stichting
// // Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using DiKErnel.FunctionLibrary.GrassRevetment;
using DiKErnel.FunctionLibrary.GrassRevetmentOvertopping;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassRevetmentOvertopping
{
    [TestFixture]
    public class GrassRevetmentOvertoppingCumulativeOverloadInputTest
    {
        [Test]
        public void GivenInput_WhenCreated_ThenExpectedValues()
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
            double accelerationAlphaA = Random.NextDouble();
            double frontVelocityCwo = Random.NextDouble();

            // Call
            var input = new GrassRevetmentOvertoppingCumulativeOverloadInput(averageNumberOfWaves, representativeWaveRunup2P,
                                                                             fixedNumberOfWaves,
                                                                             verticalDistanceWaterLevelElevation,
                                                                             criticalFrontVelocity, increasedLoadTransitionAlphaM,
                                                                             reducedStrengthTransitionAlphaS,
                                                                             gravitationalAcceleration, accelerationAlphaA,
                                                                             frontVelocityCwo);

            // Assert
            Assert.IsInstanceOf<GrassRevetmentCumulativeOverloadInput>(input);

            Assert.AreEqual(averageNumberOfWaves, input.AverageNumberOfWaves);
            Assert.AreEqual(representativeWaveRunup2P, input.RepresentativeWaveRunup2P);
            Assert.AreEqual(fixedNumberOfWaves, input.FixedNumberOfWaves);
            Assert.AreEqual(verticalDistanceWaterLevelElevation, input.VerticalDistanceWaterLevelElevation);
            Assert.AreEqual(criticalFrontVelocity, input.CriticalFrontVelocity);
            Assert.AreEqual(increasedLoadTransitionAlphaM, input.IncreasedLoadTransitionAlphaM);
            Assert.AreEqual(reducedStrengthTransitionAlphaS, input.ReducedStrengthTransitionAlphaS);
            Assert.AreEqual(gravitationalAcceleration, input.GravitationalAcceleration);
            Assert.AreEqual(accelerationAlphaA, input.AccelerationAlphaA);
            Assert.AreEqual(frontVelocityCwo, input.FrontVelocityCwo);
        }
    }
}