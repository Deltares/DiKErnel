// Copyright (C) Stichting Deltares 2020. All rights reserved.
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

#include <memory>
#include <string>

#include "ICalculationInput.h"
#include "JsonInputProcessType.h"
#include "Result.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    /*!
     * \brief Class responsible for reading Json and turning it into input data.
    */
    class JsonInputComposer
    {
        public:
            /*!
             * \brief Gets input data based on Json.
             * \param filePath
             *        The path to the Json file.
             * \return A tuple with the created ICalculationInput and the JsonInputProcessType.
            */
            static std::unique_ptr<Util::Result<std::tuple<std::unique_ptr<Core::ICalculationInput>, JsonInputProcessType>>> GetInputDataFromJson(
                const std::string& filePath);
    };
}
