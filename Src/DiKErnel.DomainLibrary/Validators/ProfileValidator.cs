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

using DiKErnel.Util.Validation;

namespace DiKErnel.DomainLibrary.Validators
{
    /// <summary>
    /// Class that holds all profile related validation routines.
    /// </summary>
    public static class ProfileValidator
    {
        /// <summary>
        /// Validates the roughness coefficient.
        /// </summary>
        /// <param name="roughnessCoefficient">The roughness coefficient [-].</param>
        /// <returns>A validation issue when the roughness coefficient is not valid;
        /// <c>null</c> otherwise.</returns>
        public static ValidationIssue RoughnessCoefficient(double roughnessCoefficient)
        {
            if (roughnessCoefficient < 0.5 || roughnessCoefficient > 1.0)
            {
                return new ValidationIssue(ValidationIssueType.Error, "Roughness coefficient must be in range [0.5, 1].");
            }

            return null;
        }
    }
}