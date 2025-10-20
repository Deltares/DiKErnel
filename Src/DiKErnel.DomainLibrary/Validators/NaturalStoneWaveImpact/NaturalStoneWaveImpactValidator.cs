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

namespace DiKErnel.DomainLibrary.Validators.NaturalStoneWaveImpact
{
    /// <summary>
    /// Class that holds natural stone wave impact validation routines.
    /// </summary>
    public static class NaturalStoneWaveImpactValidator
    {
        /// <summary>
        /// Validates the relative density.
        /// </summary>
        /// <param name="relativeDensity">The relative density [-].</param>
        /// <returns>A validation issue when the relative density is not valid;
        /// <c>null</c> otherwise.</returns>
        public static ValidationIssue RelativeDensity(double relativeDensity)
        {
            if (relativeDensity <= 0d || relativeDensity >= 10d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "RelativeDensity must be in range {0, 10}.");
            }

            if (relativeDensity < 0.1 || relativeDensity > 5d)
            {
                return new ValidationIssue(ValidationIssueType.Warning, "RelativeDensity should be in range [0.1, 5].");
            }

            return null;
        }

        /// <summary>
        /// Validates the thickness of the top layer.
        /// </summary>
        /// <param name="thicknessTopLayer">The thickness of the top layer [m].</param>
        /// <returns>A validation issue when the thickness of the top layer is not valid;
        /// <c>null</c> otherwise.</returns>
        public static ValidationIssue ThicknessTopLayer(double thicknessTopLayer)
        {
            if (thicknessTopLayer <= 0d || thicknessTopLayer >= 1d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "ThicknessTopLayer must be in range {0, 1}.");
            }

            if (thicknessTopLayer < 0.04 || thicknessTopLayer > 0.6)
            {
                return new ValidationIssue(ValidationIssueType.Warning, "ThicknessTopLayer should be in range [0.04, 0.6].");
            }

            return null;
        }

        /// <summary>
        /// Validates the Aus coefficient.
        /// </summary>
        /// <param name="slopeUpperLevelAus">The Aus coefficient [-].</param>
        /// <returns>A validation issue when the Aus coefficient is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue SlopeUpperLevelAus(double slopeUpperLevelAus)
        {
            if (slopeUpperLevelAus <= 0d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "SlopeUpperLevelAus must be larger than 0.");
            }

            if (slopeUpperLevelAus < 0.01 || slopeUpperLevelAus > 0.2)
            {
                return new ValidationIssue(ValidationIssueType.Warning, "SlopeUpperLevelAus should be in range [0.01, 0.2].");
            }

            return null;
        }

        /// <summary>
        /// Validates the Als coefficient.
        /// </summary>
        /// <param name="slopeLowerLevelAls">The Als coefficient [-].</param>
        /// <returns>A validation issue when the Als coefficient is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue SlopeLowerLevelAls(double slopeLowerLevelAls)
        {
            if (slopeLowerLevelAls <= 0d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "SlopeLowerLevelAls must be larger than 0.");
            }

            if (slopeLowerLevelAls < 1d || slopeLowerLevelAls > 2d)
            {
                return new ValidationIssue(ValidationIssueType.Warning, "SlopeLowerLevelAls should be in range [1, 2].");
            }

            return null;
        }
    }
}