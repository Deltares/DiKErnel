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
#include "GrassRevetmentWaveImpactLocationConstructionProperties.h"

namespace DiKErnel::Integration::Test
{
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    using TopLayerType = GrassRevetmentWaveImpactLocationConstructionProperties::TopLayerType;

    TEST(GrassRevetmentWaveImpactLocationConstructionPropertiesTest, Constructor_ExpectedValues)
    {
        // Setup
        const auto topLayerType = static_cast<TopLayerType>(rand() % 2);
        const string name = "Test";
        const auto tanA = 0.1;
        const auto positionZ = 0.2;

        // Call
        const GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties(
            name, tanA, positionZ, topLayerType);

        // Assert
        AssertHelper::AssertIsInstanceOf<RevetmentLocationConstructionPropertiesBase>(&constructionProperties);
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_EQ(name, constructionProperties.GetName());
        ASSERT_DOUBLE_EQ(tanA, constructionProperties.GetTanA());
        ASSERT_DOUBLE_EQ(positionZ, constructionProperties.GetPositionZ());
        ASSERT_EQ(nullptr, constructionProperties.GetInitialDamage());
        ASSERT_EQ(nullptr, constructionProperties.GetFailureNumber());
        ASSERT_EQ(nullptr, constructionProperties.GetFailureTimeAgwi());
        ASSERT_EQ(nullptr, constructionProperties.GetFailureTimeBgwi());
        ASSERT_EQ(nullptr, constructionProperties.GetFailureTimeCgwi());
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
        const auto topLayerType = static_cast<TopLayerType>(rand() % 2);
        const string name = "Test";
        const auto tanA = 0.1;
        const auto positionZ = 0.2;
        const auto initialDamage = 0.3;
        const auto failureNumber = 0.4;
        const auto failureTimeAgwi = 0.5;
        const auto failureTimeBgwi = 0.6;
        const auto failureTimeCgwi = 0.7;
        const auto minimumWaveHeightTemax = 0.8;
        const auto maximumWaveHeightTemin = 0.9;
        const auto waveAngleImpactNwa = 1.0;
        const auto waveAngleImpactQwa = 1.1;
        const auto waveAngleImpactRwa = 1.2;
        const auto upperLimitLoadingAul = 1.3;
        const auto lowerLimitLoadingAll = 1.4;

        GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties(
            name, tanA, positionZ, topLayerType);

        // When
        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties.SetFailureTimeAgwi(make_unique<double>(failureTimeAgwi));
        constructionProperties.SetFailureTimeBgwi(make_unique<double>(failureTimeBgwi));
        constructionProperties.SetFailureTimeCgwi(make_unique<double>(failureTimeCgwi));
        constructionProperties.SetMinimumWaveHeightTemax(make_unique<double>(minimumWaveHeightTemax));
        constructionProperties.SetMaximumWaveHeightTemin(make_unique<double>(maximumWaveHeightTemin));
        constructionProperties.SetWaveAngleImpactNwa(make_unique<double>(waveAngleImpactNwa));
        constructionProperties.SetWaveAngleImpactQwa(make_unique<double>(waveAngleImpactQwa));
        constructionProperties.SetWaveAngleImpactRwa(make_unique<double>(waveAngleImpactRwa));
        constructionProperties.SetUpperLimitLoadingAul(make_unique<double>(upperLimitLoadingAul));
        constructionProperties.SetLowerLimitLoadingAll(make_unique<double>(lowerLimitLoadingAll));

        // Then
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_EQ(name, constructionProperties.GetName());
        ASSERT_DOUBLE_EQ(tanA, constructionProperties.GetTanA());
        ASSERT_DOUBLE_EQ(positionZ, constructionProperties.GetPositionZ());
        ASSERT_DOUBLE_EQ(initialDamage, *constructionProperties.GetInitialDamage());
        ASSERT_DOUBLE_EQ(failureNumber, *constructionProperties.GetFailureNumber());
        ASSERT_DOUBLE_EQ(failureTimeAgwi, *constructionProperties.GetFailureTimeAgwi());
        ASSERT_DOUBLE_EQ(failureTimeBgwi, *constructionProperties.GetFailureTimeBgwi());
        ASSERT_DOUBLE_EQ(failureTimeCgwi, *constructionProperties.GetFailureTimeCgwi());
        ASSERT_DOUBLE_EQ(minimumWaveHeightTemax, *constructionProperties.GetMinimumWaveHeightTemax());
        ASSERT_DOUBLE_EQ(maximumWaveHeightTemin, *constructionProperties.GetMaximumWaveHeightTemin());
        ASSERT_DOUBLE_EQ(waveAngleImpactNwa, *constructionProperties.GetWaveAngleImpactNwa());
        ASSERT_DOUBLE_EQ(waveAngleImpactQwa, *constructionProperties.GetWaveAngleImpactQwa());
        ASSERT_DOUBLE_EQ(waveAngleImpactRwa, *constructionProperties.GetWaveAngleImpactRwa());
        ASSERT_DOUBLE_EQ(upperLimitLoadingAul, *constructionProperties.GetUpperLimitLoadingAul());
        ASSERT_DOUBLE_EQ(lowerLimitLoadingAll, *constructionProperties.GetLowerLimitLoadingAll());
    }
}
