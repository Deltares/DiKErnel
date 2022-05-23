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
        constexpr auto surfSimilarityParameter = 1.28;
        constexpr auto waveHeightHm0 = 1.8;
        constexpr auto hydraulicLoadA = 4.0;
        constexpr auto hydraulicLoadB = 0.1;
        constexpr auto hydraulicLoadC = 0.3;
        constexpr auto hydraulicLoadN = -0.9;

        // Call
        const auto hydraulicLoad = NaturalStoneRevetmentFunctions::HydraulicLoad(surfSimilarityParameter, waveHeightHm0, hydraulicLoadA,
                                                                                 hydraulicLoadB, hydraulicLoadC, hydraulicLoadN);

        // Assert
        ASSERT_DOUBLE_EQ(0.49571702636245252, hydraulicLoad);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithoutBerm_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto slopeUpperLevel = 5.425;
        constexpr auto slopeLowerLevel = 5.35;
        constexpr auto slopeUpperPosition = 30.3;
        constexpr auto slopeLowerPosition = 30.0;

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(slopeUpperLevel, slopeLowerLevel, slopeUpperPosition,
                                                                           slopeLowerPosition);

        // Assert
        ASSERT_DOUBLE_EQ(0.25, outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_UpperAndLowerSlopeLevelOnLowerSlope_ExpectedValue)
    {
        // Setup
        constexpr auto outerToeHeight = 0.5;
        constexpr auto outerCrestHeight = 7.0;
        constexpr auto notchOuterBermPosition = 25.0;
        constexpr auto notchOuterBermHeight = 4.1;
        constexpr auto crestOuterBermPosition = 15.0;
        constexpr auto crestOuterBermHeight = 3.5;
        constexpr auto slopeUpperLevel = 0.55;
        constexpr auto slopeLowerLevel = 0.5;
        constexpr auto slopeUpperPosition = 5.15625;
        constexpr auto slopeLowerPosition = 5.0;

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(outerToeHeight, outerCrestHeight, notchOuterBermPosition,
                                                                           notchOuterBermHeight, crestOuterBermPosition, crestOuterBermHeight,
                                                                           slopeUpperLevel, slopeLowerLevel, slopeUpperPosition,
                                                                           slopeLowerPosition);

        // Assert
        AssertHelper::AssertAreAlmostEqual(0.32, outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_UpperSlopeLevelOnBermAndLowerSlopeLevelOnLowerSlope_ExpectedValue)
    {
        // Setup
        constexpr auto outerToeHeight = 0.5;
        constexpr auto outerCrestHeight = 7.0;
        constexpr auto notchOuterBermPosition = 25.0;
        constexpr auto notchOuterBermHeight = 4.1;
        constexpr auto crestOuterBermPosition = 15.0;
        constexpr auto crestOuterBermHeight = 3.5;
        constexpr auto slopeUpperLevel = 3.5;
        constexpr auto slopeLowerLevel = 2.3;
        constexpr auto slopeUpperPosition = 15.0;
        constexpr auto slopeLowerPosition = 10.7142857142857;

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(outerToeHeight, outerCrestHeight, notchOuterBermPosition,
                                                                           notchOuterBermHeight, crestOuterBermPosition, crestOuterBermHeight,
                                                                           slopeUpperLevel, slopeLowerLevel, slopeUpperPosition,
                                                                           slopeLowerPosition);

        // Assert
        AssertHelper::AssertAreAlmostEqual(0.28, outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_UpperAndLowerSlopeLevelOnBerm_ExpectedValue)
    {
        // Setup
        constexpr auto outerToeHeight = 0.5;
        constexpr auto outerCrestHeight = 7.0;
        constexpr auto notchOuterBermPosition = 25.0;
        constexpr auto notchOuterBermHeight = 4.1;
        constexpr auto crestOuterBermPosition = 15.0;
        constexpr auto crestOuterBermHeight = 3.5;
        constexpr auto slopeUpperLevel = 3.8;
        constexpr auto slopeLowerLevel = 3.5;
        constexpr auto slopeUpperPosition = 18.75;
        constexpr auto slopeLowerPosition = 15.0;

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(outerToeHeight, outerCrestHeight, notchOuterBermPosition,
                                                                           notchOuterBermHeight, crestOuterBermPosition, crestOuterBermHeight,
                                                                           slopeUpperLevel, slopeLowerLevel, slopeUpperPosition,
                                                                           slopeLowerPosition);

        // Assert
        AssertHelper::AssertAreAlmostEqual(0.08, outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_UpperAndLowerSlopeLevelOnUpperSlope_ExpectedValue)
    {
        // Setup
        constexpr auto outerToeHeight = 0.5;
        constexpr auto outerCrestHeight = 7.0;
        constexpr auto notchOuterBermPosition = 25.0;
        constexpr auto notchOuterBermHeight = 4.1;
        constexpr auto crestOuterBermPosition = 15.0;
        constexpr auto crestOuterBermHeight = 3.5;
        constexpr auto slopeUpperLevel = 5.0;
        constexpr auto slopeLowerLevel = 4.25;
        constexpr auto slopeUpperPosition = 29.0909090909091;
        constexpr auto slopeLowerPosition = 25.6818181818182;

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(outerToeHeight, outerCrestHeight, notchOuterBermPosition,
                                                                           notchOuterBermHeight, crestOuterBermPosition, crestOuterBermHeight,
                                                                           slopeUpperLevel, slopeLowerLevel, slopeUpperPosition,
                                                                           slopeLowerPosition);

        // Assert
        AssertHelper::AssertAreAlmostEqual(0.22, outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_UpperSlopeLevelOnUpperSlopeAndLowerSlopeLevelOnBerm_ExpectedValue)
    {
        // Setup
        constexpr auto outerToeHeight = 0.5;
        constexpr auto outerCrestHeight = 7.0;
        constexpr auto notchOuterBermPosition = 25.0;
        constexpr auto notchOuterBermHeight = 4.1;
        constexpr auto crestOuterBermPosition = 15.0;
        constexpr auto crestOuterBermHeight = 3.5;
        constexpr auto slopeUpperLevel = 7.0;
        constexpr auto slopeLowerLevel = 4.075;
        constexpr auto slopeUpperPosition = 40.0;
        constexpr auto slopeLowerPosition = 24.375;

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(outerToeHeight, outerCrestHeight, notchOuterBermPosition,
                                                                           notchOuterBermHeight, crestOuterBermPosition, crestOuterBermHeight,
                                                                           slopeUpperLevel, slopeLowerLevel, slopeUpperPosition,
                                                                           slopeLowerPosition);

        // Assert
        AssertHelper::AssertAreAlmostEqual(0.193333333333333, outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_UpperSlopeLevelOnUpperSlopeAndLowerSlopeLevelOnLowerSlope_ExpectedValue)
    {
        // Setup
        constexpr auto outerToeHeight = 0.5;
        constexpr auto outerCrestHeight = 7.0;
        constexpr auto notchOuterBermPosition = 25.0;
        constexpr auto notchOuterBermHeight = 4.1;
        constexpr auto crestOuterBermPosition = 15.0;
        constexpr auto crestOuterBermHeight = 3.5;
        constexpr auto slopeUpperLevel = 7.0;
        constexpr auto slopeLowerLevel = 2.8;
        constexpr auto slopeUpperPosition = 40.0;
        constexpr auto slopeLowerPosition = 12.5;

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(outerToeHeight, outerCrestHeight, notchOuterBermPosition,
                                                                           notchOuterBermHeight, crestOuterBermPosition, crestOuterBermHeight,
                                                                           slopeUpperLevel, slopeLowerLevel, slopeUpperPosition,
                                                                           slopeLowerPosition);

        // Assert
        AssertHelper::AssertAreAlmostEqual(0.208714810281518, outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_UpperSlopeAboveOuterCrest_ExpectedValue)
    {
        // Setup
        constexpr auto outerToeHeight = 0.5;
        constexpr auto outerCrestHeight = 7.0;
        constexpr auto notchOuterBermPosition = 25.0;
        constexpr auto notchOuterBermHeight = 4.1;
        constexpr auto crestOuterBermPosition = 15.0;
        constexpr auto crestOuterBermHeight = 3.5;
        constexpr auto slopeUpperLevel = 7.1;
        constexpr auto slopeLowerLevel = 2.8;
        constexpr auto slopeUpperPosition = 45.0;
        constexpr auto slopeLowerPosition = 12.5;

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(outerToeHeight, outerCrestHeight, notchOuterBermPosition,
                                                                           notchOuterBermHeight, crestOuterBermPosition, crestOuterBermHeight,
                                                                           slopeUpperLevel, slopeLowerLevel, slopeUpperPosition,
                                                                           slopeLowerPosition);

        // Assert
        ASSERT_DOUBLE_EQ(numeric_limits<double>::infinity(), outerSlope);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, OuterSlopeWithBerm_LowerSlopeBelowOuterToe_ExpectedValue)
    {
        // Setup
        constexpr auto outerToeHeight = 0.5;
        constexpr auto outerCrestHeight = 7.0;
        constexpr auto notchOuterBermPosition = 25.0;
        constexpr auto notchOuterBermHeight = 4.1;
        constexpr auto crestOuterBermPosition = 15.0;
        constexpr auto crestOuterBermHeight = 3.5;
        constexpr auto slopeUpperLevel = 7.0;
        constexpr auto slopeLowerLevel = 0.4;
        constexpr auto slopeUpperPosition = 40.0;
        constexpr auto slopeLowerPosition = 0.0;

        // Call
        const auto outerSlope = NaturalStoneRevetmentFunctions::OuterSlope(outerToeHeight, outerCrestHeight, notchOuterBermPosition,
                                                                           notchOuterBermHeight, crestOuterBermPosition, crestOuterBermHeight,
                                                                           slopeUpperLevel, slopeLowerLevel, slopeUpperPosition,
                                                                           slopeLowerPosition);

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
        constexpr auto depthMaximumWaveLoad = 0.38;
        constexpr auto surfSimilarityParameter = 1.28;
        constexpr auto waterLevel = 1.77;
        constexpr auto waveHeightHm0 = 1.8;
        constexpr auto upperLimitLoadingAul = 0.1;
        constexpr auto upperLimitLoadingBul = 0.6;
        constexpr auto upperLimitLoadingCul = 4.0;

        // Call
        const auto upperLimitLoading = NaturalStoneRevetmentFunctions::UpperLimitLoading(depthMaximumWaveLoad, surfSimilarityParameter, waterLevel,
                                                                                         waveHeightHm0, upperLimitLoadingAul, upperLimitLoadingBul,
                                                                                         upperLimitLoadingCul);

        // Assert
        ASSERT_DOUBLE_EQ(2.3924, upperLimitLoading);
    }

    TEST(NaturalStoneRevetmentFunctionsTest, LowerLimitLoading_ValidInput_ExpectedValue)
    {
        // Setup
        constexpr auto depthMaximumWaveLoad = 0.38;
        constexpr auto surfSimilarityParameter = 1.28;
        constexpr auto waterLevel = 1.77;
        constexpr auto waveHeightHm0 = 1.8;
        constexpr auto lowerLimitLoadingAll = 0.1;
        constexpr auto lowerLimitLoadingBll = 0.2;
        constexpr auto lowerLimitLoadingCll = 4.0;

        // Call
        const auto lowerLimitLoading = NaturalStoneRevetmentFunctions::LowerLimitLoading(depthMaximumWaveLoad, surfSimilarityParameter, waterLevel,
                                                                                         waveHeightHm0, lowerLimitLoadingAll, lowerLimitLoadingBll,
                                                                                         lowerLimitLoadingCll);

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
