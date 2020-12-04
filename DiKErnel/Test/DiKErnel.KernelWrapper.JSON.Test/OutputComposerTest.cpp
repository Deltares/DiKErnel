#include "catch2/catch.hpp"

#include "OutputComposer.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
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
}