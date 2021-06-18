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
    class JsonInputAsphaltRevetmentDefinitions
    {
        public:
            inline static const std::string TOP_LAYER_TYPE_WAD = "WaterbouwAsfaltBeton";

            inline static const std::string FAILURE_TENSION = "BreuksterkteAsfalt";
            inline static const std::string DENSITY_OF_WATER = "SoortelijkeDichtheidWater";
            inline static const std::string SOIL_ELASTICITY = "VeerconstanteOndergrond";
            inline static const std::string THICKNESS_UPPER_LAYER = "DikteAsfaltToplaag";
            inline static const std::string THICKNESS_SUB_LAYER = "DikteAsfaltOnderlaag";
            inline static const std::string ELASTIC_MODULUS_UPPER_LAYER = "StijfheidsmodulusAsfaltToplaag";
            inline static const std::string ELASTIC_MODULUS_SUB_LAYER = "StijfheidsmodulusAsfaltOnderlaag";

            inline static const std::string FATIGUE = "VermoeiingAsfaltbekleding";
            inline static const std::string FATIGUE_ALPHA = "VermoeiingAsfaltbekledingAlfa";
            inline static const std::string FATIGUE_BETA = "VermoeiingAsfaltbekledingBeta";

            inline static const std::string IMPACT_NUMBER = "Stootgetal";
            inline static const std::string IMPACT_NUMBER_C = "StootgetalC";

            inline static const std::string STIFFNESS_RELATION = "Stijfheidsverhouding";
            inline static const std::string STIFFNESS_RELATION_NU = "StijfheidsverhoudingNu";
    };
}
