#pragma once

#include <filesystem>

namespace DiKErnel::TestUtil
{
    /*!
     * \brief Helper class for getting test data paths.
    */
    class TestDataHelper
    {
        public:

            /*!
             * \brief Gets the test data path.
             * \param currentNamespace
             *        The namespace of the test project. 
             * \return The path to the test data.
            */
            static std::filesystem::path GetTestDataPath(std::string currentNamespace);
    };
}
