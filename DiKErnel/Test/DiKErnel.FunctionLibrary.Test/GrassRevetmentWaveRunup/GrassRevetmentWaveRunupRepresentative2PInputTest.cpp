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

#include "GrassRevetmentWaveRunupRepresentative2PInput.h"

namespace DiKErnel::FunctionLibrary::Test
{
    TEST(GrassRevetmentWaveRunupRepresentative2PInputTest, GivenInput_WhenCreated_ThenExpectedValues)
    {
        // Given & When
        constexpr GrassRevetmentWaveRunupRepresentative2PInput input{};

        // Then
        ASSERT_DOUBLE_EQ(0.0, input._surfSimilarityParameter);
        ASSERT_DOUBLE_EQ(0.0, input._waveAngleImpact);
        ASSERT_DOUBLE_EQ(0.0, input._waveHeightHm0);
        ASSERT_DOUBLE_EQ(0.0, input._representativeWaveRunup2PGammab);
        ASSERT_DOUBLE_EQ(0.0, input._representativeWaveRunup2PGammaf);
        ASSERT_DOUBLE_EQ(0.0, input._representativeWaveRunup2PAru);
        ASSERT_DOUBLE_EQ(0.0, input._representativeWaveRunup2PBru);
        ASSERT_DOUBLE_EQ(0.0, input._representativeWaveRunup2PCru);
    }
}