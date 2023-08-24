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
        var topLayerType = NaturalStoneRevetmentTopLayerType::NordicStone;
        var x = 0.1;
        var thicknessTopLayer = 0.2;
        var relativeDensity = 0.3;

        // Call
        const NaturalStoneRevetmentLocationConstructionProperties constructionProperties(x, topLayerType, thicknessTopLayer, relativeDensity);

        // Assert
        Assert.IsInstanceOf<RevetmentLocationConstructionPropertiesBase>(constructionProperties);
        Assert.AreEqual(topLayerType, constructionProperties.GetTopLayerType());
        Assert.AreEqual(x, constructionProperties.GetX());
        Assert.AreEqual(thicknessTopLayer, constructionProperties.GetThicknessTopLayer());
        Assert.AreEqual(relativeDensity, constructionProperties.GetRelativeDensity());
        Assert.IsNull(constructionProperties.GetInitialDamage());
        Assert.IsNull(constructionProperties.GetFailureNumber());
        Assert.IsNull(constructionProperties.GetHydraulicLoadXib());
        Assert.IsNull(constructionProperties.GetHydraulicLoadAp());
        Assert.IsNull(constructionProperties.GetHydraulicLoadBp());
        Assert.IsNull(constructionProperties.GetHydraulicLoadCp());
        Assert.IsNull(constructionProperties.GetHydraulicLoadNp());
        Assert.IsNull(constructionProperties.GetHydraulicLoadAs());
        Assert.IsNull(constructionProperties.GetHydraulicLoadBs());
        Assert.IsNull(constructionProperties.GetHydraulicLoadCs());
        Assert.IsNull(constructionProperties.GetHydraulicLoadNs());
        Assert.IsNull(constructionProperties.GetSlopeUpperLevelAus());
        Assert.IsNull(constructionProperties.GetSlopeLowerLevelAls());
        Assert.IsNull(constructionProperties.GetUpperLimitLoadingAul());
        Assert.IsNull(constructionProperties.GetUpperLimitLoadingBul());
        Assert.IsNull(constructionProperties.GetUpperLimitLoadingCul());
        Assert.IsNull(constructionProperties.GetLowerLimitLoadingAll());
        Assert.IsNull(constructionProperties.GetLowerLimitLoadingBll());
        Assert.IsNull(constructionProperties.GetLowerLimitLoadingCll());
        Assert.IsNull(constructionProperties.GetDistanceMaximumWaveElevationAsmax());
        Assert.IsNull(constructionProperties.GetDistanceMaximumWaveElevationBsmax());
        Assert.IsNull(constructionProperties.GetNormativeWidthOfWaveImpactAwi());
        Assert.IsNull(constructionProperties.GetNormativeWidthOfWaveImpactBwi());
        Assert.IsNull(constructionProperties.GetWaveAngleImpactBetamax());
    }

        [Test]
    public void GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues()
    {
        // Given
        var topLayerType = NaturalStoneRevetmentTopLayerType::NordicStone;
        var x = 0.1;
        var thicknessTopLayer = 0.2;
        var relativeDensity = 0.3;
        var initialDamage = 0.4;
        var failureNumber = 0.5;
        var hydraulicLoadXib = 0.6;
        var hydraulicLoadAp = 0.7;
        var hydraulicLoadBp = 0.8;
        var hydraulicLoadCp = 0.9;
        var hydraulicLoadNp = 1.0;
        var hydraulicLoadAs = 1.1;
        var hydraulicLoadBs = 1.2;
        var hydraulicLoadCs = 1.3;
        var hydraulicLoadNs = 1.4;
        var slopeUpperLevelAus = 1.5;
        var slopeLowerLevelAls = 1.6;
        var upperLimitLoadingAul = 1.7;
        var upperLimitLoadingBul = 1.8;
        var upperLimitLoadingCul = 1.9;
        var lowerLimitLoadingAll = 2.0;
        var lowerLimitLoadingBll = 2.1;
        var lowerLimitLoadingCll = 2.2;
        var distanceMaximumWaveElevationAsmax = 2.3;
        var distanceMaximumWaveElevationBsmax = 2.4;
        var normativeWidthOfWaveImpactAwi = 2.5;
        var normativeWidthOfWaveImpactBwi = 2.6;
        var waveAngleImpactBetamax = 2.7;

        NaturalStoneRevetmentLocationConstructionProperties constructionProperties(x, topLayerType, thicknessTopLayer, relativeDensity);

        // When
        constructionProperties.SetInitialDamage(initialDamage));
        constructionProperties.SetFailureNumber(failureNumber));
        constructionProperties.SetHydraulicLoadXib(hydraulicLoadXib));
        constructionProperties.SetHydraulicLoadAp(hydraulicLoadAp));
        constructionProperties.SetHydraulicLoadBp(hydraulicLoadBp));
        constructionProperties.SetHydraulicLoadCp(hydraulicLoadCp));
        constructionProperties.SetHydraulicLoadNp(hydraulicLoadNp));
        constructionProperties.SetHydraulicLoadAs(hydraulicLoadAs));
        constructionProperties.SetHydraulicLoadBs(hydraulicLoadBs));
        constructionProperties.SetHydraulicLoadCs(hydraulicLoadCs));
        constructionProperties.SetHydraulicLoadNs(hydraulicLoadNs));
        constructionProperties.SetSlopeUpperLevelAus(slopeUpperLevelAus));
        constructionProperties.SetSlopeLowerLevelAls(slopeLowerLevelAls));
        constructionProperties.SetUpperLimitLoadingAul(upperLimitLoadingAul));
        constructionProperties.SetUpperLimitLoadingBul(upperLimitLoadingBul));
        constructionProperties.SetUpperLimitLoadingCul(upperLimitLoadingCul));
        constructionProperties.SetLowerLimitLoadingAll(lowerLimitLoadingAll));
        constructionProperties.SetLowerLimitLoadingBll(lowerLimitLoadingBll));
        constructionProperties.SetLowerLimitLoadingCll(lowerLimitLoadingCll));
        constructionProperties.SetDistanceMaximumWaveElevationAsmax(distanceMaximumWaveElevationAsmax));
        constructionProperties.SetDistanceMaximumWaveElevationBsmax(distanceMaximumWaveElevationBsmax));
        constructionProperties.SetNormativeWidthOfWaveImpactAwi(normativeWidthOfWaveImpactAwi));
        constructionProperties.SetNormativeWidthOfWaveImpactBwi(normativeWidthOfWaveImpactBwi));
        constructionProperties.SetWaveAngleImpactBetamax(waveAngleImpactBetamax));

        // Then
        Assert.AreEqual(topLayerType, constructionProperties.GetTopLayerType());
        Assert.AreEqual(x, constructionProperties.GetX());
        Assert.AreEqual(thicknessTopLayer, constructionProperties.GetThicknessTopLayer());
        Assert.AreEqual(relativeDensity, constructionProperties.GetRelativeDensity());
        Assert.AreEqual(initialDamage, constructionProperties.GetInitialDamage());
        Assert.AreEqual(failureNumber, constructionProperties.GetFailureNumber());
        Assert.AreEqual(hydraulicLoadXib, constructionProperties.GetHydraulicLoadXib());
        Assert.AreEqual(hydraulicLoadAp, constructionProperties.GetHydraulicLoadAp());
        Assert.AreEqual(hydraulicLoadBp, constructionProperties.GetHydraulicLoadBp());
        Assert.AreEqual(hydraulicLoadCp, constructionProperties.GetHydraulicLoadCp());
        Assert.AreEqual(hydraulicLoadNp, constructionProperties.GetHydraulicLoadNp());
        Assert.AreEqual(hydraulicLoadAs, constructionProperties.GetHydraulicLoadAs());
        Assert.AreEqual(hydraulicLoadBs, constructionProperties.GetHydraulicLoadBs());
        Assert.AreEqual(hydraulicLoadCs, constructionProperties.GetHydraulicLoadCs());
        Assert.AreEqual(hydraulicLoadNs, constructionProperties.GetHydraulicLoadNs());
        Assert.AreEqual(slopeUpperLevelAus, constructionProperties.GetSlopeUpperLevelAus());
        Assert.AreEqual(slopeLowerLevelAls, constructionProperties.GetSlopeLowerLevelAls());
        Assert.AreEqual(upperLimitLoadingAul, constructionProperties.GetUpperLimitLoadingAul());
        Assert.AreEqual(upperLimitLoadingBul, constructionProperties.GetUpperLimitLoadingBul());
        Assert.AreEqual(upperLimitLoadingCul, constructionProperties.GetUpperLimitLoadingCul());
        Assert.AreEqual(lowerLimitLoadingAll, constructionProperties.GetLowerLimitLoadingAll());
        Assert.AreEqual(lowerLimitLoadingBll, constructionProperties.GetLowerLimitLoadingBll());
        Assert.AreEqual(lowerLimitLoadingCll, constructionProperties.GetLowerLimitLoadingCll());
        Assert.AreEqual(distanceMaximumWaveElevationAsmax, constructionProperties.GetDistanceMaximumWaveElevationAsmax());
        Assert.AreEqual(distanceMaximumWaveElevationBsmax, constructionProperties.GetDistanceMaximumWaveElevationBsmax());
        Assert.AreEqual(normativeWidthOfWaveImpactAwi, constructionProperties.GetNormativeWidthOfWaveImpactAwi());
        Assert.AreEqual(normativeWidthOfWaveImpactBwi, constructionProperties.GetNormativeWidthOfWaveImpactBwi());
        Assert.AreEqual(waveAngleImpactBetamax, constructionProperties.GetWaveAngleImpactBetamax());
    }
}

}
