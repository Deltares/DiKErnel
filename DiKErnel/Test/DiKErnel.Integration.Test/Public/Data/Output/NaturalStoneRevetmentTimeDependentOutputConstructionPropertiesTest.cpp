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
#include "NaturalStoneRevetmentTimeDependentOutputConstructionProperties.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace std;
    using namespace TestUtil;

    TEST(NaturalStoneRevetmentTimeDependentOutputConstructionPropertiesTest, Constructor_ExpectedValues)
    {
        // Call
        const NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties;

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutputConstructionProperties>(&constructionProperties);
        ASSERT_EQ(nullptr, constructionProperties._incrementDamage);
        ASSERT_EQ(nullptr, constructionProperties._outerSlope);
        ASSERT_EQ(nullptr, constructionProperties._slopeUpperLevel);
        ASSERT_EQ(nullptr, constructionProperties._slopeUpperPosition);
        ASSERT_EQ(nullptr, constructionProperties._slopeLowerLevel);
        ASSERT_EQ(nullptr, constructionProperties._slopeLowerPosition);
        ASSERT_EQ(nullptr, constructionProperties._loadingRevetment);
        ASSERT_EQ(nullptr, constructionProperties._surfSimilarityParameter);
        ASSERT_EQ(nullptr, constructionProperties._waveSteepnessDeepWater);
        ASSERT_EQ(nullptr, constructionProperties._upperLimitLoading);
        ASSERT_EQ(nullptr, constructionProperties._lowerLimitLoading);
        ASSERT_EQ(nullptr, constructionProperties._depthMaximumWaveLoad);
        ASSERT_EQ(nullptr, constructionProperties._distanceMaximumWaveElevation);
        ASSERT_EQ(nullptr, constructionProperties._normativeWidthOfWaveImpact);
        ASSERT_EQ(nullptr, constructionProperties._hydraulicLoad);
        ASSERT_EQ(nullptr, constructionProperties._waveAngleImpact);
        ASSERT_EQ(nullptr, constructionProperties._resistance);
        ASSERT_EQ(nullptr, constructionProperties._referenceTimeDegradation);
        ASSERT_EQ(nullptr, constructionProperties._referenceDegradation);
    }

    TEST(NaturalStoneRevetmentTimeDependentOutputConstructionPropertiesTest, Constructor_WithAllValuesSet_ExpectedValues)
    {
        // Given
        constexpr auto incrementDamage = 0.1;
        constexpr auto outerSlope = 0.4;
        constexpr auto slopeUpperLevel = 0.5;
        constexpr auto slopeUpperPosition = 0.6;
        constexpr auto slopeLowerLevel = 0.7;
        constexpr auto slopeLowerPosition = 0.8;
        constexpr auto loadingRevetment = true;
        constexpr auto surfSimilarityParameter = 0.9;
        constexpr auto waveSteepnessDeepWater = 1.0;
        constexpr auto upperLimitLoading = 1.1;
        constexpr auto lowerLimitLoading = 1.2;
        constexpr auto depthMaximumWaveLoad = 1.3;
        constexpr auto distanceMaximumWaveElevation = 1.4;
        constexpr auto normativeWidthOfWaveImpact = 1.5;
        constexpr auto hydraulicLoad = 1.6;
        constexpr auto waveAngleImpact = 1.7;
        constexpr auto resistance = 1.8;
        constexpr auto referenceTimeDegradation = 1.9;
        constexpr auto referenceDegradation = 2.0;

        // When
        NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._outerSlope = make_unique<double>(outerSlope);
        constructionProperties._slopeUpperLevel = make_unique<double>(slopeUpperLevel);
        constructionProperties._slopeUpperPosition = make_unique<double>(slopeUpperPosition);
        constructionProperties._slopeLowerLevel = make_unique<double>(slopeLowerLevel);
        constructionProperties._slopeLowerPosition = make_unique<double>(slopeLowerPosition);
        constructionProperties._loadingRevetment = make_unique<bool>(loadingRevetment);
        constructionProperties._surfSimilarityParameter = make_unique<double>(surfSimilarityParameter);
        constructionProperties._waveSteepnessDeepWater = make_unique<double>(waveSteepnessDeepWater);
        constructionProperties._upperLimitLoading = make_unique<double>(upperLimitLoading);
        constructionProperties._lowerLimitLoading = make_unique<double>(lowerLimitLoading);
        constructionProperties._depthMaximumWaveLoad = make_unique<double>(depthMaximumWaveLoad);
        constructionProperties._distanceMaximumWaveElevation = make_unique<double>(distanceMaximumWaveElevation);
        constructionProperties._normativeWidthOfWaveImpact = make_unique<double>(normativeWidthOfWaveImpact);
        constructionProperties._hydraulicLoad = make_unique<double>(hydraulicLoad);
        constructionProperties._waveAngleImpact = make_unique<double>(waveAngleImpact);
        constructionProperties._resistance = make_unique<double>(resistance);
        constructionProperties._referenceTimeDegradation = make_unique<double>(referenceTimeDegradation);
        constructionProperties._referenceDegradation = make_unique<double>(referenceDegradation);

        // Then
        ASSERT_DOUBLE_EQ(incrementDamage, *constructionProperties._incrementDamage);
        ASSERT_DOUBLE_EQ(outerSlope, *constructionProperties._outerSlope);
        ASSERT_DOUBLE_EQ(slopeUpperLevel, *constructionProperties._slopeUpperLevel);
        ASSERT_DOUBLE_EQ(slopeUpperPosition, *constructionProperties._slopeUpperPosition);
        ASSERT_DOUBLE_EQ(slopeLowerLevel, *constructionProperties._slopeLowerLevel);
        ASSERT_DOUBLE_EQ(slopeLowerPosition, *constructionProperties._slopeLowerPosition);
        ASSERT_EQ(loadingRevetment, *constructionProperties._loadingRevetment);
        ASSERT_DOUBLE_EQ(surfSimilarityParameter, *constructionProperties._surfSimilarityParameter);
        ASSERT_DOUBLE_EQ(waveSteepnessDeepWater, *constructionProperties._waveSteepnessDeepWater);
        ASSERT_DOUBLE_EQ(upperLimitLoading, *constructionProperties._upperLimitLoading);
        ASSERT_DOUBLE_EQ(lowerLimitLoading, *constructionProperties._lowerLimitLoading);
        ASSERT_DOUBLE_EQ(depthMaximumWaveLoad, *constructionProperties._depthMaximumWaveLoad);
        ASSERT_DOUBLE_EQ(distanceMaximumWaveElevation, *constructionProperties._distanceMaximumWaveElevation);
        ASSERT_DOUBLE_EQ(normativeWidthOfWaveImpact, *constructionProperties._normativeWidthOfWaveImpact);
        ASSERT_DOUBLE_EQ(hydraulicLoad, *constructionProperties._hydraulicLoad);
        ASSERT_DOUBLE_EQ(waveAngleImpact, *constructionProperties._waveAngleImpact);
        ASSERT_DOUBLE_EQ(resistance, *constructionProperties._resistance);
        ASSERT_DOUBLE_EQ(referenceTimeDegradation, *constructionProperties._referenceTimeDegradation);
        ASSERT_DOUBLE_EQ(referenceDegradation, *constructionProperties._referenceDegradation);
    }
}
