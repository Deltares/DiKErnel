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

namespace DiKErnel.Integration.Test.Data.Output
{
    [TestFixture]
    public class GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionPropertiesTest
    {
        [Test]
    public void Constructor_ExpectedValues()
    {
        // Call
        const GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties constructionProperties;

        // Assert
        Assert.IsInstanceOf<TimeDependentOutputConstructionProperties>(constructionProperties);
        Assert.IsNull(constructionProperties.IncrementDamage);
        Assert.IsNull(constructionProperties.Damage);
        Assert.IsNull(constructionProperties.TimeOfFailure);
        Assert.IsNull(constructionProperties.VerticalDistanceWaterLevelElevation);
        Assert.IsNull(constructionProperties.WaveAngleImpact);
        Assert.IsNull(constructionProperties.RepresentativeWaveRunup2P);
        Assert.IsNull(constructionProperties.CumulativeOverload);
    }

        [Test]
    public void GivenConstructionProperties_WhenAllValuesSet_ThenExpectedValues()
    {
        // Given
        var incrementDamage = 0.1;
        var damage = 0.2;
        var timeOfFailure = 3;
        var verticalDistanceWaterLevelElevation = 0.4;
        var waveAngleImpact = 0.5;
        var representativeWaveRunup2P = 0.6;
        var cumulativeOverload = 0.7;

        // When
        GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties.IncrementDamage = incrementDamage);
        constructionProperties.Damage = damage);
        constructionProperties.TimeOfFailure = timeOfFailure);
        constructionProperties.VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation);
        constructionProperties.WaveAngleImpact = waveAngleImpact);
        constructionProperties.RepresentativeWaveRunup2P = representativeWaveRunup2P);
        constructionProperties.CumulativeOverload = cumulativeOverload);

        // Then
        Assert.AreEqual(incrementDamage, constructionProperties.IncrementDamage);
        Assert.AreEqual(damage, constructionProperties.Damage);
        Assert.AreEqual(timeOfFailure, constructionProperties.TimeOfFailure);
        Assert.AreEqual(verticalDistanceWaterLevelElevation, constructionProperties.VerticalDistanceWaterLevelElevation);
        Assert.AreEqual(waveAngleImpact, constructionProperties.WaveAngleImpact);
        Assert.AreEqual(representativeWaveRunup2P, constructionProperties.RepresentativeWaveRunup2P);
        Assert.AreEqual(cumulativeOverload, constructionProperties.CumulativeOverload);
    }
}
}
