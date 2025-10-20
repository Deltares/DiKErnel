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

namespace DiKErnel.DomainLibrary.Validators.GrassWaveImpact
{
    /// <summary>
    /// Class that holds grass wave impact validation routines.
    /// </summary>
    public static class GrassWaveImpactValidator
    {
        /// <summary>
        /// Validates the Agwi coefficient.
        /// </summary>
        /// <param name="timeLineAgwi">The Agwi coefficient [m].</param>
        /// <param name="timeLineCgwi">The Cgwi coefficient [m].</param>
        /// <returns>A validation issue when the Agwi coefficient is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue TimeLineAgwi(double timeLineAgwi, double timeLineCgwi)
        {
            if (timeLineAgwi <= timeLineCgwi)
            {
                return new ValidationIssue(ValidationIssueType.Error, "TimeLineAgwi must be larger than TimeLineCgwi.");
            }

            return null;
        }

        /// <summary>
        /// Validates the Bgwi coefficient.
        /// </summary>
        /// <param name="timeLineBgwi">The Bgwi coefficient [s^-1].</param>
        /// <returns>A validation issue when the Bgwi coefficient is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue TimeLineBgwi(double timeLineBgwi)
        {
            if (timeLineBgwi >= 0d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "TimeLineBgwi must be smaller than 0.");
            }

            return null;
        }

        /// <summary>
        /// Validates the Cgwi coefficient.
        /// </summary>
        /// <param name="timeLineCgwi">The Cgwi coefficient [m].</param>
        /// <returns>A validation issue when the Cgwi coefficient is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue TimeLineCgwi(double timeLineCgwi)
        {
            if (timeLineCgwi < 0d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "TimeLineCgwi must be equal to 0 or larger.");
            }

            return null;
        }

        /// <summary>
        /// Validates the Temax coefficient.
        /// </summary>
        /// <param name="minimumWaveHeightTemax">The Temax coefficient [s].</param>
        /// <returns>A validation issue when the Temax coefficient is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue MinimumWaveHeightTemax(double minimumWaveHeightTemax)
        {
            if (minimumWaveHeightTemax > 3600000d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "MinimumWaveHeightTemax must be equal to 3600000 or smaller.");
            }

            if (minimumWaveHeightTemax <= 1000000d)
            {
                return new ValidationIssue(ValidationIssueType.Warning, "MinimumWaveHeightTemax should be in range {1000000, 3600000].");
            }

            return null;
        }

        /// <summary>
        /// Validates the Temin coefficient.
        /// </summary>
        /// <param name="maximumWaveHeightTemin">The Temin coefficient [s].</param>
        /// <returns>A validation issue when the Temin coefficient is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue MaximumWaveHeightTemin(double maximumWaveHeightTemin)
        {
            if (maximumWaveHeightTemin < 3.6)
            {
                return new ValidationIssue(ValidationIssueType.Error, "MaximumWaveHeightTemin must be equal to 3.6 or larger.");
            }

            if (maximumWaveHeightTemin >= 10d)
            {
                return new ValidationIssue(ValidationIssueType.Warning, "MaximumWaveHeightTemin should be in range [3.6, 10}.");
            }

            return null;
        }

        /// <summary>
        /// Validates the Nwa coefficient.
        /// </summary>
        /// <param name="waveAngleImpactNwa">The Nwa coefficient [-].</param>
        /// <returns>A validation issue when the Nwa coefficient is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue WaveAngleImpactNwa(double waveAngleImpactNwa)
        {
            if (waveAngleImpactNwa > 1d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "WaveAngleImpactNwa must be equal to 1 or smaller.");
            }

            return null;
        }

        /// <summary>
        /// Validates the Qwa coefficient.
        /// </summary>
        /// <param name="waveAngleImpactQwa">The Qwa coefficient [-].</param>
        /// <returns>A validation issue when the Qwa coefficient is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue WaveAngleImpactQwa(double waveAngleImpactQwa)
        {
            if (waveAngleImpactQwa < 0d || waveAngleImpactQwa > 1d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "WaveAngleImpactQwa must be in range [0, 1].");
            }

            return null;
        }

        /// <summary>
        /// Validates the Rwa coefficient.
        /// </summary>
        /// <param name="waveAngleImpactRwa">The Rwa coefficient [-].</param>
        /// <returns>A validation issue when the Rwa coefficient is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue WaveAngleImpactRwa(double waveAngleImpactRwa)
        {
            if (waveAngleImpactRwa <= 0d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "WaveAngleImpactRwa must be larger than 0.");
            }

            return null;
        }

        /// <summary>
        /// Validates the Aul coefficient.
        /// </summary>
        /// <param name="upperLimitLoadingAul">The Aul coefficient [-].</param>
        /// <param name="lowerLimitLoadingAll">The All coefficient [-].</param>
        /// <returns>A validation issue when the Aul coefficient is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue UpperLimitLoadingAul(double upperLimitLoadingAul, double lowerLimitLoadingAll)
        {
            if (upperLimitLoadingAul >= lowerLimitLoadingAll)
            {
                return new ValidationIssue(ValidationIssueType.Error, "UpperLimitLoadingAul must be smaller than LowerLimitLoadingAll.");
            }

            return null;
        }
    }
}