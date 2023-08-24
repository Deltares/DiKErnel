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
        Assert.IsInstanceOf<RevetmentLocationConstructionPropertiesBase>(constructionProperties);
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        Assert.AreEqual(x, constructionProperties.GetX());
        Assert.AreEqual(failureTension, constructionProperties.GetFailureTension());
        Assert.AreEqual(soilElasticity, constructionProperties.GetSoilElasticity());
        Assert.AreEqual(thicknessUpperLayer, constructionProperties.GetThicknessUpperLayer());
        Assert.AreEqual(elasticModulusUpperLayer, constructionProperties.GetElasticModulusUpperLayer());
        Assert.IsNull(constructionProperties.GetInitialDamage());
        Assert.IsNull(constructionProperties.GetFailureNumber());
        Assert.IsNull(constructionProperties.GetDensityOfWater());
        Assert.IsNull(constructionProperties.GetThicknessSubLayer());
        Assert.IsNull(constructionProperties.GetElasticModulusSubLayer());
        Assert.IsNull(constructionProperties.GetAverageNumberOfWavesCtm());
        Assert.IsNull(constructionProperties.GetFatigueAlpha());
        Assert.IsNull(constructionProperties.GetFatigueBeta());
        Assert.IsNull(constructionProperties.GetImpactNumberC());
        Assert.IsNull(constructionProperties.GetStiffnessRelationNu());
        Assert.IsNull(constructionProperties.GetWidthFactors());
        Assert.IsNull(constructionProperties.GetDepthFactors());
        Assert.IsNull(constructionProperties.GetImpactFactors());
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
        constructionProperties.SetInitialDamage(initialDamage));
        constructionProperties.SetFailureNumber(failureNumber));
        constructionProperties.SetDensityOfWater(densityOfWater));
        constructionProperties.SetThicknessSubLayer(thicknessSubLayer));
        constructionProperties.SetElasticModulusSubLayer(elasticModulusSubLayer));
        constructionProperties.SetAverageNumberOfWavesCtm(averageNumberOfWavesCtm));
        constructionProperties.SetFatigueAlpha(fatigueAlpha));
        constructionProperties.SetFatigueBeta(fatigueBeta));
        constructionProperties.SetImpactNumberC(impactNumberC));
        constructionProperties.SetStiffnessRelationNu(stiffnessRelationNu));
        constructionProperties.SetWidthFactors(make_unique<vector<pair<double, double>>>(widthFactors));
        constructionProperties.SetDepthFactors(make_unique<vector<pair<double, double>>>(depthFactors));
        constructionProperties.SetImpactFactors(make_unique<vector<pair<double, double>>>(impactFactors));

        // Then
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        Assert.AreEqual(x, constructionProperties.GetX());
        Assert.AreEqual(failureTension, constructionProperties.GetFailureTension());
        Assert.AreEqual(soilElasticity, constructionProperties.GetSoilElasticity());
        Assert.AreEqual(thicknessUpperLayer, constructionProperties.GetThicknessUpperLayer());
        Assert.AreEqual(elasticModulusUpperLayer, constructionProperties.GetElasticModulusUpperLayer());
        Assert.AreEqual(initialDamage, constructionProperties.GetInitialDamage());
        Assert.AreEqual(failureNumber, constructionProperties.GetFailureNumber());
        Assert.AreEqual(densityOfWater, constructionProperties.GetDensityOfWater());
        Assert.AreEqual(thicknessSubLayer, constructionProperties.GetThicknessSubLayer());
        Assert.AreEqual(elasticModulusSubLayer, constructionProperties.GetElasticModulusSubLayer());
        Assert.AreEqual(averageNumberOfWavesCtm, constructionProperties.GetAverageNumberOfWavesCtm());
        Assert.AreEqual(fatigueAlpha, constructionProperties.GetFatigueAlpha());
        Assert.AreEqual(fatigueBeta, constructionProperties.GetFatigueBeta());
        Assert.AreEqual(impactNumberC, constructionProperties.GetImpactNumberC());
        Assert.AreEqual(stiffnessRelationNu, constructionProperties.GetStiffnessRelationNu());
        ASSERT_EQ(widthFactors, constructionProperties.GetWidthFactors());
        ASSERT_EQ(depthFactors, constructionProperties.GetDepthFactors());
        ASSERT_EQ(impactFactors, constructionProperties.GetImpactFactors());
    }
}
}
