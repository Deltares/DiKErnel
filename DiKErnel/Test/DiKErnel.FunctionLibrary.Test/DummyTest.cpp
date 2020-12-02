#include "catch2/catch.hpp"

#include "Dummy.h"

using namespace DiKErnel::FunctionLibrary;

TEST_CASE("DummyTest")
{
    SECTION("Constructor_ExpectedValues")
    {
        // Call
        Dummy dummy;

        // Assert
        REQUIRE(dummy.created == true);
    }
}
