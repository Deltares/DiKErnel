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

#include "GrassRevetmentWaveImpactOpenSodDefaults.h"

namespace DiKErnel::DomainLibrary::Test
{
    TEST(GrassRevetmentWaveImpactOpenSodDefaultsTest, TimeLineAgwi_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.8, GrassRevetmentWaveImpactOpenSodDefaults::TIME_LINE_AGWI);
    }

    TEST(GrassRevetmentWaveImpactOpenSodDefaultsTest, TimeLineBgwi_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(-0.00001944, GrassRevetmentWaveImpactOpenSodDefaults::TIME_LINE_BGWI);
    }

    TEST(GrassRevetmentWaveImpactOpenSodDefaultsTest, TimeLineCgwi_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.25, GrassRevetmentWaveImpactOpenSodDefaults::TIME_LINE_CGWI);
    }

    TEST(GrassRevetmentWaveImpactOpenSodDefaultsTest, MinimumWaveHeightTemax_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(3600000, GrassRevetmentWaveImpactOpenSodDefaults::MINIMUM_WAVE_HEIGHT_TEMAX);
    }

    TEST(GrassRevetmentWaveImpactOpenSodDefaultsTest, MaximumWaveHeightTemin_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(3.6, GrassRevetmentWaveImpactOpenSodDefaults::MAXIMUM_WAVE_HEIGHT_TEMIN);
    }

    TEST(GrassRevetmentWaveImpactOpenSodDefaultsTest, WaveAngleImpactNwa_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(2.0/3.0, GrassRevetmentWaveImpactOpenSodDefaults::WAVE_ANGLE_IMPACT_NWA);
    }

    TEST(GrassRevetmentWaveImpactOpenSodDefaultsTest, WaveAngleImpactQwa_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.35, GrassRevetmentWaveImpactOpenSodDefaults::WAVE_ANGLE_IMPACT_QWA);
    }

    TEST(GrassRevetmentWaveImpactOpenSodDefaultsTest, WaveAngleImpactRwa_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(10.0, GrassRevetmentWaveImpactOpenSodDefaults::WAVE_ANGLE_IMPACT_RWA);
    }

    TEST(GrassRevetmentWaveImpactOpenSodDefaultsTest, UpperLimitLoadingAul_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.0, GrassRevetmentWaveImpactOpenSodDefaults::UPPER_LIMIT_LOADING_AUL);
    }

    TEST(GrassRevetmentWaveImpactOpenSodDefaultsTest, LowerLimitLoadingAll_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.5, GrassRevetmentWaveImpactOpenSodDefaults::LOWER_LIMIT_LOADING_ALL);
    }
}
