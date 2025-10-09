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
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.AsphaltWaveImpact
{
    [TestFixture]
    internal sealed class AsphaltWaveImpactTimeDependentOutputTest
    {
        [Test]
        public void Constructor_WithAllValuesSet_ExpectedValues()
        {
            // Setup
            double incrementDamage = Random.NextDouble();
            double maximumPeakStress = Random.NextDouble();
            double averageNumberOfWaves = Random.NextDouble();

            var constructionProperties = new AsphaltWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                MaximumPeakStress = maximumPeakStress,
                AverageNumberOfWaves = averageNumberOfWaves
            };

            // Call
            var output = new AsphaltWaveImpactTimeDependentOutput(constructionProperties);

            // Assert
            Assert.That(output, Is.InstanceOf<TimeDependentOutput>());
            Assert.That(output.IncrementDamage, Is.EqualTo(incrementDamage));
            Assert.That(output.MaximumPeakStress, Is.EqualTo(maximumPeakStress));
            Assert.That(output.AverageNumberOfWaves, Is.EqualTo(averageNumberOfWaves));
        }

        [Test]
        public void Constructor_MaximumPeakStressNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            AsphaltWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.MaximumPeakStress = null;

            // Call
            void Call()
            {
                var output = new AsphaltWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "MaximumPeakStress must be set.");
        }

        [Test]
        public void Constructor_AverageNumberOfWavesNull_ThrowsInvalidTimeDependentOutputException()
        {
            // Setup
            AsphaltWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.AverageNumberOfWaves = null;

            // Call
            void Call()
            {
                var output = new AsphaltWaveImpactTimeDependentOutput(constructionProperties);
            }

            // Assert
            AssertHelper.AssertException<InvalidTimeDependentOutputException>(Call,
                                                                              "AverageNumberOfWaves must be set.");
        }

        private static AsphaltWaveImpactTimeDependentOutputConstructionProperties CreateFullyConfiguredConstructionProperties()
        {
            return new AsphaltWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = Random.NextDouble(),
                MaximumPeakStress = Random.NextDouble(),
                AverageNumberOfWaves = Random.NextDouble()
            };
        }
    }
}