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

using DiKErnel.Core.Data;
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.Output
{
    [TestFixture]
    public class AsphaltRevetmentWaveImpactTimeDependentOutputConstructionPropertiesTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Call
            var constructionProperties = new AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties();

            // Assert
            Assert.IsInstanceOf<TimeDependentOutputConstructionProperties>(constructionProperties);
            Assert.IsNull(constructionProperties.IncrementDamage);
            Assert.IsNull(constructionProperties.Damage);
            Assert.IsNull(constructionProperties.TimeOfFailure);
            Assert.IsNull(constructionProperties.LogFailureTension);
            Assert.IsNull(constructionProperties.MaximumPeakStress);
            Assert.IsNull(constructionProperties.StiffnessRelation);
            Assert.IsNull(constructionProperties.ComputationalThickness);
            Assert.IsNull(constructionProperties.EquivalentElasticModulus);
            Assert.IsNull(constructionProperties.AverageNumberOfWaves);
        }

        [Test]
        public void GivenConstructionProperties_WhenAllValuesSet_ThenExpectedValues()
        {
            // Given
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            int timeOfFailure = Random.Next();
            double logFailureTension = Random.NextDouble();
            double maximumPeakStress = Random.NextDouble();
            double stiffnessRelation = Random.NextDouble();
            double computationalThickness = Random.NextDouble();
            double equivalentElasticModulus = Random.NextDouble();
            double averageNumberOfWaves = Random.NextDouble();

            // When
            var constructionProperties = new AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = timeOfFailure,
                LogFailureTension = logFailureTension,
                MaximumPeakStress = maximumPeakStress,
                StiffnessRelation = stiffnessRelation,
                ComputationalThickness = computationalThickness,
                EquivalentElasticModulus = equivalentElasticModulus,
                AverageNumberOfWaves = averageNumberOfWaves
            };

            // Then
            Assert.IsInstanceOf<TimeDependentOutputConstructionProperties>(constructionProperties);
            Assert.AreEqual(incrementDamage, constructionProperties.IncrementDamage);
            Assert.AreEqual(damage, constructionProperties.Damage);
            Assert.AreEqual(timeOfFailure, constructionProperties.TimeOfFailure);
            Assert.AreEqual(logFailureTension, constructionProperties.LogFailureTension);
            Assert.AreEqual(maximumPeakStress, constructionProperties.MaximumPeakStress);
            Assert.AreEqual(stiffnessRelation, constructionProperties.StiffnessRelation);
            Assert.AreEqual(computationalThickness, constructionProperties.ComputationalThickness);
            Assert.AreEqual(equivalentElasticModulus, constructionProperties.EquivalentElasticModulus);
            Assert.AreEqual(averageNumberOfWaves, constructionProperties.AverageNumberOfWaves);
        }
    }
}