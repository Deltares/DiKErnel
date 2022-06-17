// Copyright (C) Stichting Deltares 2022. All rights reserved.
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

#include "AssertHelper.h"
#include "NaturalStoneRevetmentDefaults.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace TestUtil;

    TEST(NaturalStoneRevetmentDefaultsTest, GetSlopeUpperLevelAus_ExpectedValue)
    {
        // Assert
        ASSERT_DOUBLE_EQ(0.05, NaturalStoneRevetmentDefaults::GetSlopeUpperLevelAus());
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GetSlopeLowerLevelAls_ExpectedValue)
    {
        // Assert
        ASSERT_DOUBLE_EQ(1.5, NaturalStoneRevetmentDefaults::GetSlopeLowerLevelAls());
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GetUpperLimitLoadingAul_ExpectedValue)
    {
        // Assert
        ASSERT_DOUBLE_EQ(0.1, NaturalStoneRevetmentDefaults::GetUpperLimitLoadingAul());
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GetUpperLimitLoadingBul_ExpectedValue)
    {
        // Assert
        ASSERT_DOUBLE_EQ(0.6, NaturalStoneRevetmentDefaults::GetUpperLimitLoadingBul());
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GetUpperLimitLoadingCul_ExpectedValue)
    {
        // Assert
        ASSERT_DOUBLE_EQ(4, NaturalStoneRevetmentDefaults::GetUpperLimitLoadingCul());
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GetLowerLimitLoadingAll_ExpectedValue)
    {
        // Assert
        ASSERT_DOUBLE_EQ(0.1, NaturalStoneRevetmentDefaults::GetLowerLimitLoadingAll());
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GetLowerLimitLoadingBll_ExpectedValue)
    {
        // Assert
        ASSERT_DOUBLE_EQ(0.2, NaturalStoneRevetmentDefaults::GetLowerLimitLoadingBll());
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GetLowerLimitLoadingCll_ExpectedValue)
    {
        // Assert
        ASSERT_DOUBLE_EQ(4, NaturalStoneRevetmentDefaults::GetLowerLimitLoadingCll());
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GetDistanceMaximumWaveElevationAsmax_ExpectedValue)
    {
        // Assert
        ASSERT_DOUBLE_EQ(0.42, NaturalStoneRevetmentDefaults::GetDistanceMaximumWaveElevationAsmax());
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GetDistanceMaximumWaveElevationBsmax_ExpectedValue)
    {
        // Assert
        ASSERT_DOUBLE_EQ(0.9, NaturalStoneRevetmentDefaults::GetDistanceMaximumWaveElevationBsmax());
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GetNormativeWidthOfWaveImpactAwi_ExpectedValue)
    {
        // Assert
        ASSERT_DOUBLE_EQ(0.96, NaturalStoneRevetmentDefaults::GetNormativeWidthOfWaveImpactAwi());
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GetNormativeWidthOfWaveImpactBwi_ExpectedValue)
    {
        // Assert
        ASSERT_DOUBLE_EQ(0.11, NaturalStoneRevetmentDefaults::GetNormativeWidthOfWaveImpactBwi());
    }

    TEST(NaturalStoneRevetmentDefaultsTest, GetWaveAngleImpactBetamax_ExpectedValue)
    {
        // Assert
        ASSERT_DOUBLE_EQ(78, NaturalStoneRevetmentDefaults::GetWaveAngleImpactBetamax());
    }
}
