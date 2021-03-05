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
#include "ILocationDependentDataMock.h"
#include "ITimeDependentDataMock.h"

namespace DiKErnel::Core::Test
{
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct CalculatorTest : Test
    {
        vector<unique_ptr<ILocationDependentData>> _locationDependentDataItems = vector<unique_ptr<ILocationDependentData>>();
        vector<unique_ptr<ITimeDependentData>> _timeDependentDataItems = vector<unique_ptr<ITimeDependentData>>();

        vector<reference_wrapper<ILocationDependentData>> _locationDependentDataItemReferences = vector<reference_wrapper<ILocationDependentData>>();
        vector<reference_wrapper<ITimeDependentData>> _timeDependentDataItemReferences = vector<reference_wrapper<ITimeDependentData>>();

        explicit CalculatorTest()
        {
            _locationDependentDataItems.emplace_back(make_unique<NiceMock<ILocationDependentDataMock>>());

            _timeDependentDataItems.emplace_back(make_unique<ITimeDependentDataMock>());
            _timeDependentDataItems.emplace_back(make_unique<ITimeDependentDataMock>());
            _timeDependentDataItems.emplace_back(make_unique<ITimeDependentDataMock>());

            for (const auto& locationDependentData : _locationDependentDataItems)
            {
                _locationDependentDataItemReferences.emplace_back(*locationDependentData);
            }

            for (const auto& timeDependentData : _timeDependentDataItems)
            {
                _timeDependentDataItemReferences.emplace_back(*timeDependentData);
            }
        }
    };

    TEST_F(CalculatorTest, GivenCalculator_WhenWaitForCompletion_ThenCalculationPerformed)
    {
        // Given
        const auto damage = 0.5;

        NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, GetLocationDependentDataItems).WillByDefault(ReturnRef(_locationDependentDataItemReferences));
        ON_CALL(calculationInput, GetTimeDependentDataItems).WillByDefault(ReturnRef(_timeDependentDataItemReferences));
        ON_CALL(calculationInput, GetMaximumWaveAngle).WillByDefault(Return(0));

        auto& location = static_cast<ILocationDependentDataMock&>(_locationDependentDataItemReferences[0].get());

        ON_CALL(location, GetInitialDamage).WillByDefault(Return(0.1));
        ON_CALL(location, Calculate).WillByDefault(Return(damage));

        Calculator calculator(calculationInput);

        // When
        calculator.WaitForCompletion();

        // Then
        ASSERT_EQ(100, calculator.GetProgress());
        ASSERT_TRUE(calculator.IsFinished());
        ASSERT_FALSE(calculator.IsCancelled());

        const auto output = calculator.GetCalculationOutput();
        const auto& locationOutputs = output->GetLocationOutputs();

        ASSERT_EQ(_locationDependentDataItemReferences.size(), locationOutputs.size());

        for (auto i = 0; i < static_cast<int>(_locationDependentDataItemReferences.size()); ++i)
        {
            const auto& actualDamages = locationOutputs[i].get().GetDamages();
            ASSERT_EQ(_timeDependentDataItemReferences.size(), actualDamages.size());

            for (auto j = 0; j < _timeDependentDataItemReferences.size(); ++j)
            {
                ASSERT_EQ(damage, actualDamages[j]);
            }

            ASSERT_EQ(nullptr, locationOutputs[i].get().GetTimeOfFailure());
        }
    }

    TEST_F(CalculatorTest, GivenCalculatorWithRunningCalculation_WhenCancelCalled_ThenCalculationCancelled)
    {
        // Given
        NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, GetLocationDependentDataItems).WillByDefault(ReturnRef(_locationDependentDataItemReferences));
        ON_CALL(calculationInput, GetTimeDependentDataItems).WillByDefault(ReturnRef(_timeDependentDataItemReferences));
        ON_CALL(calculationInput, GetMaximumWaveAngle).WillByDefault(Return(0));

        Calculator calculator(calculationInput);

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
        NiceMock<ICalculationInputMock> calculationInput;
        EXPECT_CALL(calculationInput, GetLocationDependentDataItems).WillRepeatedly(ReturnRef(_locationDependentDataItemReferences));
        EXPECT_CALL(calculationInput, GetTimeDependentDataItems).WillRepeatedly(ReturnRef(_timeDependentDataItemReferences));
        EXPECT_CALL(calculationInput, GetMaximumWaveAngle).WillRepeatedly(Return(0));

        Calculator calculator(calculationInput);
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
        NiceMock<ICalculationInputMock> calculationInput;
        EXPECT_CALL(calculationInput, GetLocationDependentDataItems).WillRepeatedly(ReturnRef(_locationDependentDataItemReferences));
        EXPECT_CALL(calculationInput, GetTimeDependentDataItems).WillRepeatedly(ReturnRef(_timeDependentDataItemReferences));
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
