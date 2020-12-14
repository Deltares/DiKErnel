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

#include <filesystem>
#include <fstream>

#include "InputComposer.h"
#include <gtest/gtest.h>
#include "InputData.h"
#include "TestDataHelper.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    #pragma region Forward declarations

    void AssertCalculationData(
        CalculationData* calculationData);

    void AssertHydraulicLoads(
        HydraulicLoads* hydraulicLoads);

    void AssertCalculationLocations(
        std::vector<CalculationLocation*> calculationLocations);

    #pragma endregion

    // Given
    const auto filePath = TestUtil::TestDataHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test") / "calculation.json";

    TEST(InputComposerTest, GivenFilePathAndInputComposer_WhenGetDomainParametersFromJson_ThenCorrectDataSet)
    {
        // When
        const auto inputData = InputComposer::GetDomainParametersFromJson(filePath.u8string());

        // Assert
        AssertCalculationData(inputData->GetCalculationData());
        AssertHydraulicLoads(inputData->GetHydraulicLoads());
        AssertCalculationLocations(inputData->GetLocations());
    }

    TEST(InputComposerTest, GivenFilePathAndInputComposer_WhenReadCalculationDataFromJson_ThenCorrectDataSet)
    {
        std::ifstream ifs(filePath);
        nlohmann::json json = nlohmann::json::parse(ifs);

        // When
        const auto calculationData = InputComposer::ReadCalculationData(&json);

        // Then
        AssertCalculationData(calculationData.get());
    }

    TEST(InputComposerTest, GivenFilePathAndInputComposer_WhenReadHydraulicLoadsFromJson_ThenCorrectDataSet)
    {
        std::ifstream ifs(filePath);
        nlohmann::json json = nlohmann::json::parse(ifs);

        // When
        const auto hydraulicLoads = InputComposer::ReadHydraulicLoads(&json);

        // Then
        AssertHydraulicLoads(hydraulicLoads.get());
    }

    TEST(InputComposerTest, GivenFilePathAndInputComposer_WhenReadLocationsFromJson_ThenCorrectDataSet)
    {
        std::ifstream ifs(filePath);
        nlohmann::json json = nlohmann::json::parse(ifs);

        // When
        const auto calculationLocations = std::move(InputComposer::ReadLocations(&json));

        // Then
        std::vector<CalculationLocation*> locationPointers;

        for (const auto& location : calculationLocations)
        {
            locationPointers.push_back(location.get());
        }

        AssertCalculationLocations(locationPointers);
    }

    #pragma region Helper methods

    void AssertCalculationData(
        CalculationData* calculationData)
    {
        std::vector<int> expectedValues;

        expectedValues.push_back(0);
        expectedValues.push_back(100);
        expectedValues.push_back(500);
        expectedValues.push_back(800);
        expectedValues.push_back(1200);
        expectedValues.push_back(2000);

        ASSERT_EQ(calculationData->GetTimes(), expectedValues);
    }

    void AssertHydraulicLoads(
        HydraulicLoads* hydraulicLoads)
    {
        ASSERT_EQ(hydraulicLoads->GetWaveAngleMaximum(), 78);

        auto boundaryConditionsPerTimeStep = hydraulicLoads->GetBoundaryConditionsPerTimeStep();

        auto boundaryConditionsForTimeStep = boundaryConditionsPerTimeStep[0];
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWaveHeightHm0(), 0.5);
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWavePeriodTm10(), 2.0);
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWaveAngle(), -10.0);

        boundaryConditionsForTimeStep = boundaryConditionsPerTimeStep[1];
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWaveHeightHm0(), 0.8);
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWavePeriodTm10(), 6.0);
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWaveAngle(), -5.0);

        boundaryConditionsForTimeStep = boundaryConditionsPerTimeStep[2];
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWaveHeightHm0(), 1.2);
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWavePeriodTm10(), 6.0);
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWaveAngle(), 0.0);

        boundaryConditionsForTimeStep = boundaryConditionsPerTimeStep[3];
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWaveHeightHm0(), 1.5);
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWavePeriodTm10(), 7.0);
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWaveAngle(), 7);

        boundaryConditionsForTimeStep = boundaryConditionsPerTimeStep[4];
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWaveHeightHm0(), 0.5);
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWavePeriodTm10(), 4.0);
        ASSERT_EQ(boundaryConditionsForTimeStep->GetWaveAngle(), 8.0);
    }

    void AssertCalculationLocations(
        std::vector<CalculationLocation*> calculationLocations)
    {
        auto calculationLocation = calculationLocations[0];
        auto revetment = calculationLocation->GetRevetment();
        ASSERT_EQ(calculationLocation->GetName(), "LocatieZwak");
        ASSERT_EQ(revetment->GetTypeTopLayer(), "Noorse Steen");
        ASSERT_EQ(revetment->GetRelativeDensity(), 1.6);
        ASSERT_EQ(revetment->GetThicknessTopLayer(), 0.3);
        ASSERT_EQ(revetment->GetInitialDamage(), 0.0);
        ASSERT_EQ(revetment->GetSimilarityParameterThreshold(), 2.9);
        ASSERT_EQ(revetment->GetCoefficientPlungingAp(), 4);
        ASSERT_EQ(revetment->GetCoefficientPlungingBp(), 0.8);
        ASSERT_EQ(revetment->GetCoefficientPlungingCp(), 0.0);
        ASSERT_EQ(revetment->GetCoefficientPlungingNp(), 0.0);
        ASSERT_EQ(revetment->GetCoefficientSurgingAs(), 0.0);
        ASSERT_EQ(revetment->GetCoefficientSurgingBs(), 0.0);
        ASSERT_EQ(revetment->GetCoefficientSurgingCs(), -0.9);
        ASSERT_EQ(revetment->GetCoefficientSurgingNs(), 0.6);
        ASSERT_EQ(calculationLocation->GetProfileSchematization()->GetTanA(), 0.3);

        calculationLocation = calculationLocations[1];
        revetment = calculationLocation->GetRevetment();
        ASSERT_EQ(calculationLocation->GetName(), "LocatieSterk");
        ASSERT_EQ(revetment->GetTypeTopLayer(), "Noorse Steen");
        ASSERT_EQ(revetment->GetRelativeDensity(), 1.6);
        ASSERT_EQ(revetment->GetThicknessTopLayer(), 0.7);
        ASSERT_EQ(revetment->GetInitialDamage(), 0.0);
        ASSERT_EQ(revetment->GetSimilarityParameterThreshold(), 2.9);
        ASSERT_EQ(revetment->GetCoefficientPlungingAp(), 4.0);
        ASSERT_EQ(revetment->GetCoefficientPlungingBp(), 0.8);
        ASSERT_EQ(revetment->GetCoefficientPlungingCp(), 0.0);
        ASSERT_EQ(revetment->GetCoefficientPlungingNp(), 0.0);
        ASSERT_EQ(revetment->GetCoefficientSurgingAs(), 0.0);
        ASSERT_EQ(revetment->GetCoefficientSurgingBs(), 0.0);
        ASSERT_EQ(revetment->GetCoefficientSurgingCs(), -0.9);
        ASSERT_EQ(revetment->GetCoefficientSurgingNs(), 0.6);
        ASSERT_EQ(calculationLocation->GetProfileSchematization()->GetTanA(), 0.3);
    }

    #pragma endregion
}
