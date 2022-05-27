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
        if (!ValidateArguments(argc, argv))
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
        message << "********************** DiKErnel instructies **********************" << endl;
        message << "DiKErnel heeft 2 argumenten nodig om te kunnen draaien" << endl;
        message << "    <pad_naar_input.json>" << endl;
        message << "    <pad_naar_output.json>" << endl;
        message << "DiKErnel kan gebruikt worden door DiKErnel-cli.exe te starten vanuit de command line met deze argumenten" << endl;
        message << "Voorbeeld: DiKernel.exe Berekening1.json UitvoerBerekening1.json" << endl << endl;

        return message.str();
    }

    bool CommandLineArgumentParser::ValidateArguments(
        const int argc,
        char** argv)
    {
        return argc == 3
                && ArgumentHasValidExtension(argv[1])
                && ArgumentHasValidExtension(argv[2]);
    }

    bool CommandLineArgumentParser::ArgumentHasValidExtension(
        const string& filePathArgument)
    {
        return path(filePathArgument).extension() == ".json";
    }

    string CommandLineArgumentParser::CreateLogOutputFilePath() const
    {
        const auto outputFilePath = path(_jsonOutputFilePath);
        const auto outputDirectory = outputFilePath.parent_path();
        const auto outputFileName = outputFilePath.stem().u8string();

        return (outputDirectory / (outputFileName + ".log")).u8string();
    }
}
