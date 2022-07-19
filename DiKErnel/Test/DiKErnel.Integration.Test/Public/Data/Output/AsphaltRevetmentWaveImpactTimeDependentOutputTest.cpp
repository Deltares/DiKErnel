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
#include "TimeDependentOutput.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace std;
    using namespace TestUtil;

    TEST(AsphaltRevetmentWaveImpactTimeDependentOutputTest, Constructor_WithAllValuesSet_ExpectedValues)
    {
        // Setup
        constexpr auto timeOfFailure = 3;

        AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties(0.1, 0.2, make_unique<int>(timeOfFailure));
        constructionProperties.SetLogFailureTension(0.4);
        constructionProperties.SetMaximumPeakStress(0.5);
        constructionProperties.SetStiffnessRelation(0.6);
        constructionProperties.SetComputationalThickness(0.7);
        constructionProperties.SetEquivalentElasticModulus(0.8);

        // Call
        const AsphaltRevetmentWaveImpactTimeDependentOutput output(constructionProperties);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(constructionProperties.GetIncrementDamage(), output.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(constructionProperties.GetDamage(), output.GetDamage());
        ASSERT_EQ(timeOfFailure, *output.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(constructionProperties.GetLogFailureTension(), output.GetLogFailureTension());
        ASSERT_DOUBLE_EQ(constructionProperties.GetMaximumPeakStress(), output.GetMaximumPeakStress());
        ASSERT_DOUBLE_EQ(constructionProperties.GetStiffnessRelation(), output.GetStiffnessRelation());
        ASSERT_DOUBLE_EQ(constructionProperties.GetComputationalThickness(), output.GetComputationalThickness());
        ASSERT_DOUBLE_EQ(constructionProperties.GetEquivalentElasticModulus(), output.GetEquivalentElasticModulus());
    }

    TEST(AsphaltRevetmentWaveImpactTimeDependentOutputTest, Constructor_WithNullPtrValues_ExpectedValues)
    {
        // Setup
        AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties(0.1, 0.2, nullptr);
        constructionProperties.SetLogFailureTension(0.3);
        constructionProperties.SetMaximumPeakStress(0.4);
        constructionProperties.SetStiffnessRelation(0.5);
        constructionProperties.SetComputationalThickness(0.6);
        constructionProperties.SetEquivalentElasticModulus(0.7);

        // Call
        const AsphaltRevetmentWaveImpactTimeDependentOutput output(constructionProperties);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(constructionProperties.GetIncrementDamage(), output.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(constructionProperties.GetDamage(), output.GetDamage());
        ASSERT_EQ(nullptr, output.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(constructionProperties.GetLogFailureTension(), output.GetLogFailureTension());
        ASSERT_DOUBLE_EQ(constructionProperties.GetMaximumPeakStress(), output.GetMaximumPeakStress());
        ASSERT_DOUBLE_EQ(constructionProperties.GetStiffnessRelation(), output.GetStiffnessRelation());
        ASSERT_DOUBLE_EQ(constructionProperties.GetComputationalThickness(), output.GetComputationalThickness());
        ASSERT_DOUBLE_EQ(constructionProperties.GetEquivalentElasticModulus(), output.GetEquivalentElasticModulus());
    }
}
