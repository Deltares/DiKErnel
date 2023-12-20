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
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Protocols
{
    internal abstract class Protocol : IProtocol
    {
        private bool derivedLocationDependentInputInitialized;

        public double Z { get; private set; } = double.NaN;

        public virtual bool Validate(ILocationDependentInput locationDependentInput,
                                     IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                     IProfileData profileData)
        {
            var validationIssues = new List<ValidationIssue>
            {
                RevetmentValidator.InitialDamage(locationDependentInput.InitialDamage),
                RevetmentValidator.FailureNumber(locationDependentInput.FailureNumber,
                                                 locationDependentInput.InitialDamage)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues);
        }

        public TimeDependentOutput Calculate(double initialDamage, ILocationDependentInput locationDependentInput,
                                             ITimeDependentInput timeDependentInput, IProfileData profileData)
        {
            if (!derivedLocationDependentInputInitialized)
            {
                derivedLocationDependentInputInitialized = true;

                InitializeDerivedLocationDependentInput(locationDependentInput, profileData);
            }

            return CalculateTimeDependentOutput(initialDamage, locationDependentInput, timeDependentInput, profileData);
        }

        public abstract LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems);

        protected virtual void InitializeDerivedLocationDependentInput(ILocationDependentInput locationDependentInput,
                                                                       IProfileData profileData)
        {
            Z = profileData.GetVerticalHeight(locationDependentInput.X);
        }

        protected abstract TimeDependentOutput CalculateTimeDependentOutput(double initialDamage,
                                                                            ILocationDependentInput locationDependentInput,
                                                                            ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData);
    }
}