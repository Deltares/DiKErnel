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
#include "TestDataHelper.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    #pragma region Forward declarations

    std::unique_ptr<CalculationLocationOutput> CreateCalculationLocationOutput(
        const std::string&,
        double);

    void AssertFileContents(
        const std::string&,
        const std::string&);

    #pragma endregion

    // Given
    struct OutputComposerTest : testing::Test
    {
        const std::string expectedOutputFilePath = 
            (TestUtil::TestDataHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test")
                / "OutputComposerTest"
                / "expectedOutput.json").string();

        const std::string actualOutputFilePath = 
            (std::filesystem::temp_directory_path()
                / "actualOutput.json").string();

        ~OutputComposerTest()
        {
            std::remove(actualOutputFilePath.c_str());
        }
    };

    TEST_F(OutputComposerTest, GivenFilePathAndOutputData_WhenWriteParametersToJson_ThenCorrectDataWritten)
    {
        // Given
        std::vector<std::unique_ptr<CalculationLocationOutput>> calculationLocationsOutput;

        calculationLocationsOutput.push_back(CreateCalculationLocationOutput("testName1", 0.15));
        calculationLocationsOutput.push_back(CreateCalculationLocationOutput("testName2", 0.253));

        const auto outputData = std::make_unique<OutputData>(std::move(calculationLocationsOutput));

        // When
        OutputComposer::WriteParametersToJson(actualOutputFilePath, outputData.get());

        // Then
        AssertFileContents(expectedOutputFilePath, actualOutputFilePath);
    }

    #pragma region Helper methods

    std::unique_ptr<CalculationLocationOutput> CreateCalculationLocationOutput(
        const std::string& locationName,
        double damage)
    {
        return std::make_unique<CalculationLocationOutput>(locationName, std::make_unique<RevetmentOutput>(damage));
    }

    void AssertFileContents(
        const std::string& expectedOutputFilePath,
        const std::string& actualOutputFilePath)
    {
        std::ifstream expectedOutput(expectedOutputFilePath);
        std::stringstream expectedBuffer;
        expectedBuffer << expectedOutput.rdbuf();

        std::ifstream actualOutput(actualOutputFilePath);
        std::stringstream actualBuffer;
        actualBuffer << actualOutput.rdbuf();

        ASSERT_EQ(expectedBuffer.str(), actualBuffer.str());
    }

    #pragma endregion
}
