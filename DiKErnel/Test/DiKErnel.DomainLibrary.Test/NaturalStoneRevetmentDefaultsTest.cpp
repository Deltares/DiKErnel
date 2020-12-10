// Copyright (C) Stichting Deltares 2020. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

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
