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

#pragma once

#include <map>
#include <string>

#include "ArgumentType.h"

namespace DiKErnel::Cli
{
    class CommandLineArgumentParser
    {
        public:
            explicit CommandLineArgumentParser(
                int argc,
                char** argv);

            [[nodiscard]]
            bool ArgumentsAreValid() const;

            [[nodiscard]]
            std::string GetJsonInputFilePath() const;

            [[nodiscard]]
            std::string GetJsonOutputFilePath() const;

            [[nodiscard]]
            std::string GetLogOutputFilePath() const;

            static std::string GetHelpMessage();

        private:
            bool _argumentsAreValid = true;
            std::string _jsonInputFilePath;
            std::string _jsonOutputFilePath;
            std::string _logOutputFilePath;

            std::map<std::string, std::string> _readArguments = std::map<std::string, std::string>();

            static inline std::map<std::string, unsigned int> _argumentOptions =
            {
                std::pair<std::string, unsigned int>("invoerbestand", Required | WithArgument),
                std::pair<std::string, unsigned int>("uitvoerbestand", Required | WithArgument),
                std::pair<std::string, unsigned int>("uitvoerniveau", Optional | WithArgument),
                std::pair<std::string, unsigned int>("niet-schrijven-meta-informatie", Optional),
                std::pair<std::string, unsigned int>("niet-valideren-json-formaat", Optional),
            };

            bool ValidateReadArguments();

            static bool FilePathArgumentHasValidExtension(
                const std::string& filePathArgument);

            bool OutputLevelHasValidValue();

            [[nodiscard]]
            std::string CreateLogOutputFilePath() const;
    };
}
