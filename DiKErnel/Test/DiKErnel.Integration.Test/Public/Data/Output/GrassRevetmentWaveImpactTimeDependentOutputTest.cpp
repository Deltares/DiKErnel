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
#include "GrassRevetmentWaveImpactTimeDependentOutput.h"
#include "InvalidTimeDependentOutputException.h"
#include "TimeDependentOutput.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct GrassRevetmentWaveImpactTimeDependentOutputTest : Test
    {
        static unique_ptr<GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties> CreateFullyConfiguredConstructionProperties()
        {
            auto constructionProperties = make_unique<GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties>();
            constructionProperties->_incrementDamage = make_unique<double>(0.1);
            constructionProperties->_timeOfFailure = make_unique<int>(3);
            constructionProperties->_loadingRevetment = make_unique<bool>(true);
            constructionProperties->_upperLimitLoading = make_unique<double>(0.4);
            constructionProperties->_lowerLimitLoading = make_unique<double>(0.5);
            constructionProperties->_minimumWaveHeight = make_unique<double>(0.6);
            constructionProperties->_maximumWaveHeight = make_unique<double>(0.7);
            constructionProperties->_waveAngleImpact = make_unique<double>(0.8);
            constructionProperties->_waveHeightImpact = make_unique<double>(0.9);

            return constructionProperties;
        }

        static void CreateOutputWithConstructionPropertiesWithLoadingRevetmentNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_loadingRevetment = nullptr;

            // Call
            const GrassRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithUpperLimitLoadingNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_upperLimitLoading = nullptr;

            // Call
            const GrassRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithLowerLimitLoadingNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_lowerLimitLoading = nullptr;

            // Call
            const GrassRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }
    };

    TEST_F(GrassRevetmentWaveImpactTimeDependentOutputTest, Constructor_WithAllValuesSet_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto timeOfFailure = 3;
        constexpr auto loadingRevetment = true;
        constexpr auto upperLimitLoading = 0.4;
        constexpr auto lowerLimitLoading = 0.5;
        constexpr auto minimumWaveHeight = 0.6;
        constexpr auto maximumWaveHeight = 0.7;
        constexpr auto waveAngleImpact = 0.8;
        constexpr auto waveHeightImpact = 0.9;

        GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);
        constructionProperties._loadingRevetment = make_unique<bool>(loadingRevetment);
        constructionProperties._upperLimitLoading = make_unique<double>(upperLimitLoading);
        constructionProperties._lowerLimitLoading = make_unique<double>(lowerLimitLoading);
        constructionProperties._minimumWaveHeight = make_unique<double>(minimumWaveHeight);
        constructionProperties._maximumWaveHeight = make_unique<double>(maximumWaveHeight);
        constructionProperties._waveAngleImpact = make_unique<double>(waveAngleImpact);
        constructionProperties._waveHeightImpact = make_unique<double>(waveHeightImpact);

        // Call
        const GrassRevetmentWaveImpactTimeDependentOutput output(constructionProperties);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_EQ(timeOfFailure, *output.GetTimeOfFailure());
        ASSERT_EQ(loadingRevetment, output.GetLoadingRevetment());
        ASSERT_DOUBLE_EQ(upperLimitLoading, output.GetUpperLimitLoading());
        ASSERT_DOUBLE_EQ(lowerLimitLoading, output.GetLowerLimitLoading());
        ASSERT_DOUBLE_EQ(minimumWaveHeight, *output.GetMinimumWaveHeight());
        ASSERT_DOUBLE_EQ(maximumWaveHeight, *output.GetMaximumWaveHeight());
        ASSERT_DOUBLE_EQ(waveAngleImpact, *output.GetWaveAngleImpact());
        ASSERT_DOUBLE_EQ(waveHeightImpact, *output.GetWaveHeightImpact());
    }

    TEST_F(GrassRevetmentWaveImpactTimeDependentOutputTest, Constructor_WithNullPtrValues_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto loadingRevetment = false;
        constexpr auto upperLimitLoading = 0.3;
        constexpr auto lowerLimitLoading = 0.4;

        GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._timeOfFailure = nullptr;
        constructionProperties._loadingRevetment = make_unique<bool>(loadingRevetment);
        constructionProperties._upperLimitLoading = make_unique<double>(upperLimitLoading);
        constructionProperties._lowerLimitLoading = make_unique<double>(lowerLimitLoading);
        constructionProperties._minimumWaveHeight = nullptr;
        constructionProperties._maximumWaveHeight = nullptr;
        constructionProperties._waveAngleImpact = nullptr;
        constructionProperties._waveHeightImpact = nullptr;

        // Call
        const GrassRevetmentWaveImpactTimeDependentOutput output(constructionProperties);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_EQ(nullptr, output.GetTimeOfFailure());
        ASSERT_EQ(loadingRevetment, output.GetLoadingRevetment());
        ASSERT_DOUBLE_EQ(upperLimitLoading, output.GetUpperLimitLoading());
        ASSERT_DOUBLE_EQ(lowerLimitLoading, output.GetLowerLimitLoading());
        ASSERT_EQ(nullptr, output.GetMinimumWaveHeight());
        ASSERT_EQ(nullptr, output.GetMaximumWaveHeight());
        ASSERT_EQ(nullptr, output.GetWaveAngleImpact());
        ASSERT_EQ(nullptr, output.GetWaveHeightImpact());
    }

    TEST_F(GrassRevetmentWaveImpactTimeDependentOutputTest, Constructor_LoadingRevetmentNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &GrassRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithLoadingRevetmentNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "loadingRevetment must be set.");
    }

    TEST_F(GrassRevetmentWaveImpactTimeDependentOutputTest, Constructor_UpperLimitLoadingNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &GrassRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithUpperLimitLoadingNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "upperLimitLoading must be set.");
    }

    TEST_F(GrassRevetmentWaveImpactTimeDependentOutputTest, Constructor_LowerLimitLoadingNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &GrassRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithLowerLimitLoadingNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "lowerLimitLoading must be set.");
    }
}
