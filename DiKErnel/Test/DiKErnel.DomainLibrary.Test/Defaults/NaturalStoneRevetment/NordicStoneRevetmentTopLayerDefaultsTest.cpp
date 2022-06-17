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

#include "AssertHelper.h"
#include "NordicStoneRevetmentTopLayerDefaults.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace TestUtil;

    TEST(NordicStoneRevetmentDefaultsTest, Constructor_ExpectedValues)
    {
        // Call
        const NordicStoneRevetmentTopLayerDefaults defaults;

        // Assert
        AssertHelper::AssertIsInstanceOf<INaturalStoneRevetmentTopLayerDefaults>(&defaults);
        ASSERT_DOUBLE_EQ(2.9, defaults.GetHydraulicLoadXib());
        ASSERT_DOUBLE_EQ(4, defaults.GetHydraulicLoadAp());
        ASSERT_DOUBLE_EQ(0, defaults.GetHydraulicLoadBp());
        ASSERT_DOUBLE_EQ(0, defaults.GetHydraulicLoadCp());
        ASSERT_DOUBLE_EQ(-0.9, defaults.GetHydraulicLoadNp());
        ASSERT_DOUBLE_EQ(0.8, defaults.GetHydraulicLoadAs());
        ASSERT_DOUBLE_EQ(0, defaults.GetHydraulicLoadBs());
        ASSERT_DOUBLE_EQ(0, defaults.GetHydraulicLoadCs());
        ASSERT_DOUBLE_EQ(0.6, defaults.GetHydraulicLoadNs());
        ASSERT_DOUBLE_EQ(0.05, defaults.GetSlopeUpperLevelAus());
        ASSERT_DOUBLE_EQ(1.5, defaults.GetSlopeLowerLevelAls());
        ASSERT_DOUBLE_EQ(0.1, defaults.GetUpperLimitLoadingAul());
        ASSERT_DOUBLE_EQ(0.6, defaults.GetUpperLimitLoadingBul());
        ASSERT_DOUBLE_EQ(4, defaults.GetUpperLimitLoadingCul());
        ASSERT_DOUBLE_EQ(0.1, defaults.GetLowerLimitLoadingAll());
        ASSERT_DOUBLE_EQ(0.2, defaults.GetLowerLimitLoadingBll());
        ASSERT_DOUBLE_EQ(4, defaults.GetLowerLimitLoadingCll());
        ASSERT_DOUBLE_EQ(0.42, defaults.GetDistanceMaximumWaveElevationAsmax());
        ASSERT_DOUBLE_EQ(0.9, defaults.GetDistanceMaximumWaveElevationBsmax());
        ASSERT_DOUBLE_EQ(0.96, defaults.GetNormativeWidthOfWaveImpactAwi());
        ASSERT_DOUBLE_EQ(0.11, defaults.GetNormativeWidthOfWaveImpactBwi());
        ASSERT_DOUBLE_EQ(78, defaults.GetWaveAngleImpactBetamax());
    }
}
