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

using DiKErnel.Integration.Data.GrassOvertopping;
using NUnit.Framework;

namespace DiKErnel.Integration.TestUtil
{
    internal static class GrassRevetmentOvertoppingLocationDependentInputAssertHelper
    {
        public static void AssertGeneralProperties(double? dikeHeight,
                                                   GrassRevetmentOvertoppingLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.EnforcedDikeHeight, Is.EqualTo(dikeHeight));
        }

        public static void AssertCumulativeOverload(double criticalCumulativeOverload, int fixedNumberOfWaves,
                                                    GrassRevetmentOvertoppingLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.CriticalCumulativeOverload, Is.EqualTo(criticalCumulativeOverload));
            Assert.That(locationDependentInput.FixedNumberOfWaves, Is.EqualTo(fixedNumberOfWaves));
        }

        public static void AssertFrontVelocity(double criticalFrontVelocity, double frontVelocityCwo,
                                               GrassRevetmentOvertoppingLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.CriticalFrontVelocity, Is.EqualTo(criticalFrontVelocity));
            Assert.That(locationDependentInput.FrontVelocityCwo, Is.EqualTo(frontVelocityCwo));
        }

        public static void AssertTransitionAlpha(double increasedLoadTransitionAlphaM,
                                                 double reducedStrengthTransitionAlphaS,
                                                 GrassRevetmentOvertoppingLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.IncreasedLoadTransitionAlphaM, Is.EqualTo(increasedLoadTransitionAlphaM));
            Assert.That(locationDependentInput.ReducedStrengthTransitionAlphaS, Is.EqualTo(reducedStrengthTransitionAlphaS));
        }

        public static void AssertAverageNumberOfWaves(double averageNumberOfWavesCtm,
                                                      GrassRevetmentOvertoppingLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.AverageNumberOfWavesCtm, Is.EqualTo(averageNumberOfWavesCtm));
        }

        public static void AssertAccelerationAlphaA(
            double accelerationAlphaAForCrest, double accelerationAlphaAForInnerSlope,
            GrassOvertoppingRayleighDiscreteAccelerationAlphaA accelerationAlphaA)
        {
            Assert.That(accelerationAlphaA.ValueAtCrest, Is.EqualTo(accelerationAlphaAForCrest));
            Assert.That(accelerationAlphaA.ValueAtInnerSlope, Is.EqualTo(accelerationAlphaAForInnerSlope));
        }
    }
}