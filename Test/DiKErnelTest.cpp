#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "catch2/catch_reporter_teamcity.hpp"

TEST_CASE("Our first test case")
{
    SECTION("Our first test")
    {
        REQUIRE(true == true);
    }
}