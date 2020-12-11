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

#include "catch2/catch.hpp"

#include "InputComposer.h"
#include "InputData.h"
#include "TestDataHelper.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    #pragma region Forward declarations

    void AssertCalculationData(
        const CalculationData& calculationData);

    void AssertHydraulicLoads(
        const HydraulicLoads& hydraulicLoads);

    void AssertCalculationLocations(
        std::vector<CalculationLocation>& calculationLocations);

    #pragma endregion

    TEST_CASE("GivenFilePathAndInputComposer")
    {
        // Given
        const auto filePath = TestUtil::TestDataHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test") / "calculation.json";

        SECTION("WhenGetDomainParametersFromJson_ThenCorrectDataSet")
        {
            // When
            InputData* inputData = InputComposer::GetDomainParametersFromJson(filePath.u8string());

            // Assert
            AssertCalculationData(inputData->GetCalculationData());

            AssertHydraulicLoads(inputData->GetHydraulicLoads());

            AssertCalculationLocations(inputData->GetLocations());
        }

        SECTION("WhenReadCalculationDataFromJson_ThenCorrectDataSet")
        {
            std::ifstream ifs(filePath);
            nlohmann::json json = nlohmann::json::parse(ifs);

            // When
            CalculationData calculationData = InputComposer::ReadCalculationData(&json);

            // Then
            AssertCalculationData(calculationData);
        }

        SECTION("WhenReadHydraulicLoadsFromJson_ThenCorrectDataSet")
        {
            std::ifstream ifs(filePath);
            nlohmann::json json = nlohmann::json::parse(ifs);

            // When
            HydraulicLoads hydraulicLoads = InputComposer::ReadHydraulicLoads(&json);

            // Then
            AssertHydraulicLoads(hydraulicLoads);
        }

        SECTION("WhenReadLocationsFromJson_ThenCorrectDataSet")
        {
            std::ifstream ifs(filePath);
            nlohmann::json json = nlohmann::json::parse(ifs);

            // When
            std::vector<CalculationLocation> calculationLocations = InputComposer::ReadLocations(&json);

            // Then
            AssertCalculationLocations(calculationLocations);
        }
    }

    #pragma region Helper methods

    void AssertCalculationData(
        const CalculationData& calculationData)
    {
        REQUIRE_THAT(calculationData.time, Catch::Equals<int>({ 0, 100, 500, 800, 1200, 2000 }));
    }

    void AssertHydraulicLoads(
        const HydraulicLoads& hydraulicLoads)
    {
        REQUIRE(hydraulicLoads.GetWaveAngleMaximum() == 78);

        auto boundaryConditionsPerTimeStep = hydraulicLoads.GetBoundaryConditionsPerTimeStep();

        auto boundaryConditionsForTimeStep = boundaryConditionsPerTimeStep[0];
        REQUIRE(boundaryConditionsForTimeStep.GetWaveHeightHm0() == 0.5);
        REQUIRE(boundaryConditionsForTimeStep.GetWavePeriodTm10() == 2.0);
        REQUIRE(boundaryConditionsForTimeStep.GetWaveAngle() == -10.0);

        boundaryConditionsForTimeStep = boundaryConditionsPerTimeStep[1];
        REQUIRE(boundaryConditionsForTimeStep.GetWaveHeightHm0() == 0.8);
        REQUIRE(boundaryConditionsForTimeStep.GetWavePeriodTm10() == 6.0);
        REQUIRE(boundaryConditionsForTimeStep.GetWaveAngle() == -5.0);

        boundaryConditionsForTimeStep = boundaryConditionsPerTimeStep[2];
        REQUIRE(boundaryConditionsForTimeStep.GetWaveHeightHm0() == 1.2);
        REQUIRE(boundaryConditionsForTimeStep.GetWavePeriodTm10() == 6.0);
        REQUIRE(boundaryConditionsForTimeStep.GetWaveAngle() == 0.0);

        boundaryConditionsForTimeStep = boundaryConditionsPerTimeStep[3];
        REQUIRE(boundaryConditionsForTimeStep.GetWaveHeightHm0() == 1.5);
        REQUIRE(boundaryConditionsForTimeStep.GetWavePeriodTm10() == 7.0);
        REQUIRE(boundaryConditionsForTimeStep.GetWaveAngle() == 7);

        boundaryConditionsForTimeStep = boundaryConditionsPerTimeStep[4];
        REQUIRE(boundaryConditionsForTimeStep.GetWaveHeightHm0() == 0.5);
        REQUIRE(boundaryConditionsForTimeStep.GetWavePeriodTm10() == 4.0);
        REQUIRE(boundaryConditionsForTimeStep.GetWaveAngle() == 8.0);
    }

    void AssertCalculationLocations(
        std::vector<CalculationLocation>& calculationLocations)
    {
        auto calculationLocation = calculationLocations[0];
        auto revetment = calculationLocation.GetRevetment();
        REQUIRE(calculationLocation.GetName() == "LocatieZwak");
        REQUIRE(revetment.GetTypeTopLayer() == "Noorse Steen");
        REQUIRE(revetment.GetRelativeDensity() == 1.6);
        REQUIRE(revetment.GetThicknessTopLayer() == 0.3);
        REQUIRE(revetment.GetInitialDamage() == 0.0);
        REQUIRE(revetment.GetSimilarityParameterThreshold() == 2.9);
        REQUIRE(revetment.GetCoefficientPlungingAp() == 4);
        REQUIRE(revetment.GetCoefficientPlungingBp() == 0.8);
        REQUIRE(revetment.GetCoefficientPlungingCp() == 0.0);
        REQUIRE(revetment.GetCoefficientPlungingNp() == 0.0);
        REQUIRE(revetment.GetCoefficientSurgingAs() == 0.0);
        REQUIRE(revetment.GetCoefficientSurgingBs() == 0.0);
        REQUIRE(revetment.GetCoefficientSurgingCs() == -0.9);
        REQUIRE(revetment.GetCoefficientSurgingNs() == 0.6);
        REQUIRE(calculationLocation.GetProfileSchematization().GetTanA() == 0.3);

        calculationLocation = calculationLocations[1];
        revetment = calculationLocation.GetRevetment();
        REQUIRE(calculationLocation.GetName() == "LocatieSterk");
        REQUIRE(revetment.GetTypeTopLayer() == "Noorse Steen");
        REQUIRE(revetment.GetRelativeDensity() == 1.6);
        REQUIRE(revetment.GetThicknessTopLayer() == 0.7);
        REQUIRE(revetment.GetInitialDamage() == 0.0);
        REQUIRE(revetment.GetSimilarityParameterThreshold() == 2.9);
        REQUIRE(revetment.GetCoefficientPlungingAp() == 4.0);
        REQUIRE(revetment.GetCoefficientPlungingBp() == 0.8);
        REQUIRE(revetment.GetCoefficientPlungingCp() == 0.0);
        REQUIRE(revetment.GetCoefficientPlungingNp() == 0.0);
        REQUIRE(revetment.GetCoefficientSurgingAs() == 0.0);
        REQUIRE(revetment.GetCoefficientSurgingBs() == 0.0);
        REQUIRE(revetment.GetCoefficientSurgingCs() == -0.9);
        REQUIRE(revetment.GetCoefficientSurgingNs() == 0.6);
        REQUIRE(calculationLocation.GetProfileSchematization().GetTanA() == 0.3);
    }

    #pragma endregion
}
