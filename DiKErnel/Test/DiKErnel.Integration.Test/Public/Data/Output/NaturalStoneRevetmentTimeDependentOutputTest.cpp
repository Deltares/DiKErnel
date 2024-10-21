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
    using namespace testing;
    using namespace TestUtil;

    struct NaturalStoneRevetmentTimeDependentOutputTest : Test
    {
        static unique_ptr<NaturalStoneRevetmentTimeDependentOutputConstructionProperties> CreateFullyConfiguredConstructionProperties()
        {
            auto constructionProperties = make_unique<NaturalStoneRevetmentTimeDependentOutputConstructionProperties>();
            constructionProperties->_incrementDamage = make_unique<double>(0.1);
            constructionProperties->_timeOfFailure = make_unique<int>(3);
            constructionProperties->_outerSlope = make_unique<double>(0.4);
            constructionProperties->_slopeUpperLevel = make_unique<double>(0.5);
            constructionProperties->_slopeUpperPosition = make_unique<double>(0.6);
            constructionProperties->_slopeLowerLevel = make_unique<double>(0.7);
            constructionProperties->_slopeLowerPosition = make_unique<double>(0.8);
            constructionProperties->_loadingRevetment = make_unique<bool>(true);
            constructionProperties->_surfSimilarityParameter = make_unique<double>(0.9);
            constructionProperties->_waveSteepnessDeepWater = make_unique<double>(1.0);
            constructionProperties->_upperLimitLoading = make_unique<double>(1.1);
            constructionProperties->_lowerLimitLoading = make_unique<double>(1.2);
            constructionProperties->_depthMaximumWaveLoad = make_unique<double>(1.3);
            constructionProperties->_distanceMaximumWaveElevation = make_unique<double>(1.4);
            constructionProperties->_normativeWidthOfWaveImpact = make_unique<double>(1.5);
            constructionProperties->_hydraulicLoad = make_unique<double>(1.6);
            constructionProperties->_waveAngleImpact = make_unique<double>(1.7);
            constructionProperties->_resistance = make_unique<double>(1.8);
            constructionProperties->_referenceTimeDegradation = make_unique<double>(1.9);
            constructionProperties->_referenceDegradation = make_unique<double>(2.0);

            return constructionProperties;
        }

        static void CreateOutputWithConstructionPropertiesWithOuterSlopeNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_outerSlope = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSlopeUpperLevelNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_slopeUpperLevel = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSlopeUpperPositionNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_slopeUpperPosition = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSlopeLowerLevelNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_slopeLowerLevel = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSlopeLowerPositionNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_slopeLowerPosition = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithLoadingRevetmentNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_loadingRevetment = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSurfSimilarityParameterNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_surfSimilarityParameter = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithWaveSteepnessDeepWaterNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_waveSteepnessDeepWater = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithUpperLimitLoadingNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_upperLimitLoading = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithLowerLimitLoadingNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_lowerLimitLoading = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithDepthMaximumWaveLoadNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_depthMaximumWaveLoad = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithDistanceMaximumWaveElevationNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_distanceMaximumWaveElevation = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithNormativeWidthOfWaveImpactNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_normativeWidthOfWaveImpact = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }
    };

    TEST_F(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_WithAllValuesSet_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
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

        NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);
        constructionProperties._outerSlope = make_unique<double>(outerSlope);
        constructionProperties._slopeUpperLevel = make_unique<double>(slopeUpperLevel);
        constructionProperties._slopeUpperPosition = make_unique<double>(slopeUpperPosition);
        constructionProperties._slopeLowerLevel = make_unique<double>(slopeLowerLevel);
        constructionProperties._slopeLowerPosition = make_unique<double>(slopeLowerPosition);
        constructionProperties._loadingRevetment = make_unique<bool>(loadingRevetment);
        constructionProperties._surfSimilarityParameter = make_unique<double>(surfSimilarityParameter);
        constructionProperties._waveSteepnessDeepWater = make_unique<double>(waveSteepnessDeepWater);
        constructionProperties._upperLimitLoading = make_unique<double>(upperLimitLoading);
        constructionProperties._lowerLimitLoading = make_unique<double>(lowerLimitLoading);
        constructionProperties._depthMaximumWaveLoad = make_unique<double>(depthMaximumWaveLoad);
        constructionProperties._distanceMaximumWaveElevation = make_unique<double>(distanceMaximumWaveElevation);
        constructionProperties._normativeWidthOfWaveImpact = make_unique<double>(normativeWidthOfWaveImpact);
        constructionProperties._hydraulicLoad = make_unique<double>(hydraulicLoad);
        constructionProperties._waveAngleImpact = make_unique<double>(waveAngleImpact);
        constructionProperties._resistance = make_unique<double>(resistance);
        constructionProperties._referenceTimeDegradation = make_unique<double>(referenceTimeDegradation);
        constructionProperties._referenceDegradation = make_unique<double>(referenceDegradation);

        // Call
        const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
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

    TEST_F(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_WithNullPtrValues_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
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

        NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._timeOfFailure = nullptr;
        constructionProperties._outerSlope = make_unique<double>(outerSlope);
        constructionProperties._slopeUpperLevel = make_unique<double>(slopeUpperLevel);
        constructionProperties._slopeUpperPosition = make_unique<double>(slopeUpperPosition);
        constructionProperties._slopeLowerLevel = make_unique<double>(slopeLowerLevel);
        constructionProperties._slopeLowerPosition = make_unique<double>(slopeLowerPosition);
        constructionProperties._loadingRevetment = make_unique<bool>(loadingRevetment);
        constructionProperties._surfSimilarityParameter = make_unique<double>(surfSimilarityParameter);
        constructionProperties._waveSteepnessDeepWater = make_unique<double>(waveSteepnessDeepWater);
        constructionProperties._upperLimitLoading = make_unique<double>(upperLimitLoading);
        constructionProperties._lowerLimitLoading = make_unique<double>(lowerLimitLoading);
        constructionProperties._depthMaximumWaveLoad = make_unique<double>(depthMaximumWaveLoad);
        constructionProperties._distanceMaximumWaveElevation = make_unique<double>(distanceMaximumWaveElevation);
        constructionProperties._normativeWidthOfWaveImpact = make_unique<double>(normativeWidthOfWaveImpact);
        constructionProperties._hydraulicLoad = nullptr;
        constructionProperties._waveAngleImpact = nullptr;
        constructionProperties._resistance = nullptr;
        constructionProperties._referenceTimeDegradation = nullptr;
        constructionProperties._referenceDegradation = nullptr;

        // Call
        const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
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

    TEST_F(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_OuterSlopeNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithOuterSlopeNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "outerSlope must be set.");
    }

    TEST_F(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_SlopeUpperLevelNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithSlopeUpperLevelNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "slopeUpperLevel must be set.");
    }

    TEST_F(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_SlopeUpperPositionNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithSlopeUpperPositionNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "slopeUpperPosition must be set.");
    }

    TEST_F(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_SlopeLowerLevelNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithSlopeLowerLevelNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "slopeLowerLevel must be set.");
    }

    TEST_F(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_SlopeLowerPositionNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithSlopeLowerPositionNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "slopeLowerPosition must be set.");
    }

    TEST_F(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_LoadingRevetmentNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithLoadingRevetmentNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "loadingRevetment must be set.");
    }

    TEST_F(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_SurfSimilarityParameterNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithSurfSimilarityParameterNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "surfSimilarityParameter must be set.");
    }

    TEST_F(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_LowerLimitLoadingNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithLowerLimitLoadingNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "lowerLimitLoading must be set.");
    }

    TEST_F(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_DepthMaximumWaveLoadNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithDepthMaximumWaveLoadNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "depthMaximumWaveLoad must be set.");
    }

    TEST_F(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_DistanceMaximumWaveElevationNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &
                NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithDistanceMaximumWaveElevationNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "distanceMaximumWaveElevation must be set.");
    }

    TEST_F(NaturalStoneRevetmentTimeDependentOutputTest, Constructor_NormativeWidthOfWaveImpactNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &
                NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithNormativeWidthOfWaveImpactNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "normativeWidthOfWaveImpact must be set.");
    }
}
