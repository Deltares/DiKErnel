#include "catch2/catch.hpp"

#include "InputComposer.h"

using namespace DiKErnel::IO;

TEST_CASE("InputComposerTest")
{
    SECTION("Constructor_ExpectedValues")
    {
        InputComposer inputComposer;
        REQUIRE(inputComposer.created == true);
    }
}
