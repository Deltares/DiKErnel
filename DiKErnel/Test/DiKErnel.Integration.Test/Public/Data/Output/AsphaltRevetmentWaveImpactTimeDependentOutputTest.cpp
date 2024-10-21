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

#include "AsphaltRevetmentWaveImpactTimeDependentOutput.h"
#include "AssertHelper.h"
#include "InvalidTimeDependentOutputException.h"
#include "TimeDependentOutput.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct AsphaltRevetmentWaveImpactTimeDependentOutputTest : Test
    {
        static unique_ptr<AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties> CreateFullyConfiguredConstructionProperties()
        {
            auto constructionProperties = make_unique<AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties>();
            constructionProperties->_incrementDamage = make_unique<double>(0.1);
            constructionProperties->_timeOfFailure = make_unique<int>(3);
            constructionProperties->_logFailureTension = make_unique<double>(0.4);
            constructionProperties->_maximumPeakStress = make_unique<double>(0.5);
            constructionProperties->_stiffnessRelation = make_unique<double>(0.6);
            constructionProperties->_computationalThickness = make_unique<double>(0.7);
            constructionProperties->_equivalentElasticModulus = make_unique<double>(0.8);

            return constructionProperties;
        }

        static void CreateOutputWithConstructionPropertiesWithLogFailureTensionNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_logFailureTension = nullptr;

            // Call
            const AsphaltRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithMaximumPeakStressNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_maximumPeakStress = nullptr;

            // Call
            const AsphaltRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithStiffnessRelationNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_stiffnessRelation = nullptr;

            // Call
            const AsphaltRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithComputationalThicknessNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_computationalThickness = nullptr;

            // Call
            const AsphaltRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithEquivalentElasticModulusNullPtr()
        {
            // Setup
            const auto constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_equivalentElasticModulus = nullptr;

            // Call
            const AsphaltRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }
    };

    TEST_F(AsphaltRevetmentWaveImpactTimeDependentOutputTest, Constructor_WithAllValuesSet_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto timeOfFailure = 3;
        constexpr auto logFailureTension = 0.4;
        constexpr auto maximumPeakStress = 0.5;
        constexpr auto stiffnessRelation = 0.6;
        constexpr auto computationalThickness = 0.7;
        constexpr auto equivalentElasticModulus = 0.8;

        AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);
        constructionProperties._logFailureTension = make_unique<double>(logFailureTension);
        constructionProperties._maximumPeakStress = make_unique<double>(maximumPeakStress);
        constructionProperties._stiffnessRelation = make_unique<double>(stiffnessRelation);
        constructionProperties._computationalThickness = make_unique<double>(computationalThickness);
        constructionProperties._equivalentElasticModulus = make_unique<double>(equivalentElasticModulus);

        // Call
        const AsphaltRevetmentWaveImpactTimeDependentOutput output(constructionProperties);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_EQ(timeOfFailure, *output.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(logFailureTension, output.GetLogFailureTension());
        ASSERT_DOUBLE_EQ(maximumPeakStress, output.GetMaximumPeakStress());
        ASSERT_DOUBLE_EQ(stiffnessRelation, output.GetStiffnessRelation());
        ASSERT_DOUBLE_EQ(computationalThickness, output.GetComputationalThickness());
        ASSERT_DOUBLE_EQ(equivalentElasticModulus, output.GetEquivalentElasticModulus());
    }

    TEST_F(AsphaltRevetmentWaveImpactTimeDependentOutputTest, Constructor_WithNullPtrValues_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto logFailureTension = 0.3;
        constexpr auto maximumPeakStress = 0.4;
        constexpr auto stiffnessRelation = 0.5;
        constexpr auto computationalThickness = 0.6;
        constexpr auto equivalentElasticModulus = 0.7;

        AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._timeOfFailure = nullptr;
        constructionProperties._logFailureTension = make_unique<double>(logFailureTension);
        constructionProperties._maximumPeakStress = make_unique<double>(maximumPeakStress);
        constructionProperties._stiffnessRelation = make_unique<double>(stiffnessRelation);
        constructionProperties._computationalThickness = make_unique<double>(computationalThickness);
        constructionProperties._equivalentElasticModulus = make_unique<double>(equivalentElasticModulus);

        // Call
        const AsphaltRevetmentWaveImpactTimeDependentOutput output(constructionProperties);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_EQ(nullptr, output.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(logFailureTension, output.GetLogFailureTension());
        ASSERT_DOUBLE_EQ(maximumPeakStress, output.GetMaximumPeakStress());
        ASSERT_DOUBLE_EQ(stiffnessRelation, output.GetStiffnessRelation());
        ASSERT_DOUBLE_EQ(computationalThickness, output.GetComputationalThickness());
        ASSERT_DOUBLE_EQ(equivalentElasticModulus, output.GetEquivalentElasticModulus());
    }

    TEST_F(AsphaltRevetmentWaveImpactTimeDependentOutputTest, Constructor_LogFailureTensionNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &AsphaltRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithLogFailureTensionNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "logFailureTension must be set.");
    }

    TEST_F(AsphaltRevetmentWaveImpactTimeDependentOutputTest, Constructor_MaximumPeakStressNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &AsphaltRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithMaximumPeakStressNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "maximumPeakStress must be set.");
    }

    TEST_F(AsphaltRevetmentWaveImpactTimeDependentOutputTest, Constructor_StiffnessRelationNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action = &AsphaltRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithStiffnessRelationNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "stiffnessRelation must be set.");
    }

    TEST_F(AsphaltRevetmentWaveImpactTimeDependentOutputTest, Constructor_ComputationalThicknessNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action =
                &AsphaltRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithComputationalThicknessNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "computationalThickness must be set.");
    }

    TEST_F(AsphaltRevetmentWaveImpactTimeDependentOutputTest, Constructor_EquivalentElasticModulusNullPtr_ThrowsInvalidTimeDependentOutputException)
    {
        // Setup & Call
        const auto action =
                &AsphaltRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithEquivalentElasticModulusNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "equivalentElasticModulus must be set.");
    }
}
