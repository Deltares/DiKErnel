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

#include "NaturalStoneRevetment.h"

namespace DiKErnel::FunctionLibrary::Test::NaturalStoneRevetmentTest
{
    // Given
    const auto initialDamage = 0.1;
    const auto waveAngle = 60.0;
    const auto slopeAngle = 15.0;
    const auto spectralWaveHeight = 1.6;
    const auto spectralWavePeriod = 4.0;
    const auto relativeDensity = 1.65;
    const auto thicknessTopLayer = 0.3;
    const auto startTime = 0.0;
    const auto endTime = 36.0;

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateDamage_ThenExpectedResult)
    {
        // When
        auto damage = NaturalStoneRevetment::CalculateDamage(
            initialDamage,
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            startTime,
            endTime);

        // Then
        ASSERT_EQ(damage, 0.33458768058794086);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateIncrementDamage_ThenExpectedResult)
    {
        // When
        auto incrementDamage = NaturalStoneRevetment::CalculateIncrementDamage(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            startTime,
            endTime);

        // Then
        ASSERT_EQ(incrementDamage, 0.23458768058794083);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateHydraulicLoadWithSurfSimilarityParameterSmallerThanXiFactory_ThenExpectedResult)
    {
        // When
        auto hydraulicLoad = NaturalStoneRevetment::CalculateHydraulicLoad(
            slopeAngle,
            spectralWaveHeight,
            spectralWavePeriod);

        // Then
        ASSERT_EQ(hydraulicLoad, 0.42109231069183717);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateHydraulicLoadWithSurfSimilarityParameterBiggerThanXiFactory_ThenExpectedResult)
    {
        // When
        auto hydraulicLoad = NaturalStoneRevetment::CalculateHydraulicLoad(
            slopeAngle * 4,
            spectralWaveHeight / 4,
            spectralWavePeriod / 4);

        // Then
        ASSERT_EQ(hydraulicLoad, 0.23900384271534394);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateSurfSimilarityParameter_ThenExpectedResult)
    {
        // When
        auto surfSimilarityParameter = NaturalStoneRevetment::CalculateSurfSimilarityParameter(
            slopeAngle,
            spectralWaveHeight,
            spectralWavePeriod);

        // Then
        ASSERT_EQ(surfSimilarityParameter, 1.0587587730209971);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateResistance_ThenExpectedResult)
    {
        // When
        auto resistance = NaturalStoneRevetment::CalculateResistance(
            relativeDensity,
            thicknessTopLayer);

        // Then
        ASSERT_EQ(resistance, 0.49499999999999994);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateIncrementDegradation_ThenExpectedResult)
    {
        // When
        auto incrementDegradation = NaturalStoneRevetment::CalculateIncrementDegradation(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            0.0,
            36.0);

        // Then
        ASSERT_EQ(incrementDegradation, 0.43774354728651044);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateDegradation_ThenExpectedResult)
    {
        // When
        auto degradation = NaturalStoneRevetment::CalculateDegradation(7.0, spectralWavePeriod);

        // Then
        ASSERT_EQ(degradation, 0.53003409246204658);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateReferenceTimeDegradation_ThenExpectedResult)
    {
        // When
        auto referenceTimeDegradation = NaturalStoneRevetment::CalculateReferenceTimeDegradation(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle);

        // Then
        ASSERT_EQ(referenceTimeDegradation, 0.00020474132396956532);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateReferenceDegradation_ThenExpectedResult)
    {
        // When
        auto referenceDegradation = NaturalStoneRevetment::CalculateReferenceDegradation(
            initialDamage,
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle);

        // Then
        ASSERT_EQ(referenceDegradation, 0.18660125126324004);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateWaveAngleImpactWithPositiveWaveAngle_ThenExpectedResult)
    {
        // When
        auto waveAngleImpact = NaturalStoneRevetment::CalculateWaveAngleImpact(waveAngle);

        // Then
        ASSERT_EQ(waveAngleImpact, 0.62996052494743671);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateWaveAngleImpactWithNegativeWaveAngle_ThenExpectedResult)
    {
        // When
        auto waveAngleImpact = NaturalStoneRevetment::CalculateWaveAngleImpact(-waveAngle);

        // Then
        ASSERT_EQ(waveAngleImpact, 0.62996052494743671);
    }
}
