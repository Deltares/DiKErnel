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
            const auto result = JsonInputComposer::GetInputDataFromJson(inputFilePath);

            Calculator calculator(*result->GetData());

            calculator.WaitForCompletion();

            JsonOutputComposer::WriteCalculationOutputToJson(_actualOutputFilePath, *calculator.GetResult()->GetData(), JsonOutputType::Damage);

            // Then
            ifstream ifs(_actualOutputFilePath);
            const auto json = json::parse(ifs);

            const auto& readLocations = json.at("Uitvoerdata").at("Locaties");

            ASSERT_EQ(expectedDamages.size(), readLocations.size());
            ASSERT_EQ(expectedTimesOfFailure.size(), readLocations.size());

            for (auto i = 0; i < static_cast<int>(readLocations.size()); ++i)
            {
                const auto& readLocation = readLocations.at(i);

                const auto& actualDamages = readLocation.at("SchadeBekleding").at("SchadegetalPerTijd").get<vector<double>>();

                unique_ptr<int> actualTimeOfFailure = nullptr;

                if (!readLocation.at("FalenBekleding").at("Faaltijd").is_null())
                {
                    actualTimeOfFailure = make_unique<int>(readLocation.at("FalenBekleding").at("Faaltijd").get<int>());
                }

                AssertOutput(expectedDamages.at(i), expectedTimesOfFailure.at(i), actualDamages.back(), actualTimeOfFailure.get());
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

    TEST_F(AcceptanceTest, GivenJsonInputWithAsphaltWaveImpactLocationsBelowBerm_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.Acceptance.Test") / "AcceptanceTest"
            / "AsphaltWaveImpactBelowBerm.json").string();

        // When & Then
        PerformTest(inputFilePath, 1.2083569101835512, make_unique<int>(55992).get());
    }

    TEST_F(AcceptanceTest, GivenJsonInputWithAsphaltWaveImpactLocationsOnBerm_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.Acceptance.Test") / "AcceptanceTest"
            / "AsphaltWaveImpactOnBerm.json").string();

        // When & Then
        PerformTest(inputFilePath, vector
                    {
                        1.0211410825504219,
                        1.201708191670589
                    }, vector<const int*>
                    {
                        make_unique<int>(48692).get(),
                        make_unique<int>(32664).get(),
                    });
    }

    TEST_F(AcceptanceTest, GivenJsonInputWithAsphaltWaveImpactLocationsAboveBerm_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto inputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.Acceptance.Test") / "AcceptanceTest"
            / "AsphaltWaveImpactAboveBerm.json").string();

        // When & Then
        PerformTest(inputFilePath, 1.3416472507685535, make_unique<int>(21733).get());
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
