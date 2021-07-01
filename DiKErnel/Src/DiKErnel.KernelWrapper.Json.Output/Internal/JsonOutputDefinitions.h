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

namespace DiKErnel::KernelWrapper::Json::Output
{
    class JsonOutputDefinitions
    {
        public:
            inline static const std::string OUTPUT_DATA = "Uitvoerdata";

            inline static const std::string TIME = "Tijd";

            inline static const std::string LOCATIONS = "Locaties";
            inline static const std::string NAME = "Naam";

            inline static const std::string FAILURE_REVETMENT = "FalenBekleding";
            inline static const std::string FAILED = "Faalgebeurtenis";
            inline static const std::string TIME_OF_FAILURE = "Faaltijd";

            inline static const std::string DAMAGE_REVETMENT = "SchadeBekleding";
            inline static const std::string INITIAL_DAMAGE = "Beginschade";
            inline static const std::string FAILURE_NUMBER = "Faalgetal";
            inline static const std::string DAMAGE_OVER_TIME = "SchadegetalPerTijd";

            inline static const std::string PHYSICS_REVETMENT = "FysicaBekleding";
            inline static const std::string TOP_LAYER_TYPE = "TypeToplaag";
            inline static const std::string CALCULATION_TYPE = "RekenmethodeSoort";

            inline static const std::string HYDRAULIC_LOAD = "BelastingBekleding";
            inline static const std::string SURF_SIMILARITY_PARAMETER = "Golfbrekingparameter";
            inline static const std::string WAVE_STEEPNESS_DEEP_WATER = "GolfsteilheidDiepWater";
    };
}
