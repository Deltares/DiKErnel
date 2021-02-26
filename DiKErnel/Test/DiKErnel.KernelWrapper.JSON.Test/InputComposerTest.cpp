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

#include <gtest/gtest.h>

#include "InputComposer.h"
#include "InputData.h"
#include "TestDataPathHelper.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    using namespace std;

    struct InputComposerTest : testing::Test
    {
        const string _filePathWithAllParameters =
        (TestUtil::TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test")
            / "InputComposerTest"
            / "inputWithAllParameters.json").string();

        const string _filePathWithMandatoryParameters =
        (TestUtil::TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test")
            / "InputComposerTest"
            / "inputWithMandatoryParameters.json").string();

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

            ASSERT_EQ(expectedValues, calculationData.GetTimes());
        }

        void AssertHydraulicLoads(
            const HydraulicLoads& hydraulicLoads) const
        {
            ASSERT_EQ(78, hydraulicLoads.GetWaveAngleMaximum());

            const auto& boundaryConditionsPerTimeStep = hydraulicLoads.GetBoundaryConditionsPerTimeStep();

            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[0].get(), 0.5, 2.0, -10.0);
            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[1].get(), 0.8, 6.0, -5.0);
            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[2].get(), 1.2, 6.0, 0.0);
            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[3].get(), 1.5, 7.0, 7.0);
            AssertBoundaryConditionsForTimeStep(boundaryConditionsPerTimeStep[4].get(), 0.5, 4.0, 8.0);
        }

        void AssertBoundaryConditionsForTimeStep(
            const BoundaryConditionsPerTimeStep& boundaryConditionsForTimeStep,
            const double expectedWaveHeightHm0,
            const double expectedWavePeriodTm10,
            const double expectedWaveAngle) const
        {
            ASSERT_DOUBLE_EQ(expectedWaveHeightHm0, boundaryConditionsForTimeStep.GetWaveHeightHm0());
            ASSERT_DOUBLE_EQ(expectedWavePeriodTm10, boundaryConditionsForTimeStep.GetWavePeriodTm10());
            ASSERT_DOUBLE_EQ(expectedWaveAngle, boundaryConditionsForTimeStep.GetWaveAngle());
        }

        void AssertCalculationLocations(
            const vector<unique_ptr<CalculationLocation>>& calculationLocations,
            const double expectedCriticalDamageLocation1,
            const double expectedCriticalDamageLocation2) const
        {
            vector<reference_wrapper<CalculationLocation>> locationReferences;

            for (const auto& location : calculationLocations)
            {
                locationReferences.emplace_back(*location);
            }

            AssertCalculationLocations(locationReferences, expectedCriticalDamageLocation1, expectedCriticalDamageLocation2);
        }

        void AssertCalculationLocations(
            const vector<reference_wrapper<CalculationLocation>>& calculationLocations,
            const double expectedCriticalDamageLocation1,
            const double expectedCriticalDamageLocation2) const
        {
            AssertCalculationLocation(calculationLocations[0].get(), "LocatieZwak", "Noorse Steen", 1.65, 0.3,
                                      0.0, expectedCriticalDamageLocation1, 2.9, 4.0, 0.0,
                                      0.0, -0.9, 0.8, 0.0, 0.0, 0.6, 0.3);
            AssertCalculationLocation(calculationLocations[1].get(), "LocatieSterk", "Noorse Steen", 1.65, 0.7,
                                      0.1, expectedCriticalDamageLocation2, 2.9, 4.0, 0.0,
                                      0.0, -0.9, 0.8, 0.0, 0.0, 0.6, 0.3);
        }

        void AssertCalculationLocation(
            const CalculationLocation& calculationLocation,
            const string& expectedName,
            const string& expectedTypeTopLayer,
            const double expectedRelativeDensity,
            const double expectedThicknessTopLayer,
            const double expectedInitialDamage,
            const double expectedCriticalDamage,
            const double expectedSimilarityParameterThreshold,
            const double expectedPlungingCoefficientA,
            const double expectedPlungingCoefficientB,
            const double expectedPlungingCoefficientC,
            const double expectedPlungingCoefficientN,
            const double expectedSurgingCoefficientA,
            const double expectedSurgingCoefficientB,
            const double expectedSurgingCoefficientC,
            const double expectedSurgingCoefficientN,
            const double expectedTanA) const
        {
            ASSERT_EQ(expectedName, calculationLocation.GetName());

            AssertDamageVariables(
                calculationLocation.GetDamageVariables(),
                expectedInitialDamage,
                expectedCriticalDamage);

            AssertRevetment(
                calculationLocation.GetRevetment(),
                expectedTypeTopLayer,
                expectedRelativeDensity,
                expectedThicknessTopLayer,
                expectedSimilarityParameterThreshold,
                expectedPlungingCoefficientA,
                expectedPlungingCoefficientB,
                expectedPlungingCoefficientC,
                expectedPlungingCoefficientN,
                expectedSurgingCoefficientA,
                expectedSurgingCoefficientB,
                expectedSurgingCoefficientC,
                expectedSurgingCoefficientN);

            ASSERT_DOUBLE_EQ(expectedTanA, calculationLocation.GetProfileSchematization().GetTanA());
        }

        void AssertDamageVariables(
            const DamageVariables& damageVariables,
            const double expectedInitialDamage,
            const double expectedCriticalDamage)
             const
        {
            ASSERT_DOUBLE_EQ(expectedInitialDamage, damageVariables.GetInitialDamage());
            ASSERT_DOUBLE_EQ(expectedCriticalDamage, damageVariables.GetCriticalDamage());
        }

        void AssertRevetment(
            const Revetment& revetment,
            const string& expectedTypeTopLayer,
            const double expectedRelativeDensity,
            const double expectedThicknessTopLayer,
            const double expectedSimilarityParameterThreshold,
            const double expectedPlungingCoefficientA,
            const double expectedPlungingCoefficientB,
            const double expectedPlungingCoefficientC,
            const double expectedPlungingCoefficientN,
            const double expectedSurgingCoefficientA,
            const double expectedSurgingCoefficientB,
            const double expectedSurgingCoefficientC,
            const double expectedSurgingCoefficientN) const
        {
            ASSERT_EQ(expectedTypeTopLayer, revetment.GetTypeTopLayer());
            ASSERT_DOUBLE_EQ(expectedRelativeDensity, revetment.GetRelativeDensity());
            ASSERT_DOUBLE_EQ(expectedThicknessTopLayer, revetment.GetThicknessTopLayer());
            ASSERT_DOUBLE_EQ(expectedSimilarityParameterThreshold, revetment.GetSimilarityParameterThreshold());
            ASSERT_DOUBLE_EQ(expectedPlungingCoefficientA, revetment.GetPlungingCoefficientA());
            ASSERT_DOUBLE_EQ(expectedPlungingCoefficientB, revetment.GetPlungingCoefficientB());
            ASSERT_DOUBLE_EQ(expectedPlungingCoefficientC, revetment.GetPlungingCoefficientC());
            ASSERT_DOUBLE_EQ(expectedPlungingCoefficientN, revetment.GetPlungingCoefficientN());
            ASSERT_DOUBLE_EQ(expectedSurgingCoefficientA, revetment.GetSurgingCoefficientA());
            ASSERT_DOUBLE_EQ(expectedSurgingCoefficientB, revetment.GetSurgingCoefficientB());
            ASSERT_DOUBLE_EQ(expectedSurgingCoefficientC, revetment.GetSurgingCoefficientC());
            ASSERT_DOUBLE_EQ(expectedSurgingCoefficientN, revetment.GetSurgingCoefficientN());
        }
    };

    TEST_F(InputComposerTest, GivenFileWithAllInputParametersAndInputComposer_WhenGetDomainParametersFromJson_ThenCorrectDataSet)
    {
        // When
        const auto inputData = InputComposer::GetDomainParametersFromJson(_filePathWithAllParameters);

        // Then
        AssertCalculationData(inputData->GetCalculationData());
        AssertHydraulicLoads(inputData->GetHydraulicLoads());
        AssertCalculationLocations(inputData->GetLocations(), 1.0, 1.05);
    }

    TEST_F(InputComposerTest, GivenFileWithMandatoryInputParametersAndInputComposer_WhenGetDomainParametersFromJson_ThenCorrectDataSet)
    {
        // When
        const auto inputData = InputComposer::GetDomainParametersFromJson(_filePathWithMandatoryParameters);

        // Then
        AssertCalculationData(inputData->GetCalculationData());
        AssertHydraulicLoads(inputData->GetHydraulicLoads());
        AssertCalculationLocations(inputData->GetLocations(), 1.0, 1.0);
    }

    TEST_F(InputComposerTest, GivenFileWithAllInputParametersAndInputComposer_WhenReadCalculationDataFromJson_ThenCorrectDataSet)
    {
        // Given
        ifstream ifs(_filePathWithAllParameters);
        const auto json = nlohmann::json::parse(ifs);

        // When
        const auto calculationData = InputComposer::ReadCalculationData(json);

        // Then
        AssertCalculationData(*calculationData);
    }

    TEST_F(InputComposerTest, GivenFileWithAllInputParametersAndInputComposer_WhenReadHydraulicLoadsFromJson_ThenCorrectDataSet)
    {
        // Given
        ifstream ifs(_filePathWithAllParameters);
        const auto json = nlohmann::json::parse(ifs);

        // When
        const auto hydraulicLoads = InputComposer::ReadHydraulicLoads(json);

        // Then
        AssertHydraulicLoads(*hydraulicLoads);
    }

    TEST_F(InputComposerTest, GivenFileWithAllInputParametersAndInputComposer_WhenReadLocationsFromJson_ThenCorrectDataSet)
    {
        // Given
        ifstream ifs(_filePathWithAllParameters);
        const auto json = nlohmann::json::parse(ifs);

        // When
        const auto calculationLocations = InputComposer::ReadLocations(json);

        // Then
        AssertCalculationLocations(calculationLocations, 1.0, 1.05);
    }
}
