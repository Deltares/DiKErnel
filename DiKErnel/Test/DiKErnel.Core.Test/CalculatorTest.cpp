#include "catch2/catch.hpp"

#include "Calculator.h"

namespace DiKErnel::Core::Test
{
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
}
