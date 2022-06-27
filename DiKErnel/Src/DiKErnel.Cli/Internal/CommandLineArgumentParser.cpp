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
        for (int i = 1; i < argc; ++i)
        {
            if (string readArgument = argv[i]; readArgument.rfind("--", 0) != string::npos)
            {
                auto key = readArgument.substr(2);
                string value;

                if (const auto& foundArgument = _argumentOptions.find(key); foundArgument != _argumentOptions.end())
                {
                    if (foundArgument->second & WithArgument)
                    {
                        value = argv[++i];
                    }
                }
                else
                {
                    _argumentsAreValid = false;
                    return;
                }

                _readArguments.insert(pair(key, value));
            }
        }

        if (!ValidateReadArguments())
        {
            _argumentsAreValid = false;
            return;
        }

        _jsonInputFilePath = argv[1];
        _jsonOutputFilePath = argv[2];
        _logOutputFilePath = CreateLogOutputFilePath();
    }

    bool CommandLineArgumentParser::ArgumentsAreValid() const
    {
        return _argumentsAreValid;
    }

    string CommandLineArgumentParser::GetJsonInputFilePath() const
    {
        return _jsonInputFilePath;
    }

    string CommandLineArgumentParser::GetJsonOutputFilePath() const
    {
        return _jsonOutputFilePath;
    }

    string CommandLineArgumentParser::GetLogOutputFilePath() const
    {
        return _logOutputFilePath;
    }

    string CommandLineArgumentParser::GetHelpMessage()
    {
        stringstream message;

        message << endl;
        message << "   Deze executable kan worden gebruikt voor het uitvoeren van een command line berekening met DiKErnel." << endl;
        message << endl;
        message << "   Verplichte argumenten (in deze volgorde):" << endl;
        message << "   -----------------------------------------" << endl;
        message << "   <pad_naar_input.json>    = het pad van het invoerbestand" << endl;
        message << "   <pad_naar_output.json>   = het pad van het uitvoerbestand (dat ook de locatie van het eventuele logbestand bepaalt)" << endl;
        message << endl;
        message << "   Voorbeeld:" << endl;
        message << "   ----------" << endl;
        message << "   DiKErnel-cli.exe Berekening1.json UitvoerBerekening1.json" << endl;
        message << endl;
        message << "   Bij vragen of onduidelijkheden kunt u contact met ons opnemen via dikernel@deltares.nl." << endl;

        return message.str();
    }

    bool CommandLineArgumentParser::ValidateReadArguments()
    {
        for (const auto& [optionKey, optionType] : _argumentOptions)
        {
            if (const auto& readArgument = _readArguments.find(optionKey); readArgument == _readArguments.end() && optionType & Required)
            {
                return false;
            }
        }

        return FilePathArgumentHasValidExtension(_readArguments["invoerbestand"])
                && FilePathArgumentHasValidExtension(_readArguments["uitvoerbestand"])
                && OutputLevelHasValidValue();
    }

    bool CommandLineArgumentParser::FilePathArgumentHasValidExtension(
        const string& filePathArgument)
    {
        return path(filePathArgument).extension() == ".json";
    }

    bool CommandLineArgumentParser::OutputLevelHasValidValue()
    {
        if (const auto& readArgument = _readArguments.find("uitvoerniveau"); readArgument == _readArguments.end())
        {
            const auto& value = readArgument->second;
            return value == "falen" || value == "schade" || value == "fysica";
        }
        return true;
    }

    string CommandLineArgumentParser::CreateLogOutputFilePath() const
    {
        const auto outputFilePath = path(_jsonOutputFilePath);
        const auto outputDirectory = outputFilePath.parent_path();
        const auto outputFileName = outputFilePath.stem().u8string();

        return (outputDirectory / (outputFileName + ".log")).u8string();
    }
}
