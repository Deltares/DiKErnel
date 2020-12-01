#include "catch2/catch.hpp"

#include "Controller.h"

using namespace DiKErnel::Core;

TEST_CASE("ControllerTest")
{
    SECTION("Constructor_ExpectedValues")
    {
        Controller controller;
        REQUIRE(controller.created == true);
    }
}