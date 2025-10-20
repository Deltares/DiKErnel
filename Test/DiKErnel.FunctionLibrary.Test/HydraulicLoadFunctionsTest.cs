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

using DiKErnel.FunctionLibrary.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test
{
    [TestFixture]
    internal sealed class HydraulicLoadFunctionsTest
    {
        private const double epsilon = 1e-6;

        [Test]
        [TestCase(45, 30, 15)]
        [TestCase(30, 45, -15)]
        [TestCase(270, 45, -135)]
        [TestCase(45, 270, 135)]
        [TestCase(360, 0, 0)]
        [TestCase(0, 360, 0)]
        [TestCase(0, 0, 0)]
        [TestCase(360, 360, 0)]
        [TestCase(180 + epsilon, 0, -180 + epsilon)]
        [TestCase(0, 180 + epsilon, 180 - epsilon)]
        public void WaveAngle_VariousScenarios_ExpectedValue(double waveDirection, double dikeOrientation,
                                                             double expectedWaveAngle)
        {
            // Call
            double waveAngle = HydraulicLoadFunctions.WaveAngle(waveDirection, dikeOrientation);

            // Assert
            AssertHelper.AreEqual(expectedWaveAngle, waveAngle);
        }

        [Test]
        public void SlopeAngle_ValidInput_ExpectedValue()
        {
            // Setup
            const double outerSlope = 0.25;

            // Call
            double slopeAngle = HydraulicLoadFunctions.SlopeAngle(outerSlope);

            // Assert
            AssertHelper.AreEqual(14.03624346792647, slopeAngle);
        }

        [Test]
        public void LoadingRevetment_LowerLimitAndUpperLimitSmallerThanZ_ExpectedFalse()
        {
            // Setup
            const double lowerLimitLoadingRevetment = 1.3;
            const double upperLimitLoadingRevetment = 1.4;
            const double z = 1.5;

            // Call
            bool loadingRevetment = HydraulicLoadFunctions.LoadingRevetment(lowerLimitLoadingRevetment,
                                                                            upperLimitLoadingRevetment, z);

            // Assert
            Assert.That(loadingRevetment, Is.False);
        }

        [Test]
        public void LoadingRevetment_LowerLimitSmallerThanAndUpperLimitEqualToZ_ExpectedTrue()
        {
            // Setup
            const double lowerLimitLoadingRevetment = 1.4;
            const double upperLimitLoadingRevetment = 1.5;
            const double z = 1.5;

            // Call
            bool loadingRevetment = HydraulicLoadFunctions.LoadingRevetment(lowerLimitLoadingRevetment,
                                                                            upperLimitLoadingRevetment, z);

            // Assert
            Assert.That(loadingRevetment, Is.True);
        }

        [Test]
        public void LoadingRevetment_LowerLimitSmallerAndUpperLimitLargerThanZ_ExpectedTrue()
        {
            // Setup
            const double lowerLimitLoadingRevetment = 1.4;
            const double upperLimitLoadingRevetment = 1.6;
            const double z = 1.5;

            // Call
            bool loadingRevetment = HydraulicLoadFunctions.LoadingRevetment(lowerLimitLoadingRevetment,
                                                                            upperLimitLoadingRevetment, z);

            // Assert
            Assert.That(loadingRevetment, Is.True);
        }

        [Test]
        public void LoadingRevetment_LowerLimitEqualToAndUpperLimitLargerThanZ_ExpectedTrue()
        {
            // Setup
            const double lowerLimitLoadingRevetment = 1.5;
            const double upperLimitLoadingRevetment = 1.6;
            const double z = 1.5;

            // Call
            bool loadingRevetment = HydraulicLoadFunctions.LoadingRevetment(lowerLimitLoadingRevetment,
                                                                            upperLimitLoadingRevetment, z);

            // Assert
            Assert.That(loadingRevetment, Is.True);
        }

        [Test]
        public void LoadingRevetment_LowerLimitAndUpperLimitLargerThanZ_ExpectedFalse()
        {
            // Setup
            const double lowerLimitLoadingRevetment = 1.6;
            const double upperLimitLoadingRevetment = 1.7;
            const double z = 1.5;

            // Call
            bool loadingRevetment = HydraulicLoadFunctions.LoadingRevetment(lowerLimitLoadingRevetment,
                                                                            upperLimitLoadingRevetment, z);

            // Assert
            Assert.That(loadingRevetment, Is.False);
        }

        [Test]
        public void WaveSteepnessDeepWater_ValidInput_ExpectedValue()
        {
            // Setup
            const double waveHeightHm0 = 1.6;
            const double wavePeriodTm10 = 5.2;
            const double gravitationalAcceleration = 9.81;

            // Call
            double waveSteepnessDeepWater = HydraulicLoadFunctions.WaveSteepnessDeepWater(waveHeightHm0, wavePeriodTm10,
                                                                                          gravitationalAcceleration);

            // Assert
            AssertHelper.AreEqual(0.03789868632526, waveSteepnessDeepWater);
        }

        [Test]
        public void SurfSimilarityParameter_ValidInput_ExpectedValue()
        {
            // Setup
            const double outerSlope = 0.25;
            const double waveHeightHm0 = 1.6;
            const double wavePeriodTm10 = 5.2;
            const double gravitationalAcceleration = 9.81;

            // Call
            double surfSimilarityParameter = HydraulicLoadFunctions.SurfSimilarityParameter(outerSlope, waveHeightHm0,
                                                                                            wavePeriodTm10,
                                                                                            gravitationalAcceleration);
            // Assert
            AssertHelper.AreEqual(1.28418599850893, surfSimilarityParameter);
        }

        [Test]
        public void VerticalDistanceWaterLevelElevation_ValidInput_ExpectedValue()
        {
            // Setup
            const double z = 1.12;
            const double waterLevel = 0.03;

            // Call
            double verticalDistanceWaterLevelElevation =
                HydraulicLoadFunctions.VerticalDistanceWaterLevelElevation(z, waterLevel);

            // Assert
            AssertHelper.AreEqual(1.09, verticalDistanceWaterLevelElevation);
        }
    }
}