// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.Output
{
    [TestFixture]
    public class GrassRevetmentWaveImpactTimeDependentOutputTest
    {
        
    }

    struct GrassRevetmentWaveImpactTimeDependentOutputTest : Test
    {
        static unique_ptr<GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties> CreateFullyConfiguredConstructionProperties()
        {
            var constructionProperties = make_unique<GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties>();
            constructionProperties->_incrementDamage = make_unique<double>(0.1);
            constructionProperties->_damage = make_unique<double>(0.2);
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
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_loadingRevetment = nullptr;

            // Call
            const GrassRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithUpperLimitLoadingNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_upperLimitLoading = nullptr;

            // Call
            const GrassRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithLowerLimitLoadingNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_lowerLimitLoading = nullptr;

            // Call
            const GrassRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }
    };

        [Test]
    public void Constructor_WithAllValuesSet_ExpectedValues()
    {
        // Setup
        var incrementDamage = 0.1;
        var damage = 0.2;
        var timeOfFailure = 3;
        var loadingRevetment = true;
        var upperLimitLoading = 0.4;
        var lowerLimitLoading = 0.5;
        var minimumWaveHeight = 0.6;
        var maximumWaveHeight = 0.7;
        var waveAngleImpact = 0.8;
        var waveHeightImpact = 0.9;

        GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
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
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(timeOfFailure, *output.GetTimeOfFailure());
        ASSERT_EQ(loadingRevetment, output.GetLoadingRevetment());
        ASSERT_DOUBLE_EQ(upperLimitLoading, output.GetUpperLimitLoading());
        ASSERT_DOUBLE_EQ(lowerLimitLoading, output.GetLowerLimitLoading());
        ASSERT_DOUBLE_EQ(minimumWaveHeight, *output.GetMinimumWaveHeight());
        ASSERT_DOUBLE_EQ(maximumWaveHeight, *output.GetMaximumWaveHeight());
        ASSERT_DOUBLE_EQ(waveAngleImpact, *output.GetWaveAngleImpact());
        ASSERT_DOUBLE_EQ(waveHeightImpact, *output.GetWaveHeightImpact());
    }

        [Test]
    public void Constructor_WithNullPtrValues_ExpectedValues()
    {
        // Setup
        var incrementDamage = 0.1;
        var damage = 0.2;
        var loadingRevetment = false;
        var upperLimitLoading = 0.3;
        var lowerLimitLoading = 0.4;

        GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
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
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(nullptr, output.GetTimeOfFailure());
        ASSERT_EQ(loadingRevetment, output.GetLoadingRevetment());
        ASSERT_DOUBLE_EQ(upperLimitLoading, output.GetUpperLimitLoading());
        ASSERT_DOUBLE_EQ(lowerLimitLoading, output.GetLowerLimitLoading());
        ASSERT_EQ(nullptr, output.GetMinimumWaveHeight());
        ASSERT_EQ(nullptr, output.GetMaximumWaveHeight());
        ASSERT_EQ(nullptr, output.GetWaveAngleImpact());
        ASSERT_EQ(nullptr, output.GetWaveHeightImpact());
    }

        [Test]
    public void Constructor_LoadingRevetmentNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &GrassRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithLoadingRevetmentNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "loadingRevetment must be set.");
    }

        [Test]
    public void Constructor_UpperLimitLoadingNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &GrassRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithUpperLimitLoadingNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "upperLimitLoading must be set.");
    }

        [Test]
    public void Constructor_LowerLimitLoadingNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &GrassRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithLowerLimitLoadingNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "lowerLimitLoading must be set.");
    }
}
