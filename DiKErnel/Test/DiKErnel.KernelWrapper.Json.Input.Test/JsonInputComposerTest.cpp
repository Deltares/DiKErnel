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

#include "AssertHelper.h"
#include "CalculationInput.h"
#include "GrassRevetmentWaveImpactLocationDependentInput.h"
#include "GrassRevetmentWaveImpactLocationDependentInputAssertHelper.h"
#include "JsonConversionException.h"
#include "JsonInputComposer.h"
#include "LocationDependentInputAssertHelper.h"
#include "NaturalStoneRevetmentLocationDependentInput.h"
#include "NaturalStoneRevetmentLocationDependentInputAssertHelper.h"
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
        static void GetCalculationInputFromJsonWithInvalidNaturalStoneRevetmentTopLayerType()
        {
            const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
                / "InvalidNaturalStoneRevetmentTopLayerType.json").string();

            JsonInputComposer::GetCalculationInputFromJson(filePath);
        }

        static void GetCalculationInputFromJsonWithInvalidGrassRevetmentTopLayerType()
        {
            const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
                / "InvalidGrassRevetmentTopLayerType.json").string();

            JsonInputComposer::GetCalculationInputFromJson(filePath);
        }

        void AssertTimeDependentInputItems(
            const vector<reference_wrapper<ITimeDependentInput>>& timeDependentInputItems) const
        {
            ASSERT_EQ(5, timeDependentInputItems.size());
            TimeDependentInputAssertHelper::AssertTimeDependentInputItem(0, 100, 0.1, 0.5, 2, -10, timeDependentInputItems[0].get());
            TimeDependentInputAssertHelper::AssertTimeDependentInputItem(100, 500, 0.5, 0.8, 6, -5, timeDependentInputItems[1].get());
            TimeDependentInputAssertHelper::AssertTimeDependentInputItem(500, 800, 1.15, 1.2, 6, 0, timeDependentInputItems[2].get());
            TimeDependentInputAssertHelper::AssertTimeDependentInputItem(800, 1200, 1.77, 1.5, 7, 7, timeDependentInputItems[3].get());
            TimeDependentInputAssertHelper::AssertTimeDependentInputItem(1200, 2000, 2, 0.5, 4, 8, timeDependentInputItems[4].get());
        }
    };

    TEST_F(JsonInputComposerTest, GivenJsonFile_WhenGetCalculationInputFromJson_ThenReturnICalculationInputWithExpectedValues)
    {
        // Given
        const auto filePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
            / "CompleteInput.json").string();

        // When
        const auto calculationInput = JsonInputComposer::GetCalculationInputFromJson(filePath);

        // Then
        AssertHelper::AssertIsInstanceOf<CalculationInput>(calculationInput.get());

        AssertTimeDependentInputItems(calculationInput->GetTimeDependentInputItems());

        const auto locationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(5, locationDependentInputItems.size());

        const auto* naturalStoneRevetmentLocationDependentInputItem1 = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &locationDependentInputItems[0].get());
        ASSERT_NE(nullptr, naturalStoneRevetmentLocationDependentInputItem1);

        LocationDependentInputAssertHelper::AssertDamageProperties(0.1, 1.06, *naturalStoneRevetmentLocationDependentInputItem1);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertMandatoryProperties(
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
            1.0, 0.01, naturalStoneRevetmentLocationDependentInputItem1->GetNormativeWidthOfWaveImpact());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            30, naturalStoneRevetmentLocationDependentInputItem1->GetWaveAngleImpact());

        const auto* naturalStoneRevetmentLocationDependentInputItem2 = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &locationDependentInputItems[1].get());
        ASSERT_NE(nullptr, naturalStoneRevetmentLocationDependentInputItem2);

        LocationDependentInputAssertHelper::AssertDamageProperties(0, 1, *naturalStoneRevetmentLocationDependentInputItem2);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertMandatoryProperties(
            "NatuursteenAlleOptiesUit", 0.3, 1.0, 1.65, 0.7, *naturalStoneRevetmentLocationDependentInputItem2);
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
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMandatoryProperties(
            "GrasGolfklapAlleOptiesAan", 1.0, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            2500000, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            3.1, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            0.9, 0.1, 8.0, grassRevetmentWaveImpactLocationDependentInputItem1->GetWaveAngleImpact());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            0.3, -0.1, 0.96, grassRevetmentWaveImpactLocationDependentInputItem1->GetTimeLine());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            1.0, *grassRevetmentWaveImpactLocationDependentInputItem1);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            3.5, *grassRevetmentWaveImpactLocationDependentInputItem1);

        const auto* grassRevetmentWaveImpactLocationDependentInputItem2 = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &locationDependentInputItems[3].get());
        ASSERT_NE(nullptr, grassRevetmentWaveImpactLocationDependentInputItem2);
        LocationDependentInputAssertHelper::AssertDamageProperties(0.0, 1.0, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMandatoryProperties(
            "GrasGolfklapGeslotenZodeAlleOptiesUit", 0.0, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            3600000, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            3.6, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            2.0 / 3.0, 0.35, 10.0, grassRevetmentWaveImpactLocationDependentInputItem2->GetWaveAngleImpact());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            1.0, -0.000009722, 0.25, grassRevetmentWaveImpactLocationDependentInputItem2->GetTimeLine());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            0.0, *grassRevetmentWaveImpactLocationDependentInputItem2);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            0.5, *grassRevetmentWaveImpactLocationDependentInputItem2);

        const auto* grassRevetmentWaveImpactLocationDependentInputItem3 = dynamic_cast<GrassRevetmentWaveImpactLocationDependentInput*>(
            &locationDependentInputItems[4].get());
        ASSERT_NE(nullptr, grassRevetmentWaveImpactLocationDependentInputItem3);
        LocationDependentInputAssertHelper::AssertDamageProperties(0.0, 1.0, *grassRevetmentWaveImpactLocationDependentInputItem3);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMandatoryProperties(
            "GrasGolfklapOpenZodeAlleOptiesUit", 0.0, *grassRevetmentWaveImpactLocationDependentInputItem3);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMinimumWaveHeight(
            3600000, *grassRevetmentWaveImpactLocationDependentInputItem3);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertMaximumWaveHeight(
            3.6, *grassRevetmentWaveImpactLocationDependentInputItem3);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertWaveAngleImpact(
            2.0 / 3.0, 0.35, 10.0, grassRevetmentWaveImpactLocationDependentInputItem3->GetWaveAngleImpact());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertTimeLine(
            0.8, -0.00001944, 0.25, grassRevetmentWaveImpactLocationDependentInputItem3->GetTimeLine());
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertUpperLimitLoading(
            0.0, *grassRevetmentWaveImpactLocationDependentInputItem3);
        GrassRevetmentWaveImpactLocationDependentInputAssertHelper::AssertLowerLimitLoading(
            0.5, *grassRevetmentWaveImpactLocationDependentInputItem3);
    }

    TEST_F(JsonInputComposerTest, GivenJsonInputWithInvalidNaturalStoneRevetmentTypeTopLayer_WhenGetCalculationInputFromJson_ThenThrowsJsonConversionException)
    {
        // Given & When
        const auto action = &JsonInputComposerTest::GetCalculationInputFromJsonWithInvalidNaturalStoneRevetmentTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessage<JsonConversionException>(action, "Cannot convert top layer type.");
    }

    TEST_F(JsonInputComposerTest, GivenJsonInputWithInvalidGrassRevetmentTypeTopLayer_WhenGetCalculationInputFromJson_ThenThrowsJsonConversionException)
    {
        // Given & When
        const auto action = &JsonInputComposerTest::GetCalculationInputFromJsonWithInvalidGrassRevetmentTopLayerType;

        // Then
        AssertHelper::AssertThrowsWithMessage<JsonConversionException>(action, "Cannot convert top layer type.");
    }
}
