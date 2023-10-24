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
using DiKErnel.Integration.Data.GrassRevetment;
using DiKErnel.Integration.Data.GrassRevetmentWaveRunup;
using DiKErnel.TestUtil;
using NSubstitute;
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
            var topLayerType = Random.NextEnumValue<GrassRevetmentTopLayerType>();
            double x = Random.NextDouble();
            double outerSlope = Random.NextDouble();

            // Call
            var constructionProperties = Substitute.For<GrassRevetmentWaveRunupLocationConstructionProperties>(
                x, outerSlope, topLayerType);

            // Assert
            Assert.IsInstanceOf<RevetmentLocationConstructionProperties>(constructionProperties);
            Assert.That(constructionProperties.TopLayerType, Is.EqualTo(topLayerType));
            Assert.That(constructionProperties.X, Is.EqualTo(x));
            Assert.That(constructionProperties.OuterSlope, Is.EqualTo(outerSlope));
            Assert.IsNull(constructionProperties.InitialDamage);
            Assert.IsNull(constructionProperties.FailureNumber);
            Assert.IsNull(constructionProperties.CriticalCumulativeOverload);
            Assert.IsNull(constructionProperties.CriticalFrontVelocity);
            Assert.IsNull(constructionProperties.IncreasedLoadTransitionAlphaM);
            Assert.IsNull(constructionProperties.ReducedStrengthTransitionAlphaS);
            Assert.IsNull(constructionProperties.AverageNumberOfWavesCtm);
            Assert.IsNull(constructionProperties.RepresentativeWaveRunup2PAru);
            Assert.IsNull(constructionProperties.RepresentativeWaveRunup2PBru);
            Assert.IsNull(constructionProperties.RepresentativeWaveRunup2PCru);
            Assert.IsNull(constructionProperties.RepresentativeWaveRunup2PGammab);
            Assert.IsNull(constructionProperties.RepresentativeWaveRunup2PGammaf);
            Assert.IsNull(constructionProperties.WaveAngleImpactAbeta);
            Assert.IsNull(constructionProperties.WaveAngleImpactBetamax);
        }

        [Test]
        public void GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassRevetmentTopLayerType>();
            double x = Random.NextDouble();
            double outerSlope = Random.NextDouble();
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double criticalCumulativeOverload = Random.NextDouble();
            double criticalFrontVelocity = Random.NextDouble();
            double increasedLoadTransitionAlphaM = Random.NextDouble();
            double reducedStrengthTransitionAlphaS = Random.NextDouble();
            double averageNumberOfWavesCtm = Random.NextDouble();
            double representativeWaveRunup2PAru = Random.NextDouble();
            double representativeWaveRunup2PBru = Random.NextDouble();
            double representativeWaveRunup2PCru = Random.NextDouble();
            double representativeWaveRunup2PGammab = Random.NextDouble();
            double representativeWaveRunup2PGammaf = Random.NextDouble();
            double waveAngleImpactAbeta = Random.NextDouble();
            double waveAngleImpactBetamax = Random.NextDouble();

            var constructionProperties = Substitute.For<GrassRevetmentWaveRunupLocationConstructionProperties>(
                x, outerSlope, topLayerType);

            // When
            constructionProperties.InitialDamage = initialDamage;
            constructionProperties.FailureNumber = failureNumber;
            constructionProperties.CriticalCumulativeOverload = criticalCumulativeOverload;
            constructionProperties.CriticalFrontVelocity = criticalFrontVelocity;
            constructionProperties.IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM;
            constructionProperties.ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS;
            constructionProperties.AverageNumberOfWavesCtm = averageNumberOfWavesCtm;
            constructionProperties.RepresentativeWaveRunup2PAru = representativeWaveRunup2PAru;
            constructionProperties.RepresentativeWaveRunup2PBru = representativeWaveRunup2PBru;
            constructionProperties.RepresentativeWaveRunup2PCru = representativeWaveRunup2PCru;
            constructionProperties.RepresentativeWaveRunup2PGammab = representativeWaveRunup2PGammab;
            constructionProperties.RepresentativeWaveRunup2PGammaf = representativeWaveRunup2PGammaf;
            constructionProperties.WaveAngleImpactAbeta = waveAngleImpactAbeta;
            constructionProperties.WaveAngleImpactBetamax = waveAngleImpactBetamax;

            // Then
            Assert.That(constructionProperties.TopLayerType, Is.EqualTo(topLayerType));
            Assert.That(constructionProperties.X, Is.EqualTo(x));
            Assert.That(constructionProperties.OuterSlope, Is.EqualTo(outerSlope));
            Assert.That(constructionProperties.InitialDamage, Is.EqualTo(initialDamage));
            Assert.That(constructionProperties.FailureNumber, Is.EqualTo(failureNumber));
            Assert.That(constructionProperties.CriticalCumulativeOverload, Is.EqualTo(criticalCumulativeOverload));
            Assert.That(constructionProperties.CriticalFrontVelocity, Is.EqualTo(criticalFrontVelocity));
            Assert.That(constructionProperties.IncreasedLoadTransitionAlphaM, Is.EqualTo(increasedLoadTransitionAlphaM));
            Assert.That(constructionProperties.ReducedStrengthTransitionAlphaS, Is.EqualTo(reducedStrengthTransitionAlphaS));
            Assert.That(constructionProperties.AverageNumberOfWavesCtm, Is.EqualTo(averageNumberOfWavesCtm));
            Assert.That(constructionProperties.RepresentativeWaveRunup2PAru, Is.EqualTo(representativeWaveRunup2PAru));
            Assert.That(constructionProperties.RepresentativeWaveRunup2PBru, Is.EqualTo(representativeWaveRunup2PBru));
            Assert.That(constructionProperties.RepresentativeWaveRunup2PCru, Is.EqualTo(representativeWaveRunup2PCru));
            Assert.That(constructionProperties.RepresentativeWaveRunup2PGammab, Is.EqualTo(representativeWaveRunup2PGammab));
            Assert.That(constructionProperties.RepresentativeWaveRunup2PGammaf, Is.EqualTo(representativeWaveRunup2PGammaf));
            Assert.That(constructionProperties.WaveAngleImpactAbeta, Is.EqualTo(waveAngleImpactAbeta));
            Assert.That(constructionProperties.WaveAngleImpactBetamax, Is.EqualTo(waveAngleImpactBetamax));
        }
    }
}