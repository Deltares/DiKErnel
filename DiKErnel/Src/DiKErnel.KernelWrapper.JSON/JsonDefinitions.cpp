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

#include "JsonDefinitions.h"

namespace DiKErnel::KernelWrapper::Json
{
    using namespace std;

    const string JsonDefinitions::CALCULATION_DATA = "Rekendata";
    const string JsonDefinitions::HYDRAULIC_LOADS = "HydraulischeBelastingen";
    const string JsonDefinitions::LOCATIONS = "Locaties";

    const string JsonDefinitions::TIME = "Tijd";
    const string JsonDefinitions::MAXIMUM_WAVE_ANGLE = "GolfhoekMaximum";
    const string JsonDefinitions::BOUNDARY_CONDITIONS_PER_TIME_STEP = "RandvoorwaardenPerTijdstap";
    const string JsonDefinitions::WAVE_HEIGHT_HM0 = "GolfhoogteHm0";
    const string JsonDefinitions::WAVE_PERIOD_TM10 = "GolfperiodeTm10";
    const string JsonDefinitions::WAVE_ANGLE = "Golfhoek";

    const string JsonDefinitions::NAME = "Naam";
    const string JsonDefinitions::REVETMENT = "Bekleding";
    const string JsonDefinitions::TYPE_TOP_LAYER = "TypeToplaag";
    const string JsonDefinitions::RELATIVE_DENSITY = "RelatieveDichtheid";
    const string JsonDefinitions::THICKNESS_TOP_LAYER = "DikteToplaag";
    const string JsonDefinitions::INITIAL_DAMAGE = "BeginSchade";
    const string JsonDefinitions::CRITICAL_DAMAGE = "Faalgetal";
    const string JsonDefinitions::SIMILARITY_PARAMETER_THRESHOLD = "BrekerIndexGrenswaarde";
    const string JsonDefinitions::COEFFICIENT_PLUNGING_AP = "CoefficientPlungingAp";
    const string JsonDefinitions::COEFFICIENT_PLUNGING_BP = "CoefficientPlungingBp";
    const string JsonDefinitions::COEFFICIENT_PLUNGING_CP = "CoefficientPlungingCp";
    const string JsonDefinitions::COEFFICIENT_PLUNGING_NP = "CoefficientPlungingNp";
    const string JsonDefinitions::COEFFICIENT_SURGING_AS = "CoefficientSurgingAs";
    const string JsonDefinitions::COEFFICIENT_SURGING_BS = "CoefficientSurgingBs";
    const string JsonDefinitions::COEFFICIENT_SURGING_CS = "CoefficientSurgingCs";
    const string JsonDefinitions::COEFFICIENT_SURGING_NS = "CoefficientSurgingNs";
    const string JsonDefinitions::PROFILE_SCHEMATIZATION = "Profielschematisatie";
    const string JsonDefinitions::TAN_A = "TanA";

    const string JsonDefinitions::DAMAGE = "Schade";
    const string JsonDefinitions::DAMAGE_OVER_TIME = "SchadegetalPerTijd";

    const string JsonDefinitions::OUTPUT_DATA = "Uitvoerdata";
}
