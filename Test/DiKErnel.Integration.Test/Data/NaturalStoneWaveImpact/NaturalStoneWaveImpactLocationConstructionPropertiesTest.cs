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
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.NaturalStoneWaveImpact
{
    [TestFixture]
    internal sealed class NaturalStoneWaveImpactLocationConstructionPropertiesTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            var topLayerType = Random.NextEnumValue<NaturalStoneWaveImpactTopLayerType>();
            double x = Random.NextDouble();
            double thicknessTopLayer = Random.NextDouble();
            double relativeDensity = Random.NextDouble();

            // Call
            var constructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                x, topLayerType, thicknessTopLayer, relativeDensity);

            // Assert
            Assert.That(constructionProperties, Is.InstanceOf<LocationConstructionProperties>());
            Assert.That(constructionProperties.TopLayerType, Is.EqualTo(topLayerType));
            Assert.That(constructionProperties.X, Is.EqualTo(x));
            Assert.That(constructionProperties.ThicknessTopLayer, Is.EqualTo(thicknessTopLayer));
            Assert.That(constructionProperties.RelativeDensity, Is.EqualTo(relativeDensity));
            Assert.That(constructionProperties.InitialDamage, Is.Null);
            Assert.That(constructionProperties.FailureNumber, Is.Null);
            Assert.That(constructionProperties.HydraulicLoadXib, Is.Null);
            Assert.That(constructionProperties.HydraulicLoadAp, Is.Null);
            Assert.That(constructionProperties.HydraulicLoadBp, Is.Null);
            Assert.That(constructionProperties.HydraulicLoadCp, Is.Null);
            Assert.That(constructionProperties.HydraulicLoadNp, Is.Null);
            Assert.That(constructionProperties.HydraulicLoadAs, Is.Null);
            Assert.That(constructionProperties.HydraulicLoadBs, Is.Null);
            Assert.That(constructionProperties.HydraulicLoadCs, Is.Null);
            Assert.That(constructionProperties.HydraulicLoadNs, Is.Null);
            Assert.That(constructionProperties.SlopeUpperLevelAus, Is.Null);
            Assert.That(constructionProperties.SlopeLowerLevelAls, Is.Null);
            Assert.That(constructionProperties.UpperLimitLoadingAul, Is.Null);
            Assert.That(constructionProperties.UpperLimitLoadingBul, Is.Null);
            Assert.That(constructionProperties.UpperLimitLoadingCul, Is.Null);
            Assert.That(constructionProperties.LowerLimitLoadingAll, Is.Null);
            Assert.That(constructionProperties.LowerLimitLoadingBll, Is.Null);
            Assert.That(constructionProperties.LowerLimitLoadingCll, Is.Null);
            Assert.That(constructionProperties.DistanceMaximumWaveElevationAsmax, Is.Null);
            Assert.That(constructionProperties.DistanceMaximumWaveElevationBsmax, Is.Null);
            Assert.That(constructionProperties.NormativeWidthOfWaveImpactAwi, Is.Null);
            Assert.That(constructionProperties.NormativeWidthOfWaveImpactBwi, Is.Null);
            Assert.That(constructionProperties.WaveAngleImpactBetamax, Is.Null);
        }

        [Test]
        public void GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues()
        {
            // Given
            var topLayerType = Random.NextEnumValue<NaturalStoneWaveImpactTopLayerType>();
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

            var constructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
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
            Assert.That(constructionProperties.TopLayerType, Is.EqualTo(topLayerType));
            Assert.That(constructionProperties.X, Is.EqualTo(x));
            Assert.That(constructionProperties.ThicknessTopLayer, Is.EqualTo(thicknessTopLayer));
            Assert.That(constructionProperties.RelativeDensity, Is.EqualTo(relativeDensity));
            Assert.That(constructionProperties.InitialDamage, Is.EqualTo(initialDamage));
            Assert.That(constructionProperties.FailureNumber, Is.EqualTo(failureNumber));
            Assert.That(constructionProperties.HydraulicLoadXib, Is.EqualTo(hydraulicLoadXib));
            Assert.That(constructionProperties.HydraulicLoadAp, Is.EqualTo(hydraulicLoadAp));
            Assert.That(constructionProperties.HydraulicLoadBp, Is.EqualTo(hydraulicLoadBp));
            Assert.That(constructionProperties.HydraulicLoadCp, Is.EqualTo(hydraulicLoadCp));
            Assert.That(constructionProperties.HydraulicLoadNp, Is.EqualTo(hydraulicLoadNp));
            Assert.That(constructionProperties.HydraulicLoadAs, Is.EqualTo(hydraulicLoadAs));
            Assert.That(constructionProperties.HydraulicLoadBs, Is.EqualTo(hydraulicLoadBs));
            Assert.That(constructionProperties.HydraulicLoadCs, Is.EqualTo(hydraulicLoadCs));
            Assert.That(constructionProperties.HydraulicLoadNs, Is.EqualTo(hydraulicLoadNs));
            Assert.That(constructionProperties.SlopeUpperLevelAus, Is.EqualTo(slopeUpperLevelAus));
            Assert.That(constructionProperties.SlopeLowerLevelAls, Is.EqualTo(slopeLowerLevelAls));
            Assert.That(constructionProperties.UpperLimitLoadingAul, Is.EqualTo(upperLimitLoadingAul));
            Assert.That(constructionProperties.UpperLimitLoadingBul, Is.EqualTo(upperLimitLoadingBul));
            Assert.That(constructionProperties.UpperLimitLoadingCul, Is.EqualTo(upperLimitLoadingCul));
            Assert.That(constructionProperties.LowerLimitLoadingAll, Is.EqualTo(lowerLimitLoadingAll));
            Assert.That(constructionProperties.LowerLimitLoadingBll, Is.EqualTo(lowerLimitLoadingBll));
            Assert.That(constructionProperties.LowerLimitLoadingCll, Is.EqualTo(lowerLimitLoadingCll));
            Assert.That(constructionProperties.DistanceMaximumWaveElevationAsmax, Is.EqualTo(distanceMaximumWaveElevationAsmax));
            Assert.That(constructionProperties.DistanceMaximumWaveElevationBsmax, Is.EqualTo(distanceMaximumWaveElevationBsmax));
            Assert.That(constructionProperties.NormativeWidthOfWaveImpactAwi, Is.EqualTo(normativeWidthOfWaveImpactAwi));
            Assert.That(constructionProperties.NormativeWidthOfWaveImpactBwi, Is.EqualTo(normativeWidthOfWaveImpactBwi));
            Assert.That(constructionProperties.WaveAngleImpactBetamax, Is.EqualTo(waveAngleImpactBetamax));
        }
    }
}