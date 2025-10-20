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

namespace DiKErnel.DomainLibrary.Validators.GrassWaveRunup
{
    /// <summary>
    /// Class that holds grass wave run-up Battjes-Groenendijk analytical validation
    /// routines.
    /// </summary>
    public static class GrassWaveRunupBattjesGroenendijkAnalyticalValidator
    {
        /// <summary>
        /// Validates the foreshore slope.
        /// </summary>
        /// <param name="foreshoreSlope">The slope of the foreshore [-].</param>
        /// <returns>A validation issue when the slope of the foreshore is not valid;
        /// <c>null</c> otherwise.</returns>
        public static ValidationIssue ForeshoreSlope(double foreshoreSlope)
        {
            if (foreshoreSlope < 0.004 || foreshoreSlope > 0.05)
            {
                return new ValidationIssue(ValidationIssueType.Error, "ForeshoreSlope must be in range [0.004, 0.05].");
            }

            return null;
        }
    }
}