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

#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "Calculator.h"
#include "ICalculationInputMock.h"
#include "ILocationDependentInputMock.h"
#include "ITimeDependentInputMock.h"

namespace DiKErnel::Core::Test
{
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct CalculatorTest : Test
    {
        vector<unique_ptr<ILocationDependentInput>> _locationDependentInputItems = vector<unique_ptr<ILocationDependentInput>>();
        vector<unique_ptr<ITimeDependentInput>> _timeDependentInputItems = vector<unique_ptr<ITimeDependentInput>>();

        vector<reference_wrapper<ILocationDependentInput>> _locationDependentInputItemReferences
                = vector<reference_wrapper<ILocationDependentInput>>();
        vector<reference_wrapper<ITimeDependentInput>> _timeDependentInputItemReferences = vector<reference_wrapper<ITimeDependentInput>>();

        explicit CalculatorTest()
        {
            _locationDependentInputItems.emplace_back(make_unique<NiceMock<ILocationDependentInputMock>>());

            _timeDependentInputItems.emplace_back(make_unique<ITimeDependentInputMock>());
            _timeDependentInputItems.emplace_back(make_unique<ITimeDependentInputMock>());
            _timeDependentInputItems.emplace_back(make_unique<ITimeDependentInputMock>());

            for (const auto& locationDependentInput : _locationDependentInputItems)
            {
                _locationDependentInputItemReferences.emplace_back(*locationDependentInput);
            }

            for (const auto& timeDependentInput : _timeDependentInputItems)
            {
                _timeDependentInputItemReferences.emplace_back(*timeDependentInput);
            }
        }
    };

    TEST_F(CalculatorTest, GivenCalculator_WhenWaitForCompletion_ThenCalculationPerformed)
    {
        // Given
        const auto damage = 0.5;

        NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(_locationDependentInputItemReferences));
        ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(_timeDependentInputItemReferences));
        ON_CALL(calculationInput, GetMaximumWaveAngle).WillByDefault(Return(0));

        const auto* locationDependentInput = dynamic_cast<ILocationDependentInputMock*>(&_locationDependentInputItemReferences[0].get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        ON_CALL(*locationDependentInput, GetInitialDamage).WillByDefault(Return(0.1));
        ON_CALL(*locationDependentInput, Calculate).WillByDefault(Return(damage));

        Calculator calculator(calculationInput);

        // When
        calculator.WaitForCompletion();

        // Then
        ASSERT_EQ(100, calculator.GetProgress());
        ASSERT_TRUE(calculator.IsFinished());
        ASSERT_FALSE(calculator.IsCancelled());

        const auto output = calculator.GetCalculationOutput();

        const auto& locationOutputItems = output->GetLocationOutputItems();
        ASSERT_EQ(1, locationOutputItems.size());

        const auto& actualDamages = locationOutputItems[0].get().GetDamages();
        ASSERT_EQ(_timeDependentInputItemReferences.size(), actualDamages.size());

        for (auto j = 0; j < _timeDependentInputItemReferences.size(); ++j)
        {
            ASSERT_DOUBLE_EQ(damage, actualDamages[j]);
        }

        ASSERT_EQ(nullptr, locationOutputItems[0].get().GetTimeOfFailure());
    }

    TEST_F(CalculatorTest, GivenCalculatorWithRunningCalculation_WhenCancelCalled_ThenCalculationCancelled)
    {
        // Given
        NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(_locationDependentInputItemReferences));
        ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(_timeDependentInputItemReferences));
        ON_CALL(calculationInput, GetMaximumWaveAngle).WillByDefault(Return(0));

        Calculator calculator(calculationInput);

        // When
        calculator.Cancel();
        calculator.WaitForCompletion();

        // Then
        ASSERT_TRUE(calculator.IsCancelled());
        ASSERT_FALSE(calculator.IsFinished());
        ASSERT_NE(100, calculator.GetProgress());
    }

    TEST_F(CalculatorTest, GivenCalculatorWithFinishedCalculation_WhenCancelCalled_ThenCalculationNotCancelled)
    {
        // Given
        NiceMock<ICalculationInputMock> calculationInput;
        EXPECT_CALL(calculationInput, GetLocationDependentInputItems).WillRepeatedly(ReturnRef(_locationDependentInputItemReferences));
        EXPECT_CALL(calculationInput, GetTimeDependentInputItems).WillRepeatedly(ReturnRef(_timeDependentInputItemReferences));
        EXPECT_CALL(calculationInput, GetMaximumWaveAngle).WillRepeatedly(Return(0));

        Calculator calculator(calculationInput);
        calculator.WaitForCompletion();

        // When
        calculator.Cancel();

        // Then
        ASSERT_FALSE(calculator.IsCancelled());
        ASSERT_TRUE(calculator.IsFinished());
        ASSERT_EQ(100, calculator.GetProgress());
    }

    TEST_F(CalculatorTest, GivenCalculatorWithUnfinishedCalculation_WhenGetCalculationOutput_ThenNullPtrReturned)
    {
        // Given
        NiceMock<ICalculationInputMock> calculationInput;
        EXPECT_CALL(calculationInput, GetLocationDependentInputItems).WillRepeatedly(ReturnRef(_locationDependentInputItemReferences));
        EXPECT_CALL(calculationInput, GetTimeDependentInputItems).WillRepeatedly(ReturnRef(_timeDependentInputItemReferences));
        EXPECT_CALL(calculationInput, GetMaximumWaveAngle).WillRepeatedly(Return(0));

        Calculator calculator(calculationInput);
        calculator.Cancel();
        calculator.WaitForCompletion();

        // When
        const auto output = calculator.GetCalculationOutput();

        // Then
        ASSERT_EQ(nullptr, output);
    }
}
