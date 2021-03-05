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

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * \brief Class containing input Json related constants.
     */
    class InputJsonDefinitions
    {
        friend class InputComposer;

        static const std::string CALCULATION_DATA;
        static const std::string HYDRAULIC_LOADS;
        static const std::string LOCATIONS;

        static const std::string TIME;
        static const std::string MAXIMUM_WAVE_ANGLE;
        static const std::string BOUNDARY_CONDITIONS_PER_TIME_STEP;
        static const std::string WATER_LEVEL;
        static const std::string WAVE_HEIGHT_HM0;
        static const std::string WAVE_PERIOD_TM10;
        static const std::string WAVE_ANGLE;

        static const std::string NAME;
        static const std::string REVETMENT;
        static const std::string TYPE_TOP_LAYER;
        static const std::string RELATIVE_DENSITY;
        static const std::string THICKNESS_TOP_LAYER;
        static const std::string INITIAL_DAMAGE;
        static const std::string CRITICAL_DAMAGE;
        static const std::string SIMILARITY_PARAMETER_THRESHOLD;
        static const std::string COEFFICIENT_PLUNGING_AP;
        static const std::string COEFFICIENT_PLUNGING_BP;
        static const std::string COEFFICIENT_PLUNGING_CP;
        static const std::string COEFFICIENT_PLUNGING_NP;
        static const std::string COEFFICIENT_SURGING_AS;
        static const std::string COEFFICIENT_SURGING_BS;
        static const std::string COEFFICIENT_SURGING_CS;
        static const std::string COEFFICIENT_SURGING_NS;
        static const std::string PROFILE_SCHEMATIZATION;
        static const std::string TAN_A;
        static const std::string POSITION_Z;

        static const std::string CALCULATION_METHOD;
        static const std::string CALCULATION_METHOD_SORT;

        static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE;
        static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_XIB;
        static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_AP;
        static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_BP;
        static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_CP;
        static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_NP;
        static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_AS;
        static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_BS;
        static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_CS;
        static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_NS;

        static const std::string UPPER_LIMIT_LOADING_OF_NATURAL_STONE;
        static const std::string UPPER_LIMIT_LOADING_OF_NATURAL_STONE_AUL;
        static const std::string UPPER_LIMIT_LOADING_OF_NATURAL_STONE_BUL;
        static const std::string UPPER_LIMIT_LOADING_OF_NATURAL_STONE_CUL;

        static const std::string LOWER_LIMIT_LOADING_OF_NATURAL_STONE;
        static const std::string LOWER_LIMIT_LOADING_OF_NATURAL_STONE_AUL;
        static const std::string LOWER_LIMIT_LOADING_OF_NATURAL_STONE_BUL;
        static const std::string LOWER_LIMIT_LOADING_OF_NATURAL_STONE_CUL;

        static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE;
        static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_ASMAX;
        static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_BSMAX;

        static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT;
        static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI;
        static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI;

        static const std::string DAMAGE;
        static const std::string DAMAGE_OVER_TIME;
    };
}
