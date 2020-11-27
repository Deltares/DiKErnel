#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "DiKErnel.h"

using namespace Application;

SCENARIO("Test DiKErnel")
{
    REQUIRE(DiKErnel::Run() == "Run the DiKErnel!");
}

SCENARIO("SOME TEST")
{
    REQUIRE(true == true);
}