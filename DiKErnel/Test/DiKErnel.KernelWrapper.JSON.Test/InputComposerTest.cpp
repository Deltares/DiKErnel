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
    void AssertCalculationData(
        const CalculationData& calculationData)
    {
        REQUIRE_THAT(calculationData.time, Catch::Equals<int>({ 0, 100, 500, 800, 1200, 2000 }));
    }

    void AssertHydraulicLoads(
        const HydraulicLoads& hydraulicLoads)
    {
        REQUIRE(hydraulicLoads.waveAngleMaximum == 78);

        auto boundaryConditionsForTimeStep = hydraulicLoads.boundaryConditionsPerTimeStep[0];
        REQUIRE(boundaryConditionsForTimeStep.GetWaveHeightHm0() == 0.5);
        REQUIRE(boundaryConditionsForTimeStep.GetWavePeriodTm10() == 2.0);
        REQUIRE(boundaryConditionsForTimeStep.GetWaveAngle() == -10.0);

        boundaryConditionsForTimeStep = hydraulicLoads.boundaryConditionsPerTimeStep[1];
        REQUIRE(boundaryConditionsForTimeStep.GetWaveHeightHm0() == 0.8);
        REQUIRE(boundaryConditionsForTimeStep.GetWavePeriodTm10() == 6.0);
        REQUIRE(boundaryConditionsForTimeStep.GetWaveAngle() == -5.0);

        boundaryConditionsForTimeStep = hydraulicLoads.boundaryConditionsPerTimeStep[2];
        REQUIRE(boundaryConditionsForTimeStep.GetWaveHeightHm0() == 1.2);
        REQUIRE(boundaryConditionsForTimeStep.GetWavePeriodTm10() == 6.0);
        REQUIRE(boundaryConditionsForTimeStep.GetWaveAngle() == 0.0);

        boundaryConditionsForTimeStep = hydraulicLoads.boundaryConditionsPerTimeStep[3];
        REQUIRE(boundaryConditionsForTimeStep.GetWaveHeightHm0() == 1.5);
        REQUIRE(boundaryConditionsForTimeStep.GetWavePeriodTm10() == 7.0);
        REQUIRE(boundaryConditionsForTimeStep.GetWaveAngle() == 7);

        boundaryConditionsForTimeStep = hydraulicLoads.boundaryConditionsPerTimeStep[4];
        REQUIRE(boundaryConditionsForTimeStep.GetWaveHeightHm0() == 0.5);
        REQUIRE(boundaryConditionsForTimeStep.GetWavePeriodTm10() == 4.0);
        REQUIRE(boundaryConditionsForTimeStep.GetWaveAngle() == 8.0);
    }

    void AssertCalculationLocations(
        std::vector<CalculationLocation>& calculationLocations)
    {
        REQUIRE(calculationLocations[0].name == "LocatieZwak");

        REQUIRE(calculationLocations[0].revetment.typeTopLayer == "Noorse Steen");
        REQUIRE(calculationLocations[0].revetment.relativeDensity == 1.6);
        REQUIRE(calculationLocations[0].revetment.thicknessTopLayer == 0.3);
        REQUIRE(calculationLocations[0].revetment.initialDamage == 0.0);
        REQUIRE(calculationLocations[0].revetment.similarityParameterThreshold == 2.9);
        REQUIRE(calculationLocations[0].revetment.coefficientPlungingAp == 4);
        REQUIRE(calculationLocations[0].revetment.coefficientPlungingBp == 0.8);
        REQUIRE(calculationLocations[0].revetment.coefficientPlungingCp == 0.0);
        REQUIRE(calculationLocations[0].revetment.coefficientPlungingNp == 0.0);
        REQUIRE(calculationLocations[0].revetment.coefficientSurgingAs == 0.0);
        REQUIRE(calculationLocations[0].revetment.coefficientSurgingBs == 0.0);
        REQUIRE(calculationLocations[0].revetment.coefficientSurgingCs == -0.9);
        REQUIRE(calculationLocations[0].revetment.coefficientSurgingNs == 0.6);

        REQUIRE(calculationLocations[0].profileSchematization.tanA == 0.3);

        REQUIRE(calculationLocations[1].name == "LocatieSterk");

        REQUIRE(calculationLocations[1].revetment.typeTopLayer == "Noorse Steen");
        REQUIRE(calculationLocations[1].revetment.relativeDensity == 1.6);
        REQUIRE(calculationLocations[1].revetment.thicknessTopLayer == 0.7);
        REQUIRE(calculationLocations[1].revetment.initialDamage == 0.0);
        REQUIRE(calculationLocations[1].revetment.similarityParameterThreshold == 2.9);
        REQUIRE(calculationLocations[1].revetment.coefficientPlungingAp == 4.0);
        REQUIRE(calculationLocations[1].revetment.coefficientPlungingBp == 0.8);
        REQUIRE(calculationLocations[1].revetment.coefficientPlungingCp == 0.0);
        REQUIRE(calculationLocations[1].revetment.coefficientPlungingNp == 0.0);
        REQUIRE(calculationLocations[1].revetment.coefficientSurgingAs == 0.0);
        REQUIRE(calculationLocations[1].revetment.coefficientSurgingBs == 0.0);
        REQUIRE(calculationLocations[1].revetment.coefficientSurgingCs == -0.9);
        REQUIRE(calculationLocations[1].revetment.coefficientSurgingNs == 0.6);

        REQUIRE(calculationLocations[1].profileSchematization.tanA == 0.3);
    }

    TEST_CASE("GivenFilePathAndInputComposer")
    {
        // Given
        const auto filePath = TestUtil::TestDataHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test") / "calculation.json";
        InputComposer inputComposer;

        SECTION("WhenGetDomainParametersFromJson_ThenCorrectDataSet")
        {
            // When
            InputData* inputData = inputComposer.GetDomainParametersFromJson(filePath.u8string());

            // Assert
            AssertCalculationData(inputData->calculationData);

            AssertHydraulicLoads(inputData->hydraulicLoads);

            AssertCalculationLocations(inputData->locations);
        }

        SECTION("WhenReadCalculationDataFromJson_ThenCorrectDataSet")
        {
            std::ifstream ifs(filePath);
            nlohmann::json json = nlohmann::json::parse(ifs);

            // When
            CalculationData calculationData = inputComposer.ReadCalculationData(&json);

            // Then
            AssertCalculationData(calculationData);
        }

        SECTION("WhenReadHydraulicLoadsFromJson_ThenCorrectDataSet")
        {
            std::ifstream ifs(filePath);
            nlohmann::json json = nlohmann::json::parse(ifs);

            // When
            HydraulicLoads hydraulicLoads = inputComposer.ReadHydraulicLoads(&json);

            // Then
            AssertHydraulicLoads(hydraulicLoads);
        }

        SECTION("WhenReadLocationsFromJson_ThenCorrectDataSet")
        {
            std::ifstream ifs(filePath);
            nlohmann::json json = nlohmann::json::parse(ifs);

            // When
            std::vector<CalculationLocation> calculationLocations = inputComposer.ReadLocations(&json);

            // Then
            AssertCalculationLocations(calculationLocations);
        }
    }
}
