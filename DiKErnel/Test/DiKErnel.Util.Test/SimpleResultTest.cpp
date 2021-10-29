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
#include "SimpleResult.h"

namespace DiKErnel::Util::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(SimpleResultTest, Constructor_ExpectedValues)
    {
        // Setup
        constexpr auto message = "Test message";
        constexpr auto eventType = EventType::Error;

        auto events = vector<unique_ptr<Event>>();
        events.emplace_back(make_unique<Event>(message, eventType));

        // Call
        const SimpleResult result(true, move(events));

        // Assert
        ASSERT_TRUE(result.GetSuccessful());

        ASSERT_EQ(1, result.GetEvents().size());
        EventAssertHelper::AssertEvent(eventType, message, result.GetEvents().at(0).get());
    }
}
