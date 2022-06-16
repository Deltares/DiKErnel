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

#include <fstream>

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "AssertHelper.h"
#include "Calculator.h"
#include "JsonInputComposer.h"
#include "JsonOutputComposer.h"
#include "TestDataPathHelper.h"

namespace DiKErnel::KernelWrapper::Json::Integration::Test
{
    using namespace Core;
    using namespace Input;
    using namespace nlohmann;
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

        void AssertMetaData(
            const json& actualMetaData) const
        {
            ASSERT_EQ(1.23, actualMetaData.at("Test 1"));
            ASSERT_EQ("4.56", actualMetaData.at("Test 2"));
        }

        void AssertFailure(
            const json& expectedLocation,
            const json& actualLocation) const
        {
            const auto& expectedFailure = expectedLocation.at("FalenBekleding");
            const auto& actualFailure = actualLocation.at("FalenBekleding");

            ASSERT_EQ(expectedFailure.at("Faalgebeurtenis"), actualFailure.at("Faalgebeurtenis"));
            ASSERT_EQ(expectedFailure.at("Faaltijd"), actualFailure.at("Faaltijd"));
        }

        void AssertDamage(
            const json& expectedLocation,
            const json& actualLocation) const
        {
            const auto& expectedDamage = expectedLocation.at("SchadeBekleding");
            const auto& actualDamage = actualLocation.at("SchadeBekleding");

            AssertHelper::AssertAreAlmostEqual(expectedDamage.at("SchadegetalPerTijd").get<vector<double>>(),
                                               actualDamage.at("SchadegetalPerTijd").get<vector<double>>());
        }

        void AssertPhysics(
            const json& expectedLocation,
            const json& actualLocation) const
        {
            const auto& expectedPhysics = expectedLocation.at("FysicaBekleding");
            const auto& actualPhysics = actualLocation.at("FysicaBekleding");

            ASSERT_EQ(expectedPhysics.size(), actualPhysics.size());
            ASSERT_EQ(expectedPhysics.at("HoogteLocatie"), actualPhysics.at("HoogteLocatie"));

            for (const auto& [key, value] : expectedPhysics.items())
            {
                for (auto j = 1; j < static_cast<int>(value.size()); ++j)
                {
                    if (value.at(j).type() == json::value_t::number_float)
                    {
                        AssertHelper::AssertAreAlmostEqual(value.at(j).get<double>(), actualPhysics.at(key).at(j).get<double>());
                    }
                    else
                    {
                        ASSERT_EQ(value.at(j), actualPhysics.at(key).at(j));
                    }
                }
            }
        }

        void PerformTest(
            const string& inputFilePath,
            const string& expectedOutputFilePath,
            const bool withMetaData) const
        {
            // When
            const auto& result = JsonInputComposer::GetInputDataFromJson(inputFilePath);
            const auto* inputData = result->GetData();

            Calculator calculator(inputData->GetCalculationInput());

            calculator.WaitForCompletion();

            const auto outputType = ConvertProcessType(inputData->GetProcessType());

            auto metaDataItems = vector<pair<string, variant<double, string>>>();

            if (withMetaData)
            {
                metaDataItems.emplace_back("Test 1", 1.23);
                metaDataItems.emplace_back("Test 2", "4.56");
            }

            JsonOutputComposer::WriteCalculationOutputToJson(_actualOutputFilePath, *calculator.GetResult()->GetData(), outputType, metaDataItems);

            // Then
            ifstream ifs1(expectedOutputFilePath);
            const auto expectedJson = json::parse(ifs1);

            ifstream ifs2(_actualOutputFilePath);
            const auto actualJson = json::parse(ifs2);

            if (withMetaData)
            {
                AssertMetaData(actualJson.at("MetaInformatie"));
            }
            else
            {
                ASSERT_FALSE(actualJson.contains("MetaInformatie"));
            }

            const auto& expectedLocations = expectedJson.at("Uitvoerdata").at("Locaties");
            const auto& actualLocations = actualJson.at("Uitvoerdata").at("Locaties");

            ASSERT_EQ(expectedLocations.size(), actualLocations.size());

            for (auto i = 0; i < static_cast<int>(expectedLocations.size()); ++i)
            {
                const auto& expectedLocation = expectedLocations.at(i);
                const auto& actualLocation = actualLocations.at(i);

                AssertFailure(expectedLocation, actualLocation);

                if (outputType == JsonOutputType::Damage || outputType == JsonOutputType::Physics)
                {
                    AssertDamage(expectedLocation, actualLocation);
                }

                if (outputType == JsonOutputType::Physics)
                {
                    AssertPhysics(expectedLocation, actualLocation);
                }
            }
        }

        ~IntegrationTest() override
        {
            remove(_actualOutputFilePath.c_str());
        }
    };

    TEST_F(IntegrationTest, GivenJsonFileWithFailureOutputTypeWithoutMetaData_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest" /
            "Input" / "AllLocationsInputForFailureOutputType.json").string();

        const auto expectedOutputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest"
            / "Output" / "expectedFailureOutput.json").string();

        // When & Then
        PerformTest(inputFilePath, expectedOutputFilePath, false);
    }

    TEST_F(IntegrationTest, GivenJsonFileWithFailureOutputTypeWithMetaData_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest" /
            "Input" / "AllLocationsInputForFailureOutputType.json").string();

        const auto expectedOutputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest"
            / "Output" / "expectedFailureOutput.json").string();

        // When & Then
        PerformTest(inputFilePath, expectedOutputFilePath, true);
    }

    TEST_F(IntegrationTest, GivenJsonFileWithDamageOutputTypeWithoutMetaData_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest" /
            "Input" / "AllLocationsInputForDamageOutputType.json").string();

        const auto expectedOutputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest"
            / "Output" / "expectedDamageOutput.json").string();

        // When & Then
        PerformTest(inputFilePath, expectedOutputFilePath, false);
    }

    TEST_F(IntegrationTest, GivenJsonFileWithDamageOutputTypeWithMetaData_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest" /
            "Input" / "AllLocationsInputForDamageOutputType.json").string();

        const auto expectedOutputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest"
            / "Output" / "expectedDamageOutput.json").string();

        // When & Then
        PerformTest(inputFilePath, expectedOutputFilePath, true);
    }

    TEST_F(IntegrationTest, GivenJsonFileWithPhysicsOutputTypeWithoutMetaData_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest" /
            "Input" / "AllLocationsInputForPhysicsOutputType.json").string();

        const auto expectedOutputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest"
            / "Output" / "expectedPhysicsOutput.json").string();

        // When & Then
        PerformTest(inputFilePath, expectedOutputFilePath, false);
    }

    TEST_F(IntegrationTest, GivenJsonFileWithPhysicsOutputTypeWithMetaData_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest" /
            "Input" / "AllLocationsInputForPhysicsOutputType.json").string();

        const auto expectedOutputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Integration.Test") / "IntegrationTest"
            / "Output" / "expectedPhysicsOutput.json").string();

        // When & Then
        PerformTest(inputFilePath, expectedOutputFilePath, true);
    }
}
