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
            inline static const std::string CALCULATION_METHOD_TYPE_NATURAL_STONE = "NatuurSteen";

            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE = "ToenameSchadeNatuursteen";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_XIB = "HydraulischeBelastingNatuursteenXib";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_AP = "HydraulischeBelastingNatuursteenAp";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_BP = "HydraulischeBelastingNatuursteenBp";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_CP = "HydraulischeBelastingNatuursteenCp";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_NP = "HydraulischeBelastingNatuursteenNp";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_AS = "HydraulischeBelastingNatuursteenAs";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_BS = "HydraulischeBelastingNatuursteenBs";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_CS = "HydraulischeBelastingNatuursteenCs";
            inline static const std::string HYDRAULIC_LOAD_ON_NATURAL_STONE_NS = "HydraulischeBelastingNatuursteenNs";

            inline static const std::string UPPER_LIMIT_LOADING_OF_NATURAL_STONE = "BovengrensBelastingNatuursteen";
            inline static const std::string UPPER_LIMIT_LOADING_OF_NATURAL_STONE_AUL = "BovengrensBelastingNatuursteenAul";
            inline static const std::string UPPER_LIMIT_LOADING_OF_NATURAL_STONE_BUL = "BovengrensBelastingNatuursteenBul";
            inline static const std::string UPPER_LIMIT_LOADING_OF_NATURAL_STONE_CUL = "BovengrensBelastingNatuursteenCul";

            inline static const std::string LOWER_LIMIT_LOADING_OF_NATURAL_STONE = "OndergrensBelastingNatuursteen";
            inline static const std::string LOWER_LIMIT_LOADING_OF_NATURAL_STONE_ALL = "OndergrensBelastingNatuursteenAll";
            inline static const std::string LOWER_LIMIT_LOADING_OF_NATURAL_STONE_BLL = "OndergrensBelastingNatuursteenBll";
            inline static const std::string LOWER_LIMIT_LOADING_OF_NATURAL_STONE_CLL = "OndergrensBelastingNatuursteenCll";

            inline static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE = "AfstandMaximaleStijghoogteNatuursteen";
            inline static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_ASMAX = "AfstandMaximaleStijghoogteNatuursteenAsmax";
            inline static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_BSMAX = "AfstandMaximaleStijghoogteNatuursteenBsmax";

            inline static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE = "MaatgevendeBreedteGolfklapNatuursteen";
            inline static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE_AWI = "MaatgevendeBreedteGolfklapNatuursteenAwi";
            inline static const std::string NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE_BWI = "MaatgevendeBreedteGolfklapNatuursteenBwi";

            inline static const std::string WAVE_ANGLE_IMPACT_ON_NATURAL_STONE = "ImpactGolfhoekBekledingNatuursteen";
            inline static const std::string WAVE_ANGLE_IMPACT_ON_NATURAL_STONE_BETA_MAX = "ImpactGolfhoekBekledingNatuursteenBetamax";

            inline static const std::string TOP_LAYER_TYPE_NORDIC_STONE = "Noorse Steen";
    };
}
