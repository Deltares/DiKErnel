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
            inline static const std::string DAMAGE = "Schade";
            inline static const std::string INITIAL_DAMAGE = "BeginSchade";
            inline static const std::string CRITICAL_DAMAGE = "Faalgetal";

            inline static const std::string REVETMENT = "Bekleding";
            inline static const std::string TYPE_TOP_LAYER = "TypeToplaag";
            inline static const std::string RELATIVE_DENSITY = "RelatieveDichtheid";
            inline static const std::string THICKNESS_TOP_LAYER = "DikteToplaag";

            inline static const std::string CALCULATION_METHOD = "Rekenmethode";
            inline static const std::string CALCULATION_METHOD_TYPE = "RekenmethodeSoort";

            inline static const std::string CALCULATION_METHOD_TYPE_NATURAL_STONE = "Natuursteen";

            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE = "HydraulischeBelastingNatuurSteen";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_XIB = "HydraulischeBelastingNatuurSteenXIb";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_AP = "HydraulischeBelastingNatuurSteenAp";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_BP = "HydraulischeBelastingNatuurSteenBp";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_CP = "HydraulischeBelastingNatuurSteenCp";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_NP = "HydraulischeBelastingNatuurSteenNp";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_AS = "HydraulischeBelastingNatuurSteenAs";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_BS = "HydraulischeBelastingNatuurSteenBs";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_CS = "HydraulischeBelastingNatuurSteenCs";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_NS = "HydraulischeBelastingNatuurSteenNs";

            inline static const std::string UPPER_LIMIT_LOADING_OF_NATURAL_STONE = "BovengrensBelastingNatuursteen";
            inline static const std::string UPPER_LIMIT_LOADING_OF_NATURAL_STONE_AUL = "BovengrensBelastingNatuursteenAul";
            inline static const std::string UPPER_LIMIT_LOADING_OF_NATURAL_STONE_BUL = "BovengrensBelastingNatuursteenBul";
            inline static const std::string UPPER_LIMIT_LOADING_OF_NATURAL_STONE_CUL = "BovengrensBelastingNatuursteenCul";

            inline static const std::string LOWER_LIMIT_LOADING_OF_NATURAL_STONE = "OndergrensBelastingNatuursteen";
            inline static const std::string LOWER_LIMIT_LOADING_OF_NATURAL_STONE_ALL = "OndergrensBelastingNatuursteenAll";
            inline static const std::string LOWER_LIMIT_LOADING_OF_NATURAL_STONE_BLL = "OndergrensBelastingNatuursteenBll";
            inline static const std::string LOWER_LIMIT_LOADING_OF_NATURAL_STONE_CLL = "OndergrensBelastingNatuursteenCll";

            inline static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE = "AfstandMaximaleStijghoogte";
            inline static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_ASMAX = "AfstandMaximaleStijghoogteAsmax";
            inline static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_BSMAX = "AfstandMaximaleStijghoogteBsmax";

            inline static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT = "MaatgevendeBreedteGolfklap";
            inline static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI = "MaatgevendeBreedteGolfklapAwi";
            inline static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI = "MaatgevendeBreedteGolfklapBwi";

            inline static const std::string PROFILE_SCHEMATIZATION = "Profielschematisatie";
            inline static const std::string TAN_A = "TanA";
            inline static const std::string POSITION_Z = "PositieZ";
    };
}
