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

#include "NordicStoneRevetmentDefaults.h"

namespace DiKErnel::DomainLibrary::Test::NordicStoneRevetmentDefaultsTest
{
    TEST(NordicStoneRevetmentDefaultsTest, SimilarityParameterThreshold_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(2.9, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_XIB);
    }

    TEST(NordicStoneRevetmentDefaultsTest, PlunginCoefficientA_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(4, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_AP);
    }

    TEST(NordicStoneRevetmentDefaultsTest, PlunginCoefficientB_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_BP);
    }

    TEST(NordicStoneRevetmentDefaultsTest, PlunginCoefficientC_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_CP);
    }

    TEST(NordicStoneRevetmentDefaultsTest, PlunginCoefficientN_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(-0.9, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_NP);
    }

    TEST(NordicStoneRevetmentDefaultsTest, SurgingCoefficientA_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.8, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_AS);
    }

    TEST(NordicStoneRevetmentDefaultsTest, SurgingCoefficientB_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_BS);
    }

    TEST(NordicStoneRevetmentDefaultsTest, SurgingCoefficientC_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_CS);
    }

    TEST(NordicStoneRevetmentDefaultsTest, SurgingCoefficientN_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.6, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_NS);
    }
}
