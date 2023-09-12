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

using DiKErnel.Integration.Data.GrassRevetmentWaveImpact;
using NUnit.Framework;

namespace DiKErnel.Integration.TestUtil
{
    internal static class GrassRevetmentWaveImpactLocationDependentInputAssertHelper
    {
        public static void AssertMinimumWaveHeight(double minimumWaveHeightTemax,
                                                   GrassRevetmentWaveImpactLocationDependentInput locationDependentInput)
        {
            Assert.AreEqual(minimumWaveHeightTemax, locationDependentInput.MinimumWaveHeightTemax);
        }

        public static void AssertMaximumWaveHeight(double maximumWaveHeightTemin,
                                                   GrassRevetmentWaveImpactLocationDependentInput locationDependentInput)
        {
            Assert.AreEqual(maximumWaveHeightTemin, locationDependentInput.MaximumWaveHeightTemin);
        }

        public static void AssertWaveAngleImpact(double waveAngleImpactNwa, double waveAngleImpactQwa,
                                                 double waveAngleImpactRwa,
                                                 GrassRevetmentWaveImpactWaveAngleImpact waveAngleImpact)
        {
            Assert.AreEqual(waveAngleImpactNwa, waveAngleImpact.WaveAngleImpactNwa);
            Assert.AreEqual(waveAngleImpactQwa, waveAngleImpact.WaveAngleImpactQwa);
            Assert.AreEqual(waveAngleImpactRwa, waveAngleImpact.WaveAngleImpactRwa);
        }

        public static void AssertTimeLine(double timeLineAgwi, double timeLineBgwi, double timeLineCgwi,
                                          GrassRevetmentWaveImpactTimeLine timeLine)
        {
            Assert.AreEqual(timeLineAgwi, timeLine.TimeLineAgwi);
            Assert.AreEqual(timeLineBgwi, timeLine.TimeLineBgwi);
            Assert.AreEqual(timeLineCgwi, timeLine.TimeLineCgwi);
        }

        public static void AssertUpperLimitLoading(double upperLimitLoadingAul,
                                                   GrassRevetmentWaveImpactLocationDependentInput locationDependentInput)
        {
            Assert.AreEqual(upperLimitLoadingAul, locationDependentInput.UpperLimitLoadingAul);
        }

        public static void AssertLowerLimitLoading(double lowerLimitLoadingAll,
                                                   GrassRevetmentWaveImpactLocationDependentInput locationDependentInput)
        {
            Assert.AreEqual(lowerLimitLoadingAll, locationDependentInput.LowerLimitLoadingAll);
        }
    }
}