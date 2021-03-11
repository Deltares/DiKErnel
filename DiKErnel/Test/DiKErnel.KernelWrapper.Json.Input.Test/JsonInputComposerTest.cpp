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
        void AssertTimeDependentDataItems(
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

    TEST_F(JsonInputComposerTest, GivenJsonFileWithAllParamtersSet_WhenGetCalculationInputFromJson_ThenReturnICalculationInputWithExpectedValues)
    {
        // Given
        const auto filePath =
        (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test")
            / "JsonInputComposerTest" / "inputWithAllParameters.json").string();

        // When
        const auto calculationInput = JsonInputComposer::GetCalculationInputFromJson(filePath);

        // Then
        AssertHelper::AssertIsInstanceOf<CalculationInput>(calculationInput.get());
        ASSERT_DOUBLE_EQ(78, calculationInput->GetMaximumWaveAngle());

        AssertTimeDependentDataItems(calculationInput->GetTimeDependentInputItems());
    }
}
