// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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

namespace DiKErnel.Core.Data
{
    /// <summary>
    /// The result of a successful calculation.
    /// </summary>
    public class SuccessResult : ICalculationResult
    {
        /// <summary>
        /// Creates a new instance of <see cref="SuccessResult"/>.
        /// </summary>
        /// <param name="calculationOutput">The calculation output.</param>
        public SuccessResult(CalculationOutput calculationOutput)
        {
            CalculationOutput = calculationOutput;
        }

        /// <summary>
        /// Gets the calculation output.
        /// </summary>
        public CalculationOutput CalculationOutput { get; }
    }
}