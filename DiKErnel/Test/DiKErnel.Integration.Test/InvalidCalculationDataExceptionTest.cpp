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
#include "InvalidCalculationDataException.h"

namespace DiKErnel::Integration::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(InvalidCalculationDataExceptionTest, Constructor_WithMessage_ExpectedValues)
    {
        // Setup
        const string message = "Test message";

        // Call
        const InvalidCalculationDataException actualException(message);

        // Assert
        AssertHelper::AssertIsInstanceOf<exception>(&actualException);
        ASSERT_TRUE(message == actualException.what());
    }
}
