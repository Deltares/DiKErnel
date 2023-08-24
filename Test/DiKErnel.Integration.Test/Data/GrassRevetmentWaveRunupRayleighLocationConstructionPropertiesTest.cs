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
    public class GrassRevetmentWaveRunupRayleighLocationConstructionPropertiesTest
    {

        [Test]
    public void Constructor_ExpectedValues()
    {
        // Setup
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var x = 0.1;
        var outerSlope = 0.2;

        // Call
        const GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties(x, outerSlope, topLayerType);

        // Assert
        Assert.IsInstanceOf<GrassRevetmentWaveRunupLocationConstructionProperties>(&constructionProperties);
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        Assert.AreEqual(x, constructionProperties.GetX());
        Assert.AreEqual(outerSlope, constructionProperties.GetOuterSlope());
        ASSERT_EQ(nullptr, constructionProperties.GetInitialDamage());
        ASSERT_EQ(nullptr, constructionProperties.GetFailureNumber());
        ASSERT_EQ(nullptr, constructionProperties.GetCriticalCumulativeOverload());
        ASSERT_EQ(nullptr, constructionProperties.GetCriticalFrontVelocity());
        ASSERT_EQ(nullptr, constructionProperties.GetIncreasedLoadTransitionAlphaM());
        ASSERT_EQ(nullptr, constructionProperties.GetReducedStrengthTransitionAlphaS());
        ASSERT_EQ(nullptr, constructionProperties.GetAverageNumberOfWavesCtm());
        ASSERT_EQ(nullptr, constructionProperties.GetRepresentativeWaveRunup2PAru());
        ASSERT_EQ(nullptr, constructionProperties.GetRepresentativeWaveRunup2PBru());
        ASSERT_EQ(nullptr, constructionProperties.GetRepresentativeWaveRunup2PCru());
        ASSERT_EQ(nullptr, constructionProperties.GetRepresentativeWaveRunup2PGammab());
        ASSERT_EQ(nullptr, constructionProperties.GetRepresentativeWaveRunup2PGammaf());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveAngleImpactAbeta());
        ASSERT_EQ(nullptr, constructionProperties.GetWaveAngleImpactBetamax());
        ASSERT_EQ(nullptr, constructionProperties.GetFixedNumberOfWaves());
        ASSERT_EQ(nullptr, constructionProperties.GetFrontVelocityCu());
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
        var fixedNumberOfWaves = 17;
        var frontVelocityCu = 1.8;

        GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties(x, outerSlope, topLayerType);

        // When
        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties.SetCriticalCumulativeOverload(make_unique<double>(criticalCumulativeOverload));
        constructionProperties.SetCriticalFrontVelocity(make_unique<double>(criticalFrontVelocity));
        constructionProperties.SetIncreasedLoadTransitionAlphaM(make_unique<double>(increasedLoadTransitionAlphaM));
        constructionProperties.SetReducedStrengthTransitionAlphaS(make_unique<double>(reducedStrengthTransitionAlphaS));
        constructionProperties.SetAverageNumberOfWavesCtm(make_unique<double>(averageNumberOfWavesCtm));
        constructionProperties.SetRepresentativeWaveRunup2PAru(make_unique<double>(representativeWaveRunup2PAru));
        constructionProperties.SetRepresentativeWaveRunup2PBru(make_unique<double>(representativeWaveRunup2PBru));
        constructionProperties.SetRepresentativeWaveRunup2PCru(make_unique<double>(representativeWaveRunup2PCru));
        constructionProperties.SetRepresentativeWaveRunup2PGammab(make_unique<double>(representativeWaveRunup2PGammab));
        constructionProperties.SetRepresentativeWaveRunup2PGammaf(make_unique<double>(representativeWaveRunup2PGammaf));
        constructionProperties.SetWaveAngleImpactAbeta(make_unique<double>(waveAngleImpactAbeta));
        constructionProperties.SetWaveAngleImpactBetamax(make_unique<double>(waveAngleImpactBetamax));
        constructionProperties.SetFixedNumberOfWaves(make_unique<int>(fixedNumberOfWaves));
        constructionProperties.SetFrontVelocityCu(make_unique<double>(frontVelocityCu));

        // Then
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        Assert.AreEqual(x, constructionProperties.GetX());
        Assert.AreEqual(outerSlope, constructionProperties.GetOuterSlope());
        Assert.AreEqual(initialDamage, *constructionProperties.GetInitialDamage());
        Assert.AreEqual(failureNumber, *constructionProperties.GetFailureNumber());
        Assert.AreEqual(criticalCumulativeOverload, *constructionProperties.GetCriticalCumulativeOverload());
        Assert.AreEqual(criticalFrontVelocity, *constructionProperties.GetCriticalFrontVelocity());
        Assert.AreEqual(increasedLoadTransitionAlphaM, *constructionProperties.GetIncreasedLoadTransitionAlphaM());
        Assert.AreEqual(reducedStrengthTransitionAlphaS, *constructionProperties.GetReducedStrengthTransitionAlphaS());
        Assert.AreEqual(averageNumberOfWavesCtm, *constructionProperties.GetAverageNumberOfWavesCtm());
        Assert.AreEqual(representativeWaveRunup2PAru, *constructionProperties.GetRepresentativeWaveRunup2PAru());
        Assert.AreEqual(representativeWaveRunup2PBru, *constructionProperties.GetRepresentativeWaveRunup2PBru());
        Assert.AreEqual(representativeWaveRunup2PCru, *constructionProperties.GetRepresentativeWaveRunup2PCru());
        Assert.AreEqual(representativeWaveRunup2PGammab, *constructionProperties.GetRepresentativeWaveRunup2PGammab());
        Assert.AreEqual(representativeWaveRunup2PGammaf, *constructionProperties.GetRepresentativeWaveRunup2PGammaf());
        Assert.AreEqual(waveAngleImpactAbeta, *constructionProperties.GetWaveAngleImpactAbeta());
        Assert.AreEqual(waveAngleImpactBetamax, *constructionProperties.GetWaveAngleImpactBetamax());
        ASSERT_EQ(fixedNumberOfWaves, *constructionProperties.GetFixedNumberOfWaves());
        Assert.AreEqual(frontVelocityCu, *constructionProperties.GetFrontVelocityCu());
    }
}
}
