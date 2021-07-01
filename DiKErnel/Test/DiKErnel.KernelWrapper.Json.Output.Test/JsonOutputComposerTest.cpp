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

#include "AssertHelper.h"
#include "FileAssert.h"
#include "ICalculationInputMock.h"
#include "ILocationDependentInputMock.h"
#include "ITimeDependentInputMock.h"
#include "JsonOutputComposer.h"
#include "TestDataPathHelper.h"
#include "TimeDependentOutputMock.h"

namespace DiKErnel::KernelWrapper::Json::Output::Test
{
    using namespace Core;
    using namespace Core::TestUtil;
    using namespace DiKErnel::TestUtil;
    using namespace std;
    using namespace testing;

    struct JsonOutputComposerTest : Test
    {
        const string _actualOutputFilePath = (filesystem::temp_directory_path() / "actualOutput.json").string();

        vector<unique_ptr<ILocationDependentInput>> _locationDependentInputItems = vector<unique_ptr<ILocationDependentInput>>();
        vector<unique_ptr<ITimeDependentInput>> _timeDependentInputItems = vector<unique_ptr<ITimeDependentInput>>();

        vector<reference_wrapper<ILocationDependentInput>> _locationDependentInputItemReferences
                = vector<reference_wrapper<ILocationDependentInput>>();
        vector<reference_wrapper<ITimeDependentInput>> _timeDependentInputItemReferences = vector<reference_wrapper<ITimeDependentInput>>();

        explicit JsonOutputComposerTest()
        {
            InitializeLocationDependentInputItems();
            InitializeTimeDependentInputItems();
        }

        void InitializeLocationDependentInputItems()
        {
            auto locationDependentInput1 = make_unique<NiceMock<ILocationDependentInputMock>>();
            auto locationDependentInput2 = make_unique<NiceMock<ILocationDependentInputMock>>();

            ON_CALL(*locationDependentInput1, GetName).WillByDefault(Return("testName1"));
            ON_CALL(*locationDependentInput2, GetName).WillByDefault(Return("testName2"));

            ON_CALL(*locationDependentInput1, GetInitialDamage).WillByDefault(Return(0));
            ON_CALL(*locationDependentInput2, GetInitialDamage).WillByDefault(Return(0.05));

            ON_CALL(*locationDependentInput1, GetFailureNumber).WillByDefault(Return(0.95));
            ON_CALL(*locationDependentInput2, GetFailureNumber).WillByDefault(Return(1));

            _locationDependentInputItems.emplace_back(move(locationDependentInput1));
            _locationDependentInputItems.emplace_back(move(locationDependentInput2));

            for (const auto& locationDependentInput : _locationDependentInputItems)
            {
                _locationDependentInputItemReferences.emplace_back(*locationDependentInput);
            }
        }

        void InitializeTimeDependentInputItems()
        {
            auto timeDependentInput1 = make_unique<NiceMock<ITimeDependentInputMock>>();
            auto timeDependentInput2 = make_unique<NiceMock<ITimeDependentInputMock>>();

            ON_CALL(*timeDependentInput1, GetBeginTime).WillByDefault(Return(0));
            ON_CALL(*timeDependentInput1, GetEndTime).WillByDefault(Return(10));
            ON_CALL(*timeDependentInput2, GetBeginTime).WillByDefault(Return(10));
            ON_CALL(*timeDependentInput2, GetEndTime).WillByDefault(Return(100));

            _timeDependentInputItems.emplace_back(move(timeDependentInput1));
            _timeDependentInputItems.emplace_back(move(timeDependentInput2));

            for (const auto& timeDependentInput : _timeDependentInputItems)
            {
                _timeDependentInputItemReferences.emplace_back(*timeDependentInput);
            }
        }

        void PerformTest(
            const string& filename,
            const JsonOutputType outputType)
        {
            // Setup
            const auto expectedOutputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Output.Test")
                / "JsonOutputComposerTest" / filename).string();

            auto location1TimeDependentOutputItems = vector<unique_ptr<TimeDependentOutput>>();
            location1TimeDependentOutputItems.push_back(make_unique<TimeDependentOutputMock>(0, 0.15, nullptr));
            location1TimeDependentOutputItems.push_back(make_unique<TimeDependentOutputMock>(0, 0.253, make_unique<int>(60)));

            auto location2TimeDependentOutputItems = vector<unique_ptr<TimeDependentOutput>>();
            location2TimeDependentOutputItems.push_back(make_unique<TimeDependentOutputMock>(0, 0.28, nullptr));
            location2TimeDependentOutputItems.push_back(make_unique<TimeDependentOutputMock>(0, 0.512, nullptr));

