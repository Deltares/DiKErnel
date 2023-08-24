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
    public class GrassRevetmentOvertoppingLocationConstructionPropertiesTest
    {

        [Test]
    public void Constructor_ExpectedValues()
    {
        // Setup
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var x = 0.1;

        // Call
        const GrassRevetmentOvertoppingLocationConstructionProperties constructionProperties(x, topLayerType);

        // Assert
        Assert.IsInstanceOf<RevetmentLocationConstructionPropertiesBase>(constructionProperties);
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        Assert.AreEqual(x, constructionProperties.GetX());
        Assert.IsNull(constructionProperties.GetInitialDamage());
        Assert.IsNull(constructionProperties.GetFailureNumber());
        Assert.IsNull(constructionProperties.GetCriticalCumulativeOverload());
        Assert.IsNull(constructionProperties.GetCriticalFrontVelocity());
        Assert.IsNull(constructionProperties.GetIncreasedLoadTransitionAlphaM());
        Assert.IsNull(constructionProperties.GetReducedStrengthTransitionAlphaS());
        Assert.IsNull(constructionProperties.GetAverageNumberOfWavesCtm());
        Assert.IsNull(constructionProperties.GetFixedNumberOfWaves());
        Assert.IsNull(constructionProperties.GetFrontVelocityCwo());
        Assert.IsNull(constructionProperties.GetAccelerationAlphaAForCrest());
        Assert.IsNull(constructionProperties.GetAccelerationAlphaAForInnerSlope());
        Assert.IsNull(constructionProperties.GetDikeHeight());
    }

        [Test]
    public void GivenConstructionProperties_WhenAllInputSet_ThenExpectedValues()
    {
        // Given
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var x = 0.1;
        var initialDamage = 0.2;
        var failureNumber = 0.3;
        var criticalCumulativeOverload = 0.4;
        var criticalFrontVelocity = 0.5;
        var increasedLoadTransitionAlphaM = 0.6;
        var reducedStrengthTransitionAlphaS = 0.7;
        var averageNumberOfWavesCtm = 0.8;
        var fixedNumberOfWaves = 9;
        var frontVelocityCwo = 1.0;
        var accelerationAlphaAForCrest = 1.1;
        var accelerationAlphaAForInnerSlope = 1.2;
        var dikeHeight = 1.3;

        GrassRevetmentOvertoppingLocationConstructionProperties constructionProperties(x, topLayerType);

        // When
        constructionProperties.SetInitialDamage(initialDamage));
        constructionProperties.SetFailureNumber(failureNumber));
        constructionProperties.SetCriticalCumulativeOverload(criticalCumulativeOverload));
        constructionProperties.SetCriticalFrontVelocity(criticalFrontVelocity));
        constructionProperties.SetIncreasedLoadTransitionAlphaM(increasedLoadTransitionAlphaM));
        constructionProperties.SetReducedStrengthTransitionAlphaS(reducedStrengthTransitionAlphaS));
        constructionProperties.SetAverageNumberOfWavesCtm(averageNumberOfWavesCtm));
        constructionProperties.SetFixedNumberOfWaves(fixedNumberOfWaves));
        constructionProperties.SetFrontVelocityCwo(frontVelocityCwo));
        constructionProperties.SetAccelerationAlphaAForCrest(accelerationAlphaAForCrest));
        constructionProperties.SetAccelerationAlphaAForInnerSlope(accelerationAlphaAForInnerSlope));
        constructionProperties.SetDikeHeight(dikeHeight));

        // Then
        ASSERT_EQ(topLayerType, constructionProperties.GetTopLayerType());
        Assert.AreEqual(x, constructionProperties.GetX());
        Assert.AreEqual(initialDamage, constructionProperties.GetInitialDamage());
        Assert.AreEqual(failureNumber, constructionProperties.GetFailureNumber());
        Assert.AreEqual(criticalCumulativeOverload, constructionProperties.GetCriticalCumulativeOverload());
        Assert.AreEqual(criticalFrontVelocity, constructionProperties.GetCriticalFrontVelocity());
        Assert.AreEqual(increasedLoadTransitionAlphaM, constructionProperties.GetIncreasedLoadTransitionAlphaM());
        Assert.AreEqual(reducedStrengthTransitionAlphaS, constructionProperties.GetReducedStrengthTransitionAlphaS());
        Assert.AreEqual(averageNumberOfWavesCtm, constructionProperties.GetAverageNumberOfWavesCtm());
        Assert.AreEqual(fixedNumberOfWaves, constructionProperties.GetFixedNumberOfWaves());
        Assert.AreEqual(frontVelocityCwo, constructionProperties.GetFrontVelocityCwo());
        Assert.AreEqual(accelerationAlphaAForCrest, constructionProperties.GetAccelerationAlphaAForCrest());
        Assert.AreEqual(accelerationAlphaAForInnerSlope, constructionProperties.GetAccelerationAlphaAForInnerSlope());
        Assert.AreEqual(dikeHeight, constructionProperties.GetDikeHeight());
    }
}
}
