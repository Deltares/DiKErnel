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
using System.Linq;
using System.Reflection;
using DiKErnel.Core.Data;
using DiKErnel.KernelWrapper.Json.Input.Data.Generic.Converters;
using DiKErnel.Util;
using DiKErnel.Util.Validation;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Schema;

namespace DiKErnel.KernelWrapper.Json.Input
{
    /// <summary>
    /// Class responsible for validating and parsing Json input.
    /// </summary>
    public static class JsonInputComposer
    {
        /// <summary>
        /// Performs a Json schema based validation.
        /// </summary>
        /// <param name="filePath">The path to the Json file to validate.</param>
        /// <returns>Whether the validation was successful.</returns>
        public static bool ValidateJson(string filePath)
        {
            var validationIssues = new List<ValidationIssue>();
            if (!File.Exists(filePath))
            {
                validationIssues.Add(new ValidationIssue(ValidationIssueType.Error, "The provided input file does not exist"));
            }

            JObject jObject = JObject.Parse(File.ReadAllText(filePath));
            bool valid = jObject.IsValid(GetValidatorSchema("DiKErnel.KernelWrapper.Json.Input.Resources.schema_definition.json"),
                                         out IList<ValidationError> errors);
            validationIssues.AddRange(errors.Select(validationError =>
                                                        new ValidationIssue(ValidationIssueType.Error, validationError.Message)).ToList());

            // validationhelper is part of integration
            //return ValidationHelper.RegisterValidationIssues(validationIssues);
            return valid;
        }

        /// <summary>
        /// Gets input data based on Json.
        /// </summary>
        /// <param name="filePath">The path to the Json file to get the input from.</param>
        /// <returns>The result of the operation.</returns>
        public static DataResult<ICalculationInput> GetInputDataFromJson(string filePath)
        {
            var jsonSerializer = new JsonSerializer();
            jsonSerializer.Converters.Add(new JsonInputCalculationDataConverter());
            jsonSerializer.Converters.Add(new JsonInputLocationDataConverter());

            try
            {
                JObject jObject = JObject.Parse(File.ReadAllText(filePath));
                
                // json input adapter is dependent on the integration project

                // DataResult<ICalculationInput> calculationInputList =
                //     JsonInputAdapter.AdaptJsonInputData(jObject.ToObject<JsonInputData>(jsonSerializer));
                // 
                // return calculationInputList;
            }
            catch (Exception e)
            {
                EventRegistry.Register(new Event("An unhandled error occurred while composing calculation data" +
                                                 $" from the Json input. See stack trace for more information: {e.Message}",
                                                 EventType.Error));
            }

            return new DataResult<ICalculationInput>(null, EventRegistry.Flush());
        }

        private static JSchema GetValidatorSchema(string resourceName)
        {
            using (Stream validatorSchemaStream = Assembly.GetExecutingAssembly().GetManifestResourceStream(resourceName))
            using (var validatorSchemaReader = new StreamReader(validatorSchemaStream))
            {
                return JSchema.Parse(validatorSchemaReader.ReadToEnd());
            }
        }
    }
}