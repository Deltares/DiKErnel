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

#include "AsphaltRevetmentWaveImpactFunctionsCalculatedInput.h"

namespace DiKErnel::FunctionLibrary::Test
{
    using namespace std;

    TEST(AsphaltRevetmentWaveImpactFunctionsCalculatedInputTest, Constructor_ExpectedValues)
    {
        // Setup
        constexpr auto logFailureTension = 0.1;
        constexpr auto computationalThickness = 0.2;
        constexpr auto stiffnessRelation = 0.3;
        constexpr auto equivalentElasticModulus = 0.4;
        constexpr auto outerSlope = 0.5;

        // Call
        const AsphaltRevetmentWaveImpactFunctionsCalculatedInput input(logFailureTension, computationalThickness, stiffnessRelation,
                                                                       equivalentElasticModulus, outerSlope);

        // Assert
        ASSERT_DOUBLE_EQ(logFailureTension, input.GetLogFailureTension());
        ASSERT_DOUBLE_EQ(computationalThickness, input.GetComputationalThickness());
        ASSERT_DOUBLE_EQ(stiffnessRelation, input.GetStiffnessRelation());
        ASSERT_DOUBLE_EQ(equivalentElasticModulus, input.GetEquivalentElasticModulus());
        ASSERT_DOUBLE_EQ(outerSlope, input.GetOuterSlope());
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), input.GetAverageNumberOfWaves());
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), input.GetMaximumPeakStress());
    }

    TEST(AsphaltRevetmentWaveImpactFunctionsCalculatedInputTest, GivenInput_WhenAverageNumberOfWavesSet_ThenExpectedValue)
    {
        // Given
        AsphaltRevetmentWaveImpactFunctionsCalculatedInput input(0, 0, 0, 0, 0);

        constexpr auto expectedAverageNumberOfWaves = 0.1;

        // When
        input.SetAverageNumberOfWaves(expectedAverageNumberOfWaves);
        const auto averageNumberOfWaves = input.GetAverageNumberOfWaves();

        // Then
        ASSERT_DOUBLE_EQ(expectedAverageNumberOfWaves, averageNumberOfWaves);
    }

    TEST(AsphaltRevetmentWaveImpactFunctionsCalculatedInputTest, GivenInput_WhenWaveHeightSet_ThenExpectedValue)
    {
        // Given
        AsphaltRevetmentWaveImpactFunctionsCalculatedInput input(0, 0, 0, 0, 0);

        constexpr auto expectedMaximumPeakStress = 0.1;

        // When
        input.SetMaximumPeakStress(expectedMaximumPeakStress);
        const auto maximumPeakStress = input.GetMaximumPeakStress();

        // Then
        ASSERT_DOUBLE_EQ(expectedMaximumPeakStress, maximumPeakStress);
    }
}
