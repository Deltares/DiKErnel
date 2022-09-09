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
#include "OvertoppingWrapper.h"

namespace DiKErnel::Overtopping::KernelWrapper::Test
{
    TEST(OvertoppingWrapperTest, TestOvertoppingValidation)
    {
        const auto xCoords = new double[]{
            0,
            10,
            20,
            30,
            40
        };
        const auto yCoords = new double[]{
            -5,
            0,
            5,
            4,
            0
        };
        const auto roughness = new double[]{
            0.5,
            0.5,
            0.5,
            0.5
        };

        Geometry geometry{
            0,
            5,
            xCoords,
            yCoords,
            roughness
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

        OvertoppingWrapper overtoppingWrapper;

        const auto success = overtoppingWrapper.Validate(geometry, input, 9.1);

        delete[] xCoords, yCoords, roughness;

        ASSERT_FALSE(success);
    }
}
