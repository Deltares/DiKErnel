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
            Assert.AreEqual(0.0, input.OuterToeHeight);
            Assert.AreEqual(0.0, input.OuterCrestHeight);
            Assert.AreEqual(double.PositiveInfinity, input.NotchOuterBermPosition);
            Assert.AreEqual(double.PositiveInfinity, input.NotchOuterBermHeight);
            Assert.AreEqual(double.PositiveInfinity, input.CrestOuterBermPosition);
            Assert.AreEqual(double.PositiveInfinity, input.CrestOuterBermHeight);
            Assert.IsFalse(input.HasBerm);
        }

        [Test]
        public void HasBerm_NotchOuterBermPositionInfinite_ReturnsFalse()
        {
            // Setup
            double slopeLowerPosition = Random.NextDouble();
            double slopeLowerLevel = Random.NextDouble();
            double slopeUpperPosition = Random.NextDouble();
            double slopeUpperLevel = Random.NextDouble();

            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel)
            {
                NotchOuterBermHeight = 0.1,
                CrestOuterBermPosition = 0.2,
                CrestOuterBermHeight = 0.3
            };

            // Call
            bool hasBerm = input.HasBerm;

            // Assert
            Assert.IsFalse(hasBerm);
        }

        [Test]
        public void HasBerm_NotchOuterBermHeightInfinite_ReturnsFalse()
        {
            // Setup
            double slopeLowerPosition = Random.NextDouble();
            double slopeLowerLevel = Random.NextDouble();
            double slopeUpperPosition = Random.NextDouble();
            double slopeUpperLevel = Random.NextDouble();

            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel)
            {
                NotchOuterBermPosition = 0.1,
                CrestOuterBermPosition = 0.2,
                CrestOuterBermHeight = 0.3
            };

            // Call
            bool hasBerm = input.HasBerm;

            // Assert
            Assert.IsFalse(hasBerm);
        }

        [Test]
        public void HasBerm_CrestOuterBermPositionInfinite_ReturnsFalse()
        {
            // Setup
            double slopeLowerPosition = Random.NextDouble();
            double slopeLowerLevel = Random.NextDouble();
            double slopeUpperPosition = Random.NextDouble();
            double slopeUpperLevel = Random.NextDouble();

            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel)
            {
                NotchOuterBermPosition = 0.1,
                NotchOuterBermHeight = 0.2,
                CrestOuterBermHeight = 0.3
            };

            // Call
            bool hasBerm = input.HasBerm;

            // Assert
            Assert.IsFalse(hasBerm);
        }

        [Test]
        public void HasBerm_CrestOuterBermHeightInfinite_ReturnsFalse()
        {
            // Setup
            double slopeLowerPosition = Random.NextDouble();
            double slopeLowerLevel = Random.NextDouble();
            double slopeUpperPosition = Random.NextDouble();
            double slopeUpperLevel = Random.NextDouble();

            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel)
            {
                NotchOuterBermPosition = 0.1,
                NotchOuterBermHeight = 0.2,
                CrestOuterBermPosition = 0.3
            };

            // Call
            bool hasBerm = input.HasBerm;

            // Assert
            Assert.IsFalse(hasBerm);
        }

        [Test]
        public void HasBerm_AllBermPropertiesNotInfinite_ReturnsTrue()
        {
            // Setup
            double slopeLowerPosition = Random.NextDouble();
            double slopeLowerLevel = Random.NextDouble();
            double slopeUpperPosition = Random.NextDouble();
            double slopeUpperLevel = Random.NextDouble();

            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel)
            {
                NotchOuterBermPosition = 0.1,
                NotchOuterBermHeight = 0.2,
                CrestOuterBermPosition = 0.3,
                CrestOuterBermHeight = 0.4
            };

            // Call
            bool hasBerm = input.HasBerm;

            // Assert
            Assert.IsTrue(hasBerm);
        }
    }
}