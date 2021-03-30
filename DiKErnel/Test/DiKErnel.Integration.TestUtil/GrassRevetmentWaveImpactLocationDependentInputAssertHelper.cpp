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

#include "GrassRevetmentWaveImpactLocationDependentInputAssertHelper.h"

#include <gtest/gtest.h>

namespace DiKErnel::Integration::TestUtil
{
    using namespace std;

    void GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMandatoryProperties(
        const string& name,
        const double tanA,
        const double positionZ,
        const GrassRevetmentWaveImpactLocationDependentInput& locationDependentInput)
    {
        ASSERT_EQ(name, locationDependentInput.GetName());
        ASSERT_DOUBLE_EQ(tanA, locationDependentInput.GetTanA());
        ASSERT_DOUBLE_EQ(positionZ, locationDependentInput.GetPositionZ());
    }

    void GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
        const double minimumWaveHeightTemax,
        const GrassRevetmentWaveImpactLocationDependentInput& locationDependentInput)
    {
        ASSERT_DOUBLE_EQ(minimumWaveHeightTemax, locationDependentInput.GetMinimumWaveHeightTemax());
    }

    void GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
        const double maximumWaveHeightTemin,
        const GrassRevetmentWaveImpactLocationDependentInput& locationDependentInput)
    {
        ASSERT_DOUBLE_EQ(maximumWaveHeightTemin, locationDependentInput.GetMaximumWaveHeightTemin());
    }

    void GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
        const double waveAngleImpactNwa,
        const double waveAngleImpactQwa,
        const double waveAngleImpactRwa,
        const GrassRevetmentWaveImpactWaveAngleImpact& waveAngleImpact)
    {
        ASSERT_DOUBLE_EQ(waveAngleImpactNwa, waveAngleImpact.GetWaveAngleImpactNwa());
        ASSERT_DOUBLE_EQ(waveAngleImpactQwa, waveAngleImpact.GetWaveAngleImpactQwa());
        ASSERT_DOUBLE_EQ(waveAngleImpactRwa, waveAngleImpact.GetWaveAngleImpactRwa());
    }

    void GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFailureTime(
        const double waveAngleImpactAgwi,
        const double waveAngleImpactBgwi,
        const double waveAngleImpactCgwi,
        const GrassRevetmentWaveImpactFailureTime& failureTime)
    {
        ASSERT_DOUBLE_EQ(waveAngleImpactAgwi, failureTime.GetWaveAngleImpactAgwi());
        ASSERT_DOUBLE_EQ(waveAngleImpactBgwi, failureTime.GetWaveAngleImpactBgwi());
        ASSERT_DOUBLE_EQ(waveAngleImpactCgwi, failureTime.GetWaveAngleImpactCgwi());
    }

    void GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
        const double upperLimitLoadingAul,
        const GrassRevetmentWaveImpactLocationDependentInput& locationDependentInput)
    {
        ASSERT_DOUBLE_EQ(upperLimitLoadingAul, locationDependentInput.GetUpperLimitLoadingAul());
    }

    void GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
        const double lowerLimitLoadingAll,
        const GrassRevetmentWaveImpactLocationDependentInput& locationDependentInput)
    {
        ASSERT_DOUBLE_EQ(lowerLimitLoadingAll, locationDependentInput.GetLowerLimitLoadingAll());
    }
}
