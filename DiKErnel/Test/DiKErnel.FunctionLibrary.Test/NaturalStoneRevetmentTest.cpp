#include "catch2/catch.hpp"

#include "NaturalStoneRevetment.h"

namespace DiKErnel::FunctionLibrary::Test
{
    TEST_CASE("StoneRevetmentTest")
    {
        SECTION("Constructor_ExpectedValues")
        {
            // Call
            NaturalStoneRevetment dummy;

            // Assert
            REQUIRE(dummy.created == true);
        }
    }
}