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

#include "AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.h"

namespace DiKErnel::Integration::TestUtil
{
    using namespace std;

    void AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
        const double x,
        const double outerSlope,
        const double failureTension,
        const double densityOfWater,
        const double soilElasticity,
        const double averageNumberOfWavesCtm,
        const double impactNumberC,
        const double stiffnessRelationNu,
        const AsphaltRevetmentWaveImpactLocationDependentInput& locationDependentInput)
    {
        ASSERT_DOUBLE_EQ(outerSlope, locationDependentInput.GetOuterSlope());
        ASSERT_DOUBLE_EQ(x, locationDependentInput.GetX());
        ASSERT_DOUBLE_EQ(failureTension, locationDependentInput.GetFailureTension());
        ASSERT_DOUBLE_EQ(densityOfWater, locationDependentInput.GetDensityOfWater());
        ASSERT_DOUBLE_EQ(soilElasticity, locationDependentInput.GetSoilElasticity());
        ASSERT_DOUBLE_EQ(averageNumberOfWavesCtm, locationDependentInput.GetAverageNumberOfWavesCtm());
        ASSERT_DOUBLE_EQ(impactNumberC, locationDependentInput.GetImpactNumberC());
        ASSERT_DOUBLE_EQ(stiffnessRelationNu, locationDependentInput.GetStiffnessRelationNu());
    }

    void AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(
        const double thickness,
        const double elasticModulus,
        const AsphaltRevetmentWaveImpactLayer& layer)
    {
        ASSERT_DOUBLE_EQ(thickness, layer.GetThickness());
        ASSERT_DOUBLE_EQ(elasticModulus, layer.GetElasticModulus());
    }

    void AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFatigue(
        const double alpha,
        const double beta,
        const AsphaltRevetmentWaveImpactFatigue& fatigue)
    {
        ASSERT_DOUBLE_EQ(alpha, fatigue.GetAlpha());
        ASSERT_DOUBLE_EQ(beta, fatigue.GetBeta());
    }

    void AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFactors(
        const vector<tuple<double, double>>& widthFactors,
        const vector<tuple<double, double>>& depthFactors,
        const vector<tuple<double, double>>& impactFactors,
        const AsphaltRevetmentWaveImpactLocationDependentInput& locationDependentInput)
    {
        ASSERT_EQ(widthFactors, locationDependentInput.GetWidthFactors());
        ASSERT_EQ(depthFactors, locationDependentInput.GetDepthFactors());
        ASSERT_EQ(impactFactors, locationDependentInput.GetImpactFactors());
    }
}
