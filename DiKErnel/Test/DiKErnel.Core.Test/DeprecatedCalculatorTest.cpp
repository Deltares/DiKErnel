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
#include "DeprecatedCalculator.h"
#include "InputComposer.h"
#include "NaturalStoneRevetment.h"
#include "TestDataPathHelper.h"

namespace DiKErnel::Core::Test
{
    using namespace KernelWrapper::Json;
    using namespace std;
    using namespace TestUtil;

    struct DeprecatedCalculatorTest : testing::Test
    {
        const unique_ptr<InputData> _inputData;

        explicit DeprecatedCalculatorTest()
            : _inputData(InputComposer::GetDomainParametersFromJson(
                (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test")
                    / "InputComposerTest"
                    / "inputWithAllParameters.json").string())) { }

        static void AssertCalculationLocationOutput(
            const CalculationLocationOutput& calculationLocationOutput,
            const string& expectedLocationName,
            const vector<double>& expectedDamages)
        {
            ASSERT_EQ(expectedLocationName, calculationLocationOutput.GetName());
            AssertHelper::AssertAreEqual(expectedDamages, calculationLocationOutput.GetRevetmentOutput().GetDamages());
        }
    };

    TEST_F(DeprecatedCalculatorTest, Constructor_WithParameters_PerformsCalculationWithExpectedOutput)
    {
        // Call
        DeprecatedCalculator calculator(*_inputData, FunctionLibrary::NaturalStoneRevetment::CalculateDamage);

        calculator.WaitForCompletion();

        // Assert
        ASSERT_EQ(100, calculator.GetProgress());
        ASSERT_TRUE(calculator.IsFinished());
        ASSERT_FALSE(calculator.IsCancelled());

        const auto outputData = calculator.GetOutputData();
        const auto& calculationLocationsOutput = outputData->GetCalculationLocationsOutput();
        ASSERT_EQ(2, calculationLocationsOutput.size());

        vector<double> expectedDamagesLocation1;
        expectedDamagesLocation1.push_back(0.0);
        expectedDamagesLocation1.push_back(0.16572043642100434);
        expectedDamagesLocation1.push_back(0.59823757673282019);
        expectedDamagesLocation1.push_back(0.73793020228365425);
        expectedDamagesLocation1.push_back(0.96101463018381816);
        expectedDamagesLocation1.push_back(0.96101937828278594);
        AssertCalculationLocationOutput(calculationLocationsOutput[0].get(), "LocatieZwak", expectedDamagesLocation1);

        vector<double> expectedDamagesLocation2;
        expectedDamagesLocation2.push_back(0.1);
        expectedDamagesLocation2.push_back(0.10156947783811528);
        expectedDamagesLocation2.push_back(0.30210694594684634);
        expectedDamagesLocation2.push_back(0.37265049797655736);
        expectedDamagesLocation2.push_back(0.48530676070597473);
        expectedDamagesLocation2.push_back(0.48530915846781858);
        AssertCalculationLocationOutput(calculationLocationsOutput[1].get(), "LocatieSterk", expectedDamagesLocation2);
    }

    TEST_F(DeprecatedCalculatorTest, GivenCalculatorWithRunningCalculation_WhenCancelCalled_ThenCalculationCancelled)
    {
        // Given
        DeprecatedCalculator calculator(*_inputData, FunctionLibrary::NaturalStoneRevetment::CalculateDamage);

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
        DeprecatedCalculator calculator(*_inputData, FunctionLibrary::NaturalStoneRevetment::CalculateDamage);

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
        DeprecatedCalculator calculator(*_inputData, FunctionLibrary::NaturalStoneRevetment::CalculateDamage);

        // When
        const auto outputData = calculator.GetOutputData();

        calculator.WaitForCompletion();

        // Then
        ASSERT_EQ(0, outputData->GetCalculationLocationsOutput().size());
    }

    TEST_F(DeprecatedCalculatorTest, GivenCalculatorWithCancelledCalculation_WhenGettingOutputData_ThenOutputDataEmpty)
    {
        // Given
        DeprecatedCalculator calculator(*_inputData, FunctionLibrary::NaturalStoneRevetment::CalculateDamage);

        calculator.Cancel();

        calculator.WaitForCompletion();

        // When
        const auto outputData = calculator.GetOutputData();

        // Then
        ASSERT_EQ(0, outputData->GetCalculationLocationsOutput().size());
    }
}
