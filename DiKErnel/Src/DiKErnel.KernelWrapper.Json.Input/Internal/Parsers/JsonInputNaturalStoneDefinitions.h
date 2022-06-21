// Copyright (C) Stichting Deltares 2022. All rights reserved.
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
    class JsonInputNaturalStoneDefinitions
    {
        public:
            inline static const std::string RELATIVE_DENSITY = "relatieveDichtheid";
            inline static const std::string THICKNESS_TOP_LAYER = "dikteToplaag";

            inline static const std::string STABILITY = "stabiliteit";
            inline static const std::string STABILITY_PLUNGING = "plunging";
            inline static const std::string STABILITY_SURGING = "surging";

            inline static const std::string N_COEFFICIENT = "n";
            inline static const std::string XIB_COEFFICIENT = "xib";

            inline static const std::string SLOPE = "hellingvlak";
            inline static const std::string SLOPE_UPPER_LEVEL = "bovenzijde";
            inline static const std::string SLOPE_LOWER_LEVEL = "onderzijde";

            inline static const std::string UPPER_LIMIT_LOADING = "bovengrensBelastingNatuursteen";
            inline static const std::string UPPER_LIMIT_LOADING_AUL = "bovengrensBelastingNatuursteenAul";
            inline static const std::string UPPER_LIMIT_LOADING_BUL = "bovengrensBelastingNatuursteenBul";
            inline static const std::string UPPER_LIMIT_LOADING_CUL = "bovengrensBelastingNatuursteenCul";

            inline static const std::string LOWER_LIMIT_LOADING = "ondergrensBelastingNatuursteen";
            inline static const std::string LOWER_LIMIT_LOADING_ALL = "ondergrensBelastingNatuursteenAll";
            inline static const std::string LOWER_LIMIT_LOADING_BLL = "ondergrensBelastingNatuursteenBll";
            inline static const std::string LOWER_LIMIT_LOADING_CLL = "ondergrensBelastingNatuursteenCll";

            inline static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION = "afstandMaximaleStijghoogteNatuursteen";
            inline static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION_ASMAX = "afstandMaximaleStijghoogteNatuursteenAsmax";
            inline static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION_BSMAX = "afstandMaximaleStijghoogteNatuursteenBsmax";

            inline static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT = "maatgevendeBreedteGolfklapNatuursteen";
            inline static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI = "maatgevendeBreedteGolfklapNatuursteenAwi";
            inline static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI = "maatgevendeBreedteGolfklapNatuursteenBwi";

            inline static const std::string WAVE_ANGLE_IMPACT = "impactGolfhoekBekledingNatuursteen";
            inline static const std::string WAVE_ANGLE_IMPACT_BETAMAX = "impactGolfhoekBekledingNatuursteenBetamax";

            inline static const std::string TOP_LAYER_TYPE_NORDIC_STONE = "noorseSteen";
    };
}
