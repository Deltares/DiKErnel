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
#include "GrassRevetmentWaveImpactLocationConstructionProperties.h"

namespace DiKErnel::Integration::Test
{
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    TEST(GrassRevetmentWaveImpactLocationConstructionPropertiesTest, Constructor_ExpectedValues)
    {
        // Setup
        const auto topLayerType = static_cast<GrassRevetmentTopLayerType>(rand() % 2);
        constexpr auto x = 0.1;

        // Call
        const GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties(x, topLayerType);

        // Assert
        AssertHelper::AssertIsInstanceOf<RevetmentLocationConstructionPropertiesBase>(&constructionProperties);
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_EQ(nullptr, constructionProperties.GetInitialDamage());
        ASSERT_EQ(nullptr, constructionProperties.GetFailureNumber());
        ASSERT_EQ(nullptr, constructionProperties.GetTimeLineAgwi());
        ASSERT_EQ(nullptr, constructionProperties.GetTimeLineBgwi());
        ASSERT_EQ(nullptr, constructionProperties.GetTimeLineCgwi());
        ASSERT_EQ(nullptr, constructionProperties.GetMinimumWaveHeightTemax());
        ASSERT_EQ(nullptr, constructionProperties.GetMaximumWaveHeightTemin());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveAngleImpactNwa());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveAngleImpactQwa());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveAngleImpactRwa());
        ASSERT_EQ(nullptr, constructionProperties.GetUpperLimitLoadingAul());
        ASSERT_EQ(nullptr, constructionProperties.GetLowerLimitLoadingAll());
    }

    TEST(GrassRevetmentWaveImpactLocationConstructionPropertiesTest, GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues)
    {
        // Given
        const auto topLayerType = static_cast<GrassRevetmentTopLayerType>(rand() % 2);
        constexpr auto x = 0.1;
        constexpr auto initialDamage = 0.2;
        constexpr auto failureNumber = 0.3;
        constexpr auto timeLineAgwi = 0.4;
        constexpr auto timeLineBgwi = 0.5;
        constexpr auto timeLineCgwi = 0.6;
        constexpr auto minimumWaveHeightTemax = 0.7;
        constexpr auto maximumWaveHeightTemin = 0.8;
        constexpr auto waveAngleImpactNwa = 0.9;
        constexpr auto waveAngleImpactQwa = 1.0;
        constexpr auto waveAngleImpactRwa = 1.1;
        constexpr auto upperLimitLoadingAul = 1.2;
        constexpr auto lowerLimitLoadingAll = 1.3;

        GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties(x, topLayerType);

        // When
        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties.SetTimeLineAgwi(make_unique<double>(timeLineAgwi));
        constructionProperties.SetTimeLineBgwi(make_unique<double>(timeLineBgwi));
        constructionProperties.SetTimeLineCgwi(make_unique<double>(timeLineCgwi));
        constructionProperties.SetMinimumWaveHeightTemax(make_unique<double>(minimumWaveHeightTemax));
        constructionProperties.SetMaximumWaveHeightTemin(make_unique<double>(maximumWaveHeightTemin));
        constructionProperties.SetWaveAngleImpactNwa(make_unique<double>(waveAngleImpactNwa));
        constructionProperties.SetWaveAngleImpactQwa(make_unique<double>(waveAngleImpactQwa));
        constructionProperties.SetWaveAngleImpactRwa(make_unique<double>(waveAngleImpactRwa));
        constructionProperties.SetUpperLimitLoadingAul(make_unique<double>(upperLimitLoadingAul));
        constructionProperties.SetLowerLimitLoadingAll(make_unique<double>(lowerLimitLoadingAll));

        // Then
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_DOUBLE_EQ(initialDamage, *constructionProperties.GetInitialDamage());
        ASSERT_DOUBLE_EQ(failureNumber, *constructionProperties.GetFailureNumber());
        ASSERT_DOUBLE_EQ(timeLineAgwi, *constructionProperties.GetTimeLineAgwi());
        ASSERT_DOUBLE_EQ(timeLineBgwi, *constructionProperties.GetTimeLineBgwi());
        ASSERT_DOUBLE_EQ(timeLineCgwi, *constructionProperties.GetTimeLineCgwi());
        ASSERT_DOUBLE_EQ(minimumWaveHeightTemax, *constructionProperties.GetMinimumWaveHeightTemax());
        ASSERT_DOUBLE_EQ(maximumWaveHeightTemin, *constructionProperties.GetMaximumWaveHeightTemin());
        ASSERT_DOUBLE_EQ(waveAngleImpactNwa, *constructionProperties.GetWaveAngleImpactNwa());
        ASSERT_DOUBLE_EQ(waveAngleImpactQwa, *constructionProperties.GetWaveAngleImpactQwa());
        ASSERT_DOUBLE_EQ(waveAngleImpactRwa, *constructionProperties.GetWaveAngleImpactRwa());
        ASSERT_DOUBLE_EQ(upperLimitLoadingAul, *constructionProperties.GetUpperLimitLoadingAul());
        ASSERT_DOUBLE_EQ(lowerLimitLoadingAll, *constructionProperties.GetLowerLimitLoadingAll());
    }
}
