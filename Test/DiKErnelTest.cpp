#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "catch2/catch_reporter_teamcity.hpp"

TEST_CASE("Test case 1")
{
    SECTION("Section 1")
    {
        REQUIRE(true == true);
    }

    SECTION("Section 2")
    {
        REQUIRE(true == true);
    }
}

TEST_CASE("Test case 2")
{
    SECTION("Section 1")
    {
        REQUIRE(true == true);
    }

    SECTION("Section 2")
    {
        REQUIRE(true == true);
    }
}