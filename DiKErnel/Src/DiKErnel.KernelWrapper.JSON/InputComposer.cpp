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

#include "InputComposer.h"

#include <fstream>

#include "Defaults.h"
#include "InputData.h"
#include "InputJsonDefinitions.h"

namespace DiKErnel::KernelWrapper::Json
{
    using namespace DomainLibrary;
    using namespace std;

    unique_ptr<InputData> InputComposer::GetDomainParametersFromJson(
        const string& filePath)
    {
        const auto json = ParseJson(filePath);

        return make_unique<InputData>(
            ReadCalculationData(json),
            ReadHydraulicLoads(json),
            ReadLocations(json));
    }

    unique_ptr<CalculationData> InputComposer::ReadCalculationData(
        const nlohmann::json& json)
    {
        const auto& readCalculationData = json[InputJsonDefinitions::CALCULATION_DATA];

        return make_unique<CalculationData>(
            readCalculationData[InputJsonDefinitions::TIME].get<vector<int>>()
        );
    }

    unique_ptr<HydraulicLoads> InputComposer::ReadHydraulicLoads(
        const nlohmann::json& json)
    {
        const auto& readHydraulicLoads = json[InputJsonDefinitions::HYDRAULIC_LOADS];
        const auto& readBoundaryConditionsPerTimeStep = readHydraulicLoads[InputJsonDefinitions::BOUNDARY_CONDITIONS_PER_TIME_STEP];

        vector<unique_ptr<BoundaryConditionsPerTimeStep>> boundaryConditionsPerTimeStep;

        for (const auto& readBoundaryConditionsForTimeStep : readBoundaryConditionsPerTimeStep)
        {
            boundaryConditionsPerTimeStep.push_back(
                make_unique<BoundaryConditionsPerTimeStep>(
                    readBoundaryConditionsForTimeStep[InputJsonDefinitions::WATER_LEVEL].get<double>(),
                    readBoundaryConditionsForTimeStep[InputJsonDefinitions::WAVE_HEIGHT_HM0].get<double>(),
                    readBoundaryConditionsForTimeStep[InputJsonDefinitions::WAVE_PERIOD_TM10].get<double>(),
                    readBoundaryConditionsForTimeStep[InputJsonDefinitions::WAVE_ANGLE].get<double>()
                ));
        }

        return make_unique<HydraulicLoads>(
            readHydraulicLoads[InputJsonDefinitions::MAXIMUM_WAVE_ANGLE].get<int>(),
            move(boundaryConditionsPerTimeStep)
        );
    }

