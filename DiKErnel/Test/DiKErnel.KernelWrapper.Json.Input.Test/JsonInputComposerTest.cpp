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
#include "CalculationInput.h"
#include "EventAssertHelper.h"
#include "EventRegistry.h"
#include "GrassRevetmentOvertoppingLocationDependentInput.h"
#include "GrassRevetmentOvertoppingLocationDependentInputAssertHelper.h"
#include "GrassRevetmentWaveImpactLocationDependentInput.h"
#include "GrassRevetmentWaveImpactLocationDependentInputAssertHelper.h"
#include "GrassRevetmentWaveRunupLocationDependentInputAssertHelper.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInput.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.h"
#include "JsonInputComposer.h"
#include "LocationDependentInputAssertHelper.h"
#include "NaturalStoneRevetmentLocationDependentInput.h"
#include "NaturalStoneRevetmentLocationDependentInputAssertHelper.h"
#include "ProfileDataAssertHelper.h"
#include "TestDataPathHelper.h"
#include "TimeDependentInputAssertHelper.h"

namespace DiKErnel::KernelWrapper::Json::Input::Test
{
    using namespace Core;
    using namespace Integration;
    using namespace DiKErnel::TestUtil;
    using namespace Integration::TestUtil;
    using namespace std;
    using namespace testing;
    using namespace Util;
    using namespace Util::TestUtil;

    struct JsonInputComposerTest : Test
    {
        static void PerformInvalidJsonTest(
            const string& fileName,
            const string& expectedStackTrace)
        {
            // Given
            const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
                / fileName).string();

            // When
            const auto& result = JsonInputComposer::GetInputDataFromJson(filePath);

            // Then
            ASSERT_FALSE(result->GetSuccessful());

            const auto& events = result->GetEvents();
            ASSERT_EQ(1, events.size());

