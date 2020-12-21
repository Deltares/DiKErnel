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

#include <filesystem>
#include <fstream>

#include "InputComposer.h"
#include "InputData.h"
#include "TestDataHelper.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    #pragma region Forward declarations

    void AssertCalculationData(
        CalculationData*);

    void AssertHydraulicLoads(
        HydraulicLoads*);

    void AssertBoundaryConditionsForTimeStep(
        BoundaryConditionsPerTimeStep*,
        double,
        double,
        double);

    void AssertCalculationLocations(
        std::vector<CalculationLocation*>);

    void AssertCalculationLocation(
        CalculationLocation* calculationLocation,
        const char*,
        const char*,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double);

    void AssertRevetment(
        const Revetment&,
        const char*,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double,
        double);

    #pragma endregion

    // Given
    struct InputComposerTest : testing::Test
    {
        const std::string filePath =
        (TestUtil::TestDataHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test")
            / "InputComposerTest"
            / "testInput.json").string();
    };

    TEST_F(InputComposerTest, GivenFilePathAndInputComposer_WhenGetDomainParametersFromJson_ThenCorrectDataSet)
    {
        // When
        const auto inputData = InputComposer::GetDomainParametersFromJson(filePath);

        // Then
        AssertCalculationData(inputData->GetCalculationData());
        AssertHydraulicLoads(inputData->GetHydraulicLoads());
        AssertCalculationLocations(inputData->GetLocations());
    }

    TEST_F(InputComposerTest, GivenFilePathAndInputComposer_WhenReadCalculationDataFromJson_ThenCorrectDataSet)
    {
        std::ifstream ifs(filePath);
        auto json = nlohmann::json::parse(ifs);

        // When
        const auto calculationData = InputComposer::ReadCalculationData(&json);

        // Then
        AssertCalculationData(calculationData.get());
    }

    TEST_F(InputComposerTest, GivenFilePathAndInputComposer_WhenReadHydraulicLoadsFromJson_ThenCorrectDataSet)
    {
        std::ifstream ifs(filePath);
        auto json = nlohmann::json::parse(ifs);

        // When
        const auto hydraulicLoads = InputComposer::ReadHydraulicLoads(&json);

        // Then
        AssertHydraulicLoads(hydraulicLoads.get());
    }

    TEST_F(InputComposerTest, GivenFilePathAndInputComposer_WhenReadLocationsFromJson_ThenCorrectDataSet)
    {
        std::ifstream ifs(filePath);
        auto json = nlohmann::json::parse(ifs);

        // When
        const auto calculationLocations = InputComposer::ReadLocations(&json);

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

        AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[0], 0.5, 2.0, -10.0);
        AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[1], 0.8, 6.0, -5.0);
        AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[2], 1.2, 6.0, 0.0);
        AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[3], 1.5, 7.0, 7.0);
        AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[4], 0.5, 4.0, 8.0);
    }

    void AssertBoundaryConditionsForTimeStep(
        BoundaryConditionsPerTimeStep* boundaryConditionsForTimeStep,
        const double expectedWaveHeightHm0,
        const double expectedWavePeriodTm10,
        const double expectedWaveAngle)
    {
        ASSERT_DOUBLE_EQ(boundaryConditionsForTimeStep->GetWaveHeightHm0(), expectedWaveHeightHm0);
        ASSERT_DOUBLE_EQ(boundaryConditionsForTimeStep->GetWavePeriodTm10(), expectedWavePeriodTm10);
        ASSERT_DOUBLE_EQ(boundaryConditionsForTimeStep->GetWaveAngle(), expectedWaveAngle);
    }

    void AssertCalculationLocations(
        std::vector<CalculationLocation*> calculationLocations)
    {
        AssertCalculationLocation(calculationLocations[0], "LocatieZwak", "Noorse Steen", 1.65, 0.3, 0.0, 2.9, 4.0, 0.0, 0.0, -0.9, 0.8, 0.0, 0.0,
                                  0.6, 0.3);
        AssertCalculationLocation(calculationLocations[1], "LocatieSterk", "Noorse Steen", 1.65, 0.7, 0.0, 2.9, 4.0, 0.0, 0.0, -0.9, 0.8, 0.0, 0.0,
                                  0.6, 0.3);
    }

    void AssertCalculationLocation(
        CalculationLocation* calculationLocation,
        const char* expectedName,
        const char* expectedTypeTopLayer,
        const double expectedRelativeDensity,
        const double expectedThicknessTopLayer,
        const double expectedInitialDamage,
        const double expectedSimilarityParameterThreshold,
        const double expectedCoefficientPlungingAp,
        const double expectedCoefficientPlungingBp,
        const double expectedCoefficientPlungingCp,
        const double expectedCoefficientPlungingNp,
        const double expectedCoefficientSurgingAs,
        const double expectedCoefficientSurgingBs,
        const double expectedCoefficientSurgingCs,
        const double expectedCoefficientSurgingNs,
        const double expectedTanA)
    {
        ASSERT_EQ(calculationLocation->GetName(), expectedName);
        AssertRevetment(
            calculationLocation->GetRevetment(),
            expectedTypeTopLayer,
            expectedRelativeDensity,
            expectedThicknessTopLayer,
            expectedInitialDamage,
            expectedSimilarityParameterThreshold,
            expectedCoefficientPlungingAp,
            expectedCoefficientPlungingBp,
            expectedCoefficientPlungingCp,
            expectedCoefficientPlungingNp,
            expectedCoefficientSurgingAs,
            expectedCoefficientSurgingBs,
            expectedCoefficientSurgingCs,
            expectedCoefficientSurgingNs);
        ASSERT_DOUBLE_EQ(calculationLocation->GetProfileSchematization().GetTanA(), expectedTanA);
    }

    void AssertRevetment(
        const Revetment& revetment,
        const char* expectedTypeTopLayer,
        const double expectedRelativeDensity,
        const double expectedThicknessTopLayer,
        const double expectedInitialDamage,
        const double expectedSimilarityParameterThreshold,
        const double expectedCoefficientPlungingAp,
        const double expectedCoefficientPlungingBp,
        const double expectedCoefficientPlungingCp,
        const double expectedCoefficientPlungingNp,
        const double expectedCoefficientSurgingAs,
        const double expectedCoefficientSurgingBs,
        const double expectedCoefficientSurgingCs,
        const double expectedCoefficientSurgingNs)
    {
        ASSERT_EQ(revetment.GetTypeTopLayer(), expectedTypeTopLayer);
        ASSERT_DOUBLE_EQ(revetment.GetRelativeDensity(), expectedRelativeDensity);
        ASSERT_DOUBLE_EQ(revetment.GetThicknessTopLayer(), expectedThicknessTopLayer);
        ASSERT_DOUBLE_EQ(revetment.GetInitialDamage(), expectedInitialDamage);
        ASSERT_DOUBLE_EQ(revetment.GetSimilarityParameterThreshold(), expectedSimilarityParameterThreshold);
        ASSERT_DOUBLE_EQ(revetment.GetCoefficientPlungingAp(), expectedCoefficientPlungingAp);
        ASSERT_DOUBLE_EQ(revetment.GetCoefficientPlungingBp(), expectedCoefficientPlungingBp);
        ASSERT_DOUBLE_EQ(revetment.GetCoefficientPlungingCp(), expectedCoefficientPlungingCp);
        ASSERT_DOUBLE_EQ(revetment.GetCoefficientPlungingNp(), expectedCoefficientPlungingNp);
        ASSERT_DOUBLE_EQ(revetment.GetCoefficientSurgingAs(), expectedCoefficientSurgingAs);
        ASSERT_DOUBLE_EQ(revetment.GetCoefficientSurgingBs(), expectedCoefficientSurgingBs);
        ASSERT_DOUBLE_EQ(revetment.GetCoefficientSurgingCs(), expectedCoefficientSurgingCs);
        ASSERT_DOUBLE_EQ(revetment.GetCoefficientSurgingNs(), expectedCoefficientSurgingNs);
    }

    #pragma endregion
}
