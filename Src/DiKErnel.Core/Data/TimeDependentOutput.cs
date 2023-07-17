﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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

namespace DiKErnel.Core.Data
{
    /// <summary>
    /// Class containing time dependent output of a location.
    /// </summary>
    public abstract class TimeDependentOutput
    {
        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="incrementDamage">The increment of damage.</param>
        /// <param name="damage">The damage.</param>
        /// <param name="timeOfFailure">The time of failure.</param>
        protected TimeDependentOutput(double incrementDamage, double damage, int? timeOfFailure = null)
        {
            IncrementDamage = incrementDamage;
            Damage = damage;
            TimeOfFailure = timeOfFailure;
        }

        /// <summary>
        /// Gets the increment of damage.
        /// </summary>
        public double IncrementDamage { get; }

        /// <summary>
        /// Gets the damage.
        /// </summary>
        public double Damage { get; }

        /// <summary>
        /// Gets the time of failure.
        /// </summary>
        public int? TimeOfFailure { get; }
    }
}