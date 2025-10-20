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

using DiKErnel.FunctionLibrary.GrassWaveImpact;
using DiKErnel.FunctionLibrary.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassWaveImpact
{
    [TestFixture]
    internal sealed class GrassWaveImpactFunctionsTest
    {
        [Test]
        public void IncrementDamage_ValidInput_ExpectedValue()
        {
            // Setup
            const double incrementTime = 900;
            const double timeLine = 3319.12;

            // Call
            double incrementDamage = GrassWaveImpactFunctions.IncrementDamage(incrementTime, timeLine);

            // Assert
            AssertHelper.AreEqual(0.27115621007978, incrementDamage);
        }

        [Test]
        public void TimeLine_ValidInput_ExpectedValue()
        {
            // Setup
            const double waveHeightImpact = 1;
            const double timeLineAgwi = 0.8;
            const double timeLineBgwi = -0.00001944;
            const double timeLineCgwi = 0.25;

            // Call
            double timeLine = GrassWaveImpactFunctions.TimeLine(waveHeightImpact, timeLineAgwi, timeLineBgwi,
                                                                timeLineCgwi);

            // Assert
            AssertHelper.AreEqual(3319.8827745664184, timeLine);
        }

        [Test]
        public void WaveHeightImpact_ValidInput_ExpectedValue()
        {
            // Setup
            const double minimumWaveHeight = 0.25;
            const double maximumWaveHeight = 1.05;
            const double waveAngleImpact = 0.79;
            const double waveHeightHm0 = 1;

            // Call
            double waveHeightImpact = GrassWaveImpactFunctions.WaveHeightImpact(minimumWaveHeight, maximumWaveHeight,
                                                                                waveAngleImpact, waveHeightHm0);

            // Assert
            AssertHelper.AreEqual(0.79, waveHeightImpact);
        }

        [Test]
        public void MinimumWaveHeight_ValidInput_ExpectedValue()
        {
            // Setup
            const double timeLineAgwi = 0.8;
            const double timeLineBgwi = -0.00001944;
            const double timeLineCgwi = 0.25;
            const double minimumWaveHeightTemax = 3600000;

            // Call
            double minimumWaveHeight = GrassWaveImpactFunctions.MinimumWaveHeight(timeLineAgwi, timeLineBgwi,
                                                                                  timeLineCgwi, minimumWaveHeightTemax);

            // Assert
            AssertHelper.AreEqual(0.25, minimumWaveHeight);
        }

        [Test]
        public void MaximumWaveHeight_ValidInput_ExpectedValue()
        {
            // Setup
            const double timeLineAgwi = 0.8;
            const double timeLineBgwi = -0.00001944;
            const double timeLineCgwi = 0.25;
            const double maximumWaveHeightTemin = 3.6;

            // Call
            double maximumWaveHeight = GrassWaveImpactFunctions.MaximumWaveHeight(timeLineAgwi, timeLineBgwi,
                                                                                  timeLineCgwi, maximumWaveHeightTemin);

            // Assert
            AssertHelper.AreEqual(1.04994401475905, maximumWaveHeight);
        }

        [Test]
        public void WaveAngleImpact_ValidInputAndWaveAngleSmallerThan90Degrees_ExpectedValue()
        {
            // Setup
            const double waveAngle = 45;
            const double waveAngleImpactNwa = 0.67;
            const double waveAngleImpactQwa = 0.35;
            const double waveAngleImpactRwa = 10;

            // Call
            double waveAngleImpact = GrassWaveImpactFunctions.WaveAngleImpact(waveAngle, waveAngleImpactNwa,
                                                                              waveAngleImpactQwa, waveAngleImpactRwa);

            // Assert
            AssertHelper.AreEqual(0.79278413661028, waveAngleImpact);
        }

        [Test]
        public void WaveAngleImpact_ValidInputAndWaveAngleEqualTo90Degrees_ExpectedValue()
        {
            // Setup
            const double waveAngle = 90;
            const double waveAngleImpactNwa = 0.67;
            const double waveAngleImpactQwa = 0.35;
            const double waveAngleImpactRwa = 10;

            // Call
            double waveAngleImpact = GrassWaveImpactFunctions.WaveAngleImpact(waveAngle, waveAngleImpactNwa,
                                                                              waveAngleImpactQwa, waveAngleImpactRwa);

            // Assert
            AssertHelper.AreEqual(0.35, waveAngleImpact);
        }

        [Test]
        public void WaveAngleImpact_ValidInputAndWaveAngleLargerThan90Degrees_ExpectedValue()
        {
            // Setup
            const double waveAngle = 91;
            const double waveAngleImpactNwa = 0.67;
            const double waveAngleImpactQwa = 0.35;
            const double waveAngleImpactRwa = 10;

            // Call
            double waveAngleImpact = GrassWaveImpactFunctions.WaveAngleImpact(waveAngle, waveAngleImpactNwa,
                                                                              waveAngleImpactQwa, waveAngleImpactRwa);

            // Assert
            AssertHelper.AreEqual(0.315, waveAngleImpact);
        }

        [Test]
        public void UpperLimitLoading_ValidInput_ExpectedValue()
        {
            // Setup
            const double waterLevel = 0.03;
            const double waveHeightHm0 = 1;
            const double upperLimitLoadingAul = 0.001;

            // Call
            double upperLimitLoading = GrassWaveImpactFunctions.UpperLimitLoading(waterLevel, waveHeightHm0,
                                                                                  upperLimitLoadingAul);

            // Assert
            AssertHelper.AreEqual(0.029, upperLimitLoading);
        }

        [Test]
        public void LowerLimitLoading_ValidInput_ExpectedValue()
        {
            // Setup
            const double waterLevel = 0.03;
            const double waveHeightHm0 = 1;
            const double lowerLimitLoadingAll = 0.5;

            // Call
            double lowerLimitLoading = GrassWaveImpactFunctions.LowerLimitLoading(waterLevel, waveHeightHm0,
                                                                                  lowerLimitLoadingAll);

            // Assert
            AssertHelper.AreEqual(-0.47, lowerLimitLoading);
        }
    }
}