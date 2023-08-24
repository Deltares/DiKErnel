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
    public class GrassRevetmentWaveRunupLocationConstructionPropertiesTest
    {

        [Test]
    public void Constructor_ExpectedValues()
    {
        // Setup
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var x = 0.1;
        var outerSlope = 0.2;

        // Call
        const GrassRevetmentWaveRunupLocationConstructionPropertiesMock constructionProperties(x, outerSlope, topLayerType);

        // Assert
        Assert.IsInstanceOf<RevetmentLocationConstructionPropertiesBase>(constructionProperties);
        Assert.AreEqual(topLayerType, constructionProperties.GetTopLayerType());
        Assert.AreEqual(x, constructionProperties.GetX());
        Assert.AreEqual(outerSlope, constructionProperties.GetOuterSlope());
        Assert.IsNull(constructionProperties.GetInitialDamage());
        Assert.IsNull(constructionProperties.GetFailureNumber());
        Assert.IsNull(constructionProperties.GetCriticalCumulativeOverload());
        Assert.IsNull(constructionProperties.GetCriticalFrontVelocity());
        Assert.IsNull(constructionProperties.GetIncreasedLoadTransitionAlphaM());
        Assert.IsNull(constructionProperties.GetReducedStrengthTransitionAlphaS());
        Assert.IsNull(constructionProperties.GetAverageNumberOfWavesCtm());
        Assert.IsNull(constructionProperties.GetRepresentativeWaveRunup2PAru());
        Assert.IsNull(constructionProperties.GetRepresentativeWaveRunup2PBru());
        Assert.IsNull(constructionProperties.GetRepresentativeWaveRunup2PCru());
        Assert.IsNull(constructionProperties.GetRepresentativeWaveRunup2PGammab());
        Assert.IsNull(constructionProperties.GetRepresentativeWaveRunup2PGammaf());
        Assert.IsNull(constructionProperties.GetWaveAngleImpactAbeta());
        Assert.IsNull(constructionProperties.GetWaveAngleImpactBetamax());
    }

        [Test]
    public void GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues()
    {
        // Given
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var x = 0.1;
        var outerSlope = 0.2;
        var initialDamage = 0.3;
        var failureNumber = 0.4;
        var criticalCumulativeOverload = 0.5;
        var criticalFrontVelocity = 0.6;
        var increasedLoadTransitionAlphaM = 0.7;
        var reducedStrengthTransitionAlphaS = 0.8;
        var averageNumberOfWavesCtm = 0.9;
        var representativeWaveRunup2PAru = 1.0;
        var representativeWaveRunup2PBru = 1.1;
        var representativeWaveRunup2PCru = 1.2;
        var representativeWaveRunup2PGammab = 1.3;
        var representativeWaveRunup2PGammaf = 1.4;
        var waveAngleImpactAbeta = 1.5;
        var waveAngleImpactBetamax = 1.6;

        GrassRevetmentWaveRunupLocationConstructionPropertiesMock constructionProperties(x, outerSlope, topLayerType);

        // When
        constructionProperties.SetInitialDamage(initialDamage));
        constructionProperties.SetFailureNumber(failureNumber));
        constructionProperties.SetCriticalCumulativeOverload(criticalCumulativeOverload));
        constructionProperties.SetCriticalFrontVelocity(criticalFrontVelocity));
        constructionProperties.SetIncreasedLoadTransitionAlphaM(increasedLoadTransitionAlphaM));
        constructionProperties.SetReducedStrengthTransitionAlphaS(reducedStrengthTransitionAlphaS));
        constructionProperties.SetAverageNumberOfWavesCtm(averageNumberOfWavesCtm));
        constructionProperties.SetRepresentativeWaveRunup2PAru(representativeWaveRunup2PAru));
        constructionProperties.SetRepresentativeWaveRunup2PBru(representativeWaveRunup2PBru));
        constructionProperties.SetRepresentativeWaveRunup2PCru(representativeWaveRunup2PCru));
        constructionProperties.SetRepresentativeWaveRunup2PGammab(representativeWaveRunup2PGammab));
        constructionProperties.SetRepresentativeWaveRunup2PGammaf(representativeWaveRunup2PGammaf));
        constructionProperties.SetWaveAngleImpactAbeta(waveAngleImpactAbeta));
        constructionProperties.SetWaveAngleImpactBetamax(waveAngleImpactBetamax));

        // Then
        Assert.AreEqual(topLayerType, constructionProperties.GetTopLayerType());
        Assert.AreEqual(x, constructionProperties.GetX());
        Assert.AreEqual(outerSlope, constructionProperties.GetOuterSlope());
        Assert.AreEqual(initialDamage, constructionProperties.GetInitialDamage());
        Assert.AreEqual(failureNumber, constructionProperties.GetFailureNumber());
        Assert.AreEqual(criticalCumulativeOverload, constructionProperties.GetCriticalCumulativeOverload());
        Assert.AreEqual(criticalFrontVelocity, constructionProperties.GetCriticalFrontVelocity());
        Assert.AreEqual(increasedLoadTransitionAlphaM, constructionProperties.GetIncreasedLoadTransitionAlphaM());
        Assert.AreEqual(reducedStrengthTransitionAlphaS, constructionProperties.GetReducedStrengthTransitionAlphaS());
        Assert.AreEqual(averageNumberOfWavesCtm, constructionProperties.GetAverageNumberOfWavesCtm());
        Assert.AreEqual(representativeWaveRunup2PAru, constructionProperties.GetRepresentativeWaveRunup2PAru());
        Assert.AreEqual(representativeWaveRunup2PBru, constructionProperties.GetRepresentativeWaveRunup2PBru());
        Assert.AreEqual(representativeWaveRunup2PCru, constructionProperties.GetRepresentativeWaveRunup2PCru());
        Assert.AreEqual(representativeWaveRunup2PGammab, constructionProperties.GetRepresentativeWaveRunup2PGammab());
        Assert.AreEqual(representativeWaveRunup2PGammaf, constructionProperties.GetRepresentativeWaveRunup2PGammaf());
        Assert.AreEqual(waveAngleImpactAbeta, constructionProperties.GetWaveAngleImpactAbeta());
        Assert.AreEqual(waveAngleImpactBetamax, constructionProperties.GetWaveAngleImpactBetamax());
    }
}

}
