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
        ASSERT_DOUBLE_EQ(2.9, NaturalStoneRevetmentDefaults::SIMILARITY_PARAMETER_THRESHOLD);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, PlunginCoefficientA_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(4, NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_A);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, PlunginCoefficientB_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_B);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, PlunginCoefficientC_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_C);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, PlunginCoefficientN_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(-0.9, NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_N);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, SurgingCoefficientA_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.8, NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_A);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, SurgingCoefficientB_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_B);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, SurgingCoefficientC_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_C);
    }

    TEST(NaturalStoneRevetmentDefaultsTest, SurgingCoefficientN_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.6, NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_N);
    }
}
