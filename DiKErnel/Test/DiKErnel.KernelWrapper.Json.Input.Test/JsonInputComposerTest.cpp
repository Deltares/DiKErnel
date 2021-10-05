// Copyright (C) Stichting Deltares 2020. All rights reserved.
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
#include "GrassRevetmentWaveImpactLocationDependentInput.h"
#include "GrassRevetmentWaveImpactLocationDependentInputAssertHelper.h"
#include "GrassRevetmentWaveRunupLocationDependentInputAssertHelper.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInput.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.h"
#include "JsonInputConversionException.h"
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

    struct JsonInputComposerTest : Test
    {
        static void PerformProcessTypeTest(
            const string& filename,
            const JsonInputProcessType expectedProcessType)
        {
            // Given
            const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
                / filename).string();

            // When
            const auto processType = get<1>(JsonInputComposer::GetInputDataFromJson(filePath));

            // Then
            ASSERT_EQ(expectedProcessType, processType);
        }

        static void GetInputDataFromJsonWithInvalidAsphaltRevetmentWaveImpactTopLayerType()
        {
            const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
                / "InvalidAsphaltRevetmentWaveImpactTopLayerType.json").string();

            JsonInputComposer::GetInputDataFromJson(filePath);
        }

        static void GetInputDataFromJsonWithInvalidNaturalStoneRevetmentTopLayerType()
        {
            const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
                / "InvalidNaturalStoneRevetmentTopLayerType.json").string();

            JsonInputComposer::GetInputDataFromJson(filePath);
        }

        static void GetInputDataFromJsonWithInvalidGrassRevetmentWaveImpactTopLayerType()
        {
            const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
                / "InvalidGrassRevetmentWaveImpactTopLayerType.json").string();

            JsonInputComposer::GetInputDataFromJson(filePath);
        }

        static void GetInputDataFromJsonWithInvalidGrassRevetmentWaveRunupRayleighTopLayerType()
        {
            const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
                / "InvalidGrassRevetmentWaveRunupRayleighTopLayerType.json").string();

            JsonInputComposer::GetInputDataFromJson(filePath);
        }
    };

    TEST_F(JsonInputComposerTest, GivenJsonInputWithoutProcessType_WhenGetInputDataFromJson_ThenReturnDefaultJsonInputProcessType)
    {
        PerformProcessTypeTest("AllLocationsInput.json", JsonInputProcessType::Damage);
    }

    TEST_F(JsonInputComposerTest, GivenJsonFileWithProcessTypeFailure_WhenGetInputDataFromJson_ThenReturnExpectedJsonInputProcessType)
    {
        PerformProcessTypeTest("ProcessTypeFailure.json", JsonInputProcessType::Failure);
    }

    TEST_F(JsonInputComposerTest, GivenJsonFileWithProcessTypeDamage_WhenGetInputDataFromJson_ThenReturnExpectedJsonInputProcessType)
    {
        PerformProcessTypeTest("ProcessTypeDamage.json", JsonInputProcessType::Damage);
    }

    TEST_F(JsonInputComposerTest, GivenJsonFileWithProcessTypePhysics_WhenGetInputDataFromJson_ThenReturnExpectedJsonInputProcessType)
    {
        PerformProcessTypeTest("ProcessTypePhysics.json", JsonInputProcessType::Physics);
    }

    TEST_F(JsonInputComposerTest, GivenJsonFile_WhenGetInputDataFromJson_ThenReturnICalculationInputWithExpectedValues)
    {
        // Given
        const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
            / "AllLocationsInput.json").string();

        // When
        const auto calculationInput = get<0>(JsonInputComposer::GetInputDataFromJson(filePath));

        // Then
        AssertHelper::AssertIsInstanceOf<CalculationInput>(calculationInput.get());

        const auto& profileData = calculationInput->GetProfileData();

        const auto& profilePoints = profileData.GetProfilePoints();
        ASSERT_EQ(17, profilePoints.size());
        ProfileDataAssertHelper::AssertProfilePoint(-30, -11.85, profilePoints[0].get());
        ProfileDataAssertHelper::AssertProfilePoint(-20, -8.95, profilePoints[1].get());
        ProfileDataAssertHelper::AssertProfilePoint(-10, -6.05, profilePoints[2].get());
        ProfileDataAssertHelper::AssertProfilePoint(0, -3.15, profilePoints[3].get());
        ProfileDataAssertHelper::AssertProfilePoint(5, -1.7, profilePoints[4].get());
        ProfileDataAssertHelper::AssertProfilePoint(10, -0.25, profilePoints[5].get());
        ProfileDataAssertHelper::AssertProfilePoint(15, 1.2, profilePoints[6].get());
        ProfileDataAssertHelper::AssertProfilePoint(20, 2.65, profilePoints[7].get());
        ProfileDataAssertHelper::AssertProfilePoint(25, 4.1, profilePoints[8].get());
        ProfileDataAssertHelper::AssertProfilePoint(30, 5.55, profilePoints[9].get());
        ProfileDataAssertHelper::AssertProfilePoint(35, 7, profilePoints[10].get());
        ProfileDataAssertHelper::AssertProfilePoint(40, 8.45, profilePoints[11].get());
        ProfileDataAssertHelper::AssertProfilePoint(45, 9.9, profilePoints[12].get());
        ProfileDataAssertHelper::AssertProfilePoint(50, 11.35, profilePoints[13].get());
        ProfileDataAssertHelper::AssertProfilePoint(55, 12.8, profilePoints[14].get());
        ProfileDataAssertHelper::AssertProfilePoint(60, 14.25, profilePoints[15].get());
        ProfileDataAssertHelper::AssertProfilePoint(65, 15.7, profilePoints[16].get());

        const auto& characteristicPoints = profileData.GetCharacteristicPoints();
        ASSERT_EQ(4, characteristicPoints.size());
        ProfileDataAssertHelper::AssertCharacteristicPoint(profilePoints[9], CharacteristicPointType::OuterToe, characteristicPoints[0]);
        ProfileDataAssertHelper::AssertCharacteristicPoint(profilePoints[11], CharacteristicPointType::CrestOuterBerm, characteristicPoints[1]);
        ProfileDataAssertHelper::AssertCharacteristicPoint(profilePoints[13], CharacteristicPointType::NotchOuterBerm, characteristicPoints[2]);
        ProfileDataAssertHelper::AssertCharacteristicPoint(profilePoints[16], CharacteristicPointType::OuterCrest, characteristicPoints[3]);

        const auto& timeDependentInputItems = calculationInput->GetTimeDependentInputItems();
        ASSERT_EQ(5, timeDependentInputItems.size());
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(0, 100, 0.1, 0.5, 2, -10, timeDependentInputItems[0].get());
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(100, 500, 0.5, 0.8, 6, -5, timeDependentInputItems[1].get());
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(500, 800, 1.15, 1.2, 6, 0, timeDependentInputItems[2].get());
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(800, 1200, 1.77, 1.5, 7, 7, timeDependentInputItems[3].get());
        TimeDependentInputAssertHelper::AssertTimeDependentInputItem(1200, 2000, 2, 0.5, 4, 8, timeDependentInputItems[4].get());

        const auto& locationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(10, locationDependentInputItems.size());

        const auto* naturalStoneRevetmentLocationDependentInputItem1 = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &locationDependentInputItems[0].get());
        ASSERT_NE(nullptr, naturalStoneRevetmentLocationDependentInputItem1);

        LocationDependentInputAssertHelper::AssertDamageProperties(0.1, 1.06, *naturalStoneRevetmentLocationDependentInputItem1);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertGeneralProperties(
            "NatuursteenAlleOptiesAan", 0.25, 0.9, 1.65, 0.3, *naturalStoneRevetmentLocationDependentInputItem1);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(
            5, 1.3, 1.7, 0.9, -0.8, 10, -8, 6, 4.9, naturalStoneRevetmentLocationDependentInputItem1->GetHydraulicLoads());
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
            &locationDependentInputItems[1].get());
        ASSERT_NE(nullptr, naturalStoneRevetmentLocationDependentInputItem2);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *naturalStoneRevetmentLocationDependentInputItem2);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertGeneralProperties(
            "NatuursteenAlleOptiesUit", 0.3, 1, 1.65, 0.7, *naturalStoneRevetmentLocationDependentInputItem2);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(
            4, 0, 0, -0.9, 0.8, 0, 0, 0.6, 2.9, naturalStoneRevetmentLocationDependentInputItem2->GetHydraulicLoads());
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
            &locationDependentInputItems[2].get());
        ASSERT_NE(nullptr, grassRevetmentWaveImpactLocationDependentInputItem1);

        LocationDependentInputAssertHelper::AssertDamageProperties(0.04, 1.07, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            "GrasGolfklapAlleOptiesAan", 1, *grassRevetmentWaveImpactLocationDependentInputItem1);
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
            &locationDependentInputItems[3].get());
        ASSERT_NE(nullptr, grassRevetmentWaveImpactLocationDependentInputItem2);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            "GrasGolfklapGeslotenZodeAlleOptiesUit", 0, *grassRevetmentWaveImpactLocationDependentInputItem2);
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
            &locationDependentInputItems[4].get());
        ASSERT_NE(nullptr, grassRevetmentWaveImpactLocationDependentInputItem3);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *grassRevetmentWaveImpactLocationDependentInputItem3);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            "GrasGolfklapOpenZodeAlleOptiesUit", 0, *grassRevetmentWaveImpactLocationDependentInputItem3);
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
                <GrassRevetmentWaveRunupRayleighLocationDependentInput*>(&locationDependentInputItems[5].get());
        ASSERT_NE(nullptr, grassRevetmentWaveRunupRayleighLocationDependentInputItem1);

        LocationDependentInputAssertHelper::AssertDamageProperties(0.0006, 0.45, *grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            "GrasGolfoploopRayleighDiscreetAlleOptiesAan", 0.7, 5, *grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
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
                <GrassRevetmentWaveRunupRayleighLocationDependentInput*>(&locationDependentInputItems[6].get());
        ASSERT_NE(nullptr, grassRevetmentWaveRunupRayleighLocationDependentInputItem2);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            "GrasGolfoploopRayleighDiscreetGeslotenZodeAlleOptiesUit", 0.8, 5.1, *grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
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
                <GrassRevetmentWaveRunupRayleighLocationDependentInput*>(&locationDependentInputItems[7].get());
        ASSERT_NE(nullptr, grassRevetmentWaveRunupRayleighLocationDependentInputItem3);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *grassRevetmentWaveRunupRayleighLocationDependentInputItem3);
        GrassRevetmentWaveRunupLocationDependentInputAssertHelper::AssertGeneralProperties(
            "GrasGolfoploopRayleighDiscreetOpenZodeAlleOptiesUit", 0.9, 5.2, *grassRevetmentWaveRunupRayleighLocationDependentInputItem3);
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
                <AsphaltRevetmentWaveImpactLocationDependentInput*>(&locationDependentInputItems[8].get());
        ASSERT_NE(nullptr, asphaltRevetmentWaveImpactLocationDependentInputItem1);

        LocationDependentInputAssertHelper::AssertDamageProperties(1, 0.0098, *asphaltRevetmentWaveImpactLocationDependentInputItem1);
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            "AsfaltAlleOptiesAan", 0.6548, 7.6, 5.6, 0.25, 53, 1.1, 4, 0.58, *asphaltRevetmentWaveImpactLocationDependentInputItem1);
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(
            0.16, 18214, asphaltRevetmentWaveImpactLocationDependentInputItem1->GetUpperLayer());
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(
            0.2, 15000, asphaltRevetmentWaveImpactLocationDependentInputItem1->GetSubLayer());
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFatigue(
            0.723, 7.2, asphaltRevetmentWaveImpactLocationDependentInputItem1->GetFatigue());

        const auto expectedWidthFactors1 = vector
        {
            tuple(1.6, 1.0392),
            tuple(1.7, 1.0738)
        };

        const auto expectedDepthFactors1 = vector
        {
            tuple(-2.0, 1.0244),
            tuple(-1.875, 1.0544)
        };

        const auto expectedImpactFactors1 = vector
        {
            tuple(6.0, 2.039),
            tuple(6.4, 2.1)
        };

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFactors(
            expectedWidthFactors1, expectedDepthFactors1, expectedImpactFactors1, *asphaltRevetmentWaveImpactLocationDependentInputItem1);

        const auto* asphaltRevetmentWaveImpactLocationDependentInputItem2 = dynamic_cast
                <AsphaltRevetmentWaveImpactLocationDependentInput*>(&locationDependentInputItems[9].get());
        ASSERT_NE(nullptr, asphaltRevetmentWaveImpactLocationDependentInputItem2);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *asphaltRevetmentWaveImpactLocationDependentInputItem2);
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertGeneralProperties(
            "AsfaltAlleOptiesUit", 0.233, 2.988, 1.56, 1.25, 56, 1, 1, 0.35, *asphaltRevetmentWaveImpactLocationDependentInputItem2);
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(
            0.16, 18214, asphaltRevetmentWaveImpactLocationDependentInputItem2->GetUpperLayer());
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLayer(
            0, 18214, asphaltRevetmentWaveImpactLocationDependentInputItem2->GetSubLayer());
        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFatigue(
            0.42, 4.76, asphaltRevetmentWaveImpactLocationDependentInputItem2->GetFatigue());

        const auto expectedWidthFactors2 = vector
        {
            tuple(0.1, 0.0392),
            tuple(0.2, 0.0738),
            tuple(0.3, 0.1002),
            tuple(0.4, 0.1162),
            tuple(0.5, 0.1213),
            tuple(0.6, 0.1168),
            tuple(0.7, 0.1051),
            tuple(0.8, 0.0890),
            tuple(0.9, 0.0712),
            tuple(1.0, 0.0541),
            tuple(1.1, 0.0391),
            tuple(1.2, 0.0269),
            tuple(1.3, 0.0216),
            tuple(1.4, 0.0150),
            tuple(1.5, 0.0105)
        };

        const auto expectedDepthFactors2 = vector
        {
            tuple(-1.0, 0.0244),
            tuple(-0.875, 0.0544),
            tuple(-0.750, 0.0938),
            tuple(-0.625, 0.1407),
            tuple(-0.500, 0.1801),
            tuple(-0.375, 0.1632),
            tuple(-0.250, 0.1426),
            tuple(-0.125, 0.0994),
            tuple(0.0, 0.06),
            tuple(0.125, 0.0244),
            tuple(0.250, 0.0169)
        };

        const auto expectedImpactFactors2 = vector
        {
            tuple(2.0, 0.039),
            tuple(2.4, 0.1),
            tuple(2.8, 0.18),
            tuple(3.2, 0.235),
            tuple(3.6, 0.2),
            tuple(4.0, 0.13),
            tuple(4.4, 0.08),
            tuple(4.8, 0.02),
            tuple(5.2, 0.01),
            tuple(5.6, 0.005),
            tuple(6.0, 0.001)
        };

        AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper::AssertFactors(
            expectedWidthFactors2, expectedDepthFactors2, expectedImpactFactors2, *asphaltRevetmentWaveImpactLocationDependentInputItem2);
    }

    TEST_F(JsonInputComposerTest,
           GivenJsonInputWithInvalidAsphaltRevetmentWaveImpactTypeTopLayer_WhenGetInputDataFromJson_ThenThrowsJsonInputConversionException)
    {
        // Given & When
        const auto action = &JsonInputComposerTest::GetInputDataFromJsonWithInvalidAsphaltRevetmentWaveImpactTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessage<JsonInputConversionException>(action, "Cannot convert top layer type.");
    }

    TEST_F(JsonInputComposerTest,
           GivenJsonInputWithInvalidGrassRevetmentWaveImpactTypeTopLayer_WhenGetInputDataFromJson_ThenThrowsJsonInputConversionException)
    {
        // Given & When
        const auto action = &JsonInputComposerTest::GetInputDataFromJsonWithInvalidGrassRevetmentWaveImpactTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessage<JsonInputConversionException>(action, "Cannot convert top layer type.");
    }

    TEST_F(JsonInputComposerTest,
           GivenJsonInputWithInvalidGrassRevetmentWaveRunupRayleighTypeTopLayer_WhenGetInputDataFromJson_ThenThrowsJsonInputConversionException)
    {
        // Given & When
        const auto action = &JsonInputComposerTest::GetInputDataFromJsonWithInvalidGrassRevetmentWaveRunupRayleighTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessage<JsonInputConversionException>(action, "Cannot convert top layer type.");
    }

    TEST_F(JsonInputComposerTest,
           GivenJsonInputWithInvalidNaturalStoneRevetmentTypeTopLayer_WhenGetInputDataFromJson_ThenThrowsJsonInputConversionException)
    {
        // Given & When
        const auto action = &JsonInputComposerTest::GetInputDataFromJsonWithInvalidNaturalStoneRevetmentTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessage<JsonInputConversionException>(action, "Cannot convert top layer type.");
    }
}
