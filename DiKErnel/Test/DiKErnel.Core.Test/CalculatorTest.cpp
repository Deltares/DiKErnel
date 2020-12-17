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

#include "Calculator.h"
#include "InputComposer.h"
#include "NaturalStoneRevetment.h"
#include "TestDataHelper.h"

namespace DiKErnel::Core::Test
{
    struct CalculatorTest : testing::Test
    {
        const std::string filePath =
        (TestUtil::TestDataHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test")
            / "InputComposerTest"
            / "testInput.json").string();
    };

    void CreateCalculation(
        KernelWrapper::Json::InputData*);

    TEST_F(CalculatorTest, Constructor_WithParameters_PerformsCalculation)
    {
        // Setup
        const auto inputData = KernelWrapper::Json::InputComposer::GetDomainParametersFromJson(filePath);

        // Call & Assert
        ASSERT_NO_THROW(CreateCalculation(inputData.get()));
    }

    void CreateCalculation(
        KernelWrapper::Json::InputData* inputData)
    {
        Calculator calculator(inputData, &FunctionLibrary::NaturalStoneRevetment::CalculateDamage);

        calculator.WaitForCompletion();
    }
}
