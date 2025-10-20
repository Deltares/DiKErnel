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
    /// Class that holds generic revetment validation routines.
    /// </summary>
    public static class RevetmentValidator
    {
        /// <summary>
        /// Validates the initial damage.
        /// </summary>
        /// <param name="initialDamage">The initial damage [-].</param>
        /// <returns>A validation issue when the initial damage is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue InitialDamage(double initialDamage)
        {
            if (initialDamage < 0d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "InitialDamage must be equal to 0 or larger.");
            }

            if (initialDamage >= 1d)
            {
                return new ValidationIssue(ValidationIssueType.Warning, "InitialDamage should be in range [0, 1}.");
            }

            return null;
        }

        /// <summary>
        /// Validates the failure number.
        /// </summary>
        /// <param name="failureNumber">The failure number [-].</param>
        /// <param name="initialDamage">The initial damage [-].</param>
        /// <returns>A validation issue when the failure number is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue FailureNumber(double failureNumber, double initialDamage)
        {
            if (failureNumber < initialDamage)
            {
                return new ValidationIssue(ValidationIssueType.Error, "FailureNumber must be equal to InitialDamage or larger.");
            }

            return null;
        }

        /// <summary>
        /// Validates the Ctm coefficient.
        /// </summary>
        /// <param name="averageNumberOfWavesCtm">The Ctm coefficient [-].</param>
        /// <returns>A validation issue when the Ctm coefficient is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue AverageNumberOfWavesCtm(double averageNumberOfWavesCtm)
        {
            if (averageNumberOfWavesCtm <= 0d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "AverageNumberOfWavesCtm must be larger than 0.");
            }

            return null;
        }
    }
}