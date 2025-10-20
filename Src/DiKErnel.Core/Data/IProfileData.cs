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

namespace DiKErnel.Core.Data
{
    /// <summary>
    /// Interface defining all profile data that is needed to perform a calculation.
    /// </summary>
    public interface IProfileData
    {
        /// <summary>
        /// Gets the dike orientation to use in the calculation.
        /// </summary>
        double DikeOrientation { get; }

        /// <summary>
        /// Gets the profile segments to use in the calculation.
        /// </summary>
        IReadOnlyList<ProfileSegment> ProfileSegments { get; }

        /// <summary>
        /// Gets the characteristic points to use in the calculation.
        /// </summary>
        IReadOnlyList<CharacteristicPoint> CharacteristicPoints { get; }

        /// <summary>
        /// Gets the foreshore to use in the calculation.
        /// </summary>
        public Foreshore Foreshore { get; }

        /// <summary>
        /// Performs validation on the data.
        /// </summary>
        /// <returns>Whether the validation was successful.</returns>
        public bool Validate();

        /// <summary>
        /// Gets the vertical height based on linear interpolation.
        /// </summary>
        /// <param name="horizontalPosition">The horizontal position.</param>
        /// <returns>The vertical height or <see cref="double.NaN"/> when the
        /// horizontal position cannot be fitted with the dike profile.</returns>
        public double GetVerticalHeight(double horizontalPosition);

        /// <summary>
        /// Gets the horizontal position based on linear interpolation.
        /// </summary>
        /// <param name="verticalHeight">The vertical height.</param>
        /// <returns>The horizontal position or <see cref="double.NaN"/> when
        /// the vertical height cannot be fitted with the dike profile.</returns>
        public double GetHorizontalPosition(double verticalHeight);

        /// <summary>
        /// Gets the profile segment where the horizontal position is located on.
        /// </summary>
        /// <param name="horizontalPosition">The horizontal position.</param>
        /// <returns>The profile segment or <c>null</c> when the horizontal position cannot
        /// be fitted on a profile segment.</returns>
        public ProfileSegment GetProfileSegment(double horizontalPosition);
    }
}