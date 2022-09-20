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

#include "GrassRevetmentOvertoppingLocationDependentInputAssertHelper.h"

#include <gtest/gtest.h>

namespace DiKErnel::Integration::TestUtil
{
    using namespace std;

    void GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertGeneralProperties(
        const double x,
        const GrassRevetmentOvertoppingLocationDependentInput& locationDependentInput)
    {
        ASSERT_DOUBLE_EQ(x, locationDependentInput.GetX());
    }

    void GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertCumulativeOverload(
        const double criticalCumulativeOverload,
        const int fixedNumberOfWaves,
        const GrassRevetmentOvertoppingLocationDependentInput& locationDependentInput)
    {
        ASSERT_DOUBLE_EQ(criticalCumulativeOverload, locationDependentInput.GetCriticalCumulativeOverload());
        ASSERT_EQ(fixedNumberOfWaves, locationDependentInput.GetFixedNumberOfWaves());
    }

    void GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertFrontVelocity(
        const double criticalFrontVelocity,
        const double frontVelocityCwo,
        const GrassRevetmentOvertoppingLocationDependentInput& locationDependentInput)
    {
        ASSERT_DOUBLE_EQ(criticalFrontVelocity, locationDependentInput.GetCriticalFrontVelocity());
        ASSERT_DOUBLE_EQ(frontVelocityCwo, locationDependentInput.GetFrontVelocityCwo());
    }

    void GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertTransitionAlpha(
        const double increasedLoadTransitionAlphaM,
        const double reducedStrengthTransitionAlphaS,
        const GrassRevetmentOvertoppingLocationDependentInput& locationDependentInput)
    {
        ASSERT_DOUBLE_EQ(increasedLoadTransitionAlphaM, locationDependentInput.GetIncreasedLoadTransitionAlphaM());
        ASSERT_DOUBLE_EQ(reducedStrengthTransitionAlphaS, locationDependentInput.GetReducedStrengthTransitionAlphaS());
    }

    void GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
        const double averageNumberOfWavesCtm,
        const GrassRevetmentOvertoppingLocationDependentInput& locationDependentInput)
    {
        ASSERT_DOUBLE_EQ(averageNumberOfWavesCtm, locationDependentInput.GetAverageNumberOfWavesCtm());
    }
}
