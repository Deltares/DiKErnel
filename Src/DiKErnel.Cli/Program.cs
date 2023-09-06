// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using DiKErnel.Application;
using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.KernelWrapper.Json.Input;
using DiKErnel.KernelWrapper.Json.Output;
using DiKErnel.Util;

namespace DiKErnel.Cli
{
    public static class DiKernelConsole
    {
        private const string unexpectedErrorMessage = "Er is een onverwachte fout opgetreden. Indien gewenst kunt u " +
                                                      "contact met ons opnemen via dikernel@deltares.nl.";

        private static string logOutputFilePath;

        public static int Main(string[] args)
        {
            try
            {
                var parser = new CommandLineArgumentParser(args);

                if (!parser.ArgumentsAreValid)
                {
                    Console.WriteLine(CommandLineArgumentParser.HelpMessage);
                    return -1;
                }

                string jsonInputFilePath = parser.JsonInputFilePath;
                string jsonOutputFilePath = parser.JsonOutputFilePath;
                logOutputFilePath = parser.LogOutputFilePath;

                RemoveFileWhenExists(jsonOutputFilePath);
                RemoveFileWhenExists(logOutputFilePath);

                DataResult<ICalculationInput> calculationInputDataResult =
                    ValidateAndReadInput(jsonInputFilePath, parser);

                if (calculationInputDataResult == null)
                {
                    return -1;
                }

                ICalculationInput calculationInput = calculationInputDataResult.Data;

                if (!ValidateCalculationInput(calculationInput))
                {
                    return -1;
                }

                var stopwatch = new Stopwatch();

                stopwatch.Start();

                DataResult<CalculationOutput> calculatorResult = Calculate(calculationInput);

                if (calculatorResult == null)
                {
                    return -1;
                }

                stopwatch.Stop();

                bool writeOutputResult = WriteOutput(calculatorResult.Data, parser, stopwatch.ElapsedMilliseconds);

                return !writeOutputResult ? -1 : 0;
            }
            catch
            {
                EventRegistry.Register(new Event(unexpectedErrorMessage, EventType.Error));

                CloseApplicationAfterUnhandledError();

                return -1;
            }
        }

        private static void RemoveFileWhenExists(string filePath)
        {
            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }
        }

        private static DataResult<ICalculationInput> ValidateAndReadInput(
            string jsonInputFilePath, CommandLineArgumentParser parser)
        {
            if (parser.ValidateJsonFormat)
            {
                bool validationResult = JsonInputComposer.ValidateJson(jsonInputFilePath);

                IReadOnlyList<Event> validationEvents = EventRegistry.Flush();

                WriteToLogFile(validationEvents);

                if (!validationResult)
                {
                    return null;
                }
            }

            DataResult<ICalculationInput> inputComposerResult =
                JsonInputComposer.GetInputDataFromJson(jsonInputFilePath);

            WriteToLogFile(inputComposerResult.Events);

            return inputComposerResult.Successful ? inputComposerResult : null;
        }

        private static bool ValidateCalculationInput(ICalculationInput calculationInput)
        {
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput);

            WriteToLogFile(validationResult.Events);

            return validationResult.Successful && validationResult.Data == ValidationResultType.Successful;
        }

        private static DataResult<CalculationOutput> Calculate(ICalculationInput calculationInput)
        {
            var calculator = new Calculator(calculationInput);
            calculator.WaitForCompletion();

            DataResult<CalculationOutput> calculatorResult = calculator.Result;

            WriteToLogFile(calculatorResult.Events);

            return calculator.CalculationState != CalculationState.FinishedInError ? calculatorResult : null;
        }

        private static bool WriteOutput(CalculationOutput calculationOutput, CommandLineArgumentParser parser,
                                        long elapsed)
        {
            Dictionary<string, object> metaDataItems = null;

            if (parser.WriteMetaData)
            {
                metaDataItems = new Dictionary<string, object>
                {
                    ["versie"] = ApplicationHelper.ApplicationVersionString,
                    ["besturingssysteem"] = ApplicationHelper.OperatingSystemName,
                    ["tijdstipBerekening"] = ApplicationHelper.FormattedDateTimeString,
                    ["tijdsduurBerekening"] = elapsed
                };
            }

            SimpleResult outputComposerResult = JsonOutputComposer.WriteCalculationOutputToJson(
                parser.JsonOutputFilePath, calculationOutput, ConvertOutputType(parser.OutputLevel),
                metaDataItems);

            WriteToLogFile(outputComposerResult.Events);

            return outputComposerResult.Successful;
        }

        private static JsonOutputType ConvertOutputType(string outputTypeString)
        {
            return outputTypeString switch
            {
                "falen" => JsonOutputType.Failure,
                "schade" => JsonOutputType.Damage,
                _ => JsonOutputType.Physics
            };
        }

        private static void WriteToLogFile(IReadOnlyList<Event> events)
        {
            if (!events.Any())
            {
                return;
            }

            using var writer = new StreamWriter(logOutputFilePath, true);

            foreach (Event e in events)
            {
                writer.Write($"{GetEventTypeString(e.Type)}: {e.Message}{Environment.NewLine}");
            }
        }

        private static string GetEventTypeString(EventType eventType)
        {
            return eventType switch
            {
                EventType.Warning => "Warning",
                EventType.Error => "Error",
                _ => throw new NotSupportedException("Unsupported EventType")
            };
        }

        private static void CloseApplicationAfterUnhandledError()
        {
            WriteToLogFile(EventRegistry.Flush());
        }
    }
}