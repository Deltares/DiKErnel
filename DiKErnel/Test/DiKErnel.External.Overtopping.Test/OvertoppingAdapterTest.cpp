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
#include "ModelFactors.h"
#include "Load.h"
#include "OvertoppingAdapter.h"

namespace DiKErnel::External::Overtopping::Test
{
    using namespace std;

    constexpr int NR_OF_MESSAGES = 32;
    constexpr int MESSAGE_SIZE = 255;

    TEST(OvertoppingAdapterTest, Validate_WithInvalidData_SetsExpectedValues)
    {
        // Setup
        const double dikeHeight = 9.1;
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

        ModelFactors modelFactors{
            2.3,
            4.3,
            1.0,
            0.92,
            1,
            1,
            1.0,
            0.5
        };

        bool success = true;
        constexpr long nrOfCharacters = NR_OF_MESSAGES * MESSAGE_SIZE;
        const auto messageBuffer = make_unique<string>();
        messageBuffer->reserve(nrOfCharacters);

        // Call
        OvertoppingAdapter::Validate(geometry, modelFactors, messageBuffer.get(), &success, dikeHeight);

        // Assert
        ASSERT_FALSE(success);
        ASSERT_FALSE(strlen(messageBuffer->c_str()) == 0);
    }

    TEST(OvertoppingAdapterTest, Validate_WithValidData_SetsExpectedValues)
    {
        // Setup
        const double dikeHeight = 9.1;
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

        ModelFactors modelFactors{
            2.3,
            4.3,
            1.0,
            0.92,
            1,
            1,
            1.0,
            0.5
        };

        bool success = false;
        constexpr long nrOfCharacters = NR_OF_MESSAGES * MESSAGE_SIZE;
        const auto messageBuffer = make_unique<string>();
        messageBuffer->reserve(nrOfCharacters);

        // Call
        OvertoppingAdapter::Validate(geometry, modelFactors, messageBuffer.get(), &success, dikeHeight);

        // Assert
        ASSERT_TRUE(success);
        ASSERT_TRUE(strlen(messageBuffer->c_str()) == 0);
    }

    TEST(OvertoppingAdapterTest, Calculate_WithValidData_SetsExpectedValues)
    {
        // Setup
        const double dikeHeight = 9.1;
        const double dikeNormal = 60.0;

        ModelFactors input
        {
            2.3,
            4.3,
            1.0,
            0.92,
            1,
            1,
            1.0,
            0.5
        };

        const int nrOfPoints = 3;
        double xCoordinates[] = {
            5,
            10,
            15
        };
        double yCoordinates[] = {
            5,
            7,
            9
        };
        double roughnessCoefficients[] = {
            1,
            1,
            1
        };

        Geometry geometry
        {
            dikeNormal,
            nrOfPoints,
            xCoordinates,
            yCoordinates,
            roughnessCoefficients
        };

        Load loads
        {
            5.5,
            1,
            4.0,
            50
        };

        Result result{};

        bool success = false;
        const auto messageBuffer = make_unique<string>();
        messageBuffer->reserve(MESSAGE_SIZE);

        // Call
        OvertoppingAdapter::CalculateQo(loads, geometry, input, &result, messageBuffer.get(), &success, dikeHeight);

        // Assert
        ASSERT_TRUE(success);

        ASSERT_NE(0, result._qo);
        ASSERT_NE(0, result._z2);
        ASSERT_TRUE(strlen(messageBuffer->c_str()) == 0);
    }

    TEST(OvertoppingAdapterTest, Calculate_WithInvalidData_SetsExpectedValues)
    {
        // Setup
        const double dikeHeight = 3.7;
        const double dikeNormal = 0.0;

        ModelFactors modelFactors
        {
            2.3,
            4.3,
            1.0,
            0.92,
            1,
            1,
            1.0,
            0.5
        };

        const int nrOfPoints = 2;
        double xCoordinates[] = {
           0,
            24.0
        };
        double yCoordinates[] = {
           -3.0,
            3.0
        };
        double roughnessCoefficients[] = {
            1
        };

        Geometry geometry
        {
            dikeNormal,
            nrOfPoints,
            xCoordinates,
            yCoordinates,
            roughnessCoefficients
        };

        Load loads
        {
            1e-6,
            -0.361314622129615,
            45,
            1.912229230397281e-12
        };

        Result result{};

        bool success = false;
        const auto messageBuffer = make_unique<string>();
        messageBuffer->reserve(MESSAGE_SIZE);

        // Call
        OvertoppingAdapter::CalculateQo(loads, geometry, modelFactors, &result, messageBuffer.get(), &success, dikeHeight);

        // Assert
        ASSERT_FALSE(success);
        ASSERT_FALSE(strlen(messageBuffer->c_str()) == 0);
    }
}
