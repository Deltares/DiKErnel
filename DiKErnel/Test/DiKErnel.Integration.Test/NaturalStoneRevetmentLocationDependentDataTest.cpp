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
#include "NaturalStoneRevetmentLocationDependentData.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace TestUtil;

    TEST(NaturalStoneRevetmentLocationDependentDataTest, Constructor_ExpectedValues)
    {
        // Setup
        const auto initialDamage = 0.1;
        const auto slopeAngle = 0.2;
        const auto relativeDensity = 0.3;
        const auto thicknessTopLayer = 0.4;
        const auto plungingCoefficientA = 0.5;
        const auto plungingCoefficientB = 0.6;
        const auto plungingCoefficientC = 0.7;
        const auto plungingCoefficientN = 0.8;
        const auto surgingCoefficientA = 0.9;
        const auto surgingCoefficientB = 1.0;
        const auto surgingCoefficientC = 1.1;
        const auto surgingCoefficientN = 1.2;
        const auto similarityParameterThreshold = 1.3;

        // Call
        const NaturalStoneRevetmentLocationDependentData locationDependentData(
            initialDamage, slopeAngle, relativeDensity, thicknessTopLayer, plungingCoefficientA, plungingCoefficientB, plungingCoefficientC,
            plungingCoefficientN, surgingCoefficientA, surgingCoefficientB, surgingCoefficientC, surgingCoefficientN, similarityParameterThreshold);

        // Assert
        AssertHelper::AssertIsInstanceOf<LocationDependentData>(&locationDependentData);
        ASSERT_DOUBLE_EQ(initialDamage, locationDependentData.GetInitialDamage());
        ASSERT_DOUBLE_EQ(slopeAngle, locationDependentData.GetSlopeAngle());
        ASSERT_DOUBLE_EQ(relativeDensity, locationDependentData. GetRelativeDensity());
        ASSERT_DOUBLE_EQ(thicknessTopLayer, locationDependentData.GetThicknessTopLayer());
        ASSERT_DOUBLE_EQ(plungingCoefficientA, locationDependentData. GetPlungingCoefficientA());
        ASSERT_DOUBLE_EQ(plungingCoefficientB, locationDependentData. GetPlungingCoefficientB());
        ASSERT_DOUBLE_EQ(plungingCoefficientC, locationDependentData. GetPlungingCoefficientC());
        ASSERT_DOUBLE_EQ(plungingCoefficientN, locationDependentData. GetPlungingCoefficientN());
        ASSERT_DOUBLE_EQ(surgingCoefficientA, locationDependentData. GetSurgingCoefficientA());
        ASSERT_DOUBLE_EQ(surgingCoefficientB, locationDependentData. GetSurgingCoefficientB());
        ASSERT_DOUBLE_EQ(surgingCoefficientC, locationDependentData. GetSurgingCoefficientC());
        ASSERT_DOUBLE_EQ(surgingCoefficientN, locationDependentData. GetSurgingCoefficientN());
        ASSERT_DOUBLE_EQ(similarityParameterThreshold, locationDependentData.GetSimilarityParameterThreshold());
    }

    TEST(NaturalStoneRevetmentLocationDependentDataTest, Calculate_Always_PerformsCalculation)
    {
        // Setup
        NaturalStoneRevetmentLocationDependentData locationDependentData(0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3);
        const TimeDependentData timeDependentData(0, 10, 1.4, 1.5, 1.6, 1.7);

        // Call
        const auto damage = locationDependentData.Calculate(0.1, timeDependentData, 1.8);

        // Assert
        ASSERT_DOUBLE_EQ(6.838261669531513, damage);
    }
}
