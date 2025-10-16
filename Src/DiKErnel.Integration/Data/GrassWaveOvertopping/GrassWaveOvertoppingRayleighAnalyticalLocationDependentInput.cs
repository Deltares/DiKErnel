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

using System;
using DiKErnel.Core.Data;
using DiKErnel.DomainLibrary.Constants;
using DiKErnel.FunctionLibrary.GrassWaveOvertopping;

namespace DiKErnel.Integration.Data.GrassWaveOvertopping
{
    internal class GrassWaveOvertoppingRayleighAnalyticalLocationDependentInput
        : GrassWaveOvertoppingRayleighLocationDependentInput
    {
        private double cumulativeOverloadPartial1;
        private double cumulativeOverloadPartial2;

        public GrassWaveOvertoppingRayleighAnalyticalLocationDependentInput(
            double x, double initialDamage, double failureNumber, double criticalCumulativeOverload,
            double criticalFrontVelocity, double increasedLoadTransitionAlphaM, double reducedStrengthTransitionAlphaS,
            double averageNumberOfWavesCtm, double frontVelocityCwo,
            GrassWaveOvertoppingRayleighAccelerationAlphaA accelerationAlphaA, double? enforcedDikeHeight)
            : base(x, initialDamage, failureNumber, criticalCumulativeOverload, criticalFrontVelocity,
                   increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, averageNumberOfWavesCtm,
                   frontVelocityCwo, accelerationAlphaA, enforcedDikeHeight) {}

        public override void Initialize(IProfileData profileData)
        {
            if (IsInitialized)
            {
                return;
            }
            
            base.Initialize(profileData);

            cumulativeOverloadPartial1 = IncreasedLoadTransitionAlphaM * Math.Pow(AccelerationAlphaAValue, 2) *
                                         Math.Pow(FrontVelocityCwo, 2) * NaturalConstants.GravitationalAcceleration;

            cumulativeOverloadPartial2 = ReducedStrengthTransitionAlphaS * Math.Pow(CriticalFrontVelocity, 2);
        }

        protected override double CalculateCumulativeOverload(double averageNumberOfWaves,
                                                              double representativeWaveRunup2P,
                                                              double verticalDistanceWaterLevelElevation,
                                                              ITimeDependentInput timeDependentInput,
                                                              IProfileData profileData)
        {
            return GrassWaveOvertoppingRayleighAnalyticalFunctions.CumulativeOverload(
                new GrassWaveOvertoppingRayleighCumulativeOverloadInput(averageNumberOfWaves,
                                                                        representativeWaveRunup2P,
                                                                        verticalDistanceWaterLevelElevation,
                                                                        CriticalFrontVelocity,
                                                                        IncreasedLoadTransitionAlphaM,
                                                                        ReducedStrengthTransitionAlphaS,
                                                                        NaturalConstants.GravitationalAcceleration,
                                                                        FrontVelocityCwo,
                                                                        AccelerationAlphaAValue),
                cumulativeOverloadPartial1, cumulativeOverloadPartial2);
        }
    }
}