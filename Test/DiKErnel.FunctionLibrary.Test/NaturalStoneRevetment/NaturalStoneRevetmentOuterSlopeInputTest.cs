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

using DiKErnel.FunctionLibrary.NaturalStoneRevetment;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.NaturalStoneRevetment
{
    [TestFixture]
    public class NaturalStoneRevetmentOuterSlopeInputTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            double slopeLowerPosition = Random.NextDouble();
            double slopeLowerLevel = Random.NextDouble();
            double slopeUpperPosition = Random.NextDouble();
            double slopeUpperLevel = Random.NextDouble();

            // Call
            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel);

            // Assert
            Assert.AreEqual(slopeLowerPosition, input.SlopeLowerPosition);
            Assert.AreEqual(slopeLowerLevel, input.SlopeLowerLevel);
            Assert.AreEqual(slopeUpperPosition, input.SlopeUpperPosition);
            Assert.AreEqual(slopeUpperLevel, input.SlopeUpperLevel);
            Assert.AreEqual(0, input.OuterToeHeight);
            Assert.AreEqual(0, input.OuterCrestHeight);
            Assert.AreEqual(double.PositiveInfinity, input.NotchOuterBermPosition);
            Assert.AreEqual(double.PositiveInfinity, input.NotchOuterBermHeight);
            Assert.AreEqual(double.PositiveInfinity, input.CrestOuterBermPosition);
            Assert.AreEqual(double.PositiveInfinity, input.CrestOuterBermHeight);
        }
    }
}