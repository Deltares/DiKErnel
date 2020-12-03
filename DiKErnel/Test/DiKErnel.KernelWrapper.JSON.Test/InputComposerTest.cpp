#include "catch2/catch.hpp"

#include "InputComposer.h"

using namespace DiKErnel::KernelWrapper::Json;

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
