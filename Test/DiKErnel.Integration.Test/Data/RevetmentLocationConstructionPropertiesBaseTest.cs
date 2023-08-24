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
    public class RevetmentLocationConstructionPropertiesBaseTest
    {

        [Test]
    public void Constructor_ExpectedValues()
    {
        // Setup
        var x = 0.1;

        // Call
        const RevetmentLocationConstructionPropertiesMock constructionProperties(x);

        // Assert
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_EQ(nullptr, constructionProperties.GetInitialDamage());
        ASSERT_EQ(nullptr, constructionProperties.GetFailureNumber());
    }

        [Test]
    public void GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues()
    {
        // Given
        var x = 0.1;
        var initialDamage = 0.2;
        var failureNumber = 0.3;

        RevetmentLocationConstructionPropertiesMock constructionProperties(x);

        // When
        constructionProperties.SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties.SetFailureNumber(make_unique<double>(failureNumber));

        // Then
        ASSERT_DOUBLE_EQ(x, constructionProperties.GetX());
        ASSERT_DOUBLE_EQ(initialDamage, *constructionProperties.GetInitialDamage());
        ASSERT_DOUBLE_EQ(failureNumber, *constructionProperties.GetFailureNumber());
    }
}

}
