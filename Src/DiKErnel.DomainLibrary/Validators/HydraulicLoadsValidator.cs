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
    /// Class that holds hydraulic loads validation routines.
    /// </summary>
    public static class HydraulicLoadsValidator
    {
        /// <summary>
        /// Validates the wave height Hm0.
        /// </summary>
        /// <param name="waveHeightHm0">The wave height Hm0 [m].</param>
        /// <returns>A validation issue when the wave height Hm0 is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue WaveHeightHm0(double waveHeightHm0)
        {
            if (waveHeightHm0 <= 0d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "WaveHeightHm0 must be larger than 0.");
            }

            if (waveHeightHm0 <= 0.1 || waveHeightHm0 >= 10d)
            {
                return new ValidationIssue(ValidationIssueType.Warning, "WaveHeightHm0 should be in range {0.1, 10}.");
            }

            return null;
        }

        /// <summary>
        /// Validates the wave period Tm10.
        /// </summary>
        /// <param name="wavePeriodTm10">The wave period Tm10 [s].</param>
        /// <returns>A validation issue when the wave period Tm10 is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue WavePeriodTm10(double wavePeriodTm10)
        {
            if (wavePeriodTm10 <= 0d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "WavePeriodTm10 must be larger than 0.");
            }

            if (wavePeriodTm10 <= 0.5 || wavePeriodTm10 >= 25d)
            {
                return new ValidationIssue(ValidationIssueType.Warning, "WavePeriodTm10 should be in range {0.5, 25}.");
            }

            return null;
        }

        /// <summary>
        /// Validates the wave direction.
        /// </summary>
        /// <param name="waveDirection">The wave direction [deg].</param>
        /// <returns>A validation issue when the wave direction is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue WaveDirection(double waveDirection)
        {
            if (waveDirection < 0d || waveDirection > 360d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "WaveDirection must be in range [0, 360].");
            }

            return null;
        }
    }
}