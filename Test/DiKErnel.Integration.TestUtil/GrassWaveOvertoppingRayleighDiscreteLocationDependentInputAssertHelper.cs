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

using DiKErnel.Integration.Data.GrassWaveOvertopping;
using NUnit.Framework;

namespace DiKErnel.Integration.TestUtil
{
    internal static class GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper
    {
        public static void AssertGeneralProperties(double? dikeHeight,
                                                   GrassWaveOvertoppingRayleighDiscreteLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.EnforcedDikeHeight, Is.EqualTo(dikeHeight));
        }

        public static void AssertCumulativeOverload(double criticalCumulativeOverload, int fixedNumberOfWaves,
                                                    GrassWaveOvertoppingRayleighDiscreteLocationDependentInput locationDependentInput)
        {
            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertCumulativeOverload(
                criticalCumulativeOverload, locationDependentInput);

            Assert.That(locationDependentInput.FixedNumberOfWaves, Is.EqualTo(fixedNumberOfWaves));
        }

        public static void AssertFrontVelocity(double criticalFrontVelocity, double frontVelocityCwo,
                                               GrassWaveOvertoppingRayleighDiscreteLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.CriticalFrontVelocity, Is.EqualTo(criticalFrontVelocity));
            Assert.That(locationDependentInput.FrontVelocityCwo, Is.EqualTo(frontVelocityCwo));
        }

        public static void AssertAverageNumberOfWaves(double averageNumberOfWavesCtm,
                                                      GrassWaveOvertoppingRayleighDiscreteLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.AverageNumberOfWavesCtm, Is.EqualTo(averageNumberOfWavesCtm));
        }

        public static void AssertAccelerationAlphaA(
            double accelerationAlphaAForCrest, double accelerationAlphaAForInnerSlope,
            GrassWaveOvertoppingRayleighDiscreteAccelerationAlphaA accelerationAlphaA)
        {
            Assert.That(accelerationAlphaA.ValueAtCrest, Is.EqualTo(accelerationAlphaAForCrest));
            Assert.That(accelerationAlphaA.ValueAtInnerSlope, Is.EqualTo(accelerationAlphaAForInnerSlope));
        }
    }
}