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

            inline static const std::string HYDRAULIC_LOADS = "HydraulischeBelastingen";
            inline static const std::string LOCATIONS = "Locaties";

            inline static const std::string TIME = "Tijd";
            inline static const std::string WATER_LEVEL = "Waterstand";
            inline static const std::string WAVE_HEIGHT_HM0 = "GolfhoogteHm0";
            inline static const std::string WAVE_PERIOD_TM10 = "GolfperiodeTm10";
            inline static const std::string WAVE_ANGLE = "Golfhoek";

            inline static const std::string DIKE_PROFILE = "Dijkprofiel";
            inline static const std::string DIKE_PROFILE_POINT_X = "Positie";
            inline static const std::string DIKE_PROFILE_POINT_Z = "Hoogte";

            inline static const std::string CHARACTERISTIC_POINT = "KarakteristiekPunt";
            inline static const std::string CHARACTERISTIC_POINT_TYPE_OUTER_TOE = "TeenBuitenzijde";
            inline static const std::string CHARACTERISTIC_POINT_TYPE_OUTER_CREST = "KruinBuitenzijde";
            inline static const std::string CHARACTERISTIC_POINT_TYPE_CREST_OUTER_BERM = "KruinBermBuitenzijde";
            inline static const std::string CHARACTERISTIC_POINT_TYPE_NOTCH_OUTER_BERM = "InsteekBermBuitenzijde";

            inline static const std::string X = "PositieLocatie";
            inline static const std::string INITIAL_DAMAGE = "BeginSchade";
            inline static const std::string FAILURE_NUMBER = "Faalgetal";

            inline static const std::string TOP_LAYERS = "Toplagen";
            inline static const std::string TYPE_TOP_LAYER = "TypeToplaag";

            inline static const std::string AVERAGE_NUMBER_OF_WAVES = "GemiddeldAantalGolvenPerTijdstap";
            inline static const std::string AVERAGE_NUMBER_OF_WAVES_CTM = "GemiddeldAantalGolvenPerTijdstapCtm";

            inline static const std::string CALCULATION_METHODS = "Rekenmethoden";
            inline static const std::string CALCULATION_METHOD_TYPE = "RekenmethodeSoort";

            inline static const std::string CALCULATION_METHOD_TYPE_ASPHALT_WAVE_IMPACT = "AsfaltGolfklap";
            inline static const std::string CALCULATION_METHOD_TYPE_GRASS_WAVE_IMPACT = "GrasGolfklap";
            inline static const std::string CALCULATION_METHOD_TYPE_GRASS_WAVE_RUNUP = "GrasGolfoploop";
            inline static const std::string CALCULATION_METHOD_TYPE_NATURAL_STONE = "Natuursteen";

            inline static const std::string OUTER_SLOPE = "TanA";
    };
}
