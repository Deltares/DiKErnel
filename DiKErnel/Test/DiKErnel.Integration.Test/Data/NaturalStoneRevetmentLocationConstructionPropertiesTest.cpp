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

#include "NaturalStoneRevetmentLocationConstructionProperties.h"

namespace DiKErnel::Integration::Test
{
    using namespace std;

    TEST(NaturalStoneRevetmentLocationConstructionPropertiesTest, Constructor_ExpectedValues)
    {
        // Setup
        const auto initialDamage = 0.1;
        const auto slopeAngle = 0.2;
        const auto thicknessTopLayer = 0.3;

        // Call
        const NaturalStoneRevetmentLocationConstructionProperties constructionProperties(initialDamage, slopeAngle, thicknessTopLayer);

        // Assert
        ASSERT_DOUBLE_EQ(initialDamage, constructionProperties.GetInitialDamage());
        ASSERT_DOUBLE_EQ(slopeAngle, constructionProperties.GetSlopeAngle());
        ASSERT_DOUBLE_EQ(thicknessTopLayer, constructionProperties.GetThicknessTopLayer());
        ASSERT_TRUE(constructionProperties.GetRelativeDensity() == nullptr);
        ASSERT_TRUE(constructionProperties.GetSimilarityParameterThreshold() == nullptr);
        ASSERT_TRUE(constructionProperties.GetPlungingCoefficientA() == nullptr);
        ASSERT_TRUE(constructionProperties.GetPlungingCoefficientB() == nullptr);
        ASSERT_TRUE(constructionProperties.GetPlungingCoefficientC() == nullptr);
        ASSERT_TRUE(constructionProperties.GetPlungingCoefficientN() == nullptr);
        ASSERT_TRUE(constructionProperties.GetSurgingCoefficientA() == nullptr);
        ASSERT_TRUE(constructionProperties.GetSurgingCoefficientB() == nullptr);
        ASSERT_TRUE(constructionProperties.GetSurgingCoefficientC() == nullptr);
        ASSERT_TRUE(constructionProperties.GetSurgingCoefficientN() == nullptr);
    }

    TEST(NaturalStoneRevetmentLocationConstructionPropertiesTest, GivenConstructionProperties_WhenAllFieldsSet_ThenExpectedValues)
    {
        // Given
        const auto initialDamage = 0.1;
        const auto slopeAngle = 0.2;
        const auto thicknessTopLayer = 0.3;
        const auto relativeDensity = 0.4;
        const auto similarityParameterThreshold = 0.5;
        const auto plungingCoefficientA = 0.6;
        const auto plungingCoefficientB = 0.7;
        const auto plungingCoefficientC = 0.8;
        const auto plungingCoefficientN = 0.9;
        const auto surgingCoefficientA = 1.0;
        const auto surgingCoefficientB = 1.1;
        const auto surgingCoefficientC = 1.2;
        const auto surgingCoefficientN = 1.3;

        NaturalStoneRevetmentLocationConstructionProperties constructionProperties(initialDamage, slopeAngle, thicknessTopLayer);

        // When
        constructionProperties.SetRelativeDensity(make_unique<double>(relativeDensity));
        constructionProperties.SetSimilarityParameterThreshold(make_unique<double>(similarityParameterThreshold));
        constructionProperties.SetPlungingCoefficientA(make_unique<double>(plungingCoefficientA));
        constructionProperties.SetPlungingCoefficientB(make_unique<double>(plungingCoefficientB));
        constructionProperties.SetPlungingCoefficientC(make_unique<double>(plungingCoefficientC));
        constructionProperties.SetPlungingCoefficientN(make_unique<double>(plungingCoefficientN));
        constructionProperties.SetSurgingCoefficientA(make_unique<double>(surgingCoefficientA));
        constructionProperties.SetSurgingCoefficientB(make_unique<double>(surgingCoefficientB));
        constructionProperties.SetSurgingCoefficientC(make_unique<double>(surgingCoefficientC));
        constructionProperties.SetSurgingCoefficientN(make_unique<double>(surgingCoefficientN));

        // Then
        ASSERT_DOUBLE_EQ(initialDamage, constructionProperties.GetInitialDamage());
        ASSERT_DOUBLE_EQ(slopeAngle, constructionProperties.GetSlopeAngle());
        ASSERT_DOUBLE_EQ(thicknessTopLayer, constructionProperties.GetThicknessTopLayer());
        ASSERT_DOUBLE_EQ(relativeDensity, *constructionProperties.GetRelativeDensity());
        ASSERT_DOUBLE_EQ(similarityParameterThreshold, *constructionProperties.GetSimilarityParameterThreshold());
        ASSERT_DOUBLE_EQ(plungingCoefficientA, *constructionProperties.GetPlungingCoefficientA());
        ASSERT_DOUBLE_EQ(plungingCoefficientB, *constructionProperties.GetPlungingCoefficientB());
        ASSERT_DOUBLE_EQ(plungingCoefficientC, *constructionProperties.GetPlungingCoefficientC());
        ASSERT_DOUBLE_EQ(plungingCoefficientN, *constructionProperties.GetPlungingCoefficientN());
        ASSERT_DOUBLE_EQ(surgingCoefficientA, *constructionProperties.GetSurgingCoefficientA());
        ASSERT_DOUBLE_EQ(surgingCoefficientB, *constructionProperties.GetSurgingCoefficientB());
        ASSERT_DOUBLE_EQ(surgingCoefficientC, *constructionProperties.GetSurgingCoefficientC());
        ASSERT_DOUBLE_EQ(surgingCoefficientN, *constructionProperties.GetSurgingCoefficientN());
    }
}
