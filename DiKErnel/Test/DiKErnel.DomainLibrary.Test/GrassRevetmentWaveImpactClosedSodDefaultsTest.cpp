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

#include "GrassRevetmentWaveImpactClosedSodDefaults.h"

namespace DiKErnel::DomainLibrary::Test
{
    TEST(GrassRevetmentWaveImpactClosedSodDefaultsTest, TimeLineAgwi_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(1, GrassRevetmentWaveImpactClosedSodDefaults::TIME_LINE_AGWI);
    }

    TEST(GrassRevetmentWaveImpactClosedSodDefaultsTest, TimeLineBgwi_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(-0.000009722, GrassRevetmentWaveImpactClosedSodDefaults::TIME_LINE_BGWI);
    }

    TEST(GrassRevetmentWaveImpactClosedSodDefaultsTest, TimeLineCgwi_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.25, GrassRevetmentWaveImpactClosedSodDefaults::TIME_LINE_CGWI);
    }

    TEST(GrassRevetmentWaveImpactClosedSodDefaultsTest, MinimumWaveHeightTemax_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(3600000, GrassRevetmentWaveImpactClosedSodDefaults::MINIMUM_WAVE_HEIGHT_TEMAX);
    }

    TEST(GrassRevetmentWaveImpactClosedSodDefaultsTest, MaximumWaveHeightTemin_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(3.6, GrassRevetmentWaveImpactClosedSodDefaults::MAXIMUM_WAVE_HEIGHT_TEMIN);
    }

    TEST(GrassRevetmentWaveImpactClosedSodDefaultsTest, WaveAngleImpactNwa_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(2.0 / 3.0, GrassRevetmentWaveImpactClosedSodDefaults::WAVE_ANGLE_IMPACT_NWA);
    }

    TEST(GrassRevetmentWaveImpactClosedSodDefaultsTest, WaveAngleImpactQwa_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.35, GrassRevetmentWaveImpactClosedSodDefaults::WAVE_ANGLE_IMPACT_QWA);
    }

    TEST(GrassRevetmentWaveImpactClosedSodDefaultsTest, WaveAngleImpactRwa_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(10, GrassRevetmentWaveImpactClosedSodDefaults::WAVE_ANGLE_IMPACT_RWA);
    }

    TEST(GrassRevetmentWaveImpactClosedSodDefaultsTest, UpperLimitLoadingAul_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0, GrassRevetmentWaveImpactClosedSodDefaults::UPPER_LIMIT_LOADING_AUL);
    }

    TEST(GrassRevetmentWaveImpactClosedSodDefaultsTest, LowerLimitLoadingAll_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(0.5, GrassRevetmentWaveImpactClosedSodDefaults::LOWER_LIMIT_LOADING_ALL);
    }
}
