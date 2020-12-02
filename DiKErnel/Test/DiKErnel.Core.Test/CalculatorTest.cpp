#include "catch2/catch.hpp"

#include "Calculator.h"

using namespace DiKErnel::Core;

TEST_CASE("CalculatorTest")
{
    SECTION("Constructor_ExpectedValues")
    {
        // Call
        Calculator calculator;

        // Assert
        REQUIRE(calculator.created == true);
    }
}
