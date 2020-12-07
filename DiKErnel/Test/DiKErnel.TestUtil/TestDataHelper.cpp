#include "TestDataHelper.h"

#include <filesystem>

namespace DiKErnel::TestUtil
{
    std::filesystem::path TestDataHelper::GetTestDataPath(const std::string currentNamespace)
    {
        auto currentPath = std::filesystem::current_path();

        while (currentPath.filename() != "DiKErnel")
        {
            currentPath = currentPath.parent_path();
        }

        return currentPath / "DiKErnel" / "Test" / currentNamespace / "test-data";
    }
}
