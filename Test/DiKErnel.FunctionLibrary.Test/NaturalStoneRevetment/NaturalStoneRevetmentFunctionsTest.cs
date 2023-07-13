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
    public class NaturalStoneRevetmentFunctionsTest
    {
        [Test]
        public void IncrementDamage_ValidInput_ExpectedValue()
        {
            // Setup
            const double hydraulicLoad = 0.56;
            const double resistance = 0.495;
            const double incrementDegradation = 0.078;
            const double waveAngleImpact = 0.997;

            // Call
            double incrementDamage = NaturalStoneRevetmentFunctions.IncrementDamage(hydraulicLoad, resistance, incrementDegradation,
                                                                                    waveAngleImpact);

            // Assert
            Assert.AreEqual(0.087977696969696983, incrementDamage);
        }

        [Test]
        public void HydraulicLoad_ValidInput_ExpectedValue()
        {
            // Setup
            const double surfSimilarityParameter = 1.28;
            const double waveHeightHm0 = 1.8;
            const double a = 4.0;
            const double b = 0.1;
            const double c = 0.3;
            const double n = -0.9;

            var input = new NaturalStoneRevetmentHydraulicLoadInput(surfSimilarityParameter, waveHeightHm0, a, b, c, n);

            // Call
            double hydraulicLoad = NaturalStoneRevetmentFunctions.HydraulicLoad(input);

            // Assert
            Assert.AreEqual(0.49571702636245252, hydraulicLoad);
        }

        [Test]
        public void OuterSlopeWithoutBerm_ValidInput_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 30.0;
            const double slopeLowerLevel = 5.35;
            const double slopeUpperPosition = 30.3;
            const double slopeUpperLevel = 5.425;

            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel);

            // Call
            double outerSlope = NaturalStoneRevetmentFunctions.OuterSlope(input);

            // Assert
            Assert.AreEqual(0.25, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_UpperAndLowerSlopeLevelOnLowerSlope_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 5.0;
            const double slopeLowerLevel = 0.5;
            const double slopeUpperPosition = 5.15625;
            const double slopeUpperLevel = 0.55;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7.0;
            const double notchOuterBermPosition = 25.0;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15.0;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel)
            {
                OuterToeHeight = outerToeHeight,
                OuterCrestHeight = outerCrestHeight,
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneRevetmentFunctions.OuterSlope(input);

            // Assert
            AssertHelper.AssertAreEqualWithAcceptablePrecision(0.32, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_UpperSlopeLevelOnBermAndLowerSlopeLevelOnLowerSlope_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 10.7142857142857;
            const double slopeLowerLevel = 2.3;
            const double slopeUpperPosition = 15.0;
            const double slopeUpperLevel = 3.5;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7.0;
            const double notchOuterBermPosition = 25.0;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15.0;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel)
            {
                OuterToeHeight = outerToeHeight,
                OuterCrestHeight = outerCrestHeight,
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneRevetmentFunctions.OuterSlope(input);

            // Assert
            AssertHelper.AssertAreEqualWithAcceptablePrecision(0.28, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_UpperAndLowerSlopeLevelOnBerm_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 15.0;
            const double slopeLowerLevel = 3.5;
            const double slopeUpperPosition = 18.75;
            const double slopeUpperLevel = 3.8;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7.0;
            const double notchOuterBermPosition = 25.0;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15.0;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel)
            {
                OuterToeHeight = outerToeHeight,
                OuterCrestHeight = outerCrestHeight,
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneRevetmentFunctions.OuterSlope(input);

            // Assert
            AssertHelper.AssertAreEqualWithAcceptablePrecision(0.08, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_UpperAndLowerSlopeLevelOnUpperSlope_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 25.6818181818182;
            const double slopeLowerLevel = 4.25;
            const double slopeUpperPosition = 29.0909090909091;
            const double slopeUpperLevel = 5.0;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7.0;
            const double notchOuterBermPosition = 25.0;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15.0;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel)
            {
                OuterToeHeight = outerToeHeight,
                OuterCrestHeight = outerCrestHeight,
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneRevetmentFunctions.OuterSlope(input);

            // Assert
            AssertHelper.AssertAreEqualWithAcceptablePrecision(0.22, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_UpperSlopeLevelOnUpperSlopeAndLowerSlopeLevelOnBerm_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 24.375;
            const double slopeLowerLevel = 4.075;
            const double slopeUpperPosition = 40.0;
            const double slopeUpperLevel = 7.0;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7.0;
            const double notchOuterBermPosition = 25.0;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15.0;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel)
            {
                OuterToeHeight = outerToeHeight,
                OuterCrestHeight = outerCrestHeight,
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneRevetmentFunctions.OuterSlope(input);

            // Assert
            AssertHelper.AssertAreEqualWithAcceptablePrecision(0.19333333333333, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_UpperSlopeLevelOnUpperSlopeAndLowerSlopeLevelOnLowerSlope_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 12.5;
            const double slopeLowerLevel = 2.8;
            const double slopeUpperPosition = 40.0;
            const double slopeUpperLevel = 7.0;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7.0;
            const double notchOuterBermPosition = 25.0;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15.0;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel)
            {
                OuterToeHeight = outerToeHeight,
                OuterCrestHeight = outerCrestHeight,
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneRevetmentFunctions.OuterSlope(input);

            // Assert
            AssertHelper.AssertAreEqualWithAcceptablePrecision(0.20871481028151, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_UpperSlopeAboveOuterCrest_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 12.5;
            const double slopeLowerLevel = 2.8;
            const double slopeUpperPosition = 45.0;
            const double slopeUpperLevel = 7.1;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7.0;
            const double notchOuterBermPosition = 25.0;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15.0;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel)
            {
                OuterToeHeight = outerToeHeight,
                OuterCrestHeight = outerCrestHeight,
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneRevetmentFunctions.OuterSlope(input);

            // Assert
            Assert.AreEqual(double.PositiveInfinity, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_LowerSlopeBelowOuterToe_ExpectedValue()
        {
            // Setup

            const double slopeLowerPosition = 0.0;
            const double slopeLowerLevel = 0.4;
            const double slopeUpperPosition = 40.0;
            const double slopeUpperLevel = 7.0;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7.0;
            const double notchOuterBermPosition = 25.0;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15.0;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                 slopeUpperLevel)
            {
                OuterToeHeight = outerToeHeight,
                OuterCrestHeight = outerCrestHeight,
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneRevetmentFunctions.OuterSlope(input);

            // Assert
            Assert.AreEqual(double.PositiveInfinity, outerSlope);
        }
    }
}