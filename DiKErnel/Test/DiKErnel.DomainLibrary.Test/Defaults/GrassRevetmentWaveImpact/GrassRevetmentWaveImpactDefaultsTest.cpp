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

#include "GrassRevetmentWaveImpactDefaults.h"

namespace DiKErnel::DomainLibrary::Test
{
    TEST(GrassRevetmentWaveImpactDefaultsTest, GetMinimumWaveHeightTemax_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(3600000, GrassRevetmentWaveImpactDefaults::GetMinimumWaveHeightTemax());
    }

    TEST(GrassRevetmentWaveImpactDefaultsTest, GetMaximumWaveHeightTemin_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(3.6, GrassRevetmentWaveImpactDefaults::GetMaximumWaveHeightTemin());
    }

    TEST(GrassRevetmentWaveImpactDefaultsTest, GetWaveAngleImpactNwa_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(2.0 / 3.0, GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactNwa());
    }

    TEST(GrassRevetmentWaveImpactDefaultsTest, GetWaveAngleImpactQwa_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.35, GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactQwa());
    }

    TEST(GrassRevetmentWaveImpactDefaultsTest, GetWaveAngleImpactRwa_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(10, GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactRwa());
    }

    TEST(GrassRevetmentWaveImpactDefaultsTest, GetUpperLimitLoadingAul_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, GrassRevetmentWaveImpactDefaults::GetUpperLimitLoadingAul());
    }

    TEST(GrassRevetmentWaveImpactDefaultsTest, GetLowerLimitLoadingAll_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.5, GrassRevetmentWaveImpactDefaults::GetLowerLimitLoadingAll());
    }
}
