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

#include "NaturalStoneRevetmentDefaults.h"

namespace DiKErnel::DomainLibrary
{
    const double NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_XIB = 2.9;
    const double NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_AP = 4;
    const double NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_BP = 0;
    const double NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_CP = 0;
    const double NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_NP = -0.9;
    const double NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_AS = 0.8;
    const double NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_BS = 0;
    const double NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_CS = 0;
    const double NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_NS = 0.6;

    const double NaturalStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_AUL = 0.1;
    const double NaturalStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_BUL = 0.6;
    const double NaturalStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_CUL = 4;

    const double NaturalStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_ALL = 0.1;
    const double NaturalStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_BLL = 0.2;
    const double NaturalStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_CLL = 4;

    const double NaturalStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NORDIC_STONE_ASMAX = 0.42;
    const double NaturalStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NORDIC_STONE_BSMAX = 0.9;

    const double NaturalStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_NORDIC_STONE_AWI = 0.96;
    const double NaturalStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_NORDIC_STONE_BWI = 0.11;
}
