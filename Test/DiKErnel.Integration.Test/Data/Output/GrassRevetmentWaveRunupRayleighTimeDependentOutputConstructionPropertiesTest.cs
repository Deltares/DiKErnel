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
        Assert.IsInstanceOf<TimeDependentOutputConstructionProperties>(&constructionProperties);
        Assert.IsNull(constructionProperties._incrementDamage);
        Assert.IsNull(constructionProperties._damage);
        Assert.IsNull(constructionProperties._timeOfFailure);
        Assert.IsNull(constructionProperties._verticalDistanceWaterLevelElevation);
        Assert.IsNull(constructionProperties._waveAngleImpact);
        Assert.IsNull(constructionProperties._representativeWaveRunup2P);
        Assert.IsNull(constructionProperties._cumulativeOverload);
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
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
        constructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);
        constructionProperties._verticalDistanceWaterLevelElevation = make_unique<double>(verticalDistanceWaterLevelElevation);
        constructionProperties._waveAngleImpact = make_unique<double>(waveAngleImpact);
        constructionProperties._representativeWaveRunup2P = make_unique<double>(representativeWaveRunup2P);
        constructionProperties._cumulativeOverload = make_unique<double>(cumulativeOverload);

        // Then
        Assert.AreEqual(incrementDamage, *constructionProperties._incrementDamage);
        Assert.AreEqual(damage, *constructionProperties._damage);
        ASSERT_EQ(timeOfFailure, *constructionProperties._timeOfFailure);
        Assert.AreEqual(verticalDistanceWaterLevelElevation, *constructionProperties._verticalDistanceWaterLevelElevation);
        Assert.AreEqual(waveAngleImpact, *constructionProperties._waveAngleImpact);
        Assert.AreEqual(representativeWaveRunup2P, *constructionProperties._representativeWaveRunup2P);
        Assert.AreEqual(cumulativeOverload, *constructionProperties._cumulativeOverload);
    }
}
}
