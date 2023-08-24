// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data
{
    [TestFixture]
    public class AsphaltRevetmentWaveImpactLocationConstructionPropertiesTest
    {
        
    }

        [Test]
    public void Constructor_ExpectedValues()
    {
        // Setup
        var topLayerType = AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete;
        var x = 0.1;
        var failureTension = 0.2;
        var soilElasticity = 0.3;
        var thicknessUpperLayer = 0.4;
        var elasticModulusUpperLayer = 0.5;

        // Call
        const AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties(
            x, topLayerType, failureTension, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer);

        // Assert
        AssertHelper::AssertIsInstanceOf<RevetmentLocationConstructionPropertiesBase>(&constructionProperties);
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_DOUBLE_EQ(failureTension, constructionProperties.GetFailureTension());
        ASSERT_DOUBLE_EQ(soilElasticity, constructionProperties.GetSoilElasticity());
        ASSERT_DOUBLE_EQ(thicknessUpperLayer, constructionProperties.GetThicknessUpperLayer());
        ASSERT_DOUBLE_EQ(elasticModulusUpperLayer, constructionProperties.GetElasticModulusUpperLayer());
        ASSERT_EQ(nullptr, constructionProperties.GetInitialDamage());
        ASSERT_EQ(nullptr, constructionProperties.GetFailureNumber());
        ASSERT_EQ(nullptr, constructionProperties.GetDensityOfWater());
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

        [Test]
    public void GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues()
    {
        // Given
        var topLayerType = AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete;
        var x = 0.1;
        var failureTension = 0.2;
        var soilElasticity = 0.3;
        var thicknessUpperLayer = 0.4;
        var elasticModulusUpperLayer = 0.5;
        var initialDamage = 0.6;
        var failureNumber = 0.7;
        var densityOfWater = 0.8;
        var thicknessSubLayer = 0.9;
        var elasticModulusSubLayer = 1.0;
        var averageNumberOfWavesCtm = 1.1;
        var fatigueAlpha = 1.2;
        var fatigueBeta = 1.3;
        var impactNumberC = 1.4;
        var stiffnessRelationNu = 1.5;
        const var widthFactors = vector
        {
            pair(1.6, 1.7)
        };
        const var depthFactors = vector
        {
            pair(1.8, 1.9)
        };
        const var impactFactors = vector
        {
            pair(2.0, 2.1)
        };

        AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties(
            x, topLayerType, failureTension, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer);

        // When
        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties.SetDensityOfWater(make_unique<double>(densityOfWater));
        constructionProperties.SetThicknessSubLayer(make_unique<double>(thicknessSubLayer));
        constructionProperties.SetElasticModulusSubLayer(make_unique<double>(elasticModulusSubLayer));
        constructionProperties.SetAverageNumberOfWavesCtm(make_unique<double>(averageNumberOfWavesCtm));
        constructionProperties.SetFatigueAlpha(make_unique<double>(fatigueAlpha));
        constructionProperties.SetFatigueBeta(make_unique<double>(fatigueBeta));
        constructionProperties.SetImpactNumberC(make_unique<double>(impactNumberC));
        constructionProperties.SetStiffnessRelationNu(make_unique<double>(stiffnessRelationNu));
        constructionProperties.SetWidthFactors(make_unique<vector<pair<double, double>>>(widthFactors));
        constructionProperties.SetDepthFactors(make_unique<vector<pair<double, double>>>(depthFactors));
        constructionProperties.SetImpactFactors(make_unique<vector<pair<double, double>>>(impactFactors));

        // Then
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_DOUBLE_EQ(failureTension, constructionProperties.GetFailureTension());
        ASSERT_DOUBLE_EQ(soilElasticity, constructionProperties.GetSoilElasticity());
        ASSERT_DOUBLE_EQ(thicknessUpperLayer, constructionProperties.GetThicknessUpperLayer());
        ASSERT_DOUBLE_EQ(elasticModulusUpperLayer, constructionProperties.GetElasticModulusUpperLayer());
        ASSERT_DOUBLE_EQ(initialDamage, *constructionProperties.GetInitialDamage());
        ASSERT_DOUBLE_EQ(failureNumber, *constructionProperties.GetFailureNumber());
        ASSERT_DOUBLE_EQ(densityOfWater, *constructionProperties.GetDensityOfWater());
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
