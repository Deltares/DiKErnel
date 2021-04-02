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
    TEST(NordicStoneRevetmentDefaultsTest, HydraulicLoadXib_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(2.9, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_XIB);
    }

    TEST(NordicStoneRevetmentDefaultsTest, HydraulicLoadAp_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(4, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_AP);
    }

    TEST(NordicStoneRevetmentDefaultsTest, HydraulicLoadBp_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_BP);
    }

    TEST(NordicStoneRevetmentDefaultsTest, HydraulicLoadCp_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_CP);
    }

    TEST(NordicStoneRevetmentDefaultsTest, HydraulicLoadNp_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(-0.9, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_NP);
    }

    TEST(NordicStoneRevetmentDefaultsTest, HydraulicLoadAs_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.8, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_AS);
    }

    TEST(NordicStoneRevetmentDefaultsTest, HydraulicLoadBs_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_BS);
    }

    TEST(NordicStoneRevetmentDefaultsTest, HydraulicLoadCs_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_CS);
    }

    TEST(NordicStoneRevetmentDefaultsTest, HydraulicLoadNs_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.6, NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_NS);
    }

    TEST(NordicStoneRevetmentDefaultsTest, UpperLimitLoadingAul_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.1, NordicStoneRevetmentDefaults::UPPER_LIMIT_LOADING_AUL);
    }

    TEST(NordicStoneRevetmentDefaultsTest, UpperLimitLoadingBul_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.6, NordicStoneRevetmentDefaults::UPPER_LIMIT_LOADING_BUL);
    }

    TEST(NordicStoneRevetmentDefaultsTest, UpperLimitLoadingCul_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(4, NordicStoneRevetmentDefaults::UPPER_LIMIT_LOADING_CUL);
    }

    TEST(NordicStoneRevetmentDefaultsTest, LowerLimitLoadingAll_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.1, NordicStoneRevetmentDefaults::LOWER_LIMIT_LOADING_ALL);
    }

    TEST(NordicStoneRevetmentDefaultsTest, LowerLimitLoadingBll_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.2, NordicStoneRevetmentDefaults::LOWER_LIMIT_LOADING_BLL);
    }

    TEST(NordicStoneRevetmentDefaultsTest, LowerLimitLoadingCll_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(4, NordicStoneRevetmentDefaults::LOWER_LIMIT_LOADING_CLL);
    }

    TEST(NordicStoneRevetmentDefaultsTest, DistanceMaximumWaveElevationAsmax_ExpectedValues)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.42, NordicStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_ASMAX);
    }

    TEST(NordicStoneRevetmentDefaultsTest, DistanceMaximumWaveElevationBsmax_ExpectedValues)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.9, NordicStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_BSMAX);
    }

    TEST(NordicStoneRevetmentDefaultsTest, NormativeWidthOfWaveImpactAwi_ExpectedValues)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.96, NordicStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI);
    }

    TEST(NordicStoneRevetmentDefaultsTest, NormativeWidthOfWaveImpactBwi_ExpectedValues)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.11, NordicStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI);
    }

    TEST(NordicStoneRevetmentDefaultsTest, WaveAngleImpactBetamax_ExpectedValues)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(78, NordicStoneRevetmentDefaults::WAVE_ANGLE_IMPACT_BETAMAX);
    }
}
