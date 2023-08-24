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
        static void CreateOutputWithConstructionPropertiesWithVerticalDistanceWaterLevelElevationNullPtr()
        {
            // Setup
            GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties constructionProperties;
            constructionProperties._incrementDamage = make_unique<double>(0.1);
            constructionProperties._damage = make_unique<double>(0.2);
            constructionProperties._timeOfFailure = make_unique<int>(3);
            constructionProperties._verticalDistanceWaterLevelElevation = nullptr;
            constructionProperties._representativeWaveRunup2P = make_unique<double>(0.4);
            constructionProperties._cumulativeOverload = make_unique<double>(0.5);

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
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
        constructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);
        constructionProperties._verticalDistanceWaterLevelElevation = make_unique<double>(verticalDistanceWaterLevelElevation);
        constructionProperties._representativeWaveRunup2P = make_unique<double>(representativeWaveRunup2P);
        constructionProperties._cumulativeOverload = make_unique<double>(cumulativeOverload);

        // Call
        const GrassRevetmentOvertoppingTimeDependentOutput output(constructionProperties);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(timeOfFailure, *output.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(verticalDistanceWaterLevelElevation, output.GetVerticalDistanceWaterLevelElevation());
        ASSERT_DOUBLE_EQ(representativeWaveRunup2P, *output.GetRepresentativeWaveRunup2P());
        ASSERT_DOUBLE_EQ(cumulativeOverload, *output.GetCumulativeOverload());
    }

        [Test]
    public void Constructor_WithNullPtrValues_ExpectedValues()
    {
        // Setup
        var incrementDamage = 0.1;
        var damage = 0.2;
        var verticalDistanceWaterLevelElevation = 0.3;

        GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
        constructionProperties._verticalDistanceWaterLevelElevation = make_unique<double>(verticalDistanceWaterLevelElevation);

        // Call
        const GrassRevetmentOvertoppingTimeDependentOutput output(constructionProperties);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(nullptr, output.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(verticalDistanceWaterLevelElevation, output.GetVerticalDistanceWaterLevelElevation());
        ASSERT_EQ(nullptr, output.GetRepresentativeWaveRunup2P());
        ASSERT_EQ(nullptr, output.GetCumulativeOverload());
    }

    [Test]
    public void Constructor_VerticalDistanceWaterLevelElevationNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action =
                &GrassRevetmentOvertoppingTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithVerticalDistanceWaterLevelElevationNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "verticalDistanceWaterLevelElevation must be set.");
    }
}
}
