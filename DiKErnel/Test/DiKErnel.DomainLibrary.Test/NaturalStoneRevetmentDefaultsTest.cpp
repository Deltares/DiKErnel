#include "catch2/catch.hpp"

#include "NaturalStoneRevetmentDefaults.h"

namespace DiKErnel::DomainLibrary::Test::NaturalStoneRevetmentDefaultsTest
{
    TEST_CASE("GivenDefaults")
    {
        SECTION("WhenRelativeDensity_ThenExpectedValue")
        {
            REQUIRE(NaturalStoneRevetmentDefaults::RELATIVE_DENSITY == Approx(1.65));
        }

        SECTION("WhenSimilarityParameterThreshold_ThenExpectedValue")
        {
            REQUIRE(NaturalStoneRevetmentDefaults::SIMILARITY_PARAMETER_THRESHOLD == Approx(2.9));
        }

        SECTION("WhenCoefficientPlunginAp_ThenExpectedValue")
        {
            REQUIRE(NaturalStoneRevetmentDefaults::COEFFICIENT_PLUNGING_AP == Approx(4));
        }

        SECTION("WhenCoefficientPlunginBp_ThenExpectedValue")
        {
            REQUIRE(NaturalStoneRevetmentDefaults::COEFFICIENT_PLUNGING_BP == Approx(0.8));
        }

        SECTION("WhenCoefficientPlunginCp_ThenExpectedValue")
        {
            REQUIRE(NaturalStoneRevetmentDefaults::COEFFICIENT_PLUNGING_CP == Approx(0));
        }

        SECTION("WhenCoefficientPlunginNp_ThenExpectedValue")
        {
            REQUIRE(NaturalStoneRevetmentDefaults::COEFFICIENT_PLUNGING_NP == Approx(0));
        }

        SECTION("WhenCoefficientSurgingAs_ThenExpectedValue")
        {
            REQUIRE(NaturalStoneRevetmentDefaults::COEFFICIENT_SURGING_AS == Approx(0));
        }

        SECTION("WhenCoefficientSurgingBs_ThenExpectedValue")
        {
            REQUIRE(NaturalStoneRevetmentDefaults::COEFFICIENT_SURGING_BS == Approx(0));
        }

        SECTION("WhenCoefficientSurgingCs_ThenExpectedValue")
        {
            REQUIRE(NaturalStoneRevetmentDefaults::COEFFICIENT_SURGING_CS == Approx(-0.9));
        }

        SECTION("WhenCoefficientSurgingNs_ThenExpectedValue")
        {
            REQUIRE(NaturalStoneRevetmentDefaults::COEFFICIENT_SURGING_NS == Approx(0.6));
        }
    }
}
