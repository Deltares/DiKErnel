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

#include "GrassRevetmentWaveRunupLocationDependentInputAssertHelper.h"

#include <gtest/gtest.h>

namespace DiKErnel::Integration::TestUtil
{
    using namespace std;

    void GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
        const string& name,
        const double tanA,
        const double positionZ,
        const GrassRevetmentWaveRunupLocationDependentInput& locationDependentInput)
    {
        ASSERT_EQ(name, locationDependentInput.GetName());
        ASSERT_DOUBLE_EQ(tanA, locationDependentInput.GetTanA());
        ASSERT_DOUBLE_EQ(positionZ, locationDependentInput.GetPositionZ());
    }

    void GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertRepresentative2P(
        const double representative2PAru,
        const double representative2PBru,
        const double representative2PCru,
        const double gammaB,
        const double gammaF,
        const GrassRevetmentWaveRunupRepresentative2P& representative2P)
    {
        ASSERT_DOUBLE_EQ(representative2PAru, representative2P.GetRepresentative2PAru());
        ASSERT_DOUBLE_EQ(representative2PBru, representative2P.GetRepresentative2PBru());
        ASSERT_DOUBLE_EQ(representative2PCru, representative2P.GetRepresentative2PCru());
        ASSERT_DOUBLE_EQ(gammaB, representative2P.GetGammaB());
        ASSERT_DOUBLE_EQ(gammaF, representative2P.GetGammaF());
    }

    void GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertWaveAngleImpact(
        const double abeta,
        const double betamax,
        const GrassRevetmentWaveRunupWaveAngleImpact& waveAngleImpact)
    {
        ASSERT_DOUBLE_EQ(abeta, waveAngleImpact.GetAbeta());
        ASSERT_DOUBLE_EQ(betamax, waveAngleImpact.GetBetamax());
    }

    void GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertCumulativeOverload(
        const double criticalCumulativeOverload,
        const GrassRevetmentWaveRunupLocationDependentInput& locationDependentInput)
    {
        ASSERT_DOUBLE_EQ(criticalCumulativeOverload, locationDependentInput.GetCriticalCumulativeOverload());
    }

    void GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertFrontVelocity(
        const double criticalFrontVelocity,
        const GrassRevetmentWaveRunupLocationDependentInput& locationDependentInput)
    {
        ASSERT_DOUBLE_EQ(criticalFrontVelocity, locationDependentInput.GetCriticalFrontVelocity());
    }

    void GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertTransitionAlpha(
        const double increasedLoadTransitionAlphaM,
        const double reducedStrengthTransitionAlphaS,
        const GrassRevetmentWaveRunupLocationDependentInput& locationDependentInput)
    {
        ASSERT_DOUBLE_EQ(increasedLoadTransitionAlphaM, locationDependentInput.GetIncreasedLoadTransitionAlphaM());
        ASSERT_DOUBLE_EQ(reducedStrengthTransitionAlphaS, locationDependentInput.GetReducedStrengthTransitionAlphaS());
    }

    void GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
        const double averageNumberOfWavesCtm,
        const GrassRevetmentWaveRunupLocationDependentInput& locationDependentInput)
    {
        ASSERT_DOUBLE_EQ(averageNumberOfWavesCtm, locationDependentInput.GetAverageNumberOfWavesCtm());
    }
}
