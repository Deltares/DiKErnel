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

#include "nlohmann/json.hpp"

#include "CalculationData.h"
#include "CalculationLocation.h"
#include "HydraulicLoads.h"
#include "InputComposer.h"

namespace DiKErnel::KernelWrapper::Json
{
    class InputData;
    /*!
     * \brief Class responsible for parsing Json input.
     */
    class InputComposer
    {
        public:
            /*!
             * \brief Gets the domain parameters from the Json file represented by the provided
             *        file path.                                                                              
             * \param filePath
             *        The path to the Json file.
             * \return The input data object.
             */
            static std::unique_ptr<InputData> GetDomainParametersFromJson(
                const std::string& filePath);

            /*!
             * \brief Reads the calculation data from the given Json object. 
             * \param json
             *        The Json object to read from.
             * \return The calculation data.
             */
            static std::unique_ptr<CalculationData> ReadCalculationData(
                nlohmann::json* json);

            /*!
             * \brief Reads the hydraulic loads data from the given Json object.
             * \param json
             *        The Json object to read from.
             * \return The hydraulic loads data.
             */
            static std::unique_ptr<HydraulicLoads> ReadHydraulicLoads(
                nlohmann::json* json);

            /*!
            * \brief Reads the calculation location data from the given Json object.
            * \param json
            *        The Json object to read from.
            * \return The calculation location data.
            */
            static std::vector<std::unique_ptr<CalculationLocation>> ReadLocations(
                nlohmann::json* json);

        private:
            static nlohmann::json ParseJson(
                const std::string& filePath);
    };
}
