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

namespace DiKErnel.DomainLibrary.Validators.Grass
{
    /// <summary>
    /// Class that holds grass cumulative overload validation routines.
    /// </summary>
    public static class GrassCumulativeOverloadValidator
    {
        /// <summary>
        /// Validates the critical cumulative overload.
        /// </summary>
        /// <param name="criticalCumulativeOverload">The critical cumulative
        /// overload [m^2/s^2].</param>
        /// <returns>A validation issue when the critical cumulative overload is not valid;
        /// <c>null</c> otherwise.</returns>
        public static ValidationIssue CriticalCumulativeOverload(double criticalCumulativeOverload)
        {
            if (criticalCumulativeOverload <= 0d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "CriticalCumulativeOverload must be larger than 0.");
            }

            return null;
        }

        /// <summary>
        /// Validates the critical front velocity.
        /// </summary>
        /// <param name="criticalFrontVelocity">The critical front velocity [m/s].</param>
        /// <returns>A validation issue when the critical front velocity is not valid;
        /// <c>null</c> otherwise.</returns>
        public static ValidationIssue CriticalFrontVelocity(double criticalFrontVelocity)
        {
            return ValidateEqualToOrLargerThanZero(criticalFrontVelocity, "CriticalFrontVelocity");
        }

        /// <summary>
        /// Validates the alpha M coefficient.
        /// </summary>
        /// <param name="increasedLoadTransitionAlphaM">The alpha M coefficient [-].</param>
        /// <returns>A validation issue when the alpha M coefficient is not valid;
        /// <c>null</c> otherwise.</returns>
        public static ValidationIssue IncreasedLoadTransitionAlphaM(double increasedLoadTransitionAlphaM)
        {
            return ValidateEqualToOrLargerThanZero(increasedLoadTransitionAlphaM, "IncreasedLoadTransitionAlphaM");
        }

        /// <summary>
        /// Validates the alpha S coefficient.
        /// </summary>
        /// <param name="reducedStrengthTransitionAlphaS">The alpha S
        /// coefficient [-].</param>
        /// <returns>A validation issue when the alpha S coefficient is not valid;
        /// <c>null</c> otherwise.</returns>
        public static ValidationIssue ReducedStrengthTransitionAlphaS(double reducedStrengthTransitionAlphaS)
        {
            return ValidateEqualToOrLargerThanZero(reducedStrengthTransitionAlphaS, "ReducedStrengthTransitionAlphaS");
        }

        private static ValidationIssue ValidateEqualToOrLargerThanZero(double propertyToValidate, string propertyName)
        {
            if (propertyToValidate < 0d)
            {
                return new ValidationIssue(ValidationIssueType.Error, propertyName + " must be equal to 0 or larger.");
            }

            return null;
        }
    }
}