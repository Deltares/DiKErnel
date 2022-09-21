// Copyright (C) Stichting Deltares 2022. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#include <gtest/gtest.h>

#include "AsphaltRevetmentWaveImpactLocationDependentInput.h"
#include "AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.h"
#include "AssertHelper.h"
#include "CalculationInputBuilder.h"
#include "CalculationInputBuildException.h"
#include "GrassRevetmentOvertoppingLocationDependentInput.h"
#include "GrassRevetmentOvertoppingLocationDependentInputAssertHelper.h"
#include "GrassRevetmentWaveImpactLocationDependentInput.h"
#include "GrassRevetmentWaveImpactLocationDependentInputAssertHelper.h"
#include "GrassRevetmentWaveRunupLocationDependentInputAssertHelper.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInput.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.h"
#include "InputFactoryException.h"
#include "LocationDependentInputAssertHelper.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"
#include "NaturalStoneRevetmentLocationDependentInput.h"
#include "NaturalStoneRevetmentLocationDependentInputAssertHelper.h"
#include "ProfileDataAssertHelper.h"
#include "TimeDependentInputAssertHelper.h"

namespace DiKErnel::Integration::Test
{
    using namespace Core;
    using namespace DiKErnel::TestUtil;
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct CalculationInputBuilderTest : Test
    {
        static void CreateBuilderWithoutOuterToe()
        {
            constexpr auto startPointX = 10;

            CalculationInputBuilder builder;
            builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::OuterCrest);
            builder.AddDikeProfileSegment(0, 10, startPointX, 30, nullptr);
            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderWithoutOuterCrest()
        {
            constexpr auto startPointX = 10;

            CalculationInputBuilder builder;
            builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::OuterToe);
            builder.AddDikeProfileSegment(0, 10, startPointX, 30, nullptr);
            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderWithGrassRevetmentOvertoppingLocationAndWithoutInnerToe()
        {
            auto constructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(0.1,
                GrassRevetmentTopLayerType::ClosedSod);

            constexpr auto startPointX = 10;

            CalculationInputBuilder builder;
            builder.AddGrassOvertoppingLocation(move(constructionProperties));

            builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::OuterToe);
            builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::OuterCrest);
            builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::InnerCrest);
            builder.AddDikeProfileSegment(0, 10, startPointX, 30, nullptr);

            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderWithGrassRevetmentOvertoppingLocationAndWithoutInnerCrest()
        {
            auto constructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(0.1,
                GrassRevetmentTopLayerType::ClosedSod);

            constexpr auto startPointX = 10;

            CalculationInputBuilder builder;
            builder.AddGrassOvertoppingLocation(move(constructionProperties));
            
            builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::OuterToe);
            builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::OuterCrest);
            builder.AddDikeProfilePointData(startPointX, CharacteristicPointType::InnerToe);
            builder.AddDikeProfileSegment(0, 10, startPointX, 30, nullptr);
            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderWithoutSegments()
        {
            const CalculationInputBuilder builder;
            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderAndSegmentUnchainedOnXCoordinate()
        {
            constexpr auto startPointX = 10;
            constexpr auto startPointZ = 20;
            constexpr auto endPointX = 20;
            constexpr auto endPointZ = 30;

            CalculationInputBuilder builder;
            builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, nullptr);
            builder.AddDikeProfileSegment(endPointX + 0.01, startPointZ, endPointX, endPointZ, nullptr);
            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderAndSegmentUnchainedOnZCoordinate()
        {
            constexpr auto startPointX = 10;
            constexpr auto startPointZ = 20;
            constexpr auto endPointX = 20;
            constexpr auto endPointZ = 30;

            CalculationInputBuilder builder;
            builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, nullptr);
            builder.AddDikeProfileSegment(endPointX, startPointZ + 0.01, endPointX, endPointZ, nullptr);
            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderAndCharacteristicPointNotOnSegmentPoint()
        {
            constexpr auto startPointX = 10;
            constexpr auto endPointX = 20;
            constexpr auto endPointZ = 30;
            constexpr auto characteristicPointType = CharacteristicPointType::NotchOuterBerm;

            CalculationInputBuilder builder;
            builder.AddDikeProfilePointData(startPointX - 0.01, characteristicPointType);
            builder.AddDikeProfileSegment(0, 10, endPointX, endPointZ, nullptr);
            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderAndBuildWithoutTimeStepAdded()
        {
            CalculationInputBuilder builder;
            builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
            builder.AddGrassWaveImpactLocation(
                make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0, GrassRevetmentTopLayerType::ClosedSod));
            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderAndBuildWithInvalidTimeStepsAdded()
        {
            CalculationInputBuilder builder;
            builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
            builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
            builder.AddTimeStep(3, 4, 0.3, 0.4, 0.5, 0.6);
            builder.AddGrassWaveImpactLocation(
                make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0, GrassRevetmentTopLayerType::ClosedSod));
            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderAndBuildWithoutLocationAdded()
        {
            CalculationInputBuilder builder;
            builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
            builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderAndAddAsphaltRevetmentWaveImpactLocationWithInvalidTopLayerType()
        {
            constexpr auto topLayerType = static_cast<AsphaltRevetmentTopLayerType>(99);
            auto constructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
                0.1, topLayerType, 0.2, 0.3, 0.4, 0.5);

            CalculationInputBuilder builder;
            builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
            builder.AddAsphaltWaveImpactLocation(move(constructionProperties));
            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderAndAddGrassRevetmentOvertoppingLocationWithInvalidTopLayerType()
        {
            constexpr auto topLayerType = static_cast<GrassRevetmentTopLayerType>(99);
            auto constructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(0.1, topLayerType);

            CalculationInputBuilder builder;
            builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
            builder.AddGrassOvertoppingLocation(move(constructionProperties));
            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderAndAddGrassRevetmentWaveImpactLocationWithInvalidTopLayerType()
        {
            constexpr auto topLayerType = static_cast<GrassRevetmentTopLayerType>(99);
            auto constructionProperties = make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0.1, topLayerType);

            CalculationInputBuilder builder;
            builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
            builder.AddGrassWaveImpactLocation(move(constructionProperties));
            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderAndAddGrassRevetmentWaveRunupRayleighLocationWithInvalidTopLayerType()
        {
            constexpr auto topLayerType = static_cast<GrassRevetmentTopLayerType>(99);
            auto constructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(0.1, 0.2, topLayerType);

            CalculationInputBuilder builder;
            builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
            builder.AddGrassWaveRunupRayleighLocation(move(constructionProperties));
            const auto& calculationInput = builder.Build();
        }

        static void CreateBuilderAndAddNaturalStoneRevetmentLocationWithInvalidTopLayerType()
        {
            constexpr auto topLayerType = static_cast<NaturalStoneRevetmentTopLayerType>(99);
            auto constructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(0.1, topLayerType, 0.2, 0.3);

            CalculationInputBuilder builder;
            builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
            builder.AddNaturalStoneLocation(move(constructionProperties));
            const auto& calculationInput = builder.Build();
        }
    };

    #pragma region Validation

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithoutOuterToe_WhenBuild_ThenThrowsCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &CalculationInputBuilderTest::CreateBuilderWithoutOuterToe;

        // Then
        AssertHelper::AssertThrowsWithMessage<CalculationInputBuildException>(
            action, "Could not create calculation input. The OuterToe must be defined.");
    }

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithoutOuterCrest_WhenBuild_ThenThrowsCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &CalculationInputBuilderTest::CreateBuilderWithoutOuterCrest;

        // Then
        AssertHelper::AssertThrowsWithMessage<CalculationInputBuildException>(
            action, "Could not create calculation input. The OuterCrest must be defined.");
    }

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithGrassOvertoppingLocationAndWithoutInnerToe_WhenBuild_ThenThrowsCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &CalculationInputBuilderTest::CreateBuilderWithGrassRevetmentOvertoppingLocationAndWithoutInnerToe;

        // Then
        AssertHelper::AssertThrowsWithMessage<CalculationInputBuildException>(
            action, "Could not create calculation input. The InnerToe must be defined.");
    }

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithGrassOvertoppingLocationAndWithoutInnerCrest_WhenBuild_ThenThrowsCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &CalculationInputBuilderTest::CreateBuilderWithGrassRevetmentOvertoppingLocationAndWithoutInnerCrest;

        // Then
        AssertHelper::AssertThrowsWithMessage<CalculationInputBuildException>(
            action, "Could not create calculation input. The InnerCrest must be defined.");
    }

    #pragma endregion

    #pragma region Profile segments

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithDikeSegmentAddedWithoutRoughness_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto startPointX = 10;
        constexpr auto startPointZ = 20;
        constexpr auto endPointX = 20;
        constexpr auto endPointZ = 30;

        CalculationInputBuilder builder;
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, nullptr);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0, GrassRevetmentTopLayerType::ClosedSod));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualProfileData = calculationInput->GetProfileData();
        const auto& actualProfileSegments = actualProfileData.GetProfileSegments();
        ASSERT_EQ(1, actualProfileSegments.size());

        const auto& actualSegment = actualProfileSegments.at(0);
        ProfileDataAssertHelper::AssertProfileSegment(startPointX, startPointZ,
                                                      endPointX, endPointZ,
                                                      1.0, actualSegment);
    }

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithDikeSegmentAddedWithRoughness_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto startPointX = 10;
        constexpr auto startPointZ = 20;
        constexpr auto endPointX = 20;
        constexpr auto endPointZ = 30;
        constexpr auto roughnessCoefficient = 13.37;

        CalculationInputBuilder builder;
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, &roughnessCoefficient);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0, GrassRevetmentTopLayerType::ClosedSod));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualProfileData = calculationInput->GetProfileData();
        const auto& actualProfileSegments = actualProfileData.GetProfileSegments();
        ASSERT_EQ(1, actualProfileSegments.size());

        const auto& actualSegment = actualProfileSegments.at(0);
        ProfileDataAssertHelper::AssertProfileSegment(startPointX, startPointZ,
                                                      endPointX, endPointZ,
                                                      roughnessCoefficient, actualSegment);
    }

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithDikeSegmentsAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto startPointXSegmentOne = 10;
        constexpr auto startPointZSegmentOne = 20;
        constexpr auto endPointXSegmentOne = 20;
        constexpr auto endPointZSegmentOne = 30;
        constexpr auto endPointXSegmentTwo = 30;
        constexpr auto endPointZSegmentTwo = 40;
        constexpr auto roughnessCoefficient = 13.37;

        CalculationInputBuilder builder;
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddDikeProfileSegment(startPointXSegmentOne, startPointZSegmentOne, endPointXSegmentOne, endPointZSegmentOne,
                                      &roughnessCoefficient);
        builder.AddDikeProfileSegment(endPointXSegmentOne, endPointZSegmentOne, endPointXSegmentTwo, endPointZSegmentTwo,
                                      &roughnessCoefficient);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0, GrassRevetmentTopLayerType::ClosedSod));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualProfileData = calculationInput->GetProfileData();
        const auto& actualProfileSegments = actualProfileData.GetProfileSegments();
        ASSERT_EQ(2, actualProfileSegments.size());

        const auto& segmentOne = actualProfileSegments.at(0).get();
        ProfileDataAssertHelper::AssertProfileSegment(startPointXSegmentOne, startPointZSegmentOne,
                                                      endPointXSegmentOne, endPointZSegmentOne,
                                                      roughnessCoefficient, segmentOne);

        const auto& segmentTwo = actualProfileSegments.at(1).get();
        ProfileDataAssertHelper::AssertProfileSegment(endPointXSegmentOne, endPointZSegmentOne,
                                                      endPointXSegmentTwo, endPointZSegmentTwo,
                                                      roughnessCoefficient, segmentTwo);

        ASSERT_EQ(&segmentOne.GetEndPoint(), &segmentTwo.GetStartPoint());
    }

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithoutDikeSegments_WhenBuild_ThenThrowsCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &CalculationInputBuilderTest::CreateBuilderWithoutSegments;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<CalculationInputBuildException, InputFactoryException>(
            action, "Could not create calculation input.", "At least 1 segment is required.");
    }

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithDikeSegmentsAddedWithoutRoughness_WhenSegmentXCoordinateUnchained_ThenThrowsCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &CalculationInputBuilderTest::CreateBuilderAndSegmentUnchainedOnXCoordinate;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<CalculationInputBuildException, InputFactoryException>(
            action, "Could not create calculation input.",
            "The start point of a successive segment must be equal to the end point of the previous segment.");
    }

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithDikeSegmentsAddedWithoutRoughness_WhenSegmentZCoordinateUnchained_ThenThrowsCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &CalculationInputBuilderTest::CreateBuilderAndSegmentUnchainedOnZCoordinate;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<CalculationInputBuildException, InputFactoryException>(
            action, "Could not create calculation input.",
            "The start point of a successive segment must be equal to the end point of the previous segment.");
    }

    #pragma endregion

    #pragma region Profile point data

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithDikeProfilePointDataOnSegmentStartPoint_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto x = 10;
        constexpr auto z = 20;
        constexpr auto characteristicPointType = CharacteristicPointType::NotchOuterBerm;

        CalculationInputBuilder builder;
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddDikeProfilePointData(x, characteristicPointType);
        builder.AddDikeProfileSegment(x, z, 20, 30, nullptr);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0, GrassRevetmentTopLayerType::ClosedSod));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualProfileData = calculationInput->GetProfileData();
        const auto& actualProfileSegments = actualProfileData.GetProfileSegments();
        const auto& actualCharacteristicPoints = actualProfileData.GetCharacteristicPoints();
        ASSERT_EQ(1, actualProfileSegments.size());
        ASSERT_EQ(1, actualCharacteristicPoints.size());

        const auto& actualSegment = actualProfileSegments.at(0).get();
        ProfileDataAssertHelper::AssertCharacteristicPoint(actualSegment.GetStartPoint(), characteristicPointType,
                                                           actualCharacteristicPoints.at(0));
    }

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithDikeProfilePointDataOnSegmentEndPoint_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto x = 10;
        constexpr auto z = 20;
        constexpr auto characteristicPointType = CharacteristicPointType::NotchOuterBerm;

        CalculationInputBuilder builder;
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddDikeProfilePointData(x, characteristicPointType);
        builder.AddDikeProfileSegment(0, 10, x, z, nullptr);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0, GrassRevetmentTopLayerType::ClosedSod));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualProfileData = calculationInput->GetProfileData();
        const auto& actualProfileSegments = actualProfileData.GetProfileSegments();
        const auto& actualCharacteristicPoints = actualProfileData.GetCharacteristicPoints();
        ASSERT_EQ(1, actualProfileSegments.size());
        ASSERT_EQ(1, actualCharacteristicPoints.size());

        const auto& actualSegment = actualProfileSegments.at(0).get();
        ProfileDataAssertHelper::AssertCharacteristicPoint(actualSegment.GetEndPoint(), characteristicPointType,
                                                           actualCharacteristicPoints.at(0));
    }

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithDikeProfilePointDataNotOnSegmentPoints_WhenBuild_ThenThrowsCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &CalculationInputBuilderTest::CreateBuilderAndCharacteristicPointNotOnSegmentPoint;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<CalculationInputBuildException, InputFactoryException>(
            action, "Could not create calculation input.", "Characteristic point must be on a start or end point of a segment.");
    }

    #pragma endregion

    #pragma region Time step

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithoutTimeStepAdded_WhenBuild_ThenThrowsCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &CalculationInputBuilderTest::CreateBuilderAndBuildWithoutTimeStepAdded;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<CalculationInputBuildException, InputFactoryException>(
            action, "Could not create calculation input.", "At least 1 time step is required.");
    }

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithInvalidTimeStepsAdded_WhenBuild_ThenThrowsCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &CalculationInputBuilderTest::CreateBuilderAndBuildWithInvalidTimeStepsAdded;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<CalculationInputBuildException, InputFactoryException>(
            action, "Could not create calculation input.",
            "The begin time of a successive element must be equal to the end time of the previous element.");
    }

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithTimeStepAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto beginTime = 1;
        constexpr auto endTime = 2;
        constexpr auto waterLevel = 0.3;
        constexpr auto waveHeightHm0 = 0.4;
        constexpr auto wavePeriodTm10 = 0.5;
        constexpr auto waveAngle = 0.6;

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
        builder.AddTimeStep(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle);
        builder.AddGrassWaveImpactLocation(
            make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(0, GrassRevetmentTopLayerType::ClosedSod));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualTimeDependentInputItems = calculationInput->GetTimeDependentInputItems();
        ASSERT_EQ(1, actualTimeDependentInputItems.size());
        const auto& timeDependentInput = actualTimeDependentInputItems.at(0).get();

        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle,
                                                                     timeDependentInput);
    }

    #pragma endregion

    #pragma region Locations

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithoutLocationAdded_WhenBuild_ThenThrowsCalculationInputBuilderException)
    {
        // Given & When
        const auto action = &CalculationInputBuilderTest::CreateBuilderAndBuildWithoutLocationAdded;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<CalculationInputBuildException, InputFactoryException>(
            action, "Could not create calculation input.", "At least 1 location is required.");
    }

    #pragma region Asphalt wave impact

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithAsphaltWaveImpactLocationWithInvalidTopLayerType_WhenBuild_ThenThrowCalculationInputBuildException)
    {
        // Given & When
        const auto action =
                &CalculationInputBuilderTest::CreateBuilderAndAddAsphaltRevetmentWaveImpactLocationWithInvalidTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<CalculationInputBuildException, InputFactoryException>(
            action, "Could not create calculation input.", "Couldn't create defaults for the given top layer type.");
    }

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithFullyConfiguredAsphaltWaveImpactLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        constexpr auto topLayerType = AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete;
        constexpr auto x = 0.1;
        constexpr auto failureTension = 0.2;
        constexpr auto soilElasticity = 0.3;
        constexpr auto thicknessUpperLayer = 0.4;
        constexpr auto elasticModulusUpperLayer = 0.5;
        constexpr auto initialDamage = 0.6;
        constexpr auto failureNumber = 0.7;
        constexpr auto densityOfWater = 0.8;
        constexpr auto thicknessSubLayer = 0.9;
        constexpr auto elasticModulusSubLayer = 1.0;
        constexpr auto averageNumberOfWavesCtm = 1.1;
        constexpr auto fatigueAlpha = 1.2;
        constexpr auto fatigueBeta = 1.3;
        constexpr auto impactNumberC = 1.4;
        constexpr auto stiffnessRelationNu = 1.5;
        const auto widthFactors = vector
        {
            pair(1.6, 1.7)
        };
        const auto depthFactors = vector
        {
            pair(1.8, 1.9)
        };
        const auto impactFactors = vector
        {
            pair(2.0, 2.1)
        };

        auto constructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            x, topLayerType, failureTension, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer);

        constructionProperties->SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties->SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties->SetDensityOfWater(make_unique<double>(densityOfWater));
        constructionProperties->SetThicknessSubLayer(make_unique<double>(thicknessSubLayer));
        constructionProperties->SetElasticModulusSubLayer(make_unique<double>(elasticModulusSubLayer));
        constructionProperties->SetAverageNumberOfWavesCtm(make_unique<double>(averageNumberOfWavesCtm));
        constructionProperties->SetFatigueAlpha(make_unique<double>(fatigueAlpha));
        constructionProperties->SetFatigueBeta(make_unique<double>(fatigueBeta));
        constructionProperties->SetImpactNumberC(make_unique<double>(impactNumberC));
        constructionProperties->SetStiffnessRelationNu(make_unique<double>(stiffnessRelationNu));
        constructionProperties->SetWidthFactors(make_unique<vector<pair<double, double>>>(widthFactors));
        constructionProperties->SetDepthFactors(make_unique<vector<pair<double, double>>>(depthFactors));
        constructionProperties->SetImpactFactors(make_unique<vector<pair<double, double>>>(impactFactors));

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddAsphaltWaveImpactLocation(move(constructionProperties));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
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

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithNotFullyConfiguredAsphaltWaveImpactLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        constexpr auto topLayerType = AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete;
        constexpr auto x = 0.1;
        constexpr auto failureTension = 0.2;
        constexpr auto soilElasticity = 0.3;
        constexpr auto thicknessUpperLayer = 0.4;
        constexpr auto elasticModulusUpperLayer = 0.5;

        auto constructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
            x, topLayerType, failureTension, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer);

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddAsphaltWaveImpactLocation(move(constructionProperties));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(1, actualLocationDependentInputItems.size());

        const auto* locationDependentInput = dynamic_cast<AsphaltRevetmentWaveImpactLocationDependentInput*>(
            &actualLocationDependentInputItems.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *locationDependentInput);

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            x, failureTension, 1025, soilElasticity, 1, 1, 0.35, *locationDependentInput);

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(thicknessUpperLayer, elasticModulusUpperLayer,
                                                                                  locationDependentInput->GetUpperLayer());

        ASSERT_EQ(nullptr, locationDependentInput->GetSubLayer());

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFatigue(0.42, 4.76,
                                                                                    locationDependentInput->GetFatigue());

        const auto expectedWidthFactors = vector
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

        const auto expectedDepthFactors = vector
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

        const auto expectedImpactFactors = vector
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

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithGrassOvertoppingLocationWithInvalidTopLayerType_WhenBuild_ThenThrowsCalculationInputBuildException)
    {
        // Given & When
        const auto action =
                &CalculationInputBuilderTest::CreateBuilderAndAddGrassRevetmentOvertoppingLocationWithInvalidTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<CalculationInputBuildException, InputFactoryException>(
            action, "Could not create calculation input.", "Couldn't create defaults for the given top layer type.");
    }

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithFullyConfiguredGrassOvertoppingLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto topLayerType = static_cast<GrassRevetmentTopLayerType>(rand() % 2);
        constexpr auto x = 0.1;
        constexpr auto initialDamage = 0.2;
        constexpr auto failureNumber = 0.3;
        constexpr auto criticalCumulativeOverload = 0.4;
        constexpr auto criticalFrontVelocity = 0.5;
        constexpr auto increasedLoadTransitionAlphaM = 0.6;
        constexpr auto reducedStrengthTransitionAlphaS = 0.7;
        constexpr auto averageNumberOfWavesCtm = 0.8;
        constexpr auto fixedNumberOfWaves = 9;
        constexpr auto frontVelocityCwo = 1.0;
        constexpr auto accelerationAlphaAForCrest = 1.1;
        constexpr auto accelerationAlphaAForInnerSlope = 1.2;
        constexpr auto dikeHeight = 1.3;

        auto constructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(x, topLayerType);
        constructionProperties->SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties->SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties->SetCriticalCumulativeOverload(make_unique<double>(criticalCumulativeOverload));
        constructionProperties->SetCriticalFrontVelocity(make_unique<double>(criticalFrontVelocity));
        constructionProperties->SetIncreasedLoadTransitionAlphaM(make_unique<double>(increasedLoadTransitionAlphaM));
        constructionProperties->SetReducedStrengthTransitionAlphaS(make_unique<double>(reducedStrengthTransitionAlphaS));
        constructionProperties->SetAverageNumberOfWavesCtm(make_unique<double>(averageNumberOfWavesCtm));
        constructionProperties->SetFixedNumberOfWaves(make_unique<int>(fixedNumberOfWaves));
        constructionProperties->SetFrontVelocityCwo(make_unique<double>(frontVelocityCwo));
        constructionProperties->SetAccelerationAlphaAForCrest(make_unique<double>(accelerationAlphaAForCrest));
        constructionProperties->SetAccelerationAlphaAForInnerSlope(make_unique<double>(accelerationAlphaAForInnerSlope));
        constructionProperties->SetDikeHeight(make_unique<double>(dikeHeight));

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddGrassOvertoppingLocation(move(constructionProperties));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
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

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithNotFullyConfiguredClosedSodGrassOvertoppingLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto topLayerType = GrassRevetmentTopLayerType::ClosedSod;
        constexpr auto x = 0.1;

        auto constructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(x, topLayerType);

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddGrassOvertoppingLocation(move(constructionProperties));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
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

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithNotFullyConfiguredOpenSodGrassOvertoppingLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto topLayerType = GrassRevetmentTopLayerType::OpenSod;
        constexpr auto x = 0.1;

        auto constructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(x, topLayerType);

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddGrassOvertoppingLocation(move(constructionProperties));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
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

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithGrassWaveImpactLocationWithInvalidTopLayerType_WhenBuild_ThenThrowsCalculationInputBuildException)
    {
        // Given & When
        const auto action = &CalculationInputBuilderTest::CreateBuilderAndAddGrassRevetmentWaveImpactLocationWithInvalidTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<CalculationInputBuildException, InputFactoryException>(
            action, "Could not create calculation input.", "Couldn't create defaults for the given top layer type.");
    }

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithFullyConfiguredGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto topLayerType = static_cast<GrassRevetmentTopLayerType>(rand() % 2);
        constexpr auto x = 0.1;
        constexpr auto initialDamage = 0.2;
        constexpr auto failureNumber = 0.3;
        constexpr auto timeLineAgwi = 0.4;
        constexpr auto timeLineBgwi = 0.5;
        constexpr auto timeLineCgwi = 0.6;
        constexpr auto minimumWaveHeightTemax = 0.7;
        constexpr auto maximumWaveHeightTemin = 0.8;
        constexpr auto waveAngleImpactNwa = 0.9;
        constexpr auto waveAngleImpactQwa = 1.0;
        constexpr auto waveAngleImpactRwa = 1.1;
        constexpr auto upperLimitLoadingAul = 1.2;
        constexpr auto lowerLimitLoadingAll = 1.3;

        auto constructionProperties = make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(x, topLayerType);
        constructionProperties->SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties->SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties->SetTimeLineAgwi(make_unique<double>(timeLineAgwi));
        constructionProperties->SetTimeLineBgwi(make_unique<double>(timeLineBgwi));
        constructionProperties->SetTimeLineCgwi(make_unique<double>(timeLineCgwi));
        constructionProperties->SetMinimumWaveHeightTemax(make_unique<double>(minimumWaveHeightTemax));
        constructionProperties->SetMaximumWaveHeightTemin(make_unique<double>(maximumWaveHeightTemin));
        constructionProperties->SetWaveAngleImpactNwa(make_unique<double>(waveAngleImpactNwa));
        constructionProperties->SetWaveAngleImpactQwa(make_unique<double>(waveAngleImpactQwa));
        constructionProperties->SetWaveAngleImpactRwa(make_unique<double>(waveAngleImpactRwa));
        constructionProperties->SetUpperLimitLoadingAul(make_unique<double>(upperLimitLoadingAul));
        constructionProperties->SetLowerLimitLoadingAll(make_unique<double>(lowerLimitLoadingAll));

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddGrassWaveImpactLocation(move(constructionProperties));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
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

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithNotFullyConfiguredClosedSodGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto topLayerType = GrassRevetmentTopLayerType::ClosedSod;
        constexpr auto x = 0.1;

        auto constructionProperties = make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(x, topLayerType);

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddGrassWaveImpactLocation(move(constructionProperties));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
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

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithNotFullyConfiguredOpenSodGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto topLayerType = GrassRevetmentTopLayerType::OpenSod;
        constexpr auto x = 0.1;

        auto constructionProperties = make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(x, topLayerType);

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddGrassWaveImpactLocation(move(constructionProperties));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
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

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithGrassWaveRunupRayleighLocationWithInvalidTopLayerType_WhenBuild_ThenThrowsCalculationInputBuildException)
    {
        // Given & When
        const auto action =
                &CalculationInputBuilderTest::CreateBuilderAndAddGrassRevetmentWaveRunupRayleighLocationWithInvalidTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<CalculationInputBuildException, InputFactoryException>(
            action, "Could not create calculation input.", "Couldn't create defaults for the given top layer type.");
    }

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithFullyConfiguredGrassWaveRunupRayleighLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        const auto topLayerType = static_cast<GrassRevetmentTopLayerType>(rand() % 2);
        constexpr auto x = 0.1;
        constexpr auto outerSlope = 0.2;
        constexpr auto initialDamage = 0.3;
        constexpr auto failureNumber = 0.4;
        constexpr auto criticalCumulativeOverload = 0.5;
        constexpr auto criticalFrontVelocity = 0.6;
        constexpr auto increasedLoadTransitionAlphaM = 0.7;
        constexpr auto reducedStrengthTransitionAlphaS = 0.8;
        constexpr auto averageNumberOfWavesCtm = 0.9;
        constexpr auto representativeWaveRunup2PAru = 1.0;
        constexpr auto representativeWaveRunup2PBru = 1.1;
        constexpr auto representativeWaveRunup2PCru = 1.2;
        constexpr auto representativeWaveRunup2PGammab = 1.3;
        constexpr auto representativeWaveRunup2PGammaf = 1.4;
        constexpr auto waveAngleImpactAbeta = 1.5;
        constexpr auto waveAngleImpactBetamax = 1.6;
        constexpr auto fixedNumberOfWaves = 17;
        constexpr auto frontVelocityCu = 1.8;

        auto constructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(x, outerSlope, topLayerType);
        constructionProperties->SetInitialDamage(make_unique<double>(initialDamage));
        constructionProperties->SetFailureNumber(make_unique<double>(failureNumber));
        constructionProperties->SetCriticalCumulativeOverload(make_unique<double>(criticalCumulativeOverload));
        constructionProperties->SetCriticalFrontVelocity(make_unique<double>(criticalFrontVelocity));
        constructionProperties->SetIncreasedLoadTransitionAlphaM(make_unique<double>(increasedLoadTransitionAlphaM));
        constructionProperties->SetReducedStrengthTransitionAlphaS(make_unique<double>(reducedStrengthTransitionAlphaS));
        constructionProperties->SetAverageNumberOfWavesCtm(make_unique<double>(averageNumberOfWavesCtm));
        constructionProperties->SetRepresentativeWaveRunup2PAru(make_unique<double>(representativeWaveRunup2PAru));
        constructionProperties->SetRepresentativeWaveRunup2PBru(make_unique<double>(representativeWaveRunup2PBru));
        constructionProperties->SetRepresentativeWaveRunup2PCru(make_unique<double>(representativeWaveRunup2PCru));
        constructionProperties->SetRepresentativeWaveRunup2PGammab(make_unique<double>(representativeWaveRunup2PGammab));
        constructionProperties->SetRepresentativeWaveRunup2PGammaf(make_unique<double>(representativeWaveRunup2PGammaf));
        constructionProperties->SetWaveAngleImpactAbeta(make_unique<double>(waveAngleImpactAbeta));
        constructionProperties->SetWaveAngleImpactBetamax(make_unique<double>(waveAngleImpactBetamax));
        constructionProperties->SetFixedNumberOfWaves(make_unique<int>(fixedNumberOfWaves));
        constructionProperties->SetFrontVelocityCu(make_unique<double>(frontVelocityCu));

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddGrassWaveRunupRayleighLocation(move(constructionProperties));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
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

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithNotFullyConfiguredClosedSodGrassWaveRunupRayleighLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto topLayerType = GrassRevetmentTopLayerType::ClosedSod;
        constexpr auto x = 0.1;
        constexpr auto outerSlope = 0.2;

        auto constructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(x, outerSlope, topLayerType);

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddGrassWaveRunupRayleighLocation(move(constructionProperties));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
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

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithNotFullyConfiguredOpenSodGrassWaveRunupRayleighLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto topLayerType = GrassRevetmentTopLayerType::OpenSod;
        constexpr auto x = 0.1;
        constexpr auto outerSlope = 0.2;

        auto constructionProperties = make_unique<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(x, outerSlope, topLayerType);

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddGrassWaveRunupRayleighLocation(move(constructionProperties));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
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

    TEST_F(CalculationInputBuilderTest,
           GivenBuilderWithNaturalStoneLocationWithInvalidTopLayerType_WhenBuild_ThenThrowsCalculationInputBuildException)
    {
        // Given & When
        const auto action = &CalculationInputBuilderTest::CreateBuilderAndAddNaturalStoneRevetmentLocationWithInvalidTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessageAndInnerException<CalculationInputBuildException, InputFactoryException>(
            action, "Could not create calculation input.", "Couldn't create defaults for the given top layer type.");
    }

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithFullyConfiguredNaturalStoneLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto topLayerType = NaturalStoneRevetmentTopLayerType::NordicStone;
        constexpr auto x = 0.1;
        constexpr auto thicknessTopLayer = 0.2;
        constexpr auto relativeDensity = 0.3;
        constexpr auto initialDamage = 0.4;
        constexpr auto failureNumber = 0.5;
        constexpr auto hydraulicLoadXib = 0.6;
        constexpr auto hydraulicLoadAp = 0.7;
        constexpr auto hydraulicLoadBp = 0.8;
        constexpr auto hydraulicLoadCp = 0.9;
        constexpr auto hydraulicLoadNp = 1.0;
        constexpr auto hydraulicLoadAs = 1.1;
        constexpr auto hydraulicLoadBs = 1.2;
        constexpr auto hydraulicLoadCs = 1.3;
        constexpr auto hydraulicLoadNs = 1.4;
        constexpr auto slopeUpperLevelAus = 1.5;
        constexpr auto slopeLowerLevelAls = 1.6;
        constexpr auto upperLimitLoadingAul = 1.7;
        constexpr auto upperLimitLoadingBul = 1.8;
        constexpr auto upperLimitLoadingCul = 1.9;
        constexpr auto lowerLimitLoadingAll = 2.0;
        constexpr auto lowerLimitLoadingBll = 2.1;
        constexpr auto lowerLimitLoadingCll = 2.2;
        constexpr auto distanceMaximumWaveElevationAsmax = 2.3;
        constexpr auto distanceMaximumWaveElevationBsmax = 2.4;
        constexpr auto normativeWidthOfWaveImpactAwi = 2.5;
        constexpr auto normativeWidthOfWaveImpactBwi = 2.6;
        constexpr auto waveAngleImpactBetamax = 2.7;

        auto naturalStoneConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            x, topLayerType, thicknessTopLayer, relativeDensity);
        naturalStoneConstructionProperties->SetInitialDamage(make_unique<double>(initialDamage));
        naturalStoneConstructionProperties->SetFailureNumber(make_unique<double>(failureNumber));
        naturalStoneConstructionProperties->SetHydraulicLoadXib(make_unique<double>(hydraulicLoadXib));
        naturalStoneConstructionProperties->SetHydraulicLoadAp(make_unique<double>(hydraulicLoadAp));
        naturalStoneConstructionProperties->SetHydraulicLoadBp(make_unique<double>(hydraulicLoadBp));
        naturalStoneConstructionProperties->SetHydraulicLoadCp(make_unique<double>(hydraulicLoadCp));
        naturalStoneConstructionProperties->SetHydraulicLoadNp(make_unique<double>(hydraulicLoadNp));
        naturalStoneConstructionProperties->SetHydraulicLoadAs(make_unique<double>(hydraulicLoadAs));
        naturalStoneConstructionProperties->SetHydraulicLoadBs(make_unique<double>(hydraulicLoadBs));
        naturalStoneConstructionProperties->SetHydraulicLoadCs(make_unique<double>(hydraulicLoadCs));
        naturalStoneConstructionProperties->SetHydraulicLoadNs(make_unique<double>(hydraulicLoadNs));
        naturalStoneConstructionProperties->SetSlopeUpperLevelAus(make_unique<double>(slopeUpperLevelAus));
        naturalStoneConstructionProperties->SetSlopeLowerLevelAls(make_unique<double>(slopeLowerLevelAls));
        naturalStoneConstructionProperties->SetUpperLimitLoadingAul(make_unique<double>(upperLimitLoadingAul));
        naturalStoneConstructionProperties->SetUpperLimitLoadingBul(make_unique<double>(upperLimitLoadingBul));
        naturalStoneConstructionProperties->SetUpperLimitLoadingCul(make_unique<double>(upperLimitLoadingCul));
        naturalStoneConstructionProperties->SetLowerLimitLoadingAll(make_unique<double>(lowerLimitLoadingAll));
        naturalStoneConstructionProperties->SetLowerLimitLoadingBll(make_unique<double>(lowerLimitLoadingBll));
        naturalStoneConstructionProperties->SetLowerLimitLoadingCll(make_unique<double>(lowerLimitLoadingCll));
        naturalStoneConstructionProperties->SetDistanceMaximumWaveElevationAsmax(make_unique<double>(distanceMaximumWaveElevationAsmax));
        naturalStoneConstructionProperties->SetDistanceMaximumWaveElevationBsmax(make_unique<double>(distanceMaximumWaveElevationBsmax));
        naturalStoneConstructionProperties->SetNormativeWidthOfWaveImpactAwi(make_unique<double>(normativeWidthOfWaveImpactAwi));
        naturalStoneConstructionProperties->SetNormativeWidthOfWaveImpactBwi(make_unique<double>(normativeWidthOfWaveImpactBwi));
        naturalStoneConstructionProperties->SetWaveAngleImpactBetamax(make_unique<double>(waveAngleImpactBetamax));

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddNaturalStoneLocation(move(naturalStoneConstructionProperties));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
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

    TEST_F(CalculationInputBuilderTest, GivenBuilderWithNotFullyConfiguredNaturalStoneLocationAdded_WhenBuild_ThenReturnsCalculationInput)
    {
        // Given
        constexpr auto topLayerType = NaturalStoneRevetmentTopLayerType::NordicStone;
        constexpr auto x = 0.1;
        constexpr auto thicknessTopLayer = 0.2;
        constexpr auto relativeDensity = 0.3;

        auto naturalStoneConstructionProperties = make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
            x, topLayerType, thicknessTopLayer, relativeDensity);

        CalculationInputBuilder builder;
        builder.AddDikeProfileSegment(0, 10, 10, 20, nullptr);
        builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        builder.AddNaturalStoneLocation(move(naturalStoneConstructionProperties));

        // When
        const auto& calculationInput = builder.Build();

        // Then
        const auto& actualLocationDependentInputItems = calculationInput->GetLocationDependentInputItems();
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
