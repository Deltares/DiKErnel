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

#include <gtest/gtest.h>

#include "NaturalStoneRevetmentDefaults.h"

namespace DiKErnel::DomainLibrary::Test::NaturalStoneRevetmentDefaultsTest
{
    TEST(NaturalStoneRevetmentDefaultsTest, GivenDefaults_whenRelativeDensity_ThenExpectedValue)
    {
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::RELATIVE_DENSITY, 1.65);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GivenDefaults_whenSimilarityParameterThreshold_ThenExpectedValue)
    {
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::SIMILARITY_PARAMETER_THRESHOLD, 2.9);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GivenDefaults_whenCoefficientPlunginAp_ThenExpectedValue)
    {
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::COEFFICIENT_PLUNGING_AP, 4);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GivenDefaults_whenCoefficientPlunginBp_ThenExpectedValue)
    {
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::COEFFICIENT_PLUNGING_BP, 0.8);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GivenDefaults_whenCoefficientPlunginCp_ThenExpectedValue)
    {
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::COEFFICIENT_PLUNGING_CP, 0);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GivenDefaults_whenCoefficientPlunginNp_ThenExpectedValue)
    {
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::COEFFICIENT_PLUNGING_NP, 0);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GivenDefaults_whenCoefficientSurgingAs_ThenExpectedValue)
    {
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::COEFFICIENT_SURGING_AS, 0);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GivenDefaults_whenCoefficientSurgingBs_ThenExpectedValue)
    {
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::COEFFICIENT_SURGING_BS, 0);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GivenDefaults_whenCoefficientSurgingCs_ThenExpectedValue)
    {
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::COEFFICIENT_SURGING_CS, -0.9);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GivenDefaults_whenCoefficientSurgingNs_ThenExpectedValue)
    {
        ASSERT_DOUBLE_EQ(NaturalStoneRevetmentDefaults::COEFFICIENT_SURGING_NS, 0.6);
    }
}
