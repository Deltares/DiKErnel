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
        const auto hydraulicLoad = 1.1;
        const auto resistance = 1.1;
        const auto incrementDegradation = 1.1;
        const auto waveAngleImpact = 1.1;

        // Call
        const auto incrementDamage = NaturalStoneRevetment::IncrementDamage(hydraulicLoad, resistance, incrementDegradation, waveAngleImpact);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, incrementDamage);
    }

    TEST(NaturalStoneRevetmentTest, HydraulicLoad_ValidInput_ExpectedValue)
    {
        // Setup
        const auto surfSimilarityParameter = 1.1;
        const auto waveHeightHm0 = 1.1;
        const auto hydraulicLoadOnXib = 1.1;
        const auto hydraulicLoadOnAp = 1.1;
        const auto hydraulicLoadOnBp = 1.1;
        const auto hydraulicLoadOnCp = 1.1;
        const auto hydraulicLoadOnNp = 1.1;
        const auto hydraulicLoadOnAs = 1.1;
        const auto hydraulicLoadOnBs = 1.1;
        const auto hydraulicLoadOnCs = 1.1;
        const auto hydraulicLoadOnNs = 1.1;

        // Call
        const auto hydraulicLoad = NaturalStoneRevetment::HydraulicLoad(surfSimilarityParameter, waveHeightHm0, hydraulicLoadOnXib,
                                                                        hydraulicLoadOnAp, hydraulicLoadOnBp, hydraulicLoadOnCp, hydraulicLoadOnNp,
                                                                        hydraulicLoadOnAs, hydraulicLoadOnBs, hydraulicLoadOnCs,
                                                                        hydraulicLoadOnNs);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, hydraulicLoad);
    }

    TEST(NaturalStoneRevetmentTest, UpperLimitLoading_ValidInput_ExpectedValue)
    {
        // Setup
        const auto depthMaximumWaveLoad = 1.1;
        const auto surfSimilarityParameter = 1.1;
        const auto waterLevel = 1.1;
        const auto waveHeightHm0 = 1.1;
        const auto upperLimitLoadingOfAul = 1.1;
        const auto upperLimitLoadingOfBul = 1.1;
        const auto upperLimitLoadingOfCul = 1.1;

        // Call
        const auto upperLimitLoading = NaturalStoneRevetment::UpperLimitLoading(depthMaximumWaveLoad, surfSimilarityParameter, waterLevel,
                                                                                waveHeightHm0, upperLimitLoadingOfAul, upperLimitLoadingOfBul,
                                                                                upperLimitLoadingOfCul);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, upperLimitLoading);
    }

    TEST(NaturalStoneRevetmentTest, LowerLimitLoading_ValidInput_ExpectedValue)
    {
        // Setup
        const auto depthMaximumWaveLoad = 1.1;
        const auto surfSimilarityParameter = 1.1;
        const auto waterLevel = 1.1;
        const auto waveHeightHm0 = 1.1;
        const auto lowerLimitLoadingOfAll = 1.1;
        const auto lowerLimitLoadingOfBll = 1.1;
        const auto lowerLimitLoadingOfCll = 1.1;

        // Call
        const auto lowerLimitLoading = NaturalStoneRevetment::LowerLimitLoading(depthMaximumWaveLoad, surfSimilarityParameter, waterLevel,
                                                                                waveHeightHm0, lowerLimitLoadingOfAll, lowerLimitLoadingOfBll,
                                                                                lowerLimitLoadingOfCll);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, lowerLimitLoading);
    }

    TEST(NaturalStoneRevetmentTest, DepthMaximumWaveLoad_ValidInput_ExpectedValue)
    {
        // Setup
        const auto distanceMaximumWaveElevation = 1.1;
        const auto normativeWidthOfWaveImpact = 1.1;
        const auto slopeAngle = 1.1;

        // Call
        const auto depthMaximumWaveLoad = NaturalStoneRevetment::DepthMaximumWaveLoad(distanceMaximumWaveElevation, normativeWidthOfWaveImpact,
                                                                                      slopeAngle);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, depthMaximumWaveLoad);
    }

    TEST(NaturalStoneRevetmentTest, DistanceMaximumWaveElevation_ValidInput_ExpectedValue)
    {
        // Setup
        const auto impactShallowWater = 1.1;
        const auto waveSteepnessDeepWater = 1.1;
        const auto waveHeightHm0 = 1.1;
        const auto distanceMaximumWaveElevationAsmax = 1.1;
        const auto distanceMaximumWaveElevationBsmax = 1.1;

        // Call
        const auto distanceMaximumWaveElevation = NaturalStoneRevetment::DistanceMaximumWaveElevation(
            impactShallowWater, waveSteepnessDeepWater, waveHeightHm0, distanceMaximumWaveElevationAsmax, distanceMaximumWaveElevationBsmax);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, distanceMaximumWaveElevation);
    }

    TEST(NaturalStoneRevetmentTest, ImpactShallowWater_ValidInput_ExpectedValue)
    {
        // Call
        const auto impactShallowWater = NaturalStoneRevetment::ImpactShallowWater();

        // Assert
        ASSERT_DOUBLE_EQ(1.1, impactShallowWater);
    }

    TEST(NaturalStoneRevetmentTest, NormativeWidthOfWaveImpact_ValidInput_ExpectedValue)
    {
        // Setup
        const auto surfSimilarityParameter = 1.1;
        const auto waveHeightHm0 = 1.1;
        const auto normativeWidthOfWaveImpactAwi = 1.1;
        const auto normativeWidthOfWaveImpactBwi = 1.1;

        // Call
        const auto normativeWidthOfWaveImpact = NaturalStoneRevetment::NormativeWidthOfWaveImpact(
            surfSimilarityParameter, waveHeightHm0, normativeWidthOfWaveImpactAwi, normativeWidthOfWaveImpactBwi);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, normativeWidthOfWaveImpact);
    }

    TEST(NaturalStoneRevetmentTest, WaveAngleImpact_ValidInput_ExpectedValue)
    {
        // Setup
        const auto waveAngle = 1.1;
        const auto waveAngleImpactOnBetamax = 1.1;

        // Call
        const auto waveAngleImpact = NaturalStoneRevetment::WaveAngleImpact(waveAngle, waveAngleImpactOnBetamax);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, waveAngleImpact);
    }

    TEST(NaturalStoneRevetmentTest, Resistance_ValidInput_ExpectedValue)
    {
        // Setup
        const auto relativeDensity = 1.1;
        const auto thicknessTopLayer = 1.1;

        // Call
        const auto resistance = NaturalStoneRevetment::Resistance(relativeDensity, thicknessTopLayer);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, resistance);
    }

    TEST(NaturalStoneRevetmentTest, IncrementDegradation_ValidInput_ExpectedValue)
    {
        // Setup
        const auto referenceTimeDegradation = 1.1;
        const auto incrementTime = 1.1;
        const auto wavePeriodTm10 = 1.1;

        // Call
        const auto incrementDegradation = NaturalStoneRevetment::IncrementDegradation(referenceTimeDegradation, incrementTime, wavePeriodTm10);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, incrementDegradation);
    }

    TEST(NaturalStoneRevetmentTest, Degradation_ValidInput_ExpectedValue)
    {
        // Setup
        const auto referenceTimeDegradation = 1.1;
        const auto wavePeriodTm10 = 1.1;

        // Call
        const auto degradation = NaturalStoneRevetment::Degradation(referenceTimeDegradation, wavePeriodTm10);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, degradation);
    }

    TEST(NaturalStoneRevetmentTest, ReferenceTimeDegradation_ValidInput_ExpectedValue)
    {
        // Setup
        const auto referenceDegradation = 1.1;
        const auto wavePeriodTm10 = 1.1;

        // Call
        const auto referenceTimeDegradation = NaturalStoneRevetment::ReferenceTimeDegradation(referenceDegradation, wavePeriodTm10);

        // Assert
        ASSERT_DOUBLE_EQ(1.1, referenceTimeDegradation);
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
