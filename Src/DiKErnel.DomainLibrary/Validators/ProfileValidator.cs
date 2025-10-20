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

using DiKErnel.Util.Validation;

namespace DiKErnel.DomainLibrary.Validators
{
    /// <summary>
    /// Class that holds profile validation routines.
    /// </summary>
    public static class ProfileValidator
    {
        /// <summary>
        /// Validates the dike orientation.
        /// </summary>
        /// <param name="dikeOrientation">The dike orientation [deg].</param>
        /// <returns>A validation issue when the dike orientation is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue DikeOrientation(double dikeOrientation)
        {
            if (dikeOrientation < 0d || dikeOrientation > 360d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "Dike orientation must be in range [0, 360].");
            }

            return null;
        }

        /// <summary>
        /// Validates the roughness coefficient.
        /// </summary>
        /// <param name="roughnessCoefficient">The roughness coefficient [-].</param>
        /// <returns>A validation issue when the roughness coefficient is not valid;
        /// <c>null</c> otherwise.</returns>
        public static ValidationIssue RoughnessCoefficient(double roughnessCoefficient)
        {
            if (roughnessCoefficient < 0.5 || roughnessCoefficient > 1d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "Roughness coefficient must be in range [0.5, 1].");
            }

            return null;
        }
    }
}