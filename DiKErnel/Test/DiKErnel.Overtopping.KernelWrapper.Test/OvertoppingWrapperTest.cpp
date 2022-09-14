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
#include "Input.h"
#include "Load.h"
#include "OvertoppingWrapper.h"

namespace DiKErnel::Overtopping::KernelWrapper::Test
{
    TEST(OvertoppingWrapperTest, DISABLED_TestOvertoppingValidation)
    {
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

        Input input{
            2.3,
            4.3,
            1.0,
            0.92,
            1,
            1,
            1.0,
            0.5
        };

        const auto success = OvertoppingWrapper::Validate(geometry, input, dikeHeight);

        ASSERT_FALSE(success);
    }

    TEST(OverToppingWrapperTest, DISABLED_TestOvertoppingValidationMultiple)
    {
        const double dikeHeight = 9.1;
        Input input
        {
            2.3,
            4.3,
            1.0,
            -0.92,
            1,
            1,
            1.0,
            0.5
        };

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

        const auto success = OvertoppingWrapper::Validate(geometry, input, dikeHeight);

        ASSERT_FALSE(success);
    }

    TEST(OverToppingWrapperTest, DISABLED_TestOvertopping)
    {
        const double dikeHeight = 9.1;
        const double dikeNormal = 60.0;

        Input input
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

        const auto z2 = OvertoppingWrapper::Calculate2P(loads, geometry, input, dikeHeight);
        ASSERT_EQ(1, z2);
    }
}
