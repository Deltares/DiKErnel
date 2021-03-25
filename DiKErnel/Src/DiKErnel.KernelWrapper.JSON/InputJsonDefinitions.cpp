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

#include "InputJsonDefinitions.h"

namespace DiKErnel::KernelWrapper::Json
{
    using namespace std;

    const string InputJsonDefinitions::CALCULATION_DATA = "Rekendata";
    const string InputJsonDefinitions::HYDRAULIC_LOADS = "HydraulischeBelastingen";
    const string InputJsonDefinitions::LOCATIONS = "Locaties";

    const string InputJsonDefinitions::TIME = "Tijd";
    const string InputJsonDefinitions::MAXIMUM_WAVE_ANGLE = "GolfhoekMaximum";
    const string InputJsonDefinitions::BOUNDARY_CONDITIONS_PER_TIME_STEP = "RandvoorwaardenPerTijdstap";
    const string InputJsonDefinitions::WATER_LEVEL = "Waterstand";
    const string InputJsonDefinitions::WAVE_HEIGHT_HM0 = "GolfhoogteHm0";
    const string InputJsonDefinitions::WAVE_PERIOD_TM10 = "GolfperiodeTm10";
    const string InputJsonDefinitions::WAVE_ANGLE = "Golfhoek";

    const string InputJsonDefinitions::NAME = "Naam";
    const string InputJsonDefinitions::REVETMENT = "Bekleding";
    const string InputJsonDefinitions::TYPE_TOP_LAYER = "TypeToplaag";
    const string InputJsonDefinitions::RELATIVE_DENSITY = "RelatieveDichtheid";
    const string InputJsonDefinitions::THICKNESS_TOP_LAYER = "DikteToplaag";
    const string InputJsonDefinitions::INITIAL_DAMAGE = "BeginSchade";
    const string InputJsonDefinitions::CRITICAL_DAMAGE = "Faalgetal";
    const string InputJsonDefinitions::SIMILARITY_PARAMETER_THRESHOLD = "BrekerIndexGrenswaarde";
    const string InputJsonDefinitions::COEFFICIENT_PLUNGING_AP = "CoefficientPlungingAp";
    const string InputJsonDefinitions::COEFFICIENT_PLUNGING_BP = "CoefficientPlungingBp";
    const string InputJsonDefinitions::COEFFICIENT_PLUNGING_CP = "CoefficientPlungingCp";
    const string InputJsonDefinitions::COEFFICIENT_PLUNGING_NP = "CoefficientPlungingNp";
    const string InputJsonDefinitions::COEFFICIENT_SURGING_AS = "CoefficientSurgingAs";
    const string InputJsonDefinitions::COEFFICIENT_SURGING_BS = "CoefficientSurgingBs";
    const string InputJsonDefinitions::COEFFICIENT_SURGING_CS = "CoefficientSurgingCs";
    const string InputJsonDefinitions::COEFFICIENT_SURGING_NS = "CoefficientSurgingNs";
    const string InputJsonDefinitions::PROFILE_SCHEMATIZATION = "Profielschematisatie";
    const string InputJsonDefinitions::TAN_A = "TanA";
    const string InputJsonDefinitions::POSITION_Z = "PositieZ";

    const string InputJsonDefinitions::CALCULATION_METHOD = "Rekenmethoden";
    const string InputJsonDefinitions::CALCULATION_METHOD_SORT = "RekenmethodeSoort";

    const string InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE = "ToenameSchadeNatuursteen";
    const string InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_XIB = "HydraulischeBelastingNatuurSteenXib";
    const string InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_AP = "HydraulischeBelastingNatuurSteenAp";
    const string InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_BP = "HydraulischeBelastingNatuurSteenBp";
    const string InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_CP = "HydraulischeBelastingNatuurSteenCp";
    const string InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_NP = "HydraulischeBelastingNatuurSteenNp";
    const string InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_AS = "HydraulischeBelastingNatuurSteenAs";
    const string InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_BS = "HydraulischeBelastingNatuurSteenBs";
    const string InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_CS = "HydraulischeBelastingNatuurSteenCs";
    const string InputJsonDefinitions::HYDRAULIC_LOAD_ON_NATURAL_STONE_NS = "HydraulischeBelastingNatuurSteenNs";

    const string InputJsonDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE = "BovengrensBelastingNatuursteen";
    const string InputJsonDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_AUL = "BovengrensBelastingNatuursteenAul";
    const string InputJsonDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_BUL = "BovengrensBelastingNatuursteenBul";
    const string InputJsonDefinitions::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_CUL = "BovengrensBelastingNatuursteenCul";

    const string InputJsonDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE = "OndergrensBelastingNatuursteen";
    const string InputJsonDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_ALL = "OndergrensBelastingNatuursteenAll";
    const string InputJsonDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_BLL = "OndergrensBelastingNatuursteenBll";
    const string InputJsonDefinitions::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_CLL = "OndergrensBelastingNatuursteenCll";

    const string InputJsonDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE = "AfstandMaximaleStijghoogteNatuursteen";
    const string InputJsonDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_ASMAX = "AfstandMaximaleStijghoogteNatuursteenAsmax";
    const string InputJsonDefinitions::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_BSMAX = "AfstandMaximaleStijghoogteNatuursteenBsmax";

    const string InputJsonDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE = "MaatgevendeBreedteGolfklap";
    const string InputJsonDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE_AWI = "MaatgevendeBreedteGolfklapAwi";
    const string InputJsonDefinitions::NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE_BWI = "MaatgevendeBreedteGolfklapBwi";

    const string InputJsonDefinitions::WAVE_ANGLE_IMPACT_ON_NATURAL_STONE = "ImpactGolfhoekBekledingNatuursteen";
    const string InputJsonDefinitions::WAVE_ANGLE_IMPACT_ON_NATURAL_STONE_BETA_MAX = "ImpactGolfhoekBekledingNatuursteenBetamax";

    const string InputJsonDefinitions::DAMAGE = "Schade";
    const string InputJsonDefinitions::DAMAGE_OVER_TIME = "SchadegetalPerTijd";
}
