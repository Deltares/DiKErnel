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

using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.DomainLibrary.Constants;
using DiKErnel.DomainLibrary.Validators.Grass;
using DiKErnel.FunctionLibrary.GrassWaveOvertopping;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.GrassWaveOvertopping
{
    internal class GrassWaveOvertoppingRayleighDiscreteLocationDependentInput
        : GrassWaveOvertoppingRayleighLocationDependentInput
    {
        public GrassWaveOvertoppingRayleighDiscreteLocationDependentInput(
            double x, double initialDamage, double failureNumber, double criticalCumulativeOverload,
            double criticalFrontVelocity, double increasedLoadTransitionAlphaM, double reducedStrengthTransitionAlphaS,
            double averageNumberOfWavesCtm, double frontVelocityCwo,
            GrassWaveOvertoppingRayleighAccelerationAlphaA accelerationAlphaA, double? enforcedDikeHeight,
            int fixedNumberOfWaves)
            : base(x, initialDamage, failureNumber, criticalCumulativeOverload, criticalFrontVelocity,
                   increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, averageNumberOfWavesCtm,
                   frontVelocityCwo, accelerationAlphaA, enforcedDikeHeight)
        {
            FixedNumberOfWaves = fixedNumberOfWaves;
        }

        public int FixedNumberOfWaves { get; }

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            bool baseValidationSuccessful = base.Validate(timeDependentInputItems, profileData);

            var validationIssues = new List<ValidationIssue>
            {
                GrassRayleighDiscreteValidator.FixedNumberOfWaves(FixedNumberOfWaves)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        protected override double CalculateCumulativeOverload(double averageNumberOfWaves,
                                                              double representativeWaveRunup2P,
                                                              double verticalDistanceWaterLevelElevation,
                                                              ITimeDependentInput timeDependentInput,
                                                              IProfileData profileData)
        {
            return GrassWaveOvertoppingRayleighDiscreteFunctions.CumulativeOverload(
                new GrassWaveOvertoppingRayleighDiscreteCumulativeOverloadInput(averageNumberOfWaves,
                                                                                representativeWaveRunup2P,
                                                                                verticalDistanceWaterLevelElevation,
                                                                                CriticalFrontVelocity,
                                                                                IncreasedLoadTransitionAlphaM,
                                                                                ReducedStrengthTransitionAlphaS,
                                                                                NaturalConstants.GravitationalAcceleration,
                                                                                FrontVelocityCwo,
                                                                                AccelerationAlphaAValue,
                                                                                FixedNumberOfWaves));
        }
    }
}