            vector<unique_ptr<LocationDependentOutput>> locations;
            locations.push_back(make_unique<LocationDependentOutput>(move(location1TimeDependentOutputItems)));
            locations.push_back(make_unique<LocationDependentOutput>(move(location2TimeDependentOutputItems)));

            const CalculationOutput calculationOutput(move(locations));

            const NiceMock<ICalculationInputMock> calculationInput;
            ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(_locationDependentInputItemReferences));
            ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(_timeDependentInputItemReferences));

            // Call
            JsonOutputComposer::WriteCalculationOutputToJson(_actualOutputFilePath, calculationOutput, calculationInput, outputType);

            // Assert
            FileAssert::AssertFileContents(expectedOutputFilePath, _actualOutputFilePath);
        }

        static void WriteCalculationOutputToJsonWithNotSupportedLocationData()
        {
            // Setup
            auto location1TimeDependentOutputItems = vector<unique_ptr<TimeDependentOutput>>();
            location1TimeDependentOutputItems.push_back(make_unique<TimeDependentOutputMock>(0, 0.15, nullptr));

            vector<unique_ptr<LocationDependentOutput>> locations;
            locations.push_back(make_unique<LocationDependentOutput>(move(location1TimeDependentOutputItems)));

            const CalculationOutput calculationOutput(move(locations));

            auto locationDependentInputItems = vector<unique_ptr<ILocationDependentInput>>();
            auto timeDependentInputItems = vector<unique_ptr<ITimeDependentInput>>();

            auto locationDependentInputItemReferences = vector<reference_wrapper<ILocationDependentInput>>();
            auto timeDependentInputItemReferences = vector<reference_wrapper<ITimeDependentInput>>();

            auto locationDependentInput1 = make_unique<NiceMock<ILocationDependentInputMock>>();

            locationDependentInputItems.emplace_back(move(locationDependentInput1));

            for (const auto& locationDependentInput : locationDependentInputItems)
            {
                locationDependentInputItemReferences.emplace_back(*locationDependentInput);
            }

            const NiceMock<ICalculationInputMock> calculationInput;
            ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(locationDependentInputItemReferences));
            ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(timeDependentInputItemReferences));

            // Call
            JsonOutputComposer::WriteCalculationOutputToJson("", calculationOutput, calculationInput, JsonOutputType::Physics);
        }

        static void WriteCalculationOutputToJsonWithInvalidJsonOutputType()
        {
            auto locationDependentInputItemReferences = vector<reference_wrapper<ILocationDependentInput>>();
            auto timeDependentInputItemReferences = vector<reference_wrapper<ITimeDependentInput>>();

            const NiceMock<ICalculationInputMock> calculationInput;
            ON_CALL(calculationInput, GetLocationDependentInputItems).WillByDefault(ReturnRef(locationDependentInputItemReferences));
            ON_CALL(calculationInput, GetTimeDependentInputItems).WillByDefault(ReturnRef(timeDependentInputItemReferences));

            const CalculationOutput calculationOutput((vector<unique_ptr<LocationDependentOutput>>()));

            JsonOutputComposer::WriteCalculationOutputToJson("", calculationOutput, calculationInput, static_cast<JsonOutputType>(99));
        }

        ~JsonOutputComposerTest() override
        {
            remove(_actualOutputFilePath.c_str());
        }
    };

    TEST_F(JsonOutputComposerTest, WriteCalculationOutputToJson_InvalidJsonOutputType_ThrowsJsonConversionException)
    {
        // Setup & Call
        const auto action = &JsonOutputComposerTest::WriteCalculationOutputToJsonWithInvalidJsonOutputType;

        // Assert
        AssertHelper::AssertThrowsWithMessage<JsonConversionException>(action, "Invalid JsonOutputType.");
    }

    TEST_F(JsonOutputComposerTest, WriteCalculationOutputToJson_JsonOutputTypeFailure_WritesExpectedValues)
    {
        PerformTest("ExpectedFailureOutput.json", JsonOutputType::Failure);
    }

    TEST_F(JsonOutputComposerTest, WriteCalculationOutputToJson_JsonOutputTypeDamage_WritesExpectedValues)
    {
        PerformTest("ExpectedDamageOutput.json", JsonOutputType::Damage);
    }

    TEST_F(JsonOutputComposerTest, WriteCalculationOutputToJson_JsonOutputTypePhysicsAndLocationDataNotSupported_ThrowsJsonConversionException)
    {
        // Setup & Call
        const auto action = &JsonOutputComposerTest::WriteCalculationOutputToJsonWithNotSupportedLocationData;

        // Assert
        AssertHelper::AssertThrowsWithMessage<JsonConversionException>(action, "Invalid revetment type.");
    }
}
