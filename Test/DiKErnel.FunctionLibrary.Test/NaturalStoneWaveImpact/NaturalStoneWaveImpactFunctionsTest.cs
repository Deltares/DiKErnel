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
using AssertHelper = DiKErnel.FunctionLibrary.TestUtil.AssertHelper;

namespace DiKErnel.FunctionLibrary.Test.NaturalStoneWaveImpact
{
    [TestFixture]
    internal sealed class NaturalStoneWaveImpactFunctionsTest
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
            double incrementDamage = NaturalStoneWaveImpactFunctions.IncrementDamage(hydraulicLoad, resistance,
                                                                                     incrementDegradation,
                                                                                     waveAngleImpact);

            // Assert
            AssertHelper.AreEqual(0.08797769696969, incrementDamage);
        }

        [Test]
        public void HydraulicLoad_ValidInput_ExpectedValue()
        {
            // Setup
            const double surfSimilarityParameter = 1.28;
            const double waveHeightHm0 = 1.8;
            const double a = 4;
            const double b = 0.1;
            const double c = 0.3;
            const double n = -0.9;

            var input = new NaturalStoneWaveImpactHydraulicLoadInput(surfSimilarityParameter, waveHeightHm0, a, b, c, n);

            // Call
            double hydraulicLoad = NaturalStoneWaveImpactFunctions.HydraulicLoad(input);

            // Assert
            AssertHelper.AreEqual(0.49571702636245, hydraulicLoad);
        }

        [Test]
        public void OuterSlopeWithoutBerm_ValidInput_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 30;
            const double slopeLowerLevel = 5.35;
            const double slopeUpperPosition = 30.3;
            const double slopeUpperLevel = 5.425;

            var input = new NaturalStoneWaveImpactOuterSlopeInput(slopeLowerPosition, slopeLowerLevel,
                                                                  slopeUpperPosition, slopeUpperLevel,
                                                                  Random.NextDouble(), Random.NextDouble());

            // Call
            double outerSlope = NaturalStoneWaveImpactFunctions.OuterSlope(input);

            // Assert
            AssertHelper.AreEqual(0.25, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_UpperAndLowerSlopeLevelOnLowerSlope_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 5;
            const double slopeLowerLevel = 0.5;
            const double slopeUpperPosition = 5.15625;
            const double slopeUpperLevel = 0.55;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7;
            const double notchOuterBermPosition = 25;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneWaveImpactOuterSlopeInput(slopeLowerPosition, slopeLowerLevel,
                                                                  slopeUpperPosition, slopeUpperLevel, outerToeHeight,
                                                                  outerCrestHeight)
            {
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneWaveImpactFunctions.OuterSlope(input);

            // Assert
            AssertHelper.AreEqual(0.32, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_UpperSlopeLevelOnBermAndLowerSlopeLevelOnLowerSlope_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 10.7142857142857;
            const double slopeLowerLevel = 2.3;
            const double slopeUpperPosition = 15;
            const double slopeUpperLevel = 3.5;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7;
            const double notchOuterBermPosition = 25;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneWaveImpactOuterSlopeInput(slopeLowerPosition, slopeLowerLevel,
                                                                  slopeUpperPosition, slopeUpperLevel, outerToeHeight,
                                                                  outerCrestHeight)
            {
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneWaveImpactFunctions.OuterSlope(input);

            // Assert
            AssertHelper.AreEqual(0.28, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_UpperAndLowerSlopeLevelOnBerm_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 15;
            const double slopeLowerLevel = 3.5;
            const double slopeUpperPosition = 18.75;
            const double slopeUpperLevel = 3.8;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7;
            const double notchOuterBermPosition = 25;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneWaveImpactOuterSlopeInput(slopeLowerPosition, slopeLowerLevel,
                                                                  slopeUpperPosition, slopeUpperLevel, outerToeHeight,
                                                                  outerCrestHeight)
            {
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneWaveImpactFunctions.OuterSlope(input);

            // Assert
            AssertHelper.AreEqual(0.08, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_UpperAndLowerSlopeLevelOnUpperSlope_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 25.6818181818182;
            const double slopeLowerLevel = 4.25;
            const double slopeUpperPosition = 29.0909090909091;
            const double slopeUpperLevel = 5;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7;
            const double notchOuterBermPosition = 25;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneWaveImpactOuterSlopeInput(slopeLowerPosition, slopeLowerLevel,
                                                                  slopeUpperPosition, slopeUpperLevel, outerToeHeight,
                                                                  outerCrestHeight)
            {
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneWaveImpactFunctions.OuterSlope(input);

            // Assert
            AssertHelper.AreEqual(0.22, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_UpperSlopeLevelOnUpperSlopeAndLowerSlopeLevelOnBerm_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 24.375;
            const double slopeLowerLevel = 4.075;
            const double slopeUpperPosition = 40;
            const double slopeUpperLevel = 7;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7;
            const double notchOuterBermPosition = 25;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneWaveImpactOuterSlopeInput(slopeLowerPosition, slopeLowerLevel,
                                                                  slopeUpperPosition, slopeUpperLevel, outerToeHeight,
                                                                  outerCrestHeight)
            {
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneWaveImpactFunctions.OuterSlope(input);

            // Assert
            AssertHelper.AreEqual(0.19333333333333, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_UpperSlopeLevelOnUpperSlopeAndLowerSlopeLevelOnLowerSlope_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 12.5;
            const double slopeLowerLevel = 2.8;
            const double slopeUpperPosition = 40;
            const double slopeUpperLevel = 7;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7;
            const double notchOuterBermPosition = 25;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneWaveImpactOuterSlopeInput(slopeLowerPosition, slopeLowerLevel,
                                                                  slopeUpperPosition, slopeUpperLevel, outerToeHeight,
                                                                  outerCrestHeight)
            {
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneWaveImpactFunctions.OuterSlope(input);

            // Assert
            AssertHelper.AreEqual(0.20871481028151, outerSlope);
        }

        [Test]
        public void OuterSlopeWithBerm_UpperSlopeAboveOuterCrest_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 12.5;
            const double slopeLowerLevel = 2.8;
            const double slopeUpperPosition = 45;
            const double slopeUpperLevel = 7.1;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7;
            const double notchOuterBermPosition = 25;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneWaveImpactOuterSlopeInput(slopeLowerPosition, slopeLowerLevel,
                                                                  slopeUpperPosition, slopeUpperLevel, outerToeHeight,
                                                                  outerCrestHeight)
            {
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneWaveImpactFunctions.OuterSlope(input);

            // Assert
            Assert.That(outerSlope, Is.NaN);
        }

        [Test]
        public void OuterSlopeWithBerm_LowerSlopeBelowOuterToe_ExpectedValue()
        {
            // Setup
            const double slopeLowerPosition = 0;
            const double slopeLowerLevel = 0.4;
            const double slopeUpperPosition = 40;
            const double slopeUpperLevel = 7;
            const double outerToeHeight = 0.5;
            const double outerCrestHeight = 7;
            const double notchOuterBermPosition = 25;
            const double notchOuterBermHeight = 4.1;
            const double crestOuterBermPosition = 15;
            const double crestOuterBermHeight = 3.5;

            var input = new NaturalStoneWaveImpactOuterSlopeInput(slopeLowerPosition, slopeLowerLevel,
                                                                  slopeUpperPosition, slopeUpperLevel, outerToeHeight,
                                                                  outerCrestHeight)
            {
                NotchOuterBermPosition = notchOuterBermPosition,
                NotchOuterBermHeight = notchOuterBermHeight,
                CrestOuterBermPosition = crestOuterBermPosition,
                CrestOuterBermHeight = crestOuterBermHeight
            };

            // Call
            double outerSlope = NaturalStoneWaveImpactFunctions.OuterSlope(input);

            // Assert
            Assert.That(outerSlope, Is.NaN);
        }

        [Test]
        public void SlopeUpperLevel_ValidInput_ExpectedValue()
        {
            // Setup
            const double outerToeHeight = 5.35;
            const double outerCrestHeight = 14.1;
            const double waterLevel = 0.1;
            const double waveHeightHm0 = 1.5;
            const double slopeUpperLevelAus = 0.05;

            // Call
            double slopeUpperLevel = NaturalStoneWaveImpactFunctions.SlopeUpperLevel(outerToeHeight, outerCrestHeight,
                                                                                     waterLevel, waveHeightHm0,
                                                                                     slopeUpperLevelAus);

            // Assert
            AssertHelper.AreEqual(5.425, slopeUpperLevel);
        }

        [Test]
        public void SlopeLowerLevel_ValidInput_ExpectedValue()
        {
            // Setup
            const double outerToeHeight = 5.35;
            const double slopeUpperLevel = 5.425;
            const double waveHeightHm0 = 1.5;
            const double slopeLowerLevelAls = 1.5;

            // Call
            double slopeLowerLevel = NaturalStoneWaveImpactFunctions.SlopeLowerLevel(outerToeHeight, slopeUpperLevel,
                                                                                     waveHeightHm0, slopeLowerLevelAls);

            // Assert
            AssertHelper.AreEqual(5.35, slopeLowerLevel);
        }

        [Test]
        public void UpperLimitLoading_ValidInput_ExpectedValue()
        {
            // Setup
            const double depthMaximumWaveLoad = 0.38;
            const double surfSimilarityParameter = 1.28;
            const double waterLevel = 1.77;
            const double waveHeightHm0 = 1.8;
            const double a = 0.1;
            const double b = 0.6;
            const double c = 4;

            var input = new NaturalStoneWaveImpactLimitLoadingInput(depthMaximumWaveLoad, surfSimilarityParameter,
                                                                    waterLevel, waveHeightHm0, a, b, c);

            // Call
            double upperLimitLoading = NaturalStoneWaveImpactFunctions.UpperLimitLoading(input);

            // Assert
            AssertHelper.AreEqual(2.3924, upperLimitLoading);
        }

        [Test]
        public void LowerLimitLoading_ValidInput_ExpectedValue()
        {
            // Setup
            const double depthMaximumWaveLoad = 0.38;
            const double surfSimilarityParameter = 1.28;
            const double waterLevel = 1.77;
            const double waveHeightHm0 = 1.8;
            const double a = 0.1;
            const double b = 0.2;
            const double c = 4;

            var input = new NaturalStoneWaveImpactLimitLoadingInput(depthMaximumWaveLoad, surfSimilarityParameter,
                                                                    waterLevel, waveHeightHm0, a, b, c);

            // Call
            double lowerLimitLoading = NaturalStoneWaveImpactFunctions.LowerLimitLoading(input);

            // Assert
            AssertHelper.AreEqual(1.29, lowerLimitLoading);
        }

        [Test]
        public void DepthMaximumWaveLoad_ValidInput_ExpectedValue()
        {
            // Setup
            const double distanceMaximumWaveElevation = 2.25;
            const double normativeWidthWaveImpact = 1.47;
            const double slopeAngle = 14.037;

            // Call
            double depthMaximumWaveLoad = NaturalStoneWaveImpactFunctions.DepthMaximumWaveLoad(
                distanceMaximumWaveElevation, normativeWidthWaveImpact, slopeAngle);

            // Assert
            AssertHelper.AreEqual(0.38425846631481, depthMaximumWaveLoad);
        }

        [Test]
        public void DistanceMaximumWaveElevation_ValidInput_ExpectedValue()
        {
            // Setup
            const double impactShallowWater = 1.1;
            const double waveSteepnessDeepWater = 0.038;
            const double waveHeightHm0 = 1.8;
            const double distanceMaximumWaveElevationAsmax = 0.42;
            const double distanceMaximumWaveElevationBsmax = 0.9;

            // Call
            double distanceMaximumWaveElevation = NaturalStoneWaveImpactFunctions.DistanceMaximumWaveElevation(
                impactShallowWater, waveSteepnessDeepWater, waveHeightHm0, distanceMaximumWaveElevationAsmax,
                distanceMaximumWaveElevationBsmax);

            // Assert
            AssertHelper.AreEqual(2.48401798797007, distanceMaximumWaveElevation);
        }

        [Test]
        public void NormativeWidthWaveImpact_ValidInput_ExpectedValue()
        {
            // Setup
            const double surfSimilarityParameter = 1.28;
            const double waveHeightHm0 = 1.8;
            const double normativeWidthWaveImpactAwi = 0.96;
            const double normativeWidthWaveImpactBwi = 0.11;

            // Call
            double normativeWidthWaveImpact = NaturalStoneWaveImpactFunctions.NormativeWidthWaveImpact(
                surfSimilarityParameter, waveHeightHm0, normativeWidthWaveImpactAwi, normativeWidthWaveImpactBwi);

            // Assert
            AssertHelper.AreEqual(1.47456, normativeWidthWaveImpact);
        }

        [Test]
        public static void WaveAngleImpact_ValidInput_ExpectedValue()
        {
            // Setup
            const double waveAngle = 5;
            const double waveAngleImpactBetamax = 78;

            // Call
            double waveAngleImpact = NaturalStoneWaveImpactFunctions.WaveAngleImpact(waveAngle, waveAngleImpactBetamax);

            // Assert
            AssertHelper.AreEqual(0.99746152040928, waveAngleImpact);
        }

        [Test]
        public void Resistance_ValidInput_ExpectedValue()
        {
            // Setup
            const double relativeDensity = 1.65;
            const double thicknessTopLayer = 0.3;

            // Call
            double resistance = NaturalStoneWaveImpactFunctions.Resistance(relativeDensity, thicknessTopLayer);

            // Assert
            AssertHelper.AreEqual(0.495, resistance);
        }

        [Test]
        public static void IncrementDegradation_ValidInput_ExpectedValue()
        {
            // Setup
            const double referenceTimeDegradation = 579.743;
            const double incrementTime = 900;
            const double wavePeriodTm10 = 5.5;

            // Call
            double incrementDegradation = NaturalStoneWaveImpactFunctions.IncrementDegradation(
                referenceTimeDegradation, incrementTime, wavePeriodTm10);

            // Assert
            AssertHelper.AreEqual(0.07844247200477, incrementDegradation);
        }

        [Test]
        public void ReferenceTimeDegradation_ValidInput_ExpectedValue()
        {
            // Setup
            const double referenceDegradation = 0.802;
            const double wavePeriodTm10 = 5.5;

            // Call
            double referenceTimeDegradation = NaturalStoneWaveImpactFunctions.ReferenceTimeDegradation(
                referenceDegradation, wavePeriodTm10);

            // Assert
            AssertHelper.AreEqual(605.48915987364103, referenceTimeDegradation);
        }

        [Test]
        public void ReferenceDegradation_ValidInput_ExpectedValue()
        {
            // Setup
            const double resistance = 0.495;
            const double hydraulicLoad = 0.56;
            const double waveAngleImpact = 0.997;
            const double initialDamage = 0.905;

            // Call
            double referenceDegradation = NaturalStoneWaveImpactFunctions.ReferenceDegradation(
                resistance, hydraulicLoad, waveAngleImpact, initialDamage);

            // Assert
            AssertHelper.AreEqual(0.80236244447628, referenceDegradation);
        }

        [Test]
        public void DurationInTimeStepFailure_ValidInput_ExpectedValue()
        {
            // Setup
            const double referenceTimeFailure = 845.9;
            const double referenceTimeDegradation = 497.7;

            // Call
            double durationInTimeStepFailure = NaturalStoneWaveImpactFunctions.DurationInTimeStepFailure(
                referenceTimeFailure, referenceTimeDegradation);

            // Assert
            AssertHelper.AreEqual(348.2, durationInTimeStepFailure);
        }

        [Test]
        public void ReferenceTimeFailure_ValidInput_ExpectedValue()
        {
            // Setup
            const double referenceFailure = 0.84;
            const double wavePeriodTm10 = 5.5;

            // Call
            double referenceTimeFailure = NaturalStoneWaveImpactFunctions.ReferenceTimeFailure(
                referenceFailure, wavePeriodTm10);

            // Assert
            AssertHelper.AreEqual(961.95675821289467, referenceTimeFailure);
        }

        [Test]
        public void ReferenceFailure_ValidInput_ExpectedValue()
        {
            // Setup
            const double resistance = 0.495;
            const double hydraulicLoad = 0.56;
            const double waveAngleImpact = 0.997;
            const double failureNumber = 0.95;

            // Call
            double referenceFailure = NaturalStoneWaveImpactFunctions.ReferenceFailure(
                resistance, hydraulicLoad, waveAngleImpact, failureNumber);

            // Assert
            AssertHelper.AreEqual(0.84225891961599, referenceFailure);
        }
    }
}