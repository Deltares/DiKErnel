// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System.Collections.Generic;
using DiKErnel.Integration.Data;
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;
using DiKErnel.TestUtil;
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
            var topLayerType = Random.NextEnumValue<AsphaltRevetmentTopLayerType>();
            double x = Random.NextDouble();
            double flexuralStrength = Random.NextDouble();
            double soilElasticity = Random.NextDouble();
            double thicknessUpperLayer = Random.NextDouble();
            double elasticModulusUpperLayer = Random.NextDouble();

            // Call
            var constructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                x, topLayerType, flexuralStrength, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer);

            // Assert
            Assert.That(constructionProperties, Is.InstanceOf<RevetmentLocationConstructionProperties>());
            Assert.That(constructionProperties.TopLayerType, Is.EqualTo(topLayerType));
            Assert.That(constructionProperties.X, Is.EqualTo(x));
            Assert.That(constructionProperties.FlexuralStrength, Is.EqualTo(flexuralStrength));
            Assert.That(constructionProperties.SoilElasticity, Is.EqualTo(soilElasticity));
            Assert.That(constructionProperties.ThicknessUpperLayer, Is.EqualTo(thicknessUpperLayer));
            Assert.That(constructionProperties.ElasticModulusUpperLayer, Is.EqualTo(elasticModulusUpperLayer));
            Assert.IsNull(constructionProperties.InitialDamage);
            Assert.IsNull(constructionProperties.FailureNumber);
            Assert.IsNull(constructionProperties.DensityOfWater);
            Assert.IsNull(constructionProperties.ThicknessSubLayer);
            Assert.IsNull(constructionProperties.ElasticModulusSubLayer);
            Assert.IsNull(constructionProperties.AverageNumberOfWavesCtm);
            Assert.IsNull(constructionProperties.FatigueAlpha);
            Assert.IsNull(constructionProperties.FatigueBeta);
            Assert.IsNull(constructionProperties.ImpactNumberC);
            Assert.IsNull(constructionProperties.StiffnessRelationNu);
            Assert.IsNull(constructionProperties.WidthFactors);
            Assert.IsNull(constructionProperties.DepthFactors);
            Assert.IsNull(constructionProperties.ImpactFactors);
        }

        [Test]
        public void GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues()
        {
            // Given
            var topLayerType = Random.NextEnumValue<AsphaltRevetmentTopLayerType>();
            double x = Random.NextDouble();
            double flexuralStrength = Random.NextDouble();
            double soilElasticity = Random.NextDouble();
            double thicknessUpperLayer = Random.NextDouble();
            double elasticModulusUpperLayer = Random.NextDouble();
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double densityOfWater = Random.NextDouble();
            double thicknessSubLayer = Random.NextDouble();
            double elasticModulusSubLayer = Random.NextDouble();
            double averageNumberOfWavesCtm = Random.NextDouble();
            double fatigueAlpha = Random.NextDouble();
            double fatigueBeta = Random.NextDouble();
            double impactNumberC = Random.NextDouble();
            double stiffnessRelationNu = Random.NextDouble();
            var widthFactors = new List<(double, double)>
            {
                (Random.NextDouble(), Random.NextDouble())
            };
            var depthFactors = new List<(double, double)>
            {
                (Random.NextDouble(), Random.NextDouble())
            };
            var impactFactors = new List<(double, double)>
            {
                (Random.NextDouble(), Random.NextDouble())
            };

            var constructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                x, topLayerType, flexuralStrength, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer);

            // When
            constructionProperties.InitialDamage = initialDamage;
            constructionProperties.FailureNumber = failureNumber;
            constructionProperties.DensityOfWater = densityOfWater;
            constructionProperties.ThicknessSubLayer = thicknessSubLayer;
            constructionProperties.ElasticModulusSubLayer = elasticModulusSubLayer;
            constructionProperties.AverageNumberOfWavesCtm = averageNumberOfWavesCtm;
            constructionProperties.FatigueAlpha = fatigueAlpha;
            constructionProperties.FatigueBeta = fatigueBeta;
            constructionProperties.ImpactNumberC = impactNumberC;
            constructionProperties.StiffnessRelationNu = stiffnessRelationNu;
            constructionProperties.WidthFactors = widthFactors;
            constructionProperties.DepthFactors = depthFactors;
            constructionProperties.ImpactFactors = impactFactors;

            // Then
            Assert.That(constructionProperties.TopLayerType, Is.EqualTo(topLayerType));
            Assert.That(constructionProperties.X, Is.EqualTo(x));
            Assert.That(constructionProperties.FlexuralStrength, Is.EqualTo(flexuralStrength));
            Assert.That(constructionProperties.SoilElasticity, Is.EqualTo(soilElasticity));
            Assert.That(constructionProperties.ThicknessUpperLayer, Is.EqualTo(thicknessUpperLayer));
            Assert.That(constructionProperties.ElasticModulusUpperLayer, Is.EqualTo(elasticModulusUpperLayer));
            Assert.That(constructionProperties.InitialDamage, Is.EqualTo(initialDamage));
            Assert.That(constructionProperties.FailureNumber, Is.EqualTo(failureNumber));
            Assert.That(constructionProperties.DensityOfWater, Is.EqualTo(densityOfWater));
            Assert.That(constructionProperties.ThicknessSubLayer, Is.EqualTo(thicknessSubLayer));
            Assert.That(constructionProperties.ElasticModulusSubLayer, Is.EqualTo(elasticModulusSubLayer));
            Assert.That(constructionProperties.AverageNumberOfWavesCtm, Is.EqualTo(averageNumberOfWavesCtm));
            Assert.That(constructionProperties.FatigueAlpha, Is.EqualTo(fatigueAlpha));
            Assert.That(constructionProperties.FatigueBeta, Is.EqualTo(fatigueBeta));
            Assert.That(constructionProperties.ImpactNumberC, Is.EqualTo(impactNumberC));
            Assert.That(constructionProperties.StiffnessRelationNu, Is.EqualTo(stiffnessRelationNu));
            CollectionAssert.AreEqual(widthFactors, constructionProperties.WidthFactors);
            CollectionAssert.AreEqual(depthFactors, constructionProperties.DepthFactors);
            CollectionAssert.AreEqual(impactFactors, constructionProperties.ImpactFactors);
        }
    }
}