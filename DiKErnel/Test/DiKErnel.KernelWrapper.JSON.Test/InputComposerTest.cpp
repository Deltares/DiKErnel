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

        SECTION("Json_test")
        {
            // Call
            const auto times = inputComposer.GetDomainParametersFromJson("D:\\Development\\DiKErnel\\DiKErnel\\Test\\DiKErnel.KernelWrapper.Json.Test\\test-data\\calculation.json");

            // Assert
            REQUIRE_THAT(times, Catch::Equals<int>({0, 100, 500, 800, 1200, 2000 }));
        }
    }
}