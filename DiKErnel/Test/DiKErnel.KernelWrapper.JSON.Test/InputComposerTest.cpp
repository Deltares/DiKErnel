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
#include "TestDataPathHelper.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    using namespace std;

    struct InputComposerTest : testing::Test
    {
        const string filePath =
        (TestUtil::TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test")
            / "InputComposerTest"
            / "testInput.json").string();

        void AssertCalculationData(
            const CalculationData& calculationData) const
        {
            vector<int> expectedValues;

            expectedValues.push_back(0);
            expectedValues.push_back(100);
            expectedValues.push_back(500);
            expectedValues.push_back(800);
            expectedValues.push_back(1200);
            expectedValues.push_back(2000);

            ASSERT_EQ(calculationData.GetTimes(), expectedValues);
        }

        void AssertHydraulicLoads(
            const HydraulicLoads& hydraulicLoads) const
        {
            ASSERT_EQ(hydraulicLoads.GetWaveAngleMaximum(), 78);

            const auto& boundaryConditionsPerTimeStep = hydraulicLoads.GetBoundaryConditionsPerTimeStep();

            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[0], 0.5, 2.0, -10.0);
            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[1], 0.8, 6.0, -5.0);
            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[2], 1.2, 6.0, 0.0);
            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[3], 1.5, 7.0, 7.0);
            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[4], 0.5, 4.0, 8.0);
        }

        void AssertBoundaryConditionsForTimeStep(
            const reference_wrapper<BoundaryConditionsPerTimeStep> boundaryConditionsForTimeStep,
            const double expectedWaveHeightHm0,
            const double expectedWavePeriodTm10,
            const double expectedWaveAngle) const
        {
            ASSERT_DOUBLE_EQ(boundaryConditionsForTimeStep.get().GetWaveHeightHm0(), expectedWaveHeightHm0);
            ASSERT_DOUBLE_EQ(boundaryConditionsForTimeStep.get().GetWavePeriodTm10(), expectedWavePeriodTm10);
            ASSERT_DOUBLE_EQ(boundaryConditionsForTimeStep.get().GetWaveAngle(), expectedWaveAngle);
        }

        void AssertCalculationLocations(
            const vector<unique_ptr<CalculationLocation>>& calculationLocations) const
        {
            vector<reference_wrapper<CalculationLocation>> locationReferences;

            for (const auto& location : calculationLocations)
            {
                locationReferences.emplace_back(*location);
            }

            AssertCalculationLocations(locationReferences);
        }

        void AssertCalculationLocations(
            vector<reference_wrapper<CalculationLocation>> calculationLocations) const
        {
            AssertCalculationLocation(calculationLocations[0].get(), "LocatieZwak", "Noorse Steen", 1.65, 0.3, 0.0, 2.9, 4.0, 0.0, 0.0, -0.9, 0.8,
                                      0.0, 0.0, 0.6, 0.3);
            AssertCalculationLocation(calculationLocations[1].get(), "LocatieSterk", "Noorse Steen", 1.65, 0.7, 0.0, 2.9, 4.0, 0.0, 0.0, -0.9, 0.8,
                                      0.0, 0.0, 0.6, 0.3);
        }

        void AssertCalculationLocation(
            const CalculationLocation& calculationLocation,
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
            const double expectedTanA) const
        {
            ASSERT_EQ(calculationLocation.GetName(), expectedName);
            AssertRevetment(
                calculationLocation.GetRevetment(),
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
            ASSERT_DOUBLE_EQ(calculationLocation.GetProfileSchematization().GetTanA(), expectedTanA);
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
            const double expectedCoefficientSurgingNs) const
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
    };

    TEST_F(InputComposerTest, GivenFilePathAndInputComposer_WhenGetDomainParametersFromJson_ThenCorrectDataSet)
    {
        // Given & When
        const auto inputData = InputComposer::GetDomainParametersFromJson(filePath);

        // Then
        AssertCalculationData(inputData->GetCalculationData());
        AssertHydraulicLoads(inputData->GetHydraulicLoads());
        AssertCalculationLocations(inputData->GetLocations());
    }

    TEST_F(InputComposerTest, GivenFilePathAndInputComposer_WhenReadCalculationDataFromJson_ThenCorrectDataSet)
    {
        // Given
        ifstream ifs(filePath);
        const auto json = nlohmann::json::parse(ifs);

        // When
        const auto calculationData = InputComposer::ReadCalculationData(json);

        // Then
        AssertCalculationData(*calculationData);
    }

    TEST_F(InputComposerTest, GivenFilePathAndInputComposer_WhenReadHydraulicLoadsFromJson_ThenCorrectDataSet)
    {
        // Given
        ifstream ifs(filePath);
        const auto json = nlohmann::json::parse(ifs);

        // When
        const auto hydraulicLoads = InputComposer::ReadHydraulicLoads(json);

        // Then
        AssertHydraulicLoads(*hydraulicLoads);
    }

    TEST_F(InputComposerTest, GivenFilePathAndInputComposer_WhenReadLocationsFromJson_ThenCorrectDataSet)
    {
        // Given
        ifstream ifs(filePath);
        const auto json = nlohmann::json::parse(ifs);

        // When
        const auto calculationLocations = InputComposer::ReadLocations(json);

        // Then
        AssertCalculationLocations(calculationLocations);
    }
}
