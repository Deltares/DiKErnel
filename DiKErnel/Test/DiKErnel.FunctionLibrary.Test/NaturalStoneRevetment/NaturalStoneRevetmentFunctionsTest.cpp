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
#include "NaturalStoneRevetmentFunctions.h"

namespace DiKErnel::FunctionLibrary::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(NaturalStoneRevetmentFunctionsTest, IncrementDamage_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto hydraulicLoad = 0.56;
        constexpr auto resistance = 0.495;
        constexpr auto incrementDegradation = 0.078;
        constexpr auto waveAngleImpact = 0.997;

        // Call
        const auto incrementDamage = NaturalStoneRevetmentFunctions::IncrementDamage(hydraulicLoad, resistance, incrementDegradation,
                                                                                     waveAngleImpact);

        // Assert
        ASSERT_DOUBLE_EQ(0.087977696969696983, incrementDamage);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, HydraulicLoad_ValidInput_ExpectedValue)
    {
        // Setup
        const NaturalStoneRevetmentHydraulicLoadInput input
        {
            ._surfSimilarityParameter = 1.28,
            ._waveHeightHm0 = 1.8,
            ._a = 4.0,
            ._b = 0.1,
            ._c = 0.3,
            ._n = -0.9
        };

        // Call
        const auto hydraulicLoad = NaturalStoneRevetmentFunctions::HydraulicLoad(input);

        // Assert
        ASSERT_DOUBLE_EQ(0.49571702636245252, hydraulicLoad);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithoutBerm_ValidInput_ExpectedValue)
    {
        // Setup
        const NaturalStoneRevetmentOuterSlopeInput input
        {
            ._slopeLowerPosition = 30.0,
            ._slopeLowerLevel = 5.35,
            ._slopeUpperPosition = 30.3,
            ._slopeUpperLevel = 5.425
        };

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(input);

        // Assert
        ASSERT_DOUBLE_EQ(0.25, outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_UpperAndLowerSlopeLevelOnLowerSlope_ExpectedValue)
    {
        // Setup
        const NaturalStoneRevetmentOuterSlopeInput input
        {
            ._slopeLowerPosition = 5.0,
            ._slopeLowerLevel = 0.5,
            ._slopeUpperPosition = 5.15625,
            ._slopeUpperLevel = 0.55,
            ._outerToeHeight = 0.5,
            ._outerCrestHeight = 7.0,
            ._notchOuterBermPosition = 25.0,
            ._notchOuterBermHeight = 4.1,
            ._crestOuterBermPosition = 15.0,
            ._crestOuterBermHeight = 3.5
        };

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(input);

        // Assert
        AssertHelper::AssertAreEqualWithAcceptablePrecision(0.32, outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_UpperSlopeLevelOnBermAndLowerSlopeLevelOnLowerSlope_ExpectedValue)
    {
        // Setup
        const NaturalStoneRevetmentOuterSlopeInput input
        {
            ._slopeLowerPosition = 10.7142857142857,
            ._slopeLowerLevel = 2.3,
            ._slopeUpperPosition = 15.0,
            ._slopeUpperLevel = 3.5,
            ._outerToeHeight = 0.5,
            ._outerCrestHeight = 7.0,
            ._notchOuterBermPosition = 25.0,
            ._notchOuterBermHeight = 4.1,
            ._crestOuterBermPosition = 15.0,
            ._crestOuterBermHeight = 3.5
        };

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(input);

        // Assert
        AssertHelper::AssertAreEqualWithAcceptablePrecision(0.28, outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_UpperAndLowerSlopeLevelOnBerm_ExpectedValue)
    {
        // Setup
        const NaturalStoneRevetmentOuterSlopeInput input
        {
            ._slopeLowerPosition = 15.0,
            ._slopeLowerLevel = 3.5,
            ._slopeUpperPosition = 18.75,
            ._slopeUpperLevel = 3.8,
            ._outerToeHeight = 0.5,
            ._outerCrestHeight = 7.0,
            ._notchOuterBermPosition = 25.0,
            ._notchOuterBermHeight = 4.1,
            ._crestOuterBermPosition = 15.0,
            ._crestOuterBermHeight = 3.5
        };

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(input);

        // Assert
        AssertHelper::AssertAreEqualWithAcceptablePrecision(0.08, outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_UpperAndLowerSlopeLevelOnUpperSlope_ExpectedValue)
    {
        // Setup
        const NaturalStoneRevetmentOuterSlopeInput input
        {
            ._slopeLowerPosition = 25.6818181818182,
            ._slopeLowerLevel = 4.25,
            ._slopeUpperPosition = 29.0909090909091,
            ._slopeUpperLevel = 5.0,
            ._outerToeHeight = 0.5,
            ._outerCrestHeight = 7.0,
            ._notchOuterBermPosition = 25.0,
            ._notchOuterBermHeight = 4.1,
            ._crestOuterBermPosition = 15.0,
            ._crestOuterBermHeight = 3.5
        };

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(input);

        // Assert
        AssertHelper::AssertAreEqualWithAcceptablePrecision(0.22, outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_UpperSlopeLevelOnUpperSlopeAndLowerSlopeLevelOnBerm_ExpectedValue)
    {
        // Setup
        const NaturalStoneRevetmentOuterSlopeInput input
        {
            ._slopeLowerPosition = 24.375,
            ._slopeLowerLevel = 4.075,
            ._slopeUpperPosition = 40.0,
            ._slopeUpperLevel = 7.0,
            ._outerToeHeight = 0.5,
            ._outerCrestHeight = 7.0,
            ._notchOuterBermPosition = 25.0,
            ._notchOuterBermHeight = 4.1,
            ._crestOuterBermPosition = 15.0,
            ._crestOuterBermHeight = 3.5
        };

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(input);

        // Assert
        AssertHelper::AssertAreEqualWithAcceptablePrecision(0.19333333333333, outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_UpperSlopeLevelOnUpperSlopeAndLowerSlopeLevelOnLowerSlope_ExpectedValue)
    {
        // Setup
        const NaturalStoneRevetmentOuterSlopeInput input
        {
            ._slopeLowerPosition = 12.5,
            ._slopeLowerLevel = 2.8,
            ._slopeUpperPosition = 40.0,
            ._slopeUpperLevel = 7.0,
            ._outerToeHeight = 0.5,
            ._outerCrestHeight = 7.0,
            ._notchOuterBermPosition = 25.0,
            ._notchOuterBermHeight = 4.1,
            ._crestOuterBermPosition = 15.0,
            ._crestOuterBermHeight = 3.5
        };

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(input);

        // Assert
        AssertHelper::AssertAreEqualWithAcceptablePrecision(0.20871481028151, outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_UpperSlopeAboveOuterCrest_ExpectedValue)
    {
        // Setup
        const NaturalStoneRevetmentOuterSlopeInput input
        {
            ._slopeLowerPosition = 12.5,
            ._slopeLowerLevel = 2.8,
            ._slopeUpperPosition = 45.0,
            ._slopeUpperLevel = 7.1,
            ._outerToeHeight = 0.5,
            ._outerCrestHeight = 7.0,
            ._notchOuterBermPosition = 25.0,
            ._notchOuterBermHeight = 4.1,
            ._crestOuterBermPosition = 15.0,
            ._crestOuterBermHeight = 3.5
        };

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(input);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_LowerSlopeBelowOuterToe_ExpectedValue)
    {
        // Setup
        const NaturalStoneRevetmentOuterSlopeInput input
        {
            ._slopeLowerPosition = 0.0,
            ._slopeLowerLevel = 0.4,
            ._slopeUpperPosition = 40.0,
            ._slopeUpperLevel = 7.0,
            ._outerToeHeight = 0.5,
            ._outerCrestHeight = 7.0,
            ._notchOuterBermPosition = 25.0,
            ._notchOuterBermHeight = 4.1,
            ._crestOuterBermPosition = 15.0,
            ._crestOuterBermHeight = 3.5
        };

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(input);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, SlopeUpperLevel_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto outerToeHeight = 5.35;
        constexpr auto outerCrestHeight = 14.1;
        constexpr auto waterLevel = 0.1;
        constexpr auto waveHeightHm0 = 1.5;
        constexpr auto slopeUpperLevelAus = 0.05;

        // Call
        const auto slopeUpperLevel = NaturalStoneRevetmentFunctions::SlopeUpperLevel(outerToeHeight, outerCrestHeight, waterLevel, waveHeightHm0,
                                                                                     slopeUpperLevelAus);

        // Assert
        ASSERT_DOUBLE_EQ(5.425, slopeUpperLevel);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, SlopeLowerLevel_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto outerToeHeight = 5.35;
        constexpr auto slopeUpperLevel = 5.425;
        constexpr auto waveHeightHm0 = 1.5;
        constexpr auto slopeLowerLevelAls = 1.5;

        // Call
        const auto slopeLowerLevel = NaturalStoneRevetmentFunctions::SlopeLowerLevel(outerToeHeight, slopeUpperLevel, waveHeightHm0,
                                                                                     slopeLowerLevelAls);

        // Assert
        ASSERT_DOUBLE_EQ(5.35, slopeLowerLevel);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, UpperLimitLoading_ValidInput_ExpectedValue)
    {
        // Setup
        const NaturalStoneRevetmentLimitLoadingInput input
        {
            ._depthMaximumWaveLoad = 0.38,
            ._surfSimilarityParameter = 1.28,
            ._waterLevel = 1.77,
            ._waveHeightHm0 = 1.8,
            ._a = 0.1,
            ._b = 0.6,
            ._c = 4.0
        };

        // Call
        const auto upperLimitLoading = NaturalStoneRevetmentFunctions::UpperLimitLoading(input);

        // Assert
        ASSERT_DOUBLE_EQ(2.3924, upperLimitLoading);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, LowerLimitLoading_ValidInput_ExpectedValue)
    {
        // Setup
        const NaturalStoneRevetmentLimitLoadingInput input
        {
            ._depthMaximumWaveLoad = 0.38,
            ._surfSimilarityParameter = 1.28,
            ._waterLevel = 1.77,
            ._waveHeightHm0 = 1.8,
            ._a = 0.1,
            ._b = 0.2,
            ._c = 4.0
        };

        // Call
        const auto lowerLimitLoading = NaturalStoneRevetmentFunctions::LowerLimitLoading(input);

        // Assert
        ASSERT_DOUBLE_EQ(1.29, lowerLimitLoading);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, DepthMaximumWaveLoad_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto distanceMaximumWaveElevation = 2.25;
        constexpr auto normativeWidthWaveImpact = 1.47;
        constexpr auto slopeAngle = 14.037;

        // Call
        const auto depthMaximumWaveLoad = NaturalStoneRevetmentFunctions::DepthMaximumWaveLoad(
            distanceMaximumWaveElevation, normativeWidthWaveImpact, slopeAngle);

        // Assert
        ASSERT_DOUBLE_EQ(0.38425846631481392, depthMaximumWaveLoad);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, DistanceMaximumWaveElevation_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto impactShallowWater = 1.1;
        constexpr auto waveSteepnessDeepWater = 0.038;
        constexpr auto waveHeightHm0 = 1.8;
        constexpr auto distanceMaximumWaveElevationAsmax = 0.42;
        constexpr auto distanceMaximumWaveElevationBsmax = 0.9;

        // Call
        const auto distanceMaximumWaveElevation = NaturalStoneRevetmentFunctions::DistanceMaximumWaveElevation(
            impactShallowWater, waveSteepnessDeepWater, waveHeightHm0, distanceMaximumWaveElevationAsmax, distanceMaximumWaveElevationBsmax);

        // Assert
        ASSERT_DOUBLE_EQ(2.4840179879700712, distanceMaximumWaveElevation);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, NormativeWidthWaveImpact_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto surfSimilarityParameter = 1.28;
        constexpr auto waveHeightHm0 = 1.8;
        constexpr auto normativeWidthWaveImpactAwi = 0.96;
        constexpr auto normativeWidthWaveImpactBwi = 0.11;

        // Call
        const auto normativeWidthWaveImpact = NaturalStoneRevetmentFunctions::NormativeWidthWaveImpact(
            surfSimilarityParameter, waveHeightHm0, normativeWidthWaveImpactAwi, normativeWidthWaveImpactBwi);

        // Assert
        ASSERT_DOUBLE_EQ(1.47456, normativeWidthWaveImpact);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, WaveAngleImpact_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto waveAngle = 5.0;
        constexpr auto waveAngleImpactBetamax = 78.0;

        // Call
        const auto waveAngleImpact = NaturalStoneRevetmentFunctions::WaveAngleImpact(waveAngle, waveAngleImpactBetamax);

        // Assert
        ASSERT_DOUBLE_EQ(0.99746152040928704, waveAngleImpact);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, Resistance_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto relativeDensity = 1.65;
        constexpr auto thicknessTopLayer = 0.3;

        // Call
        const auto resistance = NaturalStoneRevetmentFunctions::Resistance(relativeDensity, thicknessTopLayer);

        // Assert
        ASSERT_DOUBLE_EQ(0.495, resistance);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, IncrementDegradation_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto referenceTimeDegradation = 579.743;
        constexpr auto incrementTime = 900;
        constexpr auto wavePeriodTm10 = 5.5;

        // Call
        const auto incrementDegradation = NaturalStoneRevetmentFunctions::IncrementDegradation(
            referenceTimeDegradation, incrementTime, wavePeriodTm10);

        // Assert
        ASSERT_DOUBLE_EQ(0.078442472004777053, incrementDegradation);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, ReferenceTimeDegradation_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto referenceDegradation = 0.802;
        constexpr auto wavePeriodTm10 = 5.5;

        // Call
        const auto referenceTimeDegradation = NaturalStoneRevetmentFunctions::ReferenceTimeDegradation(referenceDegradation, wavePeriodTm10);

        // Assert
        ASSERT_DOUBLE_EQ(605.48915987364103, referenceTimeDegradation);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, ReferenceDegradation_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto resistance = 0.495;
        constexpr auto hydraulicLoad = 0.56;
        constexpr auto waveAngleImpact = 0.997;
        constexpr auto initialDamage = 0.905;

        // Call
        const auto referenceDegradation = NaturalStoneRevetmentFunctions::ReferenceDegradation(
            resistance, hydraulicLoad, waveAngleImpact, initialDamage);

        // Assert
        ASSERT_DOUBLE_EQ(0.80236244447628591, referenceDegradation);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, DurationInTimeStepFailure_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto referenceTimeFailure = 945.943;
        constexpr auto referenceTimeDegradation = 597.743;

        // Call
        const auto durationInTimeStepFailure = NaturalStoneRevetmentFunctions::DurationInTimeStepFailure(
            referenceTimeFailure, referenceTimeDegradation);

        // Assert
        ASSERT_DOUBLE_EQ(348.2, durationInTimeStepFailure);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, ReferenceTimeFailure_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto referenceFailure = 0.84;
        constexpr auto wavePeriodTm10 = 5.5;

        // Call
        const auto referenceTimeFailure = NaturalStoneRevetmentFunctions::ReferenceTimeFailure(referenceFailure, wavePeriodTm10);

        // Assert
        ASSERT_DOUBLE_EQ(961.95675821289467, referenceTimeFailure);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, ReferenceFailure_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto resistance = 0.495;
        constexpr auto hydraulicLoad = 0.56;
        constexpr auto waveAngleImpact = 0.997;
        constexpr auto failureNumber = 0.95;

        // Call
        const auto referenceFailure = NaturalStoneRevetmentFunctions::ReferenceFailure(resistance, hydraulicLoad, waveAngleImpact, failureNumber);

        // Assert
        ASSERT_DOUBLE_EQ(0.84225891961599064, referenceFailure);
    }
}
