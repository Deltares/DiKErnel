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

#include "AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteDefaults.h"
#include "AssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteDefaults, Constructor_ExpectedValues)
    {
        // Call
        const AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteDefaults defaults;

        // Assert
        AssertHelper::AssertIsInstanceOf<IAsphaltRevetmentWaveImpactDefaults>(&defaults);
        ASSERT_DOUBLE_EQ(0, defaults.GetSubLayerThickness());
        ASSERT_DOUBLE_EQ(1, defaults.GetAverageNumberOfWavesCtm());
        ASSERT_DOUBLE_EQ(0.42, defaults.GetFatigueAlpha());
        ASSERT_DOUBLE_EQ(4.76, defaults.GetFatigueBeta());
        ASSERT_DOUBLE_EQ(1, defaults.GetImpactNumberC());
        ASSERT_DOUBLE_EQ(0.35, defaults.GetStiffnessRelationNu());

        const auto expectedWidthFactors = vector
        {
            tuple(0.1, 0.0392),
            tuple(0.2, 0.0738),
            tuple(0.3, 0.1002),
            tuple(0.4, 0.1162),
            tuple(0.5, 0.1213),
            tuple(0.6, 0.1168),
            tuple(0.7, 0.1051),
            tuple(0.8, 0.0890),
            tuple(0.9, 0.0712),
            tuple(1.0, 0.0541),
            tuple(1.1, 0.0391),
            tuple(1.2, 0.0269),
            tuple(1.3, 0.0216),
            tuple(1.4, 0.0150),
            tuple(1.5, 0.0105)
        };

        const auto expectedDepthFactors = vector
        {
            tuple(-1.0, 0.0244),
            tuple(-0.875, 0.0544),
            tuple(-0.750, 0.0938),
            tuple(-0.625, 0.1407),
            tuple(-0.500, 0.1801),
            tuple(-0.375, 0.1632),
            tuple(-0.250, 0.1426),
            tuple(-0.125, 0.0994),
            tuple(0.0, 0.06),
            tuple(0.125, 0.0244),
            tuple(0.250, 0.0169)
        };

        const auto expectedImpactFactors = vector
        {
            tuple(2.0, 0.039),
            tuple(2.4, 0.1),
            tuple(2.8, 0.18),
            tuple(3.2, 0.235),
            tuple(3.6, 0.2),
            tuple(4.0, 0.13),
            tuple(4.4, 0.08),
            tuple(4.8, 0.02),
            tuple(5.2, 0.01),
            tuple(5.6, 0.005),
            tuple(6.0, 0.001)
        };

        ASSERT_EQ(expectedWidthFactors, defaults.GetWidthFactors());
        ASSERT_EQ(expectedDepthFactors, defaults.GetDepthFactors());
        ASSERT_EQ(expectedImpactFactors, defaults.GetImpactFactors());
    }
}
