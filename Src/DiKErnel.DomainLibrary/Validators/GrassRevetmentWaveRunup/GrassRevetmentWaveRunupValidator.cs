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

namespace DiKErnel.DomainLibrary.Validators.GrassRevetmentWaveRunup
{
    /// <summary>
    /// Class that holds all grass revetment wave run-up specific validation routines.
    /// </summary>
    public static class GrassRevetmentWaveRunupValidator
    {
        /// <summary>
        /// Validates the 2P Gammab coefficient.
        /// </summary>
        /// <param name="representativeWaveRunup2PGammab">The 2P Gammab coefficient [-].</param>
        /// <returns>A validation issue when the 2P Gammab coefficient is not valid; <c>null</c> otherwise.</returns>
        public static ValidationIssue RepresentativeWaveRunup2PGammab(double representativeWaveRunup2PGammab)
        {
            if (representativeWaveRunup2PGammab < 0.6 || representativeWaveRunup2PGammab > 1.0)
            {
                return new ValidationIssue(ValidationIssueType.Error, "RepresentativeWaveRunup2PGammab must be in range [0.6, 1].");
            }

            return null;
        }

        /// <summary>
        /// Validates the 2P Gammaf coefficient.
        /// </summary>
        /// <param name="representativeWaveRunup2PGammaf">The 2P Gammaf coefficient [-].</param>
        /// <returns>A validation issue when the 2P Gammaf coefficient is not valid; <c>null</c> otherwise.</returns>
        public static ValidationIssue RepresentativeWaveRunup2PGammaf(double representativeWaveRunup2PGammaf)
        {
            if (representativeWaveRunup2PGammaf < 0.5 || representativeWaveRunup2PGammaf > 1.0)
            {
                return new ValidationIssue(ValidationIssueType.Error, "RepresentativeWaveRunup2PGammaf must be in range [0.5, 1].");
            }

            return null;
        }

        /// <summary>
        /// Validates the outer slope.
        /// </summary>
        /// <param name="outerSlope">The outer slope [-].</param>
        /// <returns>A validation issue when the outer slope is not valid; <c>null</c> otherwise.</returns>
        public static ValidationIssue OuterSlope(double outerSlope)
        {
            if (outerSlope <= 0.0 || outerSlope >= 1.0)
            {
                return new ValidationIssue(ValidationIssueType.Error, "OuterSlope must be in range {0, 1}.");
            }

            return null;
        }
    }
}