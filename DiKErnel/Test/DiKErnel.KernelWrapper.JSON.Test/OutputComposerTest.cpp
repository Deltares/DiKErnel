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

#include <fstream>
#include <memory>

#include "OutputComposer.h"
#include "OutputData.h"
#include "RevetmentOutput.h"
#include "TestDataPathHelper.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    using namespace std;

    #pragma region Forward declarations

    void AssertFileContents(
        const string&,
        const string&);

    #pragma endregion

    struct OutputComposerTest : testing::Test
    {
        const string expectedOutputFilePath =
        (TestUtil::TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test")
            / "OutputComposerTest"
            / "expectedOutput.json").string();

        const string actualOutputFilePath =
        (filesystem::temp_directory_path()
            / "actualOutput.json").string();

        ~OutputComposerTest()
        {
            remove(actualOutputFilePath.c_str());
        }

        unique_ptr<CalculationLocationOutput> CreateCalculationLocationOutput(
            const string& locationName,
            double damage) const
        {
            return make_unique<CalculationLocationOutput>(locationName, make_unique<RevetmentOutput>(damage));
        }
    };

    TEST_F(OutputComposerTest, GivenFilePathAndOutputData_WhenWriteParametersToJson_ThenCorrectDataWritten)
    {
        // Given
        vector<unique_ptr<CalculationLocationOutput>> calculationLocationsOutput;

        calculationLocationsOutput.push_back(CreateCalculationLocationOutput("testName1", 0.15));
        calculationLocationsOutput.push_back(CreateCalculationLocationOutput("testName2", 0.253));

        const auto outputData = make_unique<OutputData>(move(calculationLocationsOutput));

        // When
        OutputComposer::WriteParametersToJson(actualOutputFilePath, *outputData);

        // Then
        AssertFileContents(expectedOutputFilePath, actualOutputFilePath);
    }

    #pragma region Helper methods

    void AssertFileContents(
        const string& expectedOutputFilePath,
        const string& actualOutputFilePath)
    {
        ifstream expectedOutput(expectedOutputFilePath);
        stringstream expectedBuffer;
        expectedBuffer << expectedOutput.rdbuf();

        ifstream actualOutput(actualOutputFilePath);
        stringstream actualBuffer;
        actualBuffer << actualOutput.rdbuf();

        ASSERT_EQ(expectedBuffer.str(), actualBuffer.str());
    }

    #pragma endregion
}
