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
using System.Collections.Generic;

namespace DiKErnel.Core.Data
{
    /// <summary>
    /// Interface defining all location dependent input that is needed to perform a
    /// calculation.
    /// </summary>
    public interface ILocationDependentInput
    {
        /// <summary>
        /// Gets the x coordinate.
        /// </summary>
        public double X { get; }

        /// <summary>
        /// Gets the z coordinate.
        /// </summary>
        public double Z { get; }

        /// <summary>
        /// Gets the initial damage.
        /// </summary>
        public double InitialDamage { get; }

        /// <summary>
        /// Gets the failure number.
        /// </summary>
        public double FailureNumber { get; }

        /// <summary>
        /// Gets whether <see cref="Calculate"/> requires state that is built by previous
        /// calls to <see cref="Calculate"/>.
        /// </summary>
        /// <remarks>When <c>true</c>, calls to <see cref="Calculate"/> should not be run
        /// in parallel in order to prevent race conditions.</remarks>
        public bool CalculateIsStateful { get; }

        /// <summary>
        /// Performs validation on the input.
        /// </summary>
        /// <param name="timeDependentInputItems">One or more time dependent input items to
        /// use in the validation.</param>
        /// <param name="profileData">The profile data to use in the validation.</param>
        /// <returns>Whether the validation was successful.</returns>
        public bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems, IProfileData profileData);

        /// <summary>
        /// Initializes the location dependent input by calculating all output that is not
        /// time-dependent.
        /// </summary>
        /// <param name="profileData">The profile data to use in the calculation.</param>
        /// <remarks>The output at stake is calculated only once and is reused in every
        /// <see cref="Calculate"/> call.</remarks>
        public void Initialize(IProfileData profileData);

        /// <summary>
        /// Performs a location dependent calculation.
        /// </summary>
        /// <param name="timeDependentInput">The time dependent input to use in the
        /// calculation.</param>
        /// <param name="profileData">The profile data to use in the calculation.</param>
        /// <returns>The time dependent output.</returns>
        /// <exception cref="InvalidOperationException">Thrown when <see cref="Initialize"/>
        /// has not been called.</exception>
        public TimeDependentOutput Calculate(ITimeDependentInput timeDependentInput, IProfileData profileData);

        /// <summary>
        /// Gets location dependent output based on the derived location dependent input and
        /// the provided time dependent output items.
        /// </summary>
        /// <param name="timeDependentInputItems">The time dependent input items that were
        /// used for the calculation.</param>
        /// <param name="timeDependentOutputItems">One or more time dependent output items
        /// that were calculated for the location.</param>
        /// <returns>The location dependent output.</returns>
        public LocationDependentOutput GetLocationDependentOutput(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                                                  IReadOnlyList<TimeDependentOutput> timeDependentOutputItems);
    }
}