    vector<unique_ptr<CalculationLocation>> InputComposer::ReadLocations(
        const nlohmann::json& json)
    {
        vector<unique_ptr<CalculationLocation>> calculationLocations;

        const auto& readLocations = json[InputJsonDefinitions::LOCATIONS];

        for (const auto& readLocation : readLocations)
        {
            const auto& readRevetment = readLocation[InputJsonDefinitions::REVETMENT];
            const auto& readCalculationMethod = readRevetment[InputJsonDefinitions::CALCULATION_METHOD];
            const auto& readHydraulicLoads = readCalculationMethod[InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE];
            const auto& readUpperLimitLoadingOfNaturalStone = readCalculationMethod[InputJsonDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE];
            const auto& readLowerLimitLoadingOfNaturalStone = readCalculationMethod[InputJsonDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE];
            const auto& readDistanceMaximumWaveElevationNaturalStone = readCalculationMethod[
                InputJsonDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE];
            const auto& readNormativeWidthOfWaveImpact = readCalculationMethod[InputJsonDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT];
            const auto& readDamageVariables = readLocation[InputJsonDefinitions::DAMAGE];
            const auto& readProfileSchematization = readLocation[InputJsonDefinitions::PROFILE_SCHEMATIZATION];

            calculationLocations.push_back(make_unique<CalculationLocation>(
                readLocation[InputJsonDefinitions::NAME].get<string>(),
                make_unique<DamageVariables>(
                    readDamageVariables[InputJsonDefinitions::INITIAL_DAMAGE].get<double>(),
                    GetOptionalDoubleValue(readDamageVariables, InputJsonDefinitions::CRITICAL_DAMAGE, Defaults::CRITICAL_DAMAGE)),
                make_unique<Revetment>(
                    readRevetment[InputJsonDefinitions::TYPE_TOP_LAYER].get<string>(),
                    readRevetment[InputJsonDefinitions::RELATIVE_DENSITY].get<double>(),
                    readRevetment[InputJsonDefinitions::THICKNESS_TOP_LAYER].get<double>(),
                    make_unique<CalculationMethod>(
                        readCalculationMethod[InputJsonDefinitions::CALCULATION_METHOD_SORT].get<string>(),
                        make_unique<HydraulicLoadOnNaturalStone>(
                            GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_XIB,
                                                   Defaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_XIB),
                            GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_AP,
                                                   Defaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_AP),
                            GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_BP,
                                                   Defaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_BP),
                            GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_CP,
                                                   Defaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_CP),
                            GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_NP,
                                                   Defaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_NP),
                            GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_AS,
                                                   Defaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_AS),
                            GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_BS,
                                                   Defaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_BS),
                            GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_CS,
                                                   Defaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_CS),
                            GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_NS,
                                                   Defaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_NS)),
                        make_unique<UpperLimitLoadingOfNaturalStone>(
                            GetOptionalDoubleValue(readUpperLimitLoadingOfNaturalStone,
                                                   InputJsonDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_AUL,
                                                   Defaults::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_AUL),
                            GetOptionalDoubleValue(readUpperLimitLoadingOfNaturalStone,
                                                   InputJsonDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_BUL,
                                                   Defaults::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_BUL),
                            GetOptionalDoubleValue(readUpperLimitLoadingOfNaturalStone,
                                                   InputJsonDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_CUL,
                                                   Defaults::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_CUL)),
                        make_unique<LowerLimitLoadingOfNaturalStone>(
                            GetOptionalDoubleValue(readLowerLimitLoadingOfNaturalStone,
                                                   InputJsonDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_AUL,
                                                   Defaults::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_ALL),
                            GetOptionalDoubleValue(readLowerLimitLoadingOfNaturalStone,
                                                   InputJsonDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_BUL,
                                                   Defaults::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_BLL),
                            GetOptionalDoubleValue(readLowerLimitLoadingOfNaturalStone,
                                                   InputJsonDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_CUL,
                                                   Defaults::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_CLL)),
                        make_unique<DistanceMaximumWaveElevationNaturalStone>(
                            GetOptionalDoubleValue(readDistanceMaximumWaveElevationNaturalStone,
                                                   InputJsonDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_ASMAX,
                                                   Defaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_ASMAX),
                            GetOptionalDoubleValue(readDistanceMaximumWaveElevationNaturalStone,
                                                   InputJsonDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_BSMAX,
                                                   Defaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_BSMAX)),
                        make_unique<NormativeWidthOfWaveImpact>(
                            GetOptionalDoubleValue(readNormativeWidthOfWaveImpact,
                                                   InputJsonDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI,
                                                   Defaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI),
                            GetOptionalDoubleValue(readNormativeWidthOfWaveImpact,
                                                   InputJsonDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI,
                                                   Defaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI)))),
                make_unique<ProfileSchematization>(
                    readProfileSchematization[InputJsonDefinitions::TAN_A].get<double>(),
                    readProfileSchematization[InputJsonDefinitions::POSITION_Z].get<double>()
                )
            ));
        }

        return calculationLocations;
    }

    nlohmann::json InputComposer::ParseJson(
        const string& filePath)
    {
        ifstream ifs(filePath);
        return nlohmann::json::parse(ifs);
    }

    double InputComposer::GetOptionalDoubleValue(
        const nlohmann::basic_json<>::value_type& hydraulicLoads,
        const string& inputJsonDefinition,
        double defaultValue)
    {
        if (hydraulicLoads.contains(inputJsonDefinition))
        {
            return hydraulicLoads[inputJsonDefinition].get<double>();
        }

        return defaultValue;
    }
}
