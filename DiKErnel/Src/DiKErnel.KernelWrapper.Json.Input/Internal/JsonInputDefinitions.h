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

#pragma once

#include <string>

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputDefinitions
    {
        public:
            inline static const std::string CALCULATION_DATA = "Rekendata";

            inline static const std::string HYDRAULIC_LOADS = "HydraulischeBelastingen";
            inline static const std::string LOCATIONS = "Locaties";

            inline static const std::string TIME = "Tijd";
            inline static const std::string MAXIMUM_WAVE_ANGLE = "GolfhoekMaximum";
            inline static const std::string BOUNDARY_CONDITIONS_PER_TIME_STEP = "RandvoorwaardenPerTijdstap";
            inline static const std::string WATER_LEVEL = "Waterstand";
            inline static const std::string WAVE_HEIGHT_HM0 = "GolfhoogteHm0";
            inline static const std::string WAVE_PERIOD_TM10 = "GolfperiodeTm10";
            inline static const std::string WAVE_ANGLE = "Golfhoek";

            inline static const std::string NAME = "Naam";
            inline static const std::string REVETMENT = "Bekleding";
            inline static const std::string TYPE_TOP_LAYER = "TypeToplaag";
            inline static const std::string RELATIVE_DENSITY = "RelatieveDichtheid";
            inline static const std::string THICKNESS_TOP_LAYER = "DikteToplaag";
            inline static const std::string INITIAL_DAMAGE = "BeginSchade";
            inline static const std::string CRITICAL_DAMAGE = "Faalgetal";
            inline static const std::string SIMILARITY_PARAMETER_THRESHOLD = "BrekerIndexGrenswaarde";
            inline static const std::string COEFFICIENT_PLUNGING_AP = "CoefficientPlungingAp";
            inline static const std::string COEFFICIENT_PLUNGING_BP = "CoefficientPlungingBp";
            inline static const std::string COEFFICIENT_PLUNGING_CP = "CoefficientPlungingCp";
            inline static const std::string COEFFICIENT_PLUNGING_NP = "CoefficientPlungingNp";
            inline static const std::string COEFFICIENT_SURGING_AS = "CoefficientSurgingAs";
            inline static const std::string COEFFICIENT_SURGING_BS = "CoefficientSurgingBs";
            inline static const std::string COEFFICIENT_SURGING_CS = "CoefficientSurgingCs";
            inline static const std::string COEFFICIENT_SURGING_NS = "CoefficientSurgingNs";
            inline static const std::string PROFILE_SCHEMATIZATION = "Profielschematisatie";
            inline static const std::string TAN_A = "TanA";
            inline static const std::string POSITION_Z = "PositieZ";

            inline static const std::string DAMAGE = "Schade";
            inline static const std::string DAMAGE_OVER_TIME = "SchadegetalPerTijd";
    };
}
