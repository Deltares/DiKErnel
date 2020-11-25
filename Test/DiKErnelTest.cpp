#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "catch2/catch_reporter_teamcity.hpp"

SCENARIO()
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

SCENARIO()
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