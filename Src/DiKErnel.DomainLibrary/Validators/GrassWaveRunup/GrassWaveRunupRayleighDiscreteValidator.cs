﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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
    /// Class that holds grass wave run-up Rayleigh discrete validation routines.
    /// </summary>
    public static class GrassWaveRunupRayleighDiscreteValidator
    {
        /// <summary>
        /// Validates the Cu coefficient.
        /// </summary>
        /// <param name="frontVelocityCu">The Cu coefficient [-].</param>
        /// <returns>A validation issue when the Cu coefficient is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue FrontVelocityCu(double frontVelocityCu)
        {
            if (frontVelocityCu <= 0d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "FrontVelocityCu must be larger than 0.");
            }

            return null;
        }
    }
}