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
    public class NaturalStoneRevetmentTimeDependentOutputTest
    {

    struct NaturalStoneRevetmentTimeDependentOutputTest : Test
    {
        static unique_ptr<NaturalStoneRevetmentTimeDependentOutputConstructionProperties> CreateFullyConfiguredConstructionProperties()
        {
            var constructionProperties = make_unique<NaturalStoneRevetmentTimeDependentOutputConstructionProperties>();
            constructionProperties->IncrementDamage = 0.1);
            constructionProperties->Damage = 0.2);
            constructionProperties->TimeOfFailure = 3);
            constructionProperties->OuterSlope = 0.4);
            constructionProperties->SlopeUpperLevel = 0.5);
            constructionProperties->SlopeUpperPosition = 0.6);
            constructionProperties->SlopeLowerLevel = 0.7);
            constructionProperties->SlopeLowerPosition = 0.8);
            constructionProperties->LoadingRevetment = true);
            constructionProperties->SurfSimilarityParameter = 0.9);
            constructionProperties->WaveSteepnessDeepWater = 1.0);
            constructionProperties->UpperLimitLoading = 1.1);
            constructionProperties->LowerLimitLoading = 1.2);
            constructionProperties->DepthMaximumWaveLoad = 1.3);
            constructionProperties->DistanceMaximumWaveElevation = 1.4);
            constructionProperties->NormativeWidthOfWaveImpact = 1.5);
            constructionProperties->HydraulicLoad = 1.6);
            constructionProperties->WaveAngleImpact = 1.7);
            constructionProperties->Resistance = 1.8);
            constructionProperties->ReferenceTimeDegradation = 1.9);
            constructionProperties->ReferenceDegradation = 2.0);

            return constructionProperties;
        }

        static void CreateOutputWithConstructionPropertiesWithOuterSlopeNull()
        {
            // Setup
            var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->OuterSlope = null;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSlopeUpperLevelNull()
        {
            // Setup
            var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->SlopeUpperLevel = null;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSlopeUpperPositionNull()
        {
            // Setup
            var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->SlopeUpperPosition = null;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSlopeLowerLevelNull()
        {
            // Setup
            var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->SlopeLowerLevel = null;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSlopeLowerPositionNull()
        {
            // Setup
            var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->SlopeLowerPosition = null;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithLoadingRevetmentNull()
        {
            // Setup
            var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->LoadingRevetment = null;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSurfSimilarityParameterNull()
        {
            // Setup
            var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->SurfSimilarityParameter = null;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithWaveSteepnessDeepWaterNull()
        {
            // Setup
            var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->WaveSteepnessDeepWater = null;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithUpperLimitLoadingNull()
        {
            // Setup
            var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->UpperLimitLoading = null;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithLowerLimitLoadingNull()
        {
            // Setup
            var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->LowerLimitLoading = null;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithDepthMaximumWaveLoadNull()
        {
            // Setup
            var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->DepthMaximumWaveLoad = null;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithDistanceMaximumWaveElevationNull()
        {
            // Setup
            var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->DistanceMaximumWaveElevation = null;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithNormativeWidthOfWaveImpactNull()
        {
            // Setup
            var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->NormativeWidthOfWaveImpact = null;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);
        }
    };

        [Test]
    public void Constructor_WithAllValuesSet_ExpectedValues()
    {
        // Setup
        var incrementDamage = 0.1;
        var damage = 0.2;
        var timeOfFailure = 3;
        var outerSlope = 0.4;
        var slopeUpperLevel = 0.5;
        var slopeUpperPosition = 0.6;
        var slopeLowerLevel = 0.7;
        var slopeLowerPosition = 0.8;
        var loadingRevetment = true;
        var surfSimilarityParameter = 0.9;
        var waveSteepnessDeepWater = 1.0;
        var upperLimitLoading = 1.1;
        var lowerLimitLoading = 1.2;
        var depthMaximumWaveLoad = 1.3;
        var distanceMaximumWaveElevation = 1.4;
        var normativeWidthOfWaveImpact = 1.5;
        var hydraulicLoad = 1.6;
        var waveAngleImpact = 1.7;
        var resistance = 1.8;
        var referenceTimeDegradation = 1.9;
        var referenceDegradation = 2.0;

        NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties.IncrementDamage = incrementDamage);
        constructionProperties.Damage = damage);
        constructionProperties.TimeOfFailure = timeOfFailure);
        constructionProperties.OuterSlope = outerSlope);
        constructionProperties.SlopeUpperLevel = slopeUpperLevel);
        constructionProperties.SlopeUpperPosition = slopeUpperPosition);
        constructionProperties.SlopeLowerLevel = slopeLowerLevel);
        constructionProperties.SlopeLowerPosition = slopeLowerPosition);
        constructionProperties.LoadingRevetment = loadingRevetment);
        constructionProperties.SurfSimilarityParameter = surfSimilarityParameter);
        constructionProperties.WaveSteepnessDeepWater = waveSteepnessDeepWater);
        constructionProperties.UpperLimitLoading = upperLimitLoading);
        constructionProperties.LowerLimitLoading = lowerLimitLoading);
        constructionProperties.DepthMaximumWaveLoad = depthMaximumWaveLoad);
        constructionProperties.DistanceMaximumWaveElevation = distanceMaximumWaveElevation);
        constructionProperties.NormativeWidthOfWaveImpact = normativeWidthOfWaveImpact);
        constructionProperties.HydraulicLoad = hydraulicLoad);
        constructionProperties.WaveAngleImpact = waveAngleImpact);
        constructionProperties.Resistance = resistance);
        constructionProperties.ReferenceTimeDegradation = referenceTimeDegradation);
        constructionProperties.ReferenceDegradation = referenceDegradation);

        // Call
        const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);

        // Assert
        Assert.IsInstanceOf<TimeDependentOutput>(&output);
        Assert.AreEqual(incrementDamage, output.GetIncrementDamage());
        Assert.AreEqual(damage, output.GetDamage());
        Assert.AreEqual(timeOfFailure, *output.GetTimeOfFailure());
        Assert.AreEqual(outerSlope, output.GetOuterSlope());
        Assert.AreEqual(slopeUpperLevel, output.GetSlopeUpperLevel());
        Assert.AreEqual(slopeUpperPosition, output.GetSlopeUpperPosition());
        Assert.AreEqual(slopeLowerLevel, output.GetSlopeLowerLevel());
        Assert.AreEqual(slopeLowerPosition, output.GetSlopeLowerPosition());
        Assert.AreEqual(loadingRevetment, output.GetLoadingRevetment());
        Assert.AreEqual(surfSimilarityParameter, output.GetSurfSimilarityParameter());
        Assert.AreEqual(waveSteepnessDeepWater, output.GetWaveSteepnessDeepWater());
        Assert.AreEqual(upperLimitLoading, output.GetUpperLimitLoading());
        Assert.AreEqual(lowerLimitLoading, output.GetLowerLimitLoading());
        Assert.AreEqual(depthMaximumWaveLoad, output.GetDepthMaximumWaveLoad());
        Assert.AreEqual(distanceMaximumWaveElevation, output.GetDistanceMaximumWaveElevation());
        Assert.AreEqual(normativeWidthOfWaveImpact, output.GetNormativeWidthOfWaveImpact());
        Assert.AreEqual(hydraulicLoad, *output.GetHydraulicLoad());
        Assert.AreEqual(waveAngleImpact, *output.GetWaveAngleImpact());
        Assert.AreEqual(resistance, *output.GetResistance());
        Assert.AreEqual(referenceTimeDegradation, *output.GetReferenceTimeDegradation());
        Assert.AreEqual(referenceDegradation, *output.GetReferenceDegradation());
    }

        [Test]
    public void Constructor_WithNullPtrValues_ExpectedValues()
    {
        // Setup
        var incrementDamage = 0.1;
        var damage = 0.2;
        var outerSlope = 0.3;
        var slopeUpperLevel = 0.4;
        var slopeUpperPosition = 0.5;
        var slopeLowerLevel = 0.6;
        var slopeLowerPosition = 0.7;
        var loadingRevetment = false;
        var surfSimilarityParameter = 0.8;
        var waveSteepnessDeepWater = 0.9;
        var upperLimitLoading = 1.0;
        var lowerLimitLoading = 1.1;
        var depthMaximumWaveLoad = 1.2;
        var distanceMaximumWaveElevation = 1.3;
        var normativeWidthOfWaveImpact = 1.4;

        NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties.IncrementDamage = incrementDamage);
        constructionProperties.Damage = damage);
        constructionProperties.TimeOfFailure = null;
        constructionProperties.OuterSlope = outerSlope);
        constructionProperties.SlopeUpperLevel = slopeUpperLevel);
        constructionProperties.SlopeUpperPosition = slopeUpperPosition);
        constructionProperties.SlopeLowerLevel = slopeLowerLevel);
        constructionProperties.SlopeLowerPosition = slopeLowerPosition);
        constructionProperties.LoadingRevetment = loadingRevetment);
        constructionProperties.SurfSimilarityParameter = surfSimilarityParameter);
        constructionProperties.WaveSteepnessDeepWater = waveSteepnessDeepWater);
        constructionProperties.UpperLimitLoading = upperLimitLoading);
        constructionProperties.LowerLimitLoading = lowerLimitLoading);
        constructionProperties.DepthMaximumWaveLoad = depthMaximumWaveLoad);
        constructionProperties.DistanceMaximumWaveElevation = distanceMaximumWaveElevation);
        constructionProperties.NormativeWidthOfWaveImpact = normativeWidthOfWaveImpact);
        constructionProperties.HydraulicLoad = null;
        constructionProperties.WaveAngleImpact = null;
        constructionProperties.Resistance = null;
        constructionProperties.ReferenceTimeDegradation = null;
        constructionProperties.ReferenceDegradation = null;

        // Call
        const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);

        // Assert
        Assert.IsInstanceOf<TimeDependentOutput>(&output);
        Assert.AreEqual(incrementDamage, output.GetIncrementDamage());
        Assert.AreEqual(damage, output.GetDamage());
        Assert.IsNull(output.GetTimeOfFailure());
        Assert.AreEqual(outerSlope, output.GetOuterSlope());
        Assert.AreEqual(slopeUpperLevel, output.GetSlopeUpperLevel());
        Assert.AreEqual(slopeUpperPosition, output.GetSlopeUpperPosition());
        Assert.AreEqual(slopeLowerLevel, output.GetSlopeLowerLevel());
        Assert.AreEqual(slopeLowerPosition, output.GetSlopeLowerPosition());
        Assert.AreEqual(loadingRevetment, output.GetLoadingRevetment());
        Assert.AreEqual(surfSimilarityParameter, output.GetSurfSimilarityParameter());
        Assert.AreEqual(waveSteepnessDeepWater, output.GetWaveSteepnessDeepWater());
        Assert.AreEqual(upperLimitLoading, output.GetUpperLimitLoading());
        Assert.AreEqual(lowerLimitLoading, output.GetLowerLimitLoading());
        Assert.AreEqual(depthMaximumWaveLoad, output.GetDepthMaximumWaveLoad());
        Assert.AreEqual(distanceMaximumWaveElevation, output.GetDistanceMaximumWaveElevation());
        Assert.AreEqual(normativeWidthOfWaveImpact, output.GetNormativeWidthOfWaveImpact());
        Assert.IsNull(output.GetHydraulicLoad());
        Assert.IsNull(output.GetWaveAngleImpact());
        Assert.IsNull(output.GetResistance());
        Assert.IsNull(output.GetReferenceTimeDegradation());
        Assert.IsNull(output.GetReferenceDegradation());
    }

        [Test]
    public void Constructor_OuterSlopeNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithOuterSlopeNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "outerSlope must be set.");
    }

        [Test]
    public void Constructor_SlopeUpperLevelNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithSlopeUpperLevelNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "slopeUpperLevel must be set.");
    }

        [Test]
    public void Constructor_SlopeUpperPositionNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithSlopeUpperPositionNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "slopeUpperPosition must be set.");
    }

        [Test]
    public void Constructor_SlopeLowerLevelNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithSlopeLowerLevelNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "slopeLowerLevel must be set.");
    }

        [Test]
    public void Constructor_SlopeLowerPositionNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithSlopeLowerPositionNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "slopeLowerPosition must be set.");
    }

        [Test]
    public void Constructor_LoadingRevetmentNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithLoadingRevetmentNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "loadingRevetment must be set.");
    }

        [Test]
    public void Constructor_SurfSimilarityParameterNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithSurfSimilarityParameterNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "surfSimilarityParameter must be set.");
    }

        [Test]
    public void Constructor_LowerLimitLoadingNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithLowerLimitLoadingNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "lowerLimitLoading must be set.");
    }

        [Test]
    public void Constructor_DepthMaximumWaveLoadNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithDepthMaximumWaveLoadNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "depthMaximumWaveLoad must be set.");
    }

        [Test]
    public void Constructor_DistanceMaximumWaveElevationNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &
                NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithDistanceMaximumWaveElevationNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "distanceMaximumWaveElevation must be set.");
    }

        [Test]
    public void Constructor_NormativeWidthOfWaveImpactNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &
                NaturalStoneRevetmentTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithNormativeWidthOfWaveImpactNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "normativeWidthOfWaveImpact must be set.");
    }
}

}
