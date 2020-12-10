#include "catch2/catch.hpp"

#include "Constants.h"

namespace DiKErnel::DomainLibrary::Test
{
    TEST_CASE("DummyTest")
    {
        SECTION("Constructor_ExpectedValues")
        {
            // Call
            Constants dummy;

            // Assert
            REQUIRE(dummy.created == true);
        }
    }
}