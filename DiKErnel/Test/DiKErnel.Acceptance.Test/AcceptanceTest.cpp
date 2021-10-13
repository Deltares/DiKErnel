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
#include "JsonInputComposer.h"
#include "JsonOutputComposer.h"
#include "TestDataPathHelper.h"

namespace DiKErnel::Acceptance::Test
{
    using namespace Core;
    using namespace KernelWrapper::Json::Input;
    using namespace KernelWrapper::Json::Output;
    using namespace nlohmann;
    using namespace std;
    using namespace testing;
    using namespace TestUtil;

    struct AcceptanceTest : Test
    {
        const string _actualOutputFilePath = (filesystem::temp_directory_path() / "actualOutput.json").string();

        void PerformTest(
            const string& inputFilePath,
            const double expectedDamage,
            const int* expectedTimeOfFailure) const
        {
            PerformTest(inputFilePath, vector(1, expectedDamage), vector(1, expectedTimeOfFailure));
        }

        void PerformTest(
            const string& inputFilePath,
            const vector<double>& expectedDamages,
            const vector<const int*>& expectedTimesOfFailure) const
        {
            // When
            const auto inputData = JsonInputComposer::GetInputDataFromJson(inputFilePath);
            auto* calculationInput = get<0>(inputData).get();

            Calculator calculator(*calculationInput);
            calculator.WaitForCompletion();

            const auto outputData = calculator.GetCalculationOutput();
            JsonOutputComposer::WriteCalculationOutputToJson(_actualOutputFilePath, *outputData, *calculationInput, JsonOutputType::Damage);

            // Then
            ifstream ifs(_actualOutputFilePath);
            const auto json = json::parse(ifs);

            const auto& readLocations = json["Uitvoerdata"]["Locaties"];

            ASSERT_EQ(expectedDamages.size(), readLocations.size());
            ASSERT_EQ(expectedTimesOfFailure.size(), readLocations.size());

            for (auto i = 0; i < static_cast<int>(readLocations.size()); ++i)
            {
                const auto readLocation = readLocations[i];

                const auto& actualDamages = readLocation["SchadeBekleding"]["SchadegetalPerTijd"].get<vector<double>>();

                unique_ptr<int> actualTimeOfFailure = nullptr;

                if (!readLocation["FalenBekleding"]["Faaltijd"].is_null())
                {
                    actualTimeOfFailure = make_unique<int>(readLocation["FalenBekleding"]["Faaltijd"].get<int>());
                }

                AssertOutput(expectedDamages[i], expectedTimesOfFailure[i], actualDamages.back(), actualTimeOfFailure.get());
            }
        }

        static void AssertOutput(
            const double expectedDamage,
            const int* expectedTimeOfFailure,
            const double actualDamage,
            const int* actualTimeOfFailure)
        {
            ASSERT_DOUBLE_EQ(expectedDamage, actualDamage);

            if (expectedTimeOfFailure == nullptr)
            {
                ASSERT_EQ(expectedTimeOfFailure, actualTimeOfFailure);
            }
            else
            {
                ASSERT_EQ(*expectedTimeOfFailure, *actualTimeOfFailure);
            }
        }

        ~AcceptanceTest() override
        {
            remove(_actualOutputFilePath.c_str());
        }
    };

    TEST_F(AcceptanceTest, GivenJsonInputWithAsphaltWaveImpactLocations_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.Acceptance.Test") / "AcceptanceTest"
            / "AsphaltWaveImpact.json").string();

        // When & Then
        PerformTest(inputFilePath, vector
                    {
                        12.759112406328461,
                        0.19953624319339708
                    }, vector<const int*>
                    {
                        make_unique<int>(2895).get(),
                        nullptr
                    });
    }

    TEST_F(AcceptanceTest, GivenJsonInputWithGrassWaveImpactLocation_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.Acceptance.Test") / "AcceptanceTest"
            / "GrassWaveImpact.json").string();

        // When & Then
        PerformTest(inputFilePath, vector
                    {
                        1.0587334122468244,
                        2001.5520809290408
                    }, vector<const int*>
                    {
                        make_unique<int>(18391).get(),
                        make_unique<int>(9002).get()
                    });
    }

    TEST_F(AcceptanceTest, GivenJsonInputWithGrassWaveRunupRayleighLocation_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.Acceptance.Test") / "AcceptanceTest"
            / "GrassWaveRunupRayleigh.json").string();

        // When & Then
        PerformTest(inputFilePath, 2.4709313851627792, make_unique<int>(9959).get());
    }

    TEST_F(AcceptanceTest, GivenJsonInputWithGrassWaveRunupRayleighLocationWithHighWaterLevel_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.Acceptance.Test") / "AcceptanceTest"
            / "GrassWaveRunupRayleighWithHighWaterLevel.json").string();

        // When & Then
        PerformTest(inputFilePath, 0.26622772912694259, nullptr);
    }

    TEST_F(AcceptanceTest, GivenJsonInputWithNaturalStoneLocation_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.Acceptance.Test") / "AcceptanceTest"
            / "NaturalStone.json").string();

        // When & Then
        PerformTest(inputFilePath, 1.1709670425264469, make_unique<int>(3833).get());
    }

    TEST_F(AcceptanceTest, GivenJsonInputWithDikeProfileWithoutBermWithNaturalStoneLocation_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.Acceptance.Test") / "AcceptanceTest"
            / "NaturalStoneDikeProfileWithoutBerm.json").string();

        // When & Then
        PerformTest(inputFilePath, 1.1494612002264992, make_unique<int>(3654).get());
    }
}
