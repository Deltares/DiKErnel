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

#include "Geometry.h"
#include "OvertoppingAdapter.h"

namespace DiKErnel::External::Overtopping::Test
{
    using namespace std;

    constexpr int NR_OF_MESSAGES = 32;
    constexpr int MESSAGE_SIZE = 255;

    TEST(OvertoppingAdapterTest, Validate_WithInvalidData_SetsExpectedValues)
    {
        // Setup
        constexpr double dikeHeight = 9.1;
        double xCoordinates[] = {
            0,
            10,
            20,
            30,
            40
        };
        double yCoordinates[] = {
            -5,
            0,
            5,
            4,
            0
        };
        double roughnessCoefficients[] = {
            0.5,
            0.5,
            0.5,
            0.5
        };

        Geometry geometry{
            0,
            5,
            xCoordinates,
            yCoordinates,
            roughnessCoefficients
        };

        bool success = true;
        constexpr long nrOfCharacters = NR_OF_MESSAGES * MESSAGE_SIZE;
        const auto messageBuffer = make_unique<string>();
        messageBuffer->reserve(nrOfCharacters);

        // Call
        const auto messages = OvertoppingAdapter::Validate(geometry, dikeHeight, messageBuffer.get(), &success);

        // Assert
        ASSERT_FALSE(messages.empty());
    }

    TEST(OvertoppingAdapterTest, Validate_WithValidData_SetsExpectedValues)
    {
        // Setup
        constexpr double dikeHeight = 9.1;
        double xCoordinates[] = {
            0,
            10,
            20,
            30,
            40
        };
        double yCoordinates[] = {
            -5,
            0,
            5,
            10,
            20
        };
        double roughnessCoefficients[] = {
            0.5,
            0.5,
            0.5,
            0.5
        };

        Geometry geometry{
            0,
            5,
            xCoordinates,
            yCoordinates,
            roughnessCoefficients
        };

        bool success = false;
        constexpr long nrOfCharacters = NR_OF_MESSAGES * MESSAGE_SIZE;
        const auto messageBuffer = make_unique<string>();
        messageBuffer->reserve(nrOfCharacters);

        // Call
        const auto messages = OvertoppingAdapter::Validate(geometry, dikeHeight, messageBuffer.get(), &success);

        // Assert
        ASSERT_TRUE(messages.empty());
    }

    TEST(OvertoppingAdapterTest, CalculateZ2_WithInvalidData_ReturnsExpectedValue)
    {
        // Setup
        const vector xValues =
        {
            0,
            24.0
        };
        const vector zValues =
        {
            -3.0,
            3.0
        };
        const vector roughnessCoefficients =
        {
            1.0
        };

        // Call
        const auto z2 = OvertoppingAdapter::CalculateZ2(1e-6, -0.361314622129615, 45, 1.912229230397281e-12, xValues, zValues,
                                                        roughnessCoefficients, 3.7);

        // Assert
        ASSERT_DOUBLE_EQ(0, z2);
    }

    TEST(OvertoppingAdapterTest, CalculateZ2_WithValidData_ReturnsExpectedValue)
    {
        // Setup
        const vector<double> xValues =
        {
            5,
            10,
            15
        };
        const vector<double> zValues =
        {
            5,
            7,
            9
        };
        const vector<double> roughnessCoefficients =
        {
            1,
            1,
            1
        };

        // Call
        const auto z2 = OvertoppingAdapter::CalculateZ2(5.5, 1, 4, 50, xValues, zValues, roughnessCoefficients, 9.1);

        // Assert
        ASSERT_NE(0, z2);
    }
}
