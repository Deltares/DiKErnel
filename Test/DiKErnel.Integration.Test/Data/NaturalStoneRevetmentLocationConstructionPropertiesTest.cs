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

using DiKErnel.Integration.Data;
using DiKErnel.Integration.Data.NaturalStoneRevetment;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data
{
    [TestFixture]
    public class NaturalStoneRevetmentLocationConstructionPropertiesTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            var topLayerType = Random.NextEnumValue<NaturalStoneRevetmentTopLayerType>();
            double x = Random.NextDouble();
            double thicknessTopLayer = Random.NextDouble();
            double relativeDensity = Random.NextDouble();

            // Call
            var constructionProperties = new NaturalStoneRevetmentLocationConstructionProperties(
                x, topLayerType, thicknessTopLayer, relativeDensity);

            // Assert
            Assert.IsInstanceOf<RevetmentLocationConstructionProperties>(constructionProperties);
            Assert.AreEqual(topLayerType, constructionProperties.TopLayerType);
            Assert.AreEqual(x, constructionProperties.X);
            Assert.AreEqual(thicknessTopLayer, constructionProperties.ThicknessTopLayer);
            Assert.AreEqual(relativeDensity, constructionProperties.RelativeDensity);
            Assert.IsNull(constructionProperties.InitialDamage);
            Assert.IsNull(constructionProperties.FailureNumber);
            Assert.IsNull(constructionProperties.HydraulicLoadXib);
            Assert.IsNull(constructionProperties.HydraulicLoadAp);
            Assert.IsNull(constructionProperties.HydraulicLoadBp);
            Assert.IsNull(constructionProperties.HydraulicLoadCp);
            Assert.IsNull(constructionProperties.HydraulicLoadNp);
            Assert.IsNull(constructionProperties.HydraulicLoadAs);
            Assert.IsNull(constructionProperties.HydraulicLoadBs);
            Assert.IsNull(constructionProperties.HydraulicLoadCs);
            Assert.IsNull(constructionProperties.HydraulicLoadNs);
            Assert.IsNull(constructionProperties.SlopeUpperLevelAus);
            Assert.IsNull(constructionProperties.SlopeLowerLevelAls);
            Assert.IsNull(constructionProperties.UpperLimitLoadingAul);
            Assert.IsNull(constructionProperties.UpperLimitLoadingBul);
            Assert.IsNull(constructionProperties.UpperLimitLoadingCul);
            Assert.IsNull(constructionProperties.LowerLimitLoadingAll);
            Assert.IsNull(constructionProperties.LowerLimitLoadingBll);
            Assert.IsNull(constructionProperties.LowerLimitLoadingCll);
            Assert.IsNull(constructionProperties.DistanceMaximumWaveElevationAsmax);
            Assert.IsNull(constructionProperties.DistanceMaximumWaveElevationBsmax);
            Assert.IsNull(constructionProperties.NormativeWidthOfWaveImpactAwi);
            Assert.IsNull(constructionProperties.NormativeWidthOfWaveImpactBwi);
            Assert.IsNull(constructionProperties.WaveAngleImpactBetamax);
        }

        [Test]
        public void GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues()
        {
            // Given
            var topLayerType = Random.NextEnumValue<NaturalStoneRevetmentTopLayerType>();
            double x = Random.NextDouble();
            double thicknessTopLayer = Random.NextDouble();
            double relativeDensity = Random.NextDouble();
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double hydraulicLoadXib = Random.NextDouble();
            double hydraulicLoadAp = Random.NextDouble();
            double hydraulicLoadBp = Random.NextDouble();
            double hydraulicLoadCp = Random.NextDouble();
            double hydraulicLoadNp = Random.NextDouble();
            double hydraulicLoadAs = Random.NextDouble();
            double hydraulicLoadBs = Random.NextDouble();
            double hydraulicLoadCs = Random.NextDouble();
            double hydraulicLoadNs = Random.NextDouble();
            double slopeUpperLevelAus = Random.NextDouble();
            double slopeLowerLevelAls = Random.NextDouble();
            double upperLimitLoadingAul = Random.NextDouble();
            double upperLimitLoadingBul = Random.NextDouble();
            double upperLimitLoadingCul = Random.NextDouble();
            double lowerLimitLoadingAll = Random.NextDouble();
            double lowerLimitLoadingBll = Random.NextDouble();
            double lowerLimitLoadingCll = Random.NextDouble();
            double distanceMaximumWaveElevationAsmax = Random.NextDouble();
            double distanceMaximumWaveElevationBsmax = Random.NextDouble();
            double normativeWidthOfWaveImpactAwi = Random.NextDouble();
            double normativeWidthOfWaveImpactBwi = Random.NextDouble();
            double waveAngleImpactBetamax = Random.NextDouble();

            var constructionProperties = new NaturalStoneRevetmentLocationConstructionProperties(
                x, topLayerType, thicknessTopLayer, relativeDensity);

            // When
            constructionProperties.InitialDamage = initialDamage;
            constructionProperties.FailureNumber = failureNumber;
            constructionProperties.HydraulicLoadXib = hydraulicLoadXib;
            constructionProperties.HydraulicLoadAp = hydraulicLoadAp;
            constructionProperties.HydraulicLoadBp = hydraulicLoadBp;
            constructionProperties.HydraulicLoadCp = hydraulicLoadCp;
            constructionProperties.HydraulicLoadNp = hydraulicLoadNp;
            constructionProperties.HydraulicLoadAs = hydraulicLoadAs;
            constructionProperties.HydraulicLoadBs = hydraulicLoadBs;
            constructionProperties.HydraulicLoadCs = hydraulicLoadCs;
            constructionProperties.HydraulicLoadNs = hydraulicLoadNs;
            constructionProperties.SlopeUpperLevelAus = slopeUpperLevelAus;
            constructionProperties.SlopeLowerLevelAls = slopeLowerLevelAls;
            constructionProperties.UpperLimitLoadingAul = upperLimitLoadingAul;
            constructionProperties.UpperLimitLoadingBul = upperLimitLoadingBul;
            constructionProperties.UpperLimitLoadingCul = upperLimitLoadingCul;
            constructionProperties.LowerLimitLoadingAll = lowerLimitLoadingAll;
            constructionProperties.LowerLimitLoadingBll = lowerLimitLoadingBll;
            constructionProperties.LowerLimitLoadingCll = lowerLimitLoadingCll;
            constructionProperties.DistanceMaximumWaveElevationAsmax = distanceMaximumWaveElevationAsmax;
            constructionProperties.DistanceMaximumWaveElevationBsmax = distanceMaximumWaveElevationBsmax;
            constructionProperties.NormativeWidthOfWaveImpactAwi = normativeWidthOfWaveImpactAwi;
            constructionProperties.NormativeWidthOfWaveImpactBwi = normativeWidthOfWaveImpactBwi;
            constructionProperties.WaveAngleImpactBetamax = waveAngleImpactBetamax;

            // Then
            Assert.AreEqual(topLayerType, constructionProperties.TopLayerType);
            Assert.AreEqual(x, constructionProperties.X);
            Assert.AreEqual(thicknessTopLayer, constructionProperties.ThicknessTopLayer);
            Assert.AreEqual(relativeDensity, constructionProperties.RelativeDensity);
            Assert.AreEqual(initialDamage, constructionProperties.InitialDamage);
            Assert.AreEqual(failureNumber, constructionProperties.FailureNumber);
            Assert.AreEqual(hydraulicLoadXib, constructionProperties.HydraulicLoadXib);
            Assert.AreEqual(hydraulicLoadAp, constructionProperties.HydraulicLoadAp);
            Assert.AreEqual(hydraulicLoadBp, constructionProperties.HydraulicLoadBp);
            Assert.AreEqual(hydraulicLoadCp, constructionProperties.HydraulicLoadCp);
            Assert.AreEqual(hydraulicLoadNp, constructionProperties.HydraulicLoadNp);
            Assert.AreEqual(hydraulicLoadAs, constructionProperties.HydraulicLoadAs);
            Assert.AreEqual(hydraulicLoadBs, constructionProperties.HydraulicLoadBs);
            Assert.AreEqual(hydraulicLoadCs, constructionProperties.HydraulicLoadCs);
            Assert.AreEqual(hydraulicLoadNs, constructionProperties.HydraulicLoadNs);
            Assert.AreEqual(slopeUpperLevelAus, constructionProperties.SlopeUpperLevelAus);
            Assert.AreEqual(slopeLowerLevelAls, constructionProperties.SlopeLowerLevelAls);
            Assert.AreEqual(upperLimitLoadingAul, constructionProperties.UpperLimitLoadingAul);
            Assert.AreEqual(upperLimitLoadingBul, constructionProperties.UpperLimitLoadingBul);
            Assert.AreEqual(upperLimitLoadingCul, constructionProperties.UpperLimitLoadingCul);
            Assert.AreEqual(lowerLimitLoadingAll, constructionProperties.LowerLimitLoadingAll);
            Assert.AreEqual(lowerLimitLoadingBll, constructionProperties.LowerLimitLoadingBll);
            Assert.AreEqual(lowerLimitLoadingCll, constructionProperties.LowerLimitLoadingCll);
            Assert.AreEqual(distanceMaximumWaveElevationAsmax, constructionProperties.DistanceMaximumWaveElevationAsmax);
            Assert.AreEqual(distanceMaximumWaveElevationBsmax, constructionProperties.DistanceMaximumWaveElevationBsmax);
            Assert.AreEqual(normativeWidthOfWaveImpactAwi, constructionProperties.NormativeWidthOfWaveImpactAwi);
            Assert.AreEqual(normativeWidthOfWaveImpactBwi, constructionProperties.NormativeWidthOfWaveImpactBwi);
            Assert.AreEqual(waveAngleImpactBetamax, constructionProperties.WaveAngleImpactBetamax);
        }
    }
}