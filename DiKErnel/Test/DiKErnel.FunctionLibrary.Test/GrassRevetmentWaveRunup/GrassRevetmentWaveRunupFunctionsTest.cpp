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

#include "GrassRevetmentWaveRunupFunctions.h"

namespace DiKErnel::FunctionLibrary::Test
{
    TEST(GrassRevetmentWaveRunupFunctionsTest, IncrementDamage_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto cumulativeOverload = 1063.89;
        constexpr auto criticalCumulativeOverload = 7000.0;

        // Call
        const auto incrementDamage = GrassRevetmentWaveRunupFunctions::IncrementDamage(cumulativeOverload, criticalCumulativeOverload);

        // Assert
        ASSERT_DOUBLE_EQ(0.15198428571428574, incrementDamage);
    }

    TEST(GrassRevetmentWaveRunupFunctionsTest, RepresentativeWaveRunup2P_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto surfSimilarityParameter = 1.436;
        constexpr auto waveAngleImpact = 0.901;
        constexpr auto waveHeightHm0 = 2.0;
        constexpr auto representativeWaveRunup2PGammab = 1.1;
        constexpr auto representativeWaveRunup2PGammaf = 1.2;
        constexpr auto representativeWaveRunup2PAru = 1.65;
        constexpr auto representativeWaveRunup2PBru = 4.0;
        constexpr auto representativeWaveRunup2PCru = 1.5;

        // Call
        const auto representativeWaveRunup2P = GrassRevetmentWaveRunupFunctions::RepresentativeWaveRunup2P(
            surfSimilarityParameter,
            waveAngleImpact,
            waveHeightHm0,
            representativeWaveRunup2PGammab,
            representativeWaveRunup2PGammaf,
            representativeWaveRunup2PAru,
            representativeWaveRunup2PBru,
            representativeWaveRunup2PCru);

        // Assert
        ASSERT_DOUBLE_EQ(5.635949616, representativeWaveRunup2P);
    }

    TEST(GrassRevetmentWaveRunupFunctionsTest, WaveAngleImpact_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto waveAngle = 45.0;
        constexpr auto waveAngleImpactAbeta = 0.0022;
        constexpr auto waveAngleImpactBetamax = 80.0;

        // Call
        const auto waveAngleImpact = GrassRevetmentWaveRunupFunctions::WaveAngleImpact(waveAngle, waveAngleImpactAbeta, waveAngleImpactBetamax);

        // Assert
        ASSERT_DOUBLE_EQ(0.901, waveAngleImpact);
    }
}
