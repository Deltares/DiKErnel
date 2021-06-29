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
    class JsonInputAsphaltWaveImpactDefinitions
    {
        public:
            inline static const std::string TOP_LAYER_TYPE_HYDRAULIC_ASPHALT_CONCRETE = "WaterbouwAsfaltBeton";

            inline static const std::string FAILURE_TENSION = "BreuksterkteAsfalt";
            inline static const std::string DENSITY_OF_WATER = "SoortelijkeDichtheidWater";
            inline static const std::string SOIL_ELASTICITY = "VeerconstanteOndergrond";

            inline static const std::string UPPER_LAYER = "Toplaag";
            inline static const std::string SUB_LAYER = "Onderlaag";

            inline static const std::string THICKNESS = "Dikte";
            inline static const std::string ELASTIC_MODULUS= "Stijfheidsmodulus";

            inline static const std::string FATIGUE = "VermoeiingAsfaltbekleding";
            inline static const std::string FATIGUE_ALPHA = "VermoeiingAsfaltbekledingAlfa";
            inline static const std::string FATIGUE_BETA = "VermoeiingAsfaltbekledingBeta";

            inline static const std::string IMPACT_NUMBER = "Stootgetal";
            inline static const std::string IMPACT_NUMBER_C = "StootgetalC";

            inline static const std::string STIFFNESS_RELATION = "Stijfheidsverhouding";
            inline static const std::string STIFFNESS_RELATION_NU = "StijfheidsverhoudingNu";

            inline static const std::string WIDTH_FACTORS = "BreedteFactorenTabel";
            inline static const std::string DEPTH_FACTORS = "DiepteFactorenTabel";
            inline static const std::string IMPACT_FACTORS = "StootFactorenTabel";
    };
}
