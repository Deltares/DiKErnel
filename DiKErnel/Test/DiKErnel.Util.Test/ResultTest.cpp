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

#include "Result.h"

namespace DiKErnel::Util::Test
{
    using namespace std;

    TEST(ResultTest, Constructor_WithResultSet_ExpectedValues)
    {
        // Setup
        constexpr auto resultNumber = 45;
        constexpr auto message = "Test message";
        constexpr auto eventType = EventType::Error;

        auto events = vector<unique_ptr<Event>>();

        events.push_back(make_unique<Event>(message, eventType));

        // Call
        const Result result(make_unique<int>(resultNumber), move(events));

        // Assert
        ASSERT_EQ(resultNumber, *result.GetResult());

        ASSERT_EQ(1, result.GetEvents().size());

        const auto& eventResult = result.GetEvents()[0].get();
        ASSERT_EQ(message, eventResult.GetMessage());
        ASSERT_EQ(eventType, eventResult.GetEventType());
    }

    TEST(ResultTest, Constructor_WithResultNotSet_ExpectedValues)
    {
        // Setup
        constexpr auto message = "Test message";
        constexpr auto eventType = EventType::Error;

        auto events = vector<unique_ptr<Event>>();

        events.push_back(make_unique<Event>(message, eventType));

        // Call
        const Result<int> result(nullptr, move(events));

        // Assert
        ASSERT_EQ(nullptr, result.GetResult());

        ASSERT_EQ(1, result.GetEvents().size());

        const auto& eventResult = result.GetEvents()[0].get();
        ASSERT_EQ(message, eventResult.GetMessage());
        ASSERT_EQ(eventType, eventResult.GetEventType());
    }
}
