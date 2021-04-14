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

#include "GrassRevetmentWaveRunup.h"

namespace DiKErnel::FunctionLibrary::Test
{
    TEST(GrassRevetmentWaveRunupTest, IncrementDamage_ValidInput_ExpectedValue)
    {
        // Setup
        const auto cumulativeOverload = 1063.89;
        const auto criticalCumulativeOverload = 7000.0;

        // Call
        const auto incrementDamage = GrassRevetmentWaveRunup::IncrementDamage(cumulativeOverload, criticalCumulativeOverload);

        // Assert
        ASSERT_DOUBLE_EQ(0.15198428571428574, incrementDamage);
    }

    TEST(GrassRevetmentWaveRunupTest, AverageNumberOfWaves_ValidInput_ExpectedValue)
    {
        // Setup
        const auto incrementTime = 900.0;
        const auto wavePeriodTm10 = 1.2;
        const auto averageNumberOfWavesCtm = 6.5;

        // Call
        const auto averageNumberOfWaves = GrassRevetmentWaveRunup::AverageNumberOfWaves(incrementTime, wavePeriodTm10, averageNumberOfWavesCtm);

        // Assert
        ASSERT_DOUBLE_EQ(115.38461538461539, averageNumberOfWaves);
    }

    TEST(GrassRevetmentWaveRunupTest, RepresentativeWaveRunup2P_ValidInput_ExpectedValue)
    {
        // Setup
        const auto surfSimilarityParameter = 1.436;
        const auto waveAngleImpact = 0.901;
        const auto waveHeightHm0 = 2.0;
        const auto representativeWaveRunup2PGammab = 1.1;
        const auto representativeWaveRunup2PGammaf = 1.2;
        const auto representativeWaveRunup2PAru = 1.65;
        const auto representativeWaveRunup2PBru = 4.0;
        const auto representativeWaveRunup2PCru = 1.5;

        // Call
        const auto representativeWaveRunup2P = GrassRevetmentWaveRunup::RepresentativeWaveRunup2P(surfSimilarityParameter,
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

    TEST(GrassRevetmentWaveRunupTest, WaveAngleImpact_ValidInput_ExpectedValue)
    {
        // Setup
        const auto waveAngle = 45.0;
        const auto waveAngleImpactAbeta = 0.0022;
        const auto waveAngleImpactBetamax = 80.0;

        // Call
        const auto waveAngleImpact = GrassRevetmentWaveRunup::WaveAngleImpact(waveAngle, waveAngleImpactAbeta, waveAngleImpactBetamax);

        // Assert
        ASSERT_DOUBLE_EQ(0.901, waveAngleImpact);
    }
}
