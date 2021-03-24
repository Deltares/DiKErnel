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
    TEST(NaturalStoneRevetmentDefaultsTest, SimilarityParameterThreshold_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(2.9, NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_XIB);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, PlunginCoefficientA_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(4, NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_AP);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, PlunginCoefficientB_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_BP);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, PlunginCoefficientC_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_CP);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, PlunginCoefficientN_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(-0.9, NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_NP);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, SurgingCoefficientA_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.8, NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_AS);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, SurgingCoefficientB_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_BS);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, SurgingCoefficientC_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_CS);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, SurgingCoefficientN_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.6, NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_NS);
    }
}
