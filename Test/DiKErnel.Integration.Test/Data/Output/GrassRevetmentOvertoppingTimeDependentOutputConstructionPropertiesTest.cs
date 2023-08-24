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
    public class GrassRevetmentOvertoppingTimeDependentOutputConstructionPropertiesTest
    {

        [Test]
    public void Constructor_ExpectedValues()
    {
        // Call
        const GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties constructionProperties;

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutputConstructionProperties>(&constructionProperties);
        ASSERT_EQ(nullptr, constructionProperties._incrementDamage);
        ASSERT_EQ(nullptr, constructionProperties._damage);
        ASSERT_EQ(nullptr, constructionProperties._timeOfFailure);
        ASSERT_EQ(nullptr, constructionProperties._verticalDistanceWaterLevelElevation);
        ASSERT_EQ(nullptr, constructionProperties._representativeWaveRunup2P);
        ASSERT_EQ(nullptr, constructionProperties._cumulativeOverload);
    }

        [Test]
    public void GivenConstructionProperties_WhenAllValuesSet_ThenExpectedValues()
    {
        // Given
        var incrementDamage = 0.1;
        var damage = 0.2;
        var timeOfFailure = 3;
        var verticalDistanceWaterLevelElevation = 0.4;
        var representativeWaveRunup2P = 0.5;
        var cumulativeOverload = 0.6;

        // When
        GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
        constructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);
        constructionProperties._verticalDistanceWaterLevelElevation = make_unique<double>(verticalDistanceWaterLevelElevation);
        constructionProperties._representativeWaveRunup2P = make_unique<double>(representativeWaveRunup2P);
        constructionProperties._cumulativeOverload = make_unique<double>(cumulativeOverload);

        // Then
        ASSERT_DOUBLE_EQ(incrementDamage, *constructionProperties._incrementDamage);
        ASSERT_DOUBLE_EQ(damage, *constructionProperties._damage);
        ASSERT_EQ(timeOfFailure, *constructionProperties._timeOfFailure);
        ASSERT_DOUBLE_EQ(verticalDistanceWaterLevelElevation, *constructionProperties._verticalDistanceWaterLevelElevation);
        ASSERT_DOUBLE_EQ(representativeWaveRunup2P, *constructionProperties._representativeWaveRunup2P);
        ASSERT_DOUBLE_EQ(cumulativeOverload, *constructionProperties._cumulativeOverload);
    }
}
}
