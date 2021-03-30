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

namespace DiKErnel::FunctionLibrary::Test
{
    TEST(NaturalStoneRevetmentTest, IncrementDamage_ValidInput_ExpectedValue)
    {
        // Setup
        const auto hydraulicLoad = 0.56;
        const auto resistance = 0.495;
        const auto incrementDegradation = 0.078;
        const auto waveAngleImpact = 0.997;

        // Call
        const auto incrementDamage = NaturalStoneRevetment::IncrementDamage(hydraulicLoad, resistance, incrementDegradation, waveAngleImpact);

        // Assert
        ASSERT_DOUBLE_EQ(0.087977696969696983, incrementDamage);
    }

    TEST(NaturalStoneRevetmentTest, HydraulicLoad_ValidInput_ExpectedValue)
    {
        // Setup
        const auto surfSimilarityParameter = 1.28;
        const auto waveHeightHm0 = 1.8;
        const auto hydraulicLoadA = 4.0;
        const auto hydraulicLoadB = 0.1;
        const auto hydraulicLoadC = 0.3;
        const auto hydraulicLoadN = -0.9;

        // Call
        const auto hydraulicLoad = NaturalStoneRevetment::HydraulicLoad(surfSimilarityParameter, waveHeightHm0, hydraulicLoadA, hydraulicLoadB,
                                                                        hydraulicLoadC, hydraulicLoadN);

        // Assert
        ASSERT_DOUBLE_EQ(0.49571702636245252, hydraulicLoad);
    }

    TEST(NaturalStoneRevetmentTest, UpperLimitLoading_ValidInput_ExpectedValue)
    {
        // Setup
        const auto depthMaximumWaveLoad = 0.38;
        const auto surfSimilarityParameter = 1.28;
        const auto waterLevel = 1.77;
        const auto waveHeightHm0 = 1.8;
        const auto upperLimitLoadingAul = 0.1;
        const auto upperLimitLoadingBul = 0.6;
        const auto upperLimitLoadingCul = 4.0;

        // Call
        const auto upperLimitLoading = NaturalStoneRevetment::UpperLimitLoading(depthMaximumWaveLoad, surfSimilarityParameter, waterLevel,
                                                                                waveHeightHm0, upperLimitLoadingAul, upperLimitLoadingBul,
                                                                                upperLimitLoadingCul);

        // Assert
        ASSERT_DOUBLE_EQ(2.3924, upperLimitLoading);
    }

    TEST(NaturalStoneRevetmentTest, LowerLimitLoading_ValidInput_ExpectedValue)
    {
        // Setup
        const auto depthMaximumWaveLoad = 0.38;
        const auto surfSimilarityParameter = 1.28;
        const auto waterLevel = 1.77;
        const auto waveHeightHm0 = 1.8;
        const auto lowerLimitLoadingAll = 0.1;
        const auto lowerLimitLoadingBll = 0.2;
        const auto lowerLimitLoadingCll = 4.0;

        // Call
        const auto lowerLimitLoading = NaturalStoneRevetment::LowerLimitLoading(depthMaximumWaveLoad, surfSimilarityParameter, waterLevel,
                                                                                waveHeightHm0, lowerLimitLoadingAll, lowerLimitLoadingBll,
                                                                                lowerLimitLoadingCll);

        // Assert
        ASSERT_DOUBLE_EQ(1.29, lowerLimitLoading);
    }

    TEST(NaturalStoneRevetmentTest, DepthMaximumWaveLoad_ValidInput_ExpectedValue)
    {
        // Setup
        const auto distanceMaximumWaveElevation = 2.25;
        const auto normativeWidthWaveImpact = 1.47;
        const auto slopeAngle = 0.245;

        // Call
        const auto depthMaximumWaveLoad = NaturalStoneRevetment::DepthMaximumWaveLoad(distanceMaximumWaveElevation, normativeWidthWaveImpact,
                                                                                      slopeAngle);

        // Assert
        ASSERT_DOUBLE_EQ(0.3842721100148393, depthMaximumWaveLoad);
    }

    TEST(NaturalStoneRevetmentTest, DistanceMaximumWaveElevation_ValidInput_ExpectedValue)
    {
        // Setup
        const auto impactShallowWater = 1.1;
        const auto waveSteepnessDeepWater = 0.038;
        const auto waveHeightHm0 = 1.8;
        const auto distanceMaximumWaveElevationAsmax = 0.42;
        const auto distanceMaximumWaveElevationBsmax = 0.9;

        // Call
        const auto distanceMaximumWaveElevation = NaturalStoneRevetment::DistanceMaximumWaveElevation(
            impactShallowWater, waveSteepnessDeepWater, waveHeightHm0, distanceMaximumWaveElevationAsmax, distanceMaximumWaveElevationBsmax);

        // Assert
        ASSERT_DOUBLE_EQ(2.4840179879700712, distanceMaximumWaveElevation);
    }

    TEST(NaturalStoneRevetmentTest, ImpactShallowWater_Always_ExpectedValue)
    {
        // Call
        const auto impactShallowWater = NaturalStoneRevetment::ImpactShallowWater();

        // Assert
        ASSERT_DOUBLE_EQ(1.0, impactShallowWater);
    }

