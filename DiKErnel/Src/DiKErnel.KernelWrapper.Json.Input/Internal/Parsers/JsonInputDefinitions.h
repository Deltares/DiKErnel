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
    class JsonInputDefinitions
    {
        public:
            inline static const std::string HYDRAULIC_LOADS = "hydraulischeBelastingen";
            inline static const std::string LOCATIONS = "locaties";

            inline static const std::string TIME = "tijdstippen";
            inline static const std::string WATER_LEVELS = "waterstanden";
            inline static const std::string WAVE_HEIGHTS_HM0 = "golfhoogtenHm0";
            inline static const std::string WAVE_PERIODS_TM10 = "golfperiodenTm10";
            inline static const std::string WAVE_ANGLES = "golfhoeken";

            inline static const std::string DIKE_PROFILE = "dijkprofiel";
            inline static const std::string DIKE_PROFILE_POINTS_X = "posities";
            inline static const std::string DIKE_PROFILE_POINTS_Z = "hoogten";

            inline static const std::string CHARACTERISTIC_POINT_TYPE_OUTER_TOE = "teenBuitenzijde";
            inline static const std::string CHARACTERISTIC_POINT_TYPE_OUTER_CREST = "kruinBuitenzijde";
            inline static const std::string CHARACTERISTIC_POINT_TYPE_CREST_OUTER_BERM = "kruinBermBuitenzijde";
            inline static const std::string CHARACTERISTIC_POINT_TYPE_NOTCH_OUTER_BERM = "insteekBermBuitenzijde";

            inline static const std::string X = "positie";
            inline static const std::string INITIAL_DAMAGE = "beginschade";
            inline static const std::string FAILURE_NUMBER = "faalgetal";

            inline static const std::string CALCULATION_METHODS = "rekenmethoden";
            inline static const std::string CALCULATION_METHOD_TYPE = "rekenmethode";

            inline static const std::string CALCULATION_METHOD_TYPE_ASPHALT_WAVE_IMPACT = "asfaltGolfklap";
            inline static const std::string CALCULATION_METHOD_TYPE_GRASS_WAVE_IMPACT = "grasGolfklap";
            inline static const std::string CALCULATION_METHOD_TYPE_GRASS_WAVE_RUNUP = "grasGolfoploop";
            inline static const std::string CALCULATION_METHOD_TYPE_NATURAL_STONE = "natuursteen";

            inline static const std::string TOP_LAYERS = "toplagen";
            inline static const std::string TYPE_TOP_LAYER = "typeToplaag";

            inline static const std::string A_COEFFICIENT = "a";
            inline static const std::string B_COEFFICIENT = "b";
            inline static const std::string C_COEFFICIENT = "c";

            inline static const std::string LOADING_AREA = "belastingzone";
            inline static const std::string UPPER_LIMIT = "bovengrens";
            inline static const std::string LOWER_LIMIT = "ondergrens";

            inline static const std::string WAVE_ANGLE_IMPACT = "impactGolfhoek";
            inline static const std::string BETA_MAX = "betaMax";

            inline static const std::string FACTOR_CTM = "factorCtm";

            inline static const std::string OUTER_SLOPE = "tanA";
    };
}
