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
    class JsonInputAsphaltWaveImpactDefinitions
    {
        public:
            inline static const std::string TOP_LAYER_TYPE_HYDRAULIC_ASPHALT_CONCRETE = "waterbouwAsfaltBeton";

            inline static const std::string FAILURE_TENSION = "breuksterkteAsfalt";
            inline static const std::string DENSITY_OF_WATER = "soortelijkeDichtheidWater";
            inline static const std::string SOIL_ELASTICITY = "veerconstanteOndergrond";

            inline static const std::string UPPER_LAYER = "toplaag";
            inline static const std::string SUB_LAYER = "onderlaag";

            inline static const std::string THICKNESS = "dikte";
            inline static const std::string ELASTIC_MODULUS = "stijfheidsmodulus";

            inline static const std::string FATIGUE = "vermoeiingAsfaltbekleding";
            inline static const std::string FATIGUE_ALPHA = "vermoeiingAsfaltbekledingAlfa";
            inline static const std::string FATIGUE_BETA = "vermoeiingAsfaltbekledingBeta";

            inline static const std::string IMPACT_NUMBER = "stootgetal";
            inline static const std::string IMPACT_NUMBER_C = "stootgetalC";

            inline static const std::string STIFFNESS_RELATION = "stijfheidsverhouding";
            inline static const std::string STIFFNESS_RELATION_NU = "stijfheidsverhoudingNu";

            inline static const std::string WIDTH_FACTORS = "breedteFactorenTabel";
            inline static const std::string DEPTH_FACTORS = "diepteFactorenTabel";
            inline static const std::string IMPACT_FACTORS = "stootFactorenTabel";
    };
}
