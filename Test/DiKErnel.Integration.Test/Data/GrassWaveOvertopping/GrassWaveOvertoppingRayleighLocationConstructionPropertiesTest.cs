// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
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
using DiKErnel.Integration.Data.GrassWaveOvertopping;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.GrassWaveOvertopping
{
    [TestFixture]
    internal sealed class GrassWaveOvertoppingRayleighLocationConstructionPropertiesTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            double x = Random.NextDouble();

            // Call
            var constructionProperties = new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                x, topLayerType);

            // Assert
            Assert.That(constructionProperties, Is.InstanceOf<GrassCumulativeOverloadLocationConstructionProperties>());
            Assert.That(constructionProperties.TopLayerType, Is.EqualTo(topLayerType));
            Assert.That(constructionProperties.X, Is.EqualTo(x));
            Assert.That(constructionProperties.InitialDamage, Is.Null);
            Assert.That(constructionProperties.FailureNumber, Is.Null);
            Assert.That(constructionProperties.CriticalCumulativeOverload, Is.Null);
            Assert.That(constructionProperties.CriticalFrontVelocity, Is.Null);
            Assert.That(constructionProperties.IncreasedLoadTransitionAlphaM, Is.Null);
            Assert.That(constructionProperties.ReducedStrengthTransitionAlphaS, Is.Null);
            Assert.That(constructionProperties.AverageNumberOfWavesCtm, Is.Null);
            Assert.That(constructionProperties.FrontVelocityCwo, Is.Null);
            Assert.That(constructionProperties.AccelerationAlphaAForCrest, Is.Null);
            Assert.That(constructionProperties.AccelerationAlphaAForInnerSlope, Is.Null);
            Assert.That(constructionProperties.DikeHeight, Is.Null);
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
            double frontVelocityCwo = Random.NextDouble();
            double accelerationAlphaAForCrest = Random.NextDouble();
            double accelerationAlphaAForInnerSlope = Random.NextDouble();
            double dikeHeight = Random.NextDouble();

            var constructionProperties = new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                x, topLayerType);

            // When
            constructionProperties.InitialDamage = initialDamage;
            constructionProperties.FailureNumber = failureNumber;
            constructionProperties.CriticalCumulativeOverload = criticalCumulativeOverload;
            constructionProperties.CriticalFrontVelocity = criticalFrontVelocity;
            constructionProperties.IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM;
            constructionProperties.ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS;
            constructionProperties.AverageNumberOfWavesCtm = averageNumberOfWavesCtm;
            constructionProperties.FrontVelocityCwo = frontVelocityCwo;
            constructionProperties.AccelerationAlphaAForCrest = accelerationAlphaAForCrest;
            constructionProperties.AccelerationAlphaAForInnerSlope = accelerationAlphaAForInnerSlope;
            constructionProperties.DikeHeight = dikeHeight;

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
            Assert.That(constructionProperties.FrontVelocityCwo, Is.EqualTo(frontVelocityCwo));
            Assert.That(constructionProperties.AccelerationAlphaAForCrest, Is.EqualTo(accelerationAlphaAForCrest));
            Assert.That(constructionProperties.AccelerationAlphaAForInnerSlope, Is.EqualTo(accelerationAlphaAForInnerSlope));
            Assert.That(constructionProperties.DikeHeight, Is.EqualTo(dikeHeight));
        }
    }
}