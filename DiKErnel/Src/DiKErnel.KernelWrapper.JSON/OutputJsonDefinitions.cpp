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

#include "OutputJsonDefinitions.h"

namespace DiKErnel::KernelWrapper::Json
{
    using namespace std;

    const string OutputJsonDefinitions::CALCULATION_DATA = "Rekendata";
    const string OutputJsonDefinitions::HYDRAULIC_LOADS = "HydraulischeBelastingen";
    const string OutputJsonDefinitions::LOCATIONS = "Locaties";

    const string OutputJsonDefinitions::TIME = "Tijd";
    const string OutputJsonDefinitions::MAXIMUM_WAVE_ANGLE = "GolfhoekMaximum";
    const string OutputJsonDefinitions::BOUNDARY_CONDITIONS_PER_TIME_STEP = "RandvoorwaardenPerTijdstap";
    const string OutputJsonDefinitions::WATER_LEVEL = "Waterstand";
    const string OutputJsonDefinitions::WAVE_HEIGHT_HM0 = "GolfhoogteHm0";
    const string OutputJsonDefinitions::WAVE_PERIOD_TM10 = "GolfperiodeTm10";
    const string OutputJsonDefinitions::WAVE_ANGLE = "Golfhoek";

    const string OutputJsonDefinitions::NAME = "Naam";
    const string OutputJsonDefinitions::REVETMENT = "Bekleding";
    const string OutputJsonDefinitions::TYPE_TOP_LAYER = "TypeToplaag";
    const string OutputJsonDefinitions::RELATIVE_DENSITY = "RelatieveDichtheid";
    const string OutputJsonDefinitions::THICKNESS_TOP_LAYER = "DikteToplaag";
    const string OutputJsonDefinitions::INITIAL_DAMAGE = "BeginSchade";
    const string OutputJsonDefinitions::CRITICAL_DAMAGE = "Faalgetal";
    const string OutputJsonDefinitions::FAILED = "Faalgebeurtenis";
    const string OutputJsonDefinitions::TIME_OF_FAILURE = "Faaltijd";
    const string OutputJsonDefinitions::SIMILARITY_PARAMETER_THRESHOLD = "BrekerIndexGrenswaarde";
    const string OutputJsonDefinitions::COEFFICIENT_PLUNGING_AP = "CoefficientPlungingAp";
    const string OutputJsonDefinitions::COEFFICIENT_PLUNGING_BP = "CoefficientPlungingBp";
    const string OutputJsonDefinitions::COEFFICIENT_PLUNGING_CP = "CoefficientPlungingCp";
    const string OutputJsonDefinitions::COEFFICIENT_PLUNGING_NP = "CoefficientPlungingNp";
    const string OutputJsonDefinitions::COEFFICIENT_SURGING_AS = "CoefficientSurgingAs";
    const string OutputJsonDefinitions::COEFFICIENT_SURGING_BS = "CoefficientSurgingBs";
    const string OutputJsonDefinitions::COEFFICIENT_SURGING_CS = "CoefficientSurgingCs";
    const string OutputJsonDefinitions::COEFFICIENT_SURGING_NS = "CoefficientSurgingNs";
    const string OutputJsonDefinitions::PROFILE_SCHEMATIZATION = "Profielschematisatie";
    const string OutputJsonDefinitions::TAN_A = "TanA";
    const string OutputJsonDefinitions::POSITION_Z = "PositieZ";

    const string OutputJsonDefinitions::DAMAGE = "Schade";
    const string OutputJsonDefinitions::DAMAGE_OVER_TIME = "SchadegetalPerTijd";

    const string OutputJsonDefinitions::OUTPUT_DATA = "Uitvoerdata";
}
