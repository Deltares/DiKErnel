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

#include "GrassRevetmentWaveRunupRayleigh.h"

namespace DiKErnel::FunctionLibrary::Test
{
    TEST(GrassRevetmentWaveRunupRayleighTest, CumulativeOverload_ValidInput_ExpectedValue)
    {
        // Setup
        const auto averageNumberOfWaves = 187.5;
        const auto representativeWaveRunup2p = 2.98;
        const auto fixedNumberOfWaves = 10000;
        const auto positionZ = 1.0;
        const auto waterLevel = 0.03;
        const auto criticalFrontVelocity = 4.0;
        const auto increasedLoadTransitionAlphaM = 1.1;
        const auto reducedStrengthTransitionAlphaS = 1.2;
        const auto frontVelocityCu = 1.3;
        const auto gravitationalAcceleration = 9.81;

        // Call
        const auto cumulativeOverload = GrassRevetmentWaveRunupRayleigh::CumulativeOverload(
            averageNumberOfWaves,
            representativeWaveRunup2p,
            fixedNumberOfWaves,
            positionZ,
            waterLevel,
            criticalFrontVelocity,
            increasedLoadTransitionAlphaM,
            reducedStrengthTransitionAlphaS,
            frontVelocityCu,
            gravitationalAcceleration);

        // Assert
        ASSERT_DOUBLE_EQ(215.067825119515, cumulativeOverload);
    }
}
