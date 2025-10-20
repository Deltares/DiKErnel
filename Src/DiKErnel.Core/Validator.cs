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

using System;
using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.Util;

namespace DiKErnel.Core
{
    /// <summary>
    /// Class responsible for performing validation.
    /// </summary>
    public static class Validator
    {
        /// <summary>
        /// Performs the validation.
        /// </summary>
        /// <param name="calculationInput">The input to validate.</param>
        /// <returns>The result of the validation.</returns>
        public static DataResult<ValidationResultType> Validate(ICalculationInput calculationInput)
        {
            try
            {
                var validationResult = ValidationResultType.Successful;

                IReadOnlyList<ITimeDependentInput> timeDependentInputItems = calculationInput.TimeDependentInputItems;

                foreach (ITimeDependentInput timeDependentInput in timeDependentInputItems)
                {
                    if (!timeDependentInput.Validate())
                    {
                        validationResult = ValidationResultType.Failed;
                    }
                }

                IProfileData profileData = calculationInput.ProfileData;

                if (!profileData.Validate())
                {
                    validationResult = ValidationResultType.Failed;
                }

                foreach (ILocationDependentInput locationDependentInput in calculationInput.LocationDependentInputItems)
                {
                    if (!locationDependentInput.Validate(timeDependentInputItems, profileData))
                    {
                        validationResult = ValidationResultType.Failed;
                    }
                }

                return new DataResult<ValidationResultType>(validationResult, EventRegistry.Flush());
            }
            catch (Exception e)
            {
                EventRegistry.Register(new Event("An unhandled error occurred while validating the calculation input. See " +
                                                 $"stack trace for more information:{Environment.NewLine}{e.Message}", EventType.Error));

                return new DataResult<ValidationResultType>(EventRegistry.Flush());
            }
        }
    }
}