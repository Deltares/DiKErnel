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

namespace DiKErnel::KernelWrapper::Json::Output
{
    class JsonOutputNaturalStoneRevetmentDefinitions
    {
        public:
            inline static const std::string INCREMENT_DAMAGE = "ToenameSchadeNatuursteen";

            inline static const std::string OUTER_SLOPE = "HellingBuitentaludNatuursteen";
            inline static const std::string SLOPE_UPPER_LEVEL = "BovenzijdeHellingvlakNatuursteen";
            inline static const std::string SLOPE_UPPER_POSITION = "RechterzijdeHellingvlakNatuursteen";
            inline static const std::string SLOPE_LOWER_LEVEL = "OnderzijdeHellingvlakNatuursteen";
            inline static const std::string SLOPE_LOWER_POSITION = "LinkerzijdeHellingvlakNatuursteen";

            inline static const std::string SURF_SIMILARITY_PARAMETER = "Golfbrekingparameter";
            inline static const std::string WAVE_STEEPNESS_DEEP_WATER = "GolfsteilheidDiepWater";

            inline static const std::string UPPER_LIMIT_LOADING = "BovengrensBelastingNatuursteen";
            inline static const std::string LOWER_LIMIT_LOADING = "OndergrensBelastingNatuursteen";
            inline static const std::string DEPTH_MAXIMUM_WAVE_LOAD = "DiepteMaximaleGolfbelastingNatuursteen";
            inline static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION = "AfstandMaximaleStijghoogteNatuursteen";
            inline static const std::string NORMATIVE_WIDTH_WAVE_IMPACT = "MaatgevendeBreedteGolfklapNatuursteen";
            inline static const std::string HYDRAULIC_LOAD = "HydraulischeBelastingNatuursteen";
            inline static const std::string WAVE_ANGLE_IMPACT = "ImpactGolfhoekBekledingNatuursteen";
            inline static const std::string RESISTANCE = "SterkteBekledingNatuursteen";
            inline static const std::string REFERENCE_TIME_DEGRADATION = "ReferentieTijdDegradatieNatuursteen";
            inline static const std::string REFERENCE_DEGRADATION = "ReferentieDegradatieNatuursteen";
    };
}
