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

#include "OutputComposer.h"
#include "OutputData.h"
#include "RevetmentOutput.h"
#include "TestDataHelper.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    // // Given
    const auto filePath = TestUtil::TestDataHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test") / "calculationTest.json";
    
    TEST(OutputComposerTest, GivenFilePathAndOutputData_WhenWriteParametersToJson_ThenCorrectDataWritten)
    {
        // Given
        std::vector<CalculationLocationOutput*> locationsOutput;
        RevetmentOutput revetmentOutput(0.15);
        RevetmentOutput revetmentOutput2(0.253);
        CalculationLocationOutput calculationLocationOutput("testName", &revetmentOutput);
        CalculationLocationOutput calculationLocationOutput2("testName2", &revetmentOutput2);
        locationsOutput.push_back(&calculationLocationOutput);
        locationsOutput.push_back(&calculationLocationOutput2);
        const OutputData outputData(locationsOutput);

        const std::string expectedJson = R"({"Locaties":[{"Bekleding":{"Schade":0.15},"Naam":"testName"},{"Bekleding":{"Schade":0.253},"Naam":"testName2"}]})";

        // When
        const auto json = OutputComposer::WriteParametersToJson(filePath, outputData);

        // Then
        ASSERT_EQ(expectedJson, json);
    }
}
