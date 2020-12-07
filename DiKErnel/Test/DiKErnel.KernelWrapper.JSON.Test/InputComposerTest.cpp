#include <iostream>
#include <filesystem>

#include "catch2/catch.hpp"

#include "InputComposer.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    TEST_CASE("InputComposerTest")
    {
        InputComposer inputComposer;

        SECTION("Constructor_ExpectedValues")
        {
            // Assert
            REQUIRE(inputComposer.created == true);
        }

        SECTION("GetDomainParametersFromJson_Always_ReturnsTimes")
        {
            // Setup
            auto currentPath = std::filesystem::current_path();

            while (currentPath.filename() != "DiKErnel")
            {
                currentPath = currentPath.parent_path();
            }

            const auto testDataPath = currentPath.string() + "\\DiKErnel\\Test\\DiKErnel.KernelWrapper.Json.Test\\test-data";
            
            // Call
            const auto times = inputComposer.GetDomainParametersFromJson(testDataPath + "\\calculation.json");

            // Assert
            REQUIRE_THAT(times, Catch::Equals<int>({0, 100, 500, 800, 1200, 2000 }));
        }
    }
}