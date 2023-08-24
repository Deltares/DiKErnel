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
            constructionProperties->_incrementDamage = make_unique<double>(0.1);
            constructionProperties->_damage = make_unique<double>(0.2);
            constructionProperties->_timeOfFailure = make_unique<int>(3);
            constructionProperties->_outerSlope = make_unique<double>(0.4);
            constructionProperties->_slopeUpperLevel = make_unique<double>(0.5);
            constructionProperties->_slopeUpperPosition = make_unique<double>(0.6);
            constructionProperties->_slopeLowerLevel = make_unique<double>(0.7);
            constructionProperties->_slopeLowerPosition = make_unique<double>(0.8);
            constructionProperties->_loadingRevetment = make_unique<bool>(true);
            constructionProperties->_surfSimilarityParameter = make_unique<double>(0.9);
            constructionProperties->_waveSteepnessDeepWater = make_unique<double>(1.0);
            constructionProperties->_upperLimitLoading = make_unique<double>(1.1);
            constructionProperties->_lowerLimitLoading = make_unique<double>(1.2);
            constructionProperties->_depthMaximumWaveLoad = make_unique<double>(1.3);
            constructionProperties->_distanceMaximumWaveElevation = make_unique<double>(1.4);
            constructionProperties->_normativeWidthOfWaveImpact = make_unique<double>(1.5);
            constructionProperties->_hydraulicLoad = make_unique<double>(1.6);
            constructionProperties->_waveAngleImpact = make_unique<double>(1.7);
            constructionProperties->_resistance = make_unique<double>(1.8);
            constructionProperties->_referenceTimeDegradation = make_unique<double>(1.9);
            constructionProperties->_referenceDegradation = make_unique<double>(2.0);

            return constructionProperties;
        }

        static void CreateOutputWithConstructionPropertiesWithOuterSlopeNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_outerSlope = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSlopeUpperLevelNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_slopeUpperLevel = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSlopeUpperPositionNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_slopeUpperPosition = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSlopeLowerLevelNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_slopeLowerLevel = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSlopeLowerPositionNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_slopeLowerPosition = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithLoadingRevetmentNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_loadingRevetment = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithSurfSimilarityParameterNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_surfSimilarityParameter = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithWaveSteepnessDeepWaterNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_waveSteepnessDeepWater = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithUpperLimitLoadingNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_upperLimitLoading = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithLowerLimitLoadingNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_lowerLimitLoading = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithDepthMaximumWaveLoadNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_depthMaximumWaveLoad = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithDistanceMaximumWaveElevationNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_distanceMaximumWaveElevation = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithNormativeWidthOfWaveImpactNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_normativeWidthOfWaveImpact = nullptr;

            // Call
            const NaturalStoneRevetmentTimeDependentOutput output(*constructionProperties);
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
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
        constructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);
        constructionProperties._outerSlope = make_unique<double>(outerSlope);
        constructionProperties._slopeUpperLevel = make_unique<double>(slopeUpperLevel);
        constructionProperties._slopeUpperPosition = make_unique<double>(slopeUpperPosition);
        constructionProperties._slopeLowerLevel = make_unique<double>(slopeLowerLevel);
        constructionProperties._slopeLowerPosition = make_unique<double>(slopeLowerPosition);
        constructionProperties._loadingRevetment = make_unique<bool>(loadingRevetment);
        constructionProperties._surfSimilarityParameter = make_unique<double>(surfSimilarityParameter);
        constructionProperties._waveSteepnessDeepWater = make_unique<double>(waveSteepnessDeepWater);
        constructionProperties._upperLimitLoading = make_unique<double>(upperLimitLoading);
        constructionProperties._lowerLimitLoading = make_unique<double>(lowerLimitLoading);
        constructionProperties._depthMaximumWaveLoad = make_unique<double>(depthMaximumWaveLoad);
        constructionProperties._distanceMaximumWaveElevation = make_unique<double>(distanceMaximumWaveElevation);
        constructionProperties._normativeWidthOfWaveImpact = make_unique<double>(normativeWidthOfWaveImpact);
        constructionProperties._hydraulicLoad = make_unique<double>(hydraulicLoad);
        constructionProperties._waveAngleImpact = make_unique<double>(waveAngleImpact);
        constructionProperties._resistance = make_unique<double>(resistance);
        constructionProperties._referenceTimeDegradation = make_unique<double>(referenceTimeDegradation);
        constructionProperties._referenceDegradation = make_unique<double>(referenceDegradation);

        // Call
        const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(timeOfFailure, *output.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(outerSlope, output.GetOuterSlope());
        ASSERT_DOUBLE_EQ(slopeUpperLevel, output.GetSlopeUpperLevel());
        ASSERT_DOUBLE_EQ(slopeUpperPosition, output.GetSlopeUpperPosition());
        ASSERT_DOUBLE_EQ(slopeLowerLevel, output.GetSlopeLowerLevel());
        ASSERT_DOUBLE_EQ(slopeLowerPosition, output.GetSlopeLowerPosition());
        ASSERT_EQ(loadingRevetment, output.GetLoadingRevetment());
        ASSERT_DOUBLE_EQ(surfSimilarityParameter, output.GetSurfSimilarityParameter());
        ASSERT_DOUBLE_EQ(waveSteepnessDeepWater, output.GetWaveSteepnessDeepWater());
        ASSERT_DOUBLE_EQ(upperLimitLoading, output.GetUpperLimitLoading());
        ASSERT_DOUBLE_EQ(lowerLimitLoading, output.GetLowerLimitLoading());
        ASSERT_DOUBLE_EQ(depthMaximumWaveLoad, output.GetDepthMaximumWaveLoad());
        ASSERT_DOUBLE_EQ(distanceMaximumWaveElevation, output.GetDistanceMaximumWaveElevation());
        ASSERT_DOUBLE_EQ(normativeWidthOfWaveImpact, output.GetNormativeWidthOfWaveImpact());
        ASSERT_DOUBLE_EQ(hydraulicLoad, *output.GetHydraulicLoad());
        ASSERT_DOUBLE_EQ(waveAngleImpact, *output.GetWaveAngleImpact());
        ASSERT_DOUBLE_EQ(resistance, *output.GetResistance());
        ASSERT_DOUBLE_EQ(referenceTimeDegradation, *output.GetReferenceTimeDegradation());
        ASSERT_DOUBLE_EQ(referenceDegradation, *output.GetReferenceDegradation());
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
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
        constructionProperties._timeOfFailure = nullptr;
        constructionProperties._outerSlope = make_unique<double>(outerSlope);
        constructionProperties._slopeUpperLevel = make_unique<double>(slopeUpperLevel);
        constructionProperties._slopeUpperPosition = make_unique<double>(slopeUpperPosition);
        constructionProperties._slopeLowerLevel = make_unique<double>(slopeLowerLevel);
        constructionProperties._slopeLowerPosition = make_unique<double>(slopeLowerPosition);
        constructionProperties._loadingRevetment = make_unique<bool>(loadingRevetment);
        constructionProperties._surfSimilarityParameter = make_unique<double>(surfSimilarityParameter);
        constructionProperties._waveSteepnessDeepWater = make_unique<double>(waveSteepnessDeepWater);
        constructionProperties._upperLimitLoading = make_unique<double>(upperLimitLoading);
        constructionProperties._lowerLimitLoading = make_unique<double>(lowerLimitLoading);
        constructionProperties._depthMaximumWaveLoad = make_unique<double>(depthMaximumWaveLoad);
        constructionProperties._distanceMaximumWaveElevation = make_unique<double>(distanceMaximumWaveElevation);
        constructionProperties._normativeWidthOfWaveImpact = make_unique<double>(normativeWidthOfWaveImpact);
        constructionProperties._hydraulicLoad = nullptr;
        constructionProperties._waveAngleImpact = nullptr;
        constructionProperties._resistance = nullptr;
        constructionProperties._referenceTimeDegradation = nullptr;
        constructionProperties._referenceDegradation = nullptr;

        // Call
        const NaturalStoneRevetmentTimeDependentOutput output(constructionProperties);

        // Assert
        AssertHelper::AssertIsInstanceOf<TimeDependentOutput>(&output);
        ASSERT_DOUBLE_EQ(incrementDamage, output.GetIncrementDamage());
        ASSERT_DOUBLE_EQ(damage, output.GetDamage());
        ASSERT_EQ(nullptr, output.GetTimeOfFailure());
        ASSERT_DOUBLE_EQ(outerSlope, output.GetOuterSlope());
        ASSERT_DOUBLE_EQ(slopeUpperLevel, output.GetSlopeUpperLevel());
        ASSERT_DOUBLE_EQ(slopeUpperPosition, output.GetSlopeUpperPosition());
        ASSERT_DOUBLE_EQ(slopeLowerLevel, output.GetSlopeLowerLevel());
        ASSERT_DOUBLE_EQ(slopeLowerPosition, output.GetSlopeLowerPosition());
        ASSERT_EQ(loadingRevetment, output.GetLoadingRevetment());
        ASSERT_DOUBLE_EQ(surfSimilarityParameter, output.GetSurfSimilarityParameter());
        ASSERT_DOUBLE_EQ(waveSteepnessDeepWater, output.GetWaveSteepnessDeepWater());
        ASSERT_DOUBLE_EQ(upperLimitLoading, output.GetUpperLimitLoading());
        ASSERT_DOUBLE_EQ(lowerLimitLoading, output.GetLowerLimitLoading());
        ASSERT_DOUBLE_EQ(depthMaximumWaveLoad, output.GetDepthMaximumWaveLoad());
        ASSERT_DOUBLE_EQ(distanceMaximumWaveElevation, output.GetDistanceMaximumWaveElevation());
        ASSERT_DOUBLE_EQ(normativeWidthOfWaveImpact, output.GetNormativeWidthOfWaveImpact());
        ASSERT_EQ(nullptr, output.GetHydraulicLoad());
        ASSERT_EQ(nullptr, output.GetWaveAngleImpact());
        ASSERT_EQ(nullptr, output.GetResistance());
        ASSERT_EQ(nullptr, output.GetReferenceTimeDegradation());
        ASSERT_EQ(nullptr, output.GetReferenceDegradation());
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
