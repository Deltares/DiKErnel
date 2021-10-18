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
#include "JsonOutputComposer.h"
#include "JsonOutputConversionException.h"
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

            // Call
            JsonOutputComposer::WriteCalculationOutputToJson(_actualOutputFilePath, calculationOutput, outputType);

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

            // Call
            JsonOutputComposer::WriteCalculationOutputToJson("", calculationOutput, JsonOutputType::Physics);
        }

        static void WriteCalculationOutputToJsonWithInvalidJsonOutputType()
        {
            const CalculationOutput calculationOutput((vector<unique_ptr<LocationDependentOutput>>()));

            JsonOutputComposer::WriteCalculationOutputToJson("", calculationOutput, static_cast<JsonOutputType>(99));
        }

        ~JsonOutputComposerTest() override
        {
            remove(_actualOutputFilePath.c_str());
        }
    };

    TEST_F(JsonOutputComposerTest, WriteCalculationOutputToJson_InvalidJsonOutputType_ThrowsJsonOutputConversionException)
    {
        // Setup & Call
        const auto action = &JsonOutputComposerTest::WriteCalculationOutputToJsonWithInvalidJsonOutputType;

        // Assert
        AssertHelper::AssertThrowsWithMessage<JsonOutputConversionException>(action, "Invalid JsonOutputType.");
    }

    TEST_F(JsonOutputComposerTest, WriteCalculationOutputToJson_JsonOutputTypeFailure_WritesExpectedValues)
    {
        PerformTest("ExpectedFailureOutput.json", JsonOutputType::Failure);
    }

    TEST_F(JsonOutputComposerTest, WriteCalculationOutputToJson_JsonOutputTypeDamage_WritesExpectedValues)
    {
        PerformTest("ExpectedDamageOutput.json", JsonOutputType::Damage);
    }

    TEST_F(JsonOutputComposerTest,
           WriteCalculationOutputToJson_JsonOutputTypePhysicsAndLocationDataNotSupported_ThrowsJsonOutputConversionException)
    {
        // Setup & Call
        const auto action = &JsonOutputComposerTest::WriteCalculationOutputToJsonWithNotSupportedLocationData;

        // Assert
        AssertHelper::AssertThrowsWithMessage<JsonOutputConversionException>(action, "Invalid revetment type.");
    }
}
