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

using DiKErnel.Core.Data;
using DiKErnel.Core.Exceptions;
using DiKErnel.Integration.Data.GrassRevetmentWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.Output
{
    [TestFixture]
    public class GrassRevetmentWaveImpactTimeDependentOutputTest
    {
        

        private static GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties CreateFullyConfiguredConstructionProperties()
        {
            return new GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = Random.NextDouble(),
                Damage = Random.NextDouble(),
                TimeOfFailure = Random.Next(),
                LoadingRevetment = Random.NextBoolean(),
                UpperLimitLoading = Random.NextDouble(),
                LowerLimitLoading = Random.NextDouble(),
                MinimumWaveHeight = Random.NextDouble(),
                MaximumWaveHeight = Random.NextDouble(),
                WaveAngleImpact = Random.NextDouble(),
                WaveHeightImpact = Random.NextDouble()
            };
        }

        private static GrassRevetmentWaveImpactTimeDependentOutput CreateOutputWithConstructionPropertiesWithLoadingRevetmentNull()
        {
            GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();
            
            constructionProperties.LoadingRevetment = null;

            return new GrassRevetmentWaveImpactTimeDependentOutput(constructionProperties);
        }

        private static GrassRevetmentWaveImpactTimeDependentOutput CreateOutputWithConstructionPropertiesWithUpperLimitLoadingNull()
        {
            GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();
            
            constructionProperties.UpperLimitLoading = null;

            return new GrassRevetmentWaveImpactTimeDependentOutput(constructionProperties);
        }

        private static GrassRevetmentWaveImpactTimeDependentOutput CreateOutputWithConstructionPropertiesWithLowerLimitLoadingNull()
        {
            GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();
            
            constructionProperties.LowerLimitLoading = null;

            return new GrassRevetmentWaveImpactTimeDependentOutput(constructionProperties);
        }

        [Test]
    public void Constructor_WithAllValuesSet_ExpectedValues()
    {
        // Setup
        var incrementDamage = 0.1;
        var damage = 0.2;
        var timeOfFailure = 3;
        var loadingRevetment = true;
        var upperLimitLoading = 0.4;
        var lowerLimitLoading = 0.5;
        var minimumWaveHeight = 0.6;
        var maximumWaveHeight = 0.7;
        var waveAngleImpact = 0.8;
        var waveHeightImpact = 0.9;

        GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties.IncrementDamage = incrementDamage);
        constructionProperties.Damage = damage);
        constructionProperties.TimeOfFailure = timeOfFailure);
        constructionProperties.LoadingRevetment = loadingRevetment);
        constructionProperties.UpperLimitLoading = upperLimitLoading);
        constructionProperties.LowerLimitLoading = lowerLimitLoading);
        constructionProperties.MinimumWaveHeight = minimumWaveHeight);
        constructionProperties.MaximumWaveHeight = maximumWaveHeight);
        constructionProperties.WaveAngleImpact = waveAngleImpact);
        constructionProperties.WaveHeightImpact = waveHeightImpact);

        // Call
        const GrassRevetmentWaveImpactTimeDependentOutput output(constructionProperties);

        // Assert
        Assert.IsInstanceOf<TimeDependentOutput>(&output);
        Assert.AreEqual(incrementDamage, output.GetIncrementDamage());
        Assert.AreEqual(damage, output.GetDamage());
        Assert.AreEqual(timeOfFailure, *output.GetTimeOfFailure());
        Assert.AreEqual(loadingRevetment, output.GetLoadingRevetment());
        Assert.AreEqual(upperLimitLoading, output.GetUpperLimitLoading());
        Assert.AreEqual(lowerLimitLoading, output.GetLowerLimitLoading());
        Assert.AreEqual(minimumWaveHeight, *output.GetMinimumWaveHeight());
        Assert.AreEqual(maximumWaveHeight, *output.GetMaximumWaveHeight());
        Assert.AreEqual(waveAngleImpact, *output.GetWaveAngleImpact());
        Assert.AreEqual(waveHeightImpact, *output.GetWaveHeightImpact());
    }

        [Test]
    public void Constructor_WithNullValues_ExpectedValues()
    {
        // Setup
        var incrementDamage = 0.1;
        var damage = 0.2;
        var loadingRevetment = false;
        var upperLimitLoading = 0.3;
        var lowerLimitLoading = 0.4;

        GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties.IncrementDamage = incrementDamage);
        constructionProperties.Damage = damage);
        constructionProperties.TimeOfFailure = null;
        constructionProperties.LoadingRevetment = loadingRevetment);
        constructionProperties.UpperLimitLoading = upperLimitLoading);
        constructionProperties.LowerLimitLoading = lowerLimitLoading);
        constructionProperties.MinimumWaveHeight = null;
        constructionProperties.MaximumWaveHeight = null;
        constructionProperties.WaveAngleImpact = null;
        constructionProperties.WaveHeightImpact = null;

        // Call
        const GrassRevetmentWaveImpactTimeDependentOutput output(constructionProperties);

        // Assert
        Assert.IsInstanceOf<TimeDependentOutput>(&output);
        Assert.AreEqual(incrementDamage, output.GetIncrementDamage());
        Assert.AreEqual(damage, output.GetDamage());
        Assert.IsNull(output.GetTimeOfFailure());
        Assert.AreEqual(loadingRevetment, output.GetLoadingRevetment());
        Assert.AreEqual(upperLimitLoading, output.GetUpperLimitLoading());
        Assert.AreEqual(lowerLimitLoading, output.GetLowerLimitLoading());
        Assert.IsNull(output.GetMinimumWaveHeight());
        Assert.IsNull(output.GetMaximumWaveHeight());
        Assert.IsNull(output.GetWaveAngleImpact());
        Assert.IsNull(output.GetWaveHeightImpact());
    }

        [Test]
    public void Constructor_LoadingRevetmentNull_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &GrassRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithLoadingRevetmentNull;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "loadingRevetment must be set.");
    }

        [Test]
    public void Constructor_UpperLimitLoadingNull_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &GrassRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithUpperLimitLoadingNull;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "upperLimitLoading must be set.");
    }

        [Test]
    public void Constructor_LowerLimitLoadingNull_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &GrassRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithLowerLimitLoadingNull;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "lowerLimitLoading must be set.");
    }
}
}
