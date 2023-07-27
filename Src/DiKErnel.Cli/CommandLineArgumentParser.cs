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

namespace DiKErnel.Cli
{
    public class CommandLineArgumentParser
    {
        private static readonly string inputFilePathKey = "invoerbestand";
        private static readonly string outputFilePathKey = "uitvoerbestand";
        private static readonly string outputLevelKey = "uitvoerniveau";
        private static readonly string noMetaInformationKey = "niet-schrijven-meta-informatie";
        private static readonly string noJsonFormatValidationKey = "niet-valideren-json-formaat";

        private static readonly Dictionary<string, string> readArguments = new Dictionary<string, string>();

        private static IReadOnlyDictionary<string, IEnumerable<ArgumentType>> argumentOptions = new Dictionary<string, IEnumerable<ArgumentType>>
        {
            {inputFilePathKey, new []{ArgumentType.Required, ArgumentType.WithValue}},
            {outputFilePathKey, new []{ArgumentType.Required, ArgumentType.WithValue}},
            {outputLevelKey, new []{ArgumentType.Optional, ArgumentType.WithValue}},
            {noMetaInformationKey, new []{ArgumentType.Optional}},
            {noJsonFormatValidationKey, new []{ArgumentType.Optional}}
        };

        public CommandLineArgumentParser(string[] args)
        {
            if (!ReadArguments(args) || !ValidateReadArguments())
            {
                ArgumentsAreValid = false;
                return;
            }

            LogOutputFilePath = CreateLogOutputFilePath();
        }

        public bool ArgumentsAreValid { get; private set; } = true;

        public string LogOutputFilePath { get; private set; }

        public string JsonInputFilePath => readArguments[inputFilePathKey];

        public string JsonOutputFilePath => readArguments[outputFilePathKey];

        public bool WriteMetaData => !readArguments.ContainsKey(noMetaInformationKey);

        public bool ValidateJsonFormat => !readArguments.ContainsKey(noJsonFormatValidationKey);

        public string OutputLevel => readArguments.ContainsKey(outputLevelKey)
                                         ? readArguments[outputLevelKey]
                                         : "schade";

        public static string HelpMessage => "\n"
                                     + "Deze executable kan worden gebruikt voor het uitvoeren van een command-line berekening met DiKErnel\n"
                                     + "\n"
                                     + "Verplichte argumenten:\n"
                                     + "----------------------\n"
                                     + "--invoerbestand <pad_naar_invoerbestand>\n"
                                     + "  = Het pad van het invoerbestand\n"
                                     + "--uitvoerbestand <pad_naar_uitvoerbestand>\n"
                                     + "  = Het pad van het uitvoerbestand\n"
                                     + "    -> Dit bepaalt ook de locatie van het eventuele logbestand\n"
                                     + "\n"
                                     + "Optionele argumenten:\n"
                                     + "---------------------\n"
                                     + "--uitvoerniveau <niveau>\n"
                                     + "  = Maat voor de hoeveelheid uitvoer die wordt weggeschreven\n"
                                     + "    -> Opties voor <niveau>: falen, schade, fysica\n"
                                     + "    -> Standaardwaarde: schade\n"
                                     + "--niet-schrijven-meta-informatie\n"
                                     + "  = Schakelt het schrijven van meta-informatie uit\n"
                                     + "--niet-valideren-json-formaat\n"
                                     + "  = Schakelt het valideren van het Json-formaat uit\n"
                                     + "\n"
                                     + "Voorbeeld:\n"
                                     + "----------\n"
                                     + "DiKErnel-cli.exe --invoerbestand Berekening1.json --uitvoerbestand UitvoerBerekening1.json --uitvoerniveau fysica "
                                     + "--niet-schrijven-meta-informatie --niet-valideren-json-formaat\n"
                                     + "\n"
                                     + "Bij vragen of onduidelijkheden kunt u contact met ons opnemen via dikernel@deltares.nl\n"
                                     + "\n";

        private bool ReadArguments(string[] args)
        {
            for (var i = 0; i < args.Length; i++)
            {
                if (args[i].StartsWith("--", StringComparison.InvariantCulture))
                {
                    string key = args[i][2..];
                    var value = "";
                    if (argumentOptions.ContainsKey(key))
                    {
                        if (argumentOptions[key].Contains(ArgumentType.WithValue))
                        {
                            if (i + 1 >= args.Length)
                            {
                                return false; // Value missing
                            }

                            value = args[++i];
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
            bool requiredArgumentsArePresent = argumentOptions.Where(ao => ao.Value.Contains(ArgumentType.Required))
                                                              .Select(aoWithRequiredType =>
                                                                          readArguments.ContainsKey(aoWithRequiredType.Key))
                                                              .All(aoHasReadArgument => aoHasReadArgument);

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
            string outputFilePath = JsonOutputFilePath;
            string outputDirectory = Path.GetDirectoryName(outputFilePath);
            string outputFileName = Path.GetFileNameWithoutExtension(outputFilePath);

            return $"{Path.Join(outputDirectory, outputFileName)}.log";
        }
    }
}