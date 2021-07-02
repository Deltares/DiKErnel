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

#include <fstream>

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "Calculator.h"
#include "FileAssert.h"
#include "JsonInputComposer.h"
#include "JsonOutputComposer.h"
#include "TestDataPathHelper.h"

namespace DiKErnel::KernelWrapper::Json::Integration::Test
{
    using namespace Core;
    using namespace Input;
    using namespace Output;
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct IntegrationTest : Test
    {
        const string _actualOutputFilePath = (filesystem::temp_directory_path() / "actualOutput.json").string();

        static JsonOutputType ConvertProcessType(
            const JsonInputProcessType processType)
        {
            switch (processType)
            {
                case JsonInputProcessType::Failure:
                    return JsonOutputType::Failure;
                case JsonInputProcessType::Damage:
                    return JsonOutputType::Damage;
                case JsonInputProcessType::Physics:
                    return JsonOutputType::Physics;
                default:
                    throw runtime_error("Unsupported processType");
            }
        }

        void PerformTest(
            const string& inputFilePath,
            const string& expectedOutputFilePath) const
        {
            // When
            const auto inputData = JsonInputComposer::GetInputDataFromJson(inputFilePath);
            auto* calculationInput = get<0>(inputData).get();

            Calculator calculator(*calculationInput);
            calculator.WaitForCompletion();

            const auto outputData = calculator.GetCalculationOutput();
            JsonOutputComposer::WriteCalculationOutputToJson(_actualOutputFilePath, *outputData, *calculationInput,
                                                             ConvertProcessType(get<1>(inputData)));

            // Then
            FileAssert::AssertFileContents(expectedOutputFilePath, _actualOutputFilePath);
        }

        ~IntegrationTest() override
        {
            remove(_actualOutputFilePath.c_str());
        }
    };

    TEST_F(IntegrationTest, GivenJsonFileWithFailureOutputType_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest" /
            "Input" / "AllLocationsInputForFailureOutputType.json").string();

        const auto expectedOutputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest"
            / "Output" / "expectedFailureOutput.json").string();

        // When & Then
        PerformTest(inputFilePath, expectedOutputFilePath);
    }

    TEST_F(IntegrationTest, GivenJsonFileWithDamageOutputType_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest" /
            "Input" / "AllLocationsInputForDamageOutputType.json").string();

        const auto expectedOutputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest"
            / "Output" / "expectedDamageOutput.json").string();

        // When & Then
        PerformTest(inputFilePath, expectedOutputFilePath);
    }

    TEST_F(IntegrationTest, GivenJsonFileWithPhysicsOutputType_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest" /
            "Input" / "AllLocationsInputForPhysicsOutputType.json").string();

        const auto expectedOutputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest"
            / "Output" / "expectedPhysicsOutput.json").string();

        // When & Then
        PerformTest(inputFilePath, expectedOutputFilePath);
    }
}
