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
    using namespace testing;

    struct NaturalStoneRevetmentTest : Test
    {
        const double _initialDamage = 0.0;
        const double _waveAngle = -10.0;
        const double _slopeAngle = 0.3;
        const double _spectralWaveHeight = 0.5;
        const double _spectralWavePeriod = 2.0;
        const double _relativeDensity = 1.65;
        const double _thicknessTopLayer = 0.3;
        const double _startTime = 0.0;
        const double _endTime = 100.0;
        const double _plungingCoefficientA = 4.0;
        const double _plungingCoefficientB = 0.0;
        const double _plungingCoefficientC = 0.0;
        const double _plungingCoefficientN = -0.9;
        const double _surgingCoefficientA = 0.8;
        const double _surgingCoefficientB = 0.0;
        const double _surgingCoefficientC = 0.0;
        const double _surgingCoefficientN = 0.6;
        const double _waveAngleMaximum = 78.0;
        const double _similarityParameterThreshold = 2.9;
    };

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateDamage_ThenExpectedResult)
    {
        // When
        const auto damage = NaturalStoneRevetment::CalculateDamage(
            _initialDamage,
            _slopeAngle,
            _relativeDensity,
            _thicknessTopLayer,
            _spectralWaveHeight,
            _spectralWavePeriod,
            _waveAngle,
            _startTime,
            _endTime,
            _plungingCoefficientA,
            _plungingCoefficientB,
            _plungingCoefficientC,
            _plungingCoefficientN,
            _surgingCoefficientA,
            _surgingCoefficientB,
            _surgingCoefficientC,
            _surgingCoefficientN,
            _waveAngleMaximum,
            _similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(0.19527164721720683, damage);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateIncrementDamage_ThenExpectedResult)
    {
        // When
        const auto incrementDamage = NaturalStoneRevetment::CalculateIncrementDamage(
            _slopeAngle,
            _relativeDensity,
            _thicknessTopLayer,
            _spectralWaveHeight,
            _spectralWavePeriod,
            _waveAngle,
            _startTime,
            _endTime,
            _plungingCoefficientA,
            _plungingCoefficientB,
            _plungingCoefficientC,
            _plungingCoefficientN,
            _surgingCoefficientA,
            _surgingCoefficientB,
            _surgingCoefficientC,
            _surgingCoefficientN,
            _waveAngleMaximum,
            _initialDamage,
            _similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(0.19527164721720683, incrementDamage);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateHydraulicLoadWithSurfSimilarityParameterSmallerThanThreshold_ThenExpectedResult)
    {
        // When
        const auto hydraulicLoad = NaturalStoneRevetment::CalculateHydraulicLoad(
            _slopeAngle,
            _spectralWaveHeight,
            _spectralWavePeriod,
            _plungingCoefficientA,
            _plungingCoefficientB,
            _plungingCoefficientC,
            _plungingCoefficientN,
            _surgingCoefficientA,
            _surgingCoefficientB,
            _surgingCoefficientC,
            _surgingCoefficientN,
            _similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(0.13175883584243872, hydraulicLoad);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateHydraulicLoadWithSurfSimilarityParameterBiggerThanThreshold_ThenExpectedResult)
    {
        // When
        const auto hydraulicLoad = NaturalStoneRevetment::CalculateHydraulicLoad(
            _slopeAngle,
            _spectralWaveHeight,
            _spectralWavePeriod,
            _plungingCoefficientA,
            _plungingCoefficientB,
            _plungingCoefficientC,
            _plungingCoefficientN,
            _surgingCoefficientA,
            _surgingCoefficientB,
            _surgingCoefficientC,
            _surgingCoefficientN,
            0.5);

        // Then
        ASSERT_DOUBLE_EQ(0.60343921078080642, hydraulicLoad);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateSurfSimilarityParameter_ThenExpectedResult)
    {
        // When
        const auto surfSimilarityParameter = NaturalStoneRevetment::CalculateSurfSimilarityParameter(
            _slopeAngle,
            _spectralWaveHeight,
            _spectralWavePeriod);

        // Then
        ASSERT_DOUBLE_EQ(1.0602561926471712, surfSimilarityParameter);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateResistance_ThenExpectedResult)
    {
        // When
        const auto resistance = NaturalStoneRevetment::CalculateResistance(
            _relativeDensity,
            _thicknessTopLayer);

        // Then
        ASSERT_DOUBLE_EQ(0.49499999999999994, resistance);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateIncrementDegradation_ThenExpectedResult)
    {
        // When
        const auto incrementDegradation = NaturalStoneRevetment::CalculateIncrementDegradation(
            _slopeAngle,
            _relativeDensity,
            _thicknessTopLayer,
            _spectralWaveHeight,
            _spectralWavePeriod,
            _waveAngle,
            _startTime,
            _endTime,
            _plungingCoefficientA,
            _plungingCoefficientB,
            _plungingCoefficientC,
            _plungingCoefficientN,
            _surgingCoefficientA,
            _surgingCoefficientB,
            _surgingCoefficientC,
            _surgingCoefficientN,
            _waveAngleMaximum,
            _initialDamage,
            _similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(0.7411344491069477, incrementDegradation);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateDegradation_ThenExpectedResult)
    {
        // When
        const auto degradation = NaturalStoneRevetment::CalculateDegradation(_endTime, _spectralWavePeriod);

        // Then
        ASSERT_DOUBLE_EQ(0.7411344491069477, degradation);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateReferenceTimeDegradation_ThenExpectedResult)
    {
        // When
        const auto referenceTimeDegradation = NaturalStoneRevetment::CalculateReferenceTimeDegradation(
            _slopeAngle,
            _relativeDensity,
            _thicknessTopLayer,
            _spectralWaveHeight,
            _spectralWavePeriod,
            _waveAngle,
            _plungingCoefficientA,
            _plungingCoefficientB,
            _plungingCoefficientC,
            _plungingCoefficientN,
            _surgingCoefficientA,
            _surgingCoefficientB,
            _surgingCoefficientC,
            _surgingCoefficientN,
            _waveAngleMaximum,
            _initialDamage,
            _similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(0.0, referenceTimeDegradation);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateReferenceDegradation_ThenExpectedResult)
    {
        // When
        const auto referenceDegradation = NaturalStoneRevetment::CalculateReferenceDegradation(
            _initialDamage,
            _slopeAngle,
            _relativeDensity,
            _thicknessTopLayer,
            _spectralWaveHeight,
            _spectralWavePeriod,
            _waveAngle,
            _plungingCoefficientA,
            _plungingCoefficientB,
            _plungingCoefficientC,
            _plungingCoefficientN,
            _surgingCoefficientA,
            _surgingCoefficientB,
            _surgingCoefficientC,
            _surgingCoefficientN,
            _waveAngleMaximum,
            _similarityParameterThreshold);

        // Then
        ASSERT_DOUBLE_EQ(0.0, referenceDegradation);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateWaveAngleImpactWithPositiveWaveAngle_ThenExpectedResult)
    {
        // When
        const auto waveAngleImpact = NaturalStoneRevetment::CalculateWaveAngleImpact(_waveAngle, _waveAngleMaximum);

        // Then
        ASSERT_DOUBLE_EQ(0.98984601570399278, waveAngleImpact);
    }

    TEST_F(NaturalStoneRevetmentTest, GivenInput_WhenCalculateWaveAngleImpactWithNegativeWaveAngle_ThenExpectedResult)
    {
        // When
        const auto waveAngleImpact = NaturalStoneRevetment::CalculateWaveAngleImpact(-_waveAngle, _waveAngleMaximum);

        // Then
        ASSERT_DOUBLE_EQ(0.98984601570399278, waveAngleImpact);
    }
}
