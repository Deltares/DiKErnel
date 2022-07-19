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
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto timeOfFailure = 3;
        constexpr auto logFailureTension = 0.4;
        constexpr auto maximumPeakStress = 0.5;
        constexpr auto stiffnessRelation = 0.6;
        constexpr auto computationalThickness = 0.7;
        constexpr auto equivalentElasticModulus = 0.8;

        AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
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
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(timeOfFailure, *output.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(logFailureTension, output.GetLogFailureTension());
        ASSERT_DOUBLE_EQ(maximumPeakStress, output.GetMaximumPeakStress());
        ASSERT_DOUBLE_EQ(stiffnessRelation, output.GetStiffnessRelation());
        ASSERT_DOUBLE_EQ(computationalThickness, output.GetComputationalThickness());
        ASSERT_DOUBLE_EQ(equivalentElasticModulus, output.GetEquivalentElasticModulus());
    }

    TEST(AsphaltRevetmentWaveImpactTimeDependentOutputTest, Constructor_WithNullPtrValues_ExpectedValues)
    {
        // Setup
        constexpr auto incrementDamage = 0.1;
        constexpr auto damage = 0.2;
        constexpr auto logFailureTension = 0.3;
        constexpr auto maximumPeakStress = 0.4;
        constexpr auto stiffnessRelation = 0.5;
        constexpr auto computationalThickness = 0.6;
        constexpr auto equivalentElasticModulus = 0.7;

        AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
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
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(nullptr, output.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(logFailureTension, output.GetLogFailureTension());
        ASSERT_DOUBLE_EQ(maximumPeakStress, output.GetMaximumPeakStress());
        ASSERT_DOUBLE_EQ(stiffnessRelation, output.GetStiffnessRelation());
        ASSERT_DOUBLE_EQ(computationalThickness, output.GetComputationalThickness());
        ASSERT_DOUBLE_EQ(equivalentElasticModulus, output.GetEquivalentElasticModulus());
    }
}
