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

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace DiKErnel.Cli
{
    internal sealed class CommandLineArgumentParser
    {
        private const string inputFilePathKey = "invoerbestand";
        private const string outputFilePathKey = "uitvoerbestand";
        private const string outputLevelKey = "uitvoerniveau";
        private const string noMetaInformationKey = "niet-schrijven-meta-informatie";
        private const string noJsonFormatValidationKey = "niet-valideren-json-formaat";

        private static readonly IReadOnlyDictionary<string, IEnumerable<ArgumentType>> argumentOptions =
            new Dictionary<string, IEnumerable<ArgumentType>>
            {
                {
                    inputFilePathKey, new[]
                    {
                        ArgumentType.Required,
                        ArgumentType.WithValue
                    }
                },
                {
                    outputFilePathKey, new[]
                    {
                        ArgumentType.Required,
                        ArgumentType.WithValue
                    }
                },
                {
                    outputLevelKey, new[]
                    {
                        ArgumentType.Optional,
                        ArgumentType.WithValue
                    }
                },
                {
                    noMetaInformationKey, new[]
                    {
                        ArgumentType.Optional
                    }
                },
                {
                    noJsonFormatValidationKey, new[]
                    {
                        ArgumentType.Optional
                    }
                }
            };

        private readonly Dictionary<string, string> readArguments = new Dictionary<string, string>();

        public CommandLineArgumentParser(IReadOnlyList<string> args)
        {
            if (!ReadArguments(args) || !ValidateReadArguments())
            {
                ArgumentsAreValid = false;
                return;
            }

            LogOutputFilePath = CreateLogOutputFilePath();
        }

        public bool ArgumentsAreValid { get; private set; } = true;

        public string JsonInputFilePath => readArguments[inputFilePathKey];

        public string JsonOutputFilePath => readArguments[outputFilePathKey];

        public string LogOutputFilePath { get; private set; }

        public string OutputLevel => readArguments.TryGetValue(outputLevelKey, out string value) ? value : "schade";

        public bool WriteMetaData => !readArguments.ContainsKey(noMetaInformationKey);

        public bool ValidateJsonFormat => !readArguments.ContainsKey(noJsonFormatValidationKey);

        public static string HelpMessage =>
            Environment.NewLine + "Deze executable kan worden gebruikt voor het uitvoeren van een command-line berekening " +
            "met DiKErnel" +
            Environment.NewLine +
            Environment.NewLine + "Verplichte argumenten:" +
            Environment.NewLine + "----------------------" +
            Environment.NewLine + "--invoerbestand <pad_naar_invoerbestand>" +
            Environment.NewLine + "  = Het pad van het invoerbestand" +
            Environment.NewLine + "--uitvoerbestand <pad_naar_uitvoerbestand>" +
            Environment.NewLine + "  = Het pad van het uitvoerbestand" +
            Environment.NewLine + "    -> Dit bepaalt ook de locatie van het eventuele logbestand" +
            Environment.NewLine +
            Environment.NewLine + "Optionele argumenten:" +
            Environment.NewLine + "---------------------" +
            Environment.NewLine + "--uitvoerniveau <niveau>" +
            Environment.NewLine + "  = Bepaalt de hoeveelheid uitvoer die wordt weggeschreven" +
            Environment.NewLine + "    -> Opties voor <niveau>: falen, schade, fysica" +
            Environment.NewLine + "    -> Standaardwaarde: schade" +
            Environment.NewLine + "--niet-schrijven-meta-informatie" +
            Environment.NewLine + "  = Schakelt het schrijven van meta-informatie uit" +
            Environment.NewLine + "--niet-valideren-json-formaat" +
            Environment.NewLine + "  = Schakelt het valideren van het Json-formaat uit" +
            Environment.NewLine +
            Environment.NewLine + "Voorbeeld:" +
            Environment.NewLine + "----------" +
            Environment.NewLine + "DiKErnel-cli.exe --invoerbestand Berekening1.json --uitvoerbestand UitvoerBerekening1.json " +
            "--uitvoerniveau fysica --niet-schrijven-meta-informatie --niet-valideren-json-formaat" +
            Environment.NewLine +
            Environment.NewLine + "Bij vragen of onduidelijkheden kunt u contact met ons opnemen via dikernel@deltares.nl" +
            Environment.NewLine +
            Environment.NewLine;

        private bool ReadArguments(IReadOnlyList<string> args)
        {
            for (var i = 0; i < args.Count; i++)
            {
                string readKey = args[i];

                if (readKey.StartsWith("--", StringComparison.InvariantCulture))
                {
                    string key = readKey[2..];
                    var value = "";

                    if (argumentOptions.ContainsKey(key))
                    {
                        if (argumentOptions[key].Contains(ArgumentType.WithValue))
                        {
                            if (i + 1 >= args.Count)
                            {
                                return false; // Value missing
                            }

                            value = args[i++];
                        }
                    }
                    else
                    {
                        return false; // Unsupported key
                    }

                    readArguments[key] = value;
                }
                else
                {
                    return false; // Key not starting with "--"
                }
            }

            return true;
        }

        private bool ValidateReadArguments()
        {
            bool requiredArgumentsArePresent =
                argumentOptions.Where(argumentOption => argumentOption.Value.Contains(ArgumentType.Required))
                               .All(requiredArgumentOption => readArguments.ContainsKey(requiredArgumentOption.Key));

            return requiredArgumentsArePresent
                   && FilePathArgumentHasValidExtension(JsonInputFilePath)
                   && FilePathArgumentHasValidExtension(JsonOutputFilePath)
                   && OutputLevelHasValidValue();
        }

        private static bool FilePathArgumentHasValidExtension(string filePathArgument)
        {
            return Path.GetExtension(filePathArgument) == ".json";
        }

        private bool OutputLevelHasValidValue()
        {
            string outputLevel = OutputLevel;

            return outputLevel == "falen" || outputLevel == "schade" || outputLevel == "fysica";
        }

        private string CreateLogOutputFilePath()
        {
            return Path.Join(Path.GetDirectoryName(JsonOutputFilePath),
                             Path.GetFileNameWithoutExtension(JsonOutputFilePath) + ".log");
        }
    }
}