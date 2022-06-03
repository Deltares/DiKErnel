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
    using namespace DiKErnel::TestUtil;
    using namespace Integration;
    using namespace Integration::TestUtil;
    using namespace std;
    using namespace testing;
    using namespace Util;
    using namespace Util::TestUtil;

    struct JsonInputComposerTest : Test
    {
        static void PerformProcessTypeTest(
            const string& fileName,
            const JsonInputProcessType expectedProcessType)
        {
            // Given
            const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
                / fileName).string();

            // When
            const auto processType = JsonInputComposer::GetInputDataFromJson(filePath)->GetData()->GetProcessType();

            // Then
            ASSERT_EQ(expectedProcessType, processType);
        }

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
                events.at(0).get());
        }
    };

    TEST_F(JsonInputComposerTest, GivenJsonInputWithoutProcessType_WhenGetInputDataFromJson_ThenReturnsResultWithDefaultJsonInputProcessType)
    {
        PerformProcessTypeTest("AllLocationsInput.json", JsonInputProcessType::Damage);
    }

    TEST_F(JsonInputComposerTest, GivenJsonFileWithProcessTypeFailure_WhenGetInputDataFromJson_ThenReturnsResultWithExpectedJsonInputProcessType)
    {
        PerformProcessTypeTest("ProcessTypeFailure.json", JsonInputProcessType::Failure);
    }

    TEST_F(JsonInputComposerTest, GivenJsonFileWithProcessTypeDamage_WhenGetInputDataFromJson_ThenReturnsResultWithExpectedJsonInputProcessType)
    {
        PerformProcessTypeTest("ProcessTypeDamage.json", JsonInputProcessType::Damage);
    }

    TEST_F(JsonInputComposerTest, GivenJsonFileWithProcessTypePhysics_WhenGetInputDataFromJson_ThenReturnsResultWithExpectedJsonInputProcessType)
    {
        PerformProcessTypeTest("ProcessTypePhysics.json", JsonInputProcessType::Physics);
    }

    TEST_F(JsonInputComposerTest, GivenJsonFile_WhenGetInputDataFromJson_ThenReturnsResultWithICalculationInputWithExpectedValues)
    {
        // Given
        const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
            / "AllLocationsInput.json").string();

        // When
        const auto& result = JsonInputComposer::GetInputDataFromJson(filePath);
        const auto& calculationInput = result->GetData()->GetCalculationInput();

        // Then
        AssertHelper::AssertIsInstanceOf<CalculationInput>(&calculationInput);

        const auto& profileData = calculationInput.GetProfileData();

        const auto& profilePoints = profileData.GetProfilePoints();
        ASSERT_EQ(17, profilePoints.size());
        ProfileDataAssertHelper::AssertProfilePoint(-30, -11.85, profilePoints.at(0).get());
        ProfileDataAssertHelper::AssertProfilePoint(-20, -8.95, profilePoints.at(1).get());
        ProfileDataAssertHelper::AssertProfilePoint(-10, -6.05, profilePoints.at(2).get());
        ProfileDataAssertHelper::AssertProfilePoint(0, -3.15, profilePoints.at(3).get());
        ProfileDataAssertHelper::AssertProfilePoint(5, -1.7, profilePoints.at(4).get());
        ProfileDataAssertHelper::AssertProfilePoint(10, -0.25, profilePoints.at(5).get());
        ProfileDataAssertHelper::AssertProfilePoint(15, 1.2, profilePoints.at(6).get());
        ProfileDataAssertHelper::AssertProfilePoint(20, 2.65, profilePoints.at(7).get());
        ProfileDataAssertHelper::AssertProfilePoint(25, 4.1, profilePoints.at(8).get());
        ProfileDataAssertHelper::AssertProfilePoint(30, 5.55, profilePoints.at(9).get());
        ProfileDataAssertHelper::AssertProfilePoint(35, 7, profilePoints.at(10).get());
        ProfileDataAssertHelper::AssertProfilePoint(40, 8.45, profilePoints.at(11).get());
        ProfileDataAssertHelper::AssertProfilePoint(45, 9.9, profilePoints.at(12).get());
        ProfileDataAssertHelper::AssertProfilePoint(50, 11.35, profilePoints.at(13).get());
        ProfileDataAssertHelper::AssertProfilePoint(55, 12.8, profilePoints.at(14).get());
        ProfileDataAssertHelper::AssertProfilePoint(60, 14.25, profilePoints.at(15).get());
        ProfileDataAssertHelper::AssertProfilePoint(65, 15.7, profilePoints.at(16).get());

        const auto& characteristicPoints = profileData.GetCharacteristicPoints();
        ASSERT_EQ(4, characteristicPoints.size());
        ProfileDataAssertHelper::AssertCharacteristicPoint(profilePoints.at(9), CharacteristicPointType::OuterToe, characteristicPoints.at(0));
        ProfileDataAssertHelper::AssertCharacteristicPoint(profilePoints.at(11), CharacteristicPointType::CrestOuterBerm, characteristicPoints.at(1));
        ProfileDataAssertHelper::AssertCharacteristicPoint(profilePoints.at(13), CharacteristicPointType::NotchOuterBerm, characteristicPoints.at(2));
        ProfileDataAssertHelper::AssertCharacteristicPoint(profilePoints.at(16), CharacteristicPointType::OuterCrest, characteristicPoints.at(3));

        const auto& timeDependentInputItems = calculationInput.GetTimeDependentInputItems();
        ASSERT_EQ(5, timeDependentInputItems.size());
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(0, 100, 0.1, 0.5, 2, -10, timeDependentInputItems.at(0).get());
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(100, 500, 0.5, 0.8, 6, -5, timeDependentInputItems.at(1).get());
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(500, 800, 1.15, 1.2, 6, 0, timeDependentInputItems.at(2).get());
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(800, 1200, 1.77, 1.5, 7, 7, timeDependentInputItems.at(3).get());
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(1200, 2000, 2, 0.5, 4, 8, timeDependentInputItems.at(4).get());

        const auto& locationDependentInputItems = calculationInput.GetLocationDependentInputItems();
        ASSERT_EQ(10, locationDependentInputItems.size());

        const auto* naturalStoneRevetmentLocationDependentInputItem1 = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &locationDependentInputItems.at(0).get());
        ASSERT_NE(nullptr, naturalStoneRevetmentLocationDependentInputItem1);

        LocationDependentInputAssertHelper::AssertDamageProperties(0.1, 1.06, *naturalStoneRevetmentLocationDependentInputItem1);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertGeneralProperties(
            11, 1.65, 0.3, *naturalStoneRevetmentLocationDependentInputItem1);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(
            5, 1.3, 1.7, 0.9, -0.8, 10, -8, 6, 4.9, naturalStoneRevetmentLocationDependentInputItem1->GetHydraulicLoads());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertSlope(
            0.95, 1.8, naturalStoneRevetmentLocationDependentInputItem1->GetSlope());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            6.1, 3.6, 4.5, naturalStoneRevetmentLocationDependentInputItem1->GetUpperLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            4.1, 8, 0.5, naturalStoneRevetmentLocationDependentInputItem1->GetLowerLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertDistanceMaximumWaveElevation(
            0.7, 0.319, naturalStoneRevetmentLocationDependentInputItem1->GetDistanceMaximumWaveElevation());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertNormativeWidthOfWaveImpact(
            1, 0.01, naturalStoneRevetmentLocationDependentInputItem1->GetNormativeWidthOfWaveImpact());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            30, naturalStoneRevetmentLocationDependentInputItem1->GetWaveAngleImpact());

        const auto* naturalStoneRevetmentLocationDependentInputItem2 = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &locationDependentInputItems.at(1).get());
        ASSERT_NE(nullptr, naturalStoneRevetmentLocationDependentInputItem2);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *naturalStoneRevetmentLocationDependentInputItem2);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertGeneralProperties(
            8.79, 1.65, 0.7, *naturalStoneRevetmentLocationDependentInputItem2);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(
            4, 0, 0, -0.9, 0.8, 0, 0, 0.6, 2.9, naturalStoneRevetmentLocationDependentInputItem2->GetHydraulicLoads());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertSlope(
            0.05, 1.5, naturalStoneRevetmentLocationDependentInputItem2->GetSlope());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            0.1, 0.6, 4, naturalStoneRevetmentLocationDependentInputItem2->GetUpperLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            0.1, 0.2, 4, naturalStoneRevetmentLocationDependentInputItem2->GetLowerLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertDistanceMaximumWaveElevation(
            0.42, 0.9, naturalStoneRevetmentLocationDependentInputItem2->GetDistanceMaximumWaveElevation());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertNormativeWidthOfWaveImpact(
            0.96, 0.11, naturalStoneRevetmentLocationDependentInputItem2->GetNormativeWidthOfWaveImpact());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            78, naturalStoneRevetmentLocationDependentInputItem2->GetWaveAngleImpact());

        const auto* grassRevetmentWaveImpactLocationDependentInputItem1 = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &locationDependentInputItems.at(2).get());
        ASSERT_NE(nullptr, grassRevetmentWaveImpactLocationDependentInputItem1);

        LocationDependentInputAssertHelper::AssertDamageProperties(0.04, 1.07, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            0, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            2500000, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            3.1, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            0.9, 0.1, 8, grassRevetmentWaveImpactLocationDependentInputItem1->GetWaveAngleImpact());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            0.3, -0.1, 0.96, grassRevetmentWaveImpactLocationDependentInputItem1->GetTimeLine());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            1, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            3.5, *grassRevetmentWaveImpactLocationDependentInputItem1);

        const auto* grassRevetmentWaveImpactLocationDependentInputItem2 = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &locationDependentInputItems.at(3).get());
        ASSERT_NE(nullptr, grassRevetmentWaveImpactLocationDependentInputItem2);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            -18.4, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            3600000, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            3.6, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            2.0 / 3.0, 0.35, 10, grassRevetmentWaveImpactLocationDependentInputItem2->GetWaveAngleImpact());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            1, -0.000009722, 0.25, grassRevetmentWaveImpactLocationDependentInputItem2->GetTimeLine());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            0, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            0.5, *grassRevetmentWaveImpactLocationDependentInputItem2);

        const auto* grassRevetmentWaveImpactLocationDependentInputItem3 = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &locationDependentInputItems.at(4).get());
        ASSERT_NE(nullptr, grassRevetmentWaveImpactLocationDependentInputItem3);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *grassRevetmentWaveImpactLocationDependentInputItem3);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            4, *grassRevetmentWaveImpactLocationDependentInputItem3);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            3600000, *grassRevetmentWaveImpactLocationDependentInputItem3);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            3.6, *grassRevetmentWaveImpactLocationDependentInputItem3);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            2.0 / 3.0, 0.35, 10, grassRevetmentWaveImpactLocationDependentInputItem3->GetWaveAngleImpact());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            0.8, -0.00001944, 0.25, grassRevetmentWaveImpactLocationDependentInputItem3->GetTimeLine());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            0, *grassRevetmentWaveImpactLocationDependentInputItem3);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            0.5, *grassRevetmentWaveImpactLocationDependentInputItem3);

        const auto* grassRevetmentWaveRunupRayleighLocationDependentInputItem1 = dynamic_cast
                <GrassRevetmentWaveRunupRayleighLocationDependentInput*>(&locationDependentInputItems.at(5).get());
        ASSERT_NE(nullptr, grassRevetmentWaveRunupRayleighLocationDependentInputItem1);

        LocationDependentInputAssertHelper::AssertDamageProperties(0.0006, 0.45, *grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            157, 0.7, *grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertRepresentative2P(
            1.56, 4.6, 3.5, 3.2, 4.1, grassRevetmentWaveRunupRayleighLocationDependentInputItem1->GetRepresentative2P());
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            0.0011, 89, grassRevetmentWaveRunupRayleighLocationDependentInputItem1->GetWaveAngleImpact());
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertTransitionAlpha(
            1.5, 0.8, *grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            0.99, *grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertCumulativeOverload(
            7213, 5000, *grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertFrontVelocity(
            8.3, 3.5, *grassRevetmentWaveRunupRayleighLocationDependentInputItem1);

        const auto* grassRevetmentWaveRunupRayleighLocationDependentInputItem2 = dynamic_cast
                <GrassRevetmentWaveRunupRayleighLocationDependentInput*>(&locationDependentInputItems.at(6).get());
        ASSERT_NE(nullptr, grassRevetmentWaveRunupRayleighLocationDependentInputItem2);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            0.98, 0.8, *grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
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
            6.6, 1.1, *grassRevetmentWaveRunupRayleighLocationDependentInputItem2);

        const auto* grassRevetmentWaveRunupRayleighLocationDependentInputItem3 = dynamic_cast
                <GrassRevetmentWaveRunupRayleighLocationDependentInput*>(&locationDependentInputItems.at(7).get());
        ASSERT_NE(nullptr, grassRevetmentWaveRunupRayleighLocationDependentInputItem3);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *grassRevetmentWaveRunupRayleighLocationDependentInputItem3);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            7.698, 0.9, *grassRevetmentWaveRunupRayleighLocationDependentInputItem3);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertRepresentative2P(
            1.65, 4, 1.5, 1, 1, grassRevetmentWaveRunupRayleighLocationDependentInputItem3->GetRepresentative2P());
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            0.0022, 80, grassRevetmentWaveRunupRayleighLocationDependentInputItem3->GetWaveAngleImpact());
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertTransitionAlpha(
            1, 1, *grassRevetmentWaveRunupRayleighLocationDependentInputItem3);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertAverageNumberOfWaves(
            0.92, *grassRevetmentWaveRunupRayleighLocationDependentInputItem3);
        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertCumulativeOverload(
            7000, 10000, *grassRevetmentWaveRunupRayleighLocationDependentInputItem3);
        GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper::AssertFrontVelocity(
            4.3, 1.1, *grassRevetmentWaveRunupRayleighLocationDependentInputItem3);

        const auto* asphaltRevetmentWaveImpactLocationDependentInputItem1 = dynamic_cast
                <AsphaltRevetmentWaveImpactLocationDependentInput*>(&locationDependentInputItems.at(8).get());
        ASSERT_NE(nullptr, asphaltRevetmentWaveImpactLocationDependentInputItem1);

        LocationDependentInputAssertHelper::AssertDamageProperties(1, 0.0098, *asphaltRevetmentWaveImpactLocationDependentInputItem1);
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            25, 0.6548, 5.6, 0.25, 53, 1.1, 4, 0.58, *asphaltRevetmentWaveImpactLocationDependentInputItem1);
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(
            0.16, 18214, asphaltRevetmentWaveImpactLocationDependentInputItem1->GetUpperLayer());
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(
            0.2, 15000, *asphaltRevetmentWaveImpactLocationDependentInputItem1->GetSubLayer());
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFatigue(
            0.723, 7.2, asphaltRevetmentWaveImpactLocationDependentInputItem1->GetFatigue());

        const auto expectedWidthFactors1 = vector
        {
            pair(1.6, 1.0392),
            pair(1.7, 1.0738)
        };

        const auto expectedDepthFactors1 = vector
        {
            pair(-2.0, 1.0244),
            pair(-1.875, 1.0544)
        };

        const auto expectedImpactFactors1 = vector
        {
            pair(6.0, 2.039),
            pair(6.4, 2.1)
        };

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFactors(
            expectedWidthFactors1, expectedDepthFactors1, expectedImpactFactors1, *asphaltRevetmentWaveImpactLocationDependentInputItem1);

        const auto* asphaltRevetmentWaveImpactLocationDependentInputItem2 = dynamic_cast
                <AsphaltRevetmentWaveImpactLocationDependentInput*>(&locationDependentInputItems.at(9).get());
        ASSERT_NE(nullptr, asphaltRevetmentWaveImpactLocationDependentInputItem2);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *asphaltRevetmentWaveImpactLocationDependentInputItem2);
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            19, 0.233, 1.56, 1.25, 56, 1, 1, 0.35, *asphaltRevetmentWaveImpactLocationDependentInputItem2);
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(
            0.16, 18214, asphaltRevetmentWaveImpactLocationDependentInputItem2->GetUpperLayer());
        ASSERT_EQ(nullptr, asphaltRevetmentWaveImpactLocationDependentInputItem2->GetSubLayer());
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFatigue(
            0.42, 4.76, asphaltRevetmentWaveImpactLocationDependentInputItem2->GetFatigue());

        const auto expectedWidthFactors2 = vector
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

        const auto expectedDepthFactors2 = vector
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

        const auto expectedImpactFactors2 = vector
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
            expectedWidthFactors2, expectedDepthFactors2, expectedImpactFactors2, *asphaltRevetmentWaveImpactLocationDependentInputItem2);
    }

    TEST_F(JsonInputComposerTest,
           GivenJsonInputWithInvalidCharacteristicPointType_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent)
    {
        PerformInvalidJsonTest("InvalidCharacteristicPointType.json", "Cannot convert characteristic point type.");
    }

    TEST_F(JsonInputComposerTest,
           GivenJsonInputWithInvalidAsphaltRevetmentWaveImpactTypeTopLayer_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent)
    {
        PerformInvalidJsonTest("InvalidAsphaltRevetmentWaveImpactTopLayerType.json", "Cannot convert top layer type.");
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
           GivenJsonInputWithInvalidNaturalStoneRevetmentTypeTopLayer_WhenGetInputDataFromJson_TThenReturnsResultWithSuccessfulFalseAndEvent)
    {
        PerformInvalidJsonTest("InvalidNaturalStoneRevetmentTopLayerType.json", "Cannot convert top layer type.");
    }
}
