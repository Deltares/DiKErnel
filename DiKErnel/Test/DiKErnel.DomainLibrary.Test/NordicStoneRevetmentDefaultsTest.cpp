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

namespace DiKErnel::DomainLibrary::Test
{
    TEST(NordicStoneRevetmentDefaultsTest, hydraulicLoadXib_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(2.9, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_XIB);
    }

    TEST(NordicStoneRevetmentDefaultsTest, hydraulicLoadAp_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(4, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_AP);
    }

    TEST(NordicStoneRevetmentDefaultsTest, hydraulicLoadBp_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_BP);
    }

    TEST(NordicStoneRevetmentDefaultsTest, hydraulicLoadCp_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_CP);
    }

    TEST(NordicStoneRevetmentDefaultsTest, hydraulicLoadNp_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(-0.9, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_NP);
    }

    TEST(NordicStoneRevetmentDefaultsTest, hydraulicLoadAs_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.8, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_AS);
    }

    TEST(NordicStoneRevetmentDefaultsTest, hydraulicLoadBs_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_BS);
    }

    TEST(NordicStoneRevetmentDefaultsTest, hydraulicLoadCs_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_CS);
    }

    TEST(NordicStoneRevetmentDefaultsTest, hydraulicLoadNs_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.6, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_NS);
    }

    TEST(NordicStoneRevetmentDefaultsTest, UpperLimitLoadingAul_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.1, NordicStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_AUL);
    }

    TEST(NordicStoneRevetmentDefaultsTest, UpperLimitLoadingBul_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.6, NordicStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_BUL);
    }

    TEST(NordicStoneRevetmentDefaultsTest, UpperLimitLoadingCul_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(4, NordicStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_CUL);
    }

    TEST(NordicStoneRevetmentDefaultsTest, LowerLimitLoadingAll_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.1, NordicStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_ALL);
    }

    TEST(NordicStoneRevetmentDefaultsTest, LowerLimitLoadingBll_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.2, NordicStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_BLL);
    }

    TEST(NordicStoneRevetmentDefaultsTest, LowerLimitLoadingCll_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(4, NordicStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_CLL);
    }

    TEST(NordicStoneRevetmentDefaultsTest, DistanceMaximumWaveElevationAsmax_ExpectedValues)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.42, NordicStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_ASMAX);
    }

    TEST(NordicStoneRevetmentDefaultsTest, DistanceMaximumWaveElevationBsmax_ExpectedValues)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.9, NordicStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_BSMAX);
    }

    TEST(NordicStoneRevetmentDefaultsTest, NormativeWidthOfWaveImpactAwi_ExpectedValues)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.96, NordicStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE_AWI);
    }

    TEST(NordicStoneRevetmentDefaultsTest, NormativeWidthOfWaveImpactBwi_ExpectedValues)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.11, NordicStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE_BWI);
    }

    TEST(NordicStoneRevetmentDefaultsTest, WaveAngleImpactBetamax_ExpectedValues)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(78, NordicStoneRevetmentDefaults::WAVE_ANGLE_IMPACT_ON_NATURAL_STONE_BETAMAX);
    }
}
