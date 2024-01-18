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

using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data
{
    [TestFixture]
    public class GrassWaveRunupRayleighDiscreteLocationConstructionPropertiesTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            double x = Random.NextDouble();

            // Call
            var constructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                x, topLayerType);

            // Assert
            Assert.That(constructionProperties, Is.InstanceOf<GrassWaveRunupLocationConstructionProperties>());
            Assert.That(constructionProperties.TopLayerType, Is.EqualTo(topLayerType));
            Assert.That(constructionProperties.X, Is.EqualTo(x));
            Assert.That(constructionProperties.InitialDamage, Is.Null);
            Assert.That(constructionProperties.FailureNumber, Is.Null);
            Assert.That(constructionProperties.CriticalCumulativeOverload, Is.Null);
            Assert.That(constructionProperties.CriticalFrontVelocity, Is.Null);
            Assert.That(constructionProperties.IncreasedLoadTransitionAlphaM, Is.Null);
            Assert.That(constructionProperties.ReducedStrengthTransitionAlphaS, Is.Null);
            Assert.That(constructionProperties.AverageNumberOfWavesCtm, Is.Null);
            Assert.That(constructionProperties.FixedNumberOfWaves, Is.Null);
            Assert.That(constructionProperties.FrontVelocityCu, Is.Null);
        }

        [Test]
        public void GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            double x = Random.NextDouble();
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double criticalCumulativeOverload = Random.NextDouble();
            double criticalFrontVelocity = Random.NextDouble();
            double increasedLoadTransitionAlphaM = Random.NextDouble();
            double reducedStrengthTransitionAlphaS = Random.NextDouble();
            double averageNumberOfWavesCtm = Random.NextDouble();
            int fixedNumberOfWaves = Random.Next();
            double frontVelocityCu = Random.NextDouble();

            var constructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                x, topLayerType);

            // When
            constructionProperties.InitialDamage = initialDamage;
            constructionProperties.FailureNumber = failureNumber;
            constructionProperties.CriticalCumulativeOverload = criticalCumulativeOverload;
            constructionProperties.CriticalFrontVelocity = criticalFrontVelocity;
            constructionProperties.IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM;
            constructionProperties.ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS;
            constructionProperties.AverageNumberOfWavesCtm = averageNumberOfWavesCtm;
            constructionProperties.FixedNumberOfWaves = fixedNumberOfWaves;
            constructionProperties.FrontVelocityCu = frontVelocityCu;

            // Then
            Assert.That(constructionProperties.TopLayerType, Is.EqualTo(topLayerType));
            Assert.That(constructionProperties.X, Is.EqualTo(x));
            Assert.That(constructionProperties.InitialDamage, Is.EqualTo(initialDamage));
            Assert.That(constructionProperties.FailureNumber, Is.EqualTo(failureNumber));
            Assert.That(constructionProperties.CriticalCumulativeOverload, Is.EqualTo(criticalCumulativeOverload));
            Assert.That(constructionProperties.CriticalFrontVelocity, Is.EqualTo(criticalFrontVelocity));
            Assert.That(constructionProperties.IncreasedLoadTransitionAlphaM, Is.EqualTo(increasedLoadTransitionAlphaM));
            Assert.That(constructionProperties.ReducedStrengthTransitionAlphaS, Is.EqualTo(reducedStrengthTransitionAlphaS));
            Assert.That(constructionProperties.AverageNumberOfWavesCtm, Is.EqualTo(averageNumberOfWavesCtm));
            Assert.That(constructionProperties.FixedNumberOfWaves, Is.EqualTo(fixedNumberOfWaves));
            Assert.That(constructionProperties.FrontVelocityCu, Is.EqualTo(frontVelocityCu));
        }
    }
}