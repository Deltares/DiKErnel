#include "catch2/catch.hpp"

#include "OutputComposer.h"

using namespace DiKErnel::KernelWrapper::Json;

TEST_CASE("OutputComposerTest")
{
    SECTION("Constructor_ExpectedValues")
    {
        // Call
        OutputComposer outputComposer;

        // Assert
        REQUIRE(outputComposer.created == true);
    }
}
