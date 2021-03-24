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
#include "NaturalStoneRevetmentDefaults.h"

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

            vector<double> hydraulicLoadValues;

            if (readCalculationMethod.contains(InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE))
            {
                const auto& readHydraulicLoads = readCalculationMethod[InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE];

                hydraulicLoadValues.push_back(GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_XIB,
                                                                     NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_XIB));
                hydraulicLoadValues.push_back(GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_AP,
                                                                     NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_XIB));
                hydraulicLoadValues.push_back(GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_BP,
                                                                     NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_XIB));
                hydraulicLoadValues.push_back(GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_CP,
                                                                     NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_XIB));
                hydraulicLoadValues.push_back(GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_NP,
                                                                     NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_XIB));
                hydraulicLoadValues.push_back(GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_AS,
                                                                     NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_XIB));
                hydraulicLoadValues.push_back(GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_BS,
                                                                     NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_XIB));
                hydraulicLoadValues.push_back(GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_CS,
                                                                     NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_XIB));
                hydraulicLoadValues.push_back(GetOptionalDoubleValue(readHydraulicLoads, InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_NS,
                                                                     NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_XIB));
            }
            else
            {
                hydraulicLoadValues.push_back(NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_XIB);
                hydraulicLoadValues.push_back(NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_AP);
                hydraulicLoadValues.push_back(NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_BP);
                hydraulicLoadValues.push_back(NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_CP);
                hydraulicLoadValues.push_back(NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_NP);
                hydraulicLoadValues.push_back(NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_AS);
                hydraulicLoadValues.push_back(NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_BS);
                hydraulicLoadValues.push_back(NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_CS);
                hydraulicLoadValues.push_back(NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_NS);
            }

            vector<double> upperLimitLoadingOfNaturalStoneValues;

            if (readCalculationMethod.contains(InputJsonDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE))
            {
                const auto& readUpperLimitLoadingOfNaturalStone = readCalculationMethod[InputJsonDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE];

                upperLimitLoadingOfNaturalStoneValues.push_back(GetOptionalDoubleValue(readUpperLimitLoadingOfNaturalStone,
                                                                                       InputJsonDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_AUL,
                                                                                       NaturalStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_AUL));
                upperLimitLoadingOfNaturalStoneValues.push_back(GetOptionalDoubleValue(readUpperLimitLoadingOfNaturalStone,
                                                                                       InputJsonDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_BUL,
                                                                                       NaturalStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_BUL));
                upperLimitLoadingOfNaturalStoneValues.push_back(GetOptionalDoubleValue(readUpperLimitLoadingOfNaturalStone,
                                                                                       InputJsonDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_CUL,
                                                                                       NaturalStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_CUL));
            }
            else
            {
                upperLimitLoadingOfNaturalStoneValues.push_back(NaturalStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_AUL);
                upperLimitLoadingOfNaturalStoneValues.push_back(NaturalStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_BUL);
                upperLimitLoadingOfNaturalStoneValues.push_back(NaturalStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_CUL);
            }

            vector<double> lowerLimitLoadingOfNaturalStoneValues;

            if (readCalculationMethod.contains(InputJsonDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE))
            {
                const auto& readLowerLimitLoadingOfNaturalStone = readCalculationMethod[InputJsonDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE];

                lowerLimitLoadingOfNaturalStoneValues.push_back(GetOptionalDoubleValue(readLowerLimitLoadingOfNaturalStone,
                                                                                       InputJsonDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_ALL,
                                                                                       NaturalStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_ALL));
                lowerLimitLoadingOfNaturalStoneValues.push_back(GetOptionalDoubleValue(readLowerLimitLoadingOfNaturalStone,
                                                                                       InputJsonDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_BLL,
                                                                                       NaturalStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_BLL));
                lowerLimitLoadingOfNaturalStoneValues.push_back(GetOptionalDoubleValue(readLowerLimitLoadingOfNaturalStone,
                                                                                       InputJsonDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_CLL,
                                                                                       NaturalStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_CLL));
            }
            else
            {
                lowerLimitLoadingOfNaturalStoneValues.push_back(NaturalStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_ALL);
                lowerLimitLoadingOfNaturalStoneValues.push_back(NaturalStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_BLL);
                lowerLimitLoadingOfNaturalStoneValues.push_back(NaturalStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_CLL);
            }

            vector<double> distanceMaximumWaveElevationNaturalStoneValues;

            if (readCalculationMethod.contains(InputJsonDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE))
            {
                const auto& readDistanceMaximumWaveElevationNaturalStone = readCalculationMethod[
                    InputJsonDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE];

                distanceMaximumWaveElevationNaturalStoneValues.push_back(GetOptionalDoubleValue(
                    readDistanceMaximumWaveElevationNaturalStone, InputJsonDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_ASMAX,
                    NaturalStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NORDIC_STONE_ASMAX));
                distanceMaximumWaveElevationNaturalStoneValues.push_back(GetOptionalDoubleValue(
                    readDistanceMaximumWaveElevationNaturalStone, InputJsonDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_BSMAX,
                    NaturalStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NORDIC_STONE_BSMAX));
            }
            else
            {
                distanceMaximumWaveElevationNaturalStoneValues.push_back(
                    NaturalStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NORDIC_STONE_ASMAX);
                distanceMaximumWaveElevationNaturalStoneValues.push_back(
                    NaturalStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NORDIC_STONE_BSMAX);
            }

            vector<double> normativeWidthOfWaveImpactValues;

            if (readCalculationMethod.contains(InputJsonDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT))
            {
                const auto& readNormativeWidthOfWaveImpact = readCalculationMethod[InputJsonDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT];

                normativeWidthOfWaveImpactValues.push_back(GetOptionalDoubleValue(readNormativeWidthOfWaveImpact,
                                                                                  InputJsonDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI,
                                                                                  NaturalStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_NORDIC_STONE_AWI));
                normativeWidthOfWaveImpactValues.push_back(GetOptionalDoubleValue(readNormativeWidthOfWaveImpact,
                                                                                  InputJsonDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI,
                                                                                  NaturalStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_NORDIC_STONE_BWI));
            }
            else
            {
                normativeWidthOfWaveImpactValues.push_back(NaturalStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_NORDIC_STONE_AWI);
                normativeWidthOfWaveImpactValues.push_back(NaturalStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_NORDIC_STONE_BWI);
            }

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
                            hydraulicLoadValues.at(0),
                            hydraulicLoadValues.at(1),
                            hydraulicLoadValues.at(2),
                            hydraulicLoadValues.at(3),
                            hydraulicLoadValues.at(4),
                            hydraulicLoadValues.at(5),
                            hydraulicLoadValues.at(6),
                            hydraulicLoadValues.at(7),
                            hydraulicLoadValues.at(8)
                        ),
                        make_unique<UpperLimitLoadingOfNaturalStone>(
                            upperLimitLoadingOfNaturalStoneValues.at(0),
                            upperLimitLoadingOfNaturalStoneValues.at(1),
                            upperLimitLoadingOfNaturalStoneValues.at(2)
                        ),
                        make_unique<LowerLimitLoadingOfNaturalStone>(
                            lowerLimitLoadingOfNaturalStoneValues.at(0),
                            lowerLimitLoadingOfNaturalStoneValues.at(1),
                            lowerLimitLoadingOfNaturalStoneValues.at(2)
                        ),
                        make_unique<DistanceMaximumWaveElevationNaturalStone>(
                            distanceMaximumWaveElevationNaturalStoneValues.at(0),
                            distanceMaximumWaveElevationNaturalStoneValues.at(1)
                        ),
                        make_unique<NormativeWidthOfWaveImpact>(
                            normativeWidthOfWaveImpactValues.at(0),
                            normativeWidthOfWaveImpactValues.at(1)
                        ))),
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
        const nlohmann::basic_json<>::value_type& groupElement,
        const string& inputJsonDefinition,
        const double defaultValue)
    {
        if (groupElement.contains(inputJsonDefinition))
        {
            return groupElement[inputJsonDefinition].get<double>();
        }

        return defaultValue;
    }
}
