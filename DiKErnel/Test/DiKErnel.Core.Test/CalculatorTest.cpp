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

#include "CalculationInput.h"
#include "Calculator.h"
#include "TestLocationDependentData.h"

namespace DiKErnel::Core::Test
{
    using namespace std;
    using namespace TestUtil;

    struct CalculatorTest : testing::Test
    {
        unique_ptr<CalculationInput> _calculationInput;

        explicit CalculatorTest()
        {
            vector<unique_ptr<LocationDependentData>> locationDependentDataItems;
            locationDependentDataItems.push_back(make_unique<TestLocationDependentData>(0));
            locationDependentDataItems.push_back(make_unique<TestLocationDependentData>(0.1));
            locationDependentDataItems.push_back(make_unique<TestLocationDependentData>(0.2));

            vector<unique_ptr<TimeDependentData>> timeDependentDataItems;
            timeDependentDataItems.push_back(make_unique<TimeDependentData>(0, 10, 0.3, 0.4, 0.5, 0.6));
            timeDependentDataItems.push_back(make_unique<TimeDependentData>(10, 20, 0.7, 0.8, 0.9, 1.0));
            timeDependentDataItems.push_back(make_unique<TimeDependentData>(20, 30, 1.1, 1.2, 1.3, 1.4));

            _calculationInput = make_unique<CalculationInput>(move(locationDependentDataItems), move(timeDependentDataItems), 0);
        }

        static void AssertDamages(
            const double initialDamage,
            const int numberOfTimes,
            const vector<double>& actualDamages)
        {
            ASSERT_EQ(numberOfTimes, actualDamages.size());

            for (auto i = 0; i < numberOfTimes; ++i)
            {
                ASSERT_EQ(initialDamage + i * 0.5 + 0.5, actualDamages[i]);
            }
        }
    };

    TEST_F(CalculatorTest, GivenCalculator_WhenWaitForCompletion_ThenCalculationPerformed)
    {
        // Given
        Calculator calculator(*_calculationInput);

        // When
        calculator.WaitForCompletion();

        // Then
        ASSERT_EQ(100, calculator.GetProgress());
        ASSERT_TRUE(calculator.IsFinished());
        ASSERT_FALSE(calculator.IsCancelled());

        const auto output = calculator.GetCalculationOutput();
        const auto& locationOutputs = output->GetLocationOutputs();
        const auto& locationInputs = _calculationInput->GetLocationDependentDataItems();
        const auto numberOfTimes = _calculationInput->GetTimeDependentDataItems().size();

        ASSERT_EQ(locationInputs.size(), locationOutputs.size());

        for (auto i = 0; i < static_cast<int>(locationInputs.size()); ++i)
        {
            AssertDamages(locationInputs[i].get().GetInitialDamage(), static_cast<int>(numberOfTimes), locationOutputs[i].get().GetDamages());
            ASSERT_EQ(nullptr, locationOutputs[i].get().GetTimeOfFailure());
        }
    }

    TEST_F(CalculatorTest, GivenCalculatorWithRunningCalculation_WhenCancelCalled_ThenCalculationCancelled)
    {
        // Given
        Calculator calculator(*_calculationInput);

        // When
        calculator.Cancel();
        calculator.WaitForCompletion();

        // Then
        ASSERT_TRUE(calculator.IsCancelled());
        ASSERT_FALSE(calculator.IsFinished());
        ASSERT_FALSE(calculator.GetProgress() == 100);
    }

    TEST_F(CalculatorTest, GivenCalculatorWithFinishedCalculation_WhenCancelCalled_ThenCalculationNotCancelled)
    {
        // Given
        Calculator calculator(*_calculationInput);
        calculator.WaitForCompletion();

        // When
        calculator.Cancel();

        // Then
        ASSERT_FALSE(calculator.IsCancelled());
        ASSERT_TRUE(calculator.IsFinished());
        ASSERT_TRUE(calculator.GetProgress() == 100);
    }

    TEST_F(CalculatorTest, GivenCalculatorWithUnfinishedCalculation_WhenGetCalculationOutput_ThenNullPtrReturned)
    {
        // Given
        Calculator calculator(*_calculationInput);
        calculator.Cancel();
        calculator.WaitForCompletion();

        // When
        const auto output = calculator.GetCalculationOutput();

        // Then
        ASSERT_EQ(nullptr, output);
    }
}
