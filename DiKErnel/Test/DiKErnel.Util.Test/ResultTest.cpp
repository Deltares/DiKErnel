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

    TEST(ResultTest, Constructor_ExpectedValues)
    {
        // Setup
        const int resultNumber = 45;
        const auto message = "Test message";
        const auto eventType = EventType::Error;
        auto event = make_unique<Event>(message, eventType);
        auto events = vector<unique_ptr<Event>>();
        events.push_back(move(event));

        // Call
        const Result result(make_unique<int>(resultNumber), move(events));

        // Assert
        ASSERT_EQ(resultNumber, *result.GetResult());
        ASSERT_EQ(1, result.GetEvents().size());
        const auto eventResult = result.GetEvents()[0].get();
        ASSERT_EQ(message, eventResult.GetMessage());
        ASSERT_EQ(eventType, eventResult.GetEventType());
    }
}
