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
using DiKErnel.Core.Exceptions;
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.Output
{
    [TestFixture]
    public class AsphaltRevetmentWaveImpactTimeDependentOutputTest
    {
        [Test]
        public void Constructor_WithAllValuesSet_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            int timeOfFailure = Random.Next();
            double logFailureTension = Random.NextDouble();
            double maximumPeakStress = Random.NextDouble();
            double stiffnessRelation = Random.NextDouble();
            double computationalThickness = Random.NextDouble();
            double equivalentElasticModulus = Random.NextDouble();
            double averageNumberOfWaves = Random.NextDouble();

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

            // Call
            var output = new AsphaltRevetmentWaveImpactTimeDependentOutput(constructionProperties);

            // Assert
            Assert.IsInstanceOf<TimeDependentOutput>(output);
            Assert.AreEqual(incrementDamage, output.IncrementDamage);
            Assert.AreEqual(damage, output.Damage);
            Assert.AreEqual(timeOfFailure, output.TimeOfFailure);
            Assert.AreEqual(logFailureTension, output.LogFailureTension);
            Assert.AreEqual(maximumPeakStress, output.MaximumPeakStress);
            Assert.AreEqual(stiffnessRelation, output.StiffnessRelation);
            Assert.AreEqual(computationalThickness, output.ComputationalThickness);
            Assert.AreEqual(equivalentElasticModulus, output.EquivalentElasticModulus);
            Assert.AreEqual(averageNumberOfWaves, output.AverageNumberOfWaves);
        }

        [Test]
        public void Constructor_WithNullValues_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            double damage = Random.NextDouble();
            double logFailureTension = Random.NextDouble();
            double maximumPeakStress = Random.NextDouble();
            double stiffnessRelation = Random.NextDouble();
            double computationalThickness = Random.NextDouble();
            double equivalentElasticModulus = Random.NextDouble();
            double averageNumberOfWaves = Random.NextDouble();

            var constructionProperties = new AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = null,
                LogFailureTension = logFailureTension,
                MaximumPeakStress = maximumPeakStress,
                StiffnessRelation = stiffnessRelation,
                ComputationalThickness = computationalThickness,
                EquivalentElasticModulus = equivalentElasticModulus,
                AverageNumberOfWaves = averageNumberOfWaves
            };

            // Call
            var output = new AsphaltRevetmentWaveImpactTimeDependentOutput(constructionProperties);

            // Assert
            Assert.IsInstanceOf<TimeDependentOutput>(output);
            Assert.AreEqual(incrementDamage, output.IncrementDamage);
            Assert.AreEqual(damage, output.Damage);
            Assert.IsNull(output.TimeOfFailure);
            Assert.AreEqual(logFailureTension, output.LogFailureTension);
            Assert.AreEqual(maximumPeakStress, output.MaximumPeakStress);
            Assert.AreEqual(stiffnessRelation, output.StiffnessRelation);
            Assert.AreEqual(computationalThickness, output.ComputationalThickness);
            Assert.AreEqual(equivalentElasticModulus, output.EquivalentElasticModulus);
            Assert.AreEqual(averageNumberOfWaves, output.AverageNumberOfWaves);
        }

        [Test]
        public void Constructor_LogFailureTensionNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.LogFailureTension = null;

            // Call
            void Call()
            {
                var output = new AsphaltRevetmentWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "logFailureTension must be set.");
        }

        [Test]
        public void Constructor_MaximumPeakStressNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.MaximumPeakStress = null;

            // Call
            void Call()
            {
                var output = new AsphaltRevetmentWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "maximumPeakStress must be set.");
        }

        [Test]
        public void Constructor_StiffnessRelationNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.StiffnessRelation = null;

            // Call
            void Call()
            {
                var output = new AsphaltRevetmentWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "stiffnessRelation must be set.");
        }

        [Test]
        public void Constructor_ComputationalThicknessNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.ComputationalThickness = null;

            // Call
            void Call()
            {
                var output = new AsphaltRevetmentWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "computationalThickness must be set.");
        }

        [Test]
        public void Constructor_EquivalentElasticModulusNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.EquivalentElasticModulus = null;

            // Call
            void Call()
            {
                var output = new AsphaltRevetmentWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "equivalentElasticModulus must be set.");
        }
        
        [Test]
        public void Constructor_AverageNumberOfWavesNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.AverageNumberOfWaves = null;

            // Call
            void Call()
            {
                var output = new AsphaltRevetmentWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            Assert.Throws<InvalidTimeDependentOutputException>(Call, "equivalentElasticModulus must be set.");
        }


        private static AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties CreateFullyConfiguredConstructionProperties()
        {
            return new AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = Random.NextDouble(),
                Damage = Random.NextDouble(),
                TimeOfFailure = Random.Next(),
                LogFailureTension = Random.NextDouble(),
                MaximumPeakStress = Random.NextDouble(),
                StiffnessRelation = Random.NextDouble(),
                ComputationalThickness = Random.NextDouble(),
                EquivalentElasticModulus = Random.NextDouble(),
                AverageNumberOfWaves = Random.NextDouble()
            };
        }
    }
}