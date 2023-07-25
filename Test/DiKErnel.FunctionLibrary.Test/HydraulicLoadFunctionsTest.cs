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

using DiKErnel.TestUtil;
using NUnit.Framework;
using Random = System.Random;

namespace DiKErnel.FunctionLibrary.Test
{
    [TestFixture]
    public class HydraulicLoadFunctionsTest
    {
        private const double tolerance = 1e-6;

        [Test]
        public void WaveDirection_InputEqualTo0Degrees_ExpectedValue()
        {
            // Setup
            const double waveAngle = 0.0;

            // Call
            double waveDirection = HydraulicLoadFunctions.WaveDirection(waveAngle);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(0, waveDirection);
        }

        [Test]
        public void WaveDirection_InputLargerThan0Degrees_ExpectedValue()
        {
            // Setup
            var random = new Random(21);
            double waveAngle = tolerance + 540.0 * random.NextDouble();

            // Call
            double waveDirection = HydraulicLoadFunctions.WaveDirection(waveAngle);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(waveAngle, waveDirection);
        }

        [Test]
        public void WaveDirection_InputBetweenMinus180And0Degrees_ExpectedValue()
        {
            // Setup
            var random = new Random(21);
            double waveAngle = -180.0 + tolerance + 180.0 * random.NextDouble();

            // Call
            double waveDirection = HydraulicLoadFunctions.WaveDirection(waveAngle);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(360.0 + waveAngle, waveDirection);
        }

        [Test]
        public void WaveDirection_InputEqualToMinus180Degrees_ExpectedValue()
        {
            // Setup
            const double waveAngle = -180.0;

            // Call
            double waveDirection = HydraulicLoadFunctions.WaveDirection(waveAngle);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(180, waveDirection);
        }

        [Test]
        public void SlopeAngle_ValidInput_ExpectedValue()
        {
            // Setup
            const double outerSlope = 0.25;

            // Call
            double slopeAngle = HydraulicLoadFunctions.SlopeAngle(outerSlope);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(14.036243467926479, slopeAngle);
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
            Assert.IsFalse(loadingRevetment);
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
            Assert.IsTrue(loadingRevetment);
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
            Assert.IsTrue(loadingRevetment);
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
            Assert.IsTrue(loadingRevetment);
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
            Assert.IsFalse(loadingRevetment);
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
            AssertHelper.AssertAreEqualWithinTolerance(0.037898686325266363, waveSteepnessDeepWater);
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
            AssertHelper.AssertAreEqualWithinTolerance(1.2841859985089348, surfSimilarityParameter);
        }

        [Test]
        public void VerticalDistanceWaterLevelElevation_ValidInput_ExpectedValue()
        {
            // Setup
            const double z = 1.12;
            const double waterLevel = 0.03;

            // Call
            double verticalDistanceWaterLevelElevation =
                HydraulicLoadFunctions.VerticalWaterDistanceWaterLevelElevation(z, waterLevel);

            // Assert
            AssertHelper.AssertAreEqualWithinTolerance(1.09, verticalDistanceWaterLevelElevation);
        }
    }
}