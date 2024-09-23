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

namespace DiKErnel.Integration.Data
{
    internal abstract class LocationDependentInput : ILocationDependentInput
    {
        private bool derivedLocationDependentInputInitialized;

        protected LocationDependentInput(double x, double initialDamage, double failureNumber)
        {
            X = x;
            InitialDamage = initialDamage;
            FailureNumber = failureNumber;
        }

        public double X { get; }

        public double Z { get; private set; } = double.NaN;

        public double InitialDamage { get; }

        public double FailureNumber { get; }

        public virtual bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                     IProfileData profileData)
        {
            var validationIssues = new List<ValidationIssue>
            {
                RevetmentValidator.InitialDamage(InitialDamage),
                RevetmentValidator.FailureNumber(FailureNumber, InitialDamage)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues);
        }

        public TimeDependentOutput Calculate(double initialDamage, ITimeDependentInput timeDependentInput,
                                             IProfileData profileData)
        {
            if (!derivedLocationDependentInputInitialized)
            {
                derivedLocationDependentInputInitialized = true;

                InitializeDerivedLocationDependentInput(profileData);
            }

            return CalculateTimeDependentOutput(timeDependentInput, profileData);
        }

        public abstract LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems);

        protected virtual void InitializeDerivedLocationDependentInput(IProfileData profileData)
        {
            Z = profileData.GetVerticalHeight(X);
        }

        protected abstract TimeDependentOutput CalculateTimeDependentOutput(ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData);
    }
}