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

#include "AsphaltRevetmentWaveImpactDefaults.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;

    TEST(AsphaltRevetmentWaveImpactDefaultsTest, GetDensityOfWater_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(1025, AsphaltRevetmentWaveImpactDefaults::GetDensityOfWater());
    }

    TEST(AsphaltRevetmentWaveImpactDefaultsTest, GetAverageNumberOfWavesCtm_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(1, AsphaltRevetmentWaveImpactDefaults::GetAverageNumberOfWavesCtm());
    }

    TEST(AsphaltRevetmentWaveImpactDefaultsTest, GetImpactNumberC_ExpectedValue)
    {
        // Call & Assert
        ASSERT_DOUBLE_EQ(1, AsphaltRevetmentWaveImpactDefaults::GetImpactNumberC());
    }

    TEST(AsphaltRevetmentWaveImpactDefaultsTest, GetWidthFactors_ExpectedValue)
    {
        // Setup
        const auto expectedWidthFactors = vector
        {
            pair(0.1, 0.0392),
            pair(0.2, 0.0738),
            pair(0.3, 0.1002),
            pair(0.4, 0.1162),
            pair(0.5, 0.1213),
            pair(0.6, 0.1168),
            pair(0.7, 0.1051),
            pair(0.8, 0.0890),
            pair(0.9, 0.0712),
            pair(1.0, 0.0541),
            pair(1.1, 0.0391),
            pair(1.2, 0.0269),
            pair(1.3, 0.0216),
            pair(1.4, 0.0150),
            pair(1.5, 0.0105)
        };

        // Call & Assert
        ASSERT_EQ(expectedWidthFactors, AsphaltRevetmentWaveImpactDefaults::GetWidthFactors());
    }

    TEST(AsphaltRevetmentWaveImpactDefaultsTest, GetDepthFactors_ExpectedValue)
    {
        // Setup
        const auto expectedDepthFactors = vector
        {
            pair(-1.0, 0.0244),
            pair(-0.875, 0.0544),
            pair(-0.750, 0.0938),
            pair(-0.625, 0.1407),
            pair(-0.500, 0.1801),
            pair(-0.375, 0.1632),
            pair(-0.250, 0.1426),
            pair(-0.125, 0.0994),
            pair(0.0, 0.06),
            pair(0.125, 0.0244),
            pair(0.250, 0.0169)
        };

        // Call & Assert
        ASSERT_EQ(expectedDepthFactors, AsphaltRevetmentWaveImpactDefaults::GetDepthFactors());
    }

    TEST(AsphaltRevetmentWaveImpactDefaultsTest, GetImpactFactors_ExpectedValue)
    {
        // Setup
        const auto expectedImpactFactors = vector
        {
            pair(2.0, 0.039),
            pair(2.4, 0.1),
            pair(2.8, 0.18),
            pair(3.2, 0.235),
            pair(3.6, 0.2),
            pair(4.0, 0.13),
            pair(4.4, 0.08),
            pair(4.8, 0.02),
            pair(5.2, 0.01),
            pair(5.6, 0.005),
            pair(6.0, 0.001)
        };

        // Call & Assert
        ASSERT_EQ(expectedImpactFactors, AsphaltRevetmentWaveImpactDefaults::GetImpactFactors());
    }
}
