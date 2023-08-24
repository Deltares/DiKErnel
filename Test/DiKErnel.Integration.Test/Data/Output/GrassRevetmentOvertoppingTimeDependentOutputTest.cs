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
    public class GrassRevetmentOvertoppingTimeDependentOutputTest
    {

    struct GrassRevetmentOvertoppingTimeDependentOutputTest : Test
    {
        static void CreateOutputWithConstructionPropertiesWithVerticalDistanceWaterLevelElevationNull()
        {
            // Setup
            GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties constructionProperties;
            constructionProperties.IncrementDamage = 0.1);
            constructionProperties.Damage = 0.2);
            constructionProperties.TimeOfFailure = 3);
            constructionProperties.VerticalDistanceWaterLevelElevation = null;
            constructionProperties.RepresentativeWaveRunup2P = 0.4);
            constructionProperties.CumulativeOverload = 0.5);

            // Call
            const GrassRevetmentOvertoppingTimeDependentOutput output(constructionProperties);
        }
    };

    [Test]
    public void Constructor_WithAllValuesSet_ExpectedValues()
    {
        // Setup
        var incrementDamage = 0.1;
        var damage = 0.2;
        var timeOfFailure = 3;
        var verticalDistanceWaterLevelElevation = 0.4;
        var representativeWaveRunup2P = 0.5;
        var cumulativeOverload = 0.6;

        GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties.IncrementDamage = incrementDamage);
        constructionProperties.Damage = damage);
        constructionProperties.TimeOfFailure = timeOfFailure);
        constructionProperties.VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation);
        constructionProperties.RepresentativeWaveRunup2P = representativeWaveRunup2P);
        constructionProperties.CumulativeOverload = cumulativeOverload);

        // Call
        const GrassRevetmentOvertoppingTimeDependentOutput output(constructionProperties);

        // Assert
        Assert.IsInstanceOf<TimeDependentOutput>(&output);
        Assert.AreEqual(incrementDamage, output.GetIncrementDamage());
        Assert.AreEqual(damage, output.GetDamage());
        Assert.AreEqual(timeOfFailure, *output.GetTimeOfFailure());
        Assert.AreEqual(verticalDistanceWaterLevelElevation, output.GetVerticalDistanceWaterLevelElevation());
        Assert.AreEqual(representativeWaveRunup2P, *output.GetRepresentativeWaveRunup2P());
        Assert.AreEqual(cumulativeOverload, *output.GetCumulativeOverload());
    }

        [Test]
    public void Constructor_WithNullPtrValues_ExpectedValues()
    {
        // Setup
        var incrementDamage = 0.1;
        var damage = 0.2;
        var verticalDistanceWaterLevelElevation = 0.3;

        GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties.IncrementDamage = incrementDamage);
        constructionProperties.Damage = damage);
        constructionProperties.VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation);

        // Call
        const GrassRevetmentOvertoppingTimeDependentOutput output(constructionProperties);

        // Assert
        Assert.IsInstanceOf<TimeDependentOutput>(&output);
        Assert.AreEqual(incrementDamage, output.GetIncrementDamage());
        Assert.AreEqual(damage, output.GetDamage());
        Assert.IsNull(output.GetTimeOfFailure());
        Assert.AreEqual(verticalDistanceWaterLevelElevation, output.GetVerticalDistanceWaterLevelElevation());
        Assert.IsNull(output.GetRepresentativeWaveRunup2P());
        Assert.IsNull(output.GetCumulativeOverload());
    }

    [Test]
    public void ConstructorVerticalDistanceWaterLevelElevationNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action =
                &GrassRevetmentOvertoppingTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithVerticalDistanceWaterLevelElevationNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "verticalDistanceWaterLevelElevation must be set.");
    }
}
}
