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

namespace DiKErnel.Core.Data
{
    /// <summary>
    /// Interface defining all time dependent input that is needed to perform a calculation.
    /// </summary>
    public interface ITimeDependentInput
    {
        /// <summary>
        /// Gets the begin time.
        /// </summary>
        public double BeginTime { get; }

        /// <summary>
        /// Gets the end time.
        /// </summary>
        public double EndTime { get; }

        /// <summary>
        /// Gets the water level.
        /// </summary>
        public double WaterLevel { get; }

        /// <summary>
        /// Gets the wave height.
        /// </summary>
        public double WaveHeightHm0 { get; }

        /// <summary>
        /// Gets the wave period.
        /// </summary>
        public double WavePeriodTm10 { get; }

        /// <summary>
        /// Gets the wave direction.
        /// </summary>
        public double WaveDirection { get; }

        /// <summary>
        /// Performs validation on the input.
        /// </summary>
        /// <returns>Whether the validation was successful.</returns>
        public bool Validate();
    }
}