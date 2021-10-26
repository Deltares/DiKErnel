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

#include "ICalculationInputMock.h"
#include "ILocationDependentInputMock.h"
#include "IProfileDataMock.h"
#include "ITimeDependentInputMock.h"
#include "Validator.h"

namespace DiKErnel::Core::Test
{
    using namespace std;
    using namespace testing;
    using namespace TestUtil;
    using namespace Util;

    TEST(ValidatorTest, Validate_ValidData_ReturnExpectedResult)
    {
        // Setup
        NiceMock<IProfileDataMock> profileData;
        auto locationDependentInput = make_unique<NiceMock<ILocationDependentInputMock>>();
        ON_CALL(*locationDependentInput, Validate).WillByDefault(Return(true));

        auto locationDependentInputItemReferences = vector<reference_wrapper<ILocationDependentInput>>();
        locationDependentInputItemReferences.emplace_back(*locationDependentInput);

        auto timeDependentInput = make_unique<NiceMock<ITimeDependentInputMock>>();
        ON_CALL(*timeDependentInput, Validate).WillByDefault(Return(true));

        auto timeDependentInputItemReferences = vector<reference_wrapper<ITimeDependentInput>>();
        timeDependentInputItemReferences.emplace_back(*timeDependentInput);

        NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, Validate).WillByDefault(Return(true));
        ON_CALL(calculationInput, GetProfileData).WillByDefault(ReturnRef(profileData));
        ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(locationDependentInputItemReferences));
        ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(timeDependentInputItemReferences));

        // Call
        const auto validationResult = Validator::Validate(calculationInput);

        // Assert
        ASSERT_TRUE(validationResult->GetSuccessful());
        ASSERT_EQ(0, validationResult->GetEvents().size());
    }

    TEST(ValidatorTest, Validate_InvalidCalculationInput_ReturnExpectedResult)
    {
        // Setup
        NiceMock<IProfileDataMock> profileData;
        auto locationDependentInput = make_unique<NiceMock<ILocationDependentInputMock>>();
        ON_CALL(*locationDependentInput, Validate).WillByDefault(Return(true));

        auto locationDependentInputItemReferences = vector<reference_wrapper<ILocationDependentInput>>();
        locationDependentInputItemReferences.emplace_back(*locationDependentInput);

        auto timeDependentInput = make_unique<NiceMock<ITimeDependentInputMock>>();
        ON_CALL(*timeDependentInput, Validate).WillByDefault(Return(true));

        auto timeDependentInputItemReferences = vector<reference_wrapper<ITimeDependentInput>>();
        timeDependentInputItemReferences.emplace_back(*timeDependentInput);

        NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, Validate).WillByDefault(Return(false));
        ON_CALL(calculationInput, GetProfileData).WillByDefault(ReturnRef(profileData));
        ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(locationDependentInputItemReferences));
        ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(timeDependentInputItemReferences));

        // Call
        const auto validationResult = Validator::Validate(calculationInput);

        // Assert
        ASSERT_FALSE(validationResult->GetSuccessful());
        ASSERT_EQ(0, validationResult->GetEvents().size());
    }

    TEST(ValidatorTest, Validate_InvalidLocationDependentInputItem_ReturnExpectedResult)
    {
        // Setup
        NiceMock<IProfileDataMock> profileData;
        auto locationDependentInput = make_unique<NiceMock<ILocationDependentInputMock>>();
        ON_CALL(*locationDependentInput, Validate).WillByDefault(Return(false));

        auto locationDependentInputItemReferences = vector<reference_wrapper<ILocationDependentInput>>();
        locationDependentInputItemReferences.emplace_back(*locationDependentInput);

        auto timeDependentInput = make_unique<NiceMock<ITimeDependentInputMock>>();
        ON_CALL(*timeDependentInput, Validate).WillByDefault(Return(true));

        auto timeDependentInputItemReferences = vector<reference_wrapper<ITimeDependentInput>>();
        timeDependentInputItemReferences.emplace_back(*timeDependentInput);

        NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, Validate).WillByDefault(Return(true));
        ON_CALL(calculationInput, GetProfileData).WillByDefault(ReturnRef(profileData));
        ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(locationDependentInputItemReferences));
        ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(timeDependentInputItemReferences));

        // Call
        const auto validationResult = Validator::Validate(calculationInput);

        // Assert
        ASSERT_FALSE(validationResult->GetSuccessful());
        ASSERT_EQ(0, validationResult->GetEvents().size());
    }

    TEST(ValidatorTest, Validate_InvalidTimeDependentInputItem_ReturnExpectedResult)
    {
        // Setup
        NiceMock<IProfileDataMock> profileData;
        auto locationDependentInput = make_unique<NiceMock<ILocationDependentInputMock>>();
        ON_CALL(*locationDependentInput, Validate).WillByDefault(Return(true));

        auto locationDependentInputItemReferences = vector<reference_wrapper<ILocationDependentInput>>();
        locationDependentInputItemReferences.emplace_back(*locationDependentInput);

        auto timeDependentInput = make_unique<NiceMock<ITimeDependentInputMock>>();
        ON_CALL(*timeDependentInput, Validate).WillByDefault(Return(false));

        auto timeDependentInputItemReferences = vector<reference_wrapper<ITimeDependentInput>>();
        timeDependentInputItemReferences.emplace_back(*timeDependentInput);

        NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, Validate).WillByDefault(Return(true));
        ON_CALL(calculationInput, GetProfileData).WillByDefault(ReturnRef(profileData));
        ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(locationDependentInputItemReferences));
        ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(timeDependentInputItemReferences));

        // Call
        const auto validationResult = Validator::Validate(calculationInput);

        // Assert
        ASSERT_FALSE(validationResult->GetSuccessful());
        ASSERT_EQ(0, validationResult->GetEvents().size());
    }

    TEST(ValidatorTest, Validate_ExceptionOccurred_ReturnExpectedResult)
    {
        // Setup
        const string errorMessage = "Error in validation!";

        NiceMock<IProfileDataMock> profileData;
        auto locationDependentInput = make_unique<NiceMock<ILocationDependentInputMock>>();
        ON_CALL(*locationDependentInput, Validate).WillByDefault(Throw(runtime_error(errorMessage)));

        auto locationDependentInputItemReferences = vector<reference_wrapper<ILocationDependentInput>>();
        locationDependentInputItemReferences.emplace_back(*locationDependentInput);

        auto timeDependentInput = make_unique<NiceMock<ITimeDependentInputMock>>();
        ON_CALL(*timeDependentInput, Validate).WillByDefault(Return(false));

        auto timeDependentInputItemReferences = vector<reference_wrapper<ITimeDependentInput>>();
        timeDependentInputItemReferences.emplace_back(*timeDependentInput);

        NiceMock<ICalculationInputMock> calculationInput;
        ON_CALL(calculationInput, Validate).WillByDefault(Return(true));
        ON_CALL(calculationInput, GetProfileData).WillByDefault(ReturnRef(profileData));
        ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(locationDependentInputItemReferences));
        ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(timeDependentInputItemReferences));

        // Call
        const auto validationResult = Validator::Validate(calculationInput);

        // Assert
        ASSERT_FALSE(validationResult->GetSuccessful());
        const auto& events = validationResult->GetEvents();
        ASSERT_EQ(1, events.size());
        const auto& event = events[0].get();
        ASSERT_EQ(EventType::Error, event.GetEventType());
        ASSERT_EQ("An unhandled error occurred while validating the calculation input. See stack trace for more information:\n"
                  + errorMessage, event.GetMessage());
    }
}
