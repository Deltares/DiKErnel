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

using System;
using System.Collections.Generic;
using System.IO;
using DiKErnel.Core.Data;
using DiKErnel.KernelWrapper.Json.Output.Data.Generic;
using DiKErnel.Util;
using Newtonsoft.Json;

namespace DiKErnel.KernelWrapper.Json.Output
{
    /// <summary>
    /// Class responsible for writing Json output.
    /// </summary>
    public static class JsonOutputComposer
    {
        /// <summary>
        /// Writes the output Json based on the given calculation output.
        /// </summary>
        /// <param name="filePath">The path to the Json file.</param>
        /// <param name="calculationOutput">The calculation output to write.</param>
        /// <param name="outputType">The output type.</param>
        /// <param name="metaDataItems">The (optional) meta data items to write.</param>
        /// <returns>The result of the operation.</returns>
        public static SimpleResult WriteCalculationOutputToJson(
            string filePath, CalculationOutput calculationOutput, JsonOutputType outputType,
            IReadOnlyDictionary<string, object> metaDataItems)
        {
            try
            {
                JsonOutputData jsonOutput = CalculationOutputAdapter.AdaptCalculationOutput(
                    calculationOutput, outputType, metaDataItems);

                using (StreamWriter file = File.CreateText(filePath))
                {
                    var serializer = new JsonSerializer();
                    serializer.Serialize(file, jsonOutput);
                }

                return new SimpleResult(true, EventRegistry.Flush());
            }
            catch (Exception e)
            {
                EventRegistry.Register(new Event("An unhandled error occurred while composing Json output from the " +
                                                 $"calculation data. See stack trace for more information:\n{e.Message}",
                                                 EventType.Error));

                return new SimpleResult(false, EventRegistry.Flush());
            }
        }
    }
}