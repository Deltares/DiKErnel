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

using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.DomainLibrary.Validators;
using DiKErnel.DomainLibrary.Validators.GrassRevetment;
using DiKErnel.DomainLibrary.Validators.GrassRevetmentWaveRunup;
using DiKErnel.Integration.Data.GrassRevetmentWaveRunup;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Protocols.GrassWaveRunup
{
    internal abstract class GrassWaveRunupProtocol : Protocol
    {
        protected GrassWaveRunupProtocol(double outerSlope, double criticalCumulativeOverload,
                                         double criticalFrontVelocity, double increasedLoadTransitionAlphaM,
                                         double reducedStrengthTransitionAlphaS, double averageNumberOfWavesCtm,
                                         GrassRevetmentWaveRunupRepresentative2P representative2P,
                                         GrassRevetmentWaveRunupWaveAngleImpact waveAngleImpact)
        {
            OuterSlope = outerSlope;
            CriticalCumulativeOverload = criticalCumulativeOverload;
            CriticalFrontVelocity = criticalFrontVelocity;
            IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM;
            ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS;
            AverageNumberOfWavesCtm = averageNumberOfWavesCtm;
            Representative2P = representative2P;
            WaveAngleImpact = waveAngleImpact;
        }

        public double OuterSlope { get; }

        public double CriticalCumulativeOverload { get; }

        public double CriticalFrontVelocity { get; }

        public double IncreasedLoadTransitionAlphaM { get; }

        public double ReducedStrengthTransitionAlphaS { get; }

        public double AverageNumberOfWavesCtm { get; }

        public GrassRevetmentWaveRunupRepresentative2P Representative2P { get; }

        public GrassRevetmentWaveRunupWaveAngleImpact WaveAngleImpact { get; }

        public override bool Validate(ILocationDependentInput locationDependentInput,
                                      IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            bool baseValidationSuccessful = base.Validate(locationDependentInput, timeDependentInputItems, profileData);

            var validationIssues = new List<ValidationIssue>
            {
                GrassRevetmentValidator.CriticalCumulativeOverload(CriticalCumulativeOverload),
                GrassRevetmentWaveRunupValidator.RepresentativeWaveRunup2PGammab(Representative2P.Gammab),
                GrassRevetmentWaveRunupValidator.RepresentativeWaveRunup2PGammaf(Representative2P.Gammaf),
                GrassRevetmentValidator.CriticalFrontVelocity(CriticalFrontVelocity),
                GrassRevetmentValidator.IncreasedLoadTransitionAlphaM(IncreasedLoadTransitionAlphaM),
                GrassRevetmentValidator.ReducedStrengthTransitionAlphaS(ReducedStrengthTransitionAlphaS),
                GrassRevetmentWaveRunupValidator.OuterSlope(OuterSlope),
                RevetmentValidator.AverageNumberOfWavesCtm(AverageNumberOfWavesCtm)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }
    }
}