#pragma once

#include "nlohmann/json.hpp"

namespace DiKErnel::KernelWrapper::Json
{
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
             * \return The times from the domain parameters.
             */
            std::vector<int> GetDomainParametersFromJson(std::string filePath) const;

        private:
            nlohmann::json ParseJson(std::string filePath) const;
    };
}
