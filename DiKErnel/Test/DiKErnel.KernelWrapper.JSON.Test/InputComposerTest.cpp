#include "catch2/catch.hpp"

#include "InputComposer.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    TEST_CASE("InputComposerTest")
    {
        SECTION("Constructor_ExpectedValues")
        {
            // Call
            InputComposer inputComposer;

            // Assert
            REQUIRE(inputComposer.created == true);
        }
    }
}