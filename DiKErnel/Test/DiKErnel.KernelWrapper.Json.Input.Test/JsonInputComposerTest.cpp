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
#include "JsonInputComposer.h"
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
        const auto filePath =
        (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test")
            / "JsonInputComposerTest" / "CompleteInput.json").string();

        // When
        const auto calculationInput = JsonInputComposer::GetCalculationInputFromJson(filePath);

        // Then
        AssertHelper::AssertIsInstanceOf<CalculationInput>(calculationInput.get());

        AssertTimeDependentInputItems(calculationInput->GetTimeDependentInputItems());

        const auto locationDependentInputItems = calculationInput->GetLocationDependentInputItems();
        ASSERT_EQ(2, locationDependentInputItems.size());

        const auto* locationDependentInputItem1 = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &locationDependentInputItems[0].get());
        ASSERT_TRUE(locationDependentInputItem1 != nullptr);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertMandatoryProperties("LocatieZwak", 0, 0.25, 1.65, 0.3, *locationDependentInputItem1);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(5, 1.3, 1.7, 0.9, -0.8, 10, -8, 6, 4.9, locationDependentInputItem1->GetHydraulicLoads());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertUpperLimitLoading(6.1, 3.6, 4.5, locationDependentInputItem1->GetUpperLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertLowerLimitLoading(4.1, 8, 0.5, locationDependentInputItem1->GetLowerLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertDistanceMaximumWaveElevation(0.7, 0.319, locationDependentInputItem1->GetDistanceMaximumWaveElevation());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertNormativeWidthOfWaveImpact(1., 0.01, locationDependentInputItem1->GetNormativeWidthOfWaveImpact());

        const auto* locationDependentInputItem2 = dynamic_cast<NaturalStoneRevetmentLocationDependentInput*>(
            &locationDependentInputItems[1].get());
        ASSERT_TRUE(locationDependentInputItem2 != nullptr);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertMandatoryProperties("LocatieSterk", 0.1, 0.3, 1.65, 0.7, *locationDependentInputItem2);
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertHydraulicLoads(4, 0, 0, -0.9, 0.8, 0, 0, 0.6, 2.9, locationDependentInputItem2->GetHydraulicLoads());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertUpperLimitLoading(0.1, 0.6, 4, locationDependentInputItem2->GetUpperLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertLowerLimitLoading(0.1, 0.2, 4, locationDependentInputItem2->GetLowerLimitLoading());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertDistanceMaximumWaveElevation(0.42, 0.9, locationDependentInputItem2->GetDistanceMaximumWaveElevation());
        NaturalStoneRevetmentLocationDependentInputAssertHelper::AssertNormativeWidthOfWaveImpact(0.96, 0.11, locationDependentInputItem2->GetNormativeWidthOfWaveImpact());
    }
}
