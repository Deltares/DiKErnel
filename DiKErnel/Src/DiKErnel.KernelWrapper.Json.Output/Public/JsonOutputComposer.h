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

#include <string>

#include "CalculationOutput.h"
#include "ICalculationInput.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    /*!
     * \brief Class responsible for writing CalculationOutput to Json.
     */
    class JsonOutputComposer
    {
        public:
            /*!
             * \brief Writes the output Json based on the given calculation output.
             * \param filePath
             *        The file to the Json file.
             * \param calculationOutput
             *        The calculation output to write.
             * \param calculationInput
             *        The calculation input that corresponds to the calculation output.
             */
            static void WriteCalculationOutputToJson(
                const std::string& filePath,
                const Core::CalculationOutput& calculationOutput,
                const Core::ICalculationInput& calculationInput);
    };
}
