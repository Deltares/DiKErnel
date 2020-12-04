#include "catch2/catch.hpp"

#include "Dummy.h"

namespace DiKErnel::DomainLibrary::Test
{
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
}