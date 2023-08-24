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

using DiKErnel.Integration.Data.GrassRevetmentOvertopping;

namespace DiKErnel.Integration.TestUtil
{
    internal static class GrassRevetmentOvertoppingLocationDependentInputAssertHelper
    {
        public static void AssertGeneralProperties(double x, double? dikeHeight,
                                                   GrassRevetmentOvertoppingLocationDependentInput locationDependentInput) {}

        public static void AssertCumulativeOverload(double criticalCumulativeOverload, int fixedNumberOfWaves,
                                                    GrassRevetmentOvertoppingLocationDependentInput locationDependentInput) {}

        public static void AssertFrontVelocity(double criticalFrontVelocity, double frontVelocityCwo,
                                               GrassRevetmentOvertoppingLocationDependentInput locationDependentInput) {}

        public static void AssertTransitionAlpha(double increasedLoadTransitionAlphaM,
                                                 double reducedStrengthTransitionAlphaS,
                                                 GrassRevetmentOvertoppingLocationDependentInput locationDependentInput) {}

        public static void AssertAverageNumberOfWaves(double averageNumberOfWavesCtm,
                                                      GrassRevetmentOvertoppingLocationDependentInput locationDependentInput) {}

        public static void AssertAccelerationAlphaA(double accelerationAlphaAForCrest,
                                                    double accelerationAlphaAForInnerSlope,
                                                    GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA
                                                        locationDependentAccelerationAlphaA) {}
    }
}