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
    struct NaturalStoneRevetmentTest : testing::Test
    {
        const double initialDamage = 0.0;
        const double waveAngle = -10.0;
        const double slopeAngle = 0.3;
        const double spectralWaveHeight = 0.5;
        const double spectralWavePeriod = 2.0;
        const double relativeDensity = 1.65;
        const double thicknessTopLayer = 0.3;
        const double startTime = 0.0;
        const double endTime = 100.0;
        const double plungingCoefficientA = 4.0;
        const double plungingCoefficientB = 0.0;
        const double plungingCoefficientC = 0.0;
        const double plungingCoefficientN = -0.9;
        const double surgingCoefficientA = 0.8;
        const double surgingCoefficientB = 0.0;
        const double surgingCoefficientC = 0.0;
        const double surgingCoefficientN = 0.6;
        const double waveAngleMaximum = 78.0;
        const double similarityParameterThreshold = 2.9;
    };

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateDamage_ThenExpectedResult)
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
            plungingCoefficientA,
            plungingCoefficientB,
            plungingCoefficientC,
            plungingCoefficientN,
            surgingCoefficientA,
            surgingCoefficientB,
            surgingCoefficientC,
            surgingCoefficientN,
            waveAngleMaximum,
            similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(0.19527164721720683, damage);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateIncrementDamage_ThenExpectedResult)
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
            plungingCoefficientA,
            plungingCoefficientB,
            plungingCoefficientC,
            plungingCoefficientN,
            surgingCoefficientA,
            surgingCoefficientB,
            surgingCoefficientC,
            surgingCoefficientN,
            waveAngleMaximum,
            initialDamage,
            similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(0.19527164721720683, incrementDamage);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateHydraulicLoadWithSurfSimilarityParameterSmallerThanThreshold_ThenExpectedResult)
    {
        // When
        const auto hydraulicLoad = NaturalStoneRevetment::CalculateHydraulicLoad(
            slopeAngle,
            spectralWaveHeight,
            spectralWavePeriod,
            plungingCoefficientA,
            plungingCoefficientB,
            plungingCoefficientC,
            plungingCoefficientN,
            surgingCoefficientA,
            surgingCoefficientB,
            surgingCoefficientC,
            surgingCoefficientN,
            similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(0.13175883584243872, hydraulicLoad);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateHydraulicLoadWithSurfSimilarityParameterBiggerThanThreshold_ThenExpectedResult)
    {
        // When
        const auto hydraulicLoad = NaturalStoneRevetment::CalculateHydraulicLoad(
            slopeAngle,
            spectralWaveHeight,
            spectralWavePeriod,
            plungingCoefficientA,
            plungingCoefficientB,
            plungingCoefficientC,
            plungingCoefficientN,
            surgingCoefficientA,
            surgingCoefficientB,
            surgingCoefficientC,
            surgingCoefficientN,
            0.5);

        // Then
        ASSERT_DOUBLE_EQ(0.60343921078080642, hydraulicLoad);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateSurfSimilarityParameter_ThenExpectedResult)
    {
        // When
        const auto surfSimilarityParameter = NaturalStoneRevetment::CalculateSurfSimilarityParameter(
            slopeAngle,
            spectralWaveHeight,
            spectralWavePeriod);

        // Then
        ASSERT_DOUBLE_EQ(1.0602561926471712, surfSimilarityParameter);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateResistance_ThenExpectedResult)
    {
        // When
        const auto resistance = NaturalStoneRevetment::CalculateResistance(
            relativeDensity,
            thicknessTopLayer);

        // Then
        ASSERT_DOUBLE_EQ(0.49499999999999994, resistance);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateIncrementDegradation_ThenExpectedResult)
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
            plungingCoefficientA,
            plungingCoefficientB,
            plungingCoefficientC,
            plungingCoefficientN,
            surgingCoefficientA,
            surgingCoefficientB,
            surgingCoefficientC,
            surgingCoefficientN,
            waveAngleMaximum,
            initialDamage,
            similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(0.7411344491069477, incrementDegradation);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateDegradation_ThenExpectedResult)
    {
        // When
        const auto degradation = NaturalStoneRevetment::CalculateDegradation(endTime, spectralWavePeriod);

        // Then
        ASSERT_DOUBLE_EQ(0.7411344491069477, degradation);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateReferenceTimeDegradation_ThenExpectedResult)
    {
        // When
        const auto referenceTimeDegradation = NaturalStoneRevetment::CalculateReferenceTimeDegradation(
            slopeAngle,
            relativeDensity,
            thicknessTopLayer,
            spectralWaveHeight,
            spectralWavePeriod,
            waveAngle,
            plungingCoefficientA,
            plungingCoefficientB,
            plungingCoefficientC,
            plungingCoefficientN,
            surgingCoefficientA,
            surgingCoefficientB,
            surgingCoefficientC,
            surgingCoefficientN,
            waveAngleMaximum,
            initialDamage,
            similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(0.0, referenceTimeDegradation);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateReferenceDegradation_ThenExpectedResult)
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
            plungingCoefficientA,
            plungingCoefficientB,
            plungingCoefficientC,
            plungingCoefficientN,
            surgingCoefficientA,
            surgingCoefficientB,
            surgingCoefficientC,
            surgingCoefficientN,
            waveAngleMaximum,
            similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(0.0, referenceDegradation);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateWaveAngleImpactWithPositiveWaveAngle_ThenExpectedResult)
    {
        // When
        const auto waveAngleImpact = NaturalStoneRevetment::CalculateWaveAngleImpact(waveAngle, waveAngleMaximum);

        // Then
        ASSERT_DOUBLE_EQ(0.98984601570399278, waveAngleImpact);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateWaveAngleImpactWithNegativeWaveAngle_ThenExpectedResult)
    {
        // When
        const auto waveAngleImpact = NaturalStoneRevetment::CalculateWaveAngleImpact(-waveAngle, waveAngleMaximum);

        // Then
        ASSERT_DOUBLE_EQ(0.98984601570399278, waveAngleImpact);
    }
}
