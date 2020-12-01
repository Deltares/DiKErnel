#include "catch2/catch.hpp"

#include "Dummy.h"

using namespace DiKErnel::DomainLibrary;

TEST_CASE("DummyTest")
{
    SECTION("Constructor_ExpectedValues")
    {
        Dummy dummy;
        REQUIRE(dummy.created == true);
    }
}
