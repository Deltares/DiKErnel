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

namespace DiKErnel.Core.Data
{
    /// <summary>
    /// Interface defining all logic that is needed to validate calculation input, perform
    /// calculations and create location dependent output.
    /// </summary>
    public interface IProtocol
    {
        /// <summary>
        /// Performs validation on the input.
        /// </summary>
        /// <param name="timeDependentInputItems">One or more time dependent input items to
        /// use in the validation.</param>
        /// <param name="profileData">The profile data to use in the validation.</param>
        /// <returns>Whether the validation was successful.</returns>
        public bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems, IProfileData profileData);

        /// <summary>
        /// Performs a location dependent calculation.
        /// </summary>
        /// <param name="initialDamage">The damage at the start of the calculation.</param>
        /// <param name="timeDependentInput">The time dependent input to use in the
        /// calculation.</param>
        /// <param name="profileData">The profile data to use in the calculation.</param>
        /// <returns>The time dependent output.</returns>
        public TimeDependentOutput Calculate(double initialDamage, ITimeDependentInput timeDependentInput,
                                             IProfileData profileData);

        /// <summary>
        /// Gets location dependent output based on the derived location dependent input and
        /// the provided time dependent output items.
        /// </summary>
        /// <param name="timeDependentOutputItems">One or more time dependent output items
        /// that were calculated for the location.</param>
        /// <returns>The location dependent output.</returns>
        public LocationDependentOutput GetLocationDependentOutput(IReadOnlyList<TimeDependentOutput> timeDependentOutputItems);
    }
}