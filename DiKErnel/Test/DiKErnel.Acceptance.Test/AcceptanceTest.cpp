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

#include "Calculator.h"
#include "FileAssert.h"
#include "JsonInputComposer.h"
#include "JsonOutputComposer.h"
#include "TestDataPathHelper.h"

namespace DiKErnel::Acceptance::Test
{
    using namespace Core;
    using namespace KernelWrapper::Json::Input;
    using namespace std;
    using namespace testing;
    using namespace TestUtil;    

    struct AcceptanceTest : Test
    {
        const string _actualOutputFilePath =
            (filesystem::temp_directory_path()
                / "actualOutput.json").string();

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

        // When
        const auto calculationInput = JsonInputComposer::GetCalculationInputFromJson(filePath);
        Calculator calculator(*calculationInput);
        calculator.WaitForCompletion();

        const auto outputData = calculator.GetCalculationOutput();
        KernelWrapper::Json::Output::JsonOutputComposer::WriteCalculationOutputToJson(_actualOutputFilePath, *outputData, *calculationInput);

        // Assert
        const auto expectedOutputFilePath =
            (TestDataPathHelper::GetTestDataPath("DiKErnel.Acceptance.Test")
                / "AcceptanceTest"
                / "expectedOutputNaturalStone.json").string();
        FileAssert::AssertFileContents(expectedOutputFilePath, _actualOutputFilePath);
    }
}
