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

#include "GrassRevetmentOvertoppingRepresentative2PInput.h"

namespace DiKErnel::FunctionLibrary::Test
{
    TEST(GrassRevetmentOvertoppingRepresentative2PInputTest, GivenInput_WhenCreated_ThenExpectedValues)
    {
        // Given & When
        const GrassRevetmentOvertoppingRepresentative2PInput input{};

        // Then
        ASSERT_DOUBLE_EQ(0.0, input._waterLevel);
        ASSERT_DOUBLE_EQ(0.0, input._waveHeightHm0);
        ASSERT_DOUBLE_EQ(0.0, input._wavePeriodTm10);
        ASSERT_DOUBLE_EQ(0.0, input._waveDirection);
        ASSERT_EQ(0.0, input._xValuesProfile.size());
        ASSERT_EQ(0.0, input._zValuesProfile.size());
        ASSERT_EQ(0.0, input._roughnessCoefficients.size());
        ASSERT_DOUBLE_EQ(0.0, input._dikeHeight);
    }
}
