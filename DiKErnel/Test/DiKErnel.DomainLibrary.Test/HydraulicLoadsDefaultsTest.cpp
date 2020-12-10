#include "catch2/catch.hpp"

#include "HydraulicLoadsDefaults.h"

namespace DiKErnel::DomainLibrary::Test::HydraulicLoadsDefaultsTest
{
    TEST_CASE("GivenDefaults")
    {
        SECTION("WhenMaximumWaveAngle_ThenExpectedValue")
        {
            REQUIRE(HydraulicLoadsDefaults::MAXIMUM_WAVE_ANGLE == Approx(78));
        }

        SECTION("WhenWaveAngle_ThenExpectedValue")
        {
            REQUIRE(HydraulicLoadsDefaults::WAVE_ANGLE == Approx(0));
        }
    }
}
