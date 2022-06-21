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
            inline static const std::string PROCESS_DATA = "procesdata";

            inline static const std::string PROCESS_TYPE = "uitvoerRekenresultaten";
            inline static const std::string PROCESS_TYPE_FAILURE = "falen";
            inline static const std::string PROCESS_TYPE_DAMAGE = "schade";
            inline static const std::string PROCESS_TYPE_PHYSICS = "fysica";

            inline static const std::string CALCULATION_DATA = "rekendata";

            inline static const std::string HYDRAULIC_LOADS = "hydraulischeBelastingen";
            inline static const std::string LOCATIONS = "locaties";

            inline static const std::string TIME = "tijd";
            inline static const std::string WATER_LEVEL = "waterstand";
            inline static const std::string WAVE_HEIGHT_HM0 = "golfhoogteHm0";
            inline static const std::string WAVE_PERIOD_TM10 = "golfperiodeTm10";
            inline static const std::string WAVE_ANGLE = "golfhoek";

            inline static const std::string DIKE_PROFILE = "dijkprofiel";
            inline static const std::string DIKE_PROFILE_POINT_X = "positie";
            inline static const std::string DIKE_PROFILE_POINT_Z = "hoogte";

            inline static const std::string CHARACTERISTIC_POINT = "karakteristiekPunt";
            inline static const std::string CHARACTERISTIC_POINT_TYPE_OUTER_TOE = "teenBuitenzijde";
            inline static const std::string CHARACTERISTIC_POINT_TYPE_OUTER_CREST = "kruinBuitenzijde";
            inline static const std::string CHARACTERISTIC_POINT_TYPE_CREST_OUTER_BERM = "kruinBermBuitenzijde";
            inline static const std::string CHARACTERISTIC_POINT_TYPE_NOTCH_OUTER_BERM = "insteekBermBuitenzijde";

            inline static const std::string X = "positieLocatie";
            inline static const std::string INITIAL_DAMAGE = "beginSchade";
            inline static const std::string FAILURE_NUMBER = "faalgetal";

            inline static const std::string TOP_LAYERS = "toplagen";
            inline static const std::string TYPE_TOP_LAYER = "typeToplaag";

            inline static const std::string AVERAGE_NUMBER_OF_WAVES = "gemiddeldAantalGolvenPerTijdstap";
            inline static const std::string AVERAGE_NUMBER_OF_WAVES_CTM = "gemiddeldAantalGolvenPerTijdstapCtm";

            inline static const std::string CALCULATION_METHODS = "rekenmethoden";
            inline static const std::string CALCULATION_METHOD_TYPE = "rekenmethodeSoort";

            inline static const std::string CALCULATION_METHOD_TYPE_ASPHALT_WAVE_IMPACT = "asfaltGolfklap";
            inline static const std::string CALCULATION_METHOD_TYPE_GRASS_WAVE_IMPACT = "grasGolfklap";
            inline static const std::string CALCULATION_METHOD_TYPE_GRASS_WAVE_RUNUP = "grasGolfoploop";
            inline static const std::string CALCULATION_METHOD_TYPE_NATURAL_STONE = "natuursteen";

            inline static const std::string OUTER_SLOPE = "tanA";
    };
}
