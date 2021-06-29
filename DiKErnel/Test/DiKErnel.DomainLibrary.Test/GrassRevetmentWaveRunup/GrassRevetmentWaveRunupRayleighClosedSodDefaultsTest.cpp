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

#include "AssertHelper.h"
#include "GrassRevetmentWaveRunupRayleighClosedSodDefaults.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace TestUtil;

    TEST(GrassRevetmentWaveRunupRayleighClosedSodDefaultsTest, Constructor_ExpectedValues)
    {
        // Call
        const GrassRevetmentWaveRunupRayleighClosedSodDefaults defaults;

        // Assert
        AssertHelper::AssertIsInstanceOf<IGrassRevetmentWaveRunupRayleighDefaults>(&defaults);
        AssertHelper::AssertIsInstanceOf<GrassRevetmentWaveRunupClosedSodDefaults>(&defaults);
        ASSERT_DOUBLE_EQ(7000, defaults.GetCriticalCumulativeOverload());
        ASSERT_DOUBLE_EQ(6.6, defaults.GetCriticalFrontVelocity());
        ASSERT_DOUBLE_EQ(1, defaults.GetIncreasedLoadTransitionAlphaM());
        ASSERT_DOUBLE_EQ(1, defaults.GetReducedStrengthTransitionAlphaS());
        ASSERT_DOUBLE_EQ(0.92, defaults.GetAverageNumberOfWavesCtm());
        ASSERT_DOUBLE_EQ(1.65, defaults.GetRepresentativeWaveRunup2PAru());
        ASSERT_DOUBLE_EQ(4, defaults.GetRepresentativeWaveRunup2PBru());
        ASSERT_DOUBLE_EQ(1.5, defaults.GetRepresentativeWaveRunup2PCru());
        ASSERT_DOUBLE_EQ(1, defaults.GetRepresentativeWaveRunup2PGammab());
        ASSERT_DOUBLE_EQ(1, defaults.GetRepresentativeWaveRunup2PGammaf());
        ASSERT_DOUBLE_EQ(0.0022, defaults.GetWaveAngleImpactAbeta());
        ASSERT_DOUBLE_EQ(80, defaults.GetWaveAngleImpactBetamax());
        ASSERT_EQ(10000, defaults.GetFixedNumberOfWaves());
        ASSERT_DOUBLE_EQ(1.1, defaults.GetFrontVelocityCu());
    }
}
