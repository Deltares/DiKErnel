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
using DiKErnel.DomainLibrary.Validators.GrassWaveRunup;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.GrassWaveRunup
{
    internal abstract class GrassWaveRunupLocationDependentInput : GrassCumulativeOverloadLocationDependentInput
    {
        protected GrassWaveRunupLocationDependentInput(double x, double initialDamage, double failureNumber,
                                                       double criticalCumulativeOverload, double criticalFrontVelocity,
                                                       double increasedLoadTransitionAlphaM,
                                                       double reducedStrengthTransitionAlphaS,
                                                       double averageNumberOfWavesCtm, double frontVelocityCu)
            : base(x, initialDamage, failureNumber, criticalCumulativeOverload, criticalFrontVelocity,
                   increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, averageNumberOfWavesCtm)
        {
            FrontVelocityCu = frontVelocityCu;
        }

        public double FrontVelocityCu { get; }

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            bool baseValidationSuccessful = base.Validate(timeDependentInputItems, profileData);

            var validationIssues = new List<ValidationIssue>
            {
                GrassWaveRunupValidator.FrontVelocityCu(FrontVelocityCu)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        protected override double CalculateDikeHeight(IProfileData profileData)
        {
            (double, double) outerCrest = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.OuterCrest);

            return outerCrest.Item2;
        }

        protected override double GetRunupHeight()
        {
            return Z;
        }

        protected override bool HasLoading(double verticalDistanceWaterLevelElevation)
        {
            return verticalDistanceWaterLevelElevation > 0d;
        }
    }
}