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

using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.Util;

namespace DiKErnel.KernelWrapper.Json.Input
{
    /// <summary>
    /// Container for a calculation input data result and the associated meta-data.
    /// </summary>
    public class ComposedInputData
    {
        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="calculationInputDataResult">The calculation input data result.</param>
        /// <param name="locationIds">The ids of the locations in the calculation input data result.</param>
        internal ComposedInputData(DataResult<ICalculationInput> calculationInputDataResult, IReadOnlyList<int?> locationIds)
        {
            CalculationInputDataResult = calculationInputDataResult;
            LocationIds = locationIds;
        }

        /// <summary>
        /// Gets the calculation input data result.
        /// </summary>
        public DataResult<ICalculationInput> CalculationInputDataResult { get; }

        /// <summary>
        /// Gets the ids of the locations in the calculation input data result.
        /// </summary>
        public IReadOnlyList<int?> LocationIds { get; }
    }
}