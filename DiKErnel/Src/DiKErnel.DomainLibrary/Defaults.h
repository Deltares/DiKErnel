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

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that contains domain default values.
     */
    class Defaults
    {
        public:
            /*!
             * \brief The critical damage value.
             *        Unit = [-]
             */
            static const double CRITICAL_DAMAGE;

            static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_XIB;
            static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_AP;
            static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_BP;
            static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_CP;
            static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_NP;
            static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_AS;
            static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_BS;
            static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_CS;
            static const double HYDRAULIC_LOAD_ON_NATURAL_STONE_NS;
            
            static const double UPPER_LIMIT_LOADING_OF_NATURAL_STONE_AUL;
            static const double UPPER_LIMIT_LOADING_OF_NATURAL_STONE_BUL;
            static const double UPPER_LIMIT_LOADING_OF_NATURAL_STONE_CUL;
            
            static const double LOWER_LIMIT_LOADING_OF_NATURAL_STONE_ALL;
            static const double LOWER_LIMIT_LOADING_OF_NATURAL_STONE_BLL;
            static const double LOWER_LIMIT_LOADING_OF_NATURAL_STONE_CLL;
            
            static const double DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_ASMAX;
            static const double DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_BSMAX;
            
            static const double NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI;
            static const double NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI;
    };
}
