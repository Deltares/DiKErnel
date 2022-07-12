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
            inline static const std::string SLOPE_UPPER_LEVEL = "bovenzijdeHellingvlak";
            inline static const std::string SLOPE_UPPER_POSITION = "rechterzijdeHellingvlak";
            inline static const std::string SLOPE_LOWER_LEVEL = "onderzijdeHellingvlak";
            inline static const std::string SLOPE_LOWER_POSITION = "linkerzijdeHellingvlak";

            inline static const std::string SURF_SIMILARITY_PARAMETER = "golfbrekingparameter";
            inline static const std::string WAVE_STEEPNESS_DEEP_WATER = "golfsteilheidDiepWater";

            inline static const std::string DEPTH_MAXIMUM_WAVE_LOAD = "diepteMaximaleGolfbelasting";
            inline static const std::string DISTANCE_MAXIMUM_WAVE_ELEVATION = "afstandMaximaleStijghoogte";
            inline static const std::string NORMATIVE_WIDTH_WAVE_IMPACT = "maatgevendeBreedteGolfklap";
            inline static const std::string HYDRAULIC_LOAD = "hydraulischeBelasting";
            inline static const std::string RESISTANCE = "sterkteBekleding";
            inline static const std::string REFERENCE_TIME_DEGRADATION = "referentieTijdDegradatie";
            inline static const std::string REFERENCE_DEGRADATION = "referentieDegradatie";
    };
}
