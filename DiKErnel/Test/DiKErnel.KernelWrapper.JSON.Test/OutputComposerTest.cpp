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

#include "FileAssert.h"
#include "OutputComposer.h"
#include "OutputData.h"
#include "RevetmentOutput.h"
#include "TestDataPathHelper.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    using namespace std;
    using namespace TestUtil;

    struct OutputComposerTest : testing::Test
    {
        const string expectedOutputFilePath =
        (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test")
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
            const vector<double>& damages) const
        {
            return make_unique<CalculationLocationOutput>(locationName, make_unique<RevetmentOutput>(damages));
        }
    };

    TEST_F(OutputComposerTest, GivenFilePathAndOutputData_WhenWriteParametersToJson_ThenCorrectDataWritten)
    {
        // Given
        vector<unique_ptr<CalculationLocationOutput>> calculationLocationsOutput;

        vector<double> damagesLocation1;
        damagesLocation1.push_back(0.15);
        damagesLocation1.push_back(0.253);

        vector<double> damagesLocation2;
        damagesLocation2.push_back(0.28);
        damagesLocation2.push_back(0.512);

        vector<int> times;
        times.push_back(0);
        times.push_back(10);
        times.push_back(100);

        calculationLocationsOutput.push_back(CreateCalculationLocationOutput("testName1", damagesLocation1));
        calculationLocationsOutput.push_back(CreateCalculationLocationOutput("testName2", damagesLocation2));

        const auto outputData = make_unique<OutputData>(move(calculationLocationsOutput));

        // When
        OutputComposer::WriteParametersToJson(actualOutputFilePath, *outputData, times);

        // Then
        FileAssert::AssertFileContents(expectedOutputFilePath, actualOutputFilePath);
    }
}
