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

#include "EventAssertHelper.h"
#include "RevetmentCalculationInputBuilder.h"
#include "Validator.h"

namespace DiKErnel::System::Test
{
    using namespace Core;
    using namespace Integration;
    using namespace std;
    using namespace testing;
    using namespace Util::TestUtil;
    using namespace Util;

    TEST(ValidationSystemTest, GivenCalculationInputWithoutTimeStepsAndLocations_WhenValidating_ThenReturnsValidationResult)
    {
        // Given
        RevetmentCalculationInputBuilder builder;
        const auto calculationInput = builder.Build();

        // When
        const auto validationResult = Validator::Validate(*calculationInput);

        // Then
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(ValidationResultType::Failed, *validationResult->GetData());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(2, events.size());
        EventAssertHelper::AssertEvent(EventType::Error, "At least 1 time step must be defined.", events[0]);
        EventAssertHelper::AssertEvent(EventType::Error, "At least 1 location must be defined.", events[1]);
    }
}
