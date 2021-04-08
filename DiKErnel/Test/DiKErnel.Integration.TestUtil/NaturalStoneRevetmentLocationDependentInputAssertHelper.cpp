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

#include "NaturalStoneRevetmentLocationDependentInputAssertHelper.h"

#include <gtest/gtest.h>

namespace DiKErnel::Integration::TestUtil
{
    using namespace std;

    void NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertGeneralProperties(
        const string& name,
        const double tanA,
        const double positionZ,
        const double relativeDensity,
        const double thicknessTopLayer,
        const NaturalStoneRevetmentLocationDependentInput& locationDependentInput)
    {
        ASSERT_EQ(name, locationDependentInput.GetName());
        ASSERT_DOUBLE_EQ(tanA, locationDependentInput.GetTanA());
        ASSERT_DOUBLE_EQ(positionZ, locationDependentInput.GetPositionZ());
        ASSERT_DOUBLE_EQ(relativeDensity, locationDependentInput.GetRelativeDensity());
        ASSERT_DOUBLE_EQ(thicknessTopLayer, locationDependentInput.GetThicknessTopLayer());
    }

    void NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(
        const double hydraulicLoadAp,
        const double hydraulicLoadBp,
        const double hydraulicLoadCp,
        const double hydraulicLoadNp,
        const double hydraulicLoadAs,
        const double hydraulicLoadBs,
        const double hydraulicLoadCs,
        const double hydraulicLoadNs,
        const double hydraulicLoadXib,
        const NaturalStoneRevetmentHydraulicLoads& hydraulicLoads)
    {
        ASSERT_DOUBLE_EQ(hydraulicLoadAp, hydraulicLoads.GetHydraulicLoadAp());
        ASSERT_DOUBLE_EQ(hydraulicLoadBp, hydraulicLoads.GetHydraulicLoadBp());
        ASSERT_DOUBLE_EQ(hydraulicLoadCp, hydraulicLoads.GetHydraulicLoadCp());
        ASSERT_DOUBLE_EQ(hydraulicLoadNp, hydraulicLoads.GetHydraulicLoadNp());
        ASSERT_DOUBLE_EQ(hydraulicLoadAs, hydraulicLoads.GetHydraulicLoadAs());
        ASSERT_DOUBLE_EQ(hydraulicLoadBs, hydraulicLoads.GetHydraulicLoadBs());
        ASSERT_DOUBLE_EQ(hydraulicLoadCs, hydraulicLoads.GetHydraulicLoadCs());
        ASSERT_DOUBLE_EQ(hydraulicLoadNs, hydraulicLoads.GetHydraulicLoadNs());
        ASSERT_DOUBLE_EQ(hydraulicLoadXib, hydraulicLoads.GetHydraulicLoadXib());
    }

    void NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertUpperLimitLoading(
        const double upperLimitLoadingAul,
        const double upperLimitLoadingBul,
        const double upperLimitLoadingCul,
        const NaturalStoneRevetmentUpperLimitLoading& upperLimitLoading)
    {
        ASSERT_DOUBLE_EQ(upperLimitLoadingAul, upperLimitLoading.GetUpperLimitAul());
        ASSERT_DOUBLE_EQ(upperLimitLoadingBul, upperLimitLoading.GetUpperLimitBul());
        ASSERT_DOUBLE_EQ(upperLimitLoadingCul, upperLimitLoading.GetUpperLimitCul());
    }

    void NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertLowerLimitLoading(
        const double lowerLimitLoadingAll,
        const double lowerLimitLoadingBll,
        const double lowerLimitLoadingCll,
        const NaturalStoneRevetmentLowerLimitLoading& lowerLimitLoading)
    {
        ASSERT_DOUBLE_EQ(lowerLimitLoadingAll, lowerLimitLoading.GetLowerLimitAll());
        ASSERT_DOUBLE_EQ(lowerLimitLoadingBll, lowerLimitLoading.GetLowerLimitBll());
        ASSERT_DOUBLE_EQ(lowerLimitLoadingCll, lowerLimitLoading.GetLowerLimitCll());
    }

    void NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertDistanceMaximumWaveElevation(
        const double distanceMaximumWaveElevationAsmax,
        const double distanceMaximumWaveElevationBsmax,
        const NaturalStoneRevetmentDistanceMaximumWaveElevation& distanceMaximumWaveElevation)
    {
        ASSERT_DOUBLE_EQ(distanceMaximumWaveElevationAsmax, distanceMaximumWaveElevation.GetDistanceMaximumWaveElevationAsmax());
        ASSERT_DOUBLE_EQ(distanceMaximumWaveElevationBsmax, distanceMaximumWaveElevation.GetDistanceMaximumWaveElevationBsmax());
    }

    void NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertNormativeWidthOfWaveImpact(
        const double normativeWidthOfWaveImpactAwi,
        const double normativeWidthOfWaveImpactBwi,
        const NaturalStoneRevetmentNormativeWidthOfWaveImpact& normativeWidthOfWaveImpact)
    {
        ASSERT_DOUBLE_EQ(normativeWidthOfWaveImpactAwi, normativeWidthOfWaveImpact.GetNormativeWidthOfWaveImpactAwi());
        ASSERT_DOUBLE_EQ(normativeWidthOfWaveImpactBwi, normativeWidthOfWaveImpact.GetNormativeWidthOfWaveImpactBwi());
    }

    void NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertWaveAngleImpact(
        const double waveAngleImpactBetamax,
        const NaturalStoneRevetmentWaveAngleImpact& waveAngleImpact)
    {
        ASSERT_DOUBLE_EQ(waveAngleImpactBetamax, waveAngleImpact.GetBetamax());
    }
}
