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

        void AssertFailure(
            const json& expectedLocation,
            const json& actualLocation) const
        {
            ASSERT_EQ(expectedLocation["Naam"], actualLocation["Naam"]);

            const auto& expectedFailure = expectedLocation["FalenBekleding"];
            const auto& actualFailure = actualLocation["FalenBekleding"];

            ASSERT_EQ(expectedFailure["Faalgebeurtenis"], actualFailure["Faalgebeurtenis"]);
            ASSERT_EQ(expectedFailure["Faaltijd"], actualFailure["Faaltijd"]);
        }

        void AssertDamage(
            const json& expectedLocation,
            const json& actualLocation) const
        {
            auto expectedDamage = expectedLocation["SchadeBekleding"];
            auto actualDamage = actualLocation["SchadeBekleding"];

            ASSERT_EQ(expectedDamage["Beginschade"], actualDamage["Beginschade"]);
            ASSERT_EQ(expectedDamage["Faalgetal"], actualDamage["Faalgetal"]);
            AssertHelper::AssertAreAlmostEqual(expectedDamage["SchadegetalPerTijd"].get<vector<double>>(), actualDamage["SchadegetalPerTijd"].get<vector<double>>());
        }

        void AssertPhysics(
            const json& expectedLocation,
            const json& actualLocation) const
        {
            const auto& expectedPhysics = expectedLocation["FysicaBekleding"];
            const auto& actualPhysics = actualLocation["FysicaBekleding"];

            ASSERT_EQ(expectedPhysics.size(), actualPhysics.size());
            ASSERT_EQ(expectedPhysics["RekenmethodeSoort"], actualPhysics["RekenmethodeSoort"]);

            for (const auto& [key, value] : expectedPhysics.items())
            {
                for (auto j = 1; j < static_cast<int>(value.size()); ++j)
                {
                    if (value[j].type() == json::value_t::number_float)
                    {
                        AssertHelper::AssertAreAlmostEqual(value[j].get<double>(), actualPhysics[key][j].get<double>());
                    }
                    else
                    {
                        ASSERT_EQ(value[j], actualPhysics[key][j]);
                    }
                }
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

            const auto outputType = ConvertProcessType(get<1>(inputData));

            const auto outputData = calculator.GetCalculationOutput();
            JsonOutputComposer::WriteCalculationOutputToJson(_actualOutputFilePath, *outputData, *calculationInput,
                                                             outputType);

            // Then
            ifstream ifs1(expectedOutputFilePath);
            const auto expectedJson = json::parse(ifs1);

            ifstream ifs2(_actualOutputFilePath);
            const auto actualJson = json::parse(ifs2);

            ASSERT_EQ(expectedJson["Uitvoerdata"]["Tijd"], actualJson["Uitvoerdata"]["Tijd"]);

            const auto& expectedLocations = expectedJson["Uitvoerdata"]["Locaties"];
            const auto& actualLocations = actualJson["Uitvoerdata"]["Locaties"];

            ASSERT_EQ(expectedLocations.size(), actualLocations.size());

            for (auto i = 0; i < static_cast<int>(expectedLocations.size()); ++i)
            {
                const auto& expectedLocation = expectedLocations[i];
                const auto& actualLocation = actualLocations[i];

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
