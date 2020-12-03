#include "catch2/catch.hpp"

#include "InputComposer.h"

using namespace DiKErnel::KernelWrapper::JSON;

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