            EventAssertHelper::AssertEvent(
                EventType::Error,
                "An unhandled error occurred while composing calculation data from the Json input. See stack trace for more information:\n"
                + expectedStackTrace,
                events.at(0));
        }
    };

    TEST_F(JsonInputComposerTest, GivenJsonFileWithAllData_WhenGetInputDataFromJson_ThenReturnsResultWithICalculationInputWithExpectedValues)
    {
        // Given
        const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
            / "InputWithAllData.json").string();

        // When
        const auto& result = JsonInputComposer::GetInputDataFromJson(filePath);
        const auto& calculationInput = *result->GetData();

        // Then
        AssertHelper::AssertIsInstanceOf<CalculationInput>(&calculationInput);

        const auto& profileData = calculationInput.GetProfileData();

        const auto& profileSegments = profileData.GetProfileSegments();
        ASSERT_EQ(23, profileSegments.size());
        ProfileDataAssertHelper::AssertProfileSegment(-30, -11.85, -20, -8.95, 0, profileSegments.at(0));
        ProfileDataAssertHelper::AssertProfileSegment(-20, -8.95, -10, -6.05, 0.05, profileSegments.at(1));
        ProfileDataAssertHelper::AssertProfileSegment(-10, -6.05, 0, -3.15, 0.1, profileSegments.at(2));
        ProfileDataAssertHelper::AssertProfileSegment(0, -3.15, 5, -1.7, 0.15, profileSegments.at(3));
        ProfileDataAssertHelper::AssertProfileSegment(5, -1.7, 10, -0.25, 0.2, profileSegments.at(4));
        ProfileDataAssertHelper::AssertProfileSegment(10, -0.25, 15, 1.2, 0.25, profileSegments.at(5));
        ProfileDataAssertHelper::AssertProfileSegment(15, 1.2, 20, 2.65, 0.3, profileSegments.at(6));
        ProfileDataAssertHelper::AssertProfileSegment(20, 2.65, 25, 4.1, 0.35, profileSegments.at(7));
        ProfileDataAssertHelper::AssertProfileSegment(25, 4.1, 30, 5.55, 0.4, profileSegments.at(8));
        ProfileDataAssertHelper::AssertProfileSegment(30, 5.55, 35, 7, 0.45, profileSegments.at(9));
        ProfileDataAssertHelper::AssertProfileSegment(35, 7, 40, 8.45, 0.5, profileSegments.at(10));
        ProfileDataAssertHelper::AssertProfileSegment(40, 8.45, 45, 9.9, 0.55, profileSegments.at(11));
        ProfileDataAssertHelper::AssertProfileSegment(45, 9.9, 50, 11.35, 0.6, profileSegments.at(12));
        ProfileDataAssertHelper::AssertProfileSegment(50, 11.35, 55, 12.8, 0.65, profileSegments.at(13));
        ProfileDataAssertHelper::AssertProfileSegment(55, 12.8, 60, 14.25, 0.7, profileSegments.at(14));
        ProfileDataAssertHelper::AssertProfileSegment(60, 14.25, 65, 15.7, 0.75, profileSegments.at(15));
        ProfileDataAssertHelper::AssertProfileSegment(65, 15.7, 70, 15.8, 0.8, profileSegments.at(16));
        ProfileDataAssertHelper::AssertProfileSegment(70, 15.8, 75, 14.3, 0.85, profileSegments.at(17));
        ProfileDataAssertHelper::AssertProfileSegment(75, 14.3, 80, 12.7, 0.9, profileSegments.at(18));
        ProfileDataAssertHelper::AssertProfileSegment(80, 12.7, 85, 11.4, 0.95, profileSegments.at(19));
        ProfileDataAssertHelper::AssertProfileSegment(85, 11.4, 90, 10, 1, profileSegments.at(20));
        ProfileDataAssertHelper::AssertProfileSegment(90, 10, 95, 8.5, 1.05, profileSegments.at(21));
        ProfileDataAssertHelper::AssertProfileSegment(95, 8.5, 100, 7.1, 1.1, profileSegments.at(22));

        const auto& characteristicPoints = profileData.GetCharacteristicPoints();
        ASSERT_EQ(6, characteristicPoints.size());
        ProfileDataAssertHelper::AssertCharacteristicPoint(profileSegments.at(8).get().GetEndPoint(), CharacteristicPointType::OuterToe,
                                                           characteristicPoints.at(0));
        ProfileDataAssertHelper::AssertCharacteristicPoint(profileSegments.at(10).get().GetEndPoint(), CharacteristicPointType::CrestOuterBerm,
                                                           characteristicPoints.at(1));
        ProfileDataAssertHelper::AssertCharacteristicPoint(profileSegments.at(12.).get().GetEndPoint(), CharacteristicPointType::NotchOuterBerm,
                                                           characteristicPoints.at(2));
        ProfileDataAssertHelper::AssertCharacteristicPoint(profileSegments.at(15).get().GetEndPoint(), CharacteristicPointType::OuterCrest,
                                                           characteristicPoints.at(3));
        ProfileDataAssertHelper::AssertCharacteristicPoint(profileSegments.at(16).get().GetEndPoint(), CharacteristicPointType::InnerCrest,
                                                           characteristicPoints.at(4));
        ProfileDataAssertHelper::AssertCharacteristicPoint(profileSegments.at(22).get().GetEndPoint(), CharacteristicPointType::InnerToe,
                                                           characteristicPoints.at(5));

        const auto& timeDependentInputItems = calculationInput.GetTimeDependentInputItems();
        ASSERT_EQ(5, timeDependentInputItems.size());
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(0, 100, 0.1, 0.5, 2, -10, timeDependentInputItems.at(0));
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(100, 500, 0.5, 0.8, 6, -5, timeDependentInputItems.at(1));
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(500, 800, 1.15, 1.2, 6, 0, timeDependentInputItems.at(2));
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(800, 1200, 1.77, 1.5, 7, 7, timeDependentInputItems.at(3));
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(1200, 2000, 2, 0.5, 4, 8, timeDependentInputItems.at(4));

        const auto& locationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(5, locationDependentInputItems.size());

        const auto* naturalStoneRevetmentLocationDependentInputItem = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &locationDependentInputItems.at(0).get());
        ASSERT_NE(nullptr, naturalStoneRevetmentLocationDependentInputItem);

        LocationDependentInputAssertHelper::AssertDamageProperties(0.1, 1.06, *naturalStoneRevetmentLocationDependentInputItem);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertGeneralProperties(
            11, 1.65, 0.3, *naturalStoneRevetmentLocationDependentInputItem);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(
            5, 1.3, 1.7, 0.9, -0.8, 10, -8, 6, 4.9, naturalStoneRevetmentLocationDependentInputItem->GetHydraulicLoads());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertSlope(
            0.95, 1.8, naturalStoneRevetmentLocationDependentInputItem->GetSlope());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            6.1, 3.6, 4.5, naturalStoneRevetmentLocationDependentInputItem->GetUpperLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            4.1, 8, 0.5, naturalStoneRevetmentLocationDependentInputItem->GetLowerLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertDistanceMaximumWaveElevation(
            0.7, 0.319, naturalStoneRevetmentLocationDependentInputItem->GetDistanceMaximumWaveElevation());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertNormativeWidthOfWaveImpact(
            1, 0.01, naturalStoneRevetmentLocationDependentInputItem->GetNormativeWidthOfWaveImpact());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            30, naturalStoneRevetmentLocationDependentInputItem->GetWaveAngleImpact());

        const auto* grassRevetmentWaveImpactLocationDependentInputItem = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &locationDependentInputItems.at(1).get());
        ASSERT_NE(nullptr, grassRevetmentWaveImpactLocationDependentInputItem);

        LocationDependentInputAssertHelper::AssertDamageProperties(0.04, 1.07, *grassRevetmentWaveImpactLocationDependentInputItem);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            0, *grassRevetmentWaveImpactLocationDependentInputItem);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            2500000, *grassRevetmentWaveImpactLocationDependentInputItem);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            3.1, *grassRevetmentWaveImpactLocationDependentInputItem);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            0.9, 0.1, 8, grassRevetmentWaveImpactLocationDependentInputItem->GetWaveAngleImpact());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            0.3, -0.1, 0.96, grassRevetmentWaveImpactLocationDependentInputItem->GetTimeLine());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            1, *grassRevetmentWaveImpactLocationDependentInputItem);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            3.5, *grassRevetmentWaveImpactLocationDependentInputItem);

        const auto* grassRevetmentWaveRunupRayleighLocationDependentInputItem = dynamic_cast
                <GrassRevetmentWaveRunupRayleighLocationDependentInput*>(&locationDependentInputItems.at(2).get());
        ASSERT_NE(nullptr, grassRevetmentWaveRunupRayleighLocationDependentInputItem);

        LocationDependentInputAssertHelper::AssertDamageProperties(0.0006, 0.45, *grassRevetmentWaveRunupRayleighLocationDependentInputItem);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            157, 0.7, *grassRevetmentWaveRunupRayleighLocationDependentInputItem);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertRepresentative2P(
            1.56, 4.6, 3.5, 3.2, 4.1, grassRevetmentWaveRunupRayleighLocationDependentInputItem->GetRepresentative2P());
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            0.0011, 89, grassRevetmentWaveRunupRayleighLocationDependentInputItem->GetWaveAngleImpact());
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertTransitionAlpha(
            1.5, 0.8, *grassRevetmentWaveRunupRayleighLocationDependentInputItem);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            0.99, *grassRevetmentWaveRunupRayleighLocationDependentInputItem);
        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertCumulativeOverload(
            7213, 5000, *grassRevetmentWaveRunupRayleighLocationDependentInputItem);
        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertFrontVelocity(
            8.3, 3.5, *grassRevetmentWaveRunupRayleighLocationDependentInputItem);

        const auto* asphaltRevetmentWaveImpactLocationDependentInputItem = dynamic_cast
                <AsphaltRevetmentWaveImpactLocationDependentInput*>(&locationDependentInputItems.at(3).get());
        ASSERT_NE(nullptr, asphaltRevetmentWaveImpactLocationDependentInputItem);

        LocationDependentInputAssertHelper::AssertDamageProperties(1, 0.0098, *asphaltRevetmentWaveImpactLocationDependentInputItem);
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            25, 5.6, 0.25, 53, 1.1, 4, 0.58, *asphaltRevetmentWaveImpactLocationDependentInputItem);
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(
            0.16, 18214, asphaltRevetmentWaveImpactLocationDependentInputItem->GetUpperLayer());
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(
            0.2, 15000, *asphaltRevetmentWaveImpactLocationDependentInputItem->GetSubLayer());
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFatigue(
            0.723, 7.2, asphaltRevetmentWaveImpactLocationDependentInputItem->GetFatigue());

        const auto expectedWidthFactors = vector
        {
            pair(1.6, 1.0392),
            pair(1.7, 1.0738)
        };

        const auto expectedDepthFactors = vector
        {
            pair(-2.0, 1.0244),
            pair(-1.875, 1.0544)
        };

        const auto expectedImpactFactors = vector
        {
            pair(6.0, 2.039),
            pair(6.4, 2.1)
        };

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFactors(
            expectedWidthFactors, expectedDepthFactors, expectedImpactFactors, *asphaltRevetmentWaveImpactLocationDependentInputItem);

        const auto* grassRevetmentOvertoppingLocationDependentInputItem = dynamic_cast<GrassRevetmentOvertoppingLocationDependentInput*>(
            &locationDependentInputItems.at(4).get());
        ASSERT_NE(nullptr, grassRevetmentOvertoppingLocationDependentInputItem);
        LocationDependentInputAssertHelper::AssertDamageProperties(0.023, 0.3, *grassRevetmentOvertoppingLocationDependentInputItem);

        constexpr auto expectedDikeHeight = 8.21;
        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertGeneralProperties(
            64, &expectedDikeHeight, *grassRevetmentOvertoppingLocationDependentInputItem);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertTransitionAlpha(
            0.5, 1.8, *grassRevetmentOvertoppingLocationDependentInputItem);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            0.29, *grassRevetmentOvertoppingLocationDependentInputItem);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertCumulativeOverload(
            7001, 100000, *grassRevetmentOvertoppingLocationDependentInputItem);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertFrontVelocity(
            3.6, 45.1, *grassRevetmentOvertoppingLocationDependentInputItem);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertAccelerationAlphaA(
            1.8, 4.4, grassRevetmentOvertoppingLocationDependentInputItem->GetLocationDependentAccelerationAlphaA());
    }

    TEST_F(JsonInputComposerTest,
           GivenJsonFileWithAllMandatoryData_WhenGetInputDataFromJson_ThenReturnsResultWithICalculationInputWithExpectedValues)
    {
        // Given
        const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
            / "InputWithAllMandatoryData.json").string();

        // When
        const auto& result = JsonInputComposer::GetInputDataFromJson(filePath);
        const auto& calculationInput = *result->GetData();

        // Then
        AssertHelper::AssertIsInstanceOf<CalculationInput>(&calculationInput);

        const auto& profileData = calculationInput.GetProfileData();

        const auto& profileSegments = profileData.GetProfileSegments();
        ASSERT_EQ(3, profileSegments.size());
        auto profileSegment1 = profileSegments.at(0).get();
        auto profileSegment2 = profileSegments.at(1).get();
        auto profileSegment3 = profileSegments.at(2).get();
        ProfileDataAssertHelper::AssertProfileSegment(30, 5.55, 65, 15.7, 1, profileSegment1);
        ProfileDataAssertHelper::AssertProfileSegment(65, 15.7, 75, 15.7, 1, profileSegment2);
        ProfileDataAssertHelper::AssertProfileSegment(75, 15.7, 85, 10, 1, profileSegment3);

        const auto& characteristicPoints = profileData.GetCharacteristicPoints();
        ASSERT_EQ(4, characteristicPoints.size());

        ProfileDataAssertHelper::AssertCharacteristicPoint(profileSegment1.GetStartPoint(), CharacteristicPointType::OuterToe,
                                                           characteristicPoints.at(0));
        ProfileDataAssertHelper::AssertCharacteristicPoint(profileSegment1.GetEndPoint(), CharacteristicPointType::OuterCrest,
                                                           characteristicPoints.at(1));
        ProfileDataAssertHelper::AssertCharacteristicPoint(profileSegment3.GetStartPoint(), CharacteristicPointType::InnerCrest,
                                                           characteristicPoints.at(2));
        ProfileDataAssertHelper::AssertCharacteristicPoint(profileSegment3.GetEndPoint(), CharacteristicPointType::InnerToe,
                                                           characteristicPoints.at(3));

        const auto& timeDependentInputItems = calculationInput.GetTimeDependentInputItems();
        ASSERT_EQ(1, timeDependentInputItems.size());
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(0, 100, 0.1, 0.5, 2, -10, timeDependentInputItems.at(0));

        const auto& locationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(8, locationDependentInputItems.size());

        const auto* naturalStoneRevetmentLocationDependentInputItem = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &locationDependentInputItems.at(0).get());
        ASSERT_NE(nullptr, naturalStoneRevetmentLocationDependentInputItem);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *naturalStoneRevetmentLocationDependentInputItem);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertGeneralProperties(
            8.79, 1.65, 0.7, *naturalStoneRevetmentLocationDependentInputItem);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(
            4, 0, 0, -0.9, 0.8, 0, 0, 0.6, 2.9, naturalStoneRevetmentLocationDependentInputItem->GetHydraulicLoads());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertSlope(
            0.05, 1.5, naturalStoneRevetmentLocationDependentInputItem->GetSlope());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            0.1, 0.6, 4, naturalStoneRevetmentLocationDependentInputItem->GetUpperLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            0.1, 0.2, 4, naturalStoneRevetmentLocationDependentInputItem->GetLowerLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertDistanceMaximumWaveElevation(
            0.42, 0.9, naturalStoneRevetmentLocationDependentInputItem->GetDistanceMaximumWaveElevation());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertNormativeWidthOfWaveImpact(
            0.96, 0.11, naturalStoneRevetmentLocationDependentInputItem->GetNormativeWidthOfWaveImpact());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            78, naturalStoneRevetmentLocationDependentInputItem->GetWaveAngleImpact());

        const auto* grassRevetmentWaveImpactLocationDependentInputItem1 = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &locationDependentInputItems.at(1).get());
        ASSERT_NE(nullptr, grassRevetmentWaveImpactLocationDependentInputItem1);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            -18.4, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            3600000, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            3.6, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            2.0 / 3.0, 0.35, 10, grassRevetmentWaveImpactLocationDependentInputItem1->GetWaveAngleImpact());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            1, -0.000009722, 0.25, grassRevetmentWaveImpactLocationDependentInputItem1->GetTimeLine());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            0, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            0.5, *grassRevetmentWaveImpactLocationDependentInputItem1);

        const auto* grassRevetmentWaveImpactLocationDependentInputItem2 = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &locationDependentInputItems.at(2).get());
        ASSERT_NE(nullptr, grassRevetmentWaveImpactLocationDependentInputItem2);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            4, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            3600000, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            3.6, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            2.0 / 3.0, 0.35, 10, grassRevetmentWaveImpactLocationDependentInputItem2->GetWaveAngleImpact());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            0.8, -0.00001944, 0.25, grassRevetmentWaveImpactLocationDependentInputItem2->GetTimeLine());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            0, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            0.5, *grassRevetmentWaveImpactLocationDependentInputItem2);

        const auto* grassRevetmentWaveRunupRayleighLocationDependentInputItem1 = dynamic_cast
                <GrassRevetmentWaveRunupRayleighLocationDependentInput*>(&locationDependentInputItems.at(3).get());
        ASSERT_NE(nullptr, grassRevetmentWaveRunupRayleighLocationDependentInputItem1);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            0.98, 0.8, *grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertRepresentative2P(
            1.65, 4, 1.5, 1, 1, grassRevetmentWaveRunupRayleighLocationDependentInputItem1->GetRepresentative2P());
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            0.0022, 80, grassRevetmentWaveRunupRayleighLocationDependentInputItem1->GetWaveAngleImpact());
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertTransitionAlpha(
            1, 1, *grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            0.92, *grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertCumulativeOverload(
            7000, 10000, *grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertFrontVelocity(
            6.6, 1.1, *grassRevetmentWaveRunupRayleighLocationDependentInputItem1);

        const auto* grassRevetmentWaveRunupRayleighLocationDependentInputItem2 = dynamic_cast
                <GrassRevetmentWaveRunupRayleighLocationDependentInput*>(&locationDependentInputItems.at(4).get());
        ASSERT_NE(nullptr, grassRevetmentWaveRunupRayleighLocationDependentInputItem2);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            7.698, 0.9, *grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertRepresentative2P(
            1.65, 4, 1.5, 1, 1, grassRevetmentWaveRunupRayleighLocationDependentInputItem2->GetRepresentative2P());
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            0.0022, 80, grassRevetmentWaveRunupRayleighLocationDependentInputItem2->GetWaveAngleImpact());
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertTransitionAlpha(
            1, 1, *grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            0.92, *grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertCumulativeOverload(
            7000, 10000, *grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertFrontVelocity(
            4.3, 1.1, *grassRevetmentWaveRunupRayleighLocationDependentInputItem2);

        const auto* asphaltRevetmentWaveImpactLocationDependentInputItem = dynamic_cast
                <AsphaltRevetmentWaveImpactLocationDependentInput*>(&locationDependentInputItems.at(5).get());
        ASSERT_NE(nullptr, asphaltRevetmentWaveImpactLocationDependentInputItem);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *asphaltRevetmentWaveImpactLocationDependentInputItem);
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            19, 1.56, 1025, 56, 1, 1, 0.35, *asphaltRevetmentWaveImpactLocationDependentInputItem);
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(
            0.16, 18214, asphaltRevetmentWaveImpactLocationDependentInputItem->GetUpperLayer());
        ASSERT_EQ(nullptr, asphaltRevetmentWaveImpactLocationDependentInputItem->GetSubLayer());
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFatigue(
            0.42, 4.76, asphaltRevetmentWaveImpactLocationDependentInputItem->GetFatigue());

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

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFactors(
            expectedWidthFactors, expectedDepthFactors, expectedImpactFactors, *asphaltRevetmentWaveImpactLocationDependentInputItem);

        const auto* grassRevetmentOvertoppingLocationDependentInputItem1 = dynamic_cast<GrassRevetmentOvertoppingLocationDependentInput*>(
            &locationDependentInputItems.at(6).get());
        ASSERT_NE(nullptr, grassRevetmentOvertoppingLocationDependentInputItem1);
        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *grassRevetmentOvertoppingLocationDependentInputItem1);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertGeneralProperties(
            42, nullptr, *grassRevetmentOvertoppingLocationDependentInputItem1);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertTransitionAlpha(
            1, 1, *grassRevetmentOvertoppingLocationDependentInputItem1);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            0.92, *grassRevetmentOvertoppingLocationDependentInputItem1);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertCumulativeOverload(
            7000, 10000, *grassRevetmentOvertoppingLocationDependentInputItem1);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertFrontVelocity(
            6.6, 1.45, *grassRevetmentOvertoppingLocationDependentInputItem1);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertAccelerationAlphaA(
            1, 1.4, grassRevetmentOvertoppingLocationDependentInputItem1->GetLocationDependentAccelerationAlphaA());

        const auto* grassRevetmentOvertoppingLocationDependentInputItem2 = dynamic_cast<GrassRevetmentOvertoppingLocationDependentInput*>(
            &locationDependentInputItems.at(7).get());
        ASSERT_NE(nullptr, grassRevetmentOvertoppingLocationDependentInputItem2);
        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *grassRevetmentOvertoppingLocationDependentInputItem2);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertGeneralProperties(
            64, nullptr, *grassRevetmentOvertoppingLocationDependentInputItem2);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertTransitionAlpha(
            1, 1, *grassRevetmentOvertoppingLocationDependentInputItem2);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            0.92, *grassRevetmentOvertoppingLocationDependentInputItem2);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertCumulativeOverload(
            7000, 10000, *grassRevetmentOvertoppingLocationDependentInputItem2);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertFrontVelocity(
            4.3, 1.45, *grassRevetmentOvertoppingLocationDependentInputItem2);

        GrassRevetmentOvertoppingLocationDependentInputAssertHelper::AssertAccelerationAlphaA(
            1, 1.4, grassRevetmentOvertoppingLocationDependentInputItem2->GetLocationDependentAccelerationAlphaA());
    }

    TEST_F(JsonInputComposerTest,
           GivenJsonInputWithInvalidAsphaltRevetmentWaveImpactTypeTopLayer_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent)
    {
        PerformInvalidJsonTest("InvalidAsphaltRevetmentWaveImpactTopLayerType.json", "Cannot convert top layer type.");
    }

    TEST_F(JsonInputComposerTest,
           GivenJsonInputWithInvalidGrassRevetmentOvertoppingTypeTopLayer_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent)
    {
        PerformInvalidJsonTest("InvalidGrassRevetmentOvertoppingTopLayerType.json", "Cannot convert top layer type.");
    }

    TEST_F(JsonInputComposerTest,
           GivenJsonInputWithInvalidGrassRevetmentWaveImpactTypeTopLayer_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent)
    {
        PerformInvalidJsonTest("InvalidGrassRevetmentWaveImpactTopLayerType.json", "Cannot convert top layer type.");
    }

    TEST_F(JsonInputComposerTest,
           GivenJsonInputWithInvalidGrassRevetmentWaveRunupRayleighTypeTopLayer_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent)
    {
        PerformInvalidJsonTest("InvalidGrassRevetmentWaveRunupRayleighTopLayerType.json", "Cannot convert top layer type.");
    }

    TEST_F(JsonInputComposerTest,
           GivenJsonInputWithInvalidGrassRevetmentWaveRunupCalculationProtocolType_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent)
    {
        PerformInvalidJsonTest("InvalidGrassRevetmentWaveRunupCalculationProtocolType.json", "Cannot convert calculation protocol type.");
    }

    TEST_F(JsonInputComposerTest,
           GivenJsonInputWithGrassRevetmentWaveRunupNoCalculationMethod_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent)
    {
        PerformInvalidJsonTest("GrassRevetmentWaveRunupNoCalculationMethod.json", "Cannot convert calculation protocol type.");
    }

    TEST_F(JsonInputComposerTest,
           GivenJsonInputWithInvalidNaturalStoneRevetmentTypeTopLayer_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent)
    {
        PerformInvalidJsonTest("InvalidNaturalStoneRevetmentTopLayerType.json", "Cannot convert top layer type.");
    }

    TEST_F(JsonInputComposerTest, GivenNotExistingJsonInputFile_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent)
    {
        // Given
        const auto filePath = "NotExisting";

        // When
        const auto& result = JsonInputComposer::GetInputDataFromJson(filePath);

        // Then
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "The provided input file does not exist", events.at(0));
    }

    TEST_F(JsonInputComposerTest, GivenCompleteAndValidJsonInputFile_WhenValidatingJson_ThenReturnsTrueAndNoEventsRegistered)
    {
        // Given
        const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
            / "InputWithAllData.json").string();

        // When
        const auto result = JsonInputComposer::ValidateJson(filePath);

        // Then
        ASSERT_TRUE(result);
        ASSERT_EQ(0, EventRegistry::Flush().size());
    }

    TEST_F(JsonInputComposerTest, GivenInvalidJsonInputFile_WhenValidatingJson_ThenReturnsFalseAndExpectedEventsRegistered)
    {
        // Given
        const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
            / "InvalidFormat.json").string();

        // When
        const auto result = JsonInputComposer::ValidateJson(filePath);

        // Then
        ASSERT_FALSE(result);

        const auto& registeredEvents = EventRegistry::Flush();
        ASSERT_EQ(1, registeredEvents.size());
        EventAssertHelper::AssertEvent(EventType::Error, "At  of {} - required property 'tijdstippen' not found in object",
                                       *registeredEvents.at(0));
    }

    TEST_F(JsonInputComposerTest, GivenNotExistingJsonInputFile_WhenValidatingJson_ThenReturnsFalseAndExpectedEventsRegistered)
    {
        // Given
        const auto filePath = "NotExisting.json";

        // When
        const auto result = JsonInputComposer::ValidateJson(filePath);

        // Then
        ASSERT_FALSE(result);

        const auto& registeredEvents = EventRegistry::Flush();
        ASSERT_EQ(1, registeredEvents.size());
        EventAssertHelper::AssertEvent(EventType::Error, "The provided input file does not exist", *registeredEvents.at(0));
    }
}
