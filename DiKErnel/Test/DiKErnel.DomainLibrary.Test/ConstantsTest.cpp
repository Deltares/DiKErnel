#include "catch2/catch.hpp"

#include "Constants.h"

namespace DiKErnel::DomainLibrary::Test::ConstantsTest
{
    TEST_CASE("GivenConstants")
    {
        SECTION("WhenPi_ThenExpectedValue")
        {
            const auto pi = 2 * acos(0.0);
            REQUIRE(Constants::PI == Approx(pi));
        }

        SECTION("WhenGravity_ThenExpectedValue")
        {
            REQUIRE(Constants::GRAVITY == Approx(9.81));
        }
    }
}