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

#include <limits>

#include <gtest/gtest.h>

#include "AsphaltRevetmentWaveImpactFunctionsInput.h"

namespace DiKErnel::FunctionLibrary::Test
{
    using namespace std;

    TEST(AsphaltRevetmentWaveImpactFunctionsInputTest, Constructor_ExpectedValues)
    {
        // Setup
        const vector widthFactors
        {
            pair(0.1, 0.2)
        };
        const vector depthFactors
        {
            pair(0.3, 0.4)
        };
        const vector impactFactors
        {
            pair(0.5, 0.6)
        };
        constexpr auto z = 0.7;
        constexpr auto fatigueAlpha = 0.8;
        constexpr auto fatigueBeta = 0.9;
        constexpr auto impactNumberC = 1.0;

        // Call
        const AsphaltRevetmentWaveImpactFunctionsInput input(
            z, widthFactors, depthFactors, impactFactors, fatigueAlpha, fatigueBeta, impactNumberC);

        // Assert
        ASSERT_DOUBLE_EQ(z, input.GetZ());
        ASSERT_EQ(widthFactors, input.GetWidthFactors());
        ASSERT_EQ(depthFactors, input.GetDepthFactors());
        ASSERT_EQ(impactFactors, input.GetImpactFactors());
        ASSERT_DOUBLE_EQ(fatigueAlpha, input.GetFatigueAlpha());
        ASSERT_DOUBLE_EQ(fatigueBeta, input.GetFatigueBeta());
        ASSERT_DOUBLE_EQ(impactNumberC, input.GetImpactNumberC());
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), input.GetWaterLevel());
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), input.GetWaveHeightHm0());
    }

    TEST(AsphaltRevetmentWaveImpactFunctionsInputTest, GivenInput_WhenWaterLevelSet_ThenExpectedValue)
    {
        // Given
        const vector<pair<double, double>> factors{};
        AsphaltRevetmentWaveImpactFunctionsInput input(0, factors, factors, factors, 0, 0, 0);

        constexpr auto expectedWaterLevel = 0.1;

        // When
        input.SetWaterLevel(expectedWaterLevel);
        const auto waterLevel = input.GetWaterLevel();

        // Then
        ASSERT_DOUBLE_EQ(expectedWaterLevel, waterLevel);
    }

    TEST(AsphaltRevetmentWaveImpactFunctionsInputTest, GivenInput_WhenWaveHeightSet_ThenExpectedValue)
    {
        // Given
        const vector<pair<double, double>> factors{};
        AsphaltRevetmentWaveImpactFunctionsInput input(0, factors, factors, factors, 0, 0, 0);

        constexpr auto expectedWaveHeight = 0.1;

        // When
        input.SetWaveHeightHm0(expectedWaveHeight);
        const auto waveHeight = input.GetWaveHeightHm0();

        // Then
        ASSERT_DOUBLE_EQ(expectedWaveHeight, waveHeight);
    }
}
