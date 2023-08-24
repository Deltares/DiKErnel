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

namespace DiKErnel.Integration.Test
{
    [TestFixture]
    public class CalculationInputBuilderTest
    {
        

    struct CalculationInputBuilderTest : Test
    {
        static void AddDefaultProfileAndTimeStep(
            CalculationInputBuilder& builder)
        {
            var startPointX = 0;
            var endPointX = 10;

            builder.AddDikeProfileSegment(startPointX, 10, endPointX, 20);
            builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::OuterToe);
            builder.AddDikeProfilePointData(endPointX, CharacteristicPointType::OuterCrest);
            builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        }

        template <typename T>
        static void GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
            const T& addLocation,
            const string& locationX)
        {
            GivenLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                addLocation, "The location with position " + locationX + " must be between the outer toe and outer crest.");
        }

        static void GivenGrassOvertoppingLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
            const double locationX,
            const string& locationXString)
        {
            GivenLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                [locationX](
            CalculationInputBuilder& builder)
                {
                    builder.AddDikeProfileSegment(10, 20, 30, 40);
                    builder.AddDikeProfileSegment(30, 40, 50, 60);
                    builder.AddDikeProfilePointData(30, CharacteristicPointType::InnerCrest);
                    builder.AddDikeProfilePointData(50, CharacteristicPointType::InnerToe);
                    builder.AddGrassOvertoppingLocation(
                        make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(locationX, GrassRevetmentTopLayerType::ClosedSod));
                },
                "The location with position " + locationXString + " must be on or between the outer crest and inner toe.");
        }

        template <typename T>
        static void GivenLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
            const T& addLocation,
            const string& expectedMessage)
        {
            // Given
            CalculationInputBuilder builder;
            AddDefaultProfileAndTimeStep(builder);
            addLocation(builder);

            // When
            const var result = builder.Build();

            // Then
            ASSERT_FALSE(result->GetSuccessful());

            const auto& events = result->GetEvents();
            ASSERT_EQ(1, events.size());

            EventAssertHelper::AssertEvent(EventType::Error, expectedMessage, events.at(0));
        }
    };

    #pragma region Profile segments

        [Test]
    public void GivenBuilderWithoutDikeProfileSegments_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        const CalculationInputBuilder builder;

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "At least 1 profile segment is required.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithDikeProfileSegmentsAdded_WhenProfileSegmentXCoordinateUnchained_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(10, 20, 20, 30);
        builder.AddDikeProfileSegment(20.01, 30, 30, 40);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(
            EventType::Error,
            "The start point of the profile segment (20.01, 30) must be equal to the end point of the previous profile segment (20, 30).",
            events.at(0));
    }

        [Test]
    public void GivenBuilderWithDikeProfileSegmentsAdded_WhenProfileSegmentZCoordinateUnchained_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(10, 20, 20, 30);
        builder.AddDikeProfileSegment(20, 30.01, 30, 40);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(
            EventType::Error,
            "The start point of the profile segment (20, 30.01) must be equal to the end point of the previous profile segment (20, 30).",
            events.at(0));
    }

        [Test]
    public void GivenBuilderWithDikeProfileSegmentAddedWithoutRoughness_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var startPointX = 10;
        var startPointZ = 20;
        var endPointX = 20;
        var endPointZ = 30;

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ);
        builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(endPointX, CharacteristicPointType::OuterCrest);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(10.1, GrassRevetmentTopLayerType::ClosedSod));
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualProfileData = calculationInput.GetProfileData();
        const auto& actualProfileSegments = actualProfileData.GetProfileSegments();
        ASSERT_EQ(1, actualProfileSegments.size());

        ProfileDataAssertHelper::AssertProfileSegment(startPointX, startPointZ, endPointX, endPointZ, 1.0, actualProfileSegments.at(0));
    }

        [Test]
    public void GivenBuilderWithDikeProfileSegmentAddedWithRoughness_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var startPointX = 10;
        var startPointZ = 20;
        var endPointX = 20;
        var endPointZ = 30;
        var roughnessCoefficient = 13.37;

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, roughnessCoefficient);
        builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(endPointX, CharacteristicPointType::OuterCrest);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(10.1, GrassRevetmentTopLayerType::ClosedSod));
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualProfileData = calculationInput.GetProfileData();
        const auto& actualProfileSegments = actualProfileData.GetProfileSegments();
        ASSERT_EQ(1, actualProfileSegments.size());

        ProfileDataAssertHelper::AssertProfileSegment(startPointX, startPointZ, endPointX, endPointZ, roughnessCoefficient,
                                                      actualProfileSegments.at(0));
    }

        [Test]
    public void GivenBuilderWithDikeProfileSegmentsAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var startPointXSegment1 = 10;
        var startPointZSegment1 = 20;
        var endPointXSegment1 = 20;
        var endPointZSegment1 = 30;
        var endPointXSegment2 = 30;
        var endPointZSegment2 = 40;
        var roughnessCoefficient = 13.37;

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(startPointXSegment1, startPointZSegment1, endPointXSegment1, endPointZSegment1, roughnessCoefficient);
        builder.AddDikeProfileSegment(endPointXSegment1, endPointZSegment1, endPointXSegment2, endPointZSegment2, roughnessCoefficient);
        builder.AddDikeProfilePointData(startPointXSegment1, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(endPointXSegment1, CharacteristicPointType::OuterCrest);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(10.1, GrassRevetmentTopLayerType::ClosedSod));
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualProfileData = calculationInput.GetProfileData();
        const auto& actualProfileSegments = actualProfileData.GetProfileSegments();
        ASSERT_EQ(2, actualProfileSegments.size());

        const auto& profileSegment1 = actualProfileSegments.at(0).get();
        ProfileDataAssertHelper::AssertProfileSegment(startPointXSegment1, startPointZSegment1, endPointXSegment1, endPointZSegment1,
                                                      roughnessCoefficient, profileSegment1);

        const auto& profileSegment2 = actualProfileSegments.at(1).get();
        ProfileDataAssertHelper::AssertProfileSegment(endPointXSegment1, endPointZSegment1, endPointXSegment2, endPointZSegment2,
                                                      roughnessCoefficient, profileSegment2);

        ASSERT_EQ(&profileSegment1.GetEndPoint(), &profileSegment2.GetStartPoint());
    }

    #pragma endregion

    #pragma region Profile point data

        [Test]
    public void GivenBuilderWithDikeProfilePointDataOuterToeNotOnProfileSegmentPoints_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 20, 30);
        builder.AddDikeProfilePointData(10.01, CharacteristicPointType::OuterToe);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The outer toe must be on a start or end point of a profile segment.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithDikeProfilePointDataCrestOuterBermNotOnProfileSegmentPoints_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 20, 30);
        builder.AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(10.01, CharacteristicPointType::CrestOuterBerm);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The crest outer berm must be on a start or end point of a profile segment.",
                                       events.at(0));
    }

        [Test]
    public void GivenBuilderWithDikeProfilePointDataNotchOuterBermNotOnProfileSegmentPoints_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 20, 30);
        builder.AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(10.01, CharacteristicPointType::NotchOuterBerm);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The notch outer berm must be on a start or end point of a profile segment.",
                                       events.at(0));
    }

        [Test]
    public void GivenBuilderWithDikeProfilePointDataOuterCrestNotOnProfileSegmentPoints_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 20, 30);
        builder.AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(10.01, CharacteristicPointType::OuterCrest);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The outer crest must be on a start or end point of a profile segment.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithDikeProfilePointDataInnerCrestNotOnProfileSegmentPoints_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 20, 30);
        builder.AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(20, CharacteristicPointType::OuterCrest);
        builder.AddDikeProfilePointData(20.01, CharacteristicPointType::InnerCrest);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The inner crest must be on a start or end point of a profile segment.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithDikeProfilePointDataInnerToeNotOnProfileSegmentPoints_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 20, 30);
        builder.AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(20, CharacteristicPointType::OuterCrest);
        builder.AddDikeProfilePointData(20.01, CharacteristicPointType::InnerToe);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The inner toe must be on a start or end point of a profile segment.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithoutDikeProfilePointDataOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 30);
        builder.AddDikeProfilePointData(10, CharacteristicPointType::OuterCrest);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The outer toe is required.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithoutDikeProfilePointDataOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 30);
        builder.AddDikeProfilePointData(10, CharacteristicPointType::OuterToe);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The outer crest is required.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithGrassOvertoppingLocationAndWithoutDikeProfilePointDataInnerToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        var startPointX = 10;

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, startPointX, 30);
        builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::OuterCrest);
        builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::InnerCrest);
        builder.AddGrassOvertoppingLocation(
            make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(0.1, GrassRevetmentTopLayerType::ClosedSod));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The inner toe is required.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithGrassOvertoppingLocationAndWithoutDikeProfilePointDataInnerCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        var startPointX = 10;

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, startPointX, 30);
        builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::OuterCrest);
        builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::InnerToe);
        builder.AddGrassOvertoppingLocation(
            make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(0.1, GrassRevetmentTopLayerType::ClosedSod));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The inner crest is required.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithDikeProfilePointDataOnSegmentPoints_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var outerToe = CharacteristicPointType::OuterToe;
        var outerCrest = CharacteristicPointType::OuterCrest;

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(10, 20, 20, 30);
        builder.AddDikeProfilePointData(10, outerToe);
        builder.AddDikeProfilePointData(20, outerCrest);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(10.1, GrassRevetmentTopLayerType::ClosedSod));
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualProfileData = calculationInput.GetProfileData();
        const auto& actualProfileSegments = actualProfileData.GetProfileSegments();
        const auto& actualCharacteristicPoints = actualProfileData.GetCharacteristicPoints();
        ASSERT_EQ(1, actualProfileSegments.size());
        ASSERT_EQ(2, actualCharacteristicPoints.size());

        const auto& actualSegment = actualProfileSegments.at(0).get();
        ProfileDataAssertHelper::AssertCharacteristicPoint(actualSegment.GetStartPoint(), outerToe, actualCharacteristicPoints.at(0));
        ProfileDataAssertHelper::AssertCharacteristicPoint(actualSegment.GetEndPoint(), outerCrest, actualCharacteristicPoints.at(1));
    }

    #pragma endregion

    #pragma region Time steps

        [Test]
    public void GivenBuilderWithoutTimeStepAdded_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20);
        builder.AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(10, CharacteristicPointType::OuterCrest);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0.1, GrassRevetmentTopLayerType::ClosedSod));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "At least 1 time step is required.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithNonSuccessiveTimeStepsAdded_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20);
        builder.AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(10, CharacteristicPointType::OuterCrest);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0.1, GrassRevetmentTopLayerType::ClosedSod));
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddTimeStep(3, 4, 0.3, 0.4, 0.5, 0.6);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(
            EventType::Error,
            "The begin time of the time step (3) must be equal to the end time of the previous time step (2).",
            events.at(0));
    }

        [Test]
    public void GivenBuilderWithTimeStepWithInvalidBeginAndEndTimeAdded_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20);
        builder.AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(10, CharacteristicPointType::OuterCrest);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0.1, GrassRevetmentTopLayerType::ClosedSod));
        builder.AddTimeStep(2, 1, 0.3, 0.4, 0.5, 0.6);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(
            EventType::Error,
            "The begin time of the time step (2) must be smaller than the end time of the time step (1).",
            events.at(0));
    }

        [Test]
    public void GivenBuilderWithTimeStepAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var beginTime = 1;
        var endTime = 2;
        var waterLevel = 0.3;
        var waveHeightHm0 = 0.4;
        var wavePeriodTm10 = 0.5;
        var waveAngle = 0.6;

        var startPointX = 0;
        var endPointX = 10;

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(startPointX, 10, endPointX, 20);
        builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(endPointX, CharacteristicPointType::OuterCrest);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0.1, GrassRevetmentTopLayerType::ClosedSod));
        builder.AddTimeStep(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualTimeDependentInputItems = calculationInput.GetTimeDependentInputItems();
        ASSERT_EQ(1, actualTimeDependentInputItems.size());
        const auto& timeDependentInput = actualTimeDependentInputItems.at(0).get();

        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle,
                                                                     timeDependentInput);
    }

    #pragma endregion

    #pragma region Locations

        [Test]
    public void GivenBuilderWithoutLocationAdded_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "At least 1 location is required.", events.at(0));
    }

    #pragma region Asphalt wave impact

        [Test]
    public void GivenBuilderWithAsphaltWaveImpactLocationWithXOnOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent([](
        CalculationInputBuilder& builder)
            {
                builder.AddAsphaltWaveImpactLocation(
                    make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
                        0, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 0.2, 0.3, 0.4, 0.5));
            }, "0");
    }

        [Test]
    public void GivenBuilderWithAsphaltWaveImpactLocationWithXOnOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent([](
        CalculationInputBuilder& builder)
            {
                builder.AddAsphaltWaveImpactLocation(
                    make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
                        10, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 0.2, 0.3, 0.4, 0.5));
            }, "10");
    }

        [Test]
    public void GivenBuilderWithAsphaltWaveImpactLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        var topLayerType = static_cast<AsphaltRevetmentTopLayerType>(99);
        var constructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            0.1, topLayerType, 0.2, 0.3, 0.4, 0.5);

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddAsphaltWaveImpactLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The location with position 0.1 has an invalid top layer type.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithFullyConfiguredAsphaltWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        var topLayerType = AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete;
        var x = 0.1;
        var failureTension = 0.2;
        var soilElasticity = 0.3;
        var thicknessUpperLayer = 0.4;
        var elasticModulusUpperLayer = 0.5;
        var initialDamage = 0.6;
        var failureNumber = 0.7;
        var densityOfWater = 0.8;
        var thicknessSubLayer = 0.9;
        var elasticModulusSubLayer = 1.0;
        var averageNumberOfWavesCtm = 1.1;
        var fatigueAlpha = 1.2;
        var fatigueBeta = 1.3;
        var impactNumberC = 1.4;
        var stiffnessRelationNu = 1.5;
        const var widthFactors = vector
        {
            pair(1.6, 1.7)
        };
        const var depthFactors = vector
        {
            pair(1.8, 1.9)
        };
        const var impactFactors = vector
        {
            pair(2.0, 2.1)
        };

        var constructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            x, topLayerType, failureTension, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer);

        constructionProperties.SetInitialDamage(initialDamage));
        constructionProperties.SetFailureNumber(failureNumber));
        constructionProperties.SetDensityOfWater(densityOfWater));
        constructionProperties.SetThicknessSubLayer(thicknessSubLayer));
        constructionProperties.SetElasticModulusSubLayer(elasticModulusSubLayer));
        constructionProperties.SetAverageNumberOfWavesCtm(averageNumberOfWavesCtm));
        constructionProperties.SetFatigueAlpha(fatigueAlpha));
        constructionProperties.SetFatigueBeta(fatigueBeta));
        constructionProperties.SetImpactNumberC(impactNumberC));
        constructionProperties.SetStiffnessRelationNu(stiffnessRelationNu));
        constructionProperties.SetWidthFactors(make_unique<vector<pair<double, double>>>(widthFactors));
        constructionProperties.SetDepthFactors(make_unique<vector<pair<double, double>>>(depthFactors));
        constructionProperties.SetImpactFactors(make_unique<vector<pair<double, double>>>(impactFactors));

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddAsphaltWaveImpactLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualLocationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<AsphaltRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(initialDamage, failureNumber, *locationDependentInput);

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, failureTension, densityOfWater, soilElasticity, averageNumberOfWavesCtm,
            impactNumberC, stiffnessRelationNu, *locationDependentInput);

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(thicknessUpperLayer, elasticModulusUpperLayer,
                                                                                  locationDependentInput->GetUpperLayer());

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(thicknessSubLayer, elasticModulusSubLayer,
                                                                                  *locationDependentInput->GetSubLayer());

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFatigue(fatigueAlpha, fatigueBeta,
                                                                                    locationDependentInput->GetFatigue());

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFactors(widthFactors, depthFactors, impactFactors,
                                                                                    *locationDependentInput);
    }

        [Test]
    public void GivenBuilderWithNotFullyConfiguredAsphaltWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        var topLayerType = AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete;
        var x = 0.1;
        var failureTension = 0.2;
        var soilElasticity = 0.3;
        var thicknessUpperLayer = 0.4;
        var elasticModulusUpperLayer = 0.5;

        var constructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            x, topLayerType, failureTension, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer);

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddAsphaltWaveImpactLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualLocationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<AsphaltRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, failureTension, 1025, soilElasticity, 1, 1, 0.35, *locationDependentInput);

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(thicknessUpperLayer, elasticModulusUpperLayer,
                                                                                  locationDependentInput->GetUpperLayer());

        Assert.IsNull(locationDependentInput->GetSubLayer());

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFatigue(0.42, 4.76,
                                                                                    locationDependentInput->GetFatigue());

        const var expectedWidthFactors = vector
        {
            pair(0.1, 0.0392),
            pair(0.2, 0.0738),
            pair(0.3, 0.1002),
            pair(0.4, 0.1162),
            pair(0.5, 0.1213),
            pair(0.6, 0.1168),
            pair(0.7, 0.1051),
            pair(0.8, 0.0890),
            pair(0.9, 0.0712),
            pair(1.0, 0.0541),
            pair(1.1, 0.0391),
            pair(1.2, 0.0269),
            pair(1.3, 0.0216),
            pair(1.4, 0.0150),
            pair(1.5, 0.0105)
        };

        const var expectedDepthFactors = vector
        {
            pair(-1.0, 0.0244),
            pair(-0.875, 0.0544),
            pair(-0.750, 0.0938),
            pair(-0.625, 0.1407),
            pair(-0.500, 0.1801),
            pair(-0.375, 0.1632),
            pair(-0.250, 0.1426),
            pair(-0.125, 0.0994),
            pair(0.0, 0.06),
            pair(0.125, 0.0244),
            pair(0.250, 0.0169)
        };

        const var expectedImpactFactors = vector
        {
            pair(2.0, 0.039),
            pair(2.4, 0.1),
            pair(2.8, 0.18),
            pair(3.2, 0.235),
            pair(3.6, 0.2),
            pair(4.0, 0.13),
            pair(4.4, 0.08),
            pair(4.8, 0.02),
            pair(5.2, 0.01),
            pair(5.6, 0.005),
            pair(6.0, 0.001)
        };

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFactors(expectedWidthFactors, expectedDepthFactors,
                                                                                    expectedImpactFactors, *locationDependentInput);
    }

    #pragma endregion

    #pragma region Grass overtopping

        [Test]
    public void GivenBuilderWithGrassOvertoppingLocationWithXLeftFromOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        GivenGrassOvertoppingLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(9.9, "9.9");
    }

        [Test]
    public void GivenBuilderWithGrassOvertoppingLocationWithXRightFromOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        GivenGrassOvertoppingLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(50.1, "50.1");
    }

        [Test]
    public void GivenBuilderWithGrassOvertoppingLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        var topLayerType = static_cast<GrassRevetmentTopLayerType>(99);
        var constructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(45, topLayerType);

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddDikeProfileSegment(10, 20, 30, 40);
        builder.AddDikeProfileSegment(30, 40, 50, 60);
        builder.AddDikeProfilePointData(30, CharacteristicPointType::InnerCrest);
        builder.AddDikeProfilePointData(50, CharacteristicPointType::InnerToe);
        builder.AddGrassOvertoppingLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The location with position 45 has an invalid top layer type.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithGrassOvertoppingLocationWithInvalidGeometry_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var constructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(45, topLayerType);

        var outerToeX = 0;
        var outerCrestX = 30;

        CalculationInputBuilder builder;
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);

        builder.AddDikeProfileSegment(outerToeX, 10, 10, 20);
        builder.AddDikeProfileSegment(10, 20, 20, 20);
        builder.AddDikeProfileSegment(20, 20, outerCrestX, 10);
        builder.AddDikeProfileSegment(30, 10, 40, 40);
        builder.AddDikeProfileSegment(40, 40, 50, 60);
        builder.AddDikeProfilePointData(outerToeX, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(outerCrestX, CharacteristicPointType::OuterCrest);
        builder.AddDikeProfilePointData(30, CharacteristicPointType::InnerCrest);
        builder.AddDikeProfilePointData(50, CharacteristicPointType::InnerToe);
        builder.AddGrassOvertoppingLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEventWithNonEmptyMessage(EventType::Error, events.at(0));
    }

        [Test]
    public void GivenBuilderWithGrassOvertoppingLocationWithInvalidRoughnessCoefficients_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var constructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(45, topLayerType);

        var outerToeX = 0;
        var outerCrestX = 30;

        CalculationInputBuilder builder;
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);

        builder.AddDikeProfileSegment(outerToeX, 10, 10, 20, 0.4);
        builder.AddDikeProfileSegment(10, 20, outerCrestX, 25, 1.1);
        builder.AddDikeProfileSegment(30, 25, 40, 40);
        builder.AddDikeProfileSegment(40, 40, 50, 60);
        builder.AddDikeProfilePointData(outerToeX, CharacteristicPointType::OuterToe);
        builder.AddDikeProfilePointData(outerCrestX, CharacteristicPointType::OuterCrest);
        builder.AddDikeProfilePointData(30, CharacteristicPointType::InnerCrest);
        builder.AddDikeProfilePointData(50, CharacteristicPointType::InnerToe);
        builder.AddGrassOvertoppingLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(2, events.size());

        EventAssertHelper::AssertEventWithNonEmptyMessage(EventType::Error, events.at(0));
        EventAssertHelper::AssertEventWithNonEmptyMessage(EventType::Error, events.at(1));
    }

        [Test]
    public void GivenBuilderWithFullyConfiguredGrassOvertoppingLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var x = 45;
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

        var constructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(x, topLayerType);
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

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddDikeProfileSegment(10, 20, 30, 40);
        builder.AddDikeProfileSegment(30, 40, 50, 60);
        builder.AddDikeProfilePointData(30, CharacteristicPointType::InnerCrest);
        builder.AddDikeProfilePointData(50, CharacteristicPointType::InnerToe);
        builder.AddGrassOvertoppingLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualLocationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentOvertoppingLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(initialDamage, failureNumber, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, &dikeHeight, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertTransitionAlpha(
            increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            averageNumberOfWavesCtm, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertCumulativeOverload(
            criticalCumulativeOverload, fixedNumberOfWaves, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertFrontVelocity(
            criticalFrontVelocity, frontVelocityCwo, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertAccelerationAlphaA(
            accelerationAlphaAForCrest, accelerationAlphaAForInnerSlope, locationDependentInput->GetLocationDependentAccelerationAlphaA());
    }

        [Test]
    public void GivenBuilderWithNotFullyConfiguredClosedSodGrassOvertoppingLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var topLayerType = GrassRevetmentTopLayerType::ClosedSod;
        var x = 45;

        var constructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(x, topLayerType);

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddDikeProfileSegment(10, 20, 30, 40);
        builder.AddDikeProfileSegment(30, 40, 50, 60);
        builder.AddDikeProfilePointData(30, CharacteristicPointType::InnerCrest);
        builder.AddDikeProfilePointData(50, CharacteristicPointType::InnerToe);
        builder.AddGrassOvertoppingLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualLocationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentOvertoppingLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, nullptr, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertTransitionAlpha(
            1, 1, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            0.92, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertCumulativeOverload(
            7000, 10000, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertFrontVelocity(
            6.6, 1.45, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertAccelerationAlphaA(
            1.0, 1.4, locationDependentInput->GetLocationDependentAccelerationAlphaA());
    }

        [Test]
    public void GivenBuilderWithNotFullyConfiguredOpenSodGrassOvertoppingLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var x = 45;

        var constructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(x, topLayerType);

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddDikeProfileSegment(10, 20, 30, 40);
        builder.AddDikeProfileSegment(30, 40, 50, 60);
        builder.AddDikeProfilePointData(30, CharacteristicPointType::InnerCrest);
        builder.AddDikeProfilePointData(50, CharacteristicPointType::InnerToe);
        builder.AddGrassOvertoppingLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualLocationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentOvertoppingLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, nullptr, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertTransitionAlpha(
            1, 1, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            0.92, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertCumulativeOverload(
            7000, 10000, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertFrontVelocity(
            4.3, 1.45, *locationDependentInput);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertAccelerationAlphaA(
            1.0, 1.4, locationDependentInput->GetLocationDependentAccelerationAlphaA());
    }

    #pragma endregion

    #pragma region Grass wave impact

        [Test]
    public void GivenBuilderWithGrassWaveImpactLocationWithXOnOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent([](
        CalculationInputBuilder& builder)
            {
                builder.AddGrassWaveImpactLocation(
                    make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0, GrassRevetmentTopLayerType::ClosedSod));
            }, "0");
    }

        [Test]
    public void GivenBuilderWithGrassWaveImpactLocationWithXOnOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent([](
        CalculationInputBuilder& builder)
            {
                builder.AddGrassWaveImpactLocation(
                    make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(10, GrassRevetmentTopLayerType::ClosedSod));
            }, "10");
    }

        [Test]
    public void GivenBuilderWithGrassWaveImpactLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        var topLayerType = static_cast<GrassRevetmentTopLayerType>(99);
        var constructionProperties = make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0.1, topLayerType);

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddGrassWaveImpactLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The location with position 0.1 has an invalid top layer type.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithFullyConfiguredGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var x = 0.1;
        var initialDamage = 0.2;
        var failureNumber = 0.3;
        var timeLineAgwi = 0.4;
        var timeLineBgwi = 0.5;
        var timeLineCgwi = 0.6;
        var minimumWaveHeightTemax = 0.7;
        var maximumWaveHeightTemin = 0.8;
        var waveAngleImpactNwa = 0.9;
        var waveAngleImpactQwa = 1.0;
        var waveAngleImpactRwa = 1.1;
        var upperLimitLoadingAul = 1.2;
        var lowerLimitLoadingAll = 1.3;

        var constructionProperties = make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(x, topLayerType);
        constructionProperties.SetInitialDamage(initialDamage));
        constructionProperties.SetFailureNumber(failureNumber));
        constructionProperties.SetTimeLineAgwi(timeLineAgwi));
        constructionProperties.SetTimeLineBgwi(timeLineBgwi));
        constructionProperties.SetTimeLineCgwi(timeLineCgwi));
        constructionProperties.SetMinimumWaveHeightTemax(minimumWaveHeightTemax));
        constructionProperties.SetMaximumWaveHeightTemin(maximumWaveHeightTemin));
        constructionProperties.SetWaveAngleImpactNwa(waveAngleImpactNwa));
        constructionProperties.SetWaveAngleImpactQwa(waveAngleImpactQwa));
        constructionProperties.SetWaveAngleImpactRwa(waveAngleImpactRwa));
        constructionProperties.SetUpperLimitLoadingAul(upperLimitLoadingAul));
        constructionProperties.SetLowerLimitLoadingAll(lowerLimitLoadingAll));

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddGrassWaveImpactLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualLocationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(initialDamage, failureNumber, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            minimumWaveHeightTemax, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            maximumWaveHeightTemin, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            waveAngleImpactNwa, waveAngleImpactQwa, waveAngleImpactRwa, locationDependentInput->GetWaveAngleImpact());

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            timeLineAgwi, timeLineBgwi, timeLineCgwi, locationDependentInput->GetTimeLine());

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            upperLimitLoadingAul, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            lowerLimitLoadingAll, *locationDependentInput);
    }

        [Test]
    public void GivenBuilderWithNotFullyConfiguredClosedSodGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var topLayerType = GrassRevetmentTopLayerType::ClosedSod;
        var x = 0.1;

        var constructionProperties = make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(x, topLayerType);

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddGrassWaveImpactLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualLocationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            3600000, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            3.6, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            2.0 / 3.0, 0.35, 10, locationDependentInput->GetWaveAngleImpact());

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            1, -0.000009722, 0.25, locationDependentInput->GetTimeLine());

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            0, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            0.5, *locationDependentInput);
    }

        [Test]
    public void GivenBuilderWithNotFullyConfiguredOpenSodGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var x = 0.1;

        var constructionProperties = make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(x, topLayerType);

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddGrassWaveImpactLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualLocationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            3600000, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            3.6, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            2.0 / 3.0, 0.35, 10, locationDependentInput->GetWaveAngleImpact());

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            0.8, -0.00001944, 0.25, locationDependentInput->GetTimeLine());

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            0, *locationDependentInput);

        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            0.5, *locationDependentInput);
    }

    #pragma endregion

    #pragma region Grass wave run-up Rayleigh

        [Test]
    public void GivenBuilderWithGrassWaveRunupRayleighLocationWithXOnOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent([](
        CalculationInputBuilder& builder)
            {
                builder.AddGrassWaveRunupRayleighLocation(
                    make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(0, 0.1, GrassRevetmentTopLayerType::ClosedSod));
            }, "0");
    }

        [Test]
    public void GivenBuilderWithGrassWaveRunupRayleighLocationWithXOnOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent([](
        CalculationInputBuilder& builder)
            {
                builder.AddGrassWaveRunupRayleighLocation(
                    make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(10, 0.1, GrassRevetmentTopLayerType::ClosedSod));
            }, "10");
    }

        [Test]
    public void GivenBuilderWithGrassWaveRunupRayleighLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        var topLayerType = static_cast<GrassRevetmentTopLayerType>(99);
        var constructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(0.1, 0.2, topLayerType);

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddGrassWaveRunupRayleighLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The location with position 0.1 has an invalid top layer type.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithFullyConfiguredGrassWaveRunupRayleighLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var x = 0.1;
        var outerSlope = 0.2;
        var initialDamage = 0.3;
        var failureNumber = 0.4;
        var criticalCumulativeOverload = 0.5;
        var criticalFrontVelocity = 0.6;
        var increasedLoadTransitionAlphaM = 0.7;
        var reducedStrengthTransitionAlphaS = 0.8;
        var averageNumberOfWavesCtm = 0.9;
        var representativeWaveRunup2PAru = 1.0;
        var representativeWaveRunup2PBru = 1.1;
        var representativeWaveRunup2PCru = 1.2;
        var representativeWaveRunup2PGammab = 1.3;
        var representativeWaveRunup2PGammaf = 1.4;
        var waveAngleImpactAbeta = 1.5;
        var waveAngleImpactBetamax = 1.6;
        var fixedNumberOfWaves = 17;
        var frontVelocityCu = 1.8;

        var constructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(x, outerSlope, topLayerType);
        constructionProperties.SetInitialDamage(initialDamage));
        constructionProperties.SetFailureNumber(failureNumber));
        constructionProperties.SetCriticalCumulativeOverload(criticalCumulativeOverload));
        constructionProperties.SetCriticalFrontVelocity(criticalFrontVelocity));
        constructionProperties.SetIncreasedLoadTransitionAlphaM(increasedLoadTransitionAlphaM));
        constructionProperties.SetReducedStrengthTransitionAlphaS(reducedStrengthTransitionAlphaS));
        constructionProperties.SetAverageNumberOfWavesCtm(averageNumberOfWavesCtm));
        constructionProperties.SetRepresentativeWaveRunup2PAru(representativeWaveRunup2PAru));
        constructionProperties.SetRepresentativeWaveRunup2PBru(representativeWaveRunup2PBru));
        constructionProperties.SetRepresentativeWaveRunup2PCru(representativeWaveRunup2PCru));
        constructionProperties.SetRepresentativeWaveRunup2PGammab(representativeWaveRunup2PGammab));
        constructionProperties.SetRepresentativeWaveRunup2PGammaf(representativeWaveRunup2PGammaf));
        constructionProperties.SetWaveAngleImpactAbeta(waveAngleImpactAbeta));
        constructionProperties.SetWaveAngleImpactBetamax(waveAngleImpactBetamax));
        constructionProperties.SetFixedNumberOfWaves(fixedNumberOfWaves));
        constructionProperties.SetFrontVelocityCu(frontVelocityCu));

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddGrassWaveRunupRayleighLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualLocationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveRunupRayleighLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(initialDamage, failureNumber, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, outerSlope, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertRepresentative2P(
            representativeWaveRunup2PAru, representativeWaveRunup2PBru, representativeWaveRunup2PCru,
            representativeWaveRunup2PGammab, representativeWaveRunup2PGammaf, locationDependentInput->GetRepresentative2P());

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            waveAngleImpactAbeta, waveAngleImpactBetamax, locationDependentInput->GetWaveAngleImpact());

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertTransitionAlpha(
            increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            averageNumberOfWavesCtm, *locationDependentInput);

        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertCumulativeOverload(
            criticalCumulativeOverload, fixedNumberOfWaves, *locationDependentInput);

        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertFrontVelocity(
            criticalFrontVelocity, frontVelocityCu, *locationDependentInput);
    }

        [Test]
    public void GivenBuilderWithNotFullyConfiguredClosedSodGrassWaveRunupRayleighLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInpu()
    {
        // Given
        var topLayerType = GrassRevetmentTopLayerType::ClosedSod;
        var x = 0.1;
        var outerSlope = 0.2;

        var constructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(x, outerSlope, topLayerType);

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddGrassWaveRunupRayleighLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualLocationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveRunupRayleighLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, outerSlope, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertRepresentative2P(
            1.65, 4, 1.5, 1, 1, locationDependentInput->GetRepresentative2P());

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            0.0022, 80, locationDependentInput->GetWaveAngleImpact());

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertTransitionAlpha(
            1, 1, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            0.92, *locationDependentInput);

        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertCumulativeOverload(
            7000, 10000, *locationDependentInput);

        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertFrontVelocity(
            6.6, 1.1, *locationDependentInput);
    }

        [Test]
    public void GivenBuilderWithNotFullyConfiguredOpenSodGrassWaveRunupRayleighLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var topLayerType = GrassRevetmentTopLayerType::OpenSod;
        var x = 0.1;
        var outerSlope = 0.2;

        var constructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(x, outerSlope, topLayerType);

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddGrassWaveRunupRayleighLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualLocationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<GrassRevetmentWaveRunupRayleighLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, outerSlope, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertRepresentative2P(
            1.65, 4, 1.5, 1, 1, locationDependentInput->GetRepresentative2P());

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            0.0022, 80, locationDependentInput->GetWaveAngleImpact());

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertTransitionAlpha(
            1, 1, *locationDependentInput);

        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            0.92, *locationDependentInput);

        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertCumulativeOverload(
            7000, 10000, *locationDependentInput);

        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertFrontVelocity(
            4.3, 1.1, *locationDependentInput);
    }

    #pragma endregion

    #pragma region Natural stone

        [Test]
    public void GivenBuilderWithNaturalStoneLocationWithXOnOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent([](
        CalculationInputBuilder& builder)
            {
                builder.AddNaturalStoneLocation(
                    make_unique<NaturalStoneRevetmentLocationConstructionProperties>(0, NaturalStoneRevetmentTopLayerType::NordicStone, 0.1, 0.2));
            }, "0");
    }

        [Test]
    public void GivenBuilderWithNaturalStoneLocationWithXOnOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent([](
        CalculationInputBuilder& builder)
            {
                builder.AddNaturalStoneLocation(
                    make_unique<NaturalStoneRevetmentLocationConstructionProperties>(10, NaturalStoneRevetmentTopLayerType::NordicStone, 0.1, 0.2));
            }, "10");
    }

        [Test]
    public void GivenBuilderWithNaturalStoneLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
    {
        // Given
        var topLayerType = static_cast<NaturalStoneRevetmentTopLayerType>(99);
        var constructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(0.1, topLayerType, 0.2, 0.3);

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddNaturalStoneLocation(move(constructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(EventType::Error, "The location with position 0.1 has an invalid top layer type.", events.at(0));
    }

        [Test]
    public void GivenBuilderWithFullyConfiguredNaturalStoneLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var topLayerType = NaturalStoneRevetmentTopLayerType::NordicStone;
        var x = 0.1;
        var thicknessTopLayer = 0.2;
        var relativeDensity = 0.3;
        var initialDamage = 0.4;
        var failureNumber = 0.5;
        var hydraulicLoadXib = 0.6;
        var hydraulicLoadAp = 0.7;
        var hydraulicLoadBp = 0.8;
        var hydraulicLoadCp = 0.9;
        var hydraulicLoadNp = 1.0;
        var hydraulicLoadAs = 1.1;
        var hydraulicLoadBs = 1.2;
        var hydraulicLoadCs = 1.3;
        var hydraulicLoadNs = 1.4;
        var slopeUpperLevelAus = 1.5;
        var slopeLowerLevelAls = 1.6;
        var upperLimitLoadingAul = 1.7;
        var upperLimitLoadingBul = 1.8;
        var upperLimitLoadingCul = 1.9;
        var lowerLimitLoadingAll = 2.0;
        var lowerLimitLoadingBll = 2.1;
        var lowerLimitLoadingCll = 2.2;
        var distanceMaximumWaveElevationAsmax = 2.3;
        var distanceMaximumWaveElevationBsmax = 2.4;
        var normativeWidthOfWaveImpactAwi = 2.5;
        var normativeWidthOfWaveImpactBwi = 2.6;
        var waveAngleImpactBetamax = 2.7;

        var naturalStoneConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            x, topLayerType, thicknessTopLayer, relativeDensity);
        naturalStoneConstructionProperties->SetInitialDamage(initialDamage));
        naturalStoneConstructionProperties->SetFailureNumber(failureNumber));
        naturalStoneConstructionProperties->SetHydraulicLoadXib(hydraulicLoadXib));
        naturalStoneConstructionProperties->SetHydraulicLoadAp(hydraulicLoadAp));
        naturalStoneConstructionProperties->SetHydraulicLoadBp(hydraulicLoadBp));
        naturalStoneConstructionProperties->SetHydraulicLoadCp(hydraulicLoadCp));
        naturalStoneConstructionProperties->SetHydraulicLoadNp(hydraulicLoadNp));
        naturalStoneConstructionProperties->SetHydraulicLoadAs(hydraulicLoadAs));
        naturalStoneConstructionProperties->SetHydraulicLoadBs(hydraulicLoadBs));
        naturalStoneConstructionProperties->SetHydraulicLoadCs(hydraulicLoadCs));
        naturalStoneConstructionProperties->SetHydraulicLoadNs(hydraulicLoadNs));
        naturalStoneConstructionProperties->SetSlopeUpperLevelAus(slopeUpperLevelAus));
        naturalStoneConstructionProperties->SetSlopeLowerLevelAls(slopeLowerLevelAls));
        naturalStoneConstructionProperties->SetUpperLimitLoadingAul(upperLimitLoadingAul));
        naturalStoneConstructionProperties->SetUpperLimitLoadingBul(upperLimitLoadingBul));
        naturalStoneConstructionProperties->SetUpperLimitLoadingCul(upperLimitLoadingCul));
        naturalStoneConstructionProperties->SetLowerLimitLoadingAll(lowerLimitLoadingAll));
        naturalStoneConstructionProperties->SetLowerLimitLoadingBll(lowerLimitLoadingBll));
        naturalStoneConstructionProperties->SetLowerLimitLoadingCll(lowerLimitLoadingCll));
        naturalStoneConstructionProperties->SetDistanceMaximumWaveElevationAsmax(distanceMaximumWaveElevationAsmax));
        naturalStoneConstructionProperties->SetDistanceMaximumWaveElevationBsmax(distanceMaximumWaveElevationBsmax));
        naturalStoneConstructionProperties->SetNormativeWidthOfWaveImpactAwi(normativeWidthOfWaveImpactAwi));
        naturalStoneConstructionProperties->SetNormativeWidthOfWaveImpactBwi(normativeWidthOfWaveImpactBwi));
        naturalStoneConstructionProperties->SetWaveAngleImpactBetamax(waveAngleImpactBetamax));

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddNaturalStoneLocation(move(naturalStoneConstructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualLocationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(initialDamage, failureNumber, *locationDependentInput);

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, relativeDensity, thicknessTopLayer, *locationDependentInput);

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(
            hydraulicLoadAp, hydraulicLoadBp, hydraulicLoadCp, hydraulicLoadNp, hydraulicLoadAs, hydraulicLoadBs,
            hydraulicLoadCs, hydraulicLoadNs, hydraulicLoadXib, locationDependentInput->GetHydraulicLoads());

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertSlope(
            slopeUpperLevelAus, slopeLowerLevelAls, locationDependentInput->GetSlope());

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            upperLimitLoadingAul, upperLimitLoadingBul, upperLimitLoadingCul, locationDependentInput->GetUpperLimitLoading());

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            lowerLimitLoadingAll, lowerLimitLoadingBll, lowerLimitLoadingCll, locationDependentInput->GetLowerLimitLoading());

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertDistanceMaximumWaveElevation(
            distanceMaximumWaveElevationAsmax, distanceMaximumWaveElevationBsmax,
            locationDependentInput->GetDistanceMaximumWaveElevation());

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertNormativeWidthOfWaveImpact(
            normativeWidthOfWaveImpactAwi, normativeWidthOfWaveImpactBwi,
            locationDependentInput->GetNormativeWidthOfWaveImpact());

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            waveAngleImpactBetamax, locationDependentInput->GetWaveAngleImpact());
    }

        [Test]
    public void GivenBuilderWithNotFullyConfiguredNaturalStoneLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
    {
        // Given
        var topLayerType = NaturalStoneRevetmentTopLayerType::NordicStone;
        var x = 0.1;
        var thicknessTopLayer = 0.2;
        var relativeDensity = 0.3;

        var naturalStoneConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            x, topLayerType, thicknessTopLayer, relativeDensity);

        CalculationInputBuilder builder;
        AddDefaultProfileAndTimeStep(builder);
        builder.AddNaturalStoneLocation(move(naturalStoneConstructionProperties));

        // When
        const var result = builder.Build();

        // Then
        ASSERT_TRUE(result->GetSuccessful());

        const auto& calculationInput = *result->GetData();
        const auto& actualLocationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, relativeDensity, thicknessTopLayer, *locationDependentInput);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(
            4, 0, 0, -0.9, 0.8, 0, 0, 0.6, 2.9, locationDependentInput->GetHydraulicLoads());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertSlope(
            0.05, 1.5, locationDependentInput->GetSlope());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            0.1, 0.6, 4, locationDependentInput->GetUpperLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            0.1, 0.2, 4, locationDependentInput->GetLowerLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertDistanceMaximumWaveElevation(
            0.42, 0.9, locationDependentInput->GetDistanceMaximumWaveElevation());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertNormativeWidthOfWaveImpact(
            0.96, 0.11, locationDependentInput->GetNormativeWidthOfWaveImpact());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            78, locationDependentInput->GetWaveAngleImpact());
    }

    #pragma endregion

    #pragma endregion
    }
}
