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

#include "CalculationTestBase.h"

#include <filesystem>
#include <fstream>

#include "AssertHelper.h"

namespace DiKErnel::System::Test
{
    using namespace Core;
    using namespace std;
    using namespace std::filesystem;
    using namespace testing;
    using namespace TestUtil;

    void CalculationTestBase::AssertOutput(
        const Calculator& calculator,
        const double expectedDamage,
        const int* expectedTimeOfFailure)
    {
        ASSERT_EQ(CalculationState::FinishedSuccessfully, calculator.GetCalculationState());

        const auto calculatorResult = calculator.GetResult();
        ASSERT_TRUE(calculatorResult->GetSuccessful());
        ASSERT_EQ(0, calculatorResult->GetEvents().size());

        const auto* calculationOutput = calculatorResult->GetData();
        const auto& locationDependentOutput = calculationOutput->GetLocationDependentOutputItems().at(0).get();

        const auto actualDamage = locationDependentOutput.GetDamages().back();
        AssertHelper::AssertAreEqualWithAcceptablePrecision(expectedDamage, actualDamage);

        const auto* actualTimeOfFailure = locationDependentOutput.GetTimeOfFailure();

        if (expectedTimeOfFailure == nullptr)
        {
            ASSERT_EQ(nullptr, actualTimeOfFailure);
        }
        else
        {
            ASSERT_NE(nullptr, actualTimeOfFailure);
            ASSERT_EQ(*expectedTimeOfFailure, *actualTimeOfFailure);
        }
    }

    unique_ptr<Calculator> CalculationTestBase::PerformTest(
        const ICalculationInput& calculationInput,
        const char* testClass,
        const char* testName)
    {
        unique_ptr<Calculator> calculator = nullptr;

        const auto startTime = std::chrono::high_resolution_clock::now();

        for (auto i = 0; i < 10; ++i)
        {
            calculator = make_unique<Calculator>(calculationInput);

            calculator->WaitForCompletion();
        }

        const auto endTime = std::chrono::high_resolution_clock::now();

        const std::chrono::duration<double, std::milli> ms_double = endTime - startTime;

        ofstream outfile;

        const auto filePath = (temp_directory_path() / "Performance_CPlusPlus.txt").string();

        outfile.open(filePath, std::ios_base::app); // append instead of overwrite
        outfile << testClass;
        outfile << ";";
        outfile << testName;
        outfile << ";";
        outfile << round(ms_double.count());
        outfile << "\n";

        return calculator;
    }
}
