#pragma once

#include "CalculationData.h"
#include "CalculationLocation.h"
#include "HydraulicLoads.h"
#include "InputComposer.h"
#include "nlohmann/json.hpp"

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
             * \brief Gets the domain parameters from the given json.
             * \param filePath
             *        The path to the json file.
             * \return The input data object.
             */
            static InputData GetDomainParametersFromJson(
                std::string filePath);

            /*!
             * \brief Reads the calculation data from the given json object. 
             * \param json
             *        The json object to read from.
             * \return The calculation data.
             */
            static CalculationData ReadCalculationData(
                nlohmann::json json);

            /*!
             * \brief Reads the hydraulic loads data from the given json object.
             * \param json
             *        The json object to read from.
             * \return The hydraulic loads data.
             */
            static HydraulicLoads ReadHydraulicLoads(
                nlohmann::json json);

            /*!
            * \brief Reads the calculation location data from the given json object.
            * \param json
            *        The json object to read from.
            * \return The calculation location data.
            */
            static std::vector<CalculationLocation> ReadLocations(
                nlohmann::json json);

        private:
            static nlohmann::json ParseJson(
                const std::string& filePath);
    };
}
