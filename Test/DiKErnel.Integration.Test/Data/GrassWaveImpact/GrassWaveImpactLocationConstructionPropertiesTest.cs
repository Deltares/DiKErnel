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

using DiKErnel.Integration.Data;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.GrassWaveImpact
{
    [TestFixture]
    internal sealed class GrassWaveImpactLocationConstructionPropertiesTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            double x = Random.NextDouble();

            // Call
            var constructionProperties = new GrassWaveImpactLocationConstructionProperties(x, topLayerType);

            // Assert
            Assert.That(constructionProperties, Is.InstanceOf<LocationConstructionProperties>());
            Assert.That(constructionProperties.TopLayerType, Is.EqualTo(topLayerType));
            Assert.That(constructionProperties.X, Is.EqualTo(x));
            Assert.That(constructionProperties.InitialDamage, Is.Null);
            Assert.That(constructionProperties.FailureNumber, Is.Null);
            Assert.That(constructionProperties.TimeLineAgwi, Is.Null);
            Assert.That(constructionProperties.TimeLineBgwi, Is.Null);
            Assert.That(constructionProperties.TimeLineCgwi, Is.Null);
            Assert.That(constructionProperties.MinimumWaveHeightTemax, Is.Null);
            Assert.That(constructionProperties.MaximumWaveHeightTemin, Is.Null);
            Assert.That(constructionProperties.WaveAngleImpactNwa, Is.Null);
            Assert.That(constructionProperties.WaveAngleImpactQwa, Is.Null);
            Assert.That(constructionProperties.WaveAngleImpactRwa, Is.Null);
            Assert.That(constructionProperties.UpperLimitLoadingAul, Is.Null);
            Assert.That(constructionProperties.LowerLimitLoadingAll, Is.Null);
        }

        [Test]
        public void GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            double x = Random.NextDouble();
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double timeLineAgwi = Random.NextDouble();
            double timeLineBgwi = Random.NextDouble();
            double timeLineCgwi = Random.NextDouble();
            double minimumWaveHeightTemax = Random.NextDouble();
            double maximumWaveHeightTemin = Random.NextDouble();
            double waveAngleImpactNwa = Random.NextDouble();
            double waveAngleImpactQwa = Random.NextDouble();
            double waveAngleImpactRwa = Random.NextDouble();
            double upperLimitLoadingAul = Random.NextDouble();
            double lowerLimitLoadingAll = Random.NextDouble();

            var constructionProperties = new GrassWaveImpactLocationConstructionProperties(x, topLayerType);

            // When
            constructionProperties.InitialDamage = initialDamage;
            constructionProperties.FailureNumber = failureNumber;
            constructionProperties.TimeLineAgwi = timeLineAgwi;
            constructionProperties.TimeLineBgwi = timeLineBgwi;
            constructionProperties.TimeLineCgwi = timeLineCgwi;
            constructionProperties.MinimumWaveHeightTemax = minimumWaveHeightTemax;
            constructionProperties.MaximumWaveHeightTemin = maximumWaveHeightTemin;
            constructionProperties.WaveAngleImpactNwa = waveAngleImpactNwa;
            constructionProperties.WaveAngleImpactQwa = waveAngleImpactQwa;
            constructionProperties.WaveAngleImpactRwa = waveAngleImpactRwa;
            constructionProperties.UpperLimitLoadingAul = upperLimitLoadingAul;
            constructionProperties.LowerLimitLoadingAll = lowerLimitLoadingAll;

            // Then
            Assert.That(constructionProperties.TopLayerType, Is.EqualTo(topLayerType));
            Assert.That(constructionProperties.X, Is.EqualTo(x));
            Assert.That(constructionProperties.InitialDamage, Is.EqualTo(initialDamage));
            Assert.That(constructionProperties.FailureNumber, Is.EqualTo(failureNumber));
            Assert.That(constructionProperties.TimeLineAgwi, Is.EqualTo(timeLineAgwi));
            Assert.That(constructionProperties.TimeLineBgwi, Is.EqualTo(timeLineBgwi));
            Assert.That(constructionProperties.TimeLineCgwi, Is.EqualTo(timeLineCgwi));
            Assert.That(constructionProperties.MinimumWaveHeightTemax, Is.EqualTo(minimumWaveHeightTemax));
            Assert.That(constructionProperties.MaximumWaveHeightTemin, Is.EqualTo(maximumWaveHeightTemin));
            Assert.That(constructionProperties.WaveAngleImpactNwa, Is.EqualTo(waveAngleImpactNwa));
            Assert.That(constructionProperties.WaveAngleImpactQwa, Is.EqualTo(waveAngleImpactQwa));
            Assert.That(constructionProperties.WaveAngleImpactRwa, Is.EqualTo(waveAngleImpactRwa));
            Assert.That(constructionProperties.UpperLimitLoadingAul, Is.EqualTo(upperLimitLoadingAul));
            Assert.That(constructionProperties.LowerLimitLoadingAll, Is.EqualTo(lowerLimitLoadingAll));
        }
    }
}