    TEST(NaturalStoneRevetmentTest, NormativeWidthWaveImpact_ValidInput_ExpectedValue)
    {
        // Setup
        const auto surfSimilarityParameter = 1.28;
        const auto waveHeightHm0 = 1.8;
        const auto normativeWidthWaveImpactAwi = 0.96;
        const auto normativeWidthWaveImpactBwi = 0.11;

        // Call
        const auto normativeWidthWaveImpact = NaturalStoneRevetment::NormativeWidthWaveImpact(
            surfSimilarityParameter, waveHeightHm0, normativeWidthWaveImpactAwi, normativeWidthWaveImpactBwi);

        // Assert
        ASSERT_DOUBLE_EQ(1.47456, normativeWidthWaveImpact);
    }

    TEST(NaturalStoneRevetmentTest, WaveAngleImpact_ValidInput_ExpectedValue)
    {
        // Setup
        const auto waveAngle = 5.0;
        const auto waveAngleImpactBetamax = 78.0;

        // Call
        const auto waveAngleImpact = NaturalStoneRevetment::WaveAngleImpact(waveAngle, waveAngleImpactBetamax);

        // Assert
        ASSERT_DOUBLE_EQ(0.99746152040928704, waveAngleImpact);
    }

    TEST(NaturalStoneRevetmentTest, Resistance_ValidInput_ExpectedValue)
    {
        // Setup
        const auto relativeDensity = 1.65;
        const auto thicknessTopLayer = 0.3;

        // Call
        const auto resistance = NaturalStoneRevetment::Resistance(relativeDensity, thicknessTopLayer);

        // Assert
        ASSERT_DOUBLE_EQ(0.495, resistance);
    }

    TEST(NaturalStoneRevetmentTest, IncrementDegradation_ValidInput_ExpectedValue)
    {
        // Setup
        const auto referenceTimeDegradation = 579.743;
        const auto incrementTime = 900;
        const auto wavePeriodTm10 = 5.5;

        // Call
        const auto incrementDegradation = NaturalStoneRevetment::IncrementDegradation(referenceTimeDegradation, incrementTime, wavePeriodTm10);

        // Assert
        ASSERT_DOUBLE_EQ(0.078442472004777053, incrementDegradation);
    }

    TEST(NaturalStoneRevetmentTest, Degradation_ValidInput_ExpectedValue)
    {
        // Setup
        const auto referenceTimeDegradation = 579.743;
        const auto wavePeriodTm10 = 5.5;

        // Call
        const auto degradation = NaturalStoneRevetment::Degradation(referenceTimeDegradation, wavePeriodTm10);

        // Assert
        ASSERT_DOUBLE_EQ(0.79852272914233136, degradation);
    }

    TEST(NaturalStoneRevetmentTest, ReferenceTimeDegradation_ValidInput_ExpectedValue)
    {
        // Setup
        const auto referenceDegradation = 0.802;
        const auto wavePeriodTm10 = 5.5;

        // Call
        const auto referenceTimeDegradation = NaturalStoneRevetment::ReferenceTimeDegradation(referenceDegradation, wavePeriodTm10);

        // Assert
        ASSERT_DOUBLE_EQ(605.48915987364103, referenceTimeDegradation);
    }

    TEST(NaturalStoneRevetmentTest, ReferenceDegradation_ValidInput_ExpectedValue)
    {
        // Setup
        const auto resistance = 0.495;
        const auto hydraulicLoad = 0.56;
        const auto waveAngleImpact = 0.997;
        const auto initialDamage = 0.905;

        // Call
        const auto referenceDegradation = NaturalStoneRevetment::ReferenceDegradation(resistance, hydraulicLoad, waveAngleImpact, initialDamage);

        // Assert
        ASSERT_DOUBLE_EQ(0.80236244447628591, referenceDegradation);
    }

    TEST(NaturalStoneRevetmentTest, DurationInTimeStepFailure_ValidInput_ExpectedValue)
    {
        // Setup
        const auto referenceTimeFailure = 945.943;
        const auto referenceTimeDegradation = 597.743;

        // Call
        const auto durationInTimeStepFailure = NaturalStoneRevetment::DurationInTimeStepFailure(referenceTimeFailure, referenceTimeDegradation);

        // Assert
        ASSERT_DOUBLE_EQ(348.2, durationInTimeStepFailure);
    }

    TEST(NaturalStoneRevetmentTest, ReferenceTimeFailure_ValidInput_ExpectedValue)
    {
        // Setup
        const auto referenceFailure = 0.84;
        const auto wavePeriodTm10 = 5.5;

        // Call
        const auto referenceTimeFailure = NaturalStoneRevetment::ReferenceTimeFailure(referenceFailure, wavePeriodTm10);

        // Assert
        ASSERT_DOUBLE_EQ(961.95675821289467, referenceTimeFailure);
    }

    TEST(NaturalStoneRevetmentTest, ReferenceFailure_ValidInput_ExpectedValue)
    {
        // Setup
        const auto resistance = 0.495;
        const auto hydraulicLoad = 0.56;
        const auto waveAngleImpact = 0.997;
        const auto failureNumber = 0.95;

        // Call
        const auto referenceFailure = NaturalStoneRevetment::ReferenceFailure(resistance, hydraulicLoad, waveAngleImpact, failureNumber);

        // Assert
        ASSERT_DOUBLE_EQ(0.84225891961599064, referenceFailure);
    }
}
