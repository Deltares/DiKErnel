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
        ASSERT_TRUE(constructionProperties._relativeDensityPtr == nullptr);
        ASSERT_TRUE(constructionProperties._similarityParameterThresholdPtr == nullptr);
        ASSERT_TRUE(constructionProperties._plungingCoefficientAPtr == nullptr);
        ASSERT_TRUE(constructionProperties._plungingCoefficientBPtr == nullptr);
        ASSERT_TRUE(constructionProperties._plungingCoefficientCPtr == nullptr);
        ASSERT_TRUE(constructionProperties._plungingCoefficientNPtr == nullptr);
        ASSERT_TRUE(constructionProperties._surgingCoefficientAPtr == nullptr);
        ASSERT_TRUE(constructionProperties._surgingCoefficientBPtr == nullptr);
        ASSERT_TRUE(constructionProperties._surgingCoefficientCPtr == nullptr);
        ASSERT_TRUE(constructionProperties._surgingCoefficientNPtr == nullptr);
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
        constructionProperties._relativeDensityPtr = make_unique<double>(relativeDensity);
        constructionProperties._similarityParameterThresholdPtr = make_unique<double>(similarityParameterThreshold);
        constructionProperties._plungingCoefficientAPtr = make_unique<double>(plungingCoefficientA);
        constructionProperties._plungingCoefficientBPtr = make_unique<double>(plungingCoefficientB);
        constructionProperties._plungingCoefficientCPtr = make_unique<double>(plungingCoefficientC);
        constructionProperties._plungingCoefficientNPtr = make_unique<double>(plungingCoefficientN);
        constructionProperties._surgingCoefficientAPtr = make_unique<double>(surgingCoefficientA);
        constructionProperties._surgingCoefficientBPtr = make_unique<double>(surgingCoefficientB);
        constructionProperties._surgingCoefficientCPtr = make_unique<double>(surgingCoefficientC);
        constructionProperties._surgingCoefficientNPtr = make_unique<double>(surgingCoefficientN);

        // Then
        ASSERT_DOUBLE_EQ(initialDamage, constructionProperties.GetInitialDamage());
        ASSERT_DOUBLE_EQ(slopeAngle, constructionProperties.GetSlopeAngle());
        ASSERT_DOUBLE_EQ(thicknessTopLayer, constructionProperties.GetThicknessTopLayer());
        ASSERT_DOUBLE_EQ(relativeDensity, *constructionProperties._relativeDensityPtr);
        ASSERT_DOUBLE_EQ(similarityParameterThreshold, *constructionProperties._similarityParameterThresholdPtr);
        ASSERT_DOUBLE_EQ(plungingCoefficientA, *constructionProperties._plungingCoefficientAPtr);
        ASSERT_DOUBLE_EQ(plungingCoefficientB, *constructionProperties._plungingCoefficientBPtr);
        ASSERT_DOUBLE_EQ(plungingCoefficientC, *constructionProperties._plungingCoefficientCPtr);
        ASSERT_DOUBLE_EQ(plungingCoefficientN, *constructionProperties._plungingCoefficientNPtr);
        ASSERT_DOUBLE_EQ(surgingCoefficientA, *constructionProperties._surgingCoefficientAPtr);
        ASSERT_DOUBLE_EQ(surgingCoefficientB, *constructionProperties._surgingCoefficientBPtr);
        ASSERT_DOUBLE_EQ(surgingCoefficientC, *constructionProperties._surgingCoefficientCPtr);
        ASSERT_DOUBLE_EQ(surgingCoefficientN, *constructionProperties._surgingCoefficientNPtr);
    }
}
