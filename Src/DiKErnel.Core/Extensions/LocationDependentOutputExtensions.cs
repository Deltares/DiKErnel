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

using System;
using System.Collections.Generic;
using System.Linq;
using DiKErnel.Core.Data;

namespace DiKErnel.Core.Extensions
{
    /// <summary>
    /// Extension methods for <see cref="LocationDependentOutput"/>.
    /// </summary>
    public static class LocationDependentOutputExtensions
    {
        /// <summary>
        /// Gets the calculated damages.
        /// </summary>
        /// <param name="locationDependentOutput">The location dependent output.</param>
        /// <returns>The calculated damages for the location dependent output.</returns>
        /// <exception cref="ArgumentNullException">Thrown when
        /// <paramref name="locationDependentOutput"/> is <c>null</c>.</exception>
        public static IEnumerable<double> GetDamages(this LocationDependentOutput locationDependentOutput)
        {
            if (locationDependentOutput == null)
            {
                throw new ArgumentNullException(nameof(locationDependentOutput));
            }
            
            return locationDependentOutput.TimeDependentOutputItems.Select(timeDependentOutput => timeDependentOutput.Damage);
        }

        /// <summary>
        /// Gets the calculated time of failure.
        /// </summary>
        /// <param name="locationDependentOutput">The location dependent output.</param>
        /// <returns>The calculated time of failure for the location dependent output.</returns>
        /// <exception cref="ArgumentNullException">Thrown when
        /// <paramref name="locationDependentOutput"/> is <c>null</c>.</exception>
        public static int? GetTimeOfFailure(this LocationDependentOutput locationDependentOutput)
        {
            if (locationDependentOutput == null)
            {
                throw new ArgumentNullException(nameof(locationDependentOutput));
            }

            foreach (TimeDependentOutput timeDependentOutput in locationDependentOutput.TimeDependentOutputItems)
            {
                if (timeDependentOutput.TimeOfFailure.HasValue)
                {
                    return timeDependentOutput.TimeOfFailure;
                }
            }

            return null;
        }
    }
}