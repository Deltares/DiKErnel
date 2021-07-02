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

#include "AsphaltRevetmentWaveImpactLocationConstructionProperties.h"
#include "AssertHelper.h"

namespace DiKErnel::Integration::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(AsphaltRevetmentWaveImpactLocationConstructionPropertiesTest, Constructor_ExpectedValues)
    {
        // Setup
        const auto topLayerType = AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete;
        const string name = "Test";
        const auto tanA = 0.1;
        const auto positionZ = 0.2;
        const auto failureTension = 0.3;
        const auto densityOfWater = 0.4;
        const auto soilElasticity = 0.5;
        const auto thicknessUpperLayer = 0.6;
        const auto elasticModulusUpperLayer = 0.7;

        // Call
        const AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties(
            name, tanA, positionZ, topLayerType, failureTension, densityOfWater, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer);

        // Assert
        AssertHelper::AssertIsInstanceOf<RevetmentLocationConstructionPropertiesBase>(&constructionProperties);
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_EQ(name, constructionProperties.GetName());
        ASSERT_DOUBLE_EQ(tanA, constructionProperties.GetTanA());
        ASSERT_DOUBLE_EQ(positionZ, constructionProperties.GetPositionZ());
        ASSERT_DOUBLE_EQ(failureTension, constructionProperties.GetFailureTension());
        ASSERT_DOUBLE_EQ(densityOfWater, constructionProperties.GetDensityOfWater());
        ASSERT_DOUBLE_EQ(soilElasticity, constructionProperties.GetSoilElasticity());
        ASSERT_DOUBLE_EQ(thicknessUpperLayer, constructionProperties.GetThicknessUpperLayer());
        ASSERT_DOUBLE_EQ(elasticModulusUpperLayer, constructionProperties.GetElasticModulusUpperLayer());
        ASSERT_EQ(nullptr, constructionProperties.GetInitialDamage());
        ASSERT_EQ(nullptr, constructionProperties.GetFailureNumber());
        ASSERT_EQ(nullptr, constructionProperties.GetThicknessSubLayer());
        ASSERT_EQ(nullptr, constructionProperties.GetElasticModulusSubLayer());
        ASSERT_EQ(nullptr, constructionProperties.GetAverageNumberOfWavesCtm());
        ASSERT_EQ(nullptr, constructionProperties.GetFatigueAlpha());
        ASSERT_EQ(nullptr, constructionProperties.GetFatigueBeta());
        ASSERT_EQ(nullptr, constructionProperties.GetImpactNumberC());
        ASSERT_EQ(nullptr, constructionProperties.GetStiffnessRelationNu());
        ASSERT_EQ(nullptr, constructionProperties.GetWidthFactors());
        ASSERT_EQ(nullptr, constructionProperties.GetDepthFactors());
        ASSERT_EQ(nullptr, constructionProperties.GetImpactFactors());
    }

    TEST(AsphaltRevetmentWaveImpactLocationConstructionPropertiesTest, GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues)
    {
        // Given
        const auto topLayerType = AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete;
        const string name = "Test";
        const auto tanA = 0.1;
        const auto positionZ = 0.2;
        const auto failureTension = 0.3;
        const auto densityOfWater = 0.4;
        const auto soilElasticity = 0.5;
        const auto thicknessUpperLayer = 0.6;
        const auto elasticModulusUpperLayer = 0.7;
        const auto initialDamage = 0.8;
        const auto failureNumber = 0.9;
        const auto thicknessSubLayer = 1.0;
        const auto elasticModulusSubLayer = 1.1;
        const auto averageNumberOfWavesCtm = 1.2;
        const auto fatigueAlpha = 1.3;
        const auto fatigueBeta = 1.4;
        const auto impactNumberC = 1.5;
        const auto stiffnessRelationNu = 1.6;
        const auto widthFactors = vector
        {
            tuple(1.7, 1.8)
        };
        const auto depthFactors = vector
        {
            tuple(1.9, 2.0)
        };
        const auto impactFactors = vector
        {
            tuple(2.1, 2.2)
        };

        AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties(
            name, tanA, positionZ, topLayerType, failureTension, densityOfWater, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer);

        // When
        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties.SetThicknessSubLayer(make_unique<double>(thicknessSubLayer));
        constructionProperties.SetElasticModulusSubLayer(make_unique<double>(elasticModulusSubLayer));
        constructionProperties.SetAverageNumberOfWavesCtm(make_unique<double>(averageNumberOfWavesCtm));
        constructionProperties.SetFatigueAlpha(make_unique<double>(fatigueAlpha));
        constructionProperties.SetFatigueBeta(make_unique<double>(fatigueBeta));
        constructionProperties.SetImpactNumberC(make_unique<double>(impactNumberC));
        constructionProperties.SetStiffnessRelationNu(make_unique<double>(stiffnessRelationNu));
        constructionProperties.SetWidthFactors(make_unique<vector<tuple<double, double>>>(widthFactors));
        constructionProperties.SetDepthFactors(make_unique<vector<tuple<double, double>>>(depthFactors));
        constructionProperties.SetImpactFactors(make_unique<vector<tuple<double, double>>>(impactFactors));

        // Then
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_EQ(name, constructionProperties.GetName());
        ASSERT_DOUBLE_EQ(tanA, constructionProperties.GetTanA());
        ASSERT_DOUBLE_EQ(positionZ, constructionProperties.GetPositionZ());
        ASSERT_DOUBLE_EQ(failureTension, constructionProperties.GetFailureTension());
        ASSERT_DOUBLE_EQ(densityOfWater, constructionProperties.GetDensityOfWater());
        ASSERT_DOUBLE_EQ(soilElasticity, constructionProperties.GetSoilElasticity());
        ASSERT_DOUBLE_EQ(thicknessUpperLayer, constructionProperties.GetThicknessUpperLayer());
        ASSERT_DOUBLE_EQ(elasticModulusUpperLayer, constructionProperties.GetElasticModulusUpperLayer());
        ASSERT_DOUBLE_EQ(initialDamage, *constructionProperties.GetInitialDamage());
        ASSERT_DOUBLE_EQ(failureNumber, *constructionProperties.GetFailureNumber());
        ASSERT_DOUBLE_EQ(thicknessSubLayer, *constructionProperties.GetThicknessSubLayer());
        ASSERT_DOUBLE_EQ(elasticModulusSubLayer, *constructionProperties.GetElasticModulusSubLayer());
        ASSERT_DOUBLE_EQ(averageNumberOfWavesCtm, *constructionProperties.GetAverageNumberOfWavesCtm());
        ASSERT_DOUBLE_EQ(fatigueAlpha, *constructionProperties.GetFatigueAlpha());
        ASSERT_DOUBLE_EQ(fatigueBeta, *constructionProperties.GetFatigueBeta());
        ASSERT_DOUBLE_EQ(impactNumberC, *constructionProperties.GetImpactNumberC());
        ASSERT_DOUBLE_EQ(stiffnessRelationNu, *constructionProperties.GetStiffnessRelationNu());
        ASSERT_EQ(widthFactors, *constructionProperties.GetWidthFactors());
        ASSERT_EQ(depthFactors, *constructionProperties.GetDepthFactors());
        ASSERT_EQ(impactFactors, *constructionProperties.GetImpactFactors());
    }
}
