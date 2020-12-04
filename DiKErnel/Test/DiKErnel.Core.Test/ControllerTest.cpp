#include "catch2/catch.hpp"

#include "Controller.h"

namespace DiKErnel::Core::Test
{
    TEST_CASE("ControllerTest")
    {
        SECTION("Constructor_ExpectedValues")
        {
            // Call
            Controller controller;

            // Assert
            REQUIRE(controller.created == true);
        }
    }
}