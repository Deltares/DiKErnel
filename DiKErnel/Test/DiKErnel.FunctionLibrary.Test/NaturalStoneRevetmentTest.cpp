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
    const auto initialDamage = 0.0;
    const auto waveAngle = -10;
    const auto slopeAngle = 0.3;
    const auto spectralWaveHeight = 0.5;
    const auto spectralWavePeriod = 2.0;
    const auto relativeDensity = 1.65;
    const auto thicknessTopLayer = 0.3;
    const auto startTime = 0.0;
    const auto endTime = 100;
    const auto ap = 4.0;
    const auto np = -0.9;
    const auto bp = 0.0;
    const auto cp = 0.0;
    const auto as = 0.8;
    const auto ns = 0.6;
    const auto bs = 0.0;
    const auto cs = 0.0;
    const auto waveAngleMaximum = 78.0;
    const auto similarityParameterThreshold = 2.9;

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateDamage_ThenExpectedResult)
    {
        // When
        const auto damage = NaturalStoneRevetment::CalculateDamage(
            initialDamage,
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            startTime,
            endTime,
            ap,
            bp,
            cp,
            np,
            as,
            bs,
            cs,
            ns,
            waveAngleMaximum,
            similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(damage, 0.19527164721720683);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateIncrementDamage_ThenExpectedResult)
    {
        // When
        const auto incrementDamage = NaturalStoneRevetment::CalculateIncrementDamage(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            startTime,
            endTime,
            ap,
            bp,
            cp,
            np,
            as,
            bs,
            cs,
            ns,
            waveAngleMaximum,
            initialDamage,
            similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(incrementDamage, 0.19527164721720683);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateHydraulicLoadWithSurfSimilarityParameterSmallerThanThreshold_ThenExpectedResult)
    {
        // When
        const auto hydraulicLoad = NaturalStoneRevetment::CalculateHydraulicLoad(
            slopeAngle,
            spectralWaveHeight,
            spectralWavePeriod,
            ap,
            bp,
            cp,
            np,
            as,
            bs,
            cs,
            ns,
            similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(hydraulicLoad, 0.13175883584243872);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateHydraulicLoadWithSurfSimilarityParameterBiggerThanThreshold_ThenExpectedResult)
    {
        // When
        const auto hydraulicLoad = NaturalStoneRevetment::CalculateHydraulicLoad(
            slopeAngle,
            spectralWaveHeight,
            spectralWavePeriod,
            ap,
            bp,
            cp,
            np,
            as,
            bs,
            cs,
            ns,
            0.5);

        // Then
        ASSERT_DOUBLE_EQ(hydraulicLoad, 0.60343921078080642);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateSurfSimilarityParameter_ThenExpectedResult)
    {
        // When
        const auto surfSimilarityParameter = NaturalStoneRevetment::CalculateSurfSimilarityParameter(
            slopeAngle,
            spectralWaveHeight,
            spectralWavePeriod);

        // Then
        ASSERT_DOUBLE_EQ(surfSimilarityParameter, 1.0602561926471712);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateResistance_ThenExpectedResult)
    {
        // When
        const auto resistance = NaturalStoneRevetment::CalculateResistance(
            relativeDensity,
            thicknessTopLayer);

        // Then
        ASSERT_DOUBLE_EQ(resistance, 0.49499999999999994);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateIncrementDegradation_ThenExpectedResult)
    {
        // When
        const auto incrementDegradation = NaturalStoneRevetment::CalculateIncrementDegradation(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            startTime,
            endTime,
            ap,
            bp,
            cp,
            np,
            as,
            bs,
            cs,
            ns,
            waveAngleMaximum,
            initialDamage,
            similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(incrementDegradation, 0.7411344491069477);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateDegradation_ThenExpectedResult)
    {
        // When
        const auto degradation = NaturalStoneRevetment::CalculateDegradation(endTime, spectralWavePeriod);

        // Then
        ASSERT_DOUBLE_EQ(degradation, 0.7411344491069477);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateReferenceTimeDegradation_ThenExpectedResult)
    {
        // When
        const auto referenceTimeDegradation = NaturalStoneRevetment::CalculateReferenceTimeDegradation(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            ap,
            bp,
            cp,
            np,
            as,
            bs,
            cs,
            ns,
            waveAngleMaximum,
            initialDamage,
            similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(referenceTimeDegradation, 0.0);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateReferenceDegradation_ThenExpectedResult)
    {
        // When
        const auto referenceDegradation = NaturalStoneRevetment::CalculateReferenceDegradation(
            initialDamage,
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            ap,
            bp,
            cp,
            np,
            as,
            bs,
            cs,
            ns,
            waveAngleMaximum,
            similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(referenceDegradation, 0.0);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateWaveAngleImpactWithPositiveWaveAngle_ThenExpectedResult)
    {
        // When
        const auto waveAngleImpact = NaturalStoneRevetment::CalculateWaveAngleImpact(waveAngle, waveAngleMaximum);

        // Then
        ASSERT_DOUBLE_EQ(waveAngleImpact, 0.98984601570399278);
    }

    TEST(NaturalStoneRevetmentTest, GivenInput_WhenCalculateWaveAngleImpactWithNegativeWaveAngle_ThenExpectedResult)
    {
        // When
        const auto waveAngleImpact = NaturalStoneRevetment::CalculateWaveAngleImpact(-waveAngle, waveAngleMaximum);

        // Then
        ASSERT_DOUBLE_EQ(waveAngleImpact, 0.98984601570399278);
    }
}
