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
    const string InputJsonDefinitions::FAILED = "Faalgebeurtenis";
    const string InputJsonDefinitions::TIME_OF_FAILURE = "Faaltijd";
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

    const string InputJsonDefinitions::DAMAGE = "Schade";
    const string InputJsonDefinitions::DAMAGE_OVER_TIME = "SchadegetalPerTijd";

    const string InputJsonDefinitions::OUTPUT_DATA = "Uitvoerdata";
}
