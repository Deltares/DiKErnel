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

namespace DiKErnel::KernelWrapper::Json::Input
{
    /*!
     * \brief Class responsible for reading Json and turning it into ICalculationInput.
    */
    class JsonInputComposer
    {
        public:
            /*!
             * \brief Gets calculation input based on Json.
             * \param filePath
             *        The filepath to the Json file.
             * \return The created ICalculationInput.
            */
            static std::unique_ptr<Core::ICalculationInput> GetCalculationInputFromJson(
                const std::string& filePath);
    };
}
