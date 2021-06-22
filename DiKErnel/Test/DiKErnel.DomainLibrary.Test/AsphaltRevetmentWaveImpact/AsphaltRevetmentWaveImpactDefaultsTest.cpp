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

#include "AsphaltRevetmentWaveImpactDefaults.h"
#include "AssertHelper.h"

namespace DiKErnel::DomainLibrary::Test
{
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct AsphaltRevetmentWaveImpactDefaultsTest : Test
    {
        static vector<tuple<double, double>> GetExpectedWidthFactors()
        {
            auto expectedWidthFactors = vector<tuple<double, double>>();
            expectedWidthFactors.emplace_back(0.1, 0.0392);
            expectedWidthFactors.emplace_back(0.2, 0.0738);
            expectedWidthFactors.emplace_back(0.3, 0.1002);
            expectedWidthFactors.emplace_back(0.4, 0.1162);
            expectedWidthFactors.emplace_back(0.5, 0.1213);
            expectedWidthFactors.emplace_back(0.6, 0.1168);
            expectedWidthFactors.emplace_back(0.7, 0.1051);
            expectedWidthFactors.emplace_back(0.8, 0.0890);
            expectedWidthFactors.emplace_back(0.9, 0.0712);
            expectedWidthFactors.emplace_back(1.0, 0.0541);
            expectedWidthFactors.emplace_back(1.1, 0.0391);
            expectedWidthFactors.emplace_back(1.2, 0.0269);
            expectedWidthFactors.emplace_back(1.3, 0.0216);
            expectedWidthFactors.emplace_back(1.4, 0.0150);
            expectedWidthFactors.emplace_back(1.5, 0.0105);
            return expectedWidthFactors;
        }

        static vector<tuple<double, double>> GetExpectedDepthFactors()
        {
            auto expectedDepthFactors = vector<tuple<double, double>>();
            expectedDepthFactors.emplace_back(-1, 0.0244);
            expectedDepthFactors.emplace_back(-0.875, 0.0544);
            expectedDepthFactors.emplace_back(-0.750, 0.0938);
            expectedDepthFactors.emplace_back(-0.625, 0.1407);
            expectedDepthFactors.emplace_back(-0.500, 0.1801);
            expectedDepthFactors.emplace_back(-0.375, 0.1632);
            expectedDepthFactors.emplace_back(-0.250, 0.1426);
            expectedDepthFactors.emplace_back(-0.125, 0.0994);
            expectedDepthFactors.emplace_back(0, 0.06);
            expectedDepthFactors.emplace_back(0.125, 0.0244);
            expectedDepthFactors.emplace_back(0.250, 0.0169);
            return expectedDepthFactors;
        }

        static vector<tuple<double, double>> GetExpectedImpactFactors()
        {
            auto expectedImpactFactors = vector<tuple<double, double>>();
            expectedImpactFactors.emplace_back(2, 0.039);
            expectedImpactFactors.emplace_back(2.4, 0.1);
            expectedImpactFactors.emplace_back(2.8, 0.18);
            expectedImpactFactors.emplace_back(3.2, 0.235);
            expectedImpactFactors.emplace_back(3.6, 0.2);
            expectedImpactFactors.emplace_back(4.0, 0.13);
            expectedImpactFactors.emplace_back(4.4, 0.08);
            expectedImpactFactors.emplace_back(4.8, 0.02);
            expectedImpactFactors.emplace_back(5.2, 0.01);
            expectedImpactFactors.emplace_back(5.6, 0.005);
            expectedImpactFactors.emplace_back(6, 0.001);
            return expectedImpactFactors;
        }
    };

    TEST_F(AsphaltRevetmentWaveImpactDefaultsTest, Constructor_ExpectedValues)
    {
        // Call
        const AsphaltRevetmentWaveImpactDefaults defaults;

        // Assert
        AssertHelper::AssertIsInstanceOf<IAsphaltRevetmentWaveImpactDefaults>(&defaults);
        ASSERT_DOUBLE_EQ(0, defaults.GetSubLayerThickness());
        ASSERT_DOUBLE_EQ(1, defaults.GetAverageNumberOfWavesCtm());
        ASSERT_DOUBLE_EQ(0.42, defaults.GetFatigueAlpha());
        ASSERT_DOUBLE_EQ(4.76, defaults.GetFatigueBeta());
        ASSERT_DOUBLE_EQ(1, defaults.GetImpactNumberC());
        ASSERT_DOUBLE_EQ(0.35, defaults.GetStiffnessRelationNu());
        ASSERT_EQ(GetExpectedWidthFactors(), defaults.GetWidthFactors());
        ASSERT_EQ(GetExpectedDepthFactors(), defaults.GetDepthFactors());
        ASSERT_EQ(GetExpectedImpactFactors(), defaults.GetImpactFactors());
    }
}
