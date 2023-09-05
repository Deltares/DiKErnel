// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

using DiKErnel.Integration.Data;
using DiKErnel.Integration.Data.GrassRevetment;
using DiKErnel.Integration.Data.GrassRevetmentOvertopping;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data
{
    [TestFixture]
    public class GrassRevetmentOvertoppingLocationConstructionPropertiesTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            var topLayerType = Random.NextEnumValue<GrassRevetmentTopLayerType>();
            double x = Random.NextDouble();

            // Call
            var constructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(x, topLayerType);

            // Assert
            Assert.IsInstanceOf<RevetmentLocationConstructionPropertiesBase>(constructionProperties);
            Assert.AreEqual(topLayerType, constructionProperties.TopLayerType);
            Assert.AreEqual(x, constructionProperties.X);
            Assert.IsNull(constructionProperties.InitialDamage);
            Assert.IsNull(constructionProperties.FailureNumber);
            Assert.IsNull(constructionProperties.CriticalCumulativeOverload);
            Assert.IsNull(constructionProperties.CriticalFrontVelocity);
            Assert.IsNull(constructionProperties.IncreasedLoadTransitionAlphaM);
            Assert.IsNull(constructionProperties.ReducedStrengthTransitionAlphaS);
            Assert.IsNull(constructionProperties.AverageNumberOfWavesCtm);
            Assert.IsNull(constructionProperties.FixedNumberOfWaves);
            Assert.IsNull(constructionProperties.FrontVelocityCwo);
            Assert.IsNull(constructionProperties.AccelerationAlphaAForCrest);
            Assert.IsNull(constructionProperties.AccelerationAlphaAForInnerSlope);
            Assert.IsNull(constructionProperties.DikeHeight);
        }

        [Test]
        public void GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassRevetmentTopLayerType>();
            double x = Random.NextDouble();
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double criticalCumulativeOverload = Random.NextDouble();
            double criticalFrontVelocity = Random.NextDouble();
            double increasedLoadTransitionAlphaM = Random.NextDouble();
            double reducedStrengthTransitionAlphaS = Random.NextDouble();
            double averageNumberOfWavesCtm = Random.NextDouble();
            int fixedNumberOfWaves = Random.Next();
            double frontVelocityCwo = Random.NextDouble();
            double accelerationAlphaAForCrest = Random.NextDouble();
            double accelerationAlphaAForInnerSlope = Random.NextDouble();
            double dikeHeight = Random.NextDouble();

            var constructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(x, topLayerType);

            // When
            constructionProperties.InitialDamage = initialDamage;
            constructionProperties.FailureNumber = failureNumber;
            constructionProperties.CriticalCumulativeOverload = criticalCumulativeOverload;
            constructionProperties.CriticalFrontVelocity = criticalFrontVelocity;
            constructionProperties.IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM;
            constructionProperties.ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS;
            constructionProperties.AverageNumberOfWavesCtm = averageNumberOfWavesCtm;
            constructionProperties.FixedNumberOfWaves = fixedNumberOfWaves;
            constructionProperties.FrontVelocityCwo = frontVelocityCwo;
            constructionProperties.AccelerationAlphaAForCrest = accelerationAlphaAForCrest;
            constructionProperties.AccelerationAlphaAForInnerSlope = accelerationAlphaAForInnerSlope;
            constructionProperties.DikeHeight = dikeHeight;

            // Then
            Assert.AreEqual(topLayerType, constructionProperties.TopLayerType);
            Assert.AreEqual(x, constructionProperties.X);
            Assert.AreEqual(initialDamage, constructionProperties.InitialDamage);
            Assert.AreEqual(failureNumber, constructionProperties.FailureNumber);
            Assert.AreEqual(criticalCumulativeOverload, constructionProperties.CriticalCumulativeOverload);
            Assert.AreEqual(criticalFrontVelocity, constructionProperties.CriticalFrontVelocity);
            Assert.AreEqual(increasedLoadTransitionAlphaM, constructionProperties.IncreasedLoadTransitionAlphaM);
            Assert.AreEqual(reducedStrengthTransitionAlphaS, constructionProperties.ReducedStrengthTransitionAlphaS);
            Assert.AreEqual(averageNumberOfWavesCtm, constructionProperties.AverageNumberOfWavesCtm);
            Assert.AreEqual(fixedNumberOfWaves, constructionProperties.FixedNumberOfWaves);
            Assert.AreEqual(frontVelocityCwo, constructionProperties.FrontVelocityCwo);
            Assert.AreEqual(accelerationAlphaAForCrest, constructionProperties.AccelerationAlphaAForCrest);
            Assert.AreEqual(accelerationAlphaAForInnerSlope, constructionProperties.AccelerationAlphaAForInnerSlope);
            Assert.AreEqual(dikeHeight, constructionProperties.DikeHeight);
        }
    }
}