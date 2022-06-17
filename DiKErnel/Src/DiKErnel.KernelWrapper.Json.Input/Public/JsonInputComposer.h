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

#include "DataResult.h"
#include "JsonInputComposerResult.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    /*!
     * \brief Class responsible for reading Json and turning it into input data.
     */
    class JsonInputComposer
    {
        public:
            /*!
             * \brief Performs a Json schema based validation.
             * \param filePath
             *        The path to the Json file to validate.
             * \return The result of the operation.
             */
            static std::string ValidateJson(
                const std::string& filePath);

            /*!
             * \brief Gets input data based on Json.
             * \param filePath
             *        The path to the Json file to get the input from.
             * \return The result of the operation.
             */
            static std::unique_ptr<Util::DataResult<JsonInputComposerResult>> GetInputDataFromJson(
                const std::string& filePath);
    };
}
