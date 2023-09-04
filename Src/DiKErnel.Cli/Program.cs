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
        private static string logOutputFilePath;

        public static int Main(string[] args)
        {
            try
            {
                var parser = new CommandLineArgumentParser(args);

                if (!parser.ArgumentsAreValid)
                {
                    Console.Out.WriteLine(CommandLineArgumentParser.HelpMessage);
                    return (int) ExitCodes.ArgumentsInvalid;
                }

                string jsonInputFilePath = CommandLineArgumentParser.JsonInputFilePath;
                string jsonOutputFilePath = CommandLineArgumentParser.JsonOutputFilePath;
                logOutputFilePath = parser.LogOutputFilePath;

                RemoveFileWhenExists(jsonOutputFilePath);
                RemoveFileWhenExists(logOutputFilePath);

                DataResult<ICalculationInput> calculationInputDataResult = ValidateAndReadInput(jsonInputFilePath, parser);

                if (calculationInputDataResult == null)
                {
                    return (int) ExitCodes.CalculationInputDataResultInvalid;
                }

                ICalculationInput calculationInput = calculationInputDataResult.Data;

                if (!ValidateCalculationInput(calculationInput))
                {
                    return (int) ExitCodes.CalculationInputInvalid;
                }

                var stopwatch = new Stopwatch();
                stopwatch.Start();

                DataResult<CalculationOutput> calculatorResult = Calculate(calculationInput);

                if (calculatorResult == null)
                {
                    return (int) ExitCodes.CalculatorResultInvalid;
                }

                stopwatch.Stop();

                bool writeOutputResult = WriteOutput(calculatorResult.Data, parser, stopwatch);

                return !writeOutputResult ? (int) ExitCodes.WriteOutputResultInvalid : (int) ExitCodes.Success;
            }
            catch (Exception e)
            {
                EventRegistry.Register(new Event(e.Message, EventType.Error));

                CloseApplicationAfterUnhandledError();
                return (int) ExitCodes.UnhandledError;
            }
        }

        private static void RemoveFileWhenExists(string filePath)
        {
            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }
        }

        static DataResult<ICalculationInput> ValidateAndReadInput(string jsonInputFilePath, CommandLineArgumentParser parser)
        {
            if (CommandLineArgumentParser.ValidateJsonFormat)
            {
                bool validationResult = JsonInputComposer.ValidateJson(jsonInputFilePath);

                IReadOnlyList<Event> validationEvents = EventRegistry.Flush();

                WriteToLogFile(validationEvents);

                if (!validationResult)
                {
                    return null;
                }
            }

            DataResult<ICalculationInput> inputComposerResult = JsonInputComposer.GetInputDataFromJson(jsonInputFilePath);

            WriteToLogFile(inputComposerResult.Events);

            return !inputComposerResult.Successful ? null : inputComposerResult;
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

            return calculator.CalculationState == CalculationState.FinishedInError ? null : calculatorResult;
        }

        static bool WriteOutput(CalculationOutput calculationOutput, CommandLineArgumentParser parser, Stopwatch stopwatch)
        {
            var metaDataItems = new Dictionary<string, object>();

            if (CommandLineArgumentParser.WriteMetaData)
            {
                metaDataItems["versie"] = ApplicationHelper.ApplicationVersionString;
                metaDataItems["besturingssysteem"] = ApplicationHelper.OperatingSystemName;
                metaDataItems["tijdstipBerekening"] = ApplicationHelper.FormattedDateTimeString;
                metaDataItems["tijdsduurBerekening"] = stopwatch.ElapsedMilliseconds;
            }
            
            throw new NotImplementedException("implement this when the outputcomposer is done");
            //this part is dependent on the outputcomposer, which is dependent on the integration project
            //
            // var outputComposerResult = JsonOutputComposer.WriteCalculationOutputToJson(
            //     parser.JsonOutputFilePath,
            //     calculationOutput,
            //     ConvertOutputType(parser.OutputLevel),
            //     metaDataItems);
            //
            // WriteToLogFile(outputComposerResult.Events);
            //
            // return outputComposerResult.Succesful;
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

            using (var writer = new StreamWriter(logOutputFilePath, append: true))
            {
                foreach (Event inEvent in events)
                {
                    writer.Write($"{GetEventTypeString(inEvent.Type)}: {inEvent.Message}\n");
                }
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