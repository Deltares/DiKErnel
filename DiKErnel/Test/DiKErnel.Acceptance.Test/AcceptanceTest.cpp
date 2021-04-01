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
        const string _actualOutputFilePath =
        (filesystem::temp_directory_path()
            / "actualOutput.json").string();

        void PerformTest(
            const string& filePath,
            const double expectedDamage,
            const double* expectedFailureTime) const
        {
            // When
            const auto calculationInput = JsonInputComposer::GetCalculationInputFromJson(filePath);
            Calculator calculator(*calculationInput);
            calculator.WaitForCompletion();

            const auto outputData = calculator.GetCalculationOutput();
            JsonOutputComposer::WriteCalculationOutputToJson(_actualOutputFilePath, *outputData, *calculationInput);

            // Assert
            ifstream ifs(_actualOutputFilePath);
            const auto json = json::parse(ifs);

            const auto& readLocation = json["Uitvoerdata"]["Locaties"][0];
            const auto& actualDamages = readLocation["Schade"]["SchadegetalPerTijd"].get<vector<double>>();

            unique_ptr<double> actualFailureTime = nullptr;

            if (!readLocation["Schade"]["Faaltijd"].is_null())
            {
                actualFailureTime = make_unique<double>(readLocation["Schade"]["Faaltijd"].get<double>());
            }

            AssertOutput(expectedDamage, expectedFailureTime, actualDamages.back(), actualFailureTime.get());
        }

        static void AssertOutput(
            const double expectedDamage,
            const double* expectedFailureTime,
            const double actualDamage,
            const double* actualFailureTime)
        {
            ASSERT_DOUBLE_EQ(expectedDamage, actualDamage);

            if (expectedFailureTime == nullptr)
            {
                ASSERT_EQ(expectedFailureTime, actualFailureTime);
            }
            else
            {
                ASSERT_DOUBLE_EQ(*expectedFailureTime, *actualFailureTime);
            }
        }

        ~AcceptanceTest()
        {
            remove(_actualOutputFilePath.c_str());
        }
    };

    TEST_F(AcceptanceTest, GivenJsonWithNaturalStoneLocation_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto filePath =
        (TestDataPathHelper::GetTestDataPath("DiKErnel.Acceptance.Test")
            / "AcceptanceTest" / "naturalStone.json").string();

        // When & Then
        PerformTest(filePath, 1.1836103307707342, make_unique<double>(3067).get());
    }

    TEST_F(AcceptanceTest, GivenJsonWithGrassWaveImpactLocation_WhenCalculating_ThenExpectedOutputJsonCreated)
    {
        // Given
        const auto filePath =
        (TestDataPathHelper::GetTestDataPath("DiKErnel.Acceptance.Test")
            / "AcceptanceTest" / "grassWaveImpact.json").string();

        // When & Then
        PerformTest(filePath, 2.836154231066117, make_unique<double>(32955).get());
    }
}
