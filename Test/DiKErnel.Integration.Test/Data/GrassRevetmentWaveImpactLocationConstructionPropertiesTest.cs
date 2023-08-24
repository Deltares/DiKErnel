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

using DiKErnel.Integration.Data;
using DiKErnel.Integration.Data.GrassRevetment;
using DiKErnel.Integration.Data.GrassRevetmentWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data
{
    [TestFixture]
    public class GrassRevetmentWaveImpactLocationConstructionPropertiesTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            var topLayerType = Random.NextEnumValue<GrassRevetmentTopLayerType>();
            double x = Random.NextDouble();

            // Call
            var constructionProperties = new GrassRevetmentWaveImpactLocationConstructionProperties(x, topLayerType);

            // Assert
            Assert.IsInstanceOf<RevetmentLocationConstructionPropertiesBase>(constructionProperties);
            Assert.AreEqual(topLayerType, constructionProperties.TopLayerType);
            Assert.AreEqual(x, constructionProperties.X);
            Assert.IsNull(constructionProperties.InitialDamage);
            Assert.IsNull(constructionProperties.FailureNumber);
            Assert.IsNull(constructionProperties.TimeLineAgwi);
            Assert.IsNull(constructionProperties.TimeLineBgwi);
            Assert.IsNull(constructionProperties.TimeLineCgwi);
            Assert.IsNull(constructionProperties.MinimumWaveHeightTemax);
            Assert.IsNull(constructionProperties.MaximumWaveHeightTemin);
            Assert.IsNull(constructionProperties.WaveAngleImpactNwa);
            Assert.IsNull(constructionProperties.WaveAngleImpactQwa);
            Assert.IsNull(constructionProperties.WaveAngleImpactRwa);
            Assert.IsNull(constructionProperties.UpperLimitLoadingAul);
            Assert.IsNull(constructionProperties.LowerLimitLoadingAll);
        }

        [Test]
        public void GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassRevetmentTopLayerType>();
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

            var constructionProperties = new GrassRevetmentWaveImpactLocationConstructionProperties(x, topLayerType);

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
            Assert.AreEqual(topLayerType, constructionProperties.TopLayerType);
            Assert.AreEqual(x, constructionProperties.X);
            Assert.AreEqual(initialDamage, constructionProperties.InitialDamage);
            Assert.AreEqual(failureNumber, constructionProperties.FailureNumber);
            Assert.AreEqual(timeLineAgwi, constructionProperties.TimeLineAgwi);
            Assert.AreEqual(timeLineBgwi, constructionProperties.TimeLineBgwi);
            Assert.AreEqual(timeLineCgwi, constructionProperties.TimeLineCgwi);
            Assert.AreEqual(minimumWaveHeightTemax, constructionProperties.MinimumWaveHeightTemax);
            Assert.AreEqual(maximumWaveHeightTemin, constructionProperties.MaximumWaveHeightTemin);
            Assert.AreEqual(waveAngleImpactNwa, constructionProperties.WaveAngleImpactNwa);
            Assert.AreEqual(waveAngleImpactQwa, constructionProperties.WaveAngleImpactQwa);
            Assert.AreEqual(waveAngleImpactRwa, constructionProperties.WaveAngleImpactRwa);
            Assert.AreEqual(upperLimitLoadingAul, constructionProperties.UpperLimitLoadingAul);
            Assert.AreEqual(lowerLimitLoadingAll, constructionProperties.LowerLimitLoadingAll);
        }
    }
}