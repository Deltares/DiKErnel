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
#include "NaturalStoneRevetmentTimeDependentOutput.h"
#include "TimeDependentOutput.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace std;
    using namespace TestUtil;

    TEST(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_WithAllValuesSet_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto timeOfFailure = 3;
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

        // Call
        const NaturalStoneRevetmentTimeDependentOutput output(incrementDamage, damage, make_unique<int>(timeOfFailure), outerSlope,
                                                              slopeUpperLevel, slopeUpperPosition, slopeLowerLevel, slopeLowerPosition,
                                                              loadingRevetment, surfSimilarityParameter, waveSteepnessDeepWater, upperLimitLoading,
                                                              lowerLimitLoading, depthMaximumWaveLoad, distanceMaximumWaveElevation,
                                                              normativeWidthOfWaveImpact, make_unique<double>(hydraulicLoad),
                                                              make_unique<double>(waveAngleImpact), make_unique<double>(resistance),
                                                              make_unique<double>(referenceTimeDegradation),
                                                              make_unique<double>(referenceDegradation));

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(timeOfFailure, *output.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(outerSlope, output.GetOuterSlope());
        ASSERT_DOUBLE_EQ(slopeUpperLevel, output.GetSlopeUpperLevel());
        ASSERT_DOUBLE_EQ(slopeUpperPosition, output.GetSlopeUpperPosition());
        ASSERT_DOUBLE_EQ(slopeLowerLevel, output.GetSlopeLowerLevel());
        ASSERT_DOUBLE_EQ(slopeLowerPosition, output.GetSlopeLowerPosition());
        ASSERT_EQ(loadingRevetment, output.GetLoadingRevetment());
        ASSERT_DOUBLE_EQ(surfSimilarityParameter, output.GetSurfSimilarityParameter());
        ASSERT_DOUBLE_EQ(waveSteepnessDeepWater, output.GetWaveSteepnessDeepWater());
        ASSERT_DOUBLE_EQ(upperLimitLoading, output.GetUpperLimitLoading());
        ASSERT_DOUBLE_EQ(lowerLimitLoading, output.GetLowerLimitLoading());
        ASSERT_DOUBLE_EQ(depthMaximumWaveLoad, output.GetDepthMaximumWaveLoad());
        ASSERT_DOUBLE_EQ(distanceMaximumWaveElevation, output.GetDistanceMaximumWaveElevation());
        ASSERT_DOUBLE_EQ(normativeWidthOfWaveImpact, output.GetNormativeWidthOfWaveImpact());
        ASSERT_DOUBLE_EQ(hydraulicLoad, *output.GetHydraulicLoad());
        ASSERT_DOUBLE_EQ(waveAngleImpact, *output.GetWaveAngleImpact());
        ASSERT_DOUBLE_EQ(resistance, *output.GetResistance());
        ASSERT_DOUBLE_EQ(referenceTimeDegradation, *output.GetReferenceTimeDegradation());
        ASSERT_DOUBLE_EQ(referenceDegradation, *output.GetReferenceDegradation());
    }

    TEST(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_WithNullPtrValues_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto outerSlope = 0.3;
        constexpr auto slopeUpperLevel = 0.4;
        constexpr auto slopeUpperPosition = 0.5;
        constexpr auto slopeLowerLevel = 0.6;
        constexpr auto slopeLowerPosition = 0.7;
        constexpr auto loadingRevetment = false;
        constexpr auto surfSimilarityParameter = 0.8;
        constexpr auto waveSteepnessDeepWater = 0.9;
        constexpr auto upperLimitLoading = 1.0;
        constexpr auto lowerLimitLoading = 1.1;
        constexpr auto depthMaximumWaveLoad = 1.2;
        constexpr auto distanceMaximumWaveElevation = 1.3;
        constexpr auto normativeWidthOfWaveImpact = 1.4;

        // Call
        const NaturalStoneRevetmentTimeDependentOutput output(incrementDamage, damage, nullptr, outerSlope, slopeUpperLevel, slopeUpperPosition,
                                                              slopeLowerLevel, slopeLowerPosition, loadingRevetment, surfSimilarityParameter,
                                                              waveSteepnessDeepWater, upperLimitLoading, lowerLimitLoading, depthMaximumWaveLoad,
                                                              distanceMaximumWaveElevation, normativeWidthOfWaveImpact, nullptr, nullptr, nullptr,
                                                              nullptr, nullptr);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(nullptr, output.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(outerSlope, output.GetOuterSlope());
        ASSERT_DOUBLE_EQ(slopeUpperLevel, output.GetSlopeUpperLevel());
        ASSERT_DOUBLE_EQ(slopeUpperPosition, output.GetSlopeUpperPosition());
        ASSERT_DOUBLE_EQ(slopeLowerLevel, output.GetSlopeLowerLevel());
        ASSERT_DOUBLE_EQ(slopeLowerPosition, output.GetSlopeLowerPosition());
        ASSERT_EQ(loadingRevetment, output.GetLoadingRevetment());
        ASSERT_DOUBLE_EQ(surfSimilarityParameter, output.GetSurfSimilarityParameter());
        ASSERT_DOUBLE_EQ(waveSteepnessDeepWater, output.GetWaveSteepnessDeepWater());
        ASSERT_DOUBLE_EQ(upperLimitLoading, output.GetUpperLimitLoading());
        ASSERT_DOUBLE_EQ(lowerLimitLoading, output.GetLowerLimitLoading());
        ASSERT_DOUBLE_EQ(depthMaximumWaveLoad, output.GetDepthMaximumWaveLoad());
        ASSERT_DOUBLE_EQ(distanceMaximumWaveElevation, output.GetDistanceMaximumWaveElevation());
        ASSERT_DOUBLE_EQ(normativeWidthOfWaveImpact, output.GetNormativeWidthOfWaveImpact());
        ASSERT_EQ(nullptr, output.GetHydraulicLoad());
        ASSERT_EQ(nullptr, output.GetWaveAngleImpact());
        ASSERT_EQ(nullptr, output.GetResistance());
        ASSERT_EQ(nullptr, output.GetReferenceTimeDegradation());
        ASSERT_EQ(nullptr, output.GetReferenceDegradation());
    }
}
