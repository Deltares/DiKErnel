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

using DiKErnel.Integration.Data.GrassWaveImpact;
using NUnit.Framework;

namespace DiKErnel.Integration.TestUtil
{
    internal static class GrassWaveImpactLocationDependentInputAssertHelper
    {
        public static void AssertMinimumWaveHeight(double minimumWaveHeightTemax,
                                                   GrassWaveImpactLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.MinimumWaveHeightTemax, Is.EqualTo(minimumWaveHeightTemax));
        }

        public static void AssertMaximumWaveHeight(double maximumWaveHeightTemin,
                                                   GrassWaveImpactLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.MaximumWaveHeightTemin, Is.EqualTo(maximumWaveHeightTemin));
        }

        public static void AssertWaveAngleImpact(double waveAngleImpactNwa, double waveAngleImpactQwa,
                                                 double waveAngleImpactRwa,
                                                 GrassWaveImpactWaveAngleImpact waveAngleImpact)
        {
            Assert.That(waveAngleImpact.WaveAngleImpactNwa, Is.EqualTo(waveAngleImpactNwa));
            Assert.That(waveAngleImpact.WaveAngleImpactQwa, Is.EqualTo(waveAngleImpactQwa));
            Assert.That(waveAngleImpact.WaveAngleImpactRwa, Is.EqualTo(waveAngleImpactRwa));
        }

        public static void AssertTimeLine(double timeLineAgwi, double timeLineBgwi, double timeLineCgwi,
                                          GrassWaveImpactTimeLine timeLine)
        {
            Assert.That(timeLine.TimeLineAgwi, Is.EqualTo(timeLineAgwi));
            Assert.That(timeLine.TimeLineBgwi, Is.EqualTo(timeLineBgwi));
            Assert.That(timeLine.TimeLineCgwi, Is.EqualTo(timeLineCgwi));
        }

        public static void AssertUpperLimitLoading(double upperLimitLoadingAul,
                                                   GrassWaveImpactLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.UpperLimitLoadingAul, Is.EqualTo(upperLimitLoadingAul));
        }

        public static void AssertLowerLimitLoading(double lowerLimitLoadingAll,
                                                   GrassWaveImpactLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.LowerLimitLoadingAll, Is.EqualTo(lowerLimitLoadingAll));
        }
    }
}