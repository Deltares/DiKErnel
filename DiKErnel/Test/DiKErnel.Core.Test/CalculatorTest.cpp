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

    TEST_F(CalculatorTest, Constructor_WithParameters_PerformsCalculation)
    {
        // Setup
        const auto inputData = KernelWrapper::Json::InputComposer::GetDomainParametersFromJson(filePath);

        // Call
        Calculator calculator(*inputData, FunctionLibrary::NaturalStoneRevetment::CalculateDamage);

        // Wait
        calculator.WaitForCompletion();

        // Assert
        ASSERT_EQ(calculator.GetProgress(), 100);
        ASSERT_EQ(calculator.IsFinished(), true);
        ASSERT_EQ(calculator.IsCancelled(), false);

        const auto outputData = calculator.GetOutputData();
        ASSERT_EQ(outputData->GetCalculationLocationsOutput().size(), 2);
    }

    TEST_F(CalculatorTest, GivenCalculator_WhenCancelCalled_ThenCalculationCancelled)
    {
        // Given
        const auto inputData = KernelWrapper::Json::InputComposer::GetDomainParametersFromJson(filePath);

        Calculator calculator(*inputData, FunctionLibrary::NaturalStoneRevetment::CalculateDamage);

        // When
        calculator.Cancel();

        // Wait
        calculator.WaitForCompletion();

        // Then
        ASSERT_EQ(calculator.IsCancelled(), true);
        ASSERT_FALSE(calculator.GetProgress() == 100);
    }
}
