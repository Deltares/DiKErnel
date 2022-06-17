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

#include "GrassRevetmentWaveRunupDefaults.h"

namespace DiKErnel::DomainLibrary::Test
{
    TEST(GrassRevetmentWaveRunupDefaultsTest, GetIncreasedLoadTransitionAlphaM_ExpectedValue)
    {
        // Call& Assert
        ASSERT_DOUBLE_EQ(1, GrassRevetmentWaveRunupDefaults::GetIncreasedLoadTransitionAlphaM());
    }

    TEST(GrassRevetmentWaveRunupDefaultsTest, GetReducedStrengthTransitionAlphaS_ExpectedValue)
    {
        // Call& Assert
        ASSERT_DOUBLE_EQ(1, GrassRevetmentWaveRunupDefaults::GetReducedStrengthTransitionAlphaS());
    }

    TEST(GrassRevetmentWaveRunupDefaultsTest, GetAverageNumberOfWavesCtm_ExpectedValue)
    {
        // Call& Assert
        ASSERT_DOUBLE_EQ(0.92, GrassRevetmentWaveRunupDefaults::GetAverageNumberOfWavesCtm());
    }

    TEST(GrassRevetmentWaveRunupDefaultsTest, GetRepresentativeWaveRunup2PAru_ExpectedValue)
    {
        // Call& Assert
        ASSERT_DOUBLE_EQ(1.65, GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PAru());
    }

    TEST(GrassRevetmentWaveRunupDefaultsTest, GetRepresentativeWaveRunup2PBru_ExpectedValue)
    {
        // Call& Assert
        ASSERT_DOUBLE_EQ(4, GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PBru());
    }

    TEST(GrassRevetmentWaveRunupDefaultsTest, GetRepresentativeWaveRunup2PCru_ExpectedValue)
    {
        // Call& Assert
        ASSERT_DOUBLE_EQ(1.5, GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PCru());
    }

    TEST(GrassRevetmentWaveRunupDefaultsTest, GetRepresentativeWaveRunup2PGammab_ExpectedValue)
    {
        // Call& Assert
        ASSERT_DOUBLE_EQ(1, GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PGammab());
    }

    TEST(GrassRevetmentWaveRunupDefaultsTest, GetRepresentativeWaveRunup2PGammaf_ExpectedValue)
    {
        // Call& Assert
        ASSERT_DOUBLE_EQ(1, GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PGammaf());
    }

    TEST(GrassRevetmentWaveRunupDefaultsTest, GetWaveAngleImpactAbeta_ExpectedValue)
    {
        // Call& Assert
        ASSERT_DOUBLE_EQ(0.0022, GrassRevetmentWaveRunupDefaults::GetWaveAngleImpactAbeta());
    }

    TEST(GrassRevetmentWaveRunupDefaultsTest, GetWaveAngleImpactBetamax_ExpectedValue)
    {
        // Call& Assert
        ASSERT_DOUBLE_EQ(80, GrassRevetmentWaveRunupDefaults::GetWaveAngleImpactBetamax());
    }
}
