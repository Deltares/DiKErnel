#include "catch2/catch.hpp"

#include "Constants.h"

namespace DiKErnel::DomainLibrary::Test::ConstantsTest
{
    TEST_CASE("GivenConstants")
    {
        SECTION("WhenPi_ThenExpectedValue")
        {
            const auto pi = 2 * acos(0.0);
            REQUIRE(Constants::Pi == Approx(pi));
        }
    }
}