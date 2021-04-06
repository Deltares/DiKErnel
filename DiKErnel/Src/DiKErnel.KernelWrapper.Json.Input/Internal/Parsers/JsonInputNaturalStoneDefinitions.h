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
    class JsonInputNaturalStoneDefinitions
    {
        public:
            inline static const std::string RELATIVE_DENSITY = "RelatieveDichtheid";
            inline static const std::string THICKNESS_TOP_LAYER = "DikteToplaag";

            inline static const std::string HYDRAULIC_LOAD = "ToenameSchadeNatuursteen";
            inline static const std::string HYDRAULIC_LOAD_XIB = "HydraulischeBelastingNatuursteenXib";
            inline static const std::string HYDRAULIC_LOAD_AP = "HydraulischeBelastingNatuursteenAp";
            inline static const std::string HYDRAULIC_LOAD_BP = "HydraulischeBelastingNatuursteenBp";
            inline static const std::string HYDRAULIC_LOAD_CP = "HydraulischeBelastingNatuursteenCp";
            inline static const std::string HYDRAULIC_LOAD_NP = "HydraulischeBelastingNatuursteenNp";
            inline static const std::string HYDRAULIC_LOAD_AS = "HydraulischeBelastingNatuursteenAs";
            inline static const std::string HYDRAULIC_LOAD_BS = "HydraulischeBelastingNatuursteenBs";
            inline static const std::string HYDRAULIC_LOAD_CS = "HydraulischeBelastingNatuursteenCs";
            inline static const std::string HYDRAULIC_LOAD_NS = "HydraulischeBelastingNatuursteenNs";

            inline static const std::string UPPER_LIMIT_LOADING = "BovengrensBelastingNatuursteen";
            inline static const std::string UPPER_LIMIT_LOADING_AUL = "BovengrensBelastingNatuursteenAul";
            inline static const std::string UPPER_LIMIT_LOADING_BUL = "BovengrensBelastingNatuursteenBul";
            inline static const std::string UPPER_LIMIT_LOADING_CUL = "BovengrensBelastingNatuursteenCul";

            inline static const std::string LOWER_LIMIT_LOADING = "OndergrensBelastingNatuursteen";
            inline static const std::string LOWER_LIMIT_LOADING_ALL = "OndergrensBelastingNatuursteenAll";
            inline static const std::string LOWER_LIMIT_LOADING_BLL = "OndergrensBelastingNatuursteenBll";
            inline static const std::string LOWER_LIMIT_LOADING_CLL = "OndergrensBelastingNatuursteenCll";

            inline static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION = "AfstandMaximaleStijghoogteNatuursteen";
            inline static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION_ASMAX = "AfstandMaximaleStijghoogteNatuursteenAsmax";
            inline static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION_BSMAX = "AfstandMaximaleStijghoogteNatuursteenBsmax";

            inline static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT = "MaatgevendeBreedteGolfklapNatuursteen";
            inline static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI = "MaatgevendeBreedteGolfklapNatuursteenAwi";
            inline static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI = "MaatgevendeBreedteGolfklapNatuursteenBwi";

            inline static const std::string WAVE_ANGLE_IMPACT = "ImpactGolfhoekBekledingNatuursteen";
            inline static const std::string WAVE_ANGLE_IMPACT_BETAMAX = "ImpactGolfhoekBekledingNatuursteenBetamax";

            inline static const std::string TOP_LAYER_TYPE_NORDIC_STONE = "NoorseSteen";
    };
}
