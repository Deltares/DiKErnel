// Copyright (C) Stichting Deltares 2022. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#include "CommandLineArgumentParser.h"

#include <algorithm>
#include <filesystem>
#include <sstream>

namespace DiKErnel::Cli
{
    using namespace std;
    using namespace std::filesystem;

    CommandLineArgumentParser::CommandLineArgumentParser(
        const int argc,
        char** argv)
    {
        if (!ReadArguments(argc, argv) || !ValidateReadArguments())
        {
            _argumentsAreValid = false;
            return;
        }

        _logOutputFilePath = CreateLogOutputFilePath();
    }

    bool CommandLineArgumentParser::ArgumentsAreValid() const
    {
        return _argumentsAreValid;
    }

    string CommandLineArgumentParser::GetJsonInputFilePath() const
    {
        return _readArguments.at(_inputFilePathKey);
    }

    string CommandLineArgumentParser::GetJsonOutputFilePath() const
    {
        return _readArguments.at(_outputFilePathKey);
    }

    string CommandLineArgumentParser::GetLogOutputFilePath() const
    {
        return _logOutputFilePath;
    }

    string CommandLineArgumentParser::GetOutputLevel() const
    {
        return _readArguments.contains(_outputLevelKey)
                   ? _readArguments.at(_outputLevelKey)
                   : "schade";
    }

    bool CommandLineArgumentParser::GetWriteMetaData() const
    {
        return !_readArguments.contains(_noMetaInformationKey);
    }

    bool CommandLineArgumentParser::GetValidateJsonFormat() const
    {
        return !_readArguments.contains(_noJsonFormatValidationKey);
    }

    string CommandLineArgumentParser::GetHelpMessage()
    {
        stringstream message;

        message << endl;
        message << "Deze executable kan worden gebruikt voor het uitvoeren van een command-line berekening met DiKErnel" << endl;
        message << endl;
        message << "Verplichte argumenten:" << endl;
        message << "----------------------" << endl;
        message << "--invoerbestand <pad_naar_invoerbestand>" << endl;
        message << "  = Het pad van het invoerbestand" << endl;
        message << "--uitvoerbestand <pad_naar_uitvoerbestand>" << endl;
        message << "  = Het pad van het uitvoerbestand" << endl;
        message << "    -> Dit bepaalt ook de locatie van het eventuele logbestand" << endl;
        message << endl;
        message << "Optionele argumenten:" << endl;
        message << "---------------------" << endl;
        message << "--uitvoerniveau <niveau>" << endl;
        message << "  = Maat voor de hoeveelheid uitvoer die wordt weggeschreven" << endl;
        message << "    -> Opties voor <niveau>: falen, schade, fysica" << endl;
        message << "    -> Standaardwaarde: schade" << endl;
        message << "--niet-schrijven-meta-informatie" << endl;
        message << "  = Schakelt het schrijven van meta-informatie uit" << endl;
        message << "--niet-valideren-json-formaat" << endl;
        message << "  = Schakelt het valideren van het Json-formaat uit" << endl;
        message << endl;
        message << "Voorbeeld:" << endl;
        message << "----------" << endl;
        message << "DiKErnel-cli.exe --invoerbestand Berekening1.json --uitvoerbestand UitvoerBerekening1.json --uitvoerniveau fysica ";
        message << "--niet-schrijven-meta-informatie --niet-valideren-json-formaat" << endl;
        message << endl;
        message << "Bij vragen of onduidelijkheden kunt u contact met ons opnemen via dikernel@deltares.nl" << endl;
        message << endl;

        return message.str();
    }

    bool CommandLineArgumentParser::ReadArguments(
        const int argc,
        char** argv)
    {
        for (int i = 1; i < argc; ++i)
        {
            if (string readKey = argv[i]; readKey.rfind("--", 0) != string::npos)
            {
                auto key = readKey.substr(2);
                string value;

                if (_argumentOptions.contains(key))
                {
                    if (_argumentOptions.at(key) & WithValue)
                    {
                        if (i < argc - 1)
                        {
                            value = argv[++i];
                        }
                        else
                        {
                            return false; // Value missing
                        }
                    }
                }
                else
                {
                    return false; // Unsupported key
                }

                _readArguments.insert(pair(key, value));
            }
            else
            {
                return false; // Key not starting with "--"
            }
        }

        return true;
    }

    bool CommandLineArgumentParser::ValidateReadArguments() const
    {
        const auto requiredArgumentsArePresent = ranges::all_of(_argumentOptions, [this](
                                                            const pair<string, unsigned int>& argumentOption)
                                                                {
                                                                    return !(argumentOption.second & Required)
                                                                            || _readArguments.contains(argumentOption.first);
                                                                });

        return requiredArgumentsArePresent
                && FilePathArgumentHasValidExtension(_readArguments.at(_inputFilePathKey))
                && FilePathArgumentHasValidExtension(_readArguments.at(_outputFilePathKey))
                && OutputLevelHasValidValue();
    }

    bool CommandLineArgumentParser::FilePathArgumentHasValidExtension(
        const string& filePathArgument)
    {
        return path(filePathArgument).extension() == ".json";
    }

    bool CommandLineArgumentParser::OutputLevelHasValidValue() const
    {
        const auto outputLevel = GetOutputLevel();

        return outputLevel == "falen" || outputLevel == "schade" || outputLevel == "fysica";
    }

    string CommandLineArgumentParser::CreateLogOutputFilePath() const
    {
        const auto outputFilePath = path(GetJsonOutputFilePath());
        const auto outputDirectory = outputFilePath.parent_path();
        const auto outputFileName = outputFilePath.stem().string();

        return (outputDirectory / (outputFileName + ".log")).string();
    }
}
