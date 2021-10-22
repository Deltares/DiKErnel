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
#include "IProfileDataMock.h"
#include "ITimeDependentInputMock.h"

namespace DiKErnel::Core::Test
{
    using namespace std;
    using namespace testing;
    using namespace TestUtil;
    using namespace Util;

    struct CalculatorTest : Test
    {
        unique_ptr<IProfileData> _profileData = make_unique<IProfileDataMock>();
        vector<unique_ptr<ILocationDependentInput>> _locationDependentInputItems = vector<unique_ptr<ILocationDependentInput>>();
        vector<unique_ptr<ITimeDependentInput>> _timeDependentInputItems = vector<unique_ptr<ITimeDependentInput>>();
        vector<reference_wrapper<ILocationDependentInput>> _locationDependentInputItemReferences =
                vector<reference_wrapper<ILocationDependentInput>>();
        vector<reference_wrapper<ITimeDependentInput>> _timeDependentInputItemReferences = vector<reference_wrapper<ITimeDependentInput>>();

        explicit CalculatorTest()
        {
            _locationDependentInputItems.push_back(make_unique<NiceMock<ILocationDependentInputMock>>());

            _timeDependentInputItems.push_back(make_unique<ITimeDependentInputMock>());
            _timeDependentInputItems.push_back(make_unique<ITimeDependentInputMock>());
            _timeDependentInputItems.push_back(make_unique<ITimeDependentInputMock>());

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
        NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, GetProfileData).WillByDefault(ReturnRef(*_profileData));
        ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(_locationDependentInputItemReferences));
        ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(_timeDependentInputItemReferences));

        Calculator calculator(calculationInput);

        // When
        calculator.WaitForCompletion();

        // Then
        ASSERT_EQ(100, calculator.GetProgress());
        ASSERT_TRUE(calculator.IsFinished());
        ASSERT_FALSE(calculator.IsCancelled());
    }

    TEST_F(CalculatorTest, GivenCalculator_WhenCalculationPerformedAndNoTimeOfFailure_ThenResultWithExpectedOutput)
    {
        // Given
        const auto damage = 0.5;

        NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, GetProfileData).WillByDefault(ReturnRef(*_profileData));
        ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(_locationDependentInputItemReferences));
        ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(_timeDependentInputItemReferences));

        auto* locationDependentInput = dynamic_cast<ILocationDependentInputMock*>(&_locationDependentInputItemReferences[0].get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        locationDependentInput->SetDamage(damage);

        Calculator calculator(calculationInput);

        // When
        calculator.WaitForCompletion();

        // Then
        const auto calculatorResult = calculator.GetCalculationOutput();
        const auto* output = calculatorResult->GetResult();

        const auto& locationDependentOutputItems = output->GetLocationDependentOutputItems();
        ASSERT_EQ(1, locationDependentOutputItems.size());

        const auto& actualDamages = locationDependentOutputItems[0].get().GetDamages();
        ASSERT_EQ(_timeDependentInputItemReferences.size(), actualDamages.size());

        for (auto j = 0; j < static_cast<int>(_timeDependentInputItemReferences.size()); ++j)
        {
            ASSERT_DOUBLE_EQ(damage, actualDamages[j]);
        }

        ASSERT_EQ(nullptr, locationDependentOutputItems[0].get().GetTimeOfFailure());
    }

    TEST_F(CalculatorTest, GivenCalculator_WhenCalculationPerformedAndTimeOfFailure_ThenResultWithExpectedOutput)
    {
        // Given
        const auto damage = 0.5;
        auto timeOfFailure = 20;

        NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, GetProfileData).WillByDefault(ReturnRef(*_profileData));
        ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(_locationDependentInputItemReferences));
        ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(_timeDependentInputItemReferences));

        auto* locationDependentInput = dynamic_cast<ILocationDependentInputMock*>(&_locationDependentInputItemReferences[0].get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        locationDependentInput->SetDamage(damage);
        locationDependentInput->SetTimeOfFailure(&timeOfFailure);

        Calculator calculator(calculationInput);

        // When
        calculator.WaitForCompletion();

        // Then
        const auto calculatorResult = calculator.GetCalculationOutput();
        const auto* output = calculatorResult->GetResult();

        const auto& locationDependentOutputItems = output->GetLocationDependentOutputItems();
        ASSERT_EQ(1, locationDependentOutputItems.size());

        const auto& actualDamages = locationDependentOutputItems[0].get().GetDamages();
        ASSERT_EQ(_timeDependentInputItemReferences.size(), actualDamages.size());

        for (auto j = 0; j < static_cast<int>(_timeDependentInputItemReferences.size()); ++j)
        {
            ASSERT_DOUBLE_EQ(damage, actualDamages[j]);
        }

        ASSERT_EQ(timeOfFailure, *locationDependentOutputItems[0].get().GetTimeOfFailure());
    }

    TEST_F(CalculatorTest, GivenCalculatorWithRunningCalculation_WhenCancelCalled_ThenCalculationCancelled)
    {
        // Given
        NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, GetProfileData).WillByDefault(ReturnRef(*_profileData));
        ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(_locationDependentInputItemReferences));
        ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(_timeDependentInputItemReferences));

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
        EXPECT_CALL(calculationInput, GetProfileData).WillRepeatedly(ReturnRef(*_profileData));
        EXPECT_CALL(calculationInput, GetLocationDependentInputItems).WillRepeatedly(ReturnRef(_locationDependentInputItemReferences));
        EXPECT_CALL(calculationInput, GetTimeDependentInputItems).WillRepeatedly(ReturnRef(_timeDependentInputItemReferences));

        Calculator calculator(calculationInput);
        calculator.WaitForCompletion();

        // When
        calculator.Cancel();

        // Then
        ASSERT_FALSE(calculator.IsCancelled());
        ASSERT_TRUE(calculator.IsFinished());
        ASSERT_EQ(100, calculator.GetProgress());
    }

    TEST_F(CalculatorTest, GivenCalculatorWithUnfinishedCalculation_WhenGetCalculationOutput_ThenReturnResultWithNullPtr)
    {
        // Given
        NiceMock<ICalculationInputMock> calculationInput;
        EXPECT_CALL(calculationInput, GetProfileData).WillRepeatedly(ReturnRef(*_profileData));
        EXPECT_CALL(calculationInput, GetLocationDependentInputItems).WillRepeatedly(ReturnRef(_locationDependentInputItemReferences));
        EXPECT_CALL(calculationInput, GetTimeDependentInputItems).WillRepeatedly(ReturnRef(_timeDependentInputItemReferences));

        Calculator calculator(calculationInput);
        calculator.Cancel();
        calculator.WaitForCompletion();

        // When
        const auto calculatorResult = calculator.GetCalculationOutput();

        // Then
        const auto* output = calculatorResult->GetResult();
        ASSERT_EQ(nullptr, output);
    }

    TEST_F(CalculatorTest, GivenCalculatorWithExceptionDuringCalculation_WhenGetCalculationOutput_ThenReturnResultWithNullPtrAndEvent)
    {
        // Given
        const auto locationDependentInputMock = make_unique<NiceMock<ILocationDependentInputMock>>();
        locationDependentInputMock->SetThrowExceptionOnCalculate(true);

        auto locationDependentInputItemReferences = vector<reference_wrapper<ILocationDependentInput>>();
        locationDependentInputItemReferences.emplace_back(*locationDependentInputMock);

        NiceMock<ICalculationInputMock> calculationInput;
        EXPECT_CALL(calculationInput, GetProfileData).WillRepeatedly(ReturnRef(*_profileData));
        EXPECT_CALL(calculationInput, GetLocationDependentInputItems).WillRepeatedly(ReturnRef(locationDependentInputItemReferences));
        EXPECT_CALL(calculationInput, GetTimeDependentInputItems).WillRepeatedly(ReturnRef(_timeDependentInputItemReferences));

        Calculator calculator(calculationInput);
        calculator.WaitForCompletion();

        // When
        const auto calculatorResult = calculator.GetCalculationOutput();

        // Then
        const auto* output = calculatorResult->GetResult();
        ASSERT_EQ(nullptr, output);

        const auto& events = calculatorResult->GetEvents();
        ASSERT_EQ(1, events.size());
        const auto event = events[0].get();
        ASSERT_EQ(EventType::Error, event.GetEventType());
        ASSERT_EQ("An unhandled error occurred while performing the calculation. See stack trace for more information:\nException message",
                  event.GetMessage());
    }
}
