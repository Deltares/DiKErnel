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

#include "DeprecatedCalculator.h"
#include "InputComposer.h"
#include "NaturalStoneRevetment.h"
#include "TestDataPathHelper.h"

namespace DiKErnel::Core::Test
{
    using namespace KernelWrapper::Json;
    using namespace std;

    struct DeprecatedCalculatorTest : testing::Test
    {
        const unique_ptr<InputData> inputData;

        explicit DeprecatedCalculatorTest()
            : inputData(InputComposer::GetDomainParametersFromJson(
                (TestUtil::TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test")
                    / "InputComposerTest"
                    / "testInput.json").string())) { }

        static void AssertCalculationLocationOutput(
            const CalculationLocationOutput& calculationLocationOutput,
            const string& expectedLocationName,
            const vector<double>& expectedDamages)
        {
            ASSERT_EQ(expectedLocationName, calculationLocationOutput.GetName());
            ASSERT_EQ(expectedDamages, calculationLocationOutput.GetRevetmentOutput().GetDamages());
        }
    };

    TEST_F(DeprecatedCalculatorTest, Constructor_WithParameters_PerformsCalculationWithExpectedOutput)
    {
        // Setup
        vector<double> expectedDamages;
        expectedDamages.push_back(1.132388020800255);
        expectedDamages.push_back(0.48530915177153788);

        // Call
        DeprecatedCalculator calculator(*inputData, FunctionLibrary::NaturalStoneRevetment::CalculateDamage);

        calculator.WaitForCompletion();

        // Assert
        ASSERT_EQ(100, calculator.GetProgress());
        ASSERT_TRUE(calculator.IsFinished());
        ASSERT_FALSE(calculator.IsCancelled());

        const auto outputData = calculator.GetOutputData();
        const auto& calculationLocationsOutput = outputData->GetCalculationLocationsOutput();
        ASSERT_EQ(2, calculationLocationsOutput.size());
        AssertCalculationLocationOutput(calculationLocationsOutput[0].get(), "LocatieZwak", expectedDamages);
        AssertCalculationLocationOutput(calculationLocationsOutput[1].get(), "LocatieSterk", expectedDamages);
    }

    TEST_F(DeprecatedCalculatorTest, GivenCalculatorWithRunningCalculation_WhenCancelCalled_ThenCalculationCancelled)
    {
        // Given
        DeprecatedCalculator calculator(*inputData, FunctionLibrary::NaturalStoneRevetment::CalculateDamage);

        // When
        calculator.Cancel();

        calculator.WaitForCompletion();

        // Then
        ASSERT_TRUE(calculator.IsCancelled());
        ASSERT_FALSE(calculator.IsFinished());
        ASSERT_FALSE(calculator.GetProgress() == 100);
    }

    TEST_F(DeprecatedCalculatorTest, GivenCalculatorWithFinishedCalculation_WhenCancelCalled_ThenCalculationNotCancelled)
    {
        // Given
        DeprecatedCalculator calculator(*inputData, FunctionLibrary::NaturalStoneRevetment::CalculateDamage);

        calculator.WaitForCompletion();

        // When
        calculator.Cancel();

        // Then
        ASSERT_FALSE(calculator.IsCancelled());
        ASSERT_TRUE(calculator.IsFinished());
        ASSERT_TRUE(calculator.GetProgress() == 100);
    }

    TEST_F(DeprecatedCalculatorTest, GivenCalculatorWithRunningCalculation_WhenGettingOutputData_ThenOutputDataEmpty)
    {
        // Given
        DeprecatedCalculator calculator(*inputData, FunctionLibrary::NaturalStoneRevetment::CalculateDamage);

        // When
        const auto outputData = calculator.GetOutputData();

        calculator.WaitForCompletion();

        // Then
        ASSERT_EQ(0, outputData->GetCalculationLocationsOutput().size());
    }

    TEST_F(DeprecatedCalculatorTest, GivenCalculatorWithCancelledCalculation_WhenGettingOutputData_ThenOutputDataEmpty)
    {
        // Given
        DeprecatedCalculator calculator(*inputData, FunctionLibrary::NaturalStoneRevetment::CalculateDamage);

        calculator.Cancel();

        calculator.WaitForCompletion();

        // When
        const auto outputData = calculator.GetOutputData();

        // Then
        ASSERT_EQ(0, outputData->GetCalculationLocationsOutput().size());
    }
}
