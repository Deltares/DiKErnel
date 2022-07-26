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

#include "AsphaltRevetmentWaveImpactFunctionsInput.h"

namespace DiKErnel::FunctionLibrary::Test
{
    using namespace std;

    TEST(AsphaltRevetmentWaveImpactFunctionsInputTest, GivenAsphaltRevetmentWaveImpactFunctionsInput_WhenCreated_ThenExpectedValues)
    {
        // When
        const AsphaltRevetmentWaveImpactFunctionsInput input{};

        // Then
        ASSERT_DOUBLE_EQ(0.0, input._logFailureTension);
        ASSERT_DOUBLE_EQ(0.0, input._averageNumberOfWaves);
        ASSERT_DOUBLE_EQ(0.0, input._maximumPeakStress);
        ASSERT_DOUBLE_EQ(0.0, input._stiffnessRelation);
        ASSERT_DOUBLE_EQ(0.0, input._computationalThickness);
        ASSERT_DOUBLE_EQ(0.0, input._outerSlope);

        const auto factors = vector<pair<double, double>>();
        ASSERT_EQ(factors, input._widthFactors);
        ASSERT_EQ(factors, input._depthFactors);
        ASSERT_EQ(factors, input._impactFactors);

        ASSERT_DOUBLE_EQ(0.0, input._z);
        ASSERT_DOUBLE_EQ(0.0, input._waterLevel);
        ASSERT_DOUBLE_EQ(0.0, input._waveHeightHm0);
        ASSERT_DOUBLE_EQ(0.0, input._fatigueAlpha);
        ASSERT_DOUBLE_EQ(0.0, input._fatigueBeta);
        ASSERT_DOUBLE_EQ(0.0, input._impactNumberC);
    }
}
