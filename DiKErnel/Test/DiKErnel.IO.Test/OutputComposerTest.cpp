#include "catch2/catch.hpp"

#include "OutputComposer.h"

using namespace DiKErnel::IO;

TEST_CASE("OutputComposerTest")
{
    SECTION("Constructor_ExpectedValues")
    {
        OutputComposer outputComposer;
        REQUIRE(outputComposer.created == true);
    }
}
