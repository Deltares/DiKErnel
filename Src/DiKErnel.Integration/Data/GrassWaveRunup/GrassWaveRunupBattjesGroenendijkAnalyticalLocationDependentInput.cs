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

using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.DomainLibrary.Constants;
using DiKErnel.DomainLibrary.Validators.GrassWaveRunup;
using DiKErnel.FunctionLibrary.GrassWaveRunup;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.GrassWaveRunup
{
    internal class GrassWaveRunupBattjesGroenendijkAnalyticalLocationDependentInput
        : GrassWaveRunupLocationDependentInput
    {
        private double upperLimitWaveRunup;

        public GrassWaveRunupBattjesGroenendijkAnalyticalLocationDependentInput(double x, double initialDamage,
                                                                                double failureNumber,
                                                                                double criticalCumulativeOverload,
                                                                                double criticalFrontVelocity,
                                                                                double increasedLoadTransitionAlphaM,
                                                                                double reducedStrengthTransitionAlphaS,
                                                                                double averageNumberOfWavesCtm,
                                                                                double frontVelocityCu)
            : base(x, initialDamage, failureNumber, criticalCumulativeOverload, criticalFrontVelocity,
                   increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, averageNumberOfWavesCtm,
                   frontVelocityCu) {}

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            bool baseValidationSuccessful = base.Validate(timeDependentInputItems, profileData);

            var validationIssues = new List<ValidationIssue>
            {
                GrassWaveRunupBattjesGroenendijkAnalyticalValidator.ForeshoreSlope(profileData.Foreshore.Slope)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        public override void Initialize(IProfileData profileData)
        {
            if (IsInitialized)
            {
                return;
            }

            base.Initialize(profileData);

            upperLimitWaveRunup = GrassWaveRunupBattjesGroenendijkAnalyticalFunctions.UpperLimitWaveRunup(
                IncreasedLoadTransitionAlphaM, ReducedStrengthTransitionAlphaS, FrontVelocityCu, CriticalFrontVelocity,
                NaturalConstants.GravitationalAcceleration);
        }

        protected override double CalculateCumulativeOverload(double averageNumberOfWaves,
                                                              double representativeWaveRunup2P,
                                                              double verticalDistanceWaterLevelElevation,
                                                              ITimeDependentInput timeDependentInput,
                                                              IProfileData profileData)
        {
            Foreshore foreshore = profileData.Foreshore;

            return GrassWaveRunupBattjesGroenendijkAnalyticalFunctions.CumulativeOverload(
                new GrassWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput(
                    averageNumberOfWaves, representativeWaveRunup2P, verticalDistanceWaterLevelElevation,
                    CriticalFrontVelocity, IncreasedLoadTransitionAlphaM, ReducedStrengthTransitionAlphaS,
                    NaturalConstants.GravitationalAcceleration, FrontVelocityCu, timeDependentInput.WaterLevel,
                    timeDependentInput.WaveHeightHm0, foreshore.BottomZ, foreshore.Slope,
                    GrassWaveRunupBattjesGroenendijkAnalyticalConstants.K1,
                    GrassWaveRunupBattjesGroenendijkAnalyticalConstants.K2),
                upperLimitWaveRunup);
        }
    }
}