#pragma once

#include "nlohmann/json.hpp"

namespace DiKErnel::KernelWrapper::Json
{
    class InputData;
    /*!
     * Class responsible for parsing Json input.
     */
    class InputComposer
    {
        public:
            /*!
             * \brief Gets the domain parameters from the given json.
             * \param filePath
             *        The path to the json file.
             */
            void GetDomainParametersFromJson(std::string filePath) const;

            static void ReadCalculationData(nlohmann::json json, InputData& inputData);
            static void ReadHydraulicLoads(nlohmann::json json, InputData& inputData);
            static void ReadLocations(nlohmann::json json, InputData& inputData);

        private:
            nlohmann::json ParseJson(std::string filePath) const;
    };
}
