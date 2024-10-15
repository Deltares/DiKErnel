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

#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "Calculator.h"
#include "EventAssertHelper.h"
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
    using namespace Util::TestUtil;

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

    TEST_F(CalculatorTest, GivenCalculator_WhenCalculationPerformedAndNoTimeOfFailure_ThenReturnsResultWithExpectedOutput)
    {
        // Given
        constexpr auto damage = 0.5;

        const NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, GetProfileData).WillByDefault(ReturnRef(*_profileData));
        ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(_locationDependentInputItemReferences));
        ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(_timeDependentInputItemReferences));

        auto* locationDependentInput = dynamic_cast<ILocationDependentInputMock*>(&_locationDependentInputItemReferences.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        locationDependentInput->SetDamage(damage);

        Calculator calculator(calculationInput);

        // When
        calculator.WaitForCompletion();

        // Then
        const auto& result = calculator.GetResult();
        const auto* output = result->GetData();

        const auto& locationDependentOutputItems = output->GetLocationDependentOutputItems();
        ASSERT_EQ(1, locationDependentOutputItems.size());

        const auto& actualDamages = locationDependentOutputItems.at(0).get().GetDamages();
        ASSERT_EQ(_timeDependentInputItemReferences.size(), actualDamages.size());

        for (auto j = 0; j < static_cast<int>(_timeDependentInputItemReferences.size()); ++j)
        {
            ASSERT_DOUBLE_EQ(damage, actualDamages.at(j));
        }

        ASSERT_EQ(nullptr, locationDependentOutputItems.at(0).get().GetTimeOfFailure());
    }

    TEST_F(CalculatorTest, GivenCalculator_WhenCalculationPerformedAndTimeOfFailure_ThenReturnsResultWithExpectedOutput)
    {
        // Given
        constexpr auto damage = 0.5;
        auto timeOfFailure = 20;

        const NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, GetProfileData).WillByDefault(ReturnRef(*_profileData));
        ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(_locationDependentInputItemReferences));
        ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(_timeDependentInputItemReferences));

        auto* locationDependentInput = dynamic_cast<ILocationDependentInputMock*>(&_locationDependentInputItemReferences.at(0).get());
        ASSERT_TRUE(locationDependentInput != nullptr);

        locationDependentInput->SetDamage(damage);
        locationDependentInput->SetTimeOfFailure(&timeOfFailure);

        Calculator calculator(calculationInput);

        // When
        calculator.WaitForCompletion();

        // Then
        const auto& result = calculator.GetResult();
        const auto* output = result->GetData();

        const auto& locationDependentOutputItems = output->GetLocationDependentOutputItems();
        ASSERT_EQ(1, locationDependentOutputItems.size());

        const auto& actualDamages = locationDependentOutputItems.at(0).get().GetDamages();
        ASSERT_EQ(_timeDependentInputItemReferences.size(), actualDamages.size());

        for (auto j = 0; j < static_cast<int>(_timeDependentInputItemReferences.size()); ++j)
        {
            ASSERT_DOUBLE_EQ(damage, actualDamages.at(j));
        }

        ASSERT_EQ(timeOfFailure, *locationDependentOutputItems.at(0).get().GetTimeOfFailure());
    }

    TEST_F(CalculatorTest, GivenCalculatorWithRunningCalculation_WhenGetResult_ThenReturnsNullPtr)
    {
        // Given
        const NiceMock<ICalculationInputMock> calculationInput;
        EXPECT_CALL(calculationInput, GetProfileData).WillRepeatedly(ReturnRef(*_profileData));
        EXPECT_CALL(calculationInput, GetLocationDependentInputItems).WillRepeatedly(ReturnRef(_locationDependentInputItemReferences));
        EXPECT_CALL(calculationInput, GetTimeDependentInputItems).WillRepeatedly(ReturnRef(_timeDependentInputItemReferences));

        Calculator calculator(calculationInput);

        // When
        const auto& result = calculator.GetResult();

        // Then
        ASSERT_EQ(nullptr, result);

        calculator.WaitForCompletion();
    }

    TEST_F(CalculatorTest, GivenCalculatorWithExceptionDuringCalculation_WhenGetResult_ThenReturnsResultWithSuccessfulFalseAndEvent)
    {
        // Given
        const auto locationDependentInputMock = make_unique<NiceMock<ILocationDependentInputMock>>();
        locationDependentInputMock->SetThrowExceptionOnCalculate(true);

        auto locationDependentInputItemReferences = vector<reference_wrapper<ILocationDependentInput>>();
        locationDependentInputItemReferences.emplace_back(*locationDependentInputMock);

        const NiceMock<ICalculationInputMock> calculationInput;
        EXPECT_CALL(calculationInput, GetProfileData).WillRepeatedly(ReturnRef(*_profileData));
        EXPECT_CALL(calculationInput, GetLocationDependentInputItems).WillRepeatedly(ReturnRef(locationDependentInputItemReferences));
        EXPECT_CALL(calculationInput, GetTimeDependentInputItems).WillRepeatedly(ReturnRef(_timeDependentInputItemReferences));

        Calculator calculator(calculationInput);
        calculator.WaitForCompletion();

        // When
        const auto& result = calculator.GetResult();

        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(
            EventType::Error,
            "An unhandled error occurred while performing the calculation. See stack trace for more information:\nException message",
            events.at(0).get());
    }
}
