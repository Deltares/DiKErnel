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
        const auto incrementDamage = 0.1;
        const auto damage = 0.2;
        const auto timeOfFailure = 3;
        const auto loadingRevetment = true;
        const auto surfSimilarityParameter = 0.4;
        const auto waveSteepnessDeepWater = 0.5;
        const auto upperLimitLoading = 0.6;
        const auto lowerLimitLoading = 0.7;
        const auto depthMaximumWaveLoad = 0.8;
        const auto distanceMaximumWaveElevation = 0.9;
        const auto normativeWidthOfWaveImpact = 1.0;
        const auto hydraulicLoad = 1.1;
        const auto waveAngleImpact = 1.2;
        const auto resistance = 1.3;
        const auto referenceTimeDegradation = 1.4;
        const auto referenceDegradation = 1.5;

        // Call
        const auto output = NaturalStoneRevetmentTimeDependentOutput(incrementDamage, damage, make_unique<int>(timeOfFailure), loadingRevetment,
                                                                     surfSimilarityParameter, waveSteepnessDeepWater, upperLimitLoading,
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
        const auto incrementDamage = 0.1;
        const auto damage = 0.2;
        const auto loadingRevetment = false;
        const auto surfSimilarityParameter = 0.3;
        const auto waveSteepnessDeepWater = 0.4;
        const auto upperLimitLoading = 0.5;
        const auto lowerLimitLoading = 0.6;
        const auto depthMaximumWaveLoad = 0.7;
        const auto distanceMaximumWaveElevation = 0.8;
        const auto normativeWidthOfWaveImpact = 0.9;

        // Call
        const auto output = NaturalStoneRevetmentTimeDependentOutput(incrementDamage, damage, nullptr, loadingRevetment, surfSimilarityParameter,
                                                                     waveSteepnessDeepWater, upperLimitLoading, lowerLimitLoading,
                                                                     depthMaximumWaveLoad, distanceMaximumWaveElevation, normativeWidthOfWaveImpact,
                                                                     nullptr, nullptr, nullptr, nullptr, nullptr);
        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(nullptr, output.GetTimeOfFailure());